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

static int drawWidget(cairo_t *cr, rlSpreadsheetRow *widget)
{ // draw one of our custom widgets
  int x,y,w,h;
  pvCairoWidget cw;
  const char *xywh = widget->text(pvCairoWidget::colXYWH);
  if(cw.isXYWH(xywh))
  {
    cw.getXYWH(xywh,&x,&y,&w,&h);
    const char *name = widget->text(pvCairoWidget::colName);
    const char *text = widget->text(pvCairoWidget::colText);
    const char *temp = widget->text(pvCairoWidget::colTemp);
    if(strcmp(name,"Box")==0)
    {
      if(debugme) printf("drawBox %s \"%s\" %s\n", xywh, text, temp);
      cw.drawFilledRect(cr,widget);
      cw.drawText(cr,widget);
    }
    else if(strcmp(name,"Button")==0)
    {
      if(debugme) printf("drawButton %s \"%s\" %s\n", xywh, text, temp);
      cw.drawFilledRect(cr,widget);
      cw.drawRect(cr,widget);
      cw.drawText(cr,widget);
    }
    else if(strcmp(name,"CheckBox")==0)
    {
      if(debugme) printf("drawCheckBox %s \"%s\" %s\n", xywh, text, temp);
      cw.drawFilledRect(cr,widget);
      cw.drawText(cr,widget);
      cw.drawRect(cr,widget);
    }
    else if(strcmp(name,"Label")==0)
    {
      if(debugme) printf("drawLabel %s \"%s\" %s\n", xywh, text, temp);
      cw.drawFilledRect(cr,widget);
      cw.drawText(cr,widget);
    }
    else if(strcmp(name,"RadioButton")==0)
    {
      if(debugme) printf("drawRadioButton %s \"%s\" %s\n", xywh, text, temp);
      cw.drawFilledRect(cr,widget);
      cw.drawText(cr,widget,1,0,0);
    }
    else if(strcmp(name,"Slider")==0)
    {
      if(debugme) printf("(not implemented yet) drawSlider %s \"%s\" %s\n", xywh, text, temp);
      cw.drawFilledRect(cr,widget);
      cw.drawText(cr,widget);
    }
    else if(strcmp(name,"Diagram")==0)
    {
      if(debugme) printf("(example for a more complex widget) %s \"%s\" %s\n", xywh, text, temp);
      cw.drawFilledRect(cr,widget);
      cw.drawText(cr,widget);
      pvCairoTestDiagram(cr,x,y,w,h);
      cairo_set_font_size (cr, 14);
      cairo_select_font_face (cr, "Arial",
          CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
    }
    else if(strcmp(name,"PNG")==0)
    {
      if(debugme) printf("(example for a PNG) %s \"%s\" %s\n", xywh, text, temp);
      cw.drawPNG(cr,widget);
    }
    else if(name[0] != '\0')
    {
      if(debugme) printf("drawElse %s \"%s\" %s\n", xywh, text, temp);
      //cw.drawFilledRect(cr,widget);
      cw.drawText(cr,widget);
    }
  }
  return 0;
}

int drawMask1Widgets(PARAM *p, int id, rlSpreadsheetTable *t, int width_svg, int height_svg)
{ // draw all designed widgets on top of backround
  if(p==NULL || id<0 || t==NULL) return -1;
  pvCairo cairo;
  cairo.setSurfaceToUse((pvCairo::surfaceToUse) surface); // surface was set from p->url within main.cpp
  //murx++;
  cairo.debug = 1;
  cairo_pattern_t *pattern;
  int x,y;

  cairo_t *cr = cairo.beginDraw(p,id,width_svg,height_svg);
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
    drawWidget(cr,row);
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
  int lastRow, radio, clean, zoom;
}
DATA;

static int drawMyWidgets(PARAM *p, DATA *d)
{
  drawMask1Widgets(p,drawPreview,&d->widgetTable,1280,1024);
  return 0;
}

int moveWidget(PARAM *p, DATA *d, int id)
{
  const int step = 5;
  int x,y,w,h;
  int row = d->lastRow;
  //if(debugme) printf("DEBUG %s\n",d->widgetTable.text(pvCairoWidget::colXYWH,row));
  sscanf(d->widgetTable.text(pvCairoWidget::colXYWH,row+2),"%d,%d,%d,%d",&x,&y,&w,&h);
  //if(debugme) printf("moveWidget(%d,%d,%d,%d)\n",x,y,w,h);
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
  d->widgetTable.printf(pvCairoWidget::colXYWH,row+2,"%d,%d,%d,%d",x,y,w,h);
  pvTablePrintf(p,table1,pvCairoWidget::colXYWH-1,row,"%d,%d,%d,%d",x,y,w,h);
  drawMyWidgets(p,d);
  return 0;
}

static int slotInit(PARAM *p, DATA *d)
{
  if(p == NULL || d == NULL) return -1;
  d->widgetTable.read(mask1WidgetTableCSV);
  //memset(d,0,sizeof(DATA));
  d->clean = 1;
  d->lastRow = 2;
  d->radio = rbMove;
  d->zoom = 100;
  pvSetBufferTransparency(p,drawPreview,BUFFER_TRANSPARENCY);
  pvCSVdump(p,table1,mask1WidgetTableCSV);
  pvSetNumRows(p,table1,100);
  pvSetColumnWidth(p,table1,1,150);
  drawMyWidgets(p,d);
  pvSetChecked(p,rbMove,1);

  pvDownloadFile(p,"pvcairo.html");
  pvSetSource(p,tbHelp,"pvcairo.html");
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
  }
  else if(id == rbScale)
  {
    if(strcmp(text,"(1)") == 0) d->radio = rbScale;
    else                        d->radio = rbMove;
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
    d->lastRow = y;
    printf("Remember %s row=%d\n",text,d->lastRow);
    d->widgetTable.printf(x+1,y+2,"%s",text);
    drawMyWidgets(p,d);
  }
  return 0;
}

