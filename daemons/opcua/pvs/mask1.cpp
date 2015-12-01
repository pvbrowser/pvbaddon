////////////////////////////////////////////////////////////////////////////
//
// show_mask1 for ProcessViewServer created: Mo Aug 27 10:17:41 2007
//
////////////////////////////////////////////////////////////////////////////
#include "pvapp.h"

// _begin_of_generated_area_ (do not edit -> use ui2pvc) -------------------

// our mask contains the following objects
enum {
  ID_MAIN_WIDGET = 0,
  obj2,
  obj1,
  obj8,
  obj9,
  obj10,
  obj11,
  obj12,
  obj13,
  obj14,
  buttonIncrementAnswer,
  obj6,
  buttonInt16,
  buttonInt32,
  buttonFloat,
  buttonDouble,
  buttonHello,
  buttonWorld,
  labelWriteErrorCount,
  labelReadErrorCount,
  obj7,
  ID_END_OF_WIDGETS
};

// our mask contains the following widget names
  static const char *widgetName[] = {
  "ID_MAIN_WIDGET",
  "obj2",
  "obj1",
  "obj8",
  "obj9",
  "obj10",
  "obj11",
  "obj12",
  "obj13",
  "obj14",
  "buttonIncrementAnswer",
  "obj6",
  "buttonInt16",
  "buttonInt32",
  "buttonFloat",
  "buttonDouble",
  "buttonHello",
  "buttonWorld",
  "labelWriteErrorCount",
  "labelReadErrorCount",
  "obj7",
  "ID_END_OF_WIDGETS",
  ""};

  static const char *toolTip[] = {
  "",
  "",
  "",
  "0#61#FolderType#FolderType",
  "0#2253#Server#Server",
  "1#95#current time#current time",
  "1#96#cpu temperature#cpu temperature",
  "1#97#status LED#status LED",
  "1#the.answer#the answer#the answer",
  "1#50000#Demo#Demo",
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
  ""};

  static const int widgetType[ID_END_OF_WIDGETS+1] = {
  0,
  TQTabWidget,
  TQWidget,
  TQLabel,
  TQLabel,
  TQLabel,
  TQLabel,
  TQLabel,
  TQLabel,
  TQLabel,
  TQPushButton,
  TQWidget,
  TQPushButton,
  TQPushButton,
  TQPushButton,
  TQPushButton,
  TQPushButton,
  TQPushButton,
  TQLabel,
  TQLabel,
  TQLabel,
  -1 };

