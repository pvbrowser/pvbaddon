//###############################################################
//# loop.cpp for ProcessViewServer created: Mi. Okt. 25 12:37:48 2017
//# Yours: Lehrig Software Engineering
//###############################################################
#include "pvapp.h"
const int draw1 = 0; // proxy for pvbrowser widget
#include "mask1_slots.h"
#include "httpdhelper.h"

static int interpret(const char *cmd, DATA *d)
{
  printf("interpret cmd=%s\n", cmd);
  const char *onmouseptr = strstr(cmd,"onmouse=1");
  const char *onkeyptr   = strstr(cmd,"key=");
  if(onmouseptr != NULL)
  {
    int onmouse,x,y,button,alt,shift,ctrl;
    sscanf(onmouseptr, "onmouse=%d&x=%d&y=%d&button=%d&alt=%d&shift=%d&ctrl=%d",&onmouse,&x,&y,&button,&alt,&shift,&ctrl);
    int where = -1;
    rlSpreadsheetRow *row = pvCairoWidget::hitTest(x,y,&d->widgetTable,&where);
    if(row != NULL)
    {
      printf("loop rtest %s %s id=%s\n", row->text(pvCairoWidget::colName),
                                         row->text(pvCairoWidget::colText),
                                         row->text(pvCairoWidget::colId));
      //const char *name = row->text(pvCairoWidget::colName);
      const char *wid  = row->text(pvCairoWidget::colId);
      //pvCairoWidget::floatMouseZoom(&x,&y,d->zoom);
      if     (isEqual(wid,"idBack"))
      {
        if(d->i_infofile > 0) d->i_infofile--;
        d->istart_infofile = 0;
        //drawCairo(p,d);
      }
      else if(isEqual(wid,"idForward"))
      {
        if(d->i_infofile < d->count_infofile) d->i_infofile++;
        d->istart_infofile = 0;
        //drawCairo(p,d);
      }
      else if(isEqual(wid,"idUp"))
      {
        d->istart_infofile += 5;
        //drawCairo(p,d);
      }
      else if(isEqual(wid,"idDown"))
      {
        if(d->istart_infofile >= 5) d->istart_infofile -= 5;
        //drawCairo(p,d);
      }
    }
  }
  if(onkeyptr != NULL)
  {
    int key;
    sscanf(onkeyptr,"key=%d", &key);
    if(key>0) printf("key=dec-%d, char-%c\n",key,key);
    switch(key)
    {
      case 'h':
      case '5':
        if(d->i_infofile > 0) d->i_infofile--;
        d->istart_infofile = 0;
        break;
      case 'j':
      case '6':
        d->istart_infofile += 5;
        break;
      case 'k':
      case '7':
        if(d->istart_infofile >= 5) d->istart_infofile -= 5;
        break;
      case 'l':
      case '8':
        if(d->i_infofile < d->count_infofile) d->i_infofile++;
        d->istart_infofile = 0;
        break;
    }
  }    
  return 0;
}

int runHttpServer(PARAM *p)
{
  DATA d; init(&d);
  rlTime t;
  char buf[MAX_EVENT_LENGTH];
  int upgrade = 0;
  int first = 1;

  while(1) // while connection is alive
  {
    if(first == 1) strcpy(buf,p->url);
    else           pvtcpreceive(p,buf, sizeof(buf) -1);
    first = 0;
    if(strncmp(buf,"GET ",4) == 0)
    {
      rlString filename, parameters;
      helperParseUrl(buf,&filename,&parameters);
      while(1) // read the http header that follows the http url 
      {
        pvtcpreceive(p,buf, sizeof(buf) -1);
        if(strncmp(buf,"Upgrade:",8) == 0) upgrade = 1;
        if(strlen(buf) < 3) break;
      }
      if(upgrade) return 1;

      // respond to http GET request
      const char *cfilename = filename.text();
      const char *para = parameters.text();
      printf("cfilename=%s para=%s\n", cfilename, para); 
      
      interpret(para, &d);
      
      if(strcmp(cfilename,PNG_FILENAME1) == 0)
      {
        drawCairo(p,&d,pvCairo::PNG_httpresponse);
        //drawCairo(p,&d,pvCairo::PNG_file, PNG_FILENAME1);
        //helperPerhapsSendHttpResponseFile(p, PNG_FILENAME1, &t); // update if file_modification_time changes
      }
      else if(strcmp(cfilename,SVG_FILENAME1) == 0)
      {
        drawCairo(p,&d,pvCairo::SVG_httpresponse);
        //drawCairo(p,&d,pvCairo::SVG_file, SVG_FILENAME1);
        //helperSendHttpResponseFile(p, SVG_FILENAME1);
      }
      else
      {
        // respond with requested file 
        if(trace) printf("suggestion: cfilename=%s place PNG-, SVG-, PVTMP-file within RAMDISK\n", cfilename);
        helperSendHttpResponseFile(p, cfilename);
        /*
        if     (strstr(cfilename,"svg") != NULL) pvSendHttpResponseFile(p, cfilename, "Content-Type: image/svg+xml");
        else if(strstr(cfilename,"png") != NULL) pvSendHttpResponseFile(p, cfilename, "Content-Type: image/png");
        else if(strstr(cfilename,"jpg") != NULL) pvSendHttpResponseFile(p, cfilename, "Content-Type: image/jpeg");
        else if(strstr(cfilename,"css") != NULL) pvSendHttpResponseFile(p, cfilename, "Content-Type: text/css");
        else                                     pvSendHttpResponseFile(p, cfilename);
        */
      }
    }
  }
  return 0;
}

