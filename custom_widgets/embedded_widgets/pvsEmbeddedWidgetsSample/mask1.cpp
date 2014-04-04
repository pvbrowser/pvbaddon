////////////////////////////////////////////////////////////////////////////
//
// show_mask1 for ProcessViewServer created: lun abr 30 10:56:28 2012
//
////////////////////////////////////////////////////////////////////////////
#include "pvapp.h"

// _begin_of_generated_area_ (do not edit -> use ui2pvc) -------------------

// our mask contains the following objects
enum {
  ID_MAIN_WIDGET = 0,
  thermometer,
  slider_therm,
  slider_tacho,
  multislider,
  slider_multislider,
  tachometer,
  amperemeter,
  slider_amp,
  slide_check,
  toggle_switch,
  button_square,
  button_circular,
  my5waybutton,
  aDial,
  ID_END_OF_WIDGETS
};

  static const char *toolTip[] = {
  "",
  "myQtSvgDialGaugeThermometer",
  "myQtScrollWheel",
  "myQtScrollDial",
  "myQtMultiSlider",
  "myQtScrollDial",
  "myQtSvgDialGaugeTachometer",
  "myQtSvgDialGaugeAmperemeter",
  "myQtScrollDial",
  "myQtSvgSlideSwitch",
  "myQtSvgToggleSwitch",
  "myQtSvgButtonBerylSquare",
  "myQtSvgButtonBeryl",
  "myQt5WayButton",
  "Set whatsThis='/library/ScrollDial'",
  ""};

  static const char *whatsThis[] = {
  "",
  "/ewidgets/myQtSvgDialGaugeThermometer:arguments",
  "/ewidgets/myQtScrollWheel:arg1,arg2",
  "/ewidgets/myQtScrollDial:arguments",
  "/ewidgets/myQtMultiSlider:arguments",
  "/ewidgets/myQtScrollDial:arguments",
  "/ewidgets/myQtSvgDialGaugeTachometer:arguments",
  "/ewidgets/myQtSvgDialGaugeAmperemeter:arguments",
  "/ewidgets/myQtScrollDial:arguments",
  "/ewidgets/myQtSvgSlideSwitch:arguments",
  "/ewidgets/myQtSvgToggleSwitch:arguments",
  "/ewidgets/myQtSvgButtonBerylSquare:arguments",
  "/ewidgets/myQtSvgButtonBeryl:",
  "/ewidgets/myQt5WayButton",
  "/ewidgets/myQtScrollDial",
  ""};

  static const int widgetType[ID_END_OF_WIDGETS+1] = {
  0,
  TQCustomWidget,
  TQCustomWidget,
  TQCustomWidget,
  TQCustomWidget,
  TQCustomWidget,
  TQCustomWidget,
  TQCustomWidget,
  TQCustomWidget,
  TQCustomWidget,
  TQCustomWidget,
  TQCustomWidget,
  TQCustomWidget,
  TQCustomWidget,
  TQCustomWidget,
  -1 };

