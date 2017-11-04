//###############################################################
//# mask1_slots.h for ProcessViewServer created: Do. Mai 30 17:29:06 2013
//# please fill out these slots
//# here you find all possible events
//# Yours: Lehrig Software Engineering
//# Visualization and automation of restroom
//###############################################################

#define PI 3.141592654f
#define MAXARRAY 150

typedef struct // (todo: define your data structure here)
{
  rlSvgAnimator ani_a;
  rlSvgAnimator ani_s;
  int status_spuelung;
  int alter_wasserstand, aktueller_wasserstand;
  rlState sm;
  char stname[32],old_stname[32];
  int ind;
  double x[MAXARRAY], y[MAXARRAY]; 
}
DATA;

#include "statemachine.h"

static void setSchaukel(DATA *d, int percent)
{
  int val = ((4 * percent)/10) + 50;
  rlSvgPosition pos;
  float k1 = 1.0f;
  float k2 = 0.0235f;
  float fval = ((float) (val-50-47));
  fval *= k1;
  d->ani_a.setMatrix("linker_arm",1.0f,0.0f,0.0f,-fval/2.0f,0.0f,0.0f);
  d->ani_a.setMatrix("rechter_arm",1.0f,0.0f,0.0f,fval,0.0f,0.0f);
  d->ani_a.setMatrix("schwimmer",1.0f,-0.0f,-0.0f,fval,0.0f,0.0f);
  float alpha = ((float) ((val-50)) / PI) * k2;
  pos.rotate(alpha,132.0f+50.0f,45.0f);
  d->ani_a.setMatrix("schaukel",pos);
}

static void setWasserstand(DATA *d, int percent)
{
  d->aktueller_wasserstand = percent;
  int val = (percent * 70 * 2) / 100;
  char buf[32];
  sprintf(buf,"%d",val);
  d->ani_a.svgPrintf("wasserstand","height=",buf);
  sprintf(buf,"%d",171-val+95);
  d->ani_a.svgPrintf("wasserstand","y=",buf);
  if(percent > 72)
  {
    float a = -100.0f / 28.0f;
    float b = 10000.0f / 28.0f;
    float fv = a*((float) percent) + b;
    setSchaukel(d,fv);
  }
  else
  {
    setSchaukel(d,100);
  }
  if(d->alter_wasserstand > percent) d->status_spuelung = 1;
  if(percent > 98) 
  {
    d->ani_a.show("tropfen2",0);
    d->ani_a.show("tropfen3",0);
  }
  else 
  {
    d->ani_a.show("tropfen2",1);
    d->ani_a.show("tropfen3",1);
  }
  if(percent < 2) 
  {
    d->ani_a.show("ablauf1",0);
    d->ani_a.show("ablauf2",0);
  }
  else 
  {
    d->ani_a.show("ablauf1",1);
    d->ani_a.show("ablauf2",1);
  }
  if(percent < 10 || percent == 100 || d->status_spuelung == 0)
  {
    d->status_spuelung = 0;
    d->ani_a.svgChangeStyleOption("ventil","fill:","#ffffff");
    d->ani_a.show("ablauf2",0);
  }
  else if(d->status_spuelung == 1)
  {
    d->ani_a.svgChangeStyleOption("ventil","fill:","#0000ff");
    d->ani_a.show("ablauf2",1);
  }
  else
  {
    d->ani_a.svgChangeStyleOption("ventil","fill:","#000000");
    d->ani_a.show("ablauf2",0);
  }
  if(percent == 100) d->status_spuelung = 0; 
}

static void setStatediagram(DATA *d)
{
  char name[80];
  if(strcmp(d->stname,d->old_stname) != 0)
  { 
    d->ani_s.svgRecursivePrintf("PV.Start","fill=","grey");
    d->ani_s.svgRecursivePrintf("PV.Spülen","fill=","grey");
    d->ani_s.svgRecursivePrintf("PV.Leer","fill=","grey");
    d->ani_s.svgRecursivePrintf("PV.Füllen","fill=","grey");
    d->ani_s.svgRecursivePrintf("PV.Voll","fill=","grey");
    strcpy(name,"PV."); strcat(name,d->stname);
    d->ani_s.svgRecursivePrintf(name,"fill=","green");
  }  
}

static void drawSVGa(PARAM *p, DATA *d, int id)
{ // Anlage.svg
  gBeginDraw(p,id);
  d->ani_a.writeSocket();
  gEndDraw(p);
}

static void drawSVGs(PARAM *p, DATA *d, int id)
{ // statemachine.svg
  gBeginDraw(p,id);
  d->ani_s.writeSocket();
  gEndDraw(p);
}

