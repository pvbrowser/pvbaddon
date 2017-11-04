//###############################################################
//# mask1_slots.h for ProcessViewServer created: Sa. Dez. 31 12:35:10 2016
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
#include <math.h>
#include "rlsvgvdi.h"
#define PI 3.1414f
static rlString header("<html><head><meta http-equiv=\"refresh\" content=\"1;\"></head><body>");
static rlString trailer("</body></html>");

typedef struct // (todo: define your data structure here)
{
  int i, slide, murx;
}
DATA;

int draw(PARAM *p, DATA *d)
{
  int fontsize = 12;
  int i;
  float x1[100], sin_x[100];
  float x2[100], cos_x[100];
  int ix[16], iy[16];
  rlSvgVdi vdi;
  rlString svg;
  d->slide++;
  int slide = d->slide;

  printf("slide=%d\n", slide);
  for(i=0;i<100;i++)
  {
    float fslide = ((float) slide) / 10.0f;
    float val = ((float) i) / 16.0f;
    x1[i] = val; sin_x[i]= (float) sin(val+fslide);
    x2[i] = val; cos_x[i]= (float) cos(val-fslide);
  }
  ix[0] = 10; iy[0] = 10;
  ix[1] = 20; iy[1] = 10;
  ix[2] = 20; iy[2] = 30;

  if(strncmp(p->url,"ws",2) != 0)
  {
    if(vdi.setOutput(&p->s, drawWidget1) < 0)
    {
      pvThreadFatal(p,"connection lost, could not vdi.setOutput");
    }
  }

  //svg  = "<!-- my svg -->\n";
  svg = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n";
  svg += vdi.svgHeader(1280,1024,200,200,200);
  //svg += vdi.svg_printf("<g\nid=\"PV.my_diagram\"\ntransform=\"rotate(-5)\">\n");
  svg += vdi.setWidth(3);
  svg += vdi.setColor(0,0,0);
  svg += vdi.setFont("Courier",fontsize,0,0);
  svg += vdi.boxWithText(100,100,1024,800, fontsize, "x/radiant", "sin(x), cos(x)", "right label");
  svg += vdi.xAxis(0,1.0f,2.0f*PI);
  svg += vdi.yAxis(-1.5f,0.5f,1.5f);
  svg += vdi.textInAxis(0.0f,1.0f,"text in axis", ALIGN_LEFT);
  svg += vdi.setLinestyle("5,5");
  svg += vdi.xGrid();
  svg += vdi.yGrid();
  if(d->murx == 0) svg += vdi.setWidth(1);
  else             svg += vdi.setWidth(7);
  svg += vdi.setLinestyle("");
  svg += vdi.setColor(255,0,0);
  svg += vdi.line(x1, sin_x, 100, LINESTYLE_RECT);
  svg += vdi.setColor(0,255,0);
  svg += vdi.line(x2, cos_x, 100, LINESTYLE_CROSS);
  svg += vdi.setWidth(1);
  svg += vdi.setColor(0,0,0);
  svg += vdi.rightYAxis(-2.5f,0.5f,2.5f);
  fontsize = 24;
  svg += vdi.setColor(0,0,255);
  svg += vdi.setFont("Times", fontsize, 1, 0);
  svg += vdi.text(50, 50, "This is a Diagram", ALIGN_LEFT);
  svg += vdi.svg_printf("<path ");
  svg += vdi.svg_d(ix,iy,3);
  svg += vdi.svg_printf("fill=\"blue\" stroke=\"#ff0000\" stroke-width=\"1\" />\n");
  //svg += vdi.comment("end of my diagram (a comment)");
  //svg += vdi.svg_printf("</g>\n");
  svg += vdi.svgTrailer();
  if(strncmp(p->url,"ws",2) != 0)
  {
    if(vdi.endOutput() < 0)
    {
      pvThreadFatal(p,"connection lost");
    }
  }
  else
  {
    pvSetText(p,123,svg.text());
  }
  return 0;
}

static int slotInit(PARAM *p, DATA *d)
{
  if(p == NULL || d == NULL) return -1;
  d->i = 0;
  d->slide = 0;
  d->murx = 0;
  //memset(d,0,sizeof(DATA));
  //pvDownloadFile(p,"main.cpp");
  pvPrintf(p,0,"Hallo Welt");
  //rlString svg;
  //svg.read("test3.svg");
  //printf("svg.text()=\n%s\n", svg.text());
  //pvSetText(p,123,svg.text());
  draw(p,d);
  return 0;
}

static int slotNullEvent(PARAM *p, DATA *d)
{
  if(p == NULL || d == NULL) return -1;
  pvPrintf(p,0,"we are within slotNullEvent");
  draw(p,d);
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
  if(p == NULL || id < -1000 || d == NULL || text == NULL) return -1;
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
