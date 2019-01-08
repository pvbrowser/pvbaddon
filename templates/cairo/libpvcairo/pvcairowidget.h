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

//#define pvCairoWidget_RADIO_STRING_OFF   "( )"
//#define pvCairoWidget_RADIO_STRING_ON    "(◙)"
//#define pvCairoWidget_CHECKED_STRING_OFF "[ ]"
//#define pvCairoWidget_CHECKED_STRING_ON  "[♦]"

// This class does NOT communicate with the pvbrowser client
// because (PARAM *) p is NOT used here.
class pvCairoWidget
{
public:
  enum widgetColumns {
    colId = 1,
    colName,
    colXYWH,
    colText,
    colValues,
    colOpt1
  };

  enum widgetWhere {
    North = 1, South = 2, West = 4, East = 8
  };

  pvCairoWidget();
  virtual ~pvCairoWidget();

  // helper functions
  static int isXYWH(const char *text);
  static int getXYWH(const char *text, int *x, int *y, int *w, int *h);
  static int isDoubles(const char *text);
         int getDoubles(const char *text, double *d1, double *d2, double *d3, double *d4); // r,g,b,a || min,val,max,step
  static int floatMouseZoom(float *x, float *y, int zoom); // transforn mouse coordinates x,y in slotFunctions according to zoom
  static rlSpreadsheetRow *hitTest(double dx, double dy, rlSpreadsheetTable *t, int *where=NULL); // here use transformed mouse coordinates
  static rlSpreadsheetRow *irow2widget(rlSpreadsheetTable *t, int irow); // irow as received in slotTable... functions
  static int isChecked(rlSpreadsheetRow *widget);             // return := 0|1
  static int setChecked(rlSpreadsheetRow *widget, int check); // check := 0|1
  static int incrementValue(rlSpreadsheetRow *widget);        // return == 1 OK return == -1 OUT OF RANGE
  static int decrementValue(rlSpreadsheetRow *widget);        // return == 1 OK return == -1 OUT OF RANGE
 
  // geometry helper functions
  static int setComment(rlSpreadsheetRow *widget, int comment_on=0); // set comment_on 0|1  will hide/show widget
  static int move(rlSpreadsheetRow *widget, int x, int y);
  static int resize(rlSpreadsheetRow *widget, int w, int h);
  static int setGeometry(rlSpreadsheetRow *widget, int x, int y, int w, int h);

  // drawing helper functions that use a cairo_t *cr context 
  static int drawRect(cairo_t *cr, rlSpreadsheetRow *widget, double r=0.0, double g=0.0, double b=0.0);
  static int drawFilledRect(cairo_t *cr, rlSpreadsheetRow *widget, double r=0.9, double g=0.9, double b=0.9);
         int drawText(cairo_t *cr, rlSpreadsheetRow *widget, double r=0.0, double g=0.0, double b=0.0);
  static int drawPNG(cairo_t *cr, rlSpreadsheetRow *widget);
 
  // drawing helper functions that use a cairo_t *cr context 
  static int drawRect(cairo_t *cr, double x, double y, double w, double h);
  static int drawFilledRect(cairo_t *cr,  double x, double y, double w, double h);
  static int drawText(cairo_t *cr, double x, double y, const char *text);
  static int drawPNG(cairo_t *cr, double x, double y, const char *filename);
 
  // widget
  int setDefaultProperties();
  int setBorderColor( rlSpreadsheetRow *widget);       // text := R,G,B,A     (double)
  int setInnerColor( rlSpreadsheetRow *widget);        // text := R,G,B,A     (double)
  int setForegroundColor( rlSpreadsheetRow *widget);   // text := R,G,B,A     (double)
  int setCornerAspect( rlSpreadsheetRow *widget);      // text := ASPECT      (double)
  int setBorderLineWidth( rlSpreadsheetRow *widget);   // text := LINE_WIDTH  (double)
  int drawButton(cairo_t *cr, rlSpreadsheetRow *widget);
  int drawGauge(cairo_t *cr, rlSpreadsheetRow *widget);
  int drawWidgetInterpret(cairo_t *cr, rlSpreadsheetRow *widget);

  // defaultProperties
  double cornerAspect;
  double borderR, borderG, borderB, borderA, borderLineWidth;
  double innerR, innerG, innerB, innerA;
  double foregroundR, foregroundG, foregroundB, foregroundA;
  //double backgroundR, backgroundG, backgroundB, backgroundA;

  void setGetValueCB(double (*getValueCB)(const void *closure, const char *text), const void *closure);
private:
  double (*getValueCB)(const void *closure, const char *text);
  const void *getValueCBclosure;
};

#endif