static int generated_defineMask(PARAM *p)
{
  int w,h,depth;

  if(p == NULL) return 1;
  w = h = depth = strcmp(toolTip[0],whatsThis[0]);
  if(widgetType[0] == -1) return 1;
  if(w==h) depth=0; // fool the compiler
  pvStartDefinition(p,ID_END_OF_WIDGETS);

  pvQCustomWidget(p,thermometer,0,"/ewidgets/myQtSvgDialGaugeThermometer","arguments");
  pvSetGeometry(p,thermometer,81,48,261,222);
  pvToolTip(p,thermometer,"myQtSvgDialGaugeThermometer");
  pvSetWhatsThis(p,thermometer,"/ewidgets/myQtSvgDialGaugeThermometer:arguments");

  pvQCustomWidget(p,slider_therm,0,"/ewidgets/myQtScrollWheel","arg1,arg2");
  pvSetGeometry(p,slider_therm,30,96,39,123);
  pvToolTip(p,slider_therm,"myQtScrollWheel");
  pvSetWhatsThis(p,slider_therm,"/ewidgets/myQtScrollWheel:arg1,arg2");

  pvQCustomWidget(p,slider_tacho,0,"/ewidgets/myQtScrollDial","arguments");
  pvSetGeometry(p,slider_tacho,366,111,84,78);
  pvToolTip(p,slider_tacho,"myQtScrollDial");
  pvSetWhatsThis(p,slider_tacho,"/ewidgets/myQtScrollDial:arguments");

  pvQCustomWidget(p,multislider,0,"/ewidgets/myQtMultiSlider","arguments");
  pvSetGeometry(p,multislider,117,354,159,198);
  pvToolTip(p,multislider,"myQtMultiSlider");
  pvSetWhatsThis(p,multislider,"/ewidgets/myQtMultiSlider:arguments");

  pvQCustomWidget(p,slider_multislider,0,"/ewidgets/myQtScrollDial","arguments");
  pvSetGeometry(p,slider_multislider,18,399,87,96);
  pvToolTip(p,slider_multislider,"myQtScrollDial");
  pvSetWhatsThis(p,slider_multislider,"/ewidgets/myQtScrollDial:arguments");

  pvQCustomWidget(p,tachometer,0,"/ewidgets/myQtSvgDialGaugeTachometer","arguments");
  pvSetGeometry(p,tachometer,462,60,231,216);
  pvToolTip(p,tachometer,"myQtSvgDialGaugeTachometer");
  pvSetWhatsThis(p,tachometer,"/ewidgets/myQtSvgDialGaugeTachometer:arguments");

  pvQCustomWidget(p,amperemeter,0,"/ewidgets/myQtSvgDialGaugeAmperemeter","arguments");
  pvSetGeometry(p,amperemeter,408,372,204,156);
  pvToolTip(p,amperemeter,"myQtSvgDialGaugeAmperemeter");
  pvSetWhatsThis(p,amperemeter,"/ewidgets/myQtSvgDialGaugeAmperemeter:arguments");

  pvQCustomWidget(p,slider_amp,0,"/ewidgets/myQtScrollDial","arguments");
  pvSetGeometry(p,slider_amp,312,411,78,81);
  pvToolTip(p,slider_amp,"myQtScrollDial");
  pvSetWhatsThis(p,slider_amp,"/ewidgets/myQtScrollDial:arguments");

  pvQCustomWidget(p,slide_check,0,"/ewidgets/myQtSvgSlideSwitch","arguments");
  pvSetGeometry(p,slide_check,219,591,87,72);
  pvToolTip(p,slide_check,"myQtSvgSlideSwitch");
  pvSetWhatsThis(p,slide_check,"/ewidgets/myQtSvgSlideSwitch:arguments");

  pvQCustomWidget(p,toggle_switch,0,"/ewidgets/myQtSvgToggleSwitch","arguments");
  pvSetGeometry(p,toggle_switch,345,585,93,78);
  pvToolTip(p,toggle_switch,"myQtSvgToggleSwitch");
  pvSetWhatsThis(p,toggle_switch,"/ewidgets/myQtSvgToggleSwitch:arguments");

  pvQCustomWidget(p,button_square,0,"/ewidgets/myQtSvgButtonBerylSquare","arguments");
  pvSetGeometry(p,button_square,24,594,63,63);
  pvToolTip(p,button_square,"myQtSvgButtonBerylSquare");
  pvSetWhatsThis(p,button_square,"/ewidgets/myQtSvgButtonBerylSquare:arguments");

  pvQCustomWidget(p,button_circular,0,"/ewidgets/myQtSvgButtonBeryl","");
  pvSetGeometry(p,button_circular,117,594,69,66);
  pvToolTip(p,button_circular,"myQtSvgButtonBeryl");
  pvSetWhatsThis(p,button_circular,"/ewidgets/myQtSvgButtonBeryl:");

  pvQCustomWidget(p,my5waybutton,0,"/ewidgets/myQt5WayButton");
  pvSetGeometry(p,my5waybutton,735,100,155,140);
  pvSetFont(p,my5waybutton,"Sans Serif",10,0,0,0,0);
  pvToolTip(p,my5waybutton,"myQt5WayButton");
  pvSetWhatsThis(p,my5waybutton,"/ewidgets/myQt5WayButton");

  pvQCustomWidget(p,aDial,0,"/ewidgets/myQtScrollDial");
  pvSetGeometry(p,aDial,635,410,70,70);
  pvSetFont(p,aDial,"Sans Serif",10,0,0,0,0);
  pvToolTip(p,aDial,"Set whatsThis='/library/ScrollDial'");
  pvSetWhatsThis(p,aDial,"/ewidgets/myQtScrollDial");


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
  //set range values for sliders
  pvSetMinValue(p,slider_therm,-30);
  pvSetMaxValue(p,slider_therm,50);
  pvSetValue(p,slider_therm,0);

  //pvSetMinValue(p,slider_tacho,0);
  pvSetMaxValue(p,slider_tacho,120);

 
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
  pvClearMessageQueue(p);
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
