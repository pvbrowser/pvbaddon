////////////////////////////////////////////////////////////////////////////
//
// show_event for ProcessViewServer created: Thu Dec 19 12:51:06 2002
//
////////////////////////////////////////////////////////////////////////////
#include "pvapp.h"
#include "rleventlogserver.h"
#include "rlcutil.h"

extern COMMAND_LINE_SWITCHES switches;

static rlEventLogServer        *event_log_server = NULL;
static rlEventLogServerThreads *event_log_server_threads = NULL;

class OfflineFile
{
  public:
    OfflineFile();
    ~OfflineFile();
    const char *oldest_file();
    const char *next_file();
    const char *myfgets(char *line, int len);
    int find_files();
  private:
    rlSpreadsheetRow files;
    rlTime           file_time;
    FILE             *fp;
};

OfflineFile::OfflineFile()
{
  fp = NULL;
}

OfflineFile::~OfflineFile()
{
  if(fp != NULL) fclose(fp);
  fp = NULL;
}

const char *OfflineFile::oldest_file()
{
  rlTime ftime1(100000) ,ftime2(100000); // year 100000
  int ind;
  const char *cptr;
  static char filename[512];

  if(fp != NULL) fclose(fp);
  fp = NULL;
  file_time.year = 100000;
  filename[0] = '\0';
  ind = 1;
  while(1)
  {
    cptr = files.text(ind++);
    if(*cptr == '#') break;
    ftime1.getFileModificationTime(cptr);
    if(ftime1 < ftime2)
    {
      rlstrncpy(filename,cptr,sizeof(filename)-1);
      ftime2 = ftime1;
    }
  }
  file_time = ftime2;
#ifdef __VMS
  fp = fopen(filename,"r","shr=get");
#else
  fp = fopen(filename,"r");
#endif  
  if(filename[0] == '\0') return NULL;
  return filename;
}

const char *OfflineFile::next_file()
{
  rlTime ftime1(100000) ,ftime2(100000); // year 100000
  int ind;
  const char *cptr;
  static char filename[512];

  filename[0] = '\0';
  ind = 1;
  while(1)
  {
    cptr = files.text(ind++);
    if(*cptr == '#') break;
    ftime1.getFileModificationTime(cptr);
    if(ftime1 < ftime2 && ftime1 > file_time)
    {
      rlstrncpy(filename,cptr,sizeof(filename)-1);
      ftime2 = ftime1;
    }
  }
  file_time = ftime2;
  if(filename[0] == '\0') return NULL;
  return filename;
}

int OfflineFile::find_files()
{
  const char *cptr;
  int context,ind;

  if(fp != NULL) fclose(fp);
  fp = NULL;
  ind = 1;
  context = 0;
#ifdef unix
  while((cptr = rlFindFile(".rlEventLog",&context)) != NULL)
#else
  while((cptr = rlFindFile("*.rlEventLog",&context)) != NULL)
#endif
  {
    files.setText(ind++,cptr);
  }
  files.setText(ind++,"#"); // end of list
  return 0;
}

const char *OfflineFile::myfgets(char *line, int len)
{
  const char *cptr;
  char *cptr2;

  if(fp == NULL)    return NULL;
  cptr = fgets(line,len,fp);
  cptr2 = strchr(line,'\n');
  if(cptr2 != NULL) *cptr2 = '\0';
  if(cptr != NULL)  return cptr;
  fclose(fp);
  fp = NULL;
  cptr = next_file();
  if(cptr == NULL)  return NULL;
#ifdef __VMS
  fp = fopen(cptr,"r","shr=get");
#else
  fp = fopen(cptr,"r");
#endif
  if(fp == NULL)    return NULL;
  cptr = fgets(line,len,fp);
  cptr2 = strchr(line,'\n');
  if(cptr2 != NULL) *cptr2 = '\0';
  if(cptr != NULL)  return cptr;
  fclose(fp);
  fp = NULL;
  return NULL;
}

typedef struct // (todo: define your data structure here)
{
  int    num;
  int    online; // 1=online 2=pause 3=offline
  char   pattern[256];
  char   filter[32];
  char   scroll_down;
  int    font_size;
  int    new_font_size;
  OfflineFile offline_file;
}
DATA;

// _begin_of_generated_area_ (do not edit -> use ui2pvc) -------------------

