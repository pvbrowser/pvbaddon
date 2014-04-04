/*********************************************************
/                                                        /
/  xchange.h - data struct for shared memory             /
/  17.04.2007 by Sebastian Lehrig (sebastian@lehrig.de)  /
/                                                        /
*********************************************************/

#ifndef XCHANGE_H
#define XCHANGE_H

#include "rlsharedmemory.h"

#define MAX_XCHANGE_OBJECTS        16
#define XCHANGE_SHARED_MEMORY      "/srv/automation/shm/xchange.shm"
#define XCHANGE_SHARED_MEMORY_SIZE sizeof(XCHANGE)

typedef struct
{
  int   type;
  char  name[32];
  int   ival[16];
  float fval[16];
}
XCHANGE_OBJECT;

typedef struct
{
  int numObjects;
  XCHANGE_OBJECT o[MAX_XCHANGE_OBJECTS];
}
XCHANGE;

#endif
