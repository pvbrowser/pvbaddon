/***************************************************************************
                        pvcairovdi.h  -  description
                             -------------------
    begin                : Sun Nov 29 2017
    copyright            : (C) 2017 by R. Lehrig
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
#ifndef _PV_CAIROVDI_H_
#define _PV_CAIROVDI_H_

#include "pvcairo.h"

/*! <pre>
Class for drawing diagrams using libcairo on the pvserver and QSvgRenderer on the pvbrowser client
</pre> */
class pvCairoVdi
{
  /* font alignment */
  enum pvcairoFontAlignment {   /*             */
  ALIGN_LEFT=0,            /*  example         */
  ALIGN_CENTER,            /*      example     */
  ALIGN_RIGHT,             /*          example */
  ALIGN_VERT_CENTER        /*      e           */
  };                       /*      x           */
                           /*      a           */
                           /*      m           */
                           /*      p           */
                           /*      l           */
                           /*      e           */
                           /*                  */
                         
  /* linestyle for lines in axis */
  enum pvcairoLinestyle {
  LINESTYLE_NONE=0,
  LINESTYLE_CIRCLE,
  LINESTYLE_CROSS,
  LINESTYLE_RECT,
  LINESTYLE_CIRCLE_NO_LINE,
  LINESTYLE_CROSS_NO_LINE,
  LINESTYLE_RECT_NO_LINE
  };

public:
    pvCairoVdi(cairo_t *cr=NULL);
    ~pvCairoVdi();
    int setCairoContext(cairo_t *cr);
    int drawEllipse(int x, int y, int rx, int ry);
    int moveTo(int x, int y);
    int lineTo(int x, int y);
    int line(int x1, int y1, int x2, int y2);
    int text(int x, int y, const char *text, int alignment=ALIGN_LEFT);
    int textInAxis(float x, float y, const char *text, int alignment);
    int box(int x, int y, int w, int h);
    int boxWithText(int x, int y, int w, int h, int fontsize, const char *xlabel, const char *ylabel, const char * rylabel);
    int rect(int x, int y, int w, int h);
    int xAxis(float start, float delta, float end, int draw=1);
    int yAxis(float start, float delta, float end, int draw=1);
    int xGrid();
    int yGrid();
    int rightYAxis(float start, float delta, float end, int draw=1);
    int drawSymbol(int x, int y, int type);
    int line(float *x, float *y, int n, int linestayle=LINESTYLE_NONE);
    int setColor(int r, int g, int b);
    int setFont(const char *family, int size, int weight, int italic);
    int setWidth(int w);
    int setLinestyle(const char *dasharray);
    int getFontsize();
    int getBoxX();
    int getBoxY();
    int getBoxW();
    int getBoxH();

private:
    cairo_t  *cr;
    int      width;
    int      xold, yold;
    float    xmin,dx,xmax;
    float    ymin,dy,ymax;
    int      tx(float x);
    int      ty(float y);
    int      boxx,boxy,boxw,boxh;
    int      fontsize;
    int      sr;       // symbol radius
    char     floatFormat[80];
};

int pvCairoTestDiagram(cairo_t *cr, int xbox=100, int ybox=100, int widthbox=400, int heightbox=350);

#endif
