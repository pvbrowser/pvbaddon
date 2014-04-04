//
// SiemensTCP daemon template                                 (C) R. Lehrig 2004
//
//
// Attention: this program must be run as super user
//

#include <stdio.h>
#include <stdlib.h>
#include "rlsiemenstcp.h"
#include "rlsharedmemory.h"
#include "rlmailbox.h"
#include "rlthread.h"
#include "rlcutil.h"

#define siemensdaemon_CYCLE_TIME 50

rlSiemensTCP   slave0("192.168.1.101",rlSiemensTCP::S7_200,0,-1,-1);
rlSharedMemory shm("/srv/automation/shm/siemens.shm",32);
rlMailbox      mbx("/srv/automation/mbx/siemens.mbx");
rlThread       thread;
rlSiemensTCP   *slave_array[256];

// read mailbox and write to siemensTCP
void *reader(void *arg)
{
  int buflen,slave,org,dbnr,start_adr,len,function;
  unsigned char buf[2048+8];

  mbx.clear(); // clear old messages
  while((buflen = mbx.read(buf,sizeof(buf))) > 0)
  {
    slave     = buf[0];
    org       = buf[1];
    dbnr      = buf[2]*256 + buf[3];
    start_adr = buf[4]*256 + buf[5];
    len       = buf[6]*256 + buf[7];
    function  = buf[8];
    if(slave >= 0 && slave < 256 && slave_array[slave] != NULL)
    {
      thread.lock();
      slave_array[slave]->write(org,dbnr,start_adr,len,&buf[9],function);
      thread.unlock();
    }
  }
  return arg;
}

// read cycle on SiemensTCP
int siemensTCPCycle(int slave, int offset, int org, int dbnr, int start_adr, int len)
{
  unsigned char data[4096];
  int ret;

  if(slave_array[slave] == NULL) return len;
  thread.lock();
  ret = slave_array[slave]->fetch(org,dbnr,start_adr,len,data);
  thread.unlock();
  if(ret > 0) shm.write(offset,data,ret);
  else        printf("E"); // Error
  return len;
}

int main()
{
  int offset,ret,i;
  for(i=0; i<256; i++) slave_array[i] = NULL;
  slave_array[0] = &slave0;

  //rlSetDebugPrintf(1); // set debugging on
  thread.create(reader,NULL);
  while(1)
  {
    rlsleep(siemensdaemon_CYCLE_TIME);
    offset = 0;
    // SiemensTCPCycle(int slave, int offset, int org, int dbnr, int start_adr, int len);
    ret = siemensTCPCycle(0,offset, rlSiemensTCP::ORG_M, 0, 0, 32);
    if(ret>0) offset += ret; else continue;
  }

  return 0;
}
