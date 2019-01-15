////////////////////////////////////////////////////////////////////////////
//
// show_edit for ProcessViewServer created: Thu Dec 12 12:51:13 2002
//
////////////////////////////////////////////////////////////////////////////
#include "pvapp.h"

extern rlSpreadsheetTable spreadsheat;
extern rlFifo             toCenter;
extern rlThread           center;
extern rlPcontrol        *processlist;

typedef struct // (todo: define your data structure here)
{
  char original_name[MAX_EVENT_LENGTH];
}
DATA;

// _begin_of_generated_area_ (do not edit -> use ui2pvc) -------------------

// our mask contains the following objects
enum {
  ID_MAIN_WIDGET = 0,
  Frame3,
  TextLabel1_2,
  TextLabel1,
  Line1,
  ButtonGroup1,
  RadioButtonActive,
  RadioButtonInactive,
  RadioButtonMissing,
  LineEditName,
  LineEditError,
  LineEditOutput,
  LineEditInput,
  LineEditStartupCommand,
  TextLabel10,
  TextLabel2,
  TextLabel8,
  TextLabel9,
  TextLabel3,
  TextLabelInput,
  TextLabelOutput,
  TextLabelError,
  TextLabel1_3,
  TextLabelPriority,
  SpinBoxCredit,
  SpinBoxInterval,
  SpinBoxPriority,
  PushButtonCancel,
  PushButtonRemove,
  PushButtonNew,
  PushButtonOk,
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
  TQFrame,
  TQLabel,
  TQLabel,
  TQFrame,
  TQButtonGroup,
  TQRadio,
  TQRadio,
  TQRadio,
  TQLineEdit,
  TQLineEdit,
  TQLineEdit,
  TQLineEdit,
  TQLineEdit,
  TQLabel,
  TQLabel,
  TQLabel,
  TQLabel,
  TQLabel,
  TQLabel,
  TQLabel,
  TQLabel,
  TQLabel,
  TQLabel,
  TQSpinBox,
  TQSpinBox,
  TQSpinBox,
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

  pvQFrame(p,Frame3,0,StyledPanel,Raised,1,1);
  pvSetGeometry(p,Frame3,140,10,610,490);

  pvQLabel(p,TextLabel1_2,Frame3);
  pvSetGeometry(p,TextLabel1_2,10,10,281,21);
  pvSetText(p,TextLabel1_2,"Process Parameters:");
  pvSetFont(p,TextLabel1_2,"Nimbus Sans l [Urw]",12,0,0,0,0);

  pvQLabel(p,TextLabel1,Frame3);
  pvSetGeometry(p,TextLabel1,10,50,101,30);
  pvSetText(p,TextLabel1,"State:");

  pvQFrame(p,Line1,Frame3,HLine,Sunken,1,1);
  pvSetGeometry(p,Line1,10,30,580,20);

  pvQButtonGroup(p,ButtonGroup1,Frame3,-1,HORIZONTAL,"");
  pvSetGeometry(p,ButtonGroup1,130,50,160,100);

  pvQRadioButton(p,RadioButtonActive,ButtonGroup1);
  pvSetGeometry(p,RadioButtonActive,10,40,70,20);
  pvSetText(p,RadioButtonActive,"Active");

  pvQRadioButton(p,RadioButtonInactive,ButtonGroup1);
  pvSetGeometry(p,RadioButtonInactive,10,10,80,18);
  pvSetText(p,RadioButtonInactive,"Inactive");
  pvSetChecked(p,RadioButtonInactive,1);

  pvQRadioButton(p,RadioButtonMissing,ButtonGroup1);
  pvSetGeometry(p,RadioButtonMissing,10,70,140,20);
  pvSetText(p,RadioButtonMissing,"Missing");

  pvQLineEdit(p,LineEditName,Frame3);
  pvSetGeometry(p,LineEditName,130,160,461,30);

  pvQLineEdit(p,LineEditError,Frame3);
  pvSetGeometry(p,LineEditError,130,440,461,30);

  pvQLineEdit(p,LineEditOutput,Frame3);
  pvSetGeometry(p,LineEditOutput,130,400,461,30);

  pvQLineEdit(p,LineEditInput,Frame3);
  pvSetGeometry(p,LineEditInput,130,360,461,30);

  pvQLineEdit(p,LineEditStartupCommand,Frame3);
  pvSetGeometry(p,LineEditStartupCommand,130,320,461,30);

  pvQLabel(p,TextLabel10,Frame3);
  pvSetGeometry(p,TextLabel10,250,240,81,25);
  pvSetText(p,TextLabel10,"hours");

