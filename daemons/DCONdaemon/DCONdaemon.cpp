//
// Simple DCON daemon.  
// Used to interface ICP modules to pvbrowser using shared memory and mailbox
// Uses serial interface and rllib for communication.
// A static structure defines all communication cycles. Each measure value is put
// in shared memory as an array of byte. The value is represented as an ascii coded
// floating point decimal number. Max negative value is used as a flag for errors 
// Only one value is read at a time (7017 can return 8 values with one comand)
// Can also receive commands from a mailbox and send to the ICP modules.
// DCON uses a simple protocol structure with ascii coded commands and responses
// Get measure value  #aac\r      aa=module adress(hex), c= subadress (input nr)
// Response           >xxxxxxx\r  depending on module and setup engineering unit +nnn.nn, hex 0a77, 
//                                % of fsr +97.3 etc 
// Most modules can also be configured from the bus
//
// The daemon can use an updated rlserial (select timeout)  by changing a define, for faster response if needed

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rlsharedmemory.h"
#include "rlmailbox.h"
#include "rlthread.h"
#include "rlserial.h"
#include <ctype.h>
#include "DCONdaemon.h"


//serial
#define RLLIB_SELECT_ERROR 1		// Set if select timeout error for Linux still in rllib

// Times may have to be adjusted for different baudrate, cpu-speed and module configuration!

#define SERIAL_RESPONSETIME 16        	//time for message to be sent, modules to respond, interupt latency
#define SERIAL_TIMEOUT 8		//timeout when polling for characters
#define SERIAL_IDLETIME 1		//turn around time send/receive
#define SERIAL_CYCLETIME_ADJ 0		//delay to adjust serial cycle time

#define SERIAL_DEVICE   "/dev/ttyS0"	//default serial port
//#define SERIAL_DEVICE   "/dev/ttyUSB0"	//USB serial port
#define SERIAL_BAUDRATE B115200

#define SERIAL_BUFFL 25
#define ERROR_RESPONSE "-999999.99"

#define TRACE_DCONCycle 0    		//print measure values from modules to shared memory
#define TRACE_readersCMD 1   		//print commands from mailbox to modules

enum {
  DEC,
  HEX
  };


struct sdef {
	int channel;
	char cmd[6];
	int type;
      };

// Configuration for 3 modules. Change to actual configuration
// Freq Counter 7080 at adr 07 (2 channels), 
// Temp Pt100 7033 at adr 05 (3 channels)
// Voltage Ad-converter 7017 at adr 0a (8 channels)
// (Rs232/485 converter 7520)

#define NRCHANNELS 13 
#define CHANNEL_SIZE 9

	 
struct sdef DCONcycles[NRCHANNELS] = {
	0,"#070\r",HEX,			//Cnt 7080  07:0
	1,"#071\r",HEX,			//Cnt 7080    :1
	2,"#050\r",DEC,			//Pt100 7033 05:0
	3,"#051\r",DEC,			//Pt100 7033   :1
	4,"#052\r",DEC,			//Pt100 7033   :2
	5,"#0A0\r",DEC,			//AD 7017 0A:0
	6,"#0A1\r",DEC,			//AD 7017   :1
	7,"#0A2\r",DEC,			//AD 7017   :2
	8,"#0A3\r",DEC,			//AD 7017   :3
	9,"#0A4\r",DEC,			//AD 7017   :4
	10,"#0A5\r",DEC,		//AD 7017   :5
	11,"#0A6\r",DEC,		//AD 7017   :6
	12,"#0A7\r",DEC			//AD 7017   :7
};


rlThread       thread;
rlSerial       serials; 						//serial for ICP modules
rlSharedMemory shms(DCON_SHARED_MEMORY,DCON_SHARED_MEMORY_SIZE); 	//shared memory
rlMailbox      mbxs(DCON_MAILBOX); 				 	//message mailbox


static long cyclecnt;


int readChar(int timeout)
// Read a character with timeout
{ 
  int c;
  if (serials.select(timeout) <= 0) return -1; //error or Linux timeout
  c = serials.readChar();
  if ( c < 0 ) return -1; //error or windows timeout
  return c;
}



