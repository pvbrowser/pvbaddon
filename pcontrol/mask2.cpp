////////////////////////////////////////////////////////////////////////////
//
// show_pcontrol for ProcessViewServer created: Thu Dec 12 11:53:11 2002
//
////////////////////////////////////////////////////////////////////////////
#include "pvapp.h"

extern rlSpreadsheetTable  spreadsheat;
extern rlFifo              toCenter;
extern rlThread            center;
extern rlInterpreter       interpreter;
extern rlPcontrol         *processlist;

typedef struct // (todo: define your data structure here)
{
  char state[MAX_EVENT_LENGTH];
  long pid;
  char name[MAX_EVENT_LENGTH];
  char start_date[MAX_EVENT_LENGTH];
  int  credit;
  int  interval;
  int  priority;
  char startup_command[MAX_EVENT_LENGTH];
}
DATA;

// _begin_of_generated_area_ (do not edit -> use ui2pvc) -------------------

// our mask contains the following objects
enum {
  ID_MAIN_WIDGET = 0,
  TextLabel1,
  ListView1,
  groupBox,
  PushButtonLogout,
  PushButtonSIGKILL,
  PushButtonSIGTERM,
  PushButtonEdit,
  layout1,
  layout2,
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
  ""};

  static const int widgetType[ID_END_OF_WIDGETS+1] = {
  0,
  TQLabel,
  TQListView,
  TQGroupBox,
  TQPushButton,
  TQPushButton,
  TQPushButton,
  TQPushButton,
  -1 };

static int generated_defineMask(PARAM *p)
{
  int w,h,depth;

  if(p == NULL) return 1;
  w = h = depth = strcmp(toolTip[0],whatsThis[0]);
  if(widgetType[0] == -1) return 1;
  if(w==h) depth=0; // fool the compiler
  pvStartDefinition(p,ID_END_OF_WIDGETS);

  pvQLabel(p,TextLabel1,0);
  pvSetGeometry(p,TextLabel1,155,10,165,25);
  pvSetText(p,TextLabel1,"List of Processes:");
  pvSetFont(p,TextLabel1,"Nimbus Sans l [Urw]",14,0,0,0,0);

  pvQListView(p,ListView1,0);
  pvSetGeometry(p,ListView1,150,40,811,700);
  pvSetMultiSelection(p,ListView1,0);

  pvQGroupBox(p,groupBox,0,-1,HORIZONTAL,"");
  pvSetGeometry(p,groupBox,5,5,130,590);
  pvSetMinSize(p,groupBox,130,0);
  pvSetMaxSize(p,groupBox,130,99999);

  pvQPushButton(p,PushButtonLogout,groupBox);
  pvSetGeometry(p,PushButtonLogout,10,10,111,31);
  pvSetText(p,PushButtonLogout,"Logout");

  pvQPushButton(p,PushButtonSIGKILL,groupBox);
  pvSetGeometry(p,PushButtonSIGKILL,10,210,111,31);
  pvSetText(p,PushButtonSIGKILL,"SIGKILL");

  pvQPushButton(p,PushButtonSIGTERM,groupBox);
  pvSetGeometry(p,PushButtonSIGTERM,10,245,111,31);
  pvSetText(p,PushButtonSIGTERM,"SIGTERM");

  pvQPushButton(p,PushButtonEdit,groupBox);
  pvSetGeometry(p,PushButtonEdit,10,280,111,31);
  pvSetText(p,PushButtonEdit,"Edit");

  pvQLayoutHbox(p,ID_MAIN_WIDGET,-1);

  pvQLayoutVbox(p,layout1,ID_MAIN_WIDGET);

  pvQLayoutVbox(p,layout2,ID_MAIN_WIDGET);

  pvAddWidgetOrLayout(p,layout1,groupBox,-1,-1);
  pvAddWidgetOrLayout(p,layout2,TextLabel1,-1,-1);
  pvAddWidgetOrLayout(p,layout2,ListView1,-1,-1);
  pvAddWidgetOrLayout(p,ID_MAIN_WIDGET,layout1,-1,-1);
  pvAddWidgetOrLayout(p,ID_MAIN_WIDGET,layout2,-1,-1);

  pvEndDefinition(p);
  return 0;
}

// _end_of_generated_area_ (do not edit -> use ui2pvc) ---------------------

static const char *row(int i)
{
  static char rowbuf[100];

  sprintf(rowbuf,"/%d",i);
  return rowbuf;
}

