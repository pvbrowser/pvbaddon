/***************************************************************************
                          pvcairo.h  -  description
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
#ifndef _PVCAIRO_H
#define _PVCAIRO_H

#include "processviewserver.h"
#include "rlsvganimator.h"
#include <string.h>
#include <cairo-svg.h>
#include <unistd.h>

class pvCairo
{
  public:
    enum surfaceToUse {
      SVG_QDraw=1, // default
      SVG_file,
      PNG_QDraw,
      PNG_file
    };
    pvCairo();
    virtual ~pvCairo();
    int setSurfaceToUse(surfaceToUse use, const char *text=NULL);
    cairo_t *beginDraw(PARAM *p, int id, double width, double height);
    void endDraw(PARAM *p);    
    cairo_t *cr;
    int debug; // set 1 to produce cairo_test.svg

  private:
    cairo_t *beginDrawSVG(PARAM *p, int id, double width, double height);
    void endDrawSVG(PARAM *p);    
    cairo_t *beginDrawPNG(PARAM *p, int id, double width, double height);
    void endDrawPNG(PARAM *p);    
    cairo_surface_t *surface;
    rlSvgAnimator svgAnimator;
    int m_id, toUseSurface;
    const char *toUseText;
};

#endif
