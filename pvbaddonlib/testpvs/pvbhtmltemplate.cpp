/***************************************************************************
                       pvbhtmlcalendar.h  -  description
                             -------------------
    begin                : Thu Oct 02 2014
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
#include "pvbhtmltemplate.h"
#include "rltime.h"

pvbHtmlTemplate::pvbHtmlTemplate()
{
	debug = 0;
  mId = -1;
}

pvbHtmlTemplate::~pvbHtmlTemplate()
{
}

int pvbHtmlTemplate::update(PARAM *p)
{
  rlString tbuf;
  
  tbuf.read("test.body");
  tbuf += "<h1>Test Title</h1>\n";
  tbuf += "<p>generate html pages from pvserver.</p>\n";
  tbuf += "<img src=\"svgcal.png\" alt=\"was generated\"/>\n";
  tbuf += "<p>The above is an example buffer snapshot from QDrawWidget.</p>\n";
  pvSetTextEx(p,mId,tbuf.text(),HTML_BODY);
  pvHtmlOrSvgDump(p,mId,"test.html");

  return 0;
}

int pvbHtmlTemplate::slotInit(PARAM *p, int id)
{
  mId = id;
  rlString tbuf;
  tbuf.read("test.style");
  pvSetTextEx(p,mId,tbuf.text(),HTML_STYLE);

  tbuf  = "<h1>Test Title</h1>\n";
  tbuf += "<p>generate html pages from pvserver.</p>\n";
  pvSetTextEx(p,mId,tbuf.text(),HTML_BODY);
  return 0;
}

int pvbHtmlTemplate::slotTextEvent(PARAM *p, int id, const char *text)
{
  int pid, month, year;
  if(id != mId) return -1;
  if(strstr(text,"pvb://cal/next") != NULL)
  {
    sscanf(text,"pvb://cal/next?id=%d&month=%d&year=%d", &pid, &month, &year);
    printf("goto next current(%d,%d)\n", month, year);
    month++;
    if(month > 12) { month=1; year++; }
    return NEXT;
  }
  else if(strstr(text,"pvb://cal/previous") != NULL)
  {
    sscanf(text,"pvb://cal/previous?id=%d&month=%d&year=%d", &pid, &month, &year);
    printf("goto previous current(%d,%d)\n", month, year);
    month--;
    if(month < 1) { month=12; year--; }
    return PREVIOUS;
  }
  update(p);
  return 0;
}
