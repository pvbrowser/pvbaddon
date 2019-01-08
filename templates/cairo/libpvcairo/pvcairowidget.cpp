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
  setDefaultProperties();
  getValueCB = NULL;
  getValueCBclosure = NULL;
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

int pvCairoWidget::isDoubles(const char *text)
{ // test if text starts with a digit and contains 3 commas
  if(text == NULL) return 0;
  int cnt=0;
  if(isdigit(*text) || *text == '-')
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

int pvCairoWidget::getDoubles(const char *text, double *d1, double *d2, double *d3, double *d4)
{
  if(strchr(text,'@') == NULL)
  {
    sscanf(text,"%lf,%lf,%lf,%lf",d1,d2,d3,d4);
  }
  else
  {
    sscanf(text,"%lf,@,%lf,%lf",d1,d3,d4);
    if(getValueCB != NULL) *d2 = (getValueCB)(getValueCBclosure, text);
    else                   *d2 = -1.0;
  }
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

rlSpreadsheetRow *pvCairoWidget::hitTest(double dx, double dy, rlSpreadsheetTable *t, int *where)
{ // test if coordinate dx,dy is within widget rectangle
  if(dx<0 || dy<0 || t==NULL) return NULL;
  int x,y,w,h;
  rlSpreadsheetRow *wasHit = NULL;
  int i=0;
  rlSpreadsheetRow *row = t->getFirstRow();
  while(row != NULL) // return last row that has been hit (top most widget that was hit)
  {
    const char *name = row->text(colName);
    if(strncmp(name,"set",3) != 0)
    {
      const char *xywh = row->text(colXYWH);
      if(isXYWH(xywh))
      {
        getXYWH(xywh,&x,&y,&w,&h);
        if(dx > x && dx < (x+w) &&
           dy > y && dy < (y+h) )
        {
          wasHit = row;
          if(where != NULL)
          {
            *where = 0;
            if(dx < (x +w/2)) *where |= West;
            else              *where |= East;
            if(dy < (y +h/2)) *where |= North;
            else              *where |= South;
          }
        }
      }
    }
    row = row->getNextRow();
    i++;
  }
  return wasHit;
}

rlSpreadsheetRow *pvCairoWidget::irow2widget(rlSpreadsheetTable *t, int irow)
{
  if(t == NULL) return NULL;
  int i = 0;
  rlSpreadsheetRow *row = t->getFirstRow(); // the first row contains the title
  while((row = row->getNextRow()) != NULL)  // the following rows are the widgets
  {
    if(i==irow) return row;
    i++;
  }
  return NULL;
}

int pvCairoWidget::isChecked(rlSpreadsheetRow *widget)
{
  if(widget == NULL) return 0;
  const char *values = widget->text(colValues);
  if(*values == '0') return 0;
  return 1;
}

int pvCairoWidget::setChecked(rlSpreadsheetRow *widget, int checked)
{
  if(widget == NULL) return -1;
  if(checked == 0)  widget->setText(pvCairoWidget::colValues, "0");
  else              widget->setText(pvCairoWidget::colValues, "1");
  return 0;
}

int pvCairoWidget::incrementValue(rlSpreadsheetRow *widget)
{
  const char *values = widget->text(colValues);
  if(strchr(values,'@') != NULL) return 0;
  if(isDoubles(values))
  {
    double d1,d2,d3,d4;
    sscanf(values,"%lf,%lf,%lf,%lf",&d1,&d2,&d3,&d4);
    if(d2 >= d1 && d2 <= d3)
    {
      d2 += d4;
      if(d2 >= d1 && d2 <= d3)
      {
        widget->printf(colValues,"%.1lf,%.1lf,%.1lf,%.1lf",d1,d2,d3,d4);
        return 1;
      }
    }
  }
  return -1;
}

int pvCairoWidget::decrementValue(rlSpreadsheetRow *widget)
{
  const char *values = widget->text(colValues);
  if(strchr(values,'@') != NULL) return 0;
  if(isDoubles(values))
  {
    double d1,d2,d3,d4;
    sscanf(values,"%lf,%lf,%lf,%lf",&d1,&d2,&d3,&d4);
    if(d2 >= d1 && d2 <= d3)
    {
      d2 -= d4;
      if(d2 >= d1 && d2 <= d3)
      {
        widget->printf(colValues,"%.1lf,%.1lf,%.1lf,%.1lf",d1,d2,d3,d4);
        return 1;
      }
    }
  }
  return -1;
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

int pvCairoWidget::drawRect(cairo_t *cr, double x, double y, double w, double h)
{
  cairo_rectangle(cr,x,y,w,h);
  cairo_stroke(cr);
  return 0;
}

int pvCairoWidget::drawFilledRect(cairo_t *cr,  double x, double y, double w, double h)
{
  cairo_rectangle(cr,x,y,w,h);
  cairo_fill(cr);
  return 0;
}

int pvCairoWidget::drawText(cairo_t *cr, double x, double y, const char *text)
{
  cairo_move_to(cr,x, y);
  cairo_show_text(cr,text);
  return 0;
}

int pvCairoWidget::drawPNG(cairo_t *cr, double x, double y, const char *filename)
{
  cairo_surface_t *cs = cairo_image_surface_create_from_png(filename);
  cairo_set_source_surface(cr,cs,x,y);
  cairo_paint(cr);
  cairo_surface_destroy(cs);
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
  const char *name = widget->text(colName);
  const char *text = widget->text(colText);
  if(isXYWH(xywh))
  {
    getXYWH(xywh,&x,&y,&w,&h);
    const char *values = widget->text(colValues);
    const char *opt1 = widget->text(colOpt1);
    if     (*values == '0' && strcmp(name,"CheckBox") == 0) // not checked
    {
      
      rlString txt("□ ");
      txt += text; 
      cairo_text_extents_t extents;
      cairo_text_extents(cr,txt.text(),&extents);
      cairo_set_source_rgb(cr,r,g,b);
      int dc = extents.height/2;
      if     (*opt1 == 't') cairo_move_to(cr,x + dc                   , y + dc                     - extents.y_bearing);
      else if(*opt1 == 'l') cairo_move_to(cr,x + dc                   , y + h/2 - extents.height/2 - extents.y_bearing);
      else                  cairo_move_to(cr,x + w/2 - extents.width/2, y + h/2 - extents.height/2 - extents.y_bearing);
      cairo_show_text(cr,txt.text());
    }
    else if(*values == '1' && strcmp(name,"CheckBox") == 0) // is checked
    {
      rlString txt("■ ");
      txt += text; 
      cairo_text_extents_t extents;
      cairo_text_extents(cr,txt.text(),&extents);
      cairo_set_source_rgb(cr,r,g,b);
      int dc = extents.height/2;
      if     (*opt1 == 't') cairo_move_to(cr,x + dc                   , y + dc                     - extents.y_bearing);
      else if(*opt1 == 'l') cairo_move_to(cr,x + dc                   , y + h/2 - extents.height/2 - extents.y_bearing);
      else                  cairo_move_to(cr,x + w/2 - extents.width/2, y + h/2 - extents.height/2 - extents.y_bearing);
      cairo_show_text(cr,txt.text());
    }
    else if(*values == '0' && strcmp(name,"RadioButton") == 0) // not checked
    {
      rlString txt("() ");
      //rlString txt("◘ ");
      txt += text; 
      cairo_text_extents_t extents;
      cairo_text_extents(cr,txt.text(),&extents);
      cairo_set_source_rgb(cr,r,g,b);
      int dc = extents.height/2;
      if     (*opt1 == 't') cairo_move_to(cr,x + dc                   , y + dc                     - extents.y_bearing);
      else if(*opt1 == 'l') cairo_move_to(cr,x + dc                   , y + h/2 - extents.height/2 - extents.y_bearing);
      else                  cairo_move_to(cr,x + w/2 - extents.width/2, y + h/2 - extents.height/2 - extents.y_bearing);
      cairo_show_text(cr,txt.text());
    }
    else if(*values == '1' && strcmp(name,"RadioButton") == 0) // is checked
    {
      rlString txt("(●) ");
      //rlString txt("◙ ");
      txt += text; 
      cairo_text_extents_t extents;
      cairo_text_extents(cr,txt.text(),&extents);
      cairo_set_source_rgb(cr,r,g,b);
      int dc = extents.height/2;
      if     (*opt1 == 't') cairo_move_to(cr,x + dc                   , y + dc                     - extents.y_bearing);
      else if(*opt1 == 'l') cairo_move_to(cr,x + dc                   , y + h/2 - extents.height/2 - extents.y_bearing);
      else                  cairo_move_to(cr,x + w/2 - extents.width/2, y + h/2 - extents.height/2 - extents.y_bearing);
      cairo_show_text(cr,txt.text());
    }
    else if(strcmp(name,"Progress") == 0 || strcmp(name,"Slider") ==0) 
    {
      double min,val,max,step;
      const char *values = widget->text(colValues);
      min = val = max = step = 0.0f;
      getDoubles(values,&min,&val,&max,&step);       
      rlString txt;
      txt.printf(text,val);
      cairo_text_extents_t extents;
      cairo_text_extents(cr,txt.text(),&extents);
      cairo_set_source_rgb(cr,r,g,b);
      int dc = extents.height/2;
      if     (*opt1 == 't') cairo_move_to(cr,x + dc                   , y + dc                     - extents.y_bearing);
      else if(*opt1 == 'l') cairo_move_to(cr,x + dc                   , y + h/2 - extents.height/2 - extents.y_bearing);
      else                  cairo_move_to(cr,x + w/2 - extents.width/2, y + h/2 - extents.height/2 - extents.y_bearing);
      cairo_show_text(cr,txt.text());
      if(strcmp(name,"Slider") == 0)
      { // draw slider arrows 
        cairo_text_extents_t extents;
        cairo_text_extents(cr,"◄",&extents);
        cairo_move_to(cr,x, y + h/2 - extents.height/2 - extents.y_bearing);
        cairo_show_text(cr,"◄");
        cairo_text_extents(cr,"►",&extents);
        cairo_move_to(cr,x + w - (16*extents.width/10), y + h/2 - extents.height/2 - extents.y_bearing);
        cairo_show_text(cr,"►");
      }
    }
    else if(strcmp(name,"VProgress") == 0 || strcmp(name,"VSlider") ==0) 
    {
      double min,val,max,step;
      const char *values = widget->text(colValues);
      min = val = max = step = 0.0f;
      getDoubles(values,&min,&val,&max,&step);       
      rlString txt;
      txt.printf(text,val);
      cairo_text_extents_t extents;
      cairo_text_extents(cr,txt.text(),&extents);
      cairo_set_source_rgb(cr,r,g,b);
      int dc = extents.height/2;
      if     (*opt1 == 't') cairo_move_to(cr,x + dc                   , y + dc                     - extents.y_bearing);
      else if(*opt1 == 'l') cairo_move_to(cr,x + dc                   , y + h/2 - extents.height/2 - extents.y_bearing);
      else                  cairo_move_to(cr,x + w/2 - extents.width/2, y + h/2 - extents.height/2 - extents.y_bearing);
      cairo_show_text(cr,txt.text());
      if(strcmp(name,"VSlider") == 0)
      { // draw slider arrows 
        cairo_text_extents_t extents;
        cairo_text_extents(cr,"▲",&extents);
        cairo_move_to(cr,x + w/2 - extents.width/2 - extents.x_bearing, y + extents.height);
        cairo_show_text(cr,"▲");
        cairo_text_extents(cr,"▼",&extents);
        cairo_move_to(cr,x + w/2 - extents.width/2 - extents.x_bearing, y + h);
        cairo_show_text(cr,"▼");
      }
    }    
    else
    {
      cairo_text_extents_t extents;
      if(strchr(text,'%') == NULL)
      {
        cairo_text_extents(cr,text,&extents);
        cairo_set_source_rgb(cr,r,g,b);
        int dc = extents.height/2;
        if     (*opt1 == 't') cairo_move_to(cr,x + dc                   , y + dc                     - extents.y_bearing);
        else if(*opt1 == 'l') cairo_move_to(cr,x + dc                   , y + h/2 - extents.height/2 - extents.y_bearing);
        else                  cairo_move_to(cr,x + w/2 - extents.width/2, y + h/2 - extents.height/2 - extents.y_bearing);
        cairo_show_text(cr,text);
      }
      else
      {
        double min,val,max,step;
        getDoubles(values,&min,&val,&max,&step);       
        rlString txt;
        txt.printf(text,val);
        cairo_text_extents(cr,txt.text(),&extents);
        cairo_set_source_rgb(cr,r,g,b);
        int dc = extents.height/2;
        if     (*opt1 == 't') cairo_move_to(cr,x + dc                   , y + dc                     - extents.y_bearing);
        else if(*opt1 == 'l') cairo_move_to(cr,x + dc                   , y + h/2 - extents.height/2 - extents.y_bearing);
        else                  cairo_move_to(cr,x + w/2 - extents.width/2, y + h/2 - extents.height/2 - extents.y_bearing);
        cairo_show_text(cr,txt.text());
      }
    }
  }
  cairo_stroke(cr);
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
    cairo_surface_destroy(cs);
  }
  return 0;
}

int pvCairoWidget::setDefaultProperties()
{
  cornerAspect = 1.0;
  borderR = borderG = borderB = 0.0; borderA = 1.0; borderLineWidth = 0.5;
  innerR = innerG = innerB = 0.9; innerA = 0.5;
  foregroundR = foregroundG = 0.0; foregroundB = 1.0; foregroundA = 1.0;
  //backgroundR = backgroundG = backgroundB = 0.99; backgroundA = 1.0;
  return 0;
}

int pvCairoWidget::setBorderColor(rlSpreadsheetRow *widget)       // text := R,G,B,A     (double)
{
  getDoubles(widget->text(pvCairoWidget::colXYWH),&borderR,&borderG,&borderB,&borderA);
  return 0;
}

int pvCairoWidget::setInnerColor(rlSpreadsheetRow *widget)        // text := R,G,B,A     (double)
{
  getDoubles(widget->text(pvCairoWidget::colXYWH),&innerR,&innerG,&innerB,&innerA);
  return 0;
}

int pvCairoWidget::setForegroundColor(rlSpreadsheetRow *widget)        // text := R,G,B,A     (double)
{
  getDoubles(widget->text(pvCairoWidget::colXYWH),&foregroundR,&foregroundG,&foregroundB,&foregroundA);
  return 0;
}

int pvCairoWidget::setCornerAspect(rlSpreadsheetRow *widget)      // text := ASPECT      (double)
{
  sscanf(widget->text(pvCairoWidget::colXYWH),"%lf",&cornerAspect);
  return 0;
}

int pvCairoWidget::setBorderLineWidth(rlSpreadsheetRow *widget)   // text := LINE_WIDTH  (double)
{
  sscanf(widget->text(pvCairoWidget::colXYWH),"%lf",&borderLineWidth);
  return 0;
}

int pvCairoWidget::drawButton(cairo_t *cr, rlSpreadsheetRow *widget)
{
  const char *name = widget->text(pvCairoWidget::colName);
  const char *xywh = widget->text(pvCairoWidget::colXYWH);
  if(isXYWH(xywh))
  {
    int _x, _y, _w, _h;
    getXYWH(xywh,&_x,&_y,&_w,&_h);
    /* a custom shape that could be wrapped in a function */
    double x             = _x,             /* parameters like cairo_rectangle */
           y             = _y,
           width         = _w,
           height        = _h,
           aspect        = cornerAspect;   //1.0,     /* aspect ratio */
    double corner_radius = height / 5.0;   /* and corner curvature radius */
    if(*name == 'V') corner_radius = width / 5.0; // Vertical
    double radius = corner_radius / aspect;
    double degrees = M_PI / 180.0;

    cairo_new_sub_path(cr);
    cairo_arc(cr, x + width - radius, y + radius, radius, -90 * degrees, 0 * degrees);
    cairo_arc(cr, x + width - radius, y + height - radius, radius, 0 * degrees, 90 * degrees);
    cairo_arc(cr, x + radius, y + height - radius, radius, 90 * degrees, 180 * degrees);
    cairo_arc(cr, x + radius, y + radius, radius, 180 * degrees, 270 * degrees);
    cairo_close_path(cr);
    cairo_set_source_rgba(cr, innerR, innerG, innerB, innerA);
    cairo_fill_preserve(cr);
    cairo_set_source_rgba(cr, borderR, borderG, borderB, borderA);
    cairo_set_line_width(cr, borderLineWidth);
    cairo_stroke(cr);

    if(strcmp(name,"Progress") == 0 || strcmp(name,"Slider") == 0)
    {
      double min,val,max,step;
      const char *values = widget->text(colValues);
      min = val = max = step = 0.0f;
      getDoubles(values,&min,&val,&max,&step);
      if(max - min < 0.1) max = min+0.1;       
      cairo_new_sub_path(cr);
      double width2 = width * (val - min) / (max - min);
      if(width2 > width) width2 = width;
      cairo_arc(cr, x + width2 - radius, y + radius, radius, -90 * degrees, 0 * degrees);
      cairo_arc(cr, x + width2 - radius, y + height - radius, radius, 0 * degrees, 90 * degrees);
      cairo_arc(cr, x + radius, y + height - radius, radius, 90 * degrees, 180 * degrees);
      cairo_arc(cr, x + radius, y + radius, radius, 180 * degrees, 270 * degrees);
      cairo_close_path(cr);
      cairo_set_source_rgba(cr, foregroundR, foregroundG, foregroundB, foregroundA);
      cairo_fill_preserve(cr);
      cairo_stroke(cr);
    }
    else if(strcmp(name,"VProgress") == 0 || strcmp(name,"VSlider") == 0)
    {
      double min,val,max,step;
      const char *values = widget->text(colValues);
      min = val = max = step = 0.0f;
      getDoubles(values,&min,&val,&max,&step);
      if(max - min < 0.1) max = min+0.1;       
      cairo_new_sub_path(cr);
      double height2 = height * (max - val) / (max - min);
      if(height2 > height) height2 = height;
      cairo_arc(cr, x + width - radius, y + height2 + radius, radius, -90 * degrees, 0 * degrees);
      cairo_arc(cr, x + width - radius, y + height - radius, radius, 0 * degrees, 90 * degrees);
      cairo_arc(cr, x + radius, y + height - radius, radius, 90 * degrees, 180 * degrees);
      cairo_arc(cr, x + radius, y + height2 + radius, radius, 180 * degrees, 270 * degrees);
      cairo_close_path(cr);
      cairo_set_source_rgba(cr, foregroundR, foregroundG, foregroundB, foregroundA);
      cairo_fill_preserve(cr);
      cairo_stroke(cr);
    }
    
    drawText(cr,widget);
  }
  return 0;
}

int pvCairoWidget::drawGauge(cairo_t *cr, rlSpreadsheetRow *widget)
{
  //const char *name = widget->text(pvCairoWidget::colName);
  const char *xywh = widget->text(pvCairoWidget::colXYWH);
  if(isXYWH(xywh))
  {
    int _x, _y, _w, _h;
    double min,val,max,step;
    double ta1, ta2;
    getXYWH(xywh,&_x,&_y,&_w,&_h);
    const char *values = widget->text(pvCairoWidget::colValues);
    getDoubles(values,&min,&val,&max,&step);
    const char *opt1 = widget->text(pvCairoWidget::colOpt1);
    ta1 = 90.0  + 45.0;
    ta2 = 360.0 + 45.0;
    if(isdigit(*opt1) && strchr(opt1,',') != NULL)
    {
      sscanf(opt1,"%lf,%lf",&ta1,&ta2);
    }
    double xc = _x + _w/2.0;
    double yc = _y + _h/2.0;
    double radius = (_w + _h)/4;
    double angle1 = ta1 * (M_PI/180.0);  /* angles are specified */
    double angle2 = ta2 * (M_PI/180.0);  /* in radians           */
 
    if((max - min) < 0.1) max += 0.1;
    double angleval = angle1 + ((val - min) * (angle2 - angle1)) / (max - min);

    cairo_set_line_width(cr, 10.0);
    cairo_arc(cr, xc, yc, radius, angle1, angle2);
    cairo_stroke(cr);

    const char *text = widget->text(pvCairoWidget::colText);
    rlString txt;
    txt.printf(text,val);
    cairo_text_extents_t extents;
    cairo_text_extents(cr,txt.text(),&extents);
    cairo_move_to(cr,_x + _w/2 - extents.width/2, _y + _h - extents.height/2 - extents.y_bearing);
    cairo_show_text(cr,txt.text());
    
    // draw center circle
    cairo_set_source_rgba(cr, foregroundR, foregroundG, foregroundB, foregroundA);
    cairo_set_line_width(cr, 6.0);
    cairo_arc(cr, xc, yc, 10.0, 0, 2*M_PI);
    cairo_fill(cr);
    // draw needle
    cairo_arc(cr, xc, yc, radius, angleval, angleval);
    cairo_line_to(cr, xc, yc);
    cairo_stroke(cr);  
  }
  return 0;
}

static int isEqual(const char *s1, const char *s2)
{
  if(strcmp(s1,s2) == 0) return 1;
  return 0;
}

int pvCairoWidget::drawWidgetInterpret(cairo_t *cr, rlSpreadsheetRow *widget)
{ // draw one of our custom widgets
  int x,y,w,h;
  const char *xywh = widget->text(pvCairoWidget::colXYWH);
  const char *name = widget->text(pvCairoWidget::colName);
  if(strncmp(name,"set",3) == 0)
  {
    if(isEqual(name,"setDefaultProperties"))
    {
      setDefaultProperties();
    }
    else if(isEqual(name,"setBorderColor"))
    {
      setBorderColor(widget);
    }
    else if(isEqual(name,"setInnerColor"))
    {
      setInnerColor(widget);
    }
    else if(isEqual(name,"setForegroundColor"))
    {
      setForegroundColor(widget);
    }
    else if(isEqual(name,"setCornerAspect"))
    {
      setCornerAspect(widget);
    }
    else if(isEqual(name,"setBorderLineWidth"))
    {
      setBorderLineWidth(widget);
    }
  }
  else if(isXYWH(xywh))
  {
    getXYWH(xywh,&x,&y,&w,&h);
    const char *text = widget->text(pvCairoWidget::colText);
    const char *values = widget->text(pvCairoWidget::colValues);
    if(isEqual(name,"Box"))
    {
      drawButton(cr,widget);
    }
    else if(isEqual(name,"Button"))
    {
      drawButton(cr,widget);
    }
    else if(isEqual(name,"CheckBox"))
    {
      drawButton(cr,widget);
    }
    else if(isEqual(name,"Progress"))
    {
      drawButton(cr,widget);
    }
    else if(isEqual(name,"VProgress"))
    {
      drawButton(cr,widget);
    }
    else if(isEqual(name,"Label"))
    {
      drawText(cr,widget);
    }
    else if(isEqual(name,"RadioButton"))
    {
      drawButton(cr,widget);
    }
    else if(isEqual(name,"Slider"))
    {
      drawButton(cr,widget);
    }
    else if(isEqual(name,"VSlider"))
    {
      drawButton(cr,widget);
    }
    else if(isEqual(name,"Gauge"))
    {
      drawGauge(cr,widget);
    }
    else if(isEqual(name,"PNG"))
    {
      drawPNG(cr,widget);
    }
    else if(name[0] != '\0')
    {
      if(1) printf("drawElse %s \"%s\" %s\n", xywh, text, values);
      drawText(cr,widget);
    }
  }
  return 0;
}

void pvCairoWidget::setGetValueCB(double (*func)(const void *, const char *), const void *closure)
{
  getValueCB = func;
  getValueCBclosure = closure;
  return;
}

