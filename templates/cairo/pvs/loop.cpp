//###############################################################
//# loop.cpp for ProcessViewServer created: Mi. Okt. 25 12:37:48 2017
//# Yours: Lehrig Software Engineering
//###############################################################
#include "pvapp.h"

static int  debugme = trace;

extern int  surface;
extern char surface_filename[];
char last_cmd[MAX_PRINTF_LENGTH+1] = "last_cmd";
char last_hit[MAX_PRINTF_LENGTH+1] = "last_hit";

int use_mailbox = 1;
int use_fifo = 1;

rlMailbox loopmbx(LOOPMBX);
rlFifo    loopfifo;

static int drawWidget(cairo_t *cr, rlSpreadsheetRow *widget)
{ // draw one of our custom widgets
  int x,y,w,h;
  pvCairoWidget cw;
  const char *xywh = widget->text(pvCairoWidget::colXYWH);
  if(cw.isXYWH(xywh))
  {
    cw.getXYWH(xywh,&x,&y,&w,&h);
    const char *name   = widget->text(pvCairoWidget::colName);
    const char *text   = widget->text(pvCairoWidget::colText);
    const char *values = widget->text(pvCairoWidget::colValues);
    if(strcmp(name,"Box")==0)
    {
      if(debugme) printf("drawBox %s \"%s\" %s\n", xywh, text, values);
      cw.drawFilledRect(cr,widget);
      cw.drawText(cr,widget);
    }
    else if(strcmp(name,"Button")==0)
    {
      if(debugme) printf("drawButton %s \"%s\" %s\n", xywh, text, values);
      cw.drawFilledRect(cr,widget);
      cw.drawRect(cr,widget);
      cw.drawText(cr,widget);
    }
    else if(strcmp(name,"CheckBox")==0)
    {
      if(debugme) printf("drawCheckBox %s \"%s\" %s\n", xywh, text, values);
      cw.drawFilledRect(cr,widget);
      cw.drawText(cr,widget);
      cw.drawRect(cr,widget);
    }
    else if(strcmp(name,"Label")==0)
    {
      if(debugme) printf("drawLabel %s \"%s\" %s\n", xywh, text, values);
      cw.drawFilledRect(cr,widget);
      cw.drawText(cr,widget);
    }
    else if(strcmp(name,"RadioButton")==0)
    {
      if(debugme) printf("drawRadioButton %s \"%s\" %s\n", xywh, text, values);
      cw.drawFilledRect(cr,widget);
      cw.drawText(cr,widget,1,0,0);
    }
    else if(strcmp(name,"Slider")==0)
    {
      if(debugme) printf("(not implemented yet) drawSlider %s \"%s\" %s\n", xywh, text, values);
      cw.drawFilledRect(cr,widget);
      cw.drawText(cr,widget);
    }
    else if(strcmp(name,"Diagram")==0)
    {
      if(debugme) printf("(example for a more complex widget) %s \"%s\" %s\n", xywh, text, values);
      cw.drawFilledRect(cr,widget);
      cw.drawText(cr,widget);
      pvCairoTestDiagram(cr,x,y,w,h);
      cairo_set_font_size (cr, 14);
      cairo_select_font_face (cr, "Arial",
          CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
      cairo_move_to(cr, 520, 10);
      rlTime now;
      now.getLocalTime();
      cairo_show_text(cr, now.getIsoTimeString());
    }
    else if(strcmp(name,"PNG")==0)
    {
      if(debugme) printf("(example for a PNG) %s \"%s\" %s\n", xywh, text, values);
      cw.drawPNG(cr,widget);
    }
    else if(name[0] != '\0')
    {
      if(debugme) printf("drawElse %s \"%s\" %s\n", xywh, text, values);
      //cw.drawFilledRect(cr,widget);
      cw.drawText(cr,widget);
    }
  }
  return 0;
}

int drawMask1Widgets(PARAM *p, int id, rlSpreadsheetTable *t, int width, int height)
{ // draw all designed widgets on top of backround
  pvCairo cairo;
  cairo.setSurfaceToUse((pvCairo::surfaceToUse) surface, surface_filename); // surface was set from p->url within main.cpp
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
    drawWidget(cr,row);
    row = row->getNextRow();
  }

  cairo_move_to(cr, 220, 500);
  cairo_show_text(cr, last_cmd);
  cairo_move_to(cr, 220, 520);
  cairo_show_text(cr, last_hit);

  cairo.endDraw(p);
  return 0;
}

static int interpret(const char *cmd, rlSpreadsheetTable *t)
{
  printf("interpret cmd=%s\n", cmd);
  strcpy(last_cmd, cmd);
  if(strncmp(cmd,"onmouse=",8) == 0)
  { // cmd as was send from maskX_slots or from httpd
    int onmouse,x,y,button,alt,shift,ctrl;
    sscanf(cmd, "onmouse=%d&x=%d&y=%d&button=%d&alt=%d&shift=%d&ctrl=%d",&onmouse,&x,&y,&button,&alt,&shift,&ctrl);
    int irow = -1;
    rlSpreadsheetRow *row = pvCairoWidget::hitTest(x,y,t,&irow);
    if(onmouse==1 && irow > 0)
    {
      printf("loop rtest %s %s\n", row->text(pvCairoWidget::colName),
                                   row->text(pvCairoWidget::colText));
      const char *name = row->text(pvCairoWidget::colName);
      if(strcmp(name,"CheckBox") == 0)
      {
        if(pvCairoWidget::isChecked(row)) pvCairoWidget::setChecked(row,0);
        else                              pvCairoWidget::setChecked(row,1);
      }
      else if(strcmp(name,"RadioButton") == 0)
      {
        if(pvCairoWidget::isChecked(row)) pvCairoWidget::setChecked(row,0);
        else                              pvCairoWidget::setChecked(row,1);
      }
      sprintf(last_hit,"%s/%s", row->text(pvCairoWidget::colName), row->text(pvCairoWidget::colText));
    }
  }
  return 0;
}

void *loop(void *arg)
{ // thread function
  THREAD_PARAM *tp = (THREAD_PARAM *) arg;
  // YOUR_DATA    *d = (YOUR_DATA *) tp->user;
  char cmd[1024];
  int ret;

  debugme = 0;
  rlSpreadsheetTable widget_table;
  widget_table.read(WidgetTableCSV);
  while(1)
  {
    for(int waitcount=0; waitcount<10; waitcount++)
    {
      if(use_mailbox)
      {
        do
        {
          ret = loopmbx.read(cmd, sizeof(cmd)-1, rlMailbox::NOWAIT);
          if(ret>0) interpret(cmd, &widget_table);
        } while(ret > 0);
      }
      if(use_fifo)
      {
        while(loopfifo.poll() == rlFifo::DATA_AVAILABLE)
        {
          ret = loopfifo.read(cmd,sizeof(cmd)-1);
          if(ret>0) interpret(cmd, &widget_table);
        }
      }
      rlsleep(100);
    }
    tp->thread->lock();
    // do something critical
    drawMask1Widgets(NULL,0,&widget_table,1280,1024); // draw widgets on PNG or SVG
    tp->thread->unlock();
  }
  return arg;
}

