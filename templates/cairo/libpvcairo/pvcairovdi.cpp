/***************************************************************************
                        pvcairovdi.cpp  -  description
                             -------------------
    begin                : Sun Nov 29 2017
    copyright            : (C) 2016 by R. Lehrig
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
#include "pvcairovdi.h"
#include <math.h>

#ifndef M_PI
#define M_PI 3.141592654
#endif

pvCairoVdi::pvCairoVdi(cairo_t *_cr)
{
  cr = _cr;
  fontsize = 10;
  strcpy(floatFormat,"%.2f");
  dx = dy = 1.0f;
  sr = 3;
  boxx = boxy = boxw = boxh = 0;
  xmin = 0.0f;
  xmax = 100.0f;
  ymin = 0.0f;
  ymax = 100.0f;
  width = 1;
  xold = yold = 0;
}

pvCairoVdi::~pvCairoVdi()
{
}

int pvCairoVdi::setCairoContext(cairo_t *_cr)
{
  if(cr == NULL) return -1;
  cr = _cr;
  return 0;
}

int pvCairoVdi::drawEllipse(int x, int y, int rx, int ry)
{
  if(cr == NULL) return -1;
  double fx = x;
  double fy = y;
  double width = 2*rx;
  double height = 2*ry;
  cairo_save(cr);
  cairo_translate(cr, fx + width / 2., fy + height / 2.);
  cairo_scale(cr, width / 2., height / 2.);
  cairo_arc(cr, 0., 0., 1., 0., 2 * M_PI);
  cairo_restore(cr);
  return 0;
}

int pvCairoVdi::moveTo(int x, int y)
{
  if(cr == NULL) return -1;
  xold = x;
  yold = y;
  cairo_move_to(cr,x,y);
  return 0;
}

int pvCairoVdi::lineTo(int x, int y)
{
  if(cr == NULL) return -1;
  xold = x;
  yold = y;
  cairo_line_to(cr,x,y);
  cairo_stroke(cr);
  cairo_move_to(cr,x,y);
  return 0;
}

int pvCairoVdi::line(int x1, int y1, int x2, int y2)
{
  if(cr == NULL) return -1;
  moveTo(x1,y1);
  lineTo(x2,y2);
  cairo_stroke(cr);
  return 0;
}

int pvCairoVdi::textInAxis(float x, float y, const char *txt, int alignment)
{
  if(cr == NULL) return -1;
  float dy;
/*
  ymax-ymin        dy
  -----------   =  ----------
  boxh             fontsize/2
*/
  if(alignment == ALIGN_CENTER)
  {
    dy = ((ymax-ymin) * (fontsize/2) ) / (boxh);
    return text(tx(x), ty(y+dy), txt, alignment);
  }
  else
  {
    return text(tx(x), ty(y), txt, alignment);
  }
}

int pvCairoVdi::text(int x, int y, const char *txt, int alignment)
{
  if(cr == NULL || txt == NULL) return -1;
  cairo_text_extents_t extents;
  cairo_text_extents(cr,txt,&extents);
  switch(alignment)
  {
    case ALIGN_LEFT:     //  |example
      moveTo(x,y);
      cairo_show_text(cr,txt);
      break;
    case ALIGN_CENTER:   //  exa|mple
      moveTo(x-extents.width/2,y);
      cairo_show_text(cr,txt);
      break;
    case ALIGN_RIGHT:    //  example|
      moveTo(x-extents.width,y);
      cairo_show_text(cr,txt);
      break;
    case ALIGN_VERT_CENTER:
      moveTo(x,y+extents.width/2);
      cairo_matrix_t matrix;
      cairo_get_font_matrix(cr,&matrix);
      cairo_matrix_rotate(&matrix,-M_PI/2);
      cairo_set_font_matrix(cr,&matrix);
      cairo_show_text(cr,txt);
      cairo_matrix_rotate(&matrix,M_PI/2);
      cairo_set_font_matrix(cr,&matrix);
      break;
    default:
      moveTo(x,y);
      cairo_show_text(cr,txt);
      break;
  }
  return 0;
}

