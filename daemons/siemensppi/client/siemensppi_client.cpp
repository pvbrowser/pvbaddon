/***************************************************************************
 *   client for Siemens PPI with pvbrowser                                 *
 *   using: http://libnodave.sourceforge.net/index.php                     *
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
#include "rlthread.h"
#include "rlinifile.h"
#include "rlspreadsheet.h"
#include "rldataacquisitionprovider.h"
#include "rlmailbox.h"
#include "rlcutil.h"

#ifdef unix
#define LINUX  // needed for libnodave
#else
#define BCCWIN // needed for libnodave
#endif
extern "C"
{
#include "setport.h"
#include "nodave.h"
};

typedef union
{
  unsigned char  b[4];
  unsigned short uns[2];
  short          s[2];
  unsigned int   uni;
  int            i;
  float          f;
}SWAP;

// global values
static char               var[80]                  = "";
static int                debug                    = 1;    // 0 or 1
static int                cycletime                = 1000; // milliseconds
static char               buf[1024];

// values for libnodave
extern int daveDebug;
static daveInterface      *di;
static _daveOSserialType   fds;
static daveConnection     *namelist_dc[32+1];
rlSpreadsheetRow          *namelist                 = NULL;
static int                *namelist_count           = NULL;
static int                *namelist_area            = NULL;
static int                *namelist_slave           = NULL;
static int                *namelist_dbnum           = NULL;
static int                *namelist_start           = NULL;

// values from rllib...
int                       num_cycles               = 0;
rlDataAcquisitionProvider *provider                 = NULL;
int                        max_name_length          = 31;
int                        shared_memory_size       = 65536;
rlThread                  *thread                   = NULL;
rlMailbox                 *mbx                      = NULL;

static void *mailboxReadThread(void *arg)
{
  char buf[1024],*itemname,*itemvalue,*cptr;
  unsigned char data[1024];
  int  ret,slave,area,dbnum,start,len,doit,val;

  if(debug) printf("mailboxReadThread: starting\n");
  mbx->clear(); // clear old messages
  while(mbx->read(buf,sizeof(buf)) > 0)
  {
    itemname = itemvalue = &buf[0];  // parse buf begin
    cptr = strchr(buf,')');
    if(cptr != NULL)
    {
      cptr = strchr(cptr,',');
      if(cptr != NULL)
      {
        *cptr = '\0';
        cptr++;
        itemvalue = cptr;
        cptr = strchr(itemvalue,'\n');
        if(cptr != NULL) *cptr = 0;
      }
    }                                // parse buf end
    if(debug) printf("mailboxReadThread: Write itemname=%s itemvalue=%s\n",itemname,itemvalue);
    doit = 1;
    if     (strncmp(buf,"sd(",3)      == 0){area = -1; doit = 0; } //area = daveSD;
    else if(strncmp(buf,"inputs(",7)  == 0) area = daveInputs;
    else if(strncmp(buf,"outputs(",8) == 0) area = daveOutputs;
    else if(strncmp(buf,"flags(",6)   == 0) area = daveFlags;
    else if(strncmp(buf,"db(",3)      == 0) area = daveDB;
    else if(strncmp(buf,"di(",3)      == 0) area = daveDI;
    else if(strncmp(buf,"local(",6)   == 0) area = daveLocal;
    else if(strncmp(buf,"v(",2)       == 0) area = daveV;
    else if(strncmp(buf,"counter(",8) == 0) area = daveCounter;
    else if(strncmp(buf,"timer(",6)   == 0) area = daveTimer;
    else                                   {area = -1; doit = 0; }

    cptr = strchr(buf,'(');
    if(doit && cptr != NULL)
    {
      sscanf(cptr,"(%d,%d,%d)", &slave, &dbnum, &start);
      len = 0;
      cptr = itemvalue;
      while(1) // read array of values: 0,1,2,3,4
      {
        sscanf(cptr,"%d", &val);
        data[len++] = (unsigned char) val;
        cptr = strchr(cptr,',');
        if(cptr == NULL) break;
        cptr++;
      }
      if(len > 0 && slave >0 && slave <= 32 && dbnum >= 0 && start >= 0)
      {
        thread->lock();
        //int daveWriteBytes(daveConnection * dc,int area, int DBnum, int start,int len, void * buffer);
        ret = daveWriteBytes(namelist_dc[slave],area,dbnum,start,len,data);
        thread->unlock();
        if(ret < 0)
        {
          int cnt = provider->writeErrorCount() + 1;
          if(cnt >= 256*256) cnt = 0;
          provider->setWriteErrorCount(cnt);
        }
        if(ret!=0) printf("daveWriteBytes ret=%d\n",ret);
      }
    }
  }
  return arg;
}

static int init(int ac, char **av)
{
  int i, adr, area;
  const char *text, *cptr;
  char name[1024], baudrate[80];

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

  // init tty variables for libnodave
  i = atoi(ini.text("GLOBAL","DAVE_DEBUG"));
  if(i) daveDebug = daveDebugAll;
  strcpy(name, ini.text("TTY","DEVICENAME"));
  strcpy(baudrate, ini.text("TTY","BAUDRATE"));
  if(debug) printf("setPort(%s,%s)\n",name,baudrate);
  fds.rfd=setPort(name,baudrate,'E');
  fds.wfd=fds.rfd;
  if(fds.rfd < 0)
  {
    printf("could not open %s\n", name);
    return -1;
  }
  printf("%s starting with debug=%d cycletime=%d devicename=%s\n",
         av[0],            debug,   cycletime,   name);
  strcpy(name,"IF1");
  di = daveNewInterface(fds,name,0,daveProtoPPI,daveSpeed187k);
  for(adr=1; adr<=32; adr++) namelist_dc[adr] = daveNewConnection(di,adr,0,0);

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
  namelist_area          = new int[num_cycles];
  namelist_slave         = new int[num_cycles];
  namelist_dbnum         = new int[num_cycles];
  namelist_start         = new int[num_cycles];

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
    if     (strncmp(var,"sd(",3)      == 0) area = -1; //area = daveSD;
    else if(strncmp(var,"inputs(",7)  == 0) area = daveInputs;
    else if(strncmp(var,"outputs(",8) == 0) area = daveOutputs;
    else if(strncmp(var,"flags(",6)   == 0) area = daveFlags;
    else if(strncmp(var,"db(",3)      == 0) area = daveDB;
    else if(strncmp(var,"di(",3)      == 0) area = daveDI;
    else if(strncmp(var,"local(",6)   == 0) area = daveLocal;
    else if(strncmp(var,"v(",2)       == 0) area = daveV;
    else if(strncmp(var,"counter(",8) == 0) area = daveCounter;
    else if(strncmp(var,"timer(",6)   == 0) area = daveTimer;
    else
    {
      printf("%s(slave,dbnum,start) not implemented !\n", var);
      printf("Possible names:\n");
      printf("sd(slave,dbnum,start)\n");
      printf("inputs(slave,dbnum,start)\n");
      printf("outputs(slave,dbnum,start)\n");
      printf("flags(slave,dbnum,start)\n");
      printf("db(slave,dbnum,start)\n");
      printf("di(slave,dbnum,start)\n");
      printf("local(slave,dbnum,start)\n");
      printf("v(slave,dbnum,start)\n");
      printf("counter(slave,dbnum,start)\n");
      printf("timer(slave,dbnum,start)\n");
      return -1;
    }
    namelist_area[i] = area;
    namelist->printf(i+1,"%s",var);
    cptr = strchr(var,'(');
    if(cptr == NULL) return -1;
    sscanf(cptr,"(%d,%d,%d)", &namelist_slave[i], &namelist_dbnum[i], &namelist_start[i]);
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

  if(debug)
  {
    for(i=0; i< num_cycles; i++)
    {
      printf("namelist(%d) count=%d area=%d slave=%d dbnum=%d start=%d\n", i,
                         namelist_count[i],
                         namelist_area[i],
                         namelist_slave[i],
                         namelist_dbnum[i],
                         namelist_start[i]);
    }
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

// read cycle on ppi
static int ppiCycle(daveConnection *dc, int area, int dbnum, int start, int len, unsigned char *data)
{
  int ret;

  if(len > 256) return -1;
  if(debug) printf("daveReadBytes area=%d dbnum=%d start=%d len=%d\n",
                                  area,   dbnum,   start,   len);
  thread->lock();
  ret = daveReadBytes(dc,area,dbnum,start,len,data);
  thread->unlock();
  if(ret < 0)
  {
    int cnt = provider->readErrorCount() + 1;
    if(cnt >= 256*256) cnt = 0;
    provider->setReadErrorCount(cnt);
  }
  if(ret != 0) printf("daveReadBytes ret=%d\n",ret);

  return ret;
}

static int readSiemens(int i)
{
  unsigned char data[1024+1];
  char          name[1024], name_cat[128], value[128];
  int           i1, ind, ret, slave;

  slave = namelist_slave[i];
  if(slave < 1 || slave > 32)
  {
    printf("slave=%d out of range\n", slave);
    return -1;
  }
  ret = ppiCycle(namelist_dc[slave],
                 namelist_area[i],
                 namelist_dbnum[i],
                 namelist_start[i],
                 namelist_count[i],
                 data);
  if(ret != 0) return ret;

  ind = 0;
  for(i1=0; i1<namelist_count[i]; i1++) // store all values in shared memory
  {
    sprintf(value, "%d", data[ind]);
    switch(namelist_area[i])
    {
      //case daveSD:
      //  strcpy(name,"sd");
      //  break;
      case daveInputs:
        strcpy(name,"inputs");
        break;
      case daveOutputs:
        strcpy(name,"outputs");
        break;
      case daveFlags:
        strcpy(name,"flags");
        break;
      case daveDB:
        strcpy(name,"db");
        break;
      case daveDI:
        strcpy(name,"di");      //not tested
        break;
      case daveLocal:
        strcpy(name,"local");   //not tested
        break;
      case daveV:
        strcpy(name,"v");       //don't know what it is
        break;
      case daveCounter:
        strcpy(name,"counter"); //not tested
        break;
      case daveTimer:
        strcpy(name,"timer");   //not tested
        break;
      default:
        strcpy(name,"unknown");
        printf("USER_ERROR: unknown area=%d\n", namelist_area[i]);
        break;
    }
    if(namelist_count[i] == 1)
    {
      sprintf(name_cat,"(%d,%d,%d)",
                       namelist_slave[i], namelist_dbnum[i], namelist_start[i]);      // print name
    }
    else
    {
      sprintf(name_cat,"(%d,%d,%d)[%d]",
                       namelist_slave[i], namelist_dbnum[i], namelist_start[i], ind); // print name
    }
    strcat(name, name_cat);
    if(debug) printf("provider->setStringVaule(\"%s\",\"%s\")\n", name, value);
    provider->setStringValue(name,value);
    ind += 1;
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
          // thread->lock();   // done in modbusCycle
          ret = readSiemens(i);
          // thread->unlock(); // done in modbusCycle
          if(ret < 0) { error_reading = 1; break; }
          cell = cell->getNextCell();
        }
        provider->setLifeCounter(lifeCounter++);
        if(lifeCounter >= 256*256) lifeCounter = 0;
        rlsleep(cycletime);
      }
    }
    closeSiemens();             // PLC has been disconnected
    rlsleep(5000);             // retry connecting every 5 seconds
  }
  return 0;
}