// our mask contains the following objects
enum {
  ID_MAIN_WIDGET = 0,
  PVMultiLineEdit2,
  groupBox,
  PushButtonBack,
  ButtonGroup1,
  RadioButtonOffline,
  RadioButtonOnline,
  RadioButtonPause,
  GroupBox2,
  LineEditFilter,
  GroupBox1,
  LineEditSearch,
  PushButtonSearch,
  PushButtonScroll,
  GroupBox3,
  SpinBoxFontSize,
  layout1,
  ID_END_OF_WIDGETS
};

  static const char *toolTip[] = {
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  ""};

  static const char *whatsThis[] = {
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  ""};

  static const int widgetType[ID_END_OF_WIDGETS+1] = {
  0,
  TQMultiLineEdit,
  TQGroupBox,
  TQPushButton,
  TQGroupBox,
  TQRadio,
  TQRadio,
  TQRadio,
  TQGroupBox,
  TQLineEdit,
  TQGroupBox,
  TQLineEdit,
  TQPushButton,
  TQPushButton,
  TQGroupBox,
  TQSpinBox,
  -1 };

static int generated_defineMask(PARAM *p)
{
  int w,h,depth;

  if(p == NULL) return 1;
  w = h = depth = strcmp(toolTip[0],whatsThis[0]);
  if(widgetType[0] == -1) return 1;
  if(w==h) depth=0; // fool the compiler
  pvStartDefinition(p,ID_END_OF_WIDGETS);

  pvQMultiLineEdit(p,PVMultiLineEdit2,0,1,33);
  pvSetGeometry(p,PVMultiLineEdit2,180,20,781,591);

  pvQGroupBox(p,groupBox,0,-1,HORIZONTAL,"Event Log");
  pvSetGeometry(p,groupBox,1,10,170,601);
  pvSetMinSize(p,groupBox,170,0);
  pvSetMaxSize(p,groupBox,170,99999);

  pvQPushButton(p,PushButtonBack,groupBox);
  pvSetGeometry(p,PushButtonBack,10,30,151,41);
  pvSetText(p,PushButtonBack,"Back");

  pvQGroupBox(p,ButtonGroup1,groupBox,-1,HORIZONTAL,"Mode");
  pvSetGeometry(p,ButtonGroup1,10,110,150,115);

  pvQRadioButton(p,RadioButtonOffline,ButtonGroup1);
  pvSetGeometry(p,RadioButtonOffline,10,75,131,31);
  pvSetText(p,RadioButtonOffline,"Offline");

  pvQRadioButton(p,RadioButtonOnline,ButtonGroup1);
  pvSetGeometry(p,RadioButtonOnline,10,25,131,31);
  pvSetText(p,RadioButtonOnline,"Online");

  pvQRadioButton(p,RadioButtonPause,ButtonGroup1);
  pvSetGeometry(p,RadioButtonPause,10,55,131,21);
  pvSetText(p,RadioButtonPause,"Pause");

  pvQGroupBox(p,GroupBox2,groupBox,-1,HORIZONTAL,"Filter");
  pvSetGeometry(p,GroupBox2,10,230,151,60);

  pvQLineEdit(p,LineEditFilter,GroupBox2);
  pvSetGeometry(p,LineEditFilter,10,20,130,30);

  pvQGroupBox(p,GroupBox1,groupBox,-1,HORIZONTAL,"OfflineSearch");
  pvSetGeometry(p,GroupBox1,10,300,151,61);

  pvQLineEdit(p,LineEditSearch,GroupBox1);
  pvSetGeometry(p,LineEditSearch,10,20,130,31);

  pvQPushButton(p,PushButtonSearch,groupBox);
  pvSetGeometry(p,PushButtonSearch,10,390,150,40);
  pvSetText(p,PushButtonSearch,"Search");

  pvQPushButton(p,PushButtonScroll,groupBox);
  pvSetGeometry(p,PushButtonScroll,10,440,151,41);
  pvSetText(p,PushButtonScroll,"Scroll");

  pvQGroupBox(p,GroupBox3,groupBox,-1,HORIZONTAL,"FontSize");
  pvSetGeometry(p,GroupBox3,10,510,151,60);

  pvQSpinBox(p,SpinBoxFontSize,GroupBox3,0,99,1);
  pvSetGeometry(p,SpinBoxFontSize,10,25,131,31);

  pvQLayoutVbox(p,ID_MAIN_WIDGET,-1);

  pvQLayoutHbox(p,layout1,ID_MAIN_WIDGET);

  pvAddWidgetOrLayout(p,layout1,groupBox,-1,-1);
  pvAddWidgetOrLayout(p,layout1,PVMultiLineEdit2,-1,-1);
  pvAddWidgetOrLayout(p,ID_MAIN_WIDGET,layout1,-1,-1);

  pvEndDefinition(p);
  return 0;
}