static int generated_defineMask(PARAM *p)
{
  int w,h,depth;

  if(p == NULL) return 1;
  if(widgetName[0] == NULL) return 1; // suppress unused warning
  w = h = depth = strcmp(toolTip[0],whatsThis[0]);
  if(widgetType[0] == -1) return 1;
  if(w==h) depth=0; // fool the compiler
  pvStartDefinition(p,ID_END_OF_WIDGETS);

  pvQTabWidget(p,obj2,0);
  pvSetGeometry(p,obj2,10,50,770,540);
  pvSetFont(p,obj2,"Sans Serif",9,0,0,0,0);

  pvQWidget(p,obj1,obj2);
  pvAddTab(p,obj2,obj1,pvtr("OPC UA test"));
  pvSetFont(p,obj1,"Sans Serif",9,0,0,0,0);

  pvQLabel(p,obj8,obj1);
  pvSetGeometry(p,obj8,5,15,750,15);
  pvSetText(p,obj8,pvtr("0#61#FolderType#FolderType"));
  pvSetFont(p,obj8,"Sans Serif",9,0,0,0,0);
  pvToolTip(p,obj8,pvtr("0#61#FolderType#FolderType"));

  pvQLabel(p,obj9,obj1);
  pvSetGeometry(p,obj9,5,30,720,15);
  pvSetText(p,obj9,pvtr("0#2253#Server#Server"));
  pvSetFont(p,obj9,"Sans Serif",9,0,0,0,0);
  pvToolTip(p,obj9,pvtr("0#2253#Server#Server"));

  pvQLabel(p,obj10,obj1);
  pvSetGeometry(p,obj10,5,45,740,15);
  pvSetText(p,obj10,pvtr("1#95#current time#current time"));
  pvSetFont(p,obj10,"Sans Serif",9,0,0,0,0);
  pvToolTip(p,obj10,pvtr("1#95#current time#current time"));

  pvQLabel(p,obj11,obj1);
  pvSetGeometry(p,obj11,5,60,735,15);
  pvSetText(p,obj11,pvtr("1#96#cpu temperature#cpu temperature"));
  pvSetFont(p,obj11,"Sans Serif",9,0,0,0,0);
  pvToolTip(p,obj11,pvtr("1#96#cpu temperature#cpu temperature"));

  pvQLabel(p,obj12,obj1);
  pvSetGeometry(p,obj12,5,75,745,15);
  pvSetText(p,obj12,pvtr("1#97#status LED#status LED"));
  pvSetFont(p,obj12,"Sans Serif",9,0,0,0,0);
  pvToolTip(p,obj12,pvtr("1#97#status LED#status LED"));

  pvQLabel(p,obj13,obj1);
  pvSetGeometry(p,obj13,5,90,735,15);
  pvSetText(p,obj13,pvtr("1#the.answer#the answer#the answer"));
  pvSetFont(p,obj13,"Sans Serif",9,0,0,0,0);
  pvToolTip(p,obj13,pvtr("1#the.answer#the answer#the answer"));

  pvQLabel(p,obj14,obj1);
  pvSetGeometry(p,obj14,5,105,740,15);
  pvSetText(p,obj14,pvtr("1#50000#Demo#Demo"));
  pvSetFont(p,obj14,"Sans Serif",9,0,0,0,0);
  pvToolTip(p,obj14,pvtr("1#50000#Demo#Demo"));

  pvQPushButton(p,buttonIncrementAnswer,obj1);
  pvSetGeometry(p,buttonIncrementAnswer,5,140,135,30);
  pvSetText(p,buttonIncrementAnswer,pvtr("IncTheAnswer"));
  pvSetFont(p,buttonIncrementAnswer,"Sans Serif",9,0,0,0,0);

  pvQWidget(p,obj6,obj2);
  pvAddTab(p,obj2,obj6,pvtr("tmp test"));
  pvSetFont(p,obj6,"Sans Serif",9,0,0,0,0);

  pvQPushButton(p,buttonInt16,obj6);
  pvSetGeometry(p,buttonInt16,5,95,100,30);
  pvSetText(p,buttonInt16,pvtr("Incremt Int16"));
  pvSetFont(p,buttonInt16,"Sans Serif",9,0,0,0,0);

  pvQPushButton(p,buttonInt32,obj6);
  pvSetGeometry(p,buttonInt32,110,95,100,30);
  pvSetText(p,buttonInt32,pvtr("Increment Int32"));
  pvSetFont(p,buttonInt32,"Sans Serif",9,0,0,0,0);

  pvQPushButton(p,buttonFloat,obj6);
  pvSetGeometry(p,buttonFloat,215,95,100,30);
  pvSetText(p,buttonFloat,pvtr("Increment Float"));
  pvSetFont(p,buttonFloat,"Sans Serif",9,0,0,0,0);

  pvQPushButton(p,buttonDouble,obj6);
  pvSetGeometry(p,buttonDouble,320,95,100,30);
  pvSetText(p,buttonDouble,pvtr("Increment Double"));
  pvSetFont(p,buttonDouble,"Sans Serif",9,0,0,0,0);

  pvQPushButton(p,buttonHello,obj6);
  pvSetGeometry(p,buttonHello,425,95,100,30);
  pvSetText(p,buttonHello,pvtr("Hello"));
  pvSetFont(p,buttonHello,"Sans Serif",9,0,0,0,0);

  pvQPushButton(p,buttonWorld,obj6);
  pvSetGeometry(p,buttonWorld,530,95,100,30);
  pvSetText(p,buttonWorld,pvtr("World"));
  pvSetFont(p,buttonWorld,"Sans Serif",9,0,0,0,0);

  pvQLabel(p,labelWriteErrorCount,obj6);
  pvSetGeometry(p,labelWriteErrorCount,5,130,620,15);
  pvSetText(p,labelWriteErrorCount,pvtr("writeErrorCount"));
  pvSetFont(p,labelWriteErrorCount,"Sans Serif",9,0,0,0,0);

  pvQLabel(p,labelReadErrorCount,obj6);
  pvSetGeometry(p,labelReadErrorCount,5,145,625,15);
  pvSetText(p,labelReadErrorCount,pvtr("readErrorCount"));
  pvSetFont(p,labelReadErrorCount,"Sans Serif",9,0,0,0,0);

  pvQLabel(p,obj7,0);
  pvSetGeometry(p,obj7,10,10,1005,35);
  pvSetText(p,obj7,pvtr("OPC UA Example using opc.tcp://localhost:16664"));
  pvSetFont(p,obj7,"Sans Serif",14,1,0,0,0);


  pvEndDefinition(p);
  return 0;
}

