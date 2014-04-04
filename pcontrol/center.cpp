/***************************************************************************
                            center.cpp  -  description
                             -------------------
    begin                : Thu Dec 12 09:43:38 CET 2002
    copyright            : (C) 2002 by R. Lehrig
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

rlSpreadsheetTable spreadsheat;
rlFifo             toCenter;
rlThread           center;
rlInterpreter      interpreter;
rlPcontrol        *processlist = NULL;
rlTime             now;
rlTime             timediff;
static int         processes_have_been_modified = 0;

static void set_header()
{
  spreadsheat.printf(T_state,          1,"State");
  spreadsheat.printf(T_pid,            1,"PID");
  spreadsheat.printf(T_name,           1,"Name");
  spreadsheat.printf(T_credit,         1,"Credit");
  spreadsheat.printf(T_interval,       1,"Interval");
  spreadsheat.printf(T_priority,       1,"Priority");
  spreadsheat.printf(T_startup_command,1,"StartupCommand");
  spreadsheat.printf(T_input,          1,"Input");
  spreadsheat.printf(T_output,         1,"Output");
  spreadsheat.printf(T_error,          1,"Error");
  spreadsheat.printf(T_time,           1,"TimeStartStop");
  spreadsheat.printf(T_initial_credit, 1,"InitialCredit");
}

static void start_if_missing(int row)
{
  char name[MAX_EVENT_LENGTH];
  char state[MAX_EVENT_LENGTH];
  rlPcontrol *item;
  int credit;

  rlstrncpy(state,spreadsheat.text(T_state,row),sizeof(state)-1);
  if(strcmp(state,STATE_INACTIVE) == 0) return;
  rlstrncpy(name,spreadsheat.text(T_name,row),sizeof(name)-1);
  if(name[0] <= ' ') return;
  item = processlist;
  while(item != NULL)
  {
    if(strcmp(name,item->processName()) == 0)
    {
      if(item->isAlive()) return;   // nothing to do
      credit = 0;
      sscanf(spreadsheat.text(T_credit,row),"%d",&credit);
      if(credit >  0 || credit == -1)
      {
        item->setPriority(atoi(spreadsheat.text(T_priority,row)));
        item->start(); // restart
        spreadsheat.printf(T_state,row,STATE_ACTIVE);
      }
      if(credit == 0) spreadsheat.printf(T_state,row,STATE_MISSING);
      if(credit >  0) credit--;
      if(credit == 0 && strcmp(STATE_MISSING,spreadsheat.text(T_state,row)) == 0)
      {
        int interval = 0;
        timediff = now - *item->processTime();
        sscanf(spreadsheat.text(T_interval,row),"%d",&interval);
        if(timediff.hour >= interval)
        {
          spreadsheat.printf(T_credit,row,"%s",spreadsheat.text(T_initial_credit,row));
        }
      }
      spreadsheat.printf(T_credit,row,"%d",credit);
      spreadsheat.printf(T_time,row,item->processTime()->getTimeString());
      processes_have_been_modified = 1;
      return;
    }
    item = item->getNext();
  }
  // not found in processlist -> append to processlist and start
  if(processlist == NULL) { processlist = new rlPcontrol(); item = processlist; }
  else                    item = processlist->addNew();
  item->setStartupCommand(spreadsheat.text(T_startup_command,row), name);
  item->setPriority      (atoi(spreadsheat.text(T_priority,row)));
#ifdef __VMS
  item->setInput         (spreadsheat.text(T_input,row));
  item->setOutput        (spreadsheat.text(T_output,row));
  item->setError         (spreadsheat.text(T_error,row));
#endif
  credit = 0;
  sscanf(spreadsheat.text(T_credit,row),"%d",&credit);
  if(credit >  0) credit--;
  spreadsheat.printf(T_credit,row,"%d",credit);
  item->start();
  spreadsheat.printf(T_state,row,STATE_ACTIVE);
  spreadsheat.printf(T_time,row,item->processTime()->getTimeString());
  processes_have_been_modified = 1;
}

static void watchdog()
{
  now.getLocalTime();
  center.lock();
  for(int row=FIRST_ROW; spreadsheat.exists(row,1); row++)
  {
    start_if_missing(row);
  }
  center.unlock();
}

static void do_sigterm()
{
  long pid;
  rlPcontrol *item;

  //printf("%s",interpreter.line);
  sscanf(interpreter.line,"sigterm(%ld)",&pid);
  interpreter.line[0] = '\0';
  center.lock();
  item = processlist;
  while(item != NULL)
  {
    if(item->pid() == pid)
    {
      item->sigterm();
      item->processTime()->getLocalTime(); // stop time
      break;
    }
    item = item->getNext();
  }
  center.unlock();
}

static void do_sigkill()
{
  long pid;
  rlPcontrol *item;

  //printf("%s",interpreter.line);
  sscanf(interpreter.line,"sigkill(%ld)",&pid);
  interpreter.line[0] = '\0';
  center.lock();
  item = processlist;
  while(item != NULL)
  {
    if(item->pid() == pid)
    {
      item->sigkill();
      item->processTime()->getLocalTime(); // stop time
      break;
    }
    item = item->getNext();
  }
  center.unlock();
}

static void construct_processlist()
{
  long pid;
  rlPcontrol *item;
  char name[100];

  for(int irow=FIRST_ROW; spreadsheat.exists(irow,1); irow++)
  {
    pid = 0;
#ifdef __VMS
    sscanf(spreadsheat.text(T_pid,irow),"%x",&pid);
#else
    sscanf(spreadsheat.text(T_pid,irow),"%ld",&pid);
#endif
    rlstrncpy(name, spreadsheat.text(T_name,irow),sizeof(name)-1);
    if(name[0] > 0)
    {
      if(processlist == NULL) { processlist = new rlPcontrol(); item = processlist; }
      else                    item = processlist->addNew();
      item->setStartupCommand(spreadsheat.text(T_startup_command,irow), name);
      if(pid > 0) item->setPID(pid);
      item->processTime()->setTimeFromString(spreadsheat.text(T_time,irow));
      item->setPriority      (atoi(spreadsheat.text(T_priority,irow)));
#ifdef __VMS
      item->setInput         (spreadsheat.text(T_input,irow));
      item->setOutput        (spreadsheat.text(T_output,irow));
      item->setError         (spreadsheat.text(T_error,irow));
#endif
    }
  }
}

static void do_reload(int write_flag)
{
  char name[100];

  //printf("%s",interpreter.line);
  interpreter.line[0] = '\0';
  center.lock();
  if(write_flag)
  {
    spreadsheat.write(SPREADSHEAT_FILE);
  }
  spreadsheat.read(SPREADSHEAT_FILE);
  set_header();
  for(int irow=FIRST_ROW; spreadsheat.exists(irow,1); irow++)
  {

    rlstrncpy(name,spreadsheat.text(T_name,irow),sizeof(name)-1);
    if(name[0] > 0)
    {
      spreadsheat.printf(T_credit,irow,"%s",spreadsheat.text(T_initial_credit,irow));
    }
  }
  construct_processlist();
  center.unlock();
}

static void do_remove()
{
  char candidate_name[100],name[100];
  long pid;

  interpreter.copyStringParam(candidate_name,0);
  center.lock();
  for(int irow=FIRST_ROW; spreadsheat.exists(irow,1); irow++)
  {
    rlstrncpy(name,spreadsheat.text(T_name,irow), sizeof(name)-1);
    if(strcmp(name,candidate_name) == 0)
    {
#ifdef __VMS
      sscanf(spreadsheat.text(T_pid,irow),"%x",&pid);
#else
      sscanf(spreadsheat.text(T_pid,irow),"%ld",&pid);
#endif
      spreadsheat.printf(T_state,          irow,"");
      spreadsheat.printf(T_pid,            irow,"");
      spreadsheat.printf(T_name,           irow,"");
      spreadsheat.printf(T_credit,         irow,"");
      spreadsheat.printf(T_interval,       irow,"");
      spreadsheat.printf(T_priority,       irow,"");
      spreadsheat.printf(T_startup_command,irow,"");
      spreadsheat.printf(T_input,          irow,"");
      spreadsheat.printf(T_output,         irow,"");
      spreadsheat.printf(T_error,          irow,"");
      spreadsheat.printf(T_initial_credit, irow,"");
      spreadsheat.printf(T_time,           irow,"");
      break;
    }
  }
  center.unlock();
  do_reload(1);
}

static void do_save()
{
  rlPcontrol *item;
  char name[100];

  //printf("%s",interpreter.line);
  interpreter.line[0] = '\0';
  center.lock();
  for(int irow=FIRST_ROW; spreadsheat.exists(irow,1); irow++)
  {
    rlstrncpy(name,spreadsheat.text(T_name,irow),sizeof(name)-1);
    if(name[0] > 0)
    {
      item = processlist;
      while(item != NULL)
      {
        if(strcmp(name,item->processName()) == 0)
        {
#ifdef __VMS
          spreadsheat.printf(T_pid,irow,"%x",item->pid());
#else
          spreadsheat.printf(T_pid,irow,"%ld",item->pid());
#endif
          spreadsheat.printf(T_time,irow,item->processTime()->getTimeString());
        }
        item = item->getNext();
      }
    }
  }
  spreadsheat.write(SPREADSHEAT_FILE);
  center.unlock();
  processes_have_been_modified = 0;
}

static void *centerMain(void *arg)
{
  int cnt;

  processlist = NULL; // processlist = empty
  cnt = 99999;        // cnt = expired
  do_reload(0);       // reload speadsheat
  while(1)
  {
    if(toCenter.poll() == rlFifo::DATA_AVAILABLE)
    {
      toCenter.read(interpreter.line,rl_PRINTF_LENGTH-1);
      if     (interpreter.isCommand("sigterm(")) do_sigterm();
      else if(interpreter.isCommand("sigkill(")) do_sigkill();
      else if(interpreter.isCommand("reload("))  do_reload(1);
      else if(interpreter.isCommand("remove("))  do_remove();
      else if(interpreter.isCommand("save("))    do_save();
      if(processes_have_been_modified)           do_save();
    }
    else if(cnt++ >= WATCHDOG_CYCLE_TIME)
    {
      cnt = 0;
      watchdog();
      if(processes_have_been_modified)           do_save();
    }
    else
    {
      rlsleep(1000); // 1 second
    }
    if(arg == NULL) return NULL; // just to fool the compiler
  }
}

int create_center()
{
  center.create(centerMain,NULL);
  return 0;
}
