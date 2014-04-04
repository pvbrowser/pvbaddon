//###############################################################
//# mask6_slots.h for ProcessViewServer created: Fr Nov 10 11:54:40 2006
//# please fill out these slots
//# here you find all possible events
//# Yours: Lehrig Software Engineering
//###############################################################
//SVG1

// todo: uncomment me if you want to use this data aquisiton
// also uncomment this classes in main.cpp and pvapp.h
// also remember to uncomment rllib in the project file
//extern rlModbusClient     modbus;
//extern rlSiemensTCPClient siemensTCP;
//extern rlPPIClient        ppi;

typedef struct // (todo: define your data structure here)
{
  rlSvgAnimator svgAnimator;
}
DATA;

/*********************************************************************************************

Definition
CTM := CurrentTransformationMatrix
t   := translate
r   := rotate
s   := scale

Equotiation
CTM = t(cx,cy)*r(a)*t(-cx,-cy)*t(x0,y0)*s(sx)

      |1 0 cx| |cos(a) -sin(a) 0| |1 0 -cx| |1 0 x0| |sx 0  0|
CTM = |0 1 cy|*|sin(a)  cos(a) 0|*|0 1 -cy|*|0 1 y0|*|0  sx 0|                            # OK
      |0 0 1 | |  0       0    1| |0 0  1 | |0 0 1 | |0  0  1|

      |1 0 cx| |cos(a) -sin(a) 0| |1 0 -cx| |sx 0  x0|
CTM = |0 1 cy|*|sin(a)  cos(a) 0|*|0 1 -cy|*|0  sx y0|                                    # OK
      |0 0 1 | |  0       0    1| |0 0  1 | |0  0  1 |

      |1 0 cx| |cos(a) -sin(a) 0| |sx 0  x0-cx|
CTM = |0 1 cy|*|sin(a)  cos(a) 0|*|0  sx y0-cy|                                           # OK
      |0 0 1 | |  0       0    1| |0  0  1    |

      |1 0 cx| |sx*cos(a) -sx*sin(a) (x0-cx)*cos(a)-(y0-cy)*sin(a)|
CTM = |0 1 cy|*|sx*sin(a)  sx*cos(a) (x0-cx)*sin(a)+(y0-cy)*cos(a)|                       # OK
      |0 0 1 | |  0          0                        1           |

      |sx*cos(a) -sx*sin(a) (x0-cx)*cos(a)-(y0-cy)*sin(a)+cx|
CTM = |sx*sin(a)  sx*cos(a) (x0-cx)*sin(a)+(y0-cy)*cos(a)+cy|                             # OK
      |  0          0                     1                 |

Check
with sx = 1 and a,x0,y0,cx,cy = 0

      |1 0 0|
CTM = |0 1 0|                                                                             # OK
      |0 0 1|

|x'|         |x|   |sx*cos(a)*x-sx*sin(a)*y+(x0-cx)*cos(a)-(y0-cy)*sin(a)+cx|   |1*x-0*y|
|y'| = CTM * |y| = |sx*sin(a)*x+sx*cos(a)*y+(x0-cx)*sin(a)+(y0-cy)*cos(a)+cy| = |0*x+1*y| # OK
|0 |         |0|   |                       0                                |   |   0   |

**********************************************************************************************/

static void setMatrix(DATA *d, const char *object, float sx, float alpha, float x0, float y0, float cx, float cy)
{
  // matrix:
  // a11 a12 a13
  // a21 a22 a23
  // a31 a32 a33

  float a11, a12, a13, a21, a22, a23, a31, a32, a33;

  a11 = sx*(float)cos(alpha);
  a12 = -sx*(float)sin(alpha);
  a13 = (x0 - cx)*(float)cos(alpha) - (y0 - cy)*(float)sin(alpha) + cx;
  a21 = sx*(float)sin(alpha);
  a22 = sx*(float)cos(alpha);
  a23 = (x0 - cx)*(float)sin(alpha) + (y0 - cy)*(float)cos(alpha) + cy;
  a31 = 0;
  a32 = 0;
  a33 = 1;

  d->svgAnimator.svgPrintf(object,"transform=","matrix(%f,%f,%f,%f,%f,%f)",a11,a21,a12,a22,a13,a23);
}