static int slotInit(PARAM *p, DATA *d)
{
  if(p == NULL || d == NULL) return -1;

  // init DATA
  d->ind = 0;
  for(int i=0; i<MAXARRAY; i++)
  {
    d->x[i] = 0.0;
    d->y[i] = 100.0;
  }
  d->stname[0] = '\0';
  d->old_stname[0] = '\0';
  d->status_spuelung = 0;
  d->alter_wasserstand = 90;
  d->aktueller_wasserstand = 100;
  pvSetValue(p,slider1,100);

  p->sleep = 200;

  // hide the test sliders
  pvHide(p,slider1);
  pvHide(p,slider2);
  pvHide(p,slider3);

  // init the svgAnimators
  d->ani_a.setSocket(&p->s);
  d->ani_a.setId(svga);
  d->ani_a.setMainObject("main");
  d->ani_a.read("Anlage.svg");

  d->ani_a.svgTextPrintf("PV.spuelung2",pvtr("Spülung"));
  pvSetZoomX(p, svga, 1.0f);
  pvSetZoomY(p, svga, 1.0f);
  setSchaukel(d,0);
  setWasserstand(d,100);
  drawSVGa(p,d,svga);
  d->alter_wasserstand = d->aktueller_wasserstand;

  d->ani_s.setSocket(&p->s);
  d->ani_s.setId(svgs);
  d->ani_s.setMainObject("graph1");
  if(p->language != DEFAULT_LANGUAGE) d->ani_s.read("statemachine_en.svg");
  else                                d->ani_s.read("statemachine.svg");
  pvSetZoomX(p, svgs, 1.0f);
  pvSetZoomY(p, svgs, 1.0f);
  drawSVGs(p,d,svgs);

  pvSetValue(p,slider3,50);

  // init the wasserstand diagram
  qpwSetCanvasBackground(p,plot,0,0,128);
  qpwEnableAxis(p,plot,yLeft);
  qpwEnableAxis(p,plot,xBottom);
  qpwSetTitle(p,plot,pvtr("Wasserstand"));

  qpwEnableOutline(p,plot,1);
  qpwSetOutlinePen(p,plot,GREEN);

  qpwSetAxisTitle(p,plot,xBottom,pvtr("Zeit/sec"));
  qpwSetAxisTitle(p,plot,yLeft,"%");

  qpwInsertCurve(p,plot,0,pvtr("Wasser"));
  qpwSetCurvePen(p,plot,0, GREEN, 3, SolidLine);
  qpwSetCurveYAxis(p,plot,0,yLeft);
  qpwInsertCurve(p,plot,1,"DUMMY");
  qpwSetCurvePen(p,plot,1, BLACK, 1, DashDotLine);
  qpwSetCurveYAxis(p,plot,1,yLeft);

  double x[] = {0, 10, 20, 30 ,40 ,50, 60, 70, 80, 90};
  double y[] = {0, 10, 20, 30 ,40 ,50, 60, 70, 80, 90};
  qpwSetCurveData(p,plot,0,10,x,y);
  x[0] = 0;                            y[0] = 120; 
  x[1] = 0;                            y[1] = -20; 
  x[2] = (double)(MAXARRAY * p->sleep) / 1000.0; y[2] = -20;
  x[3] = (double)(MAXARRAY * p->sleep) / 1000.0; y[3] = 120;
  qpwSetCurveData(p,plot,1,4,x,y);
  qpwReplot(p,plot);

  for(int i=0; i<MAXARRAY; i++)
  {
    d->x[i] = (double)(i * p->sleep) / 1000.0;
  }

  // init the statemachine
  rlState *s = &d->sm;
  s->user = (void *) d;
  s->stepCounter = -1;
  s->cycletime = p->sleep;
  s->lastState = NULL;
  s->nextStep  = &stStart;

  pvDownloadFile(p,"klospuelung2.wav");
  return 0;
}

static int slotNullEvent(PARAM *p, DATA *d)
{
  if(p == NULL || d == NULL) return -1;
//if(1) return 0;
  rlState *s = &d->sm;
  s->nextStep(s);                                      // statemachine step
  s->stepCounter++;
  if(d->alter_wasserstand != d->aktueller_wasserstand) 
  {
    setWasserstand(d, d->aktueller_wasserstand);
    drawSVGa(p,d,svga);                                // wasserstand SVG
  }
  if(strcmp(d->stname,d->old_stname) != 0)
  {
    setStatediagram(d);
    drawSVGs(p,d,svgs);                                // statemachine SVG
  }
  d->y[MAXARRAY-1] = d->aktueller_wasserstand;         // diagram wasserstand
  for(int i=0; i<(MAXARRAY-1); i++) 
  {
    d->y[i] = d->y[i+1];
  }
  d->ind++;
  if(d->ind >= MAXARRAY) d->ind = 0;
  qpwSetCurveData(p,plot,0,MAXARRAY-1,d->x,d->y);
  qpwReplot(p,plot);
  d->alter_wasserstand = d->aktueller_wasserstand;
  return 0;
}

