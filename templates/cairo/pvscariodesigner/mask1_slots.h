//###############################################################
//# mask1_slots.h for ProcessViewServer created: Mi. Okt. 25 12:37:48 2017
//# please fill out these slots
//# here you find all possible events
//# Yours: Lehrig Software Engineering
//###############################################################

// todo: uncomment me if you want to use this data aquisiton
// also uncomment this classes in main.cpp and pvapp.h
// also remember to uncomment rllib in the project file
//extern rlModbusClient     modbus;  //Change if applicable
//extern rlSiemensTCPClient siemensTCP;
//extern rlPPIClient        ppi;
#include "pvapp.h"

//### BeginOfCairoCode ########################################################
//    TODO: Draw your custom widgets with libcairo
//          Use this as a template for your own app
extern int surface;
const static int  debugme = 0;

static double getMeminfo(const char *name)
{
  char line[256];
  double dval = -1.0;
  name = strchr(name,'#');
  if(name == NULL) return dval;
  name++;
  int len = strlen(name);
  printf("getMeminfo: %s",name);
  FILE *fin = fopen("/proc/meminfo","r");
  if(fin == NULL) return dval;
  while(fgets(line,sizeof(line)-1,fin) != NULL)
  {
    if(strncmp(line,name,len) == 0)
    {
      const char *cptr = strchr(line,':');
      if(cptr == NULL) break;
      cptr++;
      while(*cptr == ' ') cptr++;
      sscanf(cptr,"%lf",&dval);
      break;
    }
  }
  fclose(fin);
  printf("%f\n",dval);
  return dval;
}

static double getValueCB(const void *p, const char *text)
{
  printf("getValueCB:: text=%s p=%ld\n", text, (long int)p);
  if(strstr(text,"#cpu_up1") != NULL)
  {
    return process_image[0];
  }
  else if(strstr(text,"#cpu_up2") != NULL)
  {
    return process_image[1];
  }
  else
  {
    return getMeminfo(text);
  }
}

static int isEqual(const char *s1, const char *s2)
{
  if(strcmp(s1,s2) == 0) return 1;
  return 0;
}