// _end_of_generated_area_ (do not edit -> use ui2pvc) ---------------------

int create_eventlog()
{
  event_log_server = new rlEventLogServer("EL");
  event_log_server_threads = new rlEventLogServerThreads(switches.eventport,event_log_server);
  event_log_server_threads->start();
  return 0;
}

int free_eventlog()
{
  if(event_log_server         != NULL) delete event_log_server;
  if(event_log_server_threads != NULL) delete event_log_server_threads;
  return 0;
}

static void event_out(PARAM *p, DATA *d, const char *event)
{
  if(d->font_size != d->new_font_size)
  {
    d->font_size = d->new_font_size;
    pvSetFont(p,PVMultiLineEdit2,"courier",d->font_size,1,0,0,0);
  }
  if     (strncmp("INF",event,3) == 0)pvSetFontColor(p,PVMultiLineEdit2,GREEN);
  else if(strncmp("WAR",event,3) == 0)pvSetFontColor(p,PVMultiLineEdit2,DARK_YELLOW);
  else if(strncmp("ERR",event,3) == 0)pvSetFontColor(p,PVMultiLineEdit2,DARK_RED);
  else if(strncmp("CRI",event,3) == 0)pvSetFontColor(p,PVMultiLineEdit2,200,0,0);
  else if(strncmp("FAT",event,3) == 0)pvSetFontColor(p,PVMultiLineEdit2,RED);
  else if(strncmp("TST",event,3) == 0)pvSetFontColor(p,PVMultiLineEdit2,BLACK);
  pvPrintf(p,PVMultiLineEdit2,"%s",event);
}

static void scroll(PARAM *p, DATA *d)
{
  const char *cptr;
  char event[rl_PRINTF_LENGTH];

  for(int i=0; i<10; )
  {
    cptr = d->offline_file.myfgets(event,sizeof(event)-1);
    if(cptr == NULL) return;
    if(d->filter[0] == '\0' || strstr(event,d->filter) != NULL)
    {
      i++;
      event_out(p,d,event);
    }
  }
}

static int defineMask(PARAM *p)
{
  if(p == NULL) return 1;
  generated_defineMask(p);
  pvSetFont(p,PVMultiLineEdit2,"courier",8,1,0,0,0);
  pvSetEditable(p,PVMultiLineEdit2,0);
  pvSetChecked(p,RadioButtonOnline,1);
  pvHide(p,PushButtonSearch);
  pvHide(p,PushButtonScroll);
  if(switches.pcontrol == 0) pvHide(p,PushButtonBack);
  return 0;
}

static int showData(PARAM *p, DATA *d)
{
  char event[MAX_EVENT_LENGTH];

  if(p == NULL) return 1;
  if(d == NULL) return 1;
  if(d->online == 1)
  {
    while(d->online == 1)
    {
      if(event_log_server->getEvent(event,&d->num) == NULL) break;
      if(event[0] != ' ')
      {
        if(d->filter[0] == '\0' || strstr(event,d->filter) != NULL)
        {
          event_out(p,d,event);
        }
      }
    }
  }
  else if(d->scroll_down == 1)
  {
    scroll(p,d);
  }
  return 0;
}

static int readData(DATA *d) // from shared memory, database or something else
{
  if(d == NULL) return 1;
  // (todo: add your code here)
  return 0;
}

void show_offline(PARAM *p,DATA *d)
{
  const char *cptr;
  char event[rlMAX_EVENT];
  int found,cnt;

  pvClear(p,PVMultiLineEdit2);
  found = cnt = 0;
  cptr = d->offline_file.oldest_file();
  if(cptr == NULL)  return;
  while((cptr = d->offline_file.myfgets(event,sizeof(event)-1)) != NULL)
  {
    if(strstr(cptr,d->pattern) != NULL) found = 1;
    if(found)
    {
      if(d->filter[0] == '\0' || strstr(event,d->filter) != NULL)
      {
        cnt++;
        event_out(p,d,event);
      }
    }
    if(cnt >= 10) break;
  }
}

