/***************************************************************************
                        pvcairowidgets.h  -  description
                             -------------------
    begin                : Thu Nov 02 2017
    copyright            : (C) 2017 by R. Lehrig
    email                : lehrig@t-online.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU LESSER GENERAL PUBLIC LICENSE as        *
 *   published by the Free Software Foundation                             *
 *                                                                         *
 ***************************************************************************/
/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
#ifndef _PVCAIRO_WIDGETS_H
#define _PVCAIRO_WIDGETS_H

#include "pvcairo.h"
#include "rlsvganimator.h"
#include "rlspreadsheet.h"

// This class does NOT communicate with the pvbrowser client
// because (PARAM *) p is NOT used here.
class pvCairoWidget
{
public:
  enum widgetColumns {
    colName = 1,
    colXYWH,
    colText,
    colTemp
  };

  pvCairoWidget();
  virtual ~pvCairoWidget();

  // helper functions
  int isXYWH(const char *text);
  int getXYWH(const char *text, int *x, int *y, int *w, int *h);
  int floatMouseZoom(float *x, float *y, int zoom); // transforn mouse coordinates x,y in slotFunctions according to zoom
  rlSpreadsheetRow *hitTest(double dx, double dy, rlSpreadsheetTable *t, int *irow); // here use transformed mouse coordinates
  int setChecked(rlSpreadsheetRow *widget, const char *checked); // setStartOfText = checked
 
  // geometry helper functions
  int setComment(rlSpreadsheetRow *widget, int comment_on=0); // set comment_on 0|1  will hide/show widget
  int move(rlSpreadsheetRow *widget, int x, int y);
  int resize(rlSpreadsheetRow *widget, int w, int h);
  int setGeometry(rlSpreadsheetRow *widget, int x, int y, int w, int h);

  // drawing helper functions that use a cairo_t *cr context 
  int drawRect(cairo_t *cr, rlSpreadsheetRow *widget, double r=0.0, double g=0.0, double b=0.0);
  int drawFilledRect(cairo_t *cr, rlSpreadsheetRow *widget, double r=0.9, double g=0.9, double b=0.9);
  int drawText(cairo_t *cr, rlSpreadsheetRow *widget, double r=0.0, double g=0.0, double b=0.0);
  int drawPNG(cairo_t *cr, rlSpreadsheetRow *widget);
};

#endif
