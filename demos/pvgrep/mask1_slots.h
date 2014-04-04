//###############################################################
//# mask1_slots.h for ProcessViewServer created: Di. Dez 1 09:00:37 2009
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

#include "rlspawn.h"
#include "rlstring.h"

typedef struct // (todo: define your data structure here)
{
  rlSpawn spawn;
  char pattern[1024];
}
DATA;

static int htmlOut(FILE *fout, const char *line)
{
  if(fout == NULL || line == NULL) return -1;
  const char *cptr,*cptr2;
  cptr = strchr(line,':');
  if(cptr == NULL) return -1;
  cptr++;
  if(trace) printf("line=%s\n", cptr);
  fprintf(fout,"<hr>\n<p>");
  while(*cptr != '\0')
  {
    if(
      strncmp(cptr,"pv://",5)    == 0 ||
      strncmp(cptr,"pvssh://",8) == 0 ||
      strncmp(cptr,"http://",7)  == 0
      )
    {
      cptr2 = cptr;
      fprintf(fout,"<a href=\"");
      while(*cptr != '\0' && *cptr != '\n' && *cptr != ' ' && *cptr != '\t') fputc(*cptr++,fout);
      fprintf(fout,"\">");
      while(*cptr2 != '\0' && *cptr2 != '\n' && *cptr2 != ' ' && *cptr2 != '\t') fputc(*cptr2++,fout);
      fprintf(fout,"</a>");
    }
    else
    {
      fputc(*cptr++, fout);
    }
  }
  fprintf(fout,"</p>\n");
  return 0;
}

static int slotInit(PARAM *p, DATA *d)
{
  if(p == NULL || d == NULL) return -1;
  //memset(d,0,sizeof(DATA));
  strcpy(d->pattern,"");
  pvDownloadFile(p,"homer.jpg");
  pvDownloadFile(p,"pvgrep.css");
  pvDownloadFile(p,"index.html");
  pvDownloadFile(p,"favorites.html");
  pvSetSource(p,htmlBottom,"favorites.html");
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
  if(id == lineEditSearch || id == buttonSearch)
  {
    char command[sizeof(d->pattern) + 80];
    const char *cptr;
    rlString filename;
    sprintf(command,"grep -iR %s directory", d->pattern);
    d->spawn.spawn(command);
    filename.printf("%sfound.html", p->file_prefix);
    FILE *fout = fopen(filename.text(),"w");
    if(fout != NULL)
    {
      fprintf(fout,"<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\">\n");
      fprintf(fout,"<html>\n");
      fprintf(fout,"<head>\n");
      fprintf(fout,"<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />\n");
      fprintf(fout,"<link rel=\"stylesheet\" type=\"text/css\" href=\"pvgrep.css\">\n");
      fprintf(fout,"<title>pvgrep results</title>\n");
      fprintf(fout,"</head>\n");
      fprintf(fout,"<body>\n");
      fprintf(fout,"<h1><img src=\"homer.jpg\">pvgrep found</h1>\n");
      while((cptr = d->spawn.readLine()) != NULL)
      {
        htmlOut(fout,cptr);
        //fprintf(fout,"%s", cptr);
      }
      fprintf(fout,"</body>\n");
      fprintf(fout,"</html>");
      fclose(fout);
      pvDownloadFileAs(p,filename.text(),"pvgrep.html");
      pvSetSource(p,htmlBottom,"pvgrep.html");
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
  if(id == lineEditSearch)
  {
    if(strlen(text) < (sizeof(d->pattern) - 1)) strcpy(d->pattern, text);
  }
  else if(id == htmlBottom)
  {
    if(
       strncmp(text,"pv://",5)    == 0 || 
       strncmp(text,"pvssh://",8) == 0 ||
       strncmp(text,"http://",7)  == 0 ||
       strncmp(text,"https://",8) == 0 )
    {
      pvHyperlink(p,text);
    }
  }
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
