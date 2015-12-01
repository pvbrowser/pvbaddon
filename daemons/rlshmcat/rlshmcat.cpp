/***************************************************************************
                          rlshmcat.cpp  -  description
                             -------------------
    begin                : Tue Sep 23 2015
    copyright            : (C) 2015 by R. Lehrig
    email                : lehrig@t-online.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU LESSER GENERAL PUBLIC LICENSE as        *
 *   published by the Free Software Foundation                             *
 *                                                                         *
 ***************************************************************************/
#include <rldataacquisition.h>
#include <rlopcxmlda.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int rlshmcat(const char *name, int size)
{
  rlSharedMemory *shm = new rlSharedMemory(name,size);
  printf("# shm(\"%s\",%d) status=%d size=%ld (size + sizeof(mutex))\n", name, size, shm->status, shm->size());
  if(shm->status == rlSharedMemory::OK)
  {
    rlDataAcquisition::SHM_HEADER *shmheader = (rlDataAcquisition::SHM_HEADER *)  shm->getUserAdr();
    if(strcmp(shmheader->ident,"daq") == 0)
    {
      printf("# ident=%s\n",             shmheader->ident);
      printf("# maxItemNameLength=%d\n", shmheader->maxItemNameLength);
      printf("# maxNameLength=%d\n",     shmheader->maxNameLength);
      printf("# numItems=%d\n",          shmheader->numItems);
      printf("# readErrorCount=%d\n",    shmheader->readErrorCount);
      printf("# writeErrorCount=%d\n",   shmheader->writeErrorCount);
      printf("# lifeCounter=%d\n",       shmheader->lifeCounter);
      long value_offset = shmheader->maxItemNameLength + 1;
      long delta_index = value_offset + shmheader->maxNameLength + 1;
      long nmax = shmheader->numItems;
      const char *cptr = (const char *) shmheader + sizeof(rlDataAcquisition::SHM_HEADER);
      for(long i=0; i<nmax; i++)
      {
        printf("%s\t%s\n", cptr ,cptr + value_offset);
        cptr += delta_index;
      }
    }
    else if(strcmp(shmheader->ident,"opc") == 0)
    {
      printf("# ident=%s\n",             shmheader->ident);
      printf("# maxItemNameLength=%d\n", shmheader->maxItemNameLength);
      printf("# maxNameLength=%d\n",     shmheader->maxNameLength);
      printf("# numItems=%d\n",          shmheader->numItems);
      printf("# readErrorCount=%d\n",    shmheader->readErrorCount);
      printf("# writeErrorCount=%d\n",   shmheader->writeErrorCount);
      printf("# lifeCounter=%d\n",       shmheader->lifeCounter);
      long value_offset = shmheader->maxItemNameLength + 1;
      long delta_index = value_offset + shmheader->maxNameLength + 1;
      long nmax = shmheader->numItems;
      const char *cptr = (const char *) shmheader + sizeof(rlOpcXmlDa::SHM_HEADER);
      for(long i=0; i<nmax; i++)
      {
        printf("%s\t%s\n", cptr ,cptr + value_offset);
        cptr += delta_index;
      }
    }
    else
    {
      printf("# NOT DAQ TYPE hexdump:");
      long size = (long) shm->size() - sizeof(pthread_mutex_t);
      long i;
      unsigned char *cptr = (unsigned char *) shm->getUserAdr();
      for(i=0; i<size; i++)
      {
        if(i%32 == 0) printf("\n%05ld: ", i);
        printf("%02x ", *cptr++);
      }
      printf("\n");
    }
  }
  else
  {
    printf("ERROR: status not OK\n");
  }
  delete shm;
  return 0;
}

int main(int ac, char **av)
{
  const char *shmname = NULL;
  int shmsize = 65536;
  int ret = -1;

  for(int i=1; i<ac; i++)
  {
    const char *arg = av[i];
    if(*arg != '-')
    {
      shmname = arg;
    }  
    else if(strncmp(arg,"-size=",6) == 0)
    {
      sscanf(arg,"-size=%d", &shmsize);
    }
  }

  if(shmname != NULL)
  {
    ret = rlshmcat(shmname,shmsize);
  }
  else
  {
    printf("cat content of shared memory to stdout\n");
    printf("usage: rlshmcat filename.shm <-size=value>\n");
  }
  return ret;
}