static int drawSVG1(PARAM *p, int id, DATA *d)
{
  if(d == NULL) return -1;
  gBeginDraw(p,id);
  d->svgAnimator.writeSocket();
  gEndDraw(p);
  return 0;
}

static int slotInit(PARAM *p, DATA *d)
{
  if(p == NULL || d == NULL) return -1;
  //memset(d,0,sizeof(DATA));
  pvResize(p,0,1280,1024);
  pvSetPixmap(p,back,"back.png");
  d->svgAnimator.setSocket(&p->s);
  d->svgAnimator.setId(svg1);
  //d->svgAnimator.read("test1.svg");
  d->svgAnimator.read("Zeichnung.svg");
  drawSVG1(p,svg1,d);
  return 0;
}

static int slotNullEvent(PARAM *p, DATA *d)
{
  if(p == NULL || d == NULL) return -1;
  return 0;
}

static int slotButtonEvent(PARAM *p, int id, DATA *d)
{
  if(p == NULL || id == 0 || d == NULL) return -1;

  if(id == back) return WELLCOME;
  //rlSetDebugPrintf(1);
  if     (id == buttonShowCircle)
  {
    d->svgAnimator.show("circle1", 1);
  }
  else if(id == buttonHideCircle)
  {
    d->svgAnimator.show("circle1", 0);
  }
  else if(id == buttonHello)
  {
    d->svgAnimator.svgTextPrintf("text1", "Hello");
  }
  else if(id == buttonWorld)
  {
    d->svgAnimator.svgTextPrintf("text1", "World");
  }
  else if(id == buttonShowMonitor)
  {
    d->svgAnimator.show("monitor1", 1);
  }
  else if(id == buttonHideMonitor)
  {
    d->svgAnimator.show("monitor1", 0);
  }
  else if(id == buttonMonitorPos1)
  {
    d->svgAnimator.svgPrintf("monitor1", "transform=","translate(300.5974,286.613)");
  }
  else if(id == buttonMonitorPos2)
  {
    d->svgAnimator.svgPrintf("monitor1", "transform=","translate(200.5974,286.613)");
  }
  else if(id == buttonAnimate)
  {
    // animate roll1
    // animate lifter
    float cx, cy;
    float scale;

    cx = 312.784f + 85.224f/2.0f;
    cy = 1052.36f - 702.914f - 85.224f/2.0f;
    scale = -162.0f/100.0f;
 
    for(int i=0; i<100; i++)
    {
      // setMatrix(DATA *d, const char *object, float sx, float alpha, float x0, float y0, float cx, float cy)
      setMatrix(d, "roll1", 1.0, (i+1)*(8*PI/100), 0.0, 0.0, cx, cy);
      setMatrix(d, "lifter", 1.0, 0.0, 0.0, scale*i, 0.0, 0.0);
      drawSVG1(p,svg1,d);
    }
  }  
  drawSVG1(p,svg1,d);
  return 0;
}

static int slotButtonPressedEvent(PARAM *p, int id, DATA *d)
{
  if(p == NULL || id == 0 || d == NULL) return -1;
  return 0;
}

static int slotButtonReleasedEvent(PARAM *p, int id, DATA *d)
{
  if(p == NULL || id == 0 || d == NULL) return -1;
  return 0;
}

static int slotTextEvent(PARAM *p, int id, DATA *d, const char *text)
{
  if(p == NULL || id == 0 || d == NULL || text == NULL) return -1;
  return 0;
}