int DCONresponse(unsigned char * buf, int maxlength, int responsetime, int timeout)
// read a message from serial port. Wait for message response time, then read characters until timeout 
{
  int n,c;

     
   n=0;
#if RLLIB_SELECT_ERROR
   rlsleep(responsetime); 
#endif
   c = readChar(responsetime);  //Get initial response  
   if ( c >= 0 ) {
      buf[n++] = c;
      do
      {
         c = readChar(timeout); //Get message
         if ( c >= 0 ) buf[n++] = c;
      }
      while (c > 0); 
   }
   return n;  
}




// get commands from mailbox and send to modules
// used for setting outputs, commands that requires no direct respons,  etc

void *readers(void *arg) 
{
  int ret,buflen,n;
  unsigned char buf[SERIAL_BUFFL];

  mbxs.clear(); // clear old messages
  if (TRACE_readersCMD) printf(" \nStart mailbox thread\n");
  while((buflen = mbxs.read(buf,sizeof(buf))) > 0)
  {
    thread.lock();
    rlsleep(SERIAL_IDLETIME); 
    ret = serials.writeBlock( buf, buflen);
    buf[buflen-1]=0;
    if (TRACE_readersCMD) printf("DCON CMD:Wserial %i %s \n",buflen,buf);
    n = DCONresponse(buf,SERIAL_BUFFL,SERIAL_RESPONSETIME,SERIAL_TIMEOUT);
    if ( n<= 0) 
      printf("DCON CMD:No response %i %s \n",buflen,buf);
    else {
      buf[n-1]=0; //terminate string, delete CR
      //Check of response can be inserted here
      if (TRACE_readersCMD) printf("DCON CMD:Rserial %i %s \n",n,buf);
    }
    rlsleep(SERIAL_IDLETIME);
    thread.unlock();
  }
  return arg;
}


// send request and get measure values from ICP modules using DCON protocol, then save it in shared memory
// channel:   channel nr
// request:  command (which include delimiter,address,channel no) that will be send to the module to request data
// datatype: HEX or DEC return value from module

void DCONCycle(int channel,char  *request, int datatype ) 
{
  unsigned long hexvalue;
  unsigned char data[SERIAL_BUFFL];
  int n,ret;

  thread.lock();
  sprintf((char *)data,ERROR_RESPONSE);  //Init response to error
  ret = serials.writeBlock((unsigned char *)request,strlen(request)); //send request to ICP module
  if (ret <= 0)
    {
      printf("DCONCycle:writeBlock error %i %i\n",cyclecnt,channel);
    }
  else
  { 
    n=DCONresponse(data,SERIAL_BUFFL,SERIAL_RESPONSETIME,SERIAL_TIMEOUT);
    if (TRACE_DCONCycle) printf("Line ret %i \n",n);
    if (( n > 0) && (data[0] == '>') && (data[n-1] == '\r'))
    {
      data[0]=' '; //replace '>' 
      data[n-1]=0; //terminate string, delete CR
      if (datatype == DEC)
      {
	if (TRACE_DCONCycle) printf("DCONcycle:Response %i %i %i %s \n",cyclecnt,channel,n,data);
      }
      else if (datatype == HEX)
      {
	sscanf((char *)data,"%x",&hexvalue);
	if (TRACE_DCONCycle) printf("DCONcycle:Response %i %i %i %8d %s\n",cyclecnt,channel,n,hexvalue,data);
        sprintf((char *)data,"%9d",hexvalue);
      }
    }
    else
    {
      printf("DCONcycle:Error response %i %i %d %i \n",cyclecnt,channel,n,data[0]);
      sprintf((char *)data,ERROR_RESPONSE);
    }
  }
  shms.write(channel*CHANNEL_SIZE,data,CHANNEL_SIZE); //save the value in shared memory, each measure value occupy 9 character	
  thread.unlock();
  return;
}




int main(int ac, char **av)
{
  int ret;


  if(serials.openDevice(SERIAL_DEVICE,SERIAL_BAUDRATE,1,1,8,1,rlSerial::NONE) < 0) //serial ICP module start=1,stop=1,data=8,parity=none
  {
      printf("could not open serial device %s\n",SERIAL_DEVICE);
      return -1;
  }


  printf("Starting DCON\n");
  thread.create(readers,NULL); //create thread 

  while(1)
  {
    cyclecnt++;  //let it overflow!
    for (int nr=0; nr<NRCHANNELS; nr++ ){
      DCONCycle(DCONcycles[nr].channel,DCONcycles[nr].cmd,DCONcycles[nr].type);
      rlsleep(SERIAL_CYCLETIME_ADJ);  
    }
  }
  // we will never come here
  serials.closeDevice();
  return 0;
}