int pvCairoVdi::box(int x, int y, int w, int h)
{
  if(cr == NULL) return -1;
  boxx = x;
  boxy = y;
  boxw = w;
  boxh = h;
  moveTo(x  ,y  );
  lineTo(x+w,y  );
  lineTo(x+w,y+h);
  lineTo(x  ,y+h);
  lineTo(x  ,y  );
  return 0;
}

int pvCairoVdi::boxWithText(int x, int y, int w, int h, int fontsize, const char *xlabel, const char *ylabel, const char * rylabel)
{
  if(cr == NULL) return -1;
  box(x,y,w,h);
  if(xlabel  != NULL)
  {
    text(x+w/2,y+h+fontsize*3,xlabel,ALIGN_CENTER);
  }
  if(ylabel  != NULL)
  {
    text(x-fontsize*5,y+h/2,ylabel,ALIGN_VERT_CENTER);
  }
  if(rylabel != NULL) 
  {
    text(x+w+fontsize*5,y+h/2,rylabel,ALIGN_VERT_CENTER);
  }
  return 0;
}

int pvCairoVdi::rect(int x, int y, int w, int h)
{
  if(cr == NULL) return -1;
  moveTo(x   ,y  );
  lineTo(x+w ,y  );
  lineTo(x+w ,y+h);
  lineTo(x   ,y+h);
  lineTo(x   ,y  );
  return 0;
}

static int beautyval(char *text)
{
  char *cptr = strchr(text,'.');
  if(cptr != NULL)
  {
    char *end = cptr + strlen(cptr) - 1;
    while(end != cptr) // eliminate trailing 0
    {
      if     (*end == '0') { *end = '\0'; }
      else if(*end == '.') { *end = '\0'; break; }
      else                 { break; }
      end--;
    }
    if(cptr == end) *cptr = '\0';
  }
  return 0;
}

int pvCairoVdi::xGrid()
{
  if(cr == NULL) return -1;
  for(float x=(xmin+dx); x<xmax; x+=dx)
  {
    moveTo(tx(x),boxy);
    lineTo(tx(x),boxy+boxh);
  }
  return 0;
}

int pvCairoVdi::yGrid()
{
  if(cr == NULL) return -1;
  for(float y=(ymin+dy); y<=(ymax-dy); y+=dy)
  {
    moveTo(boxx,ty(y));
    lineTo(boxx+boxw, ty(y));
  }
  return 0;
}

int pvCairoVdi::xAxis(float start, float delta, float end, int draw)
{
  if(cr == NULL) return -1;
  float x;
  int   y;
  char  txt[80];

  xmin = start;
  dx   = delta;
  xmax = end;
  if(draw==0) return 0;

  x = start;
  y = boxy + boxh;

  while(x <= end)
  {
    moveTo(tx(x),y);
    lineTo(tx(x),y+8);
    sprintf(txt,floatFormat,x);
    beautyval(txt);
    text(tx(x),y+((3*fontsize)/2),txt,ALIGN_CENTER);
    x += delta;
  }

  if(start < 0.0f && end > 0.0f)
  {
    moveTo(tx(0.0f),boxy);
    lineTo(tx(0.0f),boxy+boxh);
  }
  return 0;
}

int pvCairoVdi::yAxis(float start, float delta, float end, int draw)
{
  if(cr == NULL) return -1;
  float y;
  int   x;
  char  txt[80];

  ymin = start;
  dy   = delta;
  ymax = end;
  if(draw==0) return 0;
  x = boxx;
  y = start;

  cairo_text_extents_t extents;
  while(y <= end)
  {
    moveTo(x,ty(y));
    lineTo(x-8,ty(y));
    sprintf(txt,floatFormat,y);
    beautyval(txt);
    cairo_text_extents(cr,txt,&extents);
    text(x-fontsize,ty(y)+extents.height/2,txt,ALIGN_RIGHT);
    y += delta;
  }

  if(start < 0.0f && end > 0.0f)
  {
    moveTo(boxx,ty(0.0f));
    lineTo(boxx+boxw,ty(0.0f));
  }
  return 0;
}