static int drawWidget(cairo_t *cr, pvCairoWidget *cw, rlSpreadsheetRow *widget)
{ // draw one of our custom widgets
  int x,y,w,h;
  const char *xywh = widget->text(pvCairoWidget::colXYWH);
  const char *name = widget->text(pvCairoWidget::colName);
  if(cw->isXYWH(xywh))
  {
    cw->getXYWH(xywh,&x,&y,&w,&h);
    if(isEqual(name,"Diagram"))
    {
      double aspectSave = cw->cornerAspect;
      cw->cornerAspect = 30.0;
      cw->drawButton(cr,widget);
      pvCairoTestDiagram(cr,x,y,w,h);
      cairo_set_font_size (cr, 14);
      cairo_select_font_face (cr, "Arial",
          CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
      cw->cornerAspect = aspectSave;
      return 0;
    }
  }
  cw->drawWidgetInterpret(cr,widget);
  return 0;
}

int drawMask1Widgets(PARAM *p, int id, rlSpreadsheetTable *t, int width, int height)
{ // draw all designed widgets on top of backround
  if(p==NULL || id<0 || t==NULL) return -1;
  pvCairo cairo;
  pvCairoWidget cw;
  cw.setGetValueCB(getValueCB, p);
  cairo.setSurfaceToUse((pvCairo::surfaceToUse) surface); // surface was set from p->url within main.cpp
  cairo.debug = 1;
  cairo_pattern_t *pattern;
  int x,y;

  cairo_t *cr = cairo.beginDraw(p,id,width,height);
  if(cr == NULL) return -1;
  /*
     Draw the background 
     Draw the squares in the background 
  */
  for (x=0; x<10; x++)
    for (y=0; y<10; y++)
      cairo_rectangle(cr, x*10.0, y*10.0, 5, 5);

  pattern = cairo_pattern_create_radial(50, 50, 5, 50, 50, 50);
  cairo_pattern_add_color_stop_rgb(pattern, 0, 0.75, 0.15, 0.99);
  cairo_pattern_add_color_stop_rgb(pattern, 0.9, 1, 1, 1);
  cairo_set_source(cr, pattern);
  cairo_fill(cr);

  /* Writing in the foreground */
  //cairo_set_font_size (cr, 15);
  //cairo_select_font_face (cr, "Georgia",
  //    CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
  cairo_set_font_size (cr, 14);
  cairo_select_font_face (cr, "Arial",
      CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
  cairo_set_source_rgb (cr, 0, 0, 0);

  /* Draw the designed widgets */
  rlSpreadsheetRow *row = t->getFirstRow();
  while(row != NULL)
  {
    drawWidget(cr,&cw,row);
    row = row->getNextRow();
  }

  cairo.endDraw(p);
  return 0;
}

//### EndOfCairoCode ########################################################
//###########################################################################
typedef struct // (todo: define your data structure here)
{
  rlSpreadsheetTable widgetTable;
  rlSpreadsheetRow *row;
  int lastY, radio, clean, zoom, alt, ctrl;
}
DATA;

static int drawMyWidgets(PARAM *p, DATA *d)
{
  drawMask1Widgets(p,drawPreview,&d->widgetTable,1280,1024);
  return 0;
}

static int statusMessage(PARAM *p, DATA *d)
{ 
  if(d->row == NULL)
  {
    pvStatusMessage(p,0,255,0,"CTRL-MouseClick to select ActiveWidget");
    return 0;
  }
  if(d->radio == rbMove)
  {
    pvStatusMessage(p,0,255,0,
      "ActiveWidget:: id=%s name=%s xywh=%s text=%s values=%s table_row=%d Use F5,F6,F7,F8 to move widget (ALT-W to switch to scale widget)", 
      d->row->text(pvCairoWidget::colId), 
      d->row->text(pvCairoWidget::colName), 
      d->row->text(pvCairoWidget::colXYWH), 
      d->row->text(pvCairoWidget::colText), 
      d->row->text(pvCairoWidget::colValues), 
      d->lastY+1);
  }
  if(d->radio == rbScale)
  {
    pvStatusMessage(p,0,255,0,
      "ActiveWidget:: id=%s name=%s xywh=%s text=%s values=%s table_row=%d Use F5,F6,F7,F8 to scale widget (ALT-M to switch to move widget)", 
      d->row->text(pvCairoWidget::colId), 
      d->row->text(pvCairoWidget::colName), 
      d->row->text(pvCairoWidget::colXYWH), 
      d->row->text(pvCairoWidget::colText), 
      d->row->text(pvCairoWidget::colValues), 
      d->lastY+1);
  }
  return 0;
}

int moveWidget(PARAM *p, DATA *d, int id)
{
  if(d->row == NULL) return -1;
  const int step = 5;
  int x,y,w,h;
  sscanf(d->row->text(pvCairoWidget::colXYWH),"%d,%d,%d,%d",&x,&y,&w,&h);
  if(d->radio == rbMove)
  {
    if(id == pbUp)    y -= step;
    if(id == pbDown)  y += step;
    if(id == pbLeft)  x -= step;
    if(id == pbRight) x += step;
  }
  else if(d->radio == rbScale)
  {
    if(id == pbUp)    h -= step;
    if(id == pbDown)  h += step;
    if(id == pbLeft)  w -= step;
    if(id == pbRight) w += step;
  }
  if(x < 0) x=0;
  if(y < 0) y=0;
  if(x > 2048) x=2048;
  if(y > 2048) y=2048;
  if(w < 0) w=0;
  if(h < 0) h=0;
  if(w > 2048) w=2048;
  if(h > 2048) h=2048;
  d->row->printf(pvCairoWidget::colXYWH,"%d,%d,%d,%d",x,y,w,h);
  pvTablePrintf(p,table1,pvCairoWidget::colXYWH-1,d->lastY,"%d,%d,%d,%d",x,y,w,h);
  drawMyWidgets(p,d);
  return 0;
}

static int slotInit(PARAM *p, DATA *d)
{
  if(p == NULL || d == NULL) return -1;
  pvResize(p,0,1280*2,1024*2);
  d->widgetTable.read(mask1WidgetTableCSV);
  //memset(d,0,sizeof(DATA));
  d->row = NULL;
  d->clean = 1;
  d->lastY = 0;
  d->radio = rbMove;
  d->zoom = 100;
  d->alt = d->ctrl = 0;
  pvSetBufferTransparency(p,drawPreview,BUFFER_TRANSPARENCY);
  pvCSVdump(p,table1,mask1WidgetTableCSV);
  pvSetNumRows(p,table1,100);
  pvSetColumnWidth(p,table1,1,150);
  pvSetColumnWidth(p,table1,2,150);
  pvSetColumnWidth(p,table1,3,150);
  pvSetColumnWidth(p,table1,4,150);
  for(int row=1; row<=100; row++) pvSetRowHeight(p,table1,row,20);
  drawMyWidgets(p,d);
  pvSetChecked(p,rbMove,1);

  pvDownloadFile(p,"pvcairo.html");
  pvSetSource(p,tbHelp,"pvcairo.html");
  
  pvStatusMessage(p,0,255,0,"CTRL-Click to select ActiveWidget");
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
  if(id == pbSave)
  {
    d->widgetTable.write(mask1WidgetTableCSV);
    d->clean = 1;
  }
  else if(id == pbUp || id == pbDown || id == pbLeft || id == pbRight)
  {
    printf("d->radio = %d\n", d->radio);
    moveWidget(p,d,id);
    d->clean = 0;
  }
  else if(id == pbMask2)
  {
    if(d->clean == 0)
    {
      pvMessageBox(p,-10,BoxWarning,"Do you want to save the table?",MessageBoxNo,MessageBoxOk,0);
      //d->widgetTable.write(widgetTableCSV); // in slotSliderEvent when MessageBoxOk
    }
    else
    {
      return 2; // show_mask2
    }
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
  return 0;
}

static int slotSliderEvent(PARAM *p, int id, DATA *d, int val)
{
  if(p == NULL || id == 0 || d == NULL || val < -1000) return -1;
  if(id == drawPreview)
  {
    d->zoom = val;
    if(debugme) printf("zoom=%d\n",d->zoom);
  }
  else if(id == -10)
  {
    if(val == MessageBoxOk)
    {
      d->widgetTable.write(mask1WidgetTableCSV);
    }
    return 2; // show_mask2
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
  if(id == rbMove)
  {
    if(strcmp(text,"(1)") == 0) d->radio = rbMove;
    else                        d->radio = rbScale;
    statusMessage(p,d);
  }
  else if(id == rbScale)
  {
    if(strcmp(text,"(1)") == 0) d->radio = rbScale;
    else                        d->radio = rbMove;
    statusMessage(p,d);
  }
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
  if(id == table1)
  {
    d->clean = 0;
    d->lastY = y;
    d->row = pvCairoWidget::irow2widget(&d->widgetTable, d->lastY);
    d->widgetTable.printf(x+1,y+2,"%s",text);
    drawMyWidgets(p,d);
    statusMessage(p,d);
  }
  return 0;
}

static int slotTableClickedEvent(PARAM *p, int id, DATA *d, int x, int y, int button)
{
  if(p == NULL || id == 0 || d == NULL || x < -1000 || y < -1000 || button < 0) return -1;
  if(id == table1)
  {
    d->lastY = y;
    d->row = pvCairoWidget::irow2widget(&d->widgetTable, d->lastY);
    statusMessage(p,d);
  }
  return 0;
}

static int slotSelectionEvent(PARAM *p, int id, DATA *d, int val, const char *text)
{
  if(p == NULL || id == 0 || d == NULL || val < -1000 || text == NULL) return -1;
  return 0;
}

static int slotClipboardEvent(PARAM *p, int id, DATA *d, int val)
{
  if(p == NULL || id == -1 || d == NULL || val < -1000) return -1;
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
  if(modifier == -1)
  {
    d->alt = 0;
    d->ctrl = 0;
    statusMessage(p,d);
  }
  else if(val == Key_F5)
  {
    moveWidget(p,d,pbLeft);
    d->clean = 0;
  }
  else if(val == Key_F6)
  {
    moveWidget(p,d,pbUp);
    d->clean = 0;
  }
  else if(val == Key_F7)
  {
    moveWidget(p,d,pbDown);
    d->clean = 0;
  }
  else if(val == Key_F8)
  {
    moveWidget(p,d,pbRight);
    d->clean = 0;
  }
  else if(modifier == ControlButton)
  {
    d->ctrl = 1;
    return 0;
  }
  else if(modifier == AltButton)
  {
    d->alt = 1;
    return 0;
  }
  return 0;
}

static int slotMouseMovedEvent(PARAM *p, int id, DATA *d, float x, float y)
{
  if(p == NULL || id == 0 || d == NULL || x < -1000 || y < -1000) return -1;
  //pvCairoWidget::floatMouseZoom(&x,&y,d->zoom);
  //rlSpreadsheetRow *row = pvCairoWidget::hitTest(x,y,&d->widgetTable);
  return 0;
}

static int slotMousePressedEvent(PARAM *p, int id, DATA *d, float x, float y)
{
  if(p == NULL || id == 0 || d == NULL || x < -1000 || y < -1000) return -1;
  int where = 0;
  pvCairoWidget::floatMouseZoom(&x,&y,d->zoom);
  rlSpreadsheetRow *row = pvCairoWidget::hitTest(x,y,&d->widgetTable,&where);
  if(row!=NULL) 
  {
    printf("where=%d\n", where);
    if(where & pvCairoWidget::North) printf("North\n");
    if(where & pvCairoWidget::South) printf("South\n");
    if(where & pvCairoWidget::West)  printf("West\n");
    if(where & pvCairoWidget::East)  printf("East\n");
  }
  if(row!=NULL && d->ctrl==1) 
  {
    d->row = row; // select active widget
    int irow = 1;
    row = d->widgetTable.getFirstRow();
    while(row != NULL)
    {
      if(row == d->row)
      {
        d->lastY = irow-2; break;
      }
      irow++;
      row = row->getNextRow();
    }
  }
  return 0;
}

static int slotMouseReleasedEvent(PARAM *p, int id, DATA *d, float x, float y)
{
  if(p == NULL || id == 0 || d == NULL || x < -1000 || y < -1000) return -1;
  pvCairoWidget::floatMouseZoom(&x,&y,d->zoom);
  rlSpreadsheetRow *row = pvCairoWidget::hitTest(x,y,&d->widgetTable);
  if(row!=NULL && d->ctrl==1) 
  {
    d->row = row; // select active widget
    int irow = 1;
    row = d->widgetTable.getFirstRow();
    while(row != NULL)
    {
      if(row == d->row)
      {
        d->lastY = irow-2; break;
      }
      irow++;
      row = row->getNextRow();
    }
  }
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
