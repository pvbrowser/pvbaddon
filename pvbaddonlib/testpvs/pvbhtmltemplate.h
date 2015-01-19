/***************************************************************************
                       pvbhtmltemplate.h  -  description
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
#ifndef _PVB_HTMLTEMPLATE_H_
#define _PVB_HTMLTEMPLATE_H_

#include <string.h>
#include "processviewserver.h"
#include "rlstring.h"
#include "rlspawn.h"

/*! <pre>
class for a serverside calendar wirget with HTML/CSS.
</pre> */
class pvbHtmlTemplate
{
public:
  enum
  {
    NEXT = 1,
    PREVIOUS,
    SELECTED
  } slotReturnCodes;

  pvbHtmlTemplate();
  virtual ~pvbHtmlTemplate();

  /*! <pre>
  init the widget with it's output widget
  </pre> */
  int slotInit(PARAM *p, int id);

  /*! <pre>
  perhaps handle pvbrowser textEvent
  </pre> */
  int slotTextEvent(PARAM *p, int id, const char *text);

  /*! <pre>
  output calendar to pvbrowser
  </pre> */
  int update(PARAM *p);

  rlSpawn sp;
  int debug;
	
private:
  int mId;
};

#endif