  pvQLabel(p,TextLabel2,Frame3);
  pvSetGeometry(p,TextLabel2,10,160,110,30);
  pvSetText(p,TextLabel2,"Name:");

  pvQLabel(p,TextLabel8,Frame3);
  pvSetGeometry(p,TextLabel8,10,200,111,30);
  pvSetText(p,TextLabel8,"Credit:");

  pvQLabel(p,TextLabel9,Frame3);
  pvSetGeometry(p,TextLabel9,10,240,111,30);
  pvSetText(p,TextLabel9,"Interval:");

  pvQLabel(p,TextLabel3,Frame3);
  pvSetGeometry(p,TextLabel3,10,320,111,30);
  pvSetText(p,TextLabel3,"Startup Command:");

  pvQLabel(p,TextLabelInput,Frame3);
  pvSetGeometry(p,TextLabelInput,10,360,111,30);
  pvSetText(p,TextLabelInput,"Input:");

  pvQLabel(p,TextLabelOutput,Frame3);
  pvSetGeometry(p,TextLabelOutput,10,400,111,30);
  pvSetText(p,TextLabelOutput,"Output:");

  pvQLabel(p,TextLabelError,Frame3);
  pvSetGeometry(p,TextLabelError,10,440,110,30);
  pvSetText(p,TextLabelError,"Error:");

  pvQLabel(p,TextLabel1_3,Frame3);
  pvSetGeometry(p,TextLabel1_3,250,200,281,31);
  pvSetText(p,TextLabel1_3,"(Credit==-1 is restart always)");

  pvQLabel(p,TextLabelPriority,Frame3);
  pvSetGeometry(p,TextLabelPriority,10,280,111,30);
  pvSetText(p,TextLabelPriority,"Priority:");

  pvQSpinBox(p,SpinBoxCredit,Frame3,-1,10,1);
  pvSetGeometry(p,SpinBoxCredit,130,200,111,30);

  pvQSpinBox(p,SpinBoxInterval,Frame3,1,10,1);
  pvSetGeometry(p,SpinBoxInterval,130,240,111,30);

  pvQSpinBox(p,SpinBoxPriority,Frame3,0,15,1);
  pvSetGeometry(p,SpinBoxPriority,130,280,111,30);

  pvQPushButton(p,PushButtonCancel,0);
  pvSetGeometry(p,PushButtonCancel,10,10,120,31);
  pvSetText(p,PushButtonCancel,"Cancel");

  pvQPushButton(p,PushButtonRemove,0);
  pvSetGeometry(p,PushButtonRemove,10,200,120,31);
  pvSetText(p,PushButtonRemove,"Remove Process");

  pvQPushButton(p,PushButtonNew,0);
  pvSetGeometry(p,PushButtonNew,10,160,120,31);
  pvSetText(p,PushButtonNew,"New Process");

  pvQPushButton(p,PushButtonOk,0);
  pvSetGeometry(p,PushButtonOk,10,120,120,31);
  pvSetText(p,PushButtonOk,"Modify Process");


  pvEndDefinition(p);
  return 0;
}

// _end_of_generated_area_ (do not edit -> use ui2pvc) ---------------------

static int defineMask(PARAM *p)
{
  USER *user;
  if(p == NULL) return 1;
  generated_defineMask(p);
  user = (USER *) p->user;
#ifndef __VMS
  pvHide(p,LineEditError);
  pvHide(p,LineEditOutput);
  pvHide(p,LineEditInput);
  pvHide(p,TextLabelInput);
  pvHide(p,TextLabelOutput);
  pvHide(p,TextLabelError);
#endif
#ifdef unix
  pvHide(p,TextLabelPriority);
  pvHide(p,SpinBoxPriority);
#endif
  if(strcmp(user->state,STATE_MISSING)  == 0)  pvSetChecked(p,RadioButtonMissing,1);
  if(strcmp(user->state,STATE_ACTIVE)   == 0)  pvSetChecked(p,RadioButtonActive,1);
  if(strcmp(user->state,STATE_INACTIVE) == 0)  pvSetChecked(p,RadioButtonInactive,1);
  pvPrintf(p,LineEditName,"%s",user->name);

  if(user->credit   < -1) user->credit   = -1;
  if(user->interval < 1)  user->interval = 1;
  if(user->priority < 0)  user->priority = 0;
  
  if(user->credit   > 10) user->credit   = 10;
  if(user->interval > 10) user->interval = 10;
#ifdef _WIN32
  if(user->priority > 3)  user->priority = 3;
#endif
#ifdef __VMS
  if(user->priority > 15) user->priority = 15;
#endif
  
  pvSetValue(p,SpinBoxCredit  ,user->credit);
  pvSetValue(p,SpinBoxInterval,user->interval),
  pvSetValue(p,SpinBoxPriority,user->priority);
  pvPrintf(p,LineEditStartupCommand,"%s",user->startup_command);
  return 0;
}

