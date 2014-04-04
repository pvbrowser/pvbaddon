//
// PPI daemon template                            (C) pvbrowser 2004-2009
// using libnodave
//
#include <stdio.h>
#include <stdlib.h>
#include "rlsharedmemory.h"
#include "rlmailbox.h"
#include "rlthread.h"
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

//##############################################
// Adjust the following begin                  #
//##############################################
// remove this if you want ISO_ON_TCP
//#define USE_ISO_ON_TCP
#define IDLETIME      50
#define SERIAL_DEVICE "/dev/ttyUSB0"
#define BAUDRATE      "9600"
#define PLC_TCP_ADR   "192.168.1.101"
rlSharedMemory shm("/srv/automation/shm/ppi.shm",128);
rlMailbox      mbx("/srv/automation/mbx/ppi.mbx");
//##############################################
// Adjust the following end                    #
//##############################################
rlThread       thread;
rlThread       watchdog;

static daveConnection   *dc[32+1];
static daveInterface    *di;
static _daveOSserialType fds;

#ifdef USE_ISO_ON_TCP
#ifdef _WIN32
#include "openSocketw.c"
#else
#include "openSocket.c"
#endif
#endif

// watchdog
static const char *av0 = "";
static int watchcnt1 = 0;
void *watchdogthread(void *arg)
{
  int cnt1 = -1;

  while(1)
  {
    rlsleep(5000);
    if(cnt1 == watchcnt1) break;
    cnt1 = watchcnt1;
  }
  rlsleep(100);
#ifdef unix
  rlexec(av0);
#endif
  exit(0); // pcontrol may start me again if rlexec fails
  return arg;
}

// read mailbox and write to modbus
void *reader(void *arg)
{
  int ret,slave,area,dbnum,start,len,buflen;
  unsigned char buf[1024+1];

  mbx.clear(); // clear old messages
  while((buflen = mbx.read(buf,sizeof(buf))) > 0)
  {
    slave = buf[0];
    area  = buf[1];
    dbnum = buf[2]*256 + buf[3];
    start = buf[4]*256 + buf[5];
    len   = buf[6]*256 + buf[7];
    if(len > 0 && slave >=0 && slave < 32)
    {
      thread.lock();
      //int daveWriteBytes(daveConnection * dc,int area, int DBnum, int start,int len, void * buffer);
      ret = daveWriteBytes(dc[slave],area,dbnum,start,len,&buf[8]);
      thread.unlock();
      if(ret!=0) printf("daveWriteBytes ret=%d\n",ret);
    }
  }
  return arg;
}

// read cycle on ppi
int ppiCycle(int offset, daveConnection *dc, int area, int dbnum, int start, int len)
{
  unsigned char data[1024+1];
  int ret;

  if(len > 256) return -1;
  watchcnt1++;
  if(watchcnt1 > 10000) watchcnt1 = 0;
  thread.lock();
  ret = daveReadBytes(dc,area,dbnum,start,len,data);
  thread.unlock();
  if(ret == 0) shm.write(offset,data,len);
  if(ret != 0) printf("daveReadBytes ret=%d\n",ret);
  return len;
}

int main(int ac, char **av)
{
  int offset,ret;
  if(ac > 0) av0 = av[0];
#ifdef USE_ISO_ON_TCP
  printf("we use: iso_on_tcp adr=%s\n", PLC_TCP_ADR);
  fds.rfd=openSocket(102, PLC_TCP_ADR);
#else
  int adr;
  printf("we use: serial line %s baudrate=%s\n", SERIAL_DEVICE, BAUDRATE);
  fds.rfd=setPort(SERIAL_DEVICE,BAUDRATE,'E');
#endif
  fds.wfd=fds.rfd;
  if(fds.rfd>0)
  {
    printf("ppidaemon starting\n");
#ifdef USE_ISO_ON_TCP
    // iso_on_tcp
    di = daveNewInterface(fds,"IF1",0,daveProtoISOTCP,daveSpeed500k);
    //daveSetTimeout(di,-1);
    if(daveInitAdapter(di) != 0) printf("Adapter-Error!\n");
    dc[0] = daveNewConnection(di,0,0,3);
    daveConnectPLC(dc[0]);
#else
    // serial line
    di = daveNewInterface(fds,"IF1",0,daveProtoPPI,daveSpeed187k);
    for(adr=1; adr<32; adr++) dc[adr] = daveNewConnection(di,adr,0,0);
#endif
    thread.create(reader,NULL);
    watchdog.create(watchdogthread,NULL);
    while(1)
    {
      rlsleep(IDLETIME);
      offset = 0;
      //###################################################
      //    Add your cycles below                         #
      //###################################################
      //    ppiCycle(offset, dc, area, dbnum, start, len);
      ret = ppiCycle(offset, dc[0], daveDB, 1, 0, 64);
      if(ret>0) offset += ret; else continue;
      ret = ppiCycle(offset, dc[0], daveDB, 1, 64, 64);
      if(ret>0) offset += ret; else continue;
    }
  }
  printf("\nerror opening connection to Siemens PLC\n");  return 0;
}
