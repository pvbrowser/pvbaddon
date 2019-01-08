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

static cairo_status_t write_func_httpchunk(void *closure, const unsigned char *data, unsigned int length)
{
  char tbuf[80];
  if(closure == NULL) return CAIRO_STATUS_NULL_POINTER;
  if(data == NULL)    return CAIRO_STATUS_NULL_POINTER;
  PARAM *p = (PARAM *) closure;
  sprintf(tbuf, "%x\r\n", (int) length);
  pvtcpsend(p,tbuf,strlen(tbuf));
  pvtcpsend_binary(p,(const char *) data,(int) length);
  sprintf(tbuf, "\r\n");
  pvtcpsend(p, tbuf, strlen(tbuf));
  return CAIRO_STATUS_SUCCESS;
}

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

static cairo_status_t write_func_png_httpresponse(void *closure, const unsigned char *data, unsigned int length)
{
  //if(debug) printf("wfunc closure=%ld\n", (long int) closure);
  //if(debug) printf("data:%s\n",data);
  if(closure == NULL) return CAIRO_STATUS_NULL_POINTER;
  if(data == NULL)    return CAIRO_STATUS_NULL_POINTER;
  char cmd[80];
  PARAM *p = (PARAM *) closure;
  sprintf(cmd, "%x\r\n", (int) length);
  pvtcpsend(p, cmd, strlen(cmd));
  pvtcpsend_binary(p, (const char *) data, length);
  sprintf(cmd, "\r\n");
  pvtcpsend(p, cmd, strlen(cmd));
  return CAIRO_STATUS_SUCCESS;
}

static const char svgend[] = "\n<svgend></svgend>\n";

pvCairo::pvCairo()
{
  debug = 0;
  if(debug) printf("pvCairo()\n");
  m_id = 0;
  cr = NULL;
  surface = NULL;
  toUseSurface = SVG_QDraw;
  toUseText = NULL;
  is_idle = 1;;
}

pvCairo::~pvCairo()
{
  if(debug) printf("~pvCairo()\n");
  if(cr != NULL) cairo_destroy(cr);
  cr = NULL;
  if(surface != NULL)
  {
    int refcnt = cairo_surface_get_reference_count(surface);
    if(debug) printf("~pvCairo::refcnt=%d\n", refcnt);
    if(refcnt > 0)
    {
      if(is_idle == 1)
      { // only free if we are still within communicating thread
        if(debug) printf("~pvCairo::delete surface 1\n");
        cairo_surface_destroy(surface); // xxxxxx
      }
      else
      { // avoid double free corruptions
        if(debug) printf("~pvCairo::NOT delete surface 2\n");
      }
    }
  }
}

int pvCairo::setSurfaceToUse(surfaceToUse use, const char *text)
{
  // toUseSurface :=
  // SVG_QDraw
  // SVG_httpresponse
  // SVG_file
  // PNG_QDraw
  // PNG_httpresponse
  // PNG_file
  toUseSurface = use;
  toUseText = text;
  return 0;
}

cairo_t *pvCairo::beginDrawSVG(PARAM *p, int id, double width, double height)
{
  if(debug) printf("beginDrawSVG\n");
  char buf[80];
  is_idle = 0;
  svgAnimator.setSocket(&p->s);
  svgAnimator.setId(id);
  m_id = id;
  if(toUseSurface == SVG_QDraw)
  {
    surface = (cairo_surface_t *)cairo_svg_surface_create_for_stream(write_func,p,width,height);
    pvSetZoomX(p,id,-1.0f);
    pvSetZoomY(p,id,-1.0f);
    sprintf(buf,"gsvgRead(%d)\n",id);
    pvtcpsend(p, buf, strlen(buf));
    cr = cairo_create(surface);
    return cr;
  }
  else if(toUseSurface == SVG_httpresponse)
  {
    surface = (cairo_surface_t *)cairo_svg_surface_create_for_stream(write_func_httpchunk,p,width,height);
    sprintf(buf,"HTTP/1.1 200 OK\r\n");
    pvtcpsendstring(p,buf);
    sprintf(buf,"Server: pvserver-%s\r\n", pvserver_version);
    pvtcpsendstring(p,buf);
    sprintf(buf,"Keep-Alive: timeout=15, max=100\r\n");
    pvtcpsendstring(p,buf);
    sprintf(buf,"Connection: Keep-Alive\r\n");
    pvtcpsendstring(p,buf);
    sprintf(buf,"Content-Type: image/svg+xml\r\n");
    pvtcpsendstring(p,buf);
    sprintf(buf,"Transfer-Encoding: chunked\r\n\r\n");
    pvtcpsendstring(p,buf);
    cr = cairo_create(surface);
    return cr;
  }
  else
  {
    //surface = (cairo_surface_t *)cairo_svg_surface_create("cairo_test.svg", width, height);
    surface = (cairo_surface_t *)cairo_svg_surface_create(toUseText, width, height);
    cr = cairo_create(surface);
    return cr;
  }
}

