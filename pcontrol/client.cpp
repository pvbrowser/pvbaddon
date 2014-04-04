/***************************************************************************
                          main.cpp  -  description
                             -------------------
    begin                : Son Nov 12 09:43:38 CET 2000
    copyright            : (C) 2000 by R. Lehrig
    email                : lehrig@t-online.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
#include "rlevent.h"
#include "rlthread.h"

int main()
{
#ifdef unix
  char *argv[] = {"","-eventhost=localhost","-eventport=6003"};
#else
  char *argv[] = {"","-eventhost=localhost","-eventport=5100"};
#endif
  int i = 0;

  rlEventInit(3,argv,"/TEST/");
  while(1)
  {
    rlEvent(rlInfo    ,"event %d",i++);
    rlEvent(rlWarning ,"event %d",i++);
    rlEvent(rlError   ,"event %d",i++);
    rlEvent(rlCritical,"event %d",i++);
    rlEvent(rlFatal   ,"event %d",i++);
    rlEvent(rlTest    ,"event %d",i++);
    rlsleep(1000);
    if(i > 100*6) break;
  }
  return 0;
}