static int slotSliderEvent(PARAM *p, int id, DATA *d, int val)
{
  if(p == NULL || id == 0 || d == NULL || val < -1000) return -1;

  if(id == slider)
  {
    // animate lifter
    float scale;

    // setMatrix(DATA *d, const char *object, float sx, float alpha, float x0, float y0, float cx, float cy)
    scale = -162.0f/100.0f; 
    setMatrix(d, "lifter", 1.0, 0.0, 0.0, scale*val, 0.0, 0.0);
    drawSVG1(p,svg1,d);
  }

  return 0;
}

static int slotCheckboxEvent(PARAM *p, int id, DATA *d, const char *text)
{
  if(p == NULL || id == 0 || d == NULL || text == NULL) return -1;
  return 0;
}

static int slotRadioButtonEvent(PARAM *p, int id, DATA *d, const char *text)
{
  if(p == NULL || id == 0 || d == NULL || text == NULL) return -1;
  return 0;
}

static int slotGlInitializeEvent(PARAM *p, int id, DATA *d)
{
  if(p == NULL || id == 0 || d == NULL) return -1;
  return 0;
}

static int slotGlPaintEvent(PARAM *p, int id, DATA *d)
{
  if(p == NULL || id == 0 || d == NULL) return -1;
  return 0;
}

static int slotGlResizeEvent(PARAM *p, int id, DATA *d, int width, int height)
{
  if(p == NULL || id == 0 || d == NULL || width < 0 || height < 0) return -1;
  printf("slotGlResizeEvent(%d,%d)\n",width,height);
  return 0;
}

static int slotGlIdleEvent(PARAM *p, int id, DATA *d)
{
  if(p == NULL || id == 0 || d == NULL) return -1;
  return 0;
}

static int slotTabEvent(PARAM *p, int id, DATA *d, int val)
{
  if(p == NULL || id == 0 || d == NULL || val < -1000) return -1;
  return 0;
}

static int slotTableTextEvent(PARAM *p, int id, DATA *d, int x, int y, const char *text)
{
  if(p == NULL || id == 0 || d == NULL || x < -1000 || y < -1000 || text == NULL) return -1;
  return 0;
}

static int slotTableClickedEvent(PARAM *p, int id, DATA *d, int x, int y, int button)
{
  if(p == NULL || id == 0 || d == NULL || x < -1000 || y < -1000 || button < 0) return -1;
  return 0;
}

static int slotSelectionEvent(PARAM *p, int id, DATA *d, int val, const char *text)
{
  if(p == NULL || id == 0 || d == NULL || val < -1000 || text == NULL) return -1;
  return 0;
}

static int slotClipboardEvent(PARAM *p, int id, DATA *d, int val)
{
  if(p == NULL || id == 0 || d == NULL || val < -1000) return -1;
  return 0;
}

static int slotRightMouseEvent(PARAM *p, int id, DATA *d, const char *text)
{
  if(p == NULL || id == 0 || d == NULL || text == NULL) return -1;
  //pvPopupMenu(p,-1,"Menu1,Menu2,,Menu3");
  return 0;
}

static int slotKeyboardEvent(PARAM *p, int id, DATA *d, int val, int modifier)
{
  if(p == NULL || id == 0 || d == NULL || val < -1000 || modifier < -1000) return -1;
  return 0;
}

static int slotMouseMovedEvent(PARAM *p, int id, DATA *d, float x, float y)
{
  if(p == NULL || id == 0 || d == NULL || x < -1000 || y < -1000) return -1;
  return 0;
}

static int slotMousePressedEvent(PARAM *p, int id, DATA *d, float x, float y)
{
  if(p == NULL || id == 0 || d == NULL || x < -1000 || y < -1000) return -1;
  return 0;
}

static int slotMouseReleasedEvent(PARAM *p, int id, DATA *d, float x, float y)
{
  if(p == NULL || id == 0 || d == NULL || x < -1000 || y < -1000) return -1;
  return 0;
}

static int slotUserEvent(PARAM *p, int id, DATA *d, const char *text)
{
  if(p == NULL || id == 0 || d == NULL || text == NULL) return -1;
  return 0;
}
