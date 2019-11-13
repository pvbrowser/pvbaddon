/***************************************************************************
 *   client for SiemensTCP with pvbrowser                                  *
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
#include "rlsiemenstcp.h"
#include "rlthread.h"
#include "rlinifile.h"
#include "rlspreadsheet.h"
#include "rldataacquisitionprovider.h"
#include "rlmailbox.h"
#include "rlcutil.h"

typedef union
{
  unsigned char  b[4];
  unsigned short us[2];
  short          s[2];
  unsigned int   ui;
  int            i;
  float          f;
}SWAP;

// global values
static char               var[80]                  = "";
static int                debug                    = 1;    // 0 or 1
static int                cycletime                = 1000; // milliseconds
static int                haveto_swap              = 1;
static char               buf[1024];

// values for slaves
typedef rlSiemensTCP *siemensPTR; 
static int                num_slaves               = 0;
rlSiemensTCP            **slave_array;

// values from rllib...
#define DATA_BIT   1
#define DATA_BYTE  2
#define DATA_SHORT 3
#define DATA_INT   4
#define DATA_FLOAT 5
rlSpreadsheetRow          *namelist                 = NULL;    
int                       *namelist_count, 
                          *namelist_slave,
                          *namelist_org,
                          *namelist_dbnum,
                          *namelist_start_adr,
                          *namelist_datatype;
int                        num_cycles               = 0;
rlDataAcquisitionProvider *provider                 = NULL;
int                        max_name_length          = 31;
int                        shared_memory_size       = 65536;
rlThread                  *thread                   = NULL;
rlMailbox                 *mbx                      = NULL;

unsigned char              cb[22];

static void *mailboxReadThread(void *arg)
{
  char  buf[1024],data[4],*itemname,*itemvalue,*cptr,*start;
  int   slave,org,dbnum,start_adr,len,function,doit,ret;
  SWAP swap;

  if(debug) printf("mailboxReadThread: starting\n");
  mbx->clear(); // clear old messages
  while(mbx->read(buf,sizeof(buf)) > 0)
  {
    itemname = itemvalue = start = &buf[0];  // parse buf begin
    function = rlSiemensTCP::WriteByte;
    cptr = strrchr(buf,',');
    if(cptr != NULL)
    {
      *cptr = '\0';
      cptr++;
      itemvalue = cptr;
      cptr = strchr(itemvalue,'\n');
      if(cptr != NULL) *cptr = 0;
      start = strchr(buf,'(');
    }                                        // parse buf end
    if(debug) printf("mailboxReadThread: Write itemname=%s itemvalue=%s\n",itemname,itemvalue);
    doit = len = 0;
    swap.i = 0;
    if     (strncmp(buf,"bitORG_",7) == 0 && start != NULL)
    {
      sscanf(start,"(%d,%d,%d)",&slave,&dbnum,&start_adr);
      function = rlSiemensTCP::WriteBit;
      len = 1;
      sscanf(itemvalue,"%d",&swap.i);
      data[0] = swap.b[0];
      doit = 1;
    }  
    else if(strncmp(buf,"byteORG_",8) == 0 && start != NULL)
    {
      sscanf(start,"(%d,%d,%d)",&slave,&dbnum,&start_adr);
      function = rlSiemensTCP::WriteByte;
      len = 1;
      sscanf(itemvalue,"%d",&swap.i);
      data[0] = swap.b[0];
      doit = 1;
    }  
    else if(strncmp(buf,"floatORG_",9) == 0 && start != NULL)
    {
      sscanf(start,"(%d,%d,%d)",&slave,&dbnum,&start_adr);
      function = rlSiemensTCP::WriteByte;
      len = 4;
      sscanf(itemvalue,"%f",&swap.f);
      if(haveto_swap)
      {
        data[3] = swap.b[0];  
        data[2] = swap.b[1];  
        data[1] = swap.b[2];  
        data[0] = swap.b[3];
      }
      else
      {
        data[0] = swap.b[0];  
        data[1] = swap.b[1];  
        data[2] = swap.b[2];  
        data[3] = swap.b[3];
      }
      doit = 1;
    }  
    else if(strncmp(buf,"dwordORG_",9) == 0 && start != NULL)
    {
      sscanf(start,"(%d,%d,%d)",&slave,&dbnum,&start_adr);
      function = rlSiemensTCP::WriteByte;
      len = 4;
      sscanf(itemvalue,"%d",&swap.i);
      if(haveto_swap)
      {
        data[3] = swap.b[0];  
        data[2] = swap.b[1];  
        data[1] = swap.b[2];  
        data[0] = swap.b[3];  
      }
      else
      {
        data[0] = swap.b[0];  
        data[1] = swap.b[1];  
        data[2] = swap.b[2];  
        data[3] = swap.b[3];
      }
      doit = 1;
    }  
    else if(strncmp(buf,"shortORG_",9) == 0 && start != NULL)
    {
      sscanf(start,"(%d,%d,%d)",&slave,&dbnum,&start_adr);
      function = rlSiemensTCP::WriteByte;
      len = 2;
      sscanf(itemvalue,"%d",&swap.i);
      if(haveto_swap)
      {
        data[1] = swap.b[0];  
        data[0] = swap.b[1];  
      }  
      else
      {
        data[0] = swap.b[0];  
        data[1] = swap.b[1]; 
      }  
      doit = 1;
    }  
    else if(strncmp(buf,"udwordORG_",10) == 0 && start != NULL)
    {
      sscanf(start,"(%d,%d,%d)",&slave,&dbnum,&start_adr);
      function = rlSiemensTCP::WriteByte;
      len = 4;
      sscanf(itemvalue,"%d",&swap.i);
      if(haveto_swap)
      {
        data[3] = swap.b[0];  
        data[2] = swap.b[1];  
        data[1] = swap.b[2];  
        data[0] = swap.b[3];  
      }
      else
      {
        data[0] = swap.b[0];  
        data[1] = swap.b[1];  
        data[2] = swap.b[2];  
        data[3] = swap.b[3];
      }
      doit = 1;
    }  
    else if(strncmp(buf,"ushortORG_",10) == 0 && start != NULL)
    {
      sscanf(start,"(%d,%d,%d)",&slave,&dbnum,&start_adr);
      function = rlSiemensTCP::WriteByte;
      len = 2;
      sscanf(itemvalue,"%d",&swap.i);
      if(haveto_swap)
      {
        data[1] = swap.b[0];  
        data[0] = swap.b[1]; 
      }  
      else
      {
        data[0] = swap.b[0];  
        data[1] = swap.b[1]; 
      }  
      doit = 1;
    }  
    else
    {
      printf("USER_ERROR: unknown %s entered\n", buf);
      printf("Possible values:\n");
      printf("bit<ORG>(slave,dbnum,adr)\n");
      printf("byte<ORG>(slave,dbnum,adr)\n");
      printf("float<ORG>(slave,dbnum,adr)\n");
      printf("dword<ORG>(slave,dbnum,adr)\n");
      printf("short<ORG>(slave,dbnum,adr)\n");
      printf("udword<ORG>(slave,dbnum,adr)\n");
      printf("ushort<ORG>(slave,dbnum,adr)\n");
    }
    org = -1;
    slave -= 1;
    if(strstr(itemname,"ORG_DB")   != NULL) org = rlSiemensTCP::ORG_DB;
    if(strstr(itemname,"ORG_M")    != NULL) org = rlSiemensTCP::ORG_M;
    if(strstr(itemname,"ORG_E")    != NULL) org = rlSiemensTCP::ORG_E;
    if(strstr(itemname,"ORG_A")    != NULL) org = rlSiemensTCP::ORG_A;
    if(strstr(itemname,"ORG_PEPA") != NULL) org = rlSiemensTCP::ORG_PEPA;
    if(strstr(itemname,"ORG_Z")    != NULL) org = rlSiemensTCP::ORG_Z;
    if(strstr(itemname,"ORG_T")    != NULL) org = rlSiemensTCP::ORG_T;
    if(slave < 0 || slave >= num_slaves)
    {
      doit = 0;
      printf("USER_ERROR: slave=%d out of range\n", slave+1);
    }
    if(dbnum < 0)
    {
      doit = 0;
      printf("USER_ERROR: dbnum=%d out of range\n", dbnum);
    }
    if(start_adr < 0)
    {
      doit = 0;
      printf("USER_ERROR: adr=%d out of range\n", start_adr);
    }

    if(doit && org != -1)
    {
      thread->lock();
      if(debug) printf("siemens_write: slave=%d org=%d dbnum=%d start_adr=%d len=%d function=%d data[0]=%d\n",
                                       slave+1, org,   dbnum,   start_adr,   len,   function,   data[0]);
      ret = slave_array[slave]->write(org,dbnum,start_adr,len,(unsigned char *) data, function);
      thread->unlock();
      if(ret < 0)
      {
        int cnt = provider->writeErrorCount() + 1;
        if(cnt >= 256*256) cnt = 0;
        provider->setWriteErrorCount(cnt);
      }
      rlsleep(10); // sleep in order that reading can work in parrallel
    }  
  }
  return arg;
}

static int init(int ac, char **av)
{
  int i, plc_type, fetch_write, function, rack_slot;
  const char *text, *adr;
  const char *cptr;
  char *varcptr, *cptr2;
  if(ac != 2)
  {
    printf("usage: %s inifile\n", av[0]);
    return -1;
  }

  rlIniFile ini;
  if(ini.read(av[1]) != 0)
  {
    printf("could not open %s\n", av[1]);
    return -1;
  }

  // init global variables
  debug       = atoi(ini.text("GLOBAL","DEBUG"));
  cycletime   = atoi(ini.text("GLOBAL","CYCLETIME"));
  haveto_swap = atoi(ini.text("GLOBAL","HAVETO_SWAP"));

  printf("%s starting with debug=%d cycletime=%d haveto_swap=%d\n",
         av[0],            debug,   cycletime,   haveto_swap);

  if(debug)
  {
    rlSetDebugPrintf(1);
  }

  // init values for socket...
  num_slaves = atoi(ini.text("SOCKET","NUM_SLAVES"));  
  if(num_slaves <= 0)
  {
    printf("num_slaves <= 0\n");
    return -1;
  }
  slave_array = new siemensPTR[num_slaves];
  if(debug) printf("init slaves ... num_slaves=%d\n", num_slaves);
  for(i=0; i<num_slaves; i++)
  {
    sprintf(buf,"SLAVE%d",i+1);
    text = ini.text("SOCKET",buf);
    if(text != NULL)
    {
      strcpy(buf,text);
      adr = &buf[0];
      varcptr = strchr(buf,',');
      if(varcptr == NULL)
      {
        printf("no , found in %s\n",buf);
        return -1;
      }
      *varcptr = '\0'; varcptr++; cptr = varcptr;
      plc_type = rlSiemensTCP::ANY_SIEMENS_COMPATIBLE_PLC;
      if(strstr(cptr,"S7_200")  != NULL) plc_type = rlSiemensTCP::S7_200;
      if(strstr(cptr,"S7_300")  != NULL) plc_type = rlSiemensTCP::S7_300;
      if(strstr(cptr,"S7_400")  != NULL) plc_type = rlSiemensTCP::S7_400;
      if(strstr(cptr,"S5")      != NULL) plc_type = rlSiemensTCP::S5;
      if(strstr(cptr,"ANY")     != NULL) plc_type = rlSiemensTCP::ANY_SIEMENS_COMPATIBLE_PLC;
      if(strstr(cptr,"S7_1200") != NULL) plc_type = rlSiemensTCP::S7_1200;
      if(strstr(cptr,"LOGO")    != NULL) plc_type = rlSiemensTCP::LOGO;
      fetch_write = 1;
      function = rack_slot = -1;
      cptr = strchr(cptr,',');
      if(cptr != NULL) sscanf(cptr,",%d,%d,%d", &fetch_write, &function, &rack_slot);
      if(debug) printf("slave_array[%d] = new rlSiemensTCP(\"%s\",%d,%d,%d,%d)\n",
                                          i,adr,plc_type,fetch_write,function,rack_slot);
      slave_array[i] = new rlSiemensTCP(adr,plc_type,fetch_write,function,rack_slot);
      if(debug) printf("getDefaultConnectBlock()\nValues read for SLAVE%d from INI file:\n", i+1);
      slave_array[i]->getDefaultConnectBlock(cb);
      char sbuf[32],cbuf[16];
      int found_cb = 0;
      for(int icb=0; icb<22; icb++)
      {
        sprintf(sbuf,"SLAVE%d_CONNECT_BLOCK", i+1);
        sprintf(cbuf,"CB%d",icb);
        const char *cptr = ini.text(sbuf,cbuf); 
        if(isdigit(*cptr))
        {
          cb[icb] = atoi(cptr);
          found_cb = 1;
          if(debug) printf("CB%d=%2x hex\n", icb, cb[icb]);
        }
        else if(*cptr == '\'')
        {
          cb[icb] = cptr[1];
          found_cb = 1;
          if(debug) printf("CB%d=%2x hex %c ascii\n", icb, cb[icb], cb[icb]);
        }
      }
      if(found_cb)
      {
        if(debug) printf("setConnectBlock() for SLAVE%d\n", i+1);
        slave_array[i]->setConnectBlock(cb);
        for(int icb=0; icb<22; icb++)
        {
          if(debug) printf("CB[%d]=%2x hex\n",icb,(unsigned int) cb[icb]);
        }
        if(debug) printf("starting communication with ANY Siemens plc_type\n");
      }  
    }
    else
    {
      printf("%s not found\n", buf);
      return -1;
    }
  }

  // init values for cycles...
  num_cycles = atoi(ini.text("CYCLES","NUM_CYCLES"));
  if(num_cycles <= 0)
  {
    printf("num_cycles=%d <= 0\n", num_cycles);
   return -1;
  }
  if(debug) printf("init cycles ... num_cycles=%d\n", num_cycles);
  namelist = new rlSpreadsheetRow();

  namelist_count         = new int[num_cycles];
  namelist_slave         = new int[num_cycles];
  namelist_org           = new int[num_cycles];
  namelist_dbnum         = new int[num_cycles];
  namelist_start_adr     = new int[num_cycles];
  namelist_datatype      = new int[num_cycles];

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
    sscanf(cptr2,"%d,%d,%d", &namelist_slave[i], &namelist_dbnum[i], &namelist_start_adr[i]);
    namelist_slave[i] -= 1;
    if     (strncmp(cptr,"bitORG_",7)     == 0) namelist_datatype[i] = DATA_BIT;
    else if(strncmp(cptr,"byteORG_",8)    == 0) namelist_datatype[i] = DATA_BYTE;
    else if(strncmp(cptr,"floatORG_",9)   == 0) namelist_datatype[i] = DATA_FLOAT;
    else if(strncmp(cptr,"dwordORG_",9)   == 0) namelist_datatype[i] = DATA_INT;
    else if(strncmp(cptr,"shortORG_",9)   == 0) namelist_datatype[i] = DATA_SHORT;
    else if(strncmp(cptr,"udwordORG_",10) == 0) namelist_datatype[i] = DATA_INT;
    else if(strncmp(cptr,"ushortORG_",10) == 0) namelist_datatype[i] = DATA_SHORT;
    else
    {
      printf("USER_ERROR: unknown %s entered\n", text);
      printf("Possible values:\n");
      printf("bit<ORG>(slave,dbnum,adr)\n");
      printf("byte<ORG>(slave,dbnum,adr)\n");
      printf("float<ORG>(slave,dbnum,adr)\n");
      printf("dword<ORG>(slave,dbnum,adr)\n");
      printf("short<ORG>(slave,dbnum,adr)\n");
      printf("udword<ORG>(slave,dbnum,adr)\n");
      printf("ushort<ORG>(slave,dbnum,adr)\n");
      return -1;
    }
    if     (strstr(cptr,"ORG_DB")   != NULL) namelist_org[i] = rlSiemensTCP::ORG_DB;
    else if(strstr(cptr,"ORG_M")    != NULL) namelist_org[i] = rlSiemensTCP::ORG_M;
    else if(strstr(cptr,"ORG_E")    != NULL) namelist_org[i] = rlSiemensTCP::ORG_E;
    else if(strstr(cptr,"ORG_A")    != NULL) namelist_org[i] = rlSiemensTCP::ORG_A;
    else if(strstr(cptr,"ORG_PEPA") != NULL) namelist_org[i] = rlSiemensTCP::ORG_PEPA;
    else if(strstr(cptr,"ORG_Z")    != NULL) namelist_org[i] = rlSiemensTCP::ORG_Z;
    else if(strstr(cptr,"ORG_T")    != NULL) namelist_org[i] = rlSiemensTCP::ORG_T;
    else
    {
      printf("no correct ORG found in %s\n", text);
      return -1;
    }
    namelist->printf(i+1,"%s",var);
    if(debug)
    {
      printf("CYCLE%d added: count=%d var=%s org=%d dbnum=%d adr=%d\n",
              i+1,  namelist_count[i],var,   namelist_org[i], namelist_dbnum[i], namelist_start_adr[i]);
    }
  } 

  // init values for rllib...
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

  if(debug) printf("init success\n");
  return 0;
}

static int openSiemens()
{
  if(debug) printf("openSiemens\n");
  return 0;
}

static int closeSiemens()
{
  if(debug) printf("Siemens closed\n");
  return 0;
}

static int siemensCycle(int slave, int org, int dbnum, int start_adr, int len, unsigned char *data)
{
  int ret;

  if(debug) printf("siemensCycle: var=%s : slave=%d org=%d dbnum=%d start_adr=%d len=%d\n",
                                  var,     slave+1, org,   dbnum,   start_adr,   len);
  if(slave < 0 || slave >= num_slaves)
  {
    printf("USER_ERROR: slave=%d out of range\n", slave+1);
    return -1;
  }
  if(dbnum < 0)
  {
    printf("USER_ERROR: dbnum=%d out of range\n", dbnum);
    return -1;
  }
  if(start_adr < 0)
  {
    printf("USER_ERROR: adr=%d out of range\n", start_adr);
    return -1;
  }
  if(slave_array[slave]->isConnected() == 0)
  {
    printf("WARNING: slave=%d is not connected\n", slave+1);
  }
  thread->lock();
  ret = slave_array[slave]->fetch(org,dbnum,start_adr,len,data);
  thread->unlock();
  if(ret < 0)
  {
    int cnt = provider->readErrorCount() + 1;
    if(cnt >= 256*256) cnt = 0;
    provider->setReadErrorCount(cnt);
  }
  if(ret <= 0) { printf("siemensCycle: ERROR ret=%d\n",ret); }
  return ret;
}

static int readSiemens(int i)
{
  unsigned char data[2048];
  char          name[1024]; 
  int           bytes_per_item, i1, ind, ret;
  SWAP          swap;

  switch(namelist_datatype[i])
  {
    case DATA_SHORT:
      bytes_per_item = 2;
      break;
    case DATA_INT:
    case DATA_FLOAT:
      bytes_per_item = 4;
      break;
    default:
      bytes_per_item = 1;
      break;
  }
  ret = siemensCycle(namelist_slave[i],
                     namelist_org[i],
                     namelist_dbnum[i],
                     namelist_start_adr[i],
                     namelist_count[i] * bytes_per_item,
                     data);
  if(ret <  0) return ret; // USER_ERROR                  
  if(ret == 0)
  {
    printf("PLC slave=%d is temporarily not connected\n", namelist_slave[i]+1);
    return 0;
  }
  ind = 0;
  for(i1=0; i1<namelist_count[i]; i1++) // store all values in shared memory
  {
    swap.i = 0;
    //sprintf(name,"%s(%d,%d,%d)", var, namelist_slave[i], namelist_dbnum[i], namelist_start_adr[i] + i1); // print name
    // The user works with slaves in the range of: 1 <= slave <= N 
    // The content of namelist_slave[] is from 0 to N-1
    sprintf(name,"%s(%d,%d,%d)", var, namelist_slave[i]+1, namelist_dbnum[i], namelist_start_adr[i] + i1); // print name
    switch(namelist_datatype[i])
    {
      case DATA_BIT:
        swap.b[0] = data[ind];
        if(debug) printf("write bit %s=%d to shared memory\n", name, swap.i);
        provider->setIntValue(name,swap.i);
        ind += 1;
        break;
      case DATA_BYTE:
        swap.b[0] = data[ind];
        if(debug) printf("write byte %s=%d to shared memory\n", name, swap.i);
        provider->setIntValue(name,swap.i);
        ind += 1;
        break;
      case DATA_SHORT:
        if(haveto_swap)
        {
          swap.b[1] = data[ind];
          swap.b[0] = data[ind+1];
        }
        else
        {
          swap.b[0] = data[ind];
          swap.b[1] = data[ind+1];
        }
        if(debug) printf("write short %s=%d to shared memory\n", name, swap.i);
        provider->setIntValue(name,swap.i);
        ind += 2;
        break;
      case DATA_INT:
        if(haveto_swap)
        {
          swap.b[3] = data[ind];
          swap.b[2] = data[ind+1];
          swap.b[1] = data[ind+2];
          swap.b[0] = data[ind+3];
        }
        else
        {
          swap.b[0] = data[ind];
          swap.b[1] = data[ind+1];
          swap.b[2] = data[ind+2];
          swap.b[3] = data[ind+3];
        }
        if(debug) printf("write int %s=%d to shared memory\n", name, swap.i);
        provider->setIntValue(name,swap.i);
        ind += 4;
        break;
      case DATA_FLOAT:
        if(haveto_swap)
        {
          swap.b[3] = data[ind];
          swap.b[2] = data[ind+1];
          swap.b[1] = data[ind+2];
          swap.b[0] = data[ind+3];
        }
        else
        {
          swap.b[0] = data[ind];
          swap.b[1] = data[ind+1];
          swap.b[2] = data[ind+2];
          swap.b[3] = data[ind+3];
        }
        if(debug) printf("write float %s=%f to shared memory\n", name, swap.f);
        provider->setIntValue(name,swap.f);
        ind += 4;
        break;
      default:
        break;
    }
  }  
  return 0;
}

int main(int argc,char *argv[])
{
  rlSpreadsheetCell *cell;
  int i, ret, error_reading, lifeCounter;

  if(init(argc, argv) != 0) return -1;
  thread->create(mailboxReadThread,NULL);
  while(1)                     // forever run the daemon
  {
    lifeCounter = 0;
    if(openSiemens() == 0)
    {
      error_reading = 0;
      while(error_reading == 0)
      {
        cell = namelist->getFirstCell();
        for(i=0; i<num_cycles; i++)
        {
          if(cell == NULL) break;
          strcpy(var,cell->text());
          // thread->lock();   // done in siemensCycle
          ret = readSiemens(i);
          // thread->unlock(); // done in siemensCycle
          if(ret < 0) { error_reading = 1; break; }
          cell = cell->getNextCell();
        }
        provider->setLifeCounter(lifeCounter++);
        if(lifeCounter >= 256*256) lifeCounter = 0;
        rlsleep(cycletime);
      }
    }
    closeSiemens();            // PLC has been disconnected
    rlsleep(5000);             // retry connecting every 5 seconds
  }
  return 0;
}