int show_event(PARAM *p)
{
  DATA d;
  char event[MAX_EVENT_LENGTH];
  char text[MAX_EVENT_LENGTH];
  char str1[MAX_EVENT_LENGTH];
  int  i,w,h,val,x,y,button;

  defineMask(p);
  d.num            = -1; // get all events
  d.online         = 1;  // online mode
  d.pattern[0]     = '\0';
  d.filter[0]      = '\0';
  d.scroll_down    = 0;
  d.font_size      = 0;
  d.new_font_size  = 8;
  readData(&d);  // from shared memory, database or something else
  showData(p,&d);
  while(1)
  {
    pvPollEvent(p,event);
    switch(pvParseEvent(event, &i, text))
    {
      case NULL_EVENT:
        readData(&d); // from shared memory, database or something else
        showData(p,&d);
        break;
      case BUTTON_EVENT:
        //printf("BUTTON_EVENT id=%d\n",i);
        if(i == PushButtonBack)
        {
          return 1;
        }
        if(i == PushButtonSearch)
        {
          d.offline_file.find_files();
          show_offline(p,&d);
        }
        break;
      case BUTTON_PRESSED_EVENT:
        if(i == PushButtonScroll) { d.scroll_down = 1; scroll(p,&d); }
        //printf("BUTTON_PRESSED_EVENT id=%d\n",i);
        break;
      case BUTTON_RELEASED_EVENT:
        if(i == PushButtonScroll) d.scroll_down = 0;
        //printf("BUTTON_RELEASED_EVENT id=%d\n",i);
        break;
      case TEXT_EVENT:
        //printf("TEXT_EVENT id=%d %s\n",i,text);
        if(i == LineEditSearch) rlstrncpy(d.pattern,text,sizeof(d.pattern)-1);
        if(i == LineEditFilter) rlstrncpy(d.filter,text,sizeof(d.filter)-1);
        break;
      case SLIDER_EVENT:
        sscanf(text,"(%d)",&val);
        //printf("SLIDER_EVENT val=%d\n",val);
        if(i == SpinBoxFontSize) d.new_font_size = val;
        break;
      case CHECKBOX_EVENT:
        printf("CHECKBOX_EVENT id=%d %s\n",i,text);
        break;
      case RADIOBUTTON_EVENT:
        //printf("RADIOBUTTON_EVENT id=%d %s\n",i,text);
        sscanf(text,"(%d)",&val);
        if(val == 1)
        {
          if(i == RadioButtonOnline)
          {
            if(d.online != 1) pvClear(p,PVMultiLineEdit2);
            d.online = 1;
            d.num = -1;
            pvHide(p,PushButtonSearch);
            pvHide(p,PushButtonScroll);
          }
          if(i == RadioButtonOffline)
          {
            d.online = 2;
            pvShow(p,PushButtonSearch);
            pvShow(p,PushButtonScroll);
            d.offline_file.find_files();
            show_offline(p,&d);
          }
          if(i == RadioButtonPause)
          {
            d.online = 3;
          }
        }
        break;
      case GL_INITIALIZE_EVENT:
        printf("you have to call initializeGL()\n");
        break;
      case GL_PAINT_EVENT:
        printf("you have to call paintGL()\n");
        break;
      case GL_RESIZE_EVENT:
        sscanf(text,"(%d,%d)",&w,&h);
        printf("you have to call resizeGL(w,h)\n");
        break;
      case GL_IDLE_EVENT:
        break;
      case TAB_EVENT:
        sscanf(text,"(%d)",&val);
        printf("TAB_EVENT(%d,page=%d)\n",i,val);
        break;
      case TABLE_TEXT_EVENT:
        sscanf(text,"(%d,%d,",&x,&y);
        pvGetText(text,str1);
        printf("TABLE_TEXT_EVENT(%d,%d,\"%s\")\n",x,y,str1);
        break;
      case TABLE_CLICKED_EVENT:
        sscanf(text,"(%d,%d,%d)",&x,&y,&button);
        printf("TABLE_CLICKED_EVENT(%d,%d,button=%d)\n",x,y,button);
        break;
      case SELECTION_EVENT:
        sscanf(text,"(%d,",&val);
        pvGetText(text,str1);
        printf("SELECTION_EVENT(column=%d,\"%s\")\n",val,str1);
        break;
      case CLIPBOARD_EVENT:
        sscanf(text,"(%d",&val);
        printf("CLIPBOARD_EVENT(id=%d)\n",val);
        printf("clipboard = \n%s\n",p->clipboard);
        break;
      default:
        printf("UNKNOWN_EVENT id=%d %s\n",i,text);
        break;
    }
  }
}
