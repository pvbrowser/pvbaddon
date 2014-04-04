/***************************************************************************
 *   client for Ethernet_IP with pvbrowser                                 *
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

#include <signal.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "TuxEip.h"
#include "rlthread.h"
#include "rlinifile.h"
#include "rlspreadsheet.h"
#include "rldataacquisitionprovider.h"
#include "rlmailbox.h"
#include "rlsocket.h"

// global values
static char            IP[80]                   = "192.168.1.115";
static char            var[80]                  = "N7:0";
static int             count                    = 8;
static Eip_Session    *session                  = NULL;
static Eip_Connection *connection               = NULL;
static int             debug                    = 1;    // 0 or 1
static int             cycletime                = 1000; // milliseconds
static int             tns                      = 1234;
static int             use_connect_over_cnet    = 1;
static char            buf[1024];

// values for ConnectPLCOver...
static int             plc_type                 = SLC500;
static int             connection_id            = 0x12345678;
static int             connection_serial_number = 0x6789;
static int             target_to_originator_id  = 0x12345678;
static int             request_packet_interval  = 5000;
static int             channel                  = Channel_B;
static unsigned char   path[80]                 = {1,0};
static int             pathlen                  = 2;

// values from rllib...
rlSpreadsheetRow         *namelist                   = NULL;    
int                      *namelist_count             = NULL;
int                       num_cycles                 = 0;
rlDataAcquisitionProvider *provider                   = NULL;
int                       max_name_length            = 31;
int                       shared_memory_size         = 65536;
rlThread                 *thread                     = NULL;
rlMailbox                *mbx                        = NULL;

static int writeTuxEip(const char *itemname, const char *itemvalue)
{
  float fval; 
  int   ret, ival;
  const char  *cptr;
  char  name[1024];

  if(debug) printf("writeTuxEip: itemname=%s itemvalue=%s\n", itemname, itemvalue);
  strcpy(name,itemname);

  cptr = strchr(itemvalue,'.');
  if(cptr == NULL) // no dot found
  {
    sscanf(itemvalue,"%d",&ival);
    ret = WritePLCData(session,connection,NULL,NULL,0,(Plc_Type) plc_type,tns,
                       name,PLC_INTEGER,&ival,1);
  }
  else
  {
    sscanf(itemvalue,"%f",&fval);
    ret = WritePLCData(session,connection,NULL,NULL,0,(Plc_Type) plc_type,tns,
                       name,PLC_FLOATING,&fval,1);
  }
  if(ret == EX_Error)
  {
    int cnt = provider->writeErrorCount() + 1;
    if(cnt >= 256*256) cnt = 0;
    provider->setWriteErrorCount(cnt);
    printf("WritePLCData Error\n");
    return -1;
  }
  else
  {
    if(debug) printf("WritePLCData Success\n");
  }
  return 0;
}

static void *mailboxReadThread(void *arg)
{
  char buf[1024],*itemname,*itemvalue,*cptr;
  int ret;

  mbx->clear();
  while(1)
  {
    if(debug) printf("mailboxReadThread: read mailbox\n");
    ret = mbx->read(buf, sizeof(buf)-1);
    if(ret < 0) break;
    itemname = itemvalue = &buf[0];  // parse buf begin
    cptr = strchr(buf,',');
    if(cptr != NULL)
    {
      *cptr = '\0';
      cptr++;
      itemvalue = cptr;
      cptr = strchr(itemvalue,'\n');
      if(cptr != NULL) *cptr = 0;
    }                                // parse buf end
    if(debug) printf("mailboxReadThread: Write itemname=%s itemvalue=%s\n",itemname,itemvalue);

    thread->lock();
    writeTuxEip(itemname,itemvalue);
    thread->unlock();
  }

  printf("thread terminating\n");
  return arg;
}

static int getPath(const char *text)
{
  int val;
  int i = 0;
  const char *cptr = text;
  printf("path=%s\n", text);
  while(1)
  {
    sscanf(cptr,"%d", &val);
    path[i++] = (unsigned char) val;
    pathlen = i;
    cptr = strchr(cptr,',');
    if(cptr == NULL) break;
    cptr++;
  }
  return 0;
}

static int init(int ac, char **av)
{
  int i;
  const char *text, *cptr;
  if(ac != 2)
  {
    printf("usage: %s inifile\n", av[0]);
    return -1;
  }

  rlwsa(); // startup sockets on windows
  rlIniFile ini;
  if(ini.read(av[1]) != 0)
  {
    printf("could not open %s\n", av[1]);
    return -1;
  }

  // init global variables
  use_connect_over_cnet = atoi(ini.text("GLOBAL","USE_CONNECT_OVER_CNET"));
  tns                   = atoi(ini.text("GLOBAL","TNS"));
  debug                 = atoi(ini.text("GLOBAL","DEBUG"));
  cycletime             = atoi(ini.text("GLOBAL","CYCLETIME"));
  strcpy(IP,                   ini.text("GLOBAL","IP"));
  printf("%s starting with IP=%s debug=%d cycletime=%d use_connect_over_cnet=%d tns=%d\n",
         av[0], IP, debug, cycletime, use_connect_over_cnet, tns);

  // init values for ConnectPLCOver...
  if(use_connect_over_cnet == 1)
  {
    text =  ini.text("ConnectPLCOverCNET","PLC_TYPE");
    if(strstr(text,"SLC500") != 0) plc_type = SLC500;
    if(strstr(text,"PLC5")   != 0) plc_type = PLC5;
    if(strstr(text,"LGX")    != 0) plc_type = LGX;
    text =  ini.text("ConnectPLCOverCNET","CONNECTION_ID");
    sscanf(text,"%x", &connection_id);
    text =  ini.text("ConnectPLCOverCNET","CONNECTION_SERIAL_NUMBER");
    sscanf(text,"%x", &connection_serial_number);
    text =  ini.text("ConnectPLCOverCNET","REQUEST_PACKET_INTERVAL");
    sscanf(text,"%d", &request_packet_interval);
    getPath(ini.text("ConnectPLCOverCNET","PATH"));
  }
  else
  {
    text =  ini.text("ConnectPLCOverDHP","PLC_TYPE");
    if(strstr(text,"SLC500") != 0) plc_type = SLC500;
    if(strstr(text,"PLC5")   != 0) plc_type = PLC5;
    if(strstr(text,"LGX")    != 0) plc_type = LGX;
    text =  ini.text("ConnectPLCOverDHP","TARGET_TO_ORIGINATOR_ID");
    sscanf(text,"%x", &target_to_originator_id);
    text =  ini.text("ConnectPLCOverDHP","CONNECTION_SERIAL_NUMBER");
    sscanf(text,"%x", &connection_serial_number);
    text =  ini.text("ConnectPLCOverDHP","CHANNEL");
    if(strstr(text,"Channel_A") != 0) channel = Channel_A;
    if(strstr(text,"Channel_B") != 0) channel = Channel_B;
    getPath(ini.text("ConnectPLCOverDHP","PATH"));
  }

  // init values for rllib...
  num_cycles = atoi(ini.text("CYCLES","NUM_CYCLES"));
  if(num_cycles <= 0)
  {
    printf("num_cycles=%d <= 0\n", num_cycles);
    return -1;
  }
  if(debug) printf("num_cycles=%d\n", num_cycles);
  namelist = new rlSpreadsheetRow();
  namelist_count = new int[num_cycles];
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
    namelist->printf(i+1,"%s",cptr);
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

  thread = new rlThread();

  mbx = new rlMailbox(ini.text("RLLIB","MAILBOX"));
  if(mbx->status != rlMailbox::OK)
  {
    printf("mailbox_status ERROR\n");
    return -1;
  }

  return 0;
}

static int openTuxEip()
{
  int res;

  if(debug) printf("entering OpenSession IP=\"%s\"\n", IP);
  session=OpenSession(IP);
  if(session==NULL)
  {
    printf("Error : OpenSession %s (%d:%d)\n",cip_err_msg,cip_errno,cip_ext_errno);
    return -1;
  }
  if(debug) printf("OpenSession Ok\n");
  if(debug) printf("entering RegisterSession \n");
  res=RegisterSession(session);
  if(res!=EX_Error)
  {
    if(debug) printf("RegisterSession Ok\n");
    if(use_connect_over_cnet == 1)
    {
      if(debug) printf("entering ConnectPLCOverCNET\n");
      connection = ConnectPLCOverCNET(
        session,                  // session whe have open
        (Plc_Type) plc_type,      // plc type
        connection_id,            // Target To Originator connection ID
        connection_serial_number, // Connection Serial Number
        request_packet_interval,  // Request Packet Interval
        (BYTE*) path,             // Path to the ControlLogix
        pathlen                   // path size
        );
    }
    else
    {
      if(debug) printf("entering ConnectPLCOverDHP\n");
      connection = ConnectPLCOverDHP(
        session,                  // session whe have open
        (Plc_Type) plc_type,      // plc type
        target_to_originator_id,  // Target To Originator connection ID
        connection_serial_number, // Connection Serial Number
        request_packet_interval,  // Request Packet Interval
        (DHP_Channel) channel,    // Channel of the 1756 DHRIO card
        (BYTE*) path,             // Path to the ControlLogix
        pathlen                   // path size
        );
    }
    if(connection != NULL)
    {
      if(debug) printf("connection Success\n");
      return 0;
    }
    printf("Error : ConnectPLCOverCNET %s (%d:%d)\n",cip_err_msg,cip_errno,cip_ext_errno);
  }
  printf("Error : RegisterSession %s (%d:%d)\n",cip_err_msg,cip_errno,cip_ext_errno);
  return -1;
}

static int closeTuxEip()
{
  int res;
  if(connection != NULL)
  {
    if(debug) printf("entering Forward_Close\n");
    res=Forward_Close(connection);
    if(res!=EX_Error) { if(debug) printf("Forward_Close %s\n",cip_err_msg); }
    else           printf("Error : Forward_Close %s (%d:%d)\n",cip_err_msg,cip_errno,cip_ext_errno);
    connection = NULL;
  }
  if(session != NULL) 
  {
    UnRegisterSession(session); 
    if(debug) printf("UnRegister : %s\n",cip_err_msg);
    if(debug) printf("entering CloseSession\n");
    CloseSession(session);
    session = NULL;
  }
  if(debug) printf("TuxEip closed\n");
  return 0;
}

static int readTuxEip()
{
  int   ret, i, first; //,val_int,val_bool;
  float val_float;
  char  *cptr, myvar[1024];
  //cip_debuglevel=LogDebug; // You can uncomment this line to see the data exchange between TuxEip and your Logic controller

  if(debug) printf("readTuxEip: var=%s count=%d\n", var, count);
  strcpy(myvar,var);
  cptr = strrchr(myvar,':');
  if(cptr != NULL) 
  {
    *cptr = '\0';
    cptr++;
    sscanf(cptr,"%d",&first);
  }
  else
  {
    first = -1;
  }

  PLC_Read *data=ReadPLCData(session,connection,NULL,NULL,0,(Plc_Type) plc_type,tns,var,count);
  if(data!=NULL)
  {
    if(data->Varcount>0)
    {
      if(debug) printf("ReadPLCData Ok :\n");
      if(debug) printf("\telements :%d\n\tDatatype : %d\n\ttotalsize : %d\n\tElement size : %d\nmask=%d\n",data->Varcount,data->type,data->totalsize,data->elementsize,data->mask);
      for(i=0;i<data->Varcount;i++)
      {
        //val_bool=PCCC_GetValueAsBoolean(data,i);
        //val_int=PCCC_GetValueAsInteger(data,i);
        val_float=PCCC_GetValueAsFloat(data,i);
        if(first == -1)
        {
          sprintf(buf,"%s:%d", var, i);
        }
        else
        {
          sprintf(buf,"%s:%d", myvar, first+i);
        }
        if(debug) printf("write to shared_memory %s=%f\n", buf, val_float);
        ret = provider->setFloatValue(buf, val_float);
        if(ret != 0) printf("ERROR writing shared memory\n");
      }
    }
    else
    {
      int cnt = provider->readErrorCount() + 1;
      if(cnt >= 256*256) cnt = 0;
      provider->setReadErrorCount(cnt);
      printf("Error ReadPLCData : %s\n",cip_err_msg);
    }
    free(data); // You have to free the data return by ReadLgxData
  }
  else
  {
    printf("Error : ReadPLCData %s (%d:%d)\n",cip_err_msg,cip_errno,cip_ext_errno);
    return -1;
  }
  return 0;
}

int main(int argc,char *argv[])
{
  rlSpreadsheetCell *cell;
  int i, ret, error_reading, lifeCounter;

  //CipSetDebug(1); // show messages send over TCP/IP
  if(init(argc, argv) != 0) return -1;
  thread->create(mailboxReadThread,NULL);
  while(1)                     // forever run the daemon
  {
    lifeCounter = 0;
    if(openTuxEip() == 0)
    {
      error_reading = 0;
      while(error_reading == 0)
      {
        cell = namelist->getFirstCell();
        for(i=0; i<num_cycles; i++)
        {
          if(cell == NULL) break;
          strcpy(var,cell->text());
          count = namelist_count[i];
          thread->lock();
          ret = readTuxEip();
          thread->unlock();
          if(ret < 0) { error_reading = 1; break; }
          cell = cell->getNextCell();
        }
        provider->setLifeCounter(lifeCounter++);
        if(lifeCounter >= 256*256) lifeCounter = 0;
        rlsleep(cycletime);
      }
    }
    closeTuxEip();             // PLC has been disconnected
    rlsleep(5000);             // retry connecting every 5 seconds
  }
  return 0;
}