static int showData(PARAM *p, DATA *d)
{
  if(p == NULL) return 1;
  if(d == NULL) return 1;
  // (todo: add your code here)
  return 0;
}

static int readData(DATA *d) // from shared memory, database or something else
{
  if(d == NULL) return 1;
  // (todo: add your code here)
  return 0;
}

static void do_remove(PARAM *p)
{
  long pid;
  int  irow,removed;
  char name[MAX_EVENT_LENGTH];
  USER *user;

  if(p == NULL) return;
  user = (USER *) p->user;
  removed = 0;
  center.lock();
  for(irow=FIRST_ROW; spreadsheat.exists(1,irow); irow++)
  {
    rlstrncpy(name,spreadsheat.text(T_name,irow), sizeof(name)-1);
    if(strcmp(name,user->name) == 0)
    {
#ifdef __VMS
      sscanf(spreadsheat.text(T_pid,irow),"%x",&pid);
#else
      sscanf(spreadsheat.text(T_pid,irow),"%ld",&pid);
#endif
      spreadsheat.printf(T_state,          irow,"");
      spreadsheat.printf(T_pid,            irow,"");
      spreadsheat.printf(T_name,           irow,"");
      spreadsheat.printf(T_credit,         irow,"");
      spreadsheat.printf(T_interval,       irow,"");
      spreadsheat.printf(T_priority,       irow,"");
      spreadsheat.printf(T_startup_command,irow,"");
      spreadsheat.printf(T_input,          irow,"");
      spreadsheat.printf(T_output,         irow,"");
      spreadsheat.printf(T_error,          irow,"");
      spreadsheat.printf(T_initial_credit, irow,"");
      spreadsheat.printf(T_time,           irow,"");
      removed = 1;
      break;
    }
  }
  center.unlock();
  if(removed)
  {
    if(pid != 0) toCenter.printf("sigkill(%ld)\n",pid);
    toCenter.printf("remove(\"%s\")\n",name);
  }
}

static void do_new(PARAM *p)
{
  int  irow;
  char name[MAX_EVENT_LENGTH];
  USER *user;

  if(p == NULL) return;
  user = (USER *) p->user;
  center.lock();
  for(irow=FIRST_ROW; spreadsheat.exists(1,irow); irow++)
  {
    rlstrncpy(name,spreadsheat.text(T_name,irow), sizeof(name)-1);
    if(name[0] <= ' ') break;
  }
  spreadsheat.printf(T_state,          irow,"%s",user->state);
  spreadsheat.printf(T_pid,            irow,"%d",0);
  spreadsheat.printf(T_name,           irow,"%s",user->name);
  spreadsheat.printf(T_credit,         irow,"%d",user->credit);
  spreadsheat.printf(T_interval,       irow,"%d",user->interval);
  spreadsheat.printf(T_priority,       irow,"%d",user->priority);
  spreadsheat.printf(T_startup_command,irow,"%s",user->startup_command);
  spreadsheat.printf(T_input,          irow,"%s",user->input);
  spreadsheat.printf(T_output,         irow,"%s",user->output);
  spreadsheat.printf(T_error,          irow,"%s",user->error);
  spreadsheat.printf(T_initial_credit, irow,"%d",user->credit);
  center.unlock();
  toCenter.printf("save()\n");
}

static void do_save(PARAM *p)
{
  long pid;
  int  irow,found;
  USER *user;

  if(p == NULL) return;
  user = (USER *) p->user;
  if(user->edited == 0) return;
  pid = found = 0;
  center.lock();
  for(irow=FIRST_ROW; spreadsheat.exists(1,irow); irow++)
  {
    if(strcmp(user->name,spreadsheat.text(T_name,irow)) == 0)
    {
#ifdef __VMS
      sscanf(spreadsheat.text(T_pid,irow),"%x",&pid);
#else
      sscanf(spreadsheat.text(T_pid,irow),"%ld",&pid);
#endif
      spreadsheat.printf(T_state,          irow,"%s",user->state);
      spreadsheat.printf(T_name,           irow,"%s",user->name);
      spreadsheat.printf(T_credit,         irow,"%d",user->credit);
      spreadsheat.printf(T_interval,       irow,"%d",user->interval);
      spreadsheat.printf(T_priority,       irow,"%d",user->priority);
      spreadsheat.printf(T_startup_command,irow,"%s",user->startup_command);
      spreadsheat.printf(T_input,          irow,"%s",user->input);
      spreadsheat.printf(T_output,         irow,"%s",user->output);
      spreadsheat.printf(T_error,          irow,"%s",user->error);
      spreadsheat.printf(T_initial_credit, irow,"%d",user->credit);
      found = 1;
      break;
    }
  }
  center.unlock();
  if(pid != 0) toCenter.printf("sigkill(%ld)\n",pid);
  if(found)    toCenter.printf("save()\n");
  else         do_new(p);
}

