/***************************************************************************
                      pvcairowidgets.cpp  -  description
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

#include "pvcairowidget.h"
  
pvCairoWidget::pvCairoWidget()
{
}

pvCairoWidget::~pvCairoWidget()
{
}

int pvCairoWidget::isXYWH(const char *text)
{ // test if text starts with a digit and contains 3 commas
  if(text == NULL) return 0;
  int cnt=0;
  if(isdigit(*text))
  {
    while(*text != '\0')
    {
      if(*text == ',') cnt++;
      text++;
    }
    if(cnt == 3) return 1;
  }
  return 0;
}

int pvCairoWidget::getXYWH(const char *text, int *x, int *y, int *w, int *h)
{
  if(text == NULL) return -1;
  sscanf(text,"%d,%d,%d,%d",x,y,w,h);
  return 0;
}

int pvCairoWidget::floatMouseZoom(float *x, float *y, int zoom)
{ // convert screen mouse coordiates x,y to zoomed coordinates
  double dzoom = zoom / 100.0;
  //dzoom = dzoom*dzoom;
  if(dzoom < 0.01) dzoom = 0.01;
  *x = *x / dzoom;
  *y = *y / dzoom;
  return 0;
}

//##########################################################################

rlSpreadsheetRow *pvCairoWidget::hitTest(double dx, double dy, rlSpreadsheetTable *t, int *irow)
{ // test if coordinate dx,dy is within widget rectangle
  if(dx<0 || dy<0 || t==NULL) return NULL;
  int x,y,w,h;
  *irow = -1;
  rlSpreadsheetRow *wasHit = NULL;
  int i=0;
  rlSpreadsheetRow *row = t->getFirstRow();
  while(row != NULL) // return last row that has been hit (top most widget that was hit)
  {
    const char *xywh = row->text(colXYWH);
    if(isXYWH(xywh))
    {
      getXYWH(xywh,&x,&y,&w,&h);
      if(dx > x && dx < (x+w) &&
         dy > y && dy < (y+h)
        )
      {
        wasHit = row;
        *irow = i;
      }
    }
    row = row->getNextRow();
    i++;
  }
  return wasHit;
}

int pvCairoWidget::setChecked(rlSpreadsheetRow *widget, const char *checked)
{
  if(widget == NULL) return -1;
  rlString rltext = widget->text(pvCairoWidget::colText);
  if(strlen(checked) > strlen(rltext.text())) return -1;
  char *txt = rltext.text();
  while(*checked != '\0') *txt++ = *checked++;
  widget->setText(pvCairoWidget::colText, rltext.text());
  return 0;
}

int pvCairoWidget::setComment(rlSpreadsheetRow *widget, int comment_on)
{
  if(widget == NULL) return -1;
  const char *old = widget->text(colXYWH);
  if(*old == '#') return 0; // already commented
  if(isXYWH(old) == 0) return -1;
  int x,y,w,h;
  getXYWH(old,&x,&y,&w,&h);
  if(comment_on) widget->printf(colXYWH,"#%d,%d,%d,%d",x,y,w,h);
  else           widget->printf(colXYWH,"%d,%d,%d,%d",x,y,w,h);
  return 0;
}

int pvCairoWidget::move(rlSpreadsheetRow *widget, int _x, int _y)
{
  if(widget == NULL) return -1;
  const char *old = widget->text(colXYWH);
  if(isXYWH(old) == 0) return -1;
  int x,y,w,h;
  getXYWH(old,&x,&y,&w,&h);
  x = _x; y = _y;
  widget->printf(colXYWH,"%d,%d,%d,%d",x,y,w,h);
  return 0;
}

int pvCairoWidget::resize(rlSpreadsheetRow *widget, int _w, int _h)
{
  if(widget == NULL) return -1;
  const char *old = widget->text(colXYWH);
  if(isXYWH(old) == 0) return -1;
  int x,y,w,h;
  getXYWH(old,&x,&y,&w,&h);
  w = _w; h = _h;
  widget->printf(colXYWH,"%d,%d,%d,%d",x,y,w,h);
  return 0;
}

int pvCairoWidget::setGeometry(rlSpreadsheetRow *widget, int _x, int _y, int _w, int _h)
{
  if(widget == NULL) return -1;
  const char *old = widget->text(colXYWH);
  if(isXYWH(old) == 0) return -1;
  int x,y,w,h;
  getXYWH(old,&x,&y,&w,&h);
  x = _x; y = _y; w = _w; h = _h;
  widget->printf(colXYWH,"%d,%d,%d,%d",x,y,w,h);
  return 0;
}

int pvCairoWidget::drawRect(cairo_t *cr, rlSpreadsheetRow *widget, double r, double g, double b)
{
  int x,y,w,h;
  if(widget == NULL) return -1;
  const char *xywh = widget->text(colXYWH);
  if(isXYWH(xywh))
  {
    getXYWH(xywh,&x,&y,&w,&h);
    cairo_set_source_rgb(cr,r,g,b);
    cairo_rectangle(cr,x,y,w,h);
    cairo_stroke(cr);
  }
  return 0;
}

int pvCairoWidget::drawFilledRect(cairo_t *cr, rlSpreadsheetRow *widget, double r, double g, double b)
{
  int x,y,w,h;
  if(widget == NULL) return -1;
  const char *xywh = widget->text(colXYWH);
  if(isXYWH(xywh))
  {
    getXYWH(xywh,&x,&y,&w,&h);
    cairo_set_source_rgb(cr,r,g,b);
    cairo_rectangle(cr,x,y,w,h);
    cairo_fill(cr);
  }
  return 0;
}

int pvCairoWidget::drawText(cairo_t *cr, rlSpreadsheetRow *widget, double r, double g, double b)
{
  int x,y,w,h;
  if(widget == NULL) return -1;
  const char *xywh = widget->text(colXYWH);
  if(isXYWH(xywh))
  {
    const char *temp = widget->text(colTemp);
    cairo_text_extents_t extents;
    cairo_text_extents(cr,widget->text(colText),&extents);
    getXYWH(xywh,&x,&y,&w,&h);
    cairo_set_source_rgb(cr,r,g,b);
    if(*temp == 'l') // left aligned
    {
      cairo_move_to(cr,x + extents.height/2, y + h/2 - extents.height/2 - extents.y_bearing);
    }
    else if(*temp == 't') // top aligned
    {
      cairo_move_to(cr,x + extents.height/2, y + extents.height/2 - extents.y_bearing);
    }
    else
    {
      cairo_move_to(cr,x + w/2 - extents.width/2, y + h/2 - extents.height/2 - extents.y_bearing);
    }
    cairo_show_text(cr,widget->text(colText));
  }
  return 0;
}

int pvCairoWidget::drawPNG(cairo_t *cr, rlSpreadsheetRow *widget)
{
  int x,y,w,h;
  if(widget == NULL) return -1;
  const char *xywh = widget->text(colXYWH);
  if(isXYWH(xywh))
  {
    getXYWH(xywh,&x,&y,&w,&h);
    const char *filename = widget->text(colText);
    cairo_surface_t *cs = cairo_image_surface_create_from_png(filename);
    cairo_set_source_surface(cr,cs,x,y);
    cairo_paint(cr);
  }
  return 0;
}