int pvCairoVdi::rightYAxis(float start, float delta, float end, int draw)
{
  if(cr == NULL) return -1;
  float y;
  int   x;
  char  txt[80];

  ymin = start;
  dy   = delta;
  ymax = end;
  if(draw==0) return 0;
  x = boxx+boxw;
  y = start;

  cairo_text_extents_t extents;
  while(y <= end)
  {
    xold = x;
    yold = ty(y);
    moveTo(xold, yold);
    lineTo(xold+8,yold);
    sprintf(txt,floatFormat,y);
    beautyval(txt);
    cairo_text_extents(cr,txt,&extents);
    text(xold+10,yold+extents.height/2,txt,ALIGN_LEFT);
    y += delta;
  }

  if(start < 0.0f && end > 0.0f)
  {
    int xnew, ynew;
    xold = boxx+boxw;
    yold = ty(0.0f);
    xnew = boxx+boxw;
    ynew = ty(0.0f);
    moveTo(xold,yold);
    lineTo(xnew,ynew);
    xold = xnew;
    yold = ynew;
  }
  return 0;
}

int pvCairoVdi::drawSymbol(int x, int y, int type)
{
  if(cr == NULL) return -1;
  int xnew, ynew;
  switch(type)
  {
    case LINESTYLE_CIRCLE:
    case LINESTYLE_CIRCLE_NO_LINE:
      drawEllipse(x-sr,y-sr,sr,sr);
      break;
    case LINESTYLE_CROSS:
    case LINESTYLE_CROSS_NO_LINE:
      xold = x+sr;
      yold = y-sr;
      line(x-sr,y+sr,xold,yold);
      xold = x+sr;
      yold = y+sr;
      line(x-sr,y-sr,xold,yold);
      break;
    case LINESTYLE_RECT:
    case LINESTYLE_RECT_NO_LINE:
      xold = x+sr;
      yold = y-sr;
      line(x-sr,y-sr,xold,yold);
      xnew = x+sr;
      ynew = y+sr;
      line(xold,yold,xnew,ynew);
      xold = xnew;
      yold = ynew;
      xnew = x-sr;
      ynew = y+sr;
      line(xold,yold,xnew,ynew);
      xold = xnew;
      yold = ynew;
      xnew = x-sr;
      ynew = y-sr;
      line(xold,yold,xnew,ynew);
      xold = xnew;
      yold = ynew;
      break;
    default:
      break;
  }
  return 0;
}

int pvCairoVdi::line(float *x, float *y, int n, int linestyle)
{
  if(cr == NULL) return -1;
  if(linestyle != LINESTYLE_CROSS_NO_LINE && linestyle != LINESTYLE_CIRCLE_NO_LINE &&linestyle != LINESTYLE_RECT_NO_LINE )
  {
    cairo_move_to(cr, tx(x[0]), ty(y[0]));
    for(int i=1; i<n; i++)
    {
      cairo_line_to(cr, tx(x[i]), ty(y[i]));
    }
    cairo_stroke(cr);
  }  
  if(linestyle != LINESTYLE_NONE)
  {
    for(int i=1; i<n; i++) drawSymbol(tx(x[i]),ty(y[i]),linestyle);
  }
  return 0;
}

int pvCairoVdi::setColor(int r, int g, int b)
{
  if(cr == NULL) return -1;
  double dr = r; dr /= 255;
  double dg = g; dg /= 255;
  double db = b; db /= 255;
  cairo_set_source_rgb(cr,dr,dg,db);
  return 0;
}

int pvCairoVdi::setFont(const char *family, int size, int weight, int italic)
{
  if(cr == NULL || family == NULL) return -1;
  fontsize = size;
  cairo_font_slant_t slant = CAIRO_FONT_SLANT_NORMAL;
  if(italic) slant = CAIRO_FONT_SLANT_ITALIC;
  cairo_font_weight_t cweight = CAIRO_FONT_WEIGHT_NORMAL;
  if(weight != 0) cweight = CAIRO_FONT_WEIGHT_BOLD;
  cairo_select_font_face(cr, family, slant, cweight);
  cairo_set_font_size(cr, fontsize);
  return 0;
}