static void show_list_view(PARAM *p)
{
  int  i,irow;
  char name[100]; // VMS is terribly deprecated
  char state[20]; // it has a very low stacksize
  USER *user;

  user = (USER *) p->user;
  // T_state = 1, T_pid, T_name, T_credit, T_interval, T_priority, T_startup_command, T_input, T_output, T_error, T_initial_credit
  // L_state = 0, L_pid, L_name, L_startdate, L_credit, L_interval, L_startup_command
  pvSetSorting(p,ListView1,-1,1);
  center.lock();
  i = 0;
  for(irow=FIRST_ROW; spreadsheat.exists(irow,1); irow++)
  {
    rlstrncpy(name,spreadsheat.text(T_name,irow),sizeof(name)-1);
    if(name[0] > ' ')
    {
      rlstrncpy(state,spreadsheat.text(T_state,irow),sizeof(state)-1);
      pvListViewPrintf(p,ListView1,row(i),L_state,           "%s",state);
      pvListViewPrintf(p,ListView1,row(i),L_pid,             "%s",spreadsheat.text(T_pid             ,irow));
      pvListViewPrintf(p,ListView1,row(i),L_name,            "%s",name);
      pvListViewPrintf(p,ListView1,row(i),L_startdate,       "%s",spreadsheat.text(T_time            ,irow));
      pvListViewPrintf(p,ListView1,row(i),L_credit,          "%s",spreadsheat.text(T_credit          ,irow));
      pvListViewPrintf(p,ListView1,row(i),L_interval,        "%s",spreadsheat.text(T_interval        ,irow));
      pvListViewPrintf(p,ListView1,row(i),L_startup_command, "%s",spreadsheat.text(T_startup_command ,irow));
      user->mytable.printf(1,irow,"%s",spreadsheat.text(T_state  ,irow));
      user->mytable.printf(2,irow,"%s",spreadsheat.text(T_pid    ,irow));
      user->mytable.printf(3,irow,"%s",spreadsheat.text(T_time   ,irow));
      user->mytable.printf(4,irow,"%s",spreadsheat.text(T_credit ,irow));
      if(strcmp(state,STATE_ACTIVE)   == 0) pvSetListViewPixmap(p,ListView1,row(i),ICON_ACTIVE,0);
      if(strcmp(state,STATE_INACTIVE) == 0) pvSetListViewPixmap(p,ListView1,row(i),ICON_INACTIVE,0);
      if(strcmp(state,STATE_MISSING)  == 0) pvSetListViewPixmap(p,ListView1,row(i),ICON_MISSING,0);
      i++;
    }
  }
  user->mytable.printf(1,irow,"#end");
  center.unlock();
  pvSetSorting(p,ListView1,1,1);
}

static int defineMask(PARAM *p)
{
  USER *user;

  if(p == NULL) return 1;
  user = (USER *) p->user;
  generated_defineMask(p);
  if(user->view == 1)
  {
    pvHide(p,PushButtonSIGTERM);
    pvHide(p,PushButtonSIGKILL);
    pvHide(p,PushButtonEdit);
  }
  pvSetMultiSelection(p,ListView1,0);
  pvAddColumn(p,ListView1,"State"             ,90);
  pvAddColumn(p,ListView1,"PID"               ,80);
  pvAddColumn(p,ListView1,"Name"              ,100);
  pvAddColumn(p,ListView1,"Time (Start/Stop)" ,180);
  pvAddColumn(p,ListView1,"Credit"            ,50);
  pvAddColumn(p,ListView1,"Interval"          ,50);
  pvAddColumn(p,ListView1,"Startup Command"   ,800);
  show_list_view(p);
  return 0;
}

static int showData(PARAM *p, DATA *d)
{
  int  irow;
  char buf1[100]; // VMS is terribly deprecated
  char buf2[100]; // it has a very low stacksize
  USER *user;

  if(p == NULL) return 1;
  if(d == NULL) return 1;
  user = (USER *) p->user;
  irow = FIRST_ROW;
  while(1)
  {
    center.lock();
    rlstrncpy(buf1,  spreadsheat.text(T_state,irow), sizeof(buf1)-1);
    center.unlock();
    rlstrncpy(buf2,user->mytable.text(1,irow),sizeof(buf2)-1);
    if(buf2[0] == '#') break;
    if(strcmp(buf1,buf2) != 0 && buf1[0] > ' ' && buf2[0] > ' ') // state has changed
    {
      pvClear(p,ListView1);
      show_list_view(p);
      break;
    }

    center.lock();
    rlstrncpy(buf1,  spreadsheat.text(T_pid,irow), sizeof(buf1)-1);
    center.unlock();
    rlstrncpy(buf2,user->mytable.text(2,irow), sizeof(buf2)-1);
    if(buf2[0] == '#') break;
    if(strcmp(buf1,buf2) != 0 && buf1[0] > ' ' && buf2[0] > ' ') // pid has changed
    {
      pvClear(p,ListView1);
      show_list_view(p);
      break;
    }

    center.lock();
    rlstrncpy(buf1,  spreadsheat.text(T_time,irow), sizeof(buf1)-1);
    center.unlock();
    rlstrncpy(buf2,user->mytable.text(3,irow), sizeof(buf2)-1);
    if(buf2[0] == '#') break;
    if(strcmp(buf1,buf2) != 0 && buf1[0] > ' ' && buf2[0] > ' ') // time has changed
    {
      pvClear(p,ListView1);
      show_list_view(p);
      break;
    }

    center.lock();
    rlstrncpy(buf1,  spreadsheat.text(T_credit,irow), sizeof(buf1)-1);
    center.unlock();
    rlstrncpy(buf2,user->mytable.text(4,irow), sizeof(buf2)-1);
    if(buf2[0] == '#') break;
    if(strcmp(buf1,buf2) != 0 && buf1[0] > ' ' && buf2[0] > ' ') // credit has changed
    {
      pvClear(p,ListView1);
      show_list_view(p);
      break;
    }

    irow++;
  }
  return 0;
}

