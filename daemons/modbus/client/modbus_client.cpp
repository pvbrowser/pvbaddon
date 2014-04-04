/***************************************************************************
 *   client for Modbus with pvbrowser                                      *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "rlmodbus.h"
#include "rlthread.h"
#include "rlinifile.h"
#include "rlspreadsheet.h"
#include "rldataacquisitionprovider.h"
#include "rlmailbox.h"
#include "rlsocket.h"
#include "rlserial.h"

// global values
static char               var[80]                  = "";
static int                debug                    = 1;    // 0 or 1
static int                cycletime                = 1000; // milliseconds
static int                use_socket               = 1;
static char               buf[1024];
static int                poll_slave_counter[256];
static int                n_poll_slave             = 1;    // poll always

// values for socket
static char               ip[80]                   = "192.168.1.115";
static int                port                     = 0;

// values for tty/
static char               devicename[1024]         = "/dev/ttyS0";
static int                baudrate                 = B9600;
static int                rtscts                   = 1;
static int                stopbits                 = 1;
static int                parity                   = 0;
static int                protocol                 = rlModbus::MODBUS_RTU;

// values from rllib...
rlSpreadsheetRow          *namelist                 = NULL;    
int                       *namelist_count, *namelist_slave, *namelist_function, *namelist_start_adr, *namelist_datasize;
int                        num_cycles               = 0;
rlDataAcquisitionProvider *provider                 = NULL;
int                        max_name_length          = 31;
int                        shared_memory_size       = 65536;
rlThread                  *thread                   = NULL;
rlMailbox                 *mbx                      = NULL;
rlModbus                  *modbus                   = NULL;
rlSocket                  *mysocket                 = NULL;
rlSerial                  *tty                      = NULL;

static int modbus_idletime = (4*1000)/96;

static void *mailboxReadThread(void *arg)
{
  char buf[1024],data[4],*itemname,*itemvalue,*cptr;
  int  ret,val,slave,function,adr,buflen,doit;

  if(debug) printf("mailboxReadThread: starting\n");
  mbx->clear(); // clear old messages
  while(mbx->read(buf,sizeof(buf)) > 0)
  {
    itemname = itemvalue = &buf[0];  // parse buf begin
    cptr = strrchr(buf,',');
    if(cptr != NULL)
    {
      *cptr = '\0';
      cptr++;
      itemvalue = cptr;
      cptr = strchr(itemvalue,'\n');
      if(cptr != NULL) *cptr = 0;
    }                                // parse buf end
    if(debug) printf("mailboxReadThread: Write itemname=%s itemvalue=%s\n",itemname,itemvalue);
    doit = 0;
    if(strncmp(buf,"coil(",5) == 0)
    {
      sscanf(itemname,"coil(%d,%d)",&slave,&adr);
      function     = rlModbus::ForceSingleCoil;
      data[0] = adr/256; data[1] = adr & 0x0ff;
      sscanf(itemvalue,"%d",&val);
      data[2] = 0; data[3] = 0;
      if(val != 0) data[2] = 0x0ff;
      buflen = 4;
      doit = 1;
    }  
    else if(strncmp(buf,"register(",8) == 0)
    {
      sscanf(itemname,"register(%d,%d)",&slave,&adr);
      function     = rlModbus::PresetSingleRegister;
      data[0] = adr/256; data[1] = adr & 0x0ff;
      sscanf(itemvalue,"%d",&val);
      data[2] = val/256; data[3] = val & 0x0ff;
      buflen = 4;
      doit = 1;
    }
    else
    {
      printf("USER_ERROR: unknown %s entered\n", buf);
      printf("Possible values:\n");
      printf("coil(slave,adr)\n");
      printf("register(slave,adr)\n");
    }

    if(doit)
    {
      thread->lock();
      if(use_socket != 1) rlsleep(modbus_idletime); // on tty we have to sleep
      if(debug) printf("modbus_write: slave=%d function=%d data[0]=%d\n",
                                      slave,   function,   data[0]);
      ret = modbus->write( slave, function, (const unsigned char *) data, buflen);
      ret = modbus->response( &slave, &function, (unsigned char *) buf);
      if(use_socket != 1) rlsleep(modbus_idletime); // on tty we have to sleep
      thread->unlock();
      if(ret < 0)
      {
        int cnt = provider->writeErrorCount() + 1;
        if(cnt >= 256*256) cnt = 0;
        provider->setWriteErrorCount(cnt);
      }
      rlsleep(10); // sleep in order that reading can work in parallel even if we are sending a lot of data
    }  
  }
  return arg;
}

static int init(int ac, char **av)
{
  int i;
  const char *text, *cptr;
  char *cptr2;
  if(ac != 2)
  {
    printf("usage: %s inifile\n", av[0]);
    return -1;
  }

  for(i=0; i<256; i++) poll_slave_counter[i] = 0;

  rlIniFile ini;
  if(ini.read(av[1]) != 0)
  {
    printf("could not open %s\n", av[1]);
    return -1;
  }

  // init global variables
  use_socket  = atoi(ini.text("GLOBAL","USE_SOCKET"));
  debug       = atoi(ini.text("GLOBAL","DEBUG"));
  cycletime   = atoi(ini.text("GLOBAL","CYCLETIME"));
  cptr = ini.text("GLOBAL","N_POLL_SLAVE");
  if(isdigit(*cptr))
  {
    n_poll_slave = atoi(cptr);
  }

  // init socket variables
  strcpy(ip,         ini.text("SOCKET","IP"));
  port        = atoi(ini.text("SOCKET","PORT"));

  // init tty variables
  strcpy(devicename, ini.text("TTY","DEVICENAME"));
  text        =      ini.text("TTY","BAUDRATE");
  baudrate    = B9600; modbus_idletime = (4*1000)/96;
  if(strcmp(text,"300" )   == 0) { baudrate = B300;    modbus_idletime = (4*1000)/3;    }    
  if(strcmp(text,"600" )   == 0) { baudrate = B600;    modbus_idletime = (4*1000)/6;    }
  if(strcmp(text,"1200")   == 0) { baudrate = B1200;   modbus_idletime = (4*1000)/12;   }
  if(strcmp(text,"1800")   == 0) { baudrate = B1800;   modbus_idletime = (4*1000)/18;   }
  if(strcmp(text,"2400")   == 0) { baudrate = B2400;   modbus_idletime = (4*1000)/24;   }
  if(strcmp(text,"4800")   == 0) { baudrate = B4800;   modbus_idletime = (4*1000)/48;   }
  if(strcmp(text,"9600")   == 0) { baudrate = B9600;   modbus_idletime = (4*1000)/96;   }
  if(strcmp(text,"19200")  == 0) { baudrate = B19200;  modbus_idletime = (4*1000)/192;  }
  if(strcmp(text,"38400")  == 0) { baudrate = B38400;  modbus_idletime = (4*1000)/384;  }
  if(strcmp(text,"57600")  == 0) { baudrate = B57600;  modbus_idletime = (4*1000)/576;  }
  if(strcmp(text,"115200") == 0) { baudrate = B115200; modbus_idletime = (4*1000)/1152; }
  rtscts      = atoi(ini.text("TTY","RTSCTS"));
  text        =      ini.text("TTY","PARITY");
  if     (strcmp(text,"EVEN") == 0)  parity = rlSerial::EVEN;
  else if(strcmp(text,"ODD")  == 0)  parity = rlSerial::ODD;
  else                               parity = rlSerial::NONE;
  text        =  ini.text("TTY","STOPBITS");
  if(*text == '1') stopbits = 1;
  if(*text == '2') stopbits = 2;
  text        =      ini.text("TTY","PROTOCOL");
  if     (strcmp(text,"ASCII") == 0) protocol = rlModbus::MODBUS_ASCII;
  else                               protocol = rlModbus::MODBUS_RTU;

  printf("%s starting with debug=%d cycletime=%d use_socket=%d n_poll_slave=%d\n",
         av[0],            debug,   cycletime,   use_socket, n_poll_slave);

  // init values for rllib...
  num_cycles = atoi(ini.text("CYCLES","NUM_CYCLES"));
  if(num_cycles <= 0)
  {
    printf("num_cycles=%d <= 0\n", num_cycles);
    return -1;
  }
  if(debug) printf("num_cycles=%d\n", num_cycles);
  namelist = new rlSpreadsheetRow();

  namelist_count         = new int[num_cycles];
  namelist_slave         = new int[num_cycles];
  namelist_function      = new int[num_cycles];
  namelist_start_adr     = new int[num_cycles];
  namelist_datasize      = new int[num_cycles];

  for(i=0; i<num_cycles; i++)
  {
    sprintf(buf,"CYCLE%d",i+1);
    text = ini.text("CYCLES",buf);
    cptr = strchr(text,',');
    if(cptr == NULL)
    {
      printf("no , given on CYCLE %s\n", text);
      return -1;
    }
    cptr++;
    sscanf(text,"%d", &namelist_count[i]);
    if(debug) printf("CYCLE%d=%s count=%d name=%s\n", i+1, text, namelist_count[i], cptr);
    if(strlen(cptr) >= sizeof(var)-1)
    {
      printf("%s too long. exit\n", cptr);
      return -1;
    }
    strcpy(var,cptr);
    cptr2 = strchr(var,'(');
    if(cptr2 == NULL)
    {
      printf("no ( given on CYCLE %s\n", text);
      return -1;
    }
    *cptr2 = '\0';
    cptr2++;
    sscanf(cptr2,"%d,%d", &namelist_slave[i], &namelist_start_adr[i]);
    if     (strcmp(var,"coilStatus"       ) == 0)
    {
      namelist_function[i] = rlModbus::ReadCoilStatus;
      namelist_datasize[i] = 1;  // bit
    }
    else if(strcmp(var,"inputStatus"      ) == 0)
    {
      namelist_function[i] = rlModbus::ReadInputStatus;
      namelist_datasize[i] = 1;  // bit
    }
    else if(strcmp(var,"holdingRegisters" ) == 0)
    {
      namelist_function[i] = rlModbus::ReadHoldingRegisters;
      namelist_datasize[i] = 16; // bit 
    }
    else if(strcmp(var,"inputRegisters"   ) == 0)
    {
      namelist_function[i] = rlModbus::ReadInputRegisters;
      namelist_datasize[i] = 16; // bit 
    }
    else
    {
      printf("%s(slave,start_adr) not implemented !\n", var);
      printf("Possible names:\n");
      printf("coilStatus(slave,start_adr)\n");
      printf("inputStatus(slave,start_adr)\n");
      printf("holdingRegisters(slave,start_adr)\n");
      printf("inputRegisters(slave,start_adr)\n");
      return -1;
    }
    namelist->printf(i+1,"%s",var);
  } 

  max_name_length = atoi(ini.text("RLLIB","MAX_NAME_LENGTH"));
  if(max_name_length < 4)
  {
    printf("max_name_length=%d < 4\n", max_name_length);
    return -1;
  }
  if(debug) printf("max_name_length=%d\n", max_name_length);

  shared_memory_size = atoi(ini.text("RLLIB","SHARED_MEMORY_SIZE"));
  if(shared_memory_size < 64)
  {
    printf("shared_memory_size=%d < 64\n", shared_memory_size);
    return -1;
  }
  if(debug) printf("shared_memory_size=%d\n", shared_memory_size);

  provider = new rlDataAcquisitionProvider(max_name_length,
                                           ini.text("RLLIB","SHARED_MEMORY"),
                                           shared_memory_size 
                                          );
  if(provider->shmStatus() != 0)
  {
    printf("shared_memory_status ERROR\n");
    return -1;
  }
  provider->setAllowAddValues(1, max_name_length);
  provider->setWriteErrorCount(0);
  provider->setReadErrorCount(0);
  provider->setLifeCounter(0);

  thread = new rlThread();

  mbx = new rlMailbox(ini.text("RLLIB","MAILBOX"));
  if(mbx->status != rlMailbox::OK)
  {
    printf("mailbox_status ERROR\n");
    return -1;
  }

  modbus = new rlModbus(1024,protocol);
  if(use_socket)
  {
    mysocket = new rlSocket(ip,port,1);
    modbus->registerSocket(mysocket);
    mysocket->connect();
    if(mysocket->isConnected()) printf("success connecting to %s:%d\n", ip, port);
    else                        printf("WARNING: could not connect to %s:%d\n", ip, port);
  }
  else
  {
    tty = new rlSerial();
    if(tty->openDevice(devicename,baudrate,1,rtscts,8,stopbits,parity) < 0)
    {
      printf("ERROR: could not open device=%s\n", devicename);
      printf("check if you have the necessary rights to open %s\n", devicename);
      return -1;
    }
    modbus->registerSerial(tty);
  }

  return 0;
}

static int modbusCycle(int slave, int function, int start_adr, int num_register, unsigned char *data)
{
  int ret;

  if(slave < 0 || slave >= 256) return -1;
  if(poll_slave_counter[slave] > 0)
  {
    if(debug) printf("modbusCycle not polling slave%d: poll_slave_counter[%d]=%d\n", slave, slave, poll_slave_counter[slave]);
    poll_slave_counter[slave] -= 1;
    if(poll_slave_counter[slave] != 0) 
    {
      int cnt = provider->readErrorCount() + 1;
      if(cnt >= 256*256) cnt = 0;
      provider->setReadErrorCount(cnt);
      return -1;
    }  
  }

  if(debug) printf("modbusRequest: var=%s : slave=%d function=%d start_adr=%d num_register=%d\n", 
                                   var,     slave,   function,   start_adr,   num_register);
  if(use_socket != 1) rlsleep(modbus_idletime); // on tty we have to sleep
  thread->lock();
  ret = modbus->request(slave, function, start_adr, num_register);
  if(ret >= 0) ret = modbus->response( &slave, &function, data);
  thread->unlock();
  if(ret < 0)
  {
    int cnt = provider->readErrorCount() + 1;
    if(cnt >= 256*256) cnt = 0;
    provider->setReadErrorCount(cnt);
    poll_slave_counter[slave] = n_poll_slave;
  }
  if(debug) printf("modbusResponse: ret=%d slave=%d function=%d data=%02x %02x %02x %02x\n",
                                    ret,   slave,   function,   data[0], data[1], data[2], data[3]);
  return ret;
}

static int readModbus(int i)
{
  unsigned char data[512];
  char          name[1024]; 
  int           i1, ind, ret;
  unsigned int  val;

  ret = modbusCycle(namelist_slave[i], namelist_function[i], namelist_start_adr[i], namelist_count[i], data);
  if(ret < 0)
  {
    if(debug) printf("modbusCycle returned error\n");
    for(i1=0; i1<namelist_count[i]; ) // store all errors in shared memory
    {
      sprintf(name,"%s(%d,%d)", var, namelist_slave[i], namelist_start_adr[i] + i1); // print name
      if     (namelist_datasize[i] == 1)  // bit
      {
        if(debug) printf("write 8bits %s=ERR Error to shared memory\n", name);
        provider->setStringValue(name,"ERR");
        ind += 1;
        i1  += 8;
      }
      else if(namelist_datasize[i] == 16) // bit
      {
        if(debug) printf("write short %s=ERR Error to shared memory\n", name);
        provider->setStringValue(name,"ERR");
        ind += 2;
        i1  += 1;
      }
    }  
    return ret;
  }
  ind = 0;
  for(i1=0; i1<namelist_count[i]; ) // store all values in shared memory
  {
    sprintf(name,"%s(%d,%d)", var, namelist_slave[i], namelist_start_adr[i] + i1); // print name
    if     (namelist_datasize[i] == 1)  // bit
    {
      val = data[ind];
      if(debug) printf("write 8bits %s=0x%x to shared memory\n", name, val);
      provider->setIntValue(name,val);
      ind += 1;
      i1  += 8;
    }
    else if(namelist_datasize[i] == 16) // bit
    {
      val = data[ind]*256 + data[ind+1];
      if(debug) printf("write short %s=%d to shared memory\n", name, val);
      provider->setIntValue(name,val);
      ind += 2;
      i1  += 1;
    }
    else
    {
      printf("ERROR: unknown datasize\n");
      return -1;
    }
  }  
  return 0;
}

int main(int argc,char *argv[])
{
  rlSpreadsheetCell *cell;
  int i, lifeCounter;

  if(init(argc, argv) != 0)
  {
    return -1;
  }  
  thread->create(mailboxReadThread,NULL);
  lifeCounter = 0;
  while(1)                 // forever run the daemon
  {
    cell = namelist->getFirstCell();
    for(i=0; i<num_cycles; i++)
    {
      if(cell == NULL) break;
      strcpy(var,cell->text());
      // thread->lock();   // done in modbusCycle
      readModbus(i);
      // thread->unlock(); // done in modbusCycle
      cell = cell->getNextCell();
    }
    provider->setLifeCounter(lifeCounter++);
    if(lifeCounter >= 256*256) lifeCounter = 0;
    rlsleep(cycletime);
  }
  return 0;
}