int pvCairoVdi::setWidth(int w)
{
  if(cr == NULL) return -1;
  cairo_set_line_width(cr,w);
  width = w;
  return 0;
}

int pvCairoVdi::setLinestyle(const char *dasharray)
{
  if(cr == NULL) return -1;
  double dashes[10];
  int numDashes = 0;
  if(isdigit(*dasharray))
  {
    const char *cptr = dasharray;
    while(cptr != NULL && isdigit(*cptr))
    {
      int ival;
      sscanf(cptr,"%d",&ival);
      dashes[numDashes++] = ival;
      if(numDashes > 8) break;
      cptr = strchr(cptr,',');
      if(cptr != NULL) cptr++;
    }
    cairo_set_dash(cr,dashes,numDashes,0);
  }
  else
  {
    cairo_set_dash(cr,dashes,numDashes,0);
  }
  return 0;
}

int pvCairoVdi::tx(float x)
{
  return (int)(boxx + (((x-xmin)*boxw)/(xmax-xmin)));    // x          i
}                                                        // xmax-xmin  boxw

int pvCairoVdi::ty(float y)
{
  int i0;
  i0 = (int)((ymin * boxh)/(ymax-ymin));
  return i0 + (int)(boxy+boxh-((y*boxh)/(ymax-ymin))); // y          i        ymin       i0
}                                                      // ymax-ymin  boxh     ymax-ymin  boxh

int pvCairoVdi::getFontsize()
{
  if(cr == NULL) return 10;
  return fontsize;
}

int pvCairoVdi::getBoxX( )
{
  return boxx;
}

int pvCairoVdi::getBoxY()
{
  return boxy;
}

int pvCairoVdi::getBoxW()
{
  return boxw;
}

int pvCairoVdi::getBoxH()
{
  return boxh;
}

static float fslide=0.0f;
int pvCairoTestDiagram(cairo_t *cr, int xbox, int ybox, int widthbox, int heightbox)
{
  int fontsize = 12;
  fslide += M_PI / 30.0f;
  if(fslide > 2*M_PI) fslide = 0.0f;
  float x1[100], sin_x[100];
  float x2[100], cos_x[100];
  for(int i=0;i<100;i++)
  {
    float val = ((float) i) / 16.0f;
    x1[i] = val; sin_x[i]= (float) sin(val+fslide);
    x2[i] = val; cos_x[i]= (float) cos(val-fslide);
  }

  pvCairoVdi vdi(cr);
  vdi.setWidth(3);
  vdi.setColor(0,0,0);
  vdi.setFont("Courier",fontsize,1,0);
  vdi.boxWithText(xbox,ybox,widthbox,heightbox, fontsize, "x/radiant", "sin(x), cos(x)", "right label");
  vdi.xAxis(0,1.0f,2.0f*M_PI);
  vdi.yAxis(-1.5f,0.5f,1.5f);
  vdi.textInAxis(0.0f,1.0f,"text in axis", ALIGN_LEFT);
  vdi.setLinestyle("5,5");
  vdi.setWidth(1);
  vdi.xGrid();
  vdi.yGrid();
  vdi.setLinestyle("");
  vdi.setColor(255,0,0);
  vdi.line(x1, sin_x, 100, LINESTYLE_RECT);
  vdi.setColor(0,255,0);
  //vdi.line(x2, cos_x, 100, LINESTYLE_CROSS);
  vdi.line(x2, cos_x, 100);
  vdi.setColor(0,0,0);
  vdi.rightYAxis(-2.5f,0.5f,2.5f);
  fontsize = 24;
  vdi.setColor(0,0,255);
  vdi.setFont("Times", fontsize, 1, 0);
  //vdi.text(50, 50, "This is a Diagram", ALIGN_LEFT);
  fontsize = 12;
  vdi.setFont("Courier",fontsize,1,0);
  return 0;
}