static int slotButtonEvent(PARAM *p, int id, DATA *d)
{
  if(p == NULL || id == 0 || d == NULL) return -1;
  if(id == en)
  {
    p->language = DEFAULT_LANGUAGE + 1;
    pvSelectLanguage(p,"en");
    return 1;
  }
  else if(id == de)
  {
    p->language = DEFAULT_LANGUAGE;
    pvSelectLanguage(p,"de");
    return 1;
  }
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
  float x,y,w,h;
  float m11,m12,m21,m22,det,dx,dy;

  if(id == svga)
  {
    switch(textEventType(text))
    {
    case PLAIN_TEXT_EVENT:
      printf("plain\n");
      break;
    case WIDGET_GEOMETRY:
      int X,Y,W,H;
      getGeometry(text,&X,&Y,&W,&H);
      printf("geometry(%d)=%d,%d,%d,%d\n",id,X,Y,W,H);
      break;
    case PARENT_WIDGET_ID:
      int PID;
      getParentWidgetId(text,&PID);
      printf("parent(%d)=%d\n",id,PID);
      break;
    case SVG_LEFT_BUTTON_PRESSED:
      //printf("left pressed\n");
      //printf("objectname=%s\n",svgObjectName(text));
      if(strcmp(svgObjectName(text),"PV.spuelung1") == 0)
      { 
        d->status_spuelung = 1;
        if(d->aktueller_wasserstand < 100) d->aktueller_wasserstand += 1;
        if(d->aktueller_wasserstand > 30) pvPlaySound(p,"klospuelung2.wav");       
      }
      break;
    case SVG_MIDDLE_BUTTON_PRESSED:
      printf("middle pressed\n");
      printf("objectname=%s\n",svgObjectName(text));
      break;
    case SVG_RIGHT_BUTTON_PRESSED:
      printf("right pressed\n");
      printf("objectname=%s\n",svgObjectName(text));
      break;
    case SVG_LEFT_BUTTON_RELEASED:
      printf("left released\n");
      printf("objectname=%s\n",svgObjectName(text));
      break;
    case SVG_MIDDLE_BUTTON_RELEASED:
      printf("middle released\n");
      printf("objectname=%s\n",svgObjectName(text));
      break;
    case SVG_RIGHT_BUTTON_RELEASED:
      printf("right released\n");
      break;
    case SVG_BOUNDS_ON_ELEMENT:
      getSvgBoundsOnElement(text, &x, &y, &w, &h);
      printf("bounds object=%s xywh=%f,%f,%f,%f\n",svgObjectName(text),x,y,w,h);
      break;
    case SVG_MATRIX_FOR_ELEMENT:
      getSvgMatrixForElement(text, &m11, &m12, &m21, &m22, &det, &dx, &dy);
      printf("matrix object=%s m=%f,%f,%f,%f det=%f dx=%f dy=%f\n",svgObjectName(text),
                               m11,m12,m21,m22,det,dx,dy);
      break;
    default:
      printf("default\n");
      break;
    }
  }
  return 0;
}

static int slotSliderEvent(PARAM *p, int id, DATA *d, int val)
{
  if(p == NULL || id == 0 || d == NULL || val < -1000) return -1;
  // handle sliders for testing
  //2 pi = grad / 360
  if(id == slider1)
  {
    setWasserstand(d,val);
    /*
    val *= 2;
    char buf[32];
    sprintf(buf,"%d",val);
    d->ani_a.svgPrintf("wasserstand","height=",buf);
    sprintf(buf,"%d",171-val+95);
    d->ani_a.svgPrintf("wasserstand","y=",buf);
    */
  }
  else if(id == slider2)
  {
    rlSvgPosition pos;
    float alpha = 20.0f - ((float) val) / 30.0f;
    pos.rotate(alpha,132.0f+50.0f,45.0f);
    d->ani_a.setMatrix("schaukel",pos);
  }
  else if(id == slider3)
  {
    setSchaukel(d,val);
    /*
    rlSvgPosition pos;
    float k1 = 1.0f;
    float k2 = 0.0235f;
    float fval = ((float) (val-50-47));
    fval *= k1;
    d->ani_a.setMatrix("linker_arm",1.0f,0.0f,0.0f,-fval/2.0f,0.0f,0.0f);
    d->ani_a.setMatrix("rechter_arm",1.0f,0.0f,0.0f,fval,0.0f,0.0f);
    d->ani_a.setMatrix("schwimmer",1.0f,-0.0f,-0.0f,fval,0.0f,0.0f);
    float alpha = ((float) ((val-50)) / PI) * k2;
    pos.rotate(alpha,132.0f+50.0f,45.0f);
    d->ani_a.setMatrix("schaukel",pos);
    */
  }
  //drawSVGa(p,d,svga);
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

static int slotMouseOverEvent(PARAM *p, int id, DATA *d, int enter)
{
  if(p == NULL || id == 0 || d == NULL || enter < -1000) return -1;
  return 0;
}

static int slotUserEvent(PARAM *p, int id, DATA *d, const char *text)
{
  if(p == NULL || id == 0 || d == NULL || text == NULL) return -1;
  return 0;
}
