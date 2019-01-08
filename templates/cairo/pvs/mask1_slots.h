//###############################################################
//# mask1_slots.h for ProcessViewServer created: Mo. Nov. 6 08:41:58 2017
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

extern rlThread tloop;
extern rlFifo   loopfifo;
extern int surface;
extern char surface_filename[];

typedef struct // (todo: define your data structure here)
{
  pvCairo cairo;
  rlTime ftime;
  rlSpreadsheetTable widgetTable;
  int zoom;
}
DATA;

static int slotInit(PARAM *p, DATA *d)
{
  if(p == NULL || d == NULL) return -1;
  //memset(d,0,sizeof(DATA));
  d->ftime.getLocalTime();
  d->zoom = 100;
  pvSetBufferTransparency(p,draw1,BUFFER_TRANSPARENCY);
  d->widgetTable.read(WidgetTableCSV);
  return 0;
}

static int slotNullEvent(PARAM *p, DATA *d)
{
  if(p == NULL || d == NULL) return -1;
  char sfilename[256],dfilename[256];
  strcpy(sfilename,surface_filename);
  sprintf(dfilename,"PVTMP%d_%s",p->s,sfilename);
  rlTime t;
  tloop.lock(); // lock/unlock the file copy operation
  t.getFileModificationTime(sfilename);
  if(t == d->ftime)
  {
    tloop.unlock();
    printf("no update necessary\n");
  }
  else
  {
    helperFilecopy(sfilename,dfilename);
    tloop.unlock();
    printf("update\n");
    d->cairo.sendFileToQDraw(p,draw1,dfilename,&d->ftime);
    unlink(dfilename);
  }
  d->ftime = t;
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
  if(id == draw1)
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
  if(id == draw1)
  {
    int irow = -1;
    pvCairoWidget::floatMouseZoom(&x,&y,d->zoom);
    rlSpreadsheetRow *row = pvCairoWidget::hitTest(x,y,&d->widgetTable,&irow);
    loopfifo.printf("onmouse=%d&x=%d&y=%d&button=%d&alt=%d&shift=%d&ctrl=%d", 1, (int)x, (int)y, p->button, 0, 0, 0);
    if(irow > 0)
    {
      pvSetMouseShape(p,PointingHandCursor);
      pvStatusMessage(p,0,255,0,"%s/%s", row->text(pvCairoWidget::colText), row->text(pvCairoWidget::colName));
    }
  }
  return 0;
}

static int slotMouseReleasedEvent(PARAM *p, int id, DATA *d, float x, float y)
{
  if(p == NULL || id == 0 || d == NULL || x < -1000 || y < -1000) return -1;
  if(id == draw1)
  {
    int irow = -1;
    pvCairoWidget::floatMouseZoom(&x,&y,d->zoom);
    loopfifo.printf("onmouse=%d&x=%d&y=%d&button=%d&alt=%d&shift=%d&ctrl=%d", 0, (int)x, (int)y, p->button, 0, 0, 0);
    rlSpreadsheetRow *row = pvCairoWidget::hitTest(x,y,&d->widgetTable,&irow);
    if(row != NULL && irow > 0)
    {
      pvSetMouseShape(p,ArrowCursor);
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