static int slotTableClickedEvent(PARAM *p, int id, DATA *d, int x, int y, int button)
{
  if(p == NULL || id == 0 || d == NULL || x < -1000 || y < -1000 || button < 0) return -1;
  if(id == table1)
  {
    d->lastRow = y;
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
  return 0;
}

static int slotMouseMovedEvent(PARAM *p, int id, DATA *d, float x, float y)
{
  if(p == NULL || id == 0 || d == NULL || x < -1000 || y < -1000) return -1;
  int irow = -1;

  pvCairoWidget widget;
  widget.floatMouseZoom(&x,&y,d->zoom);
  rlSpreadsheetRow *row = widget.hitTest(x,y,&d->widgetTable,&irow);
  if(debugme) printf("slotMouseMovedEvent: x=%f y=%f row=%ld irow=%d\n", x, y, (long int) row, irow);
  if(debugme && row!=NULL) printf("name=%s text=%s\n", row->text(pvCairoWidget::colName), row->text(pvCairoWidget::colText));
  return 0;
}

static int slotMousePressedEvent(PARAM *p, int id, DATA *d, float x, float y)
{
  if(p == NULL || id == 0 || d == NULL || x < -1000 || y < -1000) return -1;
  pvCairoWidget widget;
  int irow = -1;
  widget.floatMouseZoom(&x,&y,d->zoom);
  rlSpreadsheetRow *row = widget.hitTest(x,y,&d->widgetTable,&irow);
  if(debugme) printf("slotMousePressedEvent: x=%f y=%f row=%ld irow=%d\n", x, y, (long int) row, irow);
  if(debugme && row!=NULL) printf("name=%s text=%s\n", row->text(pvCairoWidget::colName), row->text(pvCairoWidget::colText));
  return 0;
}

static int slotMouseReleasedEvent(PARAM *p, int id, DATA *d, float x, float y)
{
  if(p == NULL || id == 0 || d == NULL || x < -1000 || y < -1000) return -1;
  pvCairoWidget widget;
  int irow = -1;
  widget.floatMouseZoom(&x,&y,d->zoom);
  rlSpreadsheetRow *row = widget.hitTest(x,y,&d->widgetTable,&irow);
  if(irow > 0) pvStatusMessage(p,0,255,0,"%s %s row=%d", row->text(pvCairoWidget::colName), row->text(pvCairoWidget::colText), irow);
  if(debugme) printf("slotMouseReleasedEvent: x=%f y=%f row=%ld irow=%d\n", x, y, (long int) row, irow);
  if(debugme && row!=NULL) printf("name=%s text=%s\n", row->text(pvCairoWidget::colName), row->text(pvCairoWidget::colText));
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