cairo_t *pvCairo::beginDrawPNG(PARAM *p, int id, double width, double height)
{
  if(debug) printf("beginDrawPNG\n");
  if(p==NULL) {};
  is_idle = 0;
  m_id = id;
  surface = (cairo_surface_t *)cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
  cr = cairo_create(surface);
  return cr;
}

void pvCairo::endDrawSVG(PARAM *p)
{
  if(debug) printf("endDrawSVG\n");
  if(cr != NULL) cairo_destroy(cr);
  cr = NULL;
  if(surface != NULL) cairo_surface_destroy(surface);
  surface = NULL;
  if(toUseSurface == SVG_QDraw)
  {
    pvtcpsend(p, svgend, strlen(svgend));
    gBeginDraw(p,m_id);
    svgAnimator.writeSocket();
    gEndDraw(p);
  }
  else if(toUseSurface == SVG_httpresponse)
  {
    char tbuf[80];
    strcpy(tbuf,"0\r\n\r\n"); // last chunk
    pvtcpsend(p,tbuf,strlen(tbuf));
  }
  is_idle = 1;
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
  else if(toUseSurface == PNG_httpresponse)
  {
    char buf[80];
    sprintf(buf,"HTTP/1.1 200 OK\r\n");
    pvtcpsendstring(p,buf);
    sprintf(buf,"Server: pvserver-%s\r\n", pvserver_version);
    pvtcpsendstring(p,buf);
    sprintf(buf,"Keep-Alive: timeout=15, max=100\r\n");
    pvtcpsendstring(p,buf);
    sprintf(buf,"Connection: Keep-Alive\r\n");
    pvtcpsendstring(p,buf);
    sprintf(buf,"Content-Type: image/png\r\n");
    pvtcpsendstring(p,buf);
    sprintf(buf,"Transfer-Encoding: chunked\r\n\r\n");
    pvtcpsendstring(p,buf);
    cairo_surface_write_to_png_stream(surface,write_func_png_httpresponse,p);
    strcpy(buf,"0\r\n\r\n"); // last chunk
    pvtcpsend(p,buf,strlen(buf));
  }
  else
  {
    cairo_surface_write_to_png(surface,toUseText);
  }
  cairo_destroy(cr);
  cr = NULL;
  cairo_surface_destroy(surface);
  surface = NULL;
  is_idle = 1;
}

cairo_t *pvCairo::beginDraw(PARAM *p, int id, double width, double height)
{
  is_idle = 0;
  if(toUseSurface == SVG_QDraw || toUseSurface == SVG_file || toUseSurface == SVG_httpresponse) 
  {
    return beginDrawSVG(p, id, width, height);
  }
  return beginDrawPNG(p, id, width, height);  
}

void pvCairo::endDraw(PARAM *p)
{
  if(toUseSurface == SVG_QDraw || toUseSurface == SVG_file || toUseSurface == SVG_httpresponse) 
  {
    return endDrawSVG(p);
  }
  return endDrawPNG(p);  
}

