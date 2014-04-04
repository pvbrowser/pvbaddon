/***************************************************************************
                          pvapp.h  -  description
                             -------------------
    begin                : Sun Nov 12 2000
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
#ifndef _PVAPP_H_
#define _PVAPP_H_

#include <stdlib.h>
#include "processviewserver.h"
#include "rldefine.h"
#include "rlcutil.h"
#include "rlthread.h"
#include "rlfifo.h"
#include "rlspreadsheet.h"
#include "rlinterpreter.h"
#include "rlpcontrol.h"

#define BUS_ID "bus_id"

int create_center();
int create_eventlog();
int free_eventlog();
int show_mask1(PARAM *p);
int show_pcontrol(PARAM *p);
int show_edit(PARAM *p);
int show_event(PARAM *p);
int show_mask5(PARAM *p);

#ifdef unix
#define SPREADSHEAT_FILE        "PCONTROL.TXT"
#endif
#ifdef __VMS
#define SPREADSHEAT_FILE        "PCONTROL_VMS.TXT"
#endif
#ifdef _WIN32
#define SPREADSHEAT_FILE        "PCONTROL_WIN.TXT"
#endif
#define WATCHDOG_CYCLE_TIME     10 // seconds
#define STATE_MISSING           "Missing"
#define STATE_ACTIVE            "Active"
#define STATE_INACTIVE          "Inactive"
#define STATE_REMOVED           "Removed"
#define ICON_ACTIVE             "icon_green.bmp"
#define ICON_INACTIVE           "icon_yellow.bmp"
#define ICON_MISSING            "icon_red.bmp"

enum TypeSpreadsheet
{
  T_state = 1, T_pid, T_name, T_credit, T_interval, T_priority, T_startup_command, T_input, T_output, T_error, T_time, T_initial_credit
};

enum ListViewFields
{
  L_state = 0, L_pid, L_name, L_startdate, L_credit, L_interval, L_startup_command
};

#define FIRST_ROW 2

typedef struct
{
  int  view; // 0|1 1==only view
  // EDIT begin
  char state[MAX_EVENT_LENGTH];
  char name[MAX_EVENT_LENGTH];
  int  credit;
  int  interval;
  int  priority;
  char startup_command[MAX_EVENT_LENGTH];
  char input[MAX_EVENT_LENGTH];
  char output[MAX_EVENT_LENGTH];
  char error[MAX_EVENT_LENGTH];
  rlSpreadsheetTable  mytable;
  int  edited;
  // EDIT end
}USER;

typedef struct
{
  int pcontrol;
  int eventlog;
  int eventport;
}COMMAND_LINE_SWITCHES;
#endif
