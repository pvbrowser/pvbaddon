//###############################################################
//# mask1_slots.h for ProcessViewServer created: Mo. Nov. 27 08:56:13 2017
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

const int width  = 1280;
const int height = 1024;
const int SCR_HEIGHT = 60;

const char files[][32] = {
  "buddyinfo",
  "cgroups",
  "cmdline",
  "consoles",
  "cpuinfo",
  "crypto",
  "devices",
  "diskstats",
  "dma",
  "execdomains",
  "fb",
  "filesystems",
  "i8k",
  "interrupts",
  "iomem",
  "ioports",
  "kallsyms",
  "keys",
  "key-users",
  "loadavg",
  "locks",
  "meminfo",
  "misc",
  "modules",
  "pagetypeinfo",
  "partitions",
  "sched_debug",
  "schedstat",
  "softirqs",
  "stat",
  "swaps",
  "timer_list",
  "uptime",
  "version",
  "vmstat",
  "zoneinfo",
  ""
  };


typedef struct // (todo: define your data structure here)
{
  rlSpreadsheetTable widgetTable;
  int i_infofile, count_infofile, istart_infofile, zoom;
}
DATA;

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
    if(isEqual(name,"Diagram")) // example for using further non standard widgets
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

static int drawInfo(cairo_t *cr, DATA *d)
{
  if(cr==NULL || d==NULL) return -1;
  double x,y,dx,dy;
  dx=10.0; dy=14.0;
  char line[1024], *cptr;
  char filename[256];
  sprintf(filename,"/proc/%s", files[d->i_infofile]);
  FILE *fin = fopen(filename,"r");
  if(fin==NULL)
  {
    printf("could not read %s\n", filename);
    return -1;
  }
  int iline = 0;
  x = dx; y=dy;
  sprintf(line,"### /proc/%s (%d:%d) ###", files[d->i_infofile], d->i_infofile, d->istart_infofile);
  pvCairoWidget::drawText(cr,x,y,line);
  y += dy;
  y += dy;
  y += dy;
  while(fgets(line,sizeof(line)-1,fin) != NULL)
  {
    cptr = strchr(line,'\n');
    if(cptr != NULL) *cptr = '\0';
    if(iline >= d->istart_infofile)
    {
      pvCairoWidget::drawText(cr,x,y,line);
      y += dy;
    }
    iline++;
    if(iline - d->istart_infofile > SCR_HEIGHT) break;
  }
  fclose(fin);
  return 0;
}

static int drawCairo(PARAM *p, DATA *d, pvCairo::surfaceToUse surface=pvCairo::SVG_QDraw, const char *surface_file=NULL)
{
  if(p==NULL || d==NULL) return -1;
  pvCairo cairo;
  pvCairoWidget cw;
  cairo.setSurfaceToUse(surface,surface_file);
  //cairo.setSurfaceToUse(pvCairo::SVG_file,"test.svg");
  cairo_t *cr = cairo.beginDraw(p,draw1,width,height);

  // draw info
  cairo_set_font_size(cr, 14);
  cairo_select_font_face(cr, "Courier",
      CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
  cairo_set_source_rgb(cr, 0, 0, 0);
  drawInfo(cr,d);
  cairo_select_font_face(cr, "Arial",
      CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);

  rlSpreadsheetRow *row = d->widgetTable.getFirstRow();
  while(row != NULL)
  {
    drawWidget(cr,&cw,row);
    row = row->getNextRow();
  }

  cairo.endDraw(p);
  return 0;
}

static int init(DATA *d)
{
  if(d == NULL) return -1;
  //memset(d,0,sizeof(DATA));
  d->i_infofile = 21;
  d->count_infofile = 0;
  d->istart_infofile = 0;
  while(files[d->count_infofile][0] > ' ') d->count_infofile++;
  d->zoom = 100;
  d->widgetTable.read("widgetTable.csv");
  return 0;
}

static int slotInit(PARAM *p, DATA *d)
{
  if(p == NULL || d == NULL) return -1;
  init(d);
  pvResize(p,0,width,height);
  return 0;
}

static int slotNullEvent(PARAM *p, DATA *d)
{
  if(p == NULL || d == NULL) return -1;
  drawCairo(p,d);
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
  if(modifier == -1)
  {
  }
  else if(val == Key_F5)
  {
    if(d->i_infofile > 0) d->i_infofile--;
    d->istart_infofile = 0;
    drawCairo(p,d);
  }
  else if(val == Key_F8)
  {
    if(d->i_infofile < d->count_infofile) d->i_infofile++;
    d->istart_infofile = 0;
    drawCairo(p,d);
  }
  else if(val == Key_F6)
  {
    d->istart_infofile += 5;
    drawCairo(p,d);
  }
  else if(val == Key_F7)
  {
    if(d->istart_infofile >= 5) d->istart_infofile -= 5;
    drawCairo(p,d);
  }
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
    int where = 0;
    pvCairoWidget::floatMouseZoom(&x,&y,d->zoom);
    rlSpreadsheetRow *row = pvCairoWidget::hitTest(x,y,&d->widgetTable,&where);
    if(row != NULL)
    {
      pvSetMouseShape(p,PointingHandCursor);
      const char *wid  = row->text(pvCairoWidget::colId);
      const char *name = row->text(pvCairoWidget::colName);
      const char *text = row->text(pvCairoWidget::colText);
      pvStatusMessage(p,255,255,255,"%s %s button=%d", name, text, p->button);
      if     (isEqual(wid,"idBack"))
      {
        if(d->i_infofile > 0) d->i_infofile--;
        d->istart_infofile = 0;
        drawCairo(p,d);
      }
      else if(isEqual(wid,"idForward"))
      {
        if(d->i_infofile < d->count_infofile) d->i_infofile++;
        d->istart_infofile = 0;
        drawCairo(p,d);
      }
      else if(isEqual(wid,"idUp"))
      {
        d->istart_infofile += 5;
        drawCairo(p,d);
      }
      else if(isEqual(wid,"idDown"))
      {
        if(d->istart_infofile >= 5) d->istart_infofile -= 5;
        drawCairo(p,d);
      }
    }
  }
  return 0;
}

static int slotMouseReleasedEvent(PARAM *p, int id, DATA *d, float x, float y)
{
  if(p == NULL || id == 0 || d == NULL || x < -1000 || y < -1000) return -1;
  if(id == draw1) 
  {
    pvSetMouseShape(p,ArrowCursor);
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
