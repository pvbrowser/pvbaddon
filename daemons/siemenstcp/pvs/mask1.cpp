////////////////////////////////////////////////////////////////////////////
//
// show_mask1 for ProcessViewServer created: Do Jan 17 17:06:13 2008
//
////////////////////////////////////////////////////////////////////////////
#include "pvapp.h"

// _begin_of_generated_area_ (do not edit -> use ui2pvc) -------------------

// our mask contains the following objects
enum {
  ID_MAIN_WIDGET = 0,
  obj1,
  obj2,
  obj3,
  obj4,
  obj5,
  obj6,
  obj7,
  buttonList,
  obj8,
  obj9,
  obj10,
  obj11,
  obj12,
  obj13,
  obj14,
  spinByte,
  spinInt,
  spinFloat,
  spinBit,
  obj15,
  obj16,
  bit0,
  bit1,
  bit2,
  bit3,
  bit4,
  bit5,
  bit6,
  bit7,
  bit_0_1_2,
  buttonSet0,
  ID_END_OF_WIDGETS
};

  static const char *toolTip[] = {
  "",
  "byteORG_M(0,0,0)",
  "byteORG_M(0,0,1)",
  "byteORG_M(0,0,2)",
  "byteORG_M(0,0,3)",
  "byteORG_M(0,0,4)",
  "byteORG_M(0,0,5)",
  "byteORG_M(0,0,6)",
  "",
  "byteORG_M(0,0,7)",
  "byteORG_M(0,0,8)",
  "byteORG_M(0,0,9)",
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
  "",
  ""};

  static const int widgetType[ID_END_OF_WIDGETS+1] = {
  0,
  TQLabel,
  TQLabel,
  TQLabel,
  TQLabel,
  TQLabel,
  TQLabel,
  TQLabel,
  TQPushButton,
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
  TQSpinBox,
  TQLabel,
  TQGroupBox,
  TQRadio,
  TQRadio,
  TQRadio,
  TQRadio,
  TQRadio,
  TQRadio,
  TQRadio,
  TQRadio,
  TQRadio,
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

  pvQLabel(p,obj1,0);
  pvSetGeometry(p,obj1,10,10,345,30);
  pvSetText(p,obj1,"Label");
  pvToolTip(p,obj1,"byteORG_M(0,0,0)");

  pvQLabel(p,obj2,0);
  pvSetGeometry(p,obj2,10,40,345,30);
  pvSetText(p,obj2,"Label");
  pvToolTip(p,obj2,"byteORG_M(0,0,1)");

  pvQLabel(p,obj3,0);
  pvSetGeometry(p,obj3,10,65,345,30);
  pvSetText(p,obj3,"Label");
  pvToolTip(p,obj3,"byteORG_M(0,0,2)");

  pvQLabel(p,obj4,0);
  pvSetGeometry(p,obj4,10,90,345,30);
  pvSetText(p,obj4,"Label");
  pvToolTip(p,obj4,"byteORG_M(0,0,3)");

  pvQLabel(p,obj5,0);
  pvSetGeometry(p,obj5,10,115,345,30);
  pvSetText(p,obj5,"Label");
  pvToolTip(p,obj5,"byteORG_M(0,0,4)");

  pvQLabel(p,obj6,0);
  pvSetGeometry(p,obj6,10,140,345,30);
  pvSetText(p,obj6,"Label");
  pvToolTip(p,obj6,"byteORG_M(0,0,5)");

  pvQLabel(p,obj7,0);
  pvSetGeometry(p,obj7,10,165,345,30);
  pvSetText(p,obj7,"Label");
  pvToolTip(p,obj7,"byteORG_M(0,0,6)");

  pvQPushButton(p,buttonList,0);
  pvSetGeometry(p,buttonList,355,10,130,30);
  pvSetText(p,buttonList,"List");

  pvQLabel(p,obj8,0);
  pvSetGeometry(p,obj8,10,190,345,30);
  pvSetText(p,obj8,"Label");
  pvToolTip(p,obj8,"byteORG_M(0,0,7)");

  pvQLabel(p,obj9,0);
  pvSetGeometry(p,obj9,10,215,345,30);
  pvSetText(p,obj9,"Label");
  pvToolTip(p,obj9,"byteORG_M(0,0,8)");

  pvQLabel(p,obj10,0);
  pvSetGeometry(p,obj10,10,240,345,30);
  pvSetText(p,obj10,"Label");
  pvToolTip(p,obj10,"byteORG_M(0,0,9)");

  pvQLabel(p,obj11,0);
  pvSetGeometry(p,obj11,355,50,60,30);
  pvSetText(p,obj11,"Bit");

  pvQLabel(p,obj12,0);
  pvSetGeometry(p,obj12,355,85,60,30);
  pvSetText(p,obj12,"Byte");

  pvQLabel(p,obj13,0);
  pvSetGeometry(p,obj13,355,120,60,30);
  pvSetText(p,obj13,"Int");

  pvQLabel(p,obj14,0);
  pvSetGeometry(p,obj14,355,155,60,30);
  pvSetText(p,obj14,"Float");

  pvQSpinBox(p,spinByte,0,0,255,1);
  pvSetGeometry(p,spinByte,430,85,100,30);

  pvQSpinBox(p,spinInt,0,0,10000,1);
  pvSetGeometry(p,spinInt,430,120,100,30);

  pvQSpinBox(p,spinFloat,0,-100,100,1);
  pvSetGeometry(p,spinFloat,430,155,100,30);

  pvQSpinBox(p,spinBit,0,0,1,1);
  pvSetGeometry(p,spinBit,430,50,100,30);

  pvQLabel(p,obj15,0);
  pvSetGeometry(p,obj15,540,105,280,35);
  pvSetText(p,obj15,"set ORG_M, slave=1, dbnum=0, adr=0");

  pvQGroupBox(p,obj16,0,-1,HORIZONTAL,"Bits in Byte 2");
  pvSetGeometry(p,obj16,355,200,285,260);

  pvQRadioButton(p,bit0,obj16);
  pvSetGeometry(p,bit0,5,20,100,30);
  pvSetText(p,bit0,"Bit 0");

  pvQRadioButton(p,bit1,obj16);
  pvSetGeometry(p,bit1,5,45,100,30);
  pvSetText(p,bit1,"Bit 1");

  pvQRadioButton(p,bit2,obj16);
  pvSetGeometry(p,bit2,5,75,100,30);
  pvSetText(p,bit2,"Bit 2");

  pvQRadioButton(p,bit3,obj16);
  pvSetGeometry(p,bit3,5,105,100,30);
  pvSetText(p,bit3,"Bit 3");

  pvQRadioButton(p,bit4,obj16);
  pvSetGeometry(p,bit4,5,135,100,30);
  pvSetText(p,bit4,"Bit 4");

  pvQRadioButton(p,bit5,obj16);
  pvSetGeometry(p,bit5,5,165,100,30);
  pvSetText(p,bit5,"Bit 5");

  pvQRadioButton(p,bit6,obj16);
  pvSetGeometry(p,bit6,5,195,100,30);
  pvSetText(p,bit6,"Bit 6");

  pvQRadioButton(p,bit7,obj16);
  pvSetGeometry(p,bit7,5,225,100,30);
  pvSetText(p,bit7,"Bit 7");

  pvQRadioButton(p,bit_0_1_2,obj16);
  pvSetGeometry(p,bit_0_1_2,170,20,100,30);
  pvSetText(p,bit_0_1_2,"Bit 0 1 2");

  pvQPushButton(p,buttonSet0,obj16);
  pvSetGeometry(p,buttonSet0,170,60,100,30);
  pvSetText(p,buttonSet0,"Set value=0");


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