// _end_of_generated_area_ (do not edit -> use ui2pvc) ---------------------

#include "mask1_slots.h"

static int defineMask(PARAM *p)
{
  if(p == NULL) return 1;
  generated_defineMask(p);
  // (todo: add your code here)
  return 0;
}


static int showData(PARAM *p, DATA *d)
{
  if(p == NULL) return 1;
  if(d == NULL) return 1;
  return 0;
}

static int readData(DATA *d) // from shared memory, database or something else
{
  if(d == NULL) return 1;
  // (todo: add your code here)
  return 0;
}


int show_mask1(PARAM *p)
{
  DATA d;
  char event[MAX_EVENT_LENGTH];
  char text[MAX_EVENT_LENGTH];
  char str1[MAX_EVENT_LENGTH];
  int  i,w,h,val,x,y,button,ret;
  float xval, yval;

  defineMask(p);
  //rlSetDebugPrintf(1);
  if((ret=slotInit(p,&d)) != 0) return ret;
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
        if((ret=slotNullEvent(p,&d)) != 0) return ret;
        break;
      case BUTTON_EVENT:
        printf("BUTTON_EVENT id=%d\n",i);
        if((ret=slotButtonEvent(p,i,&d)) != 0) return ret;
        break;
      case BUTTON_PRESSED_EVENT:
        printf("BUTTON_PRESSED_EVENT id=%d\n",i);
        if((ret=slotButtonPressedEvent(p,i,&d)) != 0) return ret;
        break;
      case BUTTON_RELEASED_EVENT:
        printf("BUTTON_RELEASED_EVENT id=%d\n",i);
        if((ret=slotButtonReleasedEvent(p,i,&d)) != 0) return ret;
        break;
      case TEXT_EVENT:
        printf("TEXT_EVENT id=%d %s\n",i,text);
        if((ret=slotTextEvent(p,i,&d,text)) != 0) return ret;
        break;
      case SLIDER_EVENT:
        sscanf(text,"(%d)",&val);
        printf("SLIDER_EVENT val=%d\n",val);
        if((ret=slotSliderEvent(p,i,&d,val)) != 0) return ret;
        break;
      case CHECKBOX_EVENT:
        printf("CHECKBOX_EVENT id=%d %s\n",i,text);
        if((ret=slotCheckboxEvent(p,i,&d,text)) != 0) return ret;
        break;
      case RADIOBUTTON_EVENT:
        printf("RADIOBUTTON_EVENT id=%d %s\n",i,text);
        if((ret=slotRadioButtonEvent(p,i,&d,text)) != 0) return ret;
        break;
      case GL_INITIALIZE_EVENT:
        printf("you have to call initializeGL()\n");
        if((ret=slotGlInitializeEvent(p,i,&d)) != 0) return ret;
        break;
      case GL_PAINT_EVENT:
        printf("you have to call paintGL()\n");
        if((ret=slotGlPaintEvent(p,i,&d)) != 0) return ret;
        break;
      case GL_RESIZE_EVENT:
        sscanf(text,"(%d,%d)",&w,&h);
        printf("you have to call resizeGL(w,h)\n");
        if((ret=slotGlResizeEvent(p,i,&d,w,h)) != 0) return ret;
        break;
      case GL_IDLE_EVENT:
        if((ret=slotGlIdleEvent(p,i,&d)) != 0) return ret;
        break;
      case TAB_EVENT:
        sscanf(text,"(%d)",&val);
        printf("TAB_EVENT(%d,page=%d)\n",i,val);
        if((ret=slotTabEvent(p,i,&d,val)) != 0) return ret;
        break;
      case TABLE_TEXT_EVENT:
        sscanf(text,"(%d,%d,",&x,&y);
        pvGetText(text,str1);
        printf("TABLE_TEXT_EVENT(%d,%d,\"%s\")\n",x,y,str1);
        if((ret=slotTableTextEvent(p,i,&d,x,y,str1)) != 0) return ret;
        break;
      case TABLE_CLICKED_EVENT:
        sscanf(text,"(%d,%d,%d)",&x,&y,&button);
        printf("TABLE_CLICKED_EVENT(%d,%d,button=%d)\n",x,y,button);
        if((ret=slotTableClickedEvent(p,i,&d,x,y,button)) != 0) return ret;
        break;
      case SELECTION_EVENT:
        sscanf(text,"(%d,",&val);
        pvGetText(text,str1);
        printf("SELECTION_EVENT(column=%d,\"%s\")\n",val,str1);
        if((ret=slotSelectionEvent(p,i,&d,val,str1)) != 0) return ret;
        break;
      case CLIPBOARD_EVENT:
        sscanf(text,"(%d",&val);
        printf("CLIPBOARD_EVENT(id=%d)\n",val);
        printf("clipboard = \n%s\n",p->clipboard);
        if((ret=slotClipboardEvent(p,i,&d,val)) != 0) return ret;
        break;
      case RIGHT_MOUSE_EVENT:
        printf("RIGHT_MOUSE_EVENT id=%d text=%s\n",i,text);
        if((ret=slotRightMouseEvent(p,i,&d,text)) != 0) return ret;
        break;
      case KEYBOARD_EVENT:
        sscanf(text,"(%d",&val);
        printf("KEYBOARD_EVENT modifier=%d key=%d\n",i,val);
        if((ret=slotKeyboardEvent(p,i,&d,val,i)) != 0) return ret;
        break;
      case PLOT_MOUSE_MOVED_EVENT:
        sscanf(text,"(%f,%f)",&xval,&yval);
        printf("PLOT_MOUSE_MOVE %f %f\n",xval,yval);
        if((ret=slotMouseMovedEvent(p,i,&d,xval,yval)) != 0) return ret;
        break;
      case PLOT_MOUSE_PRESSED_EVENT:
        sscanf(text,"(%f,%f)",&xval,&yval);
        printf("PLOT_MOUSE_PRESSED %f %f\n",xval,yval);
        if((ret=slotMousePressedEvent(p,i,&d,xval,yval)) != 0) return ret;
        break;
      case PLOT_MOUSE_RELEASED_EVENT:
        sscanf(text,"(%f,%f)",&xval,&yval);
        printf("PLOT_MOUSE_RELEASED %f %f\n",xval,yval);
        if((ret=slotMouseReleasedEvent(p,i,&d,xval,yval)) != 0) return ret;
        break;
      case MOUSE_OVER_EVENT:
        sscanf(text,"%d",&val);
        printf("MOUSE_OVER_EVENT %d\n",val);
        if((ret=slotMouseOverEvent(p,i,&d,val)) != 0) return ret;
        break;
      case USER_EVENT:
        printf("USER_EVENT id=%d %s\n",i,text);
        if((ret=slotUserEvent(p,i,&d,text)) != 0) return ret;
        break;
      default:
        printf("UNKNOWN_EVENT id=%d %s\n",i,text);
        break;
    }
  }
}
