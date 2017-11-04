/***************************************************************************
                          pvcairo.cpp  -  description
                             -------------------
    begin                : Tue Oct 24 2017
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
#include "pvcairo.h"

static cairo_status_t write_func(void *closure, const unsigned char *data, unsigned int length)
{
  //if(debug) printf("wfunc closure=%ld\n", (long int) closure);
  //if(debug) printf("data:%s\n",data);
  if(closure == NULL) return CAIRO_STATUS_NULL_POINTER;
  if(data == NULL)    return CAIRO_STATUS_NULL_POINTER;

  unsigned int i;
  unsigned int end=0;
  for(i=0; i<length; i++) // we substitude /symbol/g/ because QSvgRenderer does not support symbol
  {
    if(data[i] == '>')
    {
      pvtcpsend_binary((PARAM *) closure, (const char *) &data[end], i - end + 1);
      end = i+1;
      pvtcpsend_binary((PARAM *) closure, "\n ", 2);
    }
    else if(strncmp((const char *) &data[i],"<symbol ",8) == 0)
    {
      if(i>end) pvtcpsend_binary((PARAM *) closure, (const char *) &data[end], i - end);
      pvtcpsend_binary((PARAM *) closure, "<g ", 3);
      i += 8;
      end = i;
    }
    else if(strncmp((const char *) &data[i],"</symbol>",9) == 0)
    {
      if(i>end) pvtcpsend_binary((PARAM *) closure, (const char *) &data[end], i - end);
      pvtcpsend_binary((PARAM *) closure, "</g>", 4);
      pvtcpsend_binary((PARAM *) closure, "\n ", 2);
      i += 9;
      end = i;
    }
  }
  if(i > end)
  {
    pvtcpsend_binary((PARAM *) closure, (const char *) &data[end], i - end);
  }
  return CAIRO_STATUS_SUCCESS;
}

static cairo_status_t write_func_png(void *closure, const unsigned char *data, unsigned int length)
{
  //if(debug) printf("wfunc closure=%ld\n", (long int) closure);
  //if(debug) printf("data:%s\n",data);
  if(closure == NULL) return CAIRO_STATUS_NULL_POINTER;
  if(data == NULL)    return CAIRO_STATUS_NULL_POINTER;
  char cmd[80];
  sprintf(cmd,"pngchunk=%d\n", length);
  pvtcpsend((PARAM *) closure, cmd, strlen(cmd));
  pvtcpsend_binary((PARAM *) closure, (const char *) data, length);
  return CAIRO_STATUS_SUCCESS;
}


static const char svgend[] = "\n<svgend></svgend>\n";

pvCairo::pvCairo()
{
  debug = 0;
  m_id = 0;
  cr = NULL;
  surface = NULL;
  toUseSurface = SVG_QDraw;
  toUseText = NULL;
}

pvCairo::~pvCairo()
{
  if(cr != NULL) cairo_destroy(cr);
  if(surface != NULL)
  {
    int refcnt = cairo_surface_get_reference_count(surface);
    if(debug) printf("~pvCairo::refcnt=%d\n", refcnt);
    if(refcnt > 0)
    {
      if(debug) printf("~pvCairo::NOT delete surface\n");
      //cairo_surface_destroy(surface);
    }
  }
}

int pvCairo::setSurfaceToUse(surfaceToUse use, const char *text)
{
  // toUseSurface :=
  // SVG_QDraw
  // SVG_file
  // PNG_QDraw
  // PNG_file
  toUseSurface = use;
  toUseText = text;
  return 0;
}

cairo_t *pvCairo::beginDrawSVG(PARAM *p, int id, double width, double height)
{
  char buf[80];
  svgAnimator.setSocket(&p->s);
  svgAnimator.setId(id);
  m_id = id;
  if(toUseSurface == SVG_QDraw)
  {
    surface = (cairo_surface_t *)cairo_svg_surface_create_for_stream(write_func,p,width,height);
  }
  else
  {
    //surface = (cairo_surface_t *)cairo_svg_surface_create("cairo_test.svg", width, height);
    surface = (cairo_surface_t *)cairo_svg_surface_create(toUseText, width, height);
  }
  pvSetZoomX(p,id,-1.0f);
  pvSetZoomY(p,id,-1.0f);
  sprintf(buf,"gsvgRead(%d)\n",id);
  pvtcpsend(p, buf, strlen(buf));
  cr = cairo_create(surface);
  return cr;
}

cairo_t *pvCairo::beginDrawPNG(PARAM *p, int id, double width, double height)
{
  if(p==NULL) {};
  m_id = id;
  surface = (cairo_surface_t *)cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
  cr = cairo_create(surface);
  return cr;
}

void pvCairo::endDrawSVG(PARAM *p)
{
  cairo_destroy(cr);
  cr = NULL;
  cairo_surface_destroy(surface);
  surface = NULL;
  pvtcpsend(p, svgend, strlen(svgend));
  gBeginDraw(p,m_id);
  svgAnimator.writeSocket();
  gEndDraw(p);
}

void pvCairo::endDrawPNG(PARAM *p)
{
  if(p==NULL) {};
  if(toUseSurface == PNG_QDraw)
  {
    gBeginDraw(p,m_id);
    char buf[] = "gbufferLoadFromData\n";
    pvtcpsend(p, buf, strlen(buf));
    cairo_surface_write_to_png_stream(surface,write_func_png,p);
    gEndDraw(p);
  }
  else
  {
    cairo_surface_write_to_png(surface,toUseText);
  }
  cairo_destroy(cr);
  cr = NULL;
  cairo_surface_destroy(surface);
  surface = NULL;
}

cairo_t *pvCairo::beginDraw(PARAM *p, int id, double width, double height)
{
  if(toUseSurface == SVG_QDraw || toUseSurface == SVG_file) 
  {
    return beginDrawSVG(p, id, width, height);
  }
  return beginDrawPNG(p, id, width, height);  
}

void pvCairo::endDraw(PARAM *p)
{
  if(toUseSurface == SVG_QDraw || toUseSurface == SVG_file) 
  {
    return endDrawSVG(p);
  }
  return endDrawPNG(p);  
}

