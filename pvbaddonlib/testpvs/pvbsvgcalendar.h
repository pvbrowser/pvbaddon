/***************************************************************************
                       pvbcalendar.h  -  description
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
#ifndef _PVB_SVGCALENDAR_H_
#define _PVB_SVGCALENDAR_H_

#include <string.h>
#include "processviewserver.h"
#include "rlstring.h"
#include "rlspawn.h"
#include "rlsvganimator.h"

/*! <pre>
class for a serverside calendar wirget with HTML/CSS.
</pre> */
class pvbSvgCalendar
{
public:
  enum
  {
    NEXT = 1,
    PREVIOUS,
    SELECTED,
    CLOSE
  } slotReturnCodes;

  pvbSvgCalendar();
  virtual ~pvbSvgCalendar();

  /*! <pre>
  output calendar to pvbrowser
  </pre> */
  void setSvg(int id, int month=-1, int year=-1, int createLinkToOther=1);

  /*! <pre>
  update/render svg in pvbrowser
  </pre> */
  int drawSVG(PARAM *p);
	
  /*! <pre>
  Initialize graphics
  </pre> */
  int slotInit(PARAM *p, int id, const char *svgfile, float scale=1.0f, int month=-1, int year=-1, int createLinkToOther=0);

  /*! <pre>
  perhaps handle pvbrowser textEvent
  </pre> */
  int slotTextEvent(PARAM *p, int id, const char *text);

  int selectedDay, selectedMonth, selectedYear;
  int debug;
  rlSvgAnimator ani;

private:
  int mId;
  rlSpawn sp;
  void spawn(int id, int month, int year, int createLinkToOther);
  void splitLine(const char *line);
  char d1[4], d2[4], d3[4], d4[4], d5[4], d6[4], d7[4];
  char selectedObject[8];
  int  currentDays[7][8], currentMonth, currentYear;
};

#endif
