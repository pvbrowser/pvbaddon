//###############################################################
//# loop.cpp for ProcessViewServer created: Mi. Okt. 25 12:37:48 2017
//# Yours: Lehrig Software Engineering
//###############################################################
#include "pvapp.h"
extern rlThread tloop;
extern rlFifo loopfifo;
#include "httpdhelper.h"

int draw1(PARAM *p)
{
printf("httpd: draw1 begin p->url=%s\n", p->url);
//tloop.lock();
  pvCairo cairo;
  cairo.debug = 0;
  cairo.setSurfaceToUse(pvCairo::PNG_httpresponse);
  //cairo.setSurfaceToUse(pvCairo::PNG_file,PNG_FILENAME1);
  cairo_t *cr = cairo.beginDraw(p,0,900.0,665.0);

  static int cnt=0; // test counter dummy
  cairo_pattern_t *pattern;
  int x,y;
  char buf[256];

  /* Draw the squares in the background */
  for (x=0; x<10; x++)
    for (y=0; y<10; y++)
      cairo_rectangle(cr, x*10.0, y*10.0, 5, 5);

  pattern = cairo_pattern_create_radial(50, 50, 5, 50, 50, 50);
  cairo_pattern_add_color_stop_rgb(pattern, 0, 0.75, 0.15, 0.99);
  cairo_pattern_add_color_stop_rgb(pattern, 0.9, 1, 1, 1);
  cairo_set_source(cr, pattern);
  cairo_fill(cr);

  /* Writing in the foreground */
  cairo_set_font_size (cr, 15);
  cairo_select_font_face (cr, "Georgia",
      CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
  cairo_set_source_rgb (cr, 0, 0, 0);
  cairo_move_to(cr, 10, 25);
  cairo_show_text(cr, "Hallo");
  cairo_move_to(cr, 10, 75);
  cairo_show_text(cr, "Wikipedia!");
  cairo_move_to(cr, 10, 95);
  sprintf(buf,"cnt=%d",cnt++);
  cairo_show_text(cr, buf);
  cairo.endDraw(p);
//tloop.unlock();
printf("httpd: draw1 end\n");
  return 0;
}
        
int runHttpServer(PARAM *p)
{
  rlTime t;
  char buf[MAX_EVENT_LENGTH];
  int upgrade = 0;
  int first = 1;

  while(1) // while connection is alive
  {
    if(first == 1) strcpy(buf,p->url);
    else           pvtcpreceive(p,buf, sizeof(buf) -1);
    first = 0;
    if(1) printf("httpd while1 buf=%s\n", buf);
    if(strncmp(buf,"GET ",4) == 0)
    {
      rlString filename, parameters;
      helperParseUrl(buf,&filename,&parameters);
      while(1) // read the http header that follows the http url 
      {
        pvtcpreceive(p,buf, sizeof(buf) -1);
        if(trace) printf("httpd while2 buf=%s\n", buf);
        if(strncmp(buf,"Upgrade:",8) == 0) upgrade = 1;
        if(strlen(buf) < 3) break;
      }
      if(upgrade) return 1;

      const char *cfilename = filename.text();
      const char *para = parameters.text();
      
      // respond to http GET request
      if(strstr(para,"=") != NULL && strncmp(para,"cnt=",3) != 0)
      {
        loopfifo.printf("%s", para); // send to interpreter which is located in loop thread
        helperSendAccepted(p);       // tell the browser that we accepted the request
      }
      else if(strcmp(cfilename,PNG_FILENAME1) == 0)
      {
        helperPerhapsSendHttpResponseFile(p, PNG_FILENAME1, &t); // update if file_modification_time changes
      }
      else if(strcmp(cfilename,SVG_FILENAME1) == 0)
      {
        helperPerhapsSendHttpResponseFile(p, SVG_FILENAME1, &t); // update if file_modification_time changes
      }
       else
      {
        // respond with requested file
        if(trace) printf("suggestion: cfilename=%s place PNG-, SVG-, PVTMP-file within RAMDISK\n", cfilename);
        if     (strstr(cfilename,"svg") != NULL) pvSendHttpResponseFile(p, cfilename, "Content-Type: image/svg+xml");
        else if(strstr(cfilename,"png") != NULL) pvSendHttpResponseFile(p, cfilename, "Content-Type: image/png");
        else if(strstr(cfilename,"jpg") != NULL) pvSendHttpResponseFile(p, cfilename, "Content-Type: image/jpeg");
        else if(strstr(cfilename,"css") != NULL) pvSendHttpResponseFile(p, cfilename, "Content-Type: text/css");
        else                                     pvSendHttpResponseFile(p, cfilename);
      }
    }
  }
  return 0;
}