int show_edit(PARAM *p)
{
  USER *user;
  DATA d;
  char event[MAX_EVENT_LENGTH];
  char text[MAX_EVENT_LENGTH];
  char str1[MAX_EVENT_LENGTH];
  int  i,w,h,val,x,y,button;

  user = (USER *) p->user;
  user->edited = 0;
  defineMask(p);
  memset(&d,0,sizeof(DATA));
  readData(&d); // from shared memory, database or something else
  showData(p,&d);
  rlstrncpy(d.original_name,user->name,sizeof(d.original_name)-1);
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
        if(i == PushButtonOk)
        {
          if(user->name[0] <= ' ')
          {
            pvMessageBox(p,-1,BoxInformation,"Please supply a process name",1,0,0);
          }
          else if(user->startup_command[0] <= ' ')
          {
            pvMessageBox(p,-1,BoxInformation,"Please supply a startup command",1,0,0);
          }
          else if(strcmp(d.original_name,user->name) != 0)
          {
            pvMessageBox(p,-1,BoxInformation,"Sorry you have modified the process name",1,0,0);
          }
          else
          {
            do_save(p);
            return 2;
          }
        }
        if(i == PushButtonCancel) return 2;
        if(i == PushButtonRemove)
        {
          if(user->name[0] <= ' ')
          {
            pvMessageBox(p,-1,BoxInformation,"Please supply a process name",1,0,0);
          }
          else if(user->startup_command[0] <= ' ')
          {
            pvMessageBox(p,-1,BoxInformation,"Please supply a startup command",1,0,0);
          }
          else if(strcmp(d.original_name,user->name) != 0)
          {
            pvMessageBox(p,-1,BoxInformation,"Sorry you have modified the process name",1,0,0);
          }
          else
          {
            do_remove(p);
            return 2;
          }
        }
        if(i == PushButtonNew)
        {
          if(user->name[0] <= ' ')
          {
            pvMessageBox(p,-1,BoxInformation,"Please supply a process name",1,0,0);
          }
          else if(user->startup_command[0] <= ' ')
          {
            pvMessageBox(p,-1,BoxInformation,"Please supply a startup command",1,0,0);
          }
          else
          {
            do_new(p);
            return 2;
          }
        }
        //printf("BUTTON_EVENT id=%d\n",i);
        break;
      case TEXT_EVENT:
        user->edited = 1;
        if(i == LineEditName)           rlstrncpy(user->name,text,sizeof(user->name)-1);
        if(i == LineEditError)          rlstrncpy(user->error,text,sizeof(user->error)-1);
        if(i == LineEditOutput)         rlstrncpy(user->output,text,sizeof(user->output)-1);
        if(i == LineEditInput)          rlstrncpy(user->input,text,sizeof(user->input)-1);
        if(i == LineEditStartupCommand) rlstrncpy(user->startup_command,text,sizeof(user->startup_command)-1);
        //printf("TEXT_EVENT id=%d %s\n",i,text);
        break;
      case SLIDER_EVENT:
        user->edited = 1;
        sscanf(text,"(%d)",&val);
        if(i == SpinBoxInterval) user->interval = val;
        if(i == SpinBoxPriority)
        {
#ifdef _WIN32
          if(val > 3)
          {
            val = 3;
            pvSetValue(p,SpinBoxPriority,val);
          }
#endif
          user->priority = val;
        }
        if(i == SpinBoxCredit)   user->credit   = val;
        //printf("SLIDER_EVENT val=%d\n",val);
        break;
      case CHECKBOX_EVENT:
        printf("CHECKBOX_EVENT id=%d %s\n",i,text);
        break;
      case RADIOBUTTON_EVENT:
        user->edited = 1;
        sscanf(text,"(%d)",&val);
        if(i == RadioButtonMissing  && val==1) rlstrncpy(user->state,STATE_MISSING,sizeof(user->state)-1);
        if(i == RadioButtonActive   && val==1) rlstrncpy(user->state,STATE_ACTIVE,sizeof(user->state)-1);
        if(i == RadioButtonInactive && val==1) rlstrncpy(user->state,STATE_INACTIVE,sizeof(user->state)-1);
        //printf("RADIOBUTTON_EVENT id=%d %s\n",i,text);
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
        //printf("UNKNOWN_EVENT id=%d %s\n",i,text);
        break;
    }
  }
}