int pvCairo::sendSVGFileToQDraw(PARAM *p, int id, const char *filename)
{
  if(p==NULL || id<0 || filename==NULL) return -1;
  unsigned char buf[MAX_PRINTF_LENGTH];
  FILE *fp = fopen(filename,"r");
  if(fp == NULL)
  {
    printf("sendSVGFileToQDraw::could not open file %s\n", filename);
    return -1;
  }
  
  svgAnimator.setSocket(&p->s);
  svgAnimator.setId(id);
  m_id = id;
  pvSetZoomX(p,id,-1.0f);
  pvSetZoomY(p,id,-1.0f);
  sprintf((char *) buf,"gsvgRead(%d)\n",id);
  pvtcpsend(p, (char *) buf, strlen((char *) buf));

  while(fgets((char *) buf,sizeof(buf)-1,fp) != NULL)
  {
    write_func(p, buf, strlen((const char *) buf));
    //pvtcpsend(p,(char *) buf,strlen((char *) buf));
  }
  fclose(fp);
  pvtcpsend(p, svgend, strlen(svgend));

  gBeginDraw(p,m_id);
  svgAnimator.writeSocket();
  gEndDraw(p);
  return 0;
}

int pvCairo::sendPNGFileToQDraw(PARAM *p, int id, const char *filename)
{
  if(p==NULL || id<0 || filename==NULL) return -1;
  unsigned char buf[1024];
  char cmd[80] = "gbufferLoadFromData\n";
  int len;

  FILE *fp = fopen(filename,"rb");
  if(fp == NULL)
  {
    printf("sendPNGFileToQDraw::could not open file %s\n", filename);
    return -1;
  }
  len = fread(buf,1,8,fp);
  if(len!=8 || buf[0]!=137 || 
               buf[1]!=80  || 
               buf[2]!=78  ||
               buf[3]!=71  ||
               buf[4]!=13  ||
               buf[5]!=10  ||
               buf[6]!=26  )
  {
    fclose(fp);
    printf("sendPNGFileToQDraw::is not a valid PNG file %s\n", filename);
    return -1;  
  }
  gBeginDraw(p,id);
  pvtcpsend(p,cmd,strlen(cmd));
  sprintf(cmd,"pngchunk=%d\n",len);
  pvtcpsend(p,cmd,strlen(cmd));
  pvtcpsend_binary(p,(const char *) buf,len);

  while(1)
  {
    len = fread(buf,1,8,fp);
    //printf("fread len=%d\n", len);
    if(len <= 0) break;
    unsigned int chunkLength = ((buf[0]*256 + buf[1])*256 + buf[2])*256 + buf[3];    
    if(chunkLength == 0)
    {
      // printf("Send EOF\n");
      sprintf(cmd,"pngchunk=%d\n",len);
      pvtcpsend(p,cmd,strlen(cmd));
      pvtcpsend_binary(p, (const char *) buf, len);
      
      len = fread(buf,1,8,fp);
      sprintf(cmd,"pngchunk=%d\n",len);
      pvtcpsend(p,cmd,strlen(cmd));
      pvtcpsend_binary(p, (const char *) buf, len);
      break;
    }
    //printf("chunkLength=%d\n", chunkLength);
    sprintf(cmd,"pngchunk=%d\n",8+chunkLength+4);
    pvtcpsend(p,cmd,strlen(cmd));
    pvtcpsend_binary(p, (const char *) buf, 8);
    while(chunkLength > 0)
    {
      len = sizeof(buf); // maxlen
      if(chunkLength < (unsigned int) len) len = chunkLength;
      len = fread(buf,1,len,fp);
      pvtcpsend_binary(p, (const char *) buf, len);
      chunkLength -= len;
    }
    len = fread(buf,1,4,fp);
    pvtcpsend_binary(p, (const char *) buf, 4);
  }

  gEndDraw(p);
  fclose(fp);
  return 0;
}

int pvCairo::sendFileToQDraw(PARAM *p, int id, const char *filename, rlTime *ftime)
{
  if(ftime != NULL)
  {
    rlTime now;
    now.getFileModificationTime(filename);
    if(now == *ftime)
    {
      if(debug) printf("UpToDate\n");
      return 0;
    }
    else
    {
      if(debug) printf("ftime=%s\n",now.getIsoTimeString());
      *ftime = now;
    }
  }
  if(p==NULL || id<0 || filename==NULL) return -1;
  if(strstr(filename,".svg") != NULL) return sendSVGFileToQDraw(p,id,filename);
  if(strstr(filename,".SVG") != NULL) return sendSVGFileToQDraw(p,id,filename);
  if(strstr(filename,".png") != NULL) return sendPNGFileToQDraw(p,id,filename);
  if(strstr(filename,".PNG") != NULL) return sendPNGFileToQDraw(p,id,filename);
  return -1;
}


