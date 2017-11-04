////////////////////////////////////////////////////////////////////////////
//
// show_mask1 for ProcessViewServer created: Mi Sep 16 09:47:34 2009
//
////////////////////////////////////////////////////////////////////////////
#include "pvapp.h"

// _begin_of_generated_area_ (do not edit -> use ui2pvc) -------------------

// our mask contains the following objects
enum {
  ID_MAIN_WIDGET = 0,
  upperWidget,
  leftWidget,
  centerWidget,
  rightWidget,
  obj1,
  iCenter,
  iUp,
  iDown,
  iLeft,
  iRight,
  sliderZoom,
  pbPrintHtml,
  layout1,
  layout2,
  ID_END_OF_WIDGETS
};

// our mask contains the following widget names
  static const char *widgetName[] = {
  "ID_MAIN_WIDGET",
  "upperWidget",
  "leftWidget",
  "centerWidget",
  "rightWidget",
  "obj1",
  "iCenter",
  "iUp",
  "iDown",
  "iLeft",
  "iRight",
  "sliderZoom",
  "pbPrintHtml",
  "layout1",
  "layout2",
  "ID_END_OF_WIDGETS",
  ""};

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
  ""};

  static const char *whatsThis[] = {
  "",
  "",
  "",
  "test.svg",
  "",
  "",
  "1center.png",
  "1uparrow.png",
  "1downarrow.png",
  "1leftarrow.png",
  "1rightarrow.png",
  "",
  "",
  ""};

  static const int widgetType[ID_END_OF_WIDGETS+1] = {
  0,
  TQTextBrowser,
  TQTextBrowser,
  TQDraw,
  TQGroupBox,
  TQLabel,
  TQImage,
  TQImage,
  TQImage,
  TQImage,
  TQImage,
  TQSlider,
  TQPushButton,
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

  pvQTextBrowser(p,upperWidget,0);
  pvSetGeometry(p,upperWidget,5,5,945,200);
  pvSetFont(p,upperWidget,"Sans Serif",10,0,0,0,0);
  pvSetMinSize(p,upperWidget,0,200);
  pvSetMaxSize(p,upperWidget,99999,200);

  pvQTextBrowser(p,leftWidget,0);
  pvSetGeometry(p,leftWidget,5,215,200,445);
  pvSetFont(p,leftWidget,"Sans Serif",10,0,0,0,0);
  pvSetMinSize(p,leftWidget,200,100);
  pvSetMaxSize(p,leftWidget,200,99999);

  pvQDraw(p,centerWidget,0);
  pvSetGeometry(p,centerWidget,190,215,580,425);
  pvSetFont(p,centerWidget,"Sans Serif",10,0,0,0,0);
  pvSetWhatsThis(p,centerWidget,pvtr("test.svg"));
  pvSetMinSize(p,centerWidget,300,100);

  pvQGroupBox(p,rightWidget,0,-1,HORIZONTAL,pvtr("Tools"));
  pvSetGeometry(p,rightWidget,780,210,200,450);
  pvSetFont(p,rightWidget,"Sans Serif",10,0,0,0,0);
  pvSetMinSize(p,rightWidget,200,100);
  pvSetMaxSize(p,rightWidget,200,99999);

  pvQLabel(p,obj1,rightWidget);
  pvSetGeometry(p,obj1,10,150,145,35);
  pvSetText(p,obj1,pvtr("Put your tools here"));
  pvSetFont(p,obj1,"Sans Serif",10,0,0,0,0);

  pvDownloadFile(p,"1center.png");
  pvQImage(p,iCenter,rightWidget,"1center.png",&w,&h,&depth);
  pvSetGeometry(p,iCenter,35,65,22,22);
  pvSetFont(p,iCenter,"Sans Serif",10,0,0,0,0);
  pvSetWhatsThis(p,iCenter,pvtr("1center.png"));

  pvDownloadFile(p,"1uparrow.png");
  pvQImage(p,iUp,rightWidget,"1uparrow.png",&w,&h,&depth);
  pvSetGeometry(p,iUp,35,40,22,22);
  pvSetFont(p,iUp,"Sans Serif",10,0,0,0,0);
  pvSetWhatsThis(p,iUp,pvtr("1uparrow.png"));

  pvDownloadFile(p,"1downarrow.png");
  pvQImage(p,iDown,rightWidget,"1downarrow.png",&w,&h,&depth);
  pvSetGeometry(p,iDown,35,90,22,22);
  pvSetFont(p,iDown,"Sans Serif",10,0,0,0,0);
  pvSetWhatsThis(p,iDown,pvtr("1downarrow.png"));

  pvDownloadFile(p,"1leftarrow.png");
  pvQImage(p,iLeft,rightWidget,"1leftarrow.png",&w,&h,&depth);
  pvSetGeometry(p,iLeft,10,65,22,22);
  pvSetFont(p,iLeft,"Sans Serif",10,0,0,0,0);
  pvSetWhatsThis(p,iLeft,pvtr("1leftarrow.png"));

  pvDownloadFile(p,"1rightarrow.png");
  pvQImage(p,iRight,rightWidget,"1rightarrow.png",&w,&h,&depth);
  pvSetGeometry(p,iRight,60,65,22,22);
  pvSetFont(p,iRight,"Sans Serif",10,0,0,0,0);
  pvSetWhatsThis(p,iRight,pvtr("1rightarrow.png"));

  pvQSlider(p,sliderZoom,rightWidget,10,200,1,10,Vertical);
  pvSetGeometry(p,sliderZoom,125,30,25,100);
  pvSetFont(p,sliderZoom,"Sans Serif",10,0,0,0,0);

  pvQPushButton(p,pbPrintHtml,rightWidget);
  pvSetGeometry(p,pbPrintHtml,10,210,100,30);
  pvSetText(p,pbPrintHtml,pvtr("&PrintHtml"));
  pvSetFont(p,pbPrintHtml,"Sans Serif",10,0,0,0,0);

  pvQLayoutHbox(p,ID_MAIN_WIDGET,-1);

  pvQLayoutVbox(p,layout1,-1);

  pvQLayoutHbox(p,layout2,-1);

  pvAddWidgetOrLayout(p,ID_MAIN_WIDGET,layout1,-1,-1);
  pvAddWidgetOrLayout(p,layout1,upperWidget,-1,-1);
  pvAddWidgetOrLayout(p,layout1,layout2,-1,-1);
  pvAddWidgetOrLayout(p,layout2,leftWidget,-1,-1);
  pvAddWidgetOrLayout(p,layout2,centerWidget,-1,-1);
  pvAddWidgetOrLayout(p,layout2,rightWidget,-1,-1);

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
        if(trace) printf("BUTTON_EVENT id=%d\n",i);
        if((ret=slotButtonEvent(p,i,&d)) != 0) return ret;
        break;
      case BUTTON_PRESSED_EVENT:
        if(trace) printf("BUTTON_PRESSED_EVENT id=%d\n",i);
        if((ret=slotButtonPressedEvent(p,i,&d)) != 0) return ret;
        break;
      case BUTTON_RELEASED_EVENT:
        if(trace) printf("BUTTON_RELEASED_EVENT id=%d\n",i);
        if((ret=slotButtonReleasedEvent(p,i,&d)) != 0) return ret;
        break;
      case TEXT_EVENT:
        if(trace) printf("TEXT_EVENT id=%d %s\n",i,text);
        if((ret=slotTextEvent(p,i,&d,text)) != 0) return ret;
        break;
      case SLIDER_EVENT:
        sscanf(text,"(%d)",&val);
        if(trace) printf("SLIDER_EVENT val=%d\n",val);
        if((ret=slotSliderEvent(p,i,&d,val)) != 0) return ret;
        break;
      case CHECKBOX_EVENT:
        if(trace) printf("CHECKBOX_EVENT id=%d %s\n",i,text);
        if((ret=slotCheckboxEvent(p,i,&d,text)) != 0) return ret;
        break;
      case RADIOBUTTON_EVENT:
        if(trace) printf("RADIOBUTTON_EVENT id=%d %s\n",i,text);
        if((ret=slotRadioButtonEvent(p,i,&d,text)) != 0) return ret;
        break;
      case GL_INITIALIZE_EVENT:
        if(trace) printf("you have to call initializeGL()\n");
        if((ret=slotGlInitializeEvent(p,i,&d)) != 0) return ret;
        break;
      case GL_PAINT_EVENT:
        if(trace) printf("you have to call paintGL()\n");
        if((ret=slotGlPaintEvent(p,i,&d)) != 0) return ret;
        break;
      case GL_RESIZE_EVENT:
        sscanf(text,"(%d,%d)",&w,&h);
        if(trace) printf("you have to call resizeGL(w,h)\n");
        if((ret=slotGlResizeEvent(p,i,&d,w,h)) != 0) return ret;
        break;
      case GL_IDLE_EVENT:
        if((ret=slotGlIdleEvent(p,i,&d)) != 0) return ret;
        break;
      case TAB_EVENT:
        sscanf(text,"(%d)",&val);
        if(trace) printf("TAB_EVENT(%d,page=%d)\n",i,val);
        if((ret=slotTabEvent(p,i,&d,val)) != 0) return ret;
        break;
      case TABLE_TEXT_EVENT:
        sscanf(text,"(%d,%d,",&x,&y);
        pvGetText(text,str1);
        if(trace) printf("TABLE_TEXT_EVENT(%d,%d,\"%s\")\n",x,y,str1);
        if((ret=slotTableTextEvent(p,i,&d,x,y,str1)) != 0) return ret;
        break;
      case TABLE_CLICKED_EVENT:
        sscanf(text,"(%d,%d,%d)",&x,&y,&button);
        if(trace) printf("TABLE_CLICKED_EVENT(%d,%d,button=%d)\n",x,y,button);
        if((ret=slotTableClickedEvent(p,i,&d,x,y,button)) != 0) return ret;
        break;
      case SELECTION_EVENT:
        sscanf(text,"(%d,",&val);
        pvGetText(text,str1);
        if(trace) printf("SELECTION_EVENT(column=%d,\"%s\")\n",val,str1);
        if((ret=slotSelectionEvent(p,i,&d,val,str1)) != 0) return ret;
        break;
      case CLIPBOARD_EVENT:
        sscanf(text,"(%d",&val);
        if(trace) printf("CLIPBOARD_EVENT(id=%d)\n",val);
        if(trace) printf("clipboard = \n%s\n",p->clipboard);
        if((ret=slotClipboardEvent(p,i,&d,val)) != 0) return ret;
        break;
      case RIGHT_MOUSE_EVENT:
        if(trace) printf("RIGHT_MOUSE_EVENT id=%d text=%s\n",i,text);
        if((ret=slotRightMouseEvent(p,i,&d,text)) != 0) return ret;
        break;
      case KEYBOARD_EVENT:
        sscanf(text,"(%d",&val);
        if(trace) printf("KEYBOARD_EVENT modifier=%d key=%d\n",i,val);
        if((ret=slotKeyboardEvent(p,i,&d,val,i)) != 0) return ret;
        break;
      case PLOT_MOUSE_MOVED_EVENT:
        sscanf(text,"(%f,%f)",&xval,&yval);
        if(trace) printf("PLOT_MOUSE_MOVE %f %f\n",xval,yval);
        if((ret=slotMouseMovedEvent(p,i,&d,xval,yval)) != 0) return ret;
        break;
      case PLOT_MOUSE_PRESSED_EVENT:
        sscanf(text,"(%f,%f)",&xval,&yval);
        if(trace) printf("PLOT_MOUSE_PRESSED %f %f\n",xval,yval);
        if((ret=slotMousePressedEvent(p,i,&d,xval,yval)) != 0) return ret;
        break;
      case PLOT_MOUSE_RELEASED_EVENT:
        sscanf(text,"(%f,%f)",&xval,&yval);
        if(trace) printf("PLOT_MOUSE_RELEASED %f %f\n",xval,yval);
        if((ret=slotMouseReleasedEvent(p,i,&d,xval,yval)) != 0) return ret;
        break;
      case MOUSE_OVER_EVENT:
        sscanf(text,"%d",&val);
        if(trace) printf("MOUSE_OVER_EVENT %d\n",val);
        if((ret=slotMouseOverEvent(p,i,&d,val)) != 0) return ret;
        break;
      case USER_EVENT:
        if(trace) printf("USER_EVENT id=%d %s\n",i,text);
        if((ret=slotUserEvent(p,i,&d,text)) != 0) return ret;
        break;
      default:
        if(trace) printf("UNKNOWN_EVENT id=%d %s\n",i,text);
        break;
    }
  }
}
