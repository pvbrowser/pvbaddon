/*********************************************************
/                                                        /
/  main.cpp - fake model for shared memory               /
/  17.04.2007 by Sebastian Lehrig (sebastian@lehrig.de)  /
/                                                        /
*********************************************************/

#include <string.h>
#include <stdio.h>

#ifdef unix
#include "xchange.h"
#include <unistd.h>

rlSharedMemory shm(XCHANGE_SHARED_MEMORY, XCHANGE_SHARED_MEMORY_SIZE);
XCHANGE xchange;

int step()
{
  return 0;
}

int main()
{
  int ret;

  printf("status = %d\n", shm.status);
  memset(&xchange, 0, sizeof(XCHANGE));
  
  while(1)
  {
    step();
    ret = shm.write(0, &xchange, sizeof(XCHANGE));
    if (ret < 0) printf("Error writing Shared Memory ret=%d\n", ret);
    sleep(5);
  }

  return 0;
}
#else
int main()
{
  printf("not for windows\n");	
  return 0;	
}	
#endif
