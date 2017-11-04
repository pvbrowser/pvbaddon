//###############################################################
//# mask2_slots.h for ProcessViewServer created: Do. Okt. 26 13:11:23 2017
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

typedef struct // (todo: define your data structure here)
{
  rlSpreadsheetTable widgetTable;
  rlSpreadsheetRow *diagram1, *check1;
  int width_svg, height_svg, zoom;
}
DATA;

static int findWidgets(DATA *d)
{
  d->diagram1 = NULL;
  d->check1 = NULL;
  rlSpreadsheetRow *row = d->widgetTable.getFirstRow();
  while(row != NULL)
  {
    const char *name = row->text(pvCairoWidget::colName); 
    const char *text = row->text(pvCairoWidget::colText); 
    if(strcmp(name,"Diagram") == 0 && strcmp(text,"Welt") == 0)
    {
      d->diagram1 = row;
    }
    else if(strcmp(name,"CheckBox") == 0)
    {
      d->check1 = row;
    }
    row = row->getNextRow();
  }
  return 0;
}

static int slotInit(PARAM *p, DATA *d)
{
  if(p == NULL || d == NULL) return -1;
  //memset(d,0,sizeof(DATA));
  d->width_svg = 1280;
  d->height_svg = 1024;
  d->zoom = 100;
  pvSetBufferTransparency(p,svg1,BUFFER_TRANSPARENCY);
  d->widgetTable.read(mask1WidgetTableCSV);
  drawMask1Widgets(p,svg1,&d->widgetTable,d->width_svg,d->height_svg);
  findWidgets(d);
  return 0;
}

static int slotNullEvent(PARAM *p, DATA *d)
{
  if(p == NULL || d == NULL) return -1;
  pvCairoWidget cw;
  drawMask1Widgets(p,svg1,&d->widgetTable,d->width_svg,d->height_svg);
  if(d->diagram1 != NULL)
  {
    int x,y,w,h;
    const char *xywh = d->diagram1->text(pvCairoWidget::colXYWH);
    cw.getXYWH(xywh,&x,&y,&w,&h);
    x += 5;
    if(x > 400) x=100;
    cw.move(d->diagram1,x,y);
    h += 5;
    if(h > 400) h=100;
    cw.resize(d->diagram1,w,h);
  }
  return 0;
}

static int slotButtonEvent(PARAM *p, int id, DATA *d)
{
  if(p == NULL || id == 0 || d == NULL) return -1;
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
  if(id == svg1)
  {
    d->zoom = val;
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
  if(id == svg1) printf("slotGlResize(%d,%d)\n", width, height);
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
  return 0;
}

static int slotMousePressedEvent(PARAM *p, int id, DATA *d, float x, float y)
{
  if(p == NULL || id == 0 || d == NULL || x < -1000 || y < -1000) return -1;
  if(id == svg1)
  {
    pvCairoWidget widget;
    int irow = -1;
    widget.floatMouseZoom(&x,&y,d->zoom);
    rlSpreadsheetRow *row = widget.hitTest(x,y,&d->widgetTable,&irow);
    if(irow > 0) 
    {
      pvSetMouseShape(p,PointingHandCursor);
      const char *name = row->text(pvCairoWidget::colName);
      const char *text = row->text(pvCairoWidget::colText);
      pvStatusMessage(p,255,255,255,"%s %s row=%d button=%d", name, text, irow, p->button);
      if(strcmp(name,"CheckBox") == 0)
      {
        if(strncmp(text,"[#]",3) == 0) widget.setChecked(row,"[ ]"); 
        else                           widget.setChecked(row,"[#]");
      }
      else if(strcmp(name,"RadioButton") == 0)
      {
        if(strncmp(text,"(*)",3) == 0) widget.setChecked(row,"( )"); 
        else                           widget.setChecked(row,"(*)");
      }
    }
  }
  return 0;
}

static int slotMouseReleasedEvent(PARAM *p, int id, DATA *d, float x, float y)
{
  if(p == NULL || id == 0 || d == NULL || x < -1000 || y < -1000) return -1;
  pvCairoWidget widget;
  int irow = -1;
  widget.floatMouseZoom(&x,&y,d->zoom);
  rlSpreadsheetRow *row = widget.hitTest(x,y,&d->widgetTable,&irow);
  if(row != NULL && irow > 0)
  {
    pvSetMouseShape(p,ArrowCursor);
    pvStatusMessage(p,0,255,0,"");
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
