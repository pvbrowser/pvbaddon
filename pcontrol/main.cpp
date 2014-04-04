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
#include "pvapp.h"

COMMAND_LINE_SWITCHES switches;

void getSwitches(int ac, char **av)
{
  switches.pcontrol = 1;
  switches.eventlog = 1;
#ifdef unix
  switches.eventport = 6003;
#else
  switches.eventport = 5100;
#endif

  for(int i=1; i<ac; i++)
  {
    if(strcmp("-only_eventlog",av[i]) == 0)  switches.pcontrol = 0;
    if(strcmp("-only_pcontrol",av[i]) == 0)  switches.eventlog = 0;
    if(strncmp(av[i],"-eventport=",11) == 0) 
    {
      sscanf(av[i],"-eventport=%d",&switches.eventport);
      printf("waiting on port=%d for event log messages\n", switches.eventport);
    }
    if((strncmp(av[i],"-h",2) == 0) || (strncmp(av[i],"--h",3) == 0))
    {
      printf("usage: pcontrol <-port=num> <-sleep=milliseconds> <-cd=/working/dir> <-eventport=num> <-only_eventlog> <-only_pcontrol>\n");
      printf("-port=port number for ProcessViewBrowser\n");
      printf("-sleep=cycle time for ProcessViewBrowser\n");
      printf("-cd=/your/working/directory\n");
      printf("-eventport=port number for rlEvent, default=%d\n",switches.eventport);
      printf("-only_eventlog=only implement eventlog\n");
      printf("-only_pcontrol=only implement pcontrol\n");
      exit(0);
    }
  }
}

int cleanup(void *ptr)
{
  USER *user;

  user = (USER *) ptr;
  if(user != NULL) delete user;
  return 0;
}

int pvMain(PARAM *p)
{
int ret;

  p->user = (void *) new USER;
  pvSetCleanup(p,cleanup,p->user);
  pvSetCaption(p,"pcontrol");
  pvResize(p,0,1280,1024);
  ret = 1;
  if(switches.eventlog == 1 && switches.pcontrol == 0) ret = 4;
  while(1)
  {
    switch(ret)
    {
      case 5:
        ret = show_mask5(p);
        break;
      case 1:
        ret = show_mask1(p);
        break;
      case 2:
        ret = show_pcontrol(p);
        break;
      case 3:
        ret = show_edit(p);
        break;
      case 4:
        ret = show_event(p);
        break;
      default:
        return 0;
    }
  }
}

#ifdef USE_INETD
int main(int ac, char **av)
{
PARAM p;

  getSwitches(ac,av);
  pvInit(ac,av,&p);
  p.user = (void *) new USER;
  if(switches.pcontrol) create_center();
  if(switches.eventlog) create_eventlog();

  /* here you may interpret ac,av and set p->user to your data */
  pvMain(&p);
  return 0;
}
#else  // multi threaded server
static void handler(void *arg)
{
  printf("handler\n");
  if(arg == NULL) return;
}

int main(int ac, char **av)
{
PARAM p;
int   s;

  rlSetSigtermHandler(handler,NULL);

  getSwitches(ac,av);
  pvInit(ac,av,&p);
  if(switches.pcontrol) create_center();
  if(switches.eventlog) create_eventlog();
  /* here you may interpret ac,av and set p->user to your data */
  while(1)
  {
    s = pvAccept(&p);
    if(s != -1) pvCreateThread(&p,s);
    else        break;
  }
  return 0;
}
#endif