static int readData(DATA *d) // from shared memory, database or something else
{
  if(d == NULL) return 1;
  // (todo: add your code here)
  return 0;
}

int show_pcontrol(PARAM *p)
{
  DATA d;
  USER *user;
  char event[MAX_EVENT_LENGTH];
  char text[MAX_EVENT_LENGTH];
  char str1[MAX_EVENT_LENGTH];
  int  i,w,h,val,x,y,button,irow;

  user = (USER *) p->user;
  defineMask(p);
  memset(&d,0,sizeof(DATA));
  readData(&d); // from shared memory, database or something else
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
        if(i == PushButtonLogout)  return 1;
        if(i == PushButtonSIGTERM)
        {
          printf("sigterm(%ld)\n",d.pid);
          toCenter.printf("sigterm(%ld)\n",d.pid);
        }
        if(i == PushButtonSIGKILL)
        {
          printf("sigkill(%ld)\n",d.pid);
          toCenter.printf("sigkill(%ld)\n",d.pid);
        }
        if(i == PushButtonEdit)
        {
          rlstrncpy(user->state,d.state,sizeof(user->state)-1);
          rlstrncpy(user->name,d.name,sizeof(user->name)-1);
          rlstrncpy(user->startup_command,d.startup_command,sizeof(user->startup_command)-1);
          for(irow=FIRST_ROW; spreadsheat.exists(irow,1); irow++)
          {
            rlstrncpy(str1,spreadsheat.text(T_name,irow),sizeof(str1)-1);
            if(strcmp(d.name,str1) == 0)
            {
              if(str1[0] > ' ')
              {
                rlstrncpy(str1,spreadsheat.text(T_initial_credit,irow),sizeof(str1)-1);
                sscanf(str1,"%d",&d.credit);
                rlstrncpy(str1,spreadsheat.text(T_priority      ,irow),sizeof(str1)-1);
                sscanf(str1,"%d",&d.priority);
                break;
              }
            }
          }
          user->credit   = d.credit;
          user->interval = d.interval;
          user->priority = d.priority;
          return 3;
        }
        //printf("BUTTON_EVENT id=%d\n",i);
        break;
      case TEXT_EVENT:
        printf("TEXT_EVENT id=%d %s\n",i,text);
        break;
      case SLIDER_EVENT:
        sscanf(text,"(%d)",&val);
        printf("SLIDER_EVENT val=%d\n",val);
        break;
      case CHECKBOX_EVENT:
        printf("CHECKBOX_EVENT id=%d %s\n",i,text);
        break;
      case RADIOBUTTON_EVENT:
        printf("RADIOBUTTON_EVENT id=%d %s\n",i,text);
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
        //printf("SELECTION_EVENT(column=%d,\"%s\")\n",val,str1);
        if(i == ListView1)
        {
          if(val == 0) rlstrncpy(d.state,str1,sizeof(d.state)-1);
#ifdef __VMS
          if(val == 1) sscanf(str1,"%x",&d.pid);
#else
          if(val == 1) sscanf(str1,"%ld",&d.pid);
#endif
          if(val == 2) rlstrncpy(d.name,str1,sizeof(d.name)-1);
          if(val == 3) rlstrncpy(d.start_date,str1,sizeof(d.start_date)-1);
          if(val == 4) sscanf(str1,"%d",&d.credit);
          if(val == 5) sscanf(str1,"%d",&d.interval);
          if(val == 6) rlstrncpy(d.startup_command,str1,sizeof(d.startup_command)-1);
        }
        break;
      case CLIPBOARD_EVENT:
        sscanf(text,"(%d",&val);
        printf("CLIPBOARD_EVENT(id=%d)\n",val);
        printf("clipboard = \n%s\n",p->clipboard);
        break;
      default:
        //printf("UNKNOWN_EVENT id=%d %s\n",i,text);
        break;
    }
  }
}
