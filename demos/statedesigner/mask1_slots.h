//###############################################################
//# mask1_slots.h for ProcessViewServer created: Mo. Dez 31 09:24:35 2012
//# please fill out these slots
//# here you find all possible events
//# Yours: Lehrig Software Engineering
//###############################################################

// todo: uncomment me if you want to use this data aquisiton
// also uncomment this classes in main.cpp and pvapp.h
// also remember to uncomment rllib in the project file
//extern rlModbusClient     modbus;
//extern rlSiemensTCPClient siemensTCP;
//extern rlPPIClient        ppi;
#include "rlcutil.h"
#include "rlstring.h"
#include "rlfileload.h"
#include "rlsvganimator.h"
extern char file[];

typedef struct // (todo: define your data structure here)
{
  rlSvgAnimator ani;
}
DATA;

static void drawSVG(PARAM *p, DATA *d, int id)
{
printf("Render\n");
  gBeginDraw(p,id);
  d->ani.writeSocket();
  gEndDraw(p);
}

static int slotInit(PARAM *p, DATA *d)
{
  if(p == NULL || d == NULL) return -1;
  rlFileLoad rlfl;
  rlString filename(file);
  filename += ".dot";
  rlfl.load(filename.text());
  pvClear(p,edit);
  const char *line = rlfl.firstLine();
  while(line != NULL)
  {
    pvSetText(p,edit,line);
    line = rlfl.nextLine();
  }
  rlString svgfilename(file);
  svgfilename += ".svg";
  rlString cmd;
  cmd.printf("dot -Tsvg %s -o %s", filename.text(), svgfilename.text());
  system(cmd.text());
  d->ani.setSocket(&p->s);
  d->ani.setId(svgview);
  d->ani.setMainObject("graph1");
  d->ani.read(svgfilename.text());
  pvSetZoomX(p, svgview, -1.0f);
  pvSetZoomY(p, svgview, -1.0f);
  drawSVG(p,d,svgview);
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
  if(id == update) 
  {
    pvText(p,edit);
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
  if(id == edit)
  {
    rlString filename(file);
    rlString svgfilename(file);
    filename += ".dot";
    svgfilename += ".svg";
    FILE *fout = fopen(filename.text(),"w");
    if(fout == NULL)
    {
      pvBeep(p);
      pvStatusMessage(p,255,0,0,"could not write DOT file");
      return 0;
    }
    fprintf(fout,"%s",p->clipboard);
    fclose(fout);
    rlString cmd;
    cmd.printf("dot -Tsvg %s -o %s", filename.text(), svgfilename.text());
    system(cmd.text());
    d->ani.read(svgfilename.text());
    drawSVG(p,d,svgview);
  }
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
  if(id == svgview) // the SVG
  {
    d->ani.moveMainObject(x,y);
    drawSVG(p,d,svgview);
    d->ani.setMouseXY0(x,y);
  }
  return 0;
}

static int slotMousePressedEvent(PARAM *p, int id, DATA *d, float x, float y)
{
  if(p == NULL || id == 0 || d == NULL || x < -1000 || y < -1000) return -1;
  if(id == svgview) // the SVG
  {
    // remember initial position for dragging
    d->ani.setMouseXY0(x,y);
  }
  return 0;
}

static int slotMouseReleasedEvent(PARAM *p, int id, DATA *d, float x, float y)
{
  if(p == NULL || id == 0 || d == NULL || x < -1000 || y < -1000) return -1;
  if(id == svgview) // the SVG
  {
    // drag the SVG with your mouse
    d->ani.moveMainObject(x,y);
    drawSVG(p,d,svgview);
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
