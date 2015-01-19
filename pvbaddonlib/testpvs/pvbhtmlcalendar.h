/***************************************************************************
                       pvbhtmlcalendar.h  -  description
                             -------------------
    begin                : Thu Sep 23 2014
    copyright            : (C) Lehrig Software Enigineering
    email                : lehrig@t-online.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU LESSER GENERAL PUBLIC LICENSE as        *
 *   published by the Free Software Foundation                             *
 *                                                                         *
 ***************************************************************************/
#ifndef _PVB_HTMLCALENDAR_H_
#define _PVB_HTMLCALENDAR_H_

#include <string.h>
#include "processviewserver.h"
#include "rlstring.h"
#include "rlspawn.h"

/*! <pre>
class for a serverside calendar wirget with HTML/CSS.
</pre> */
class pvbHtmlCalendar
{
public:
  enum
  {
    NEXT = 1,
    PREVIOUS,
    SELECTED
  } slotReturnCodes;

  pvbHtmlCalendar();
  virtual ~pvbHtmlCalendar();

  /*! <pre>
  init the widget with it's output widget
  </pre> */
  int slotInit(PARAM *p, int id, int month=-1, int year=-1, int createLinkToOther=1);

  /*! <pre>
  perhaps handle pvbrowser textEvent
  </pre> */
  int slotTextEvent(PARAM *p, int id, const char *text);

  /*! <pre>
  output calendar to pvbrowser
  </pre> */
  void setHtml(int id, int month=-1, int year=-1, int createLinkToOther=1);

  /*! <pre>
  generate mMonth member
  </pre> */
  void setMonth(int id, int month=-1, int year=-1, int createLinkToOther=0);

  rlString mHtml;
  rlString mStyle;
  rlString mHeader;
  rlString mTitleText;
  rlString mMonth;
  rlString mTrailer;
  
  int selectedDay, selectedMonth, selectedYear;
  int debug;
	
private:
  int mId;
  rlSpawn sp;
  void spawn(int id, int month, int year, int createLinkToOther);
  void splitLine(const char *line);
  char d1[4], d2[4], d3[4], d4[4], d5[4], d6[4], d7[4];
};

#endif
