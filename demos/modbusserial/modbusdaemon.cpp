//
// Modbus daemon template                                 (C) R. Lehrig 2003
//
//
// Attention: this program must be run as super user
//

#include <stdio.h>
#include <stdlib.h>
#include "rlmodbus.h"
#include "rlsharedmemory.h"
#include "rlmailbox.h"
#include "rlthread.h"
#include "rlcutil.h"
#include "modbusdaemon.h"

#define MODBUS_IDLETIME (4*1000)/96
#define SERIAL_DEVICE   "COM1"
rlModbus       modbus(256+1,rlModbus::MODBUS_RTU);
rlSerial       serial;
rlSharedMemory shm("/srv/automation/shm/modbusxy.shm",8);
rlMailbox      mbx("/srv/automation/mbx/modbusxy.mbx");
rlThread       thread;
rlThread       watchdog;
short          lifeCounter     = 0;
short          readErrorCount  = 0;
short          writeErrorCount = 0;

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
  serial.closeDevice();
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
  int ret,slave,function,buflen;
  unsigned char buf[256+1];

  mbx.clear(); // clear old messages
  while((buflen = mbx.read(buf,sizeof(buf))) > 0)
  {
    slave        = buf[0];
    function     = buf[1];
    thread.lock();
    rlsleep(MODBUS_IDLETIME);
    ret = modbus.write( slave, function, &buf[2], buflen-2);
    ret = modbus.response( &slave, &function, buf);
    rlsleep(MODBUS_IDLETIME);
    thread.unlock();
    if(ret < 0)
    {
      writeErrorCount++;
      if(writeErrorCount >= 256*128) writeErrorCount = 0;
      shm.write(modbusdaemon_WRITE_ERROR_COUNT_BASE,&writeErrorCount,2);
    }
    printf("mbx ret=%d slave=%d function=%d buf[2]=%d\n",ret,slave,function,buf[2]);
  }
  return arg;
}

// read cycle on modbus
int modbusCycle(int offset, int slave, int function, int start_adr, int num_register)
{
  unsigned char data[256+1];
  int ret;

  watchcnt1++;
  if(watchcnt1 > 10000) watchcnt1 = 0;
  rlsleep(MODBUS_IDLETIME);
  thread.lock();
  ret = modbus.request(slave, function, start_adr, num_register);
  if(ret >= 0) ret = modbus.response( &slave, &function, data);
  thread.unlock();
  if(ret > 0) shm.write(offset,data,ret);
  else
  {
    readErrorCount++;
    if(readErrorCount >= 256*128) readErrorCount = 0;
    shm.write(modbusdaemon_READ_ERROR_COUNT_BASE,&readErrorCount,2);
  }
  printf("cycle ret=%d slave=%d function=%d data[0]=%d\n",ret,slave,function,data[0]);
  return ret;
}

int main(int ac, char **av)
{
  int offset,ret,first;
  if(ac > 0) av0 = av[0];
  first = 1;
  while(serial.openDevice(SERIAL_DEVICE,B9600,1,1,8,1,rlSerial::NONE) < 0)
  {
    if(first==1) printf("could not open serial device %s\n",SERIAL_DEVICE);
    first = 0;
    rlsleep(1000);
  }
  printf("\n%s starting\n",av0);
  modbus.registerSerial(&serial);
  thread.create(reader,NULL);
  watchdog.create(watchdogthread,NULL);

  shm.write(modbusdaemon_LIFE_COUNTER_BASE,&lifeCounter,2);
  shm.write(modbusdaemon_READ_ERROR_COUNT_BASE,&readErrorCount,2);
  shm.write(modbusdaemon_WRITE_ERROR_COUNT_BASE,&writeErrorCount,2);
  while(1)
  {
    lifeCounter++;
    if(lifeCounter >= 256*128) lifeCounter = 0;
    shm.write(modbusdaemon_LIFE_COUNTER_BASE,&lifeCounter,2);
    offset = 0;
    //    modbusCycle(offset, slave, function, start_adr, num_register);
    ret = modbusCycle(offset,1,2,0,10);
    if(ret>0) offset += ret; else continue;
  }

  // we will never come here
  serial.closeDevice();
  return 0;
}
