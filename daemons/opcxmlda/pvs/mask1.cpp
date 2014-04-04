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
  obj15,
  obj16,
  obj17,
  obj20,
  obj21,
  obj22,
  obj18,
  obj19,
  obj3,
  obj23,
  obj24,
  obj25,
  obj26,
  obj27,
  obj32,
  obj33,
  obj34,
  obj35,
  obj36,
  obj37,
  obj28,
  obj29,
  obj30,
  obj31,
  obj4,
  obj38,
  obj39,
  obj40,
  obj41,
  obj42,
  obj43,
  obj46,
  obj47,
  obj48,
  obj49,
  obj50,
  obj52,
  obj51,
  obj53,
  obj5,
  obj54,
  obj55,
  obj56,
  obj57,
  obj58,
  obj59,
  obj60,
  obj61,
  obj62,
  obj63,
  obj64,
  obj65,
  obj66,
  obj6,
  testInt16,
  testInt32,
  testFloat,
  testDouble,
  testString,
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

  static const char *toolTip[] = {
  "",
  "",
  "",
  "Pump1/DS_Devicename",
  "Pump1/DS_DeviceID",
  "Pump1/DeviceType",
  "Pump1/DS_Vendorname",
  "Pump1/ProfileID",
  "Pump1/SW_Rev",
  "Pump1/HW_Rev",
  "Pump1/Ser_Num",
  "Pump1/Descriptor",
  "Pump1/Dev_Instal_Date",
  "Pump1/Revolutions",
  "Pump1/Capacity",
  "Pump1/Gain",
  "Pump1/Dev_Message",
  "Pump1/ThroughPut",
  "",
  "Pump2/DS_Devicename",
  "Pump2/DS_DeviceID",
  "Pump2/DeviceType",
  "Pump2/DS_Vendorname",
  "Pump2/ProfileID",
  "Pump2/Dev_Instal_Date",
  "Pump2/Dev_Message",
  "Pump2/ThroughPut",
  "Pump2/Revolutions",
  "Pump2/Capacity",
  "Pump2/Gain",
  "Pump2/SW_Rev",
  "Pump2/HW_Rev",
  "Pump2/Ser_Num",
  "Pump2/Descriptor",
  "",
  "Level1/DS_Devicename",
  "Level1/DS_DeviceID",
  "Level1/DeviceType",
  "Level1/DS_Vendorname",
  "Level1/ProfileID",
  "Level1/SW_Rev",
  "Level1/HW_Rev",
  "Level1/Ser_Num",
  "Level1/Descriptor",
  "Level1/Dev_Instal_Date",
  "Level1/Dev_Message",
  "Level1/Hi_Lim",
  "Level1/Out",
  "Level1/Lo_LIM",
  "",
  "Level2/DS_Devicename",
  "Level2/DS_DeviceID",
  "Level2/DeviceType",
  "Level2/DS_Vendorname",
  "Level2/ProfileID",
  "Level2/SW_Rev",
  "Level2/HW_Rev",
  "Level2/Ser_Num",
  "Level2/Descriptor",
  "Level2/Dev_Instal_Date",
  "Level2/Dev_Message",
  "Level2/Out",
  "Level2/Target",
  "",
  "test/Int16",
  "test/Int32",
  "test/float",
  "test/double",
  "test/string",
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

static int generated_defineMask(PARAM *p)
{
  int w,h,depth;

  if(p == NULL) return 1;
  w = h = depth = strcmp(toolTip[0],whatsThis[0]);
  if(w==h) depth=0; // fool the compiler
  pvStartDefinition(p,ID_END_OF_WIDGETS);

  pvQTabWidget(p,obj2,0);
  pvSetGeometry(p,obj2,10,50,770,540);

  pvQWidget(p,obj1,obj2);
  pvAddTab(p,obj2,obj1,"Pump1");

  pvQLabel(p,obj8,obj1);
  pvSetGeometry(p,obj8,5,15,750,15);
  pvSetText(p,obj8,"Pump1/DS_Devicename");
  pvToolTip(p,obj8,"Pump1/DS_Devicename");

  pvQLabel(p,obj9,obj1);
  pvSetGeometry(p,obj9,5,30,720,15);
  pvSetText(p,obj9,"Pump1/DS_DeviceID");
  pvToolTip(p,obj9,"Pump1/DS_DeviceID");

  pvQLabel(p,obj10,obj1);
  pvSetGeometry(p,obj10,5,45,740,15);
  pvSetText(p,obj10,"Pump1/DeviceType");
  pvToolTip(p,obj10,"Pump1/DeviceType");

  pvQLabel(p,obj11,obj1);
  pvSetGeometry(p,obj11,5,60,735,15);
  pvSetText(p,obj11,"Pump1/DS_Vendorname");
  pvToolTip(p,obj11,"Pump1/DS_Vendorname");

  pvQLabel(p,obj12,obj1);
  pvSetGeometry(p,obj12,5,75,745,15);
  pvSetText(p,obj12,"Pump1/ProfileID");
  pvToolTip(p,obj12,"Pump1/ProfileID");

  pvQLabel(p,obj13,obj1);
  pvSetGeometry(p,obj13,5,90,735,15);
  pvSetText(p,obj13,"Pump1/SW_Rev");
  pvToolTip(p,obj13,"Pump1/SW_Rev");

  pvQLabel(p,obj14,obj1);
  pvSetGeometry(p,obj14,5,105,740,15);
  pvSetText(p,obj14,"Pump1/HW_Rev");
  pvToolTip(p,obj14,"Pump1/HW_Rev");

  pvQLabel(p,obj15,obj1);
  pvSetGeometry(p,obj15,5,120,745,15);
  pvSetText(p,obj15,"Pump1/Ser_Num");
  pvToolTip(p,obj15,"Pump1/Ser_Num");

  pvQLabel(p,obj16,obj1);
  pvSetGeometry(p,obj16,5,135,740,15);
  pvSetText(p,obj16,"Pump1/Descriptor");
  pvToolTip(p,obj16,"Pump1/Descriptor");

  pvQLabel(p,obj17,obj1);
  pvSetGeometry(p,obj17,5,150,745,15);
  pvSetText(p,obj17,"Pump1/Dev_Instal_Date");
  pvToolTip(p,obj17,"Pump1/Dev_Instal_Date");

  pvQLabel(p,obj20,obj1);
  pvSetGeometry(p,obj20,5,195,740,15);
  pvSetText(p,obj20,"Pump1/Revolutions");
  pvToolTip(p,obj20,"Pump1/Revolutions");

  pvQLabel(p,obj21,obj1);
  pvSetGeometry(p,obj21,5,210,720,15);
  pvSetText(p,obj21,"Pump1/Capacity");
  pvToolTip(p,obj21,"Pump1/Capacity");

  pvQLabel(p,obj22,obj1);
  pvSetGeometry(p,obj22,5,225,735,15);
  pvSetText(p,obj22,"Pump1/Gain");
  pvToolTip(p,obj22,"Pump1/Gain");

  pvQLabel(p,obj18,obj1);
  pvSetGeometry(p,obj18,5,165,745,15);
  pvSetText(p,obj18,"Pump1/Dev_Message");
  pvToolTip(p,obj18,"Pump1/Dev_Message");

  pvQLabel(p,obj19,obj1);
  pvSetGeometry(p,obj19,5,180,730,15);
  pvSetText(p,obj19,"Pump1/ThroughPut");
  pvToolTip(p,obj19,"Pump1/ThroughPut");

  pvQWidget(p,obj3,obj2);
  pvAddTab(p,obj2,obj3,"Pump2");

  pvQLabel(p,obj23,obj3);
  pvSetGeometry(p,obj23,5,5,735,15);
  pvSetText(p,obj23,"Pump2/DS_Devicename");
  pvToolTip(p,obj23,"Pump2/DS_Devicename");

  pvQLabel(p,obj24,obj3);
  pvSetGeometry(p,obj24,5,20,730,15);
  pvSetText(p,obj24,"Pump2/DS_DeviceID");
  pvToolTip(p,obj24,"Pump2/DS_DeviceID");

  pvQLabel(p,obj25,obj3);
  pvSetGeometry(p,obj25,5,35,735,15);
  pvSetText(p,obj25,"Pump2/DeviceType");
  pvToolTip(p,obj25,"Pump2/DeviceType");

  pvQLabel(p,obj26,obj3);
  pvSetGeometry(p,obj26,5,50,740,15);
  pvSetText(p,obj26,"Pump2/DS_Vendorname");
  pvToolTip(p,obj26,"Pump2/DS_Vendorname");

  pvQLabel(p,obj27,obj3);
  pvSetGeometry(p,obj27,5,65,750,15);
  pvSetText(p,obj27,"Pump2/ProfileID");
  pvToolTip(p,obj27,"Pump2/ProfileID");

  pvQLabel(p,obj32,obj3);
  pvSetGeometry(p,obj32,5,140,745,15);
  pvSetText(p,obj32,"Pump2/Dev_Instal_Date");
  pvToolTip(p,obj32,"Pump2/Dev_Instal_Date");

  pvQLabel(p,obj33,obj3);
  pvSetGeometry(p,obj33,5,155,750,15);
  pvSetText(p,obj33,"Pump2/Dev_Message");
  pvToolTip(p,obj33,"Pump2/Dev_Message");

  pvQLabel(p,obj34,obj3);
  pvSetGeometry(p,obj34,5,170,745,15);
  pvSetText(p,obj34,"Pump2/ThroughPut");
  pvToolTip(p,obj34,"Pump2/ThroughPut");

  pvQLabel(p,obj35,obj3);
  pvSetGeometry(p,obj35,5,185,740,15);
  pvSetText(p,obj35,"Pump2/Revolutions");
  pvToolTip(p,obj35,"Pump2/Revolutions");

  pvQLabel(p,obj36,obj3);
  pvSetGeometry(p,obj36,5,200,750,15);
  pvSetText(p,obj36,"Pump2/Capacity");
  pvToolTip(p,obj36,"Pump2/Capacity");

  pvQLabel(p,obj37,obj3);
  pvSetGeometry(p,obj37,5,215,750,15);
  pvSetText(p,obj37,"Pump2/Gain");
  pvToolTip(p,obj37,"Pump2/Gain");

  pvQLabel(p,obj28,obj3);
  pvSetGeometry(p,obj28,5,80,750,15);
  pvSetText(p,obj28,"Pump2/SW_Rev");
  pvToolTip(p,obj28,"Pump2/SW_Rev");

  pvQLabel(p,obj29,obj3);
  pvSetGeometry(p,obj29,5,95,725,15);
  pvSetText(p,obj29,"Pump2/HW_Rev");
  pvToolTip(p,obj29,"Pump2/HW_Rev");

  pvQLabel(p,obj30,obj3);
  pvSetGeometry(p,obj30,5,110,750,15);
  pvSetText(p,obj30,"Pump2/Ser_Num");
  pvToolTip(p,obj30,"Pump2/Ser_Num");

  pvQLabel(p,obj31,obj3);
  pvSetGeometry(p,obj31,5,125,750,15);
  pvSetText(p,obj31,"Pump2/Descriptor");
  pvToolTip(p,obj31,"Pump2/Descriptor");

  pvQWidget(p,obj4,obj2);
  pvAddTab(p,obj2,obj4,"Level1");

  pvQLabel(p,obj38,obj4);
  pvSetGeometry(p,obj38,5,10,680,15);
  pvSetText(p,obj38,"Level1/DS_Devicename");
  pvToolTip(p,obj38,"Level1/DS_Devicename");

  pvQLabel(p,obj39,obj4);
  pvSetGeometry(p,obj39,5,25,710,15);
  pvSetText(p,obj39,"Level1/DS_DeviceID");
  pvToolTip(p,obj39,"Level1/DS_DeviceID");

  pvQLabel(p,obj40,obj4);
  pvSetGeometry(p,obj40,5,40,715,15);
  pvSetText(p,obj40,"Level1/DeviceType");
  pvToolTip(p,obj40,"Level1/DeviceType");

  pvQLabel(p,obj41,obj4);
  pvSetGeometry(p,obj41,5,55,710,15);
  pvSetText(p,obj41,"Level1/DS_Vendorname");
  pvToolTip(p,obj41,"Level1/DS_Vendorname");

  pvQLabel(p,obj42,obj4);
  pvSetGeometry(p,obj42,5,70,720,15);
  pvSetText(p,obj42,"Level1/ProfileID");
  pvToolTip(p,obj42,"Level1/ProfileID");

  pvQLabel(p,obj43,obj4);
  pvSetGeometry(p,obj43,5,85,720,15);
  pvSetText(p,obj43,"Level1/SW_Rev");
  pvToolTip(p,obj43,"Level1/SW_Rev");

  pvQLabel(p,obj46,obj4);
  pvSetGeometry(p,obj46,5,100,700,15);
  pvSetText(p,obj46,"Level1/HW_Rev");
  pvToolTip(p,obj46,"Level1/HW_Rev");

  pvQLabel(p,obj47,obj4);
  pvSetGeometry(p,obj47,5,115,725,15);
  pvSetText(p,obj47,"Level1/Ser_Num");
  pvToolTip(p,obj47,"Level1/Ser_Num");

  pvQLabel(p,obj48,obj4);
  pvSetGeometry(p,obj48,5,130,705,15);
  pvSetText(p,obj48,"Level1/Descriptor");
  pvToolTip(p,obj48,"Level1/Descriptor");

  pvQLabel(p,obj49,obj4);
  pvSetGeometry(p,obj49,5,145,725,15);
  pvSetText(p,obj49,"Level1/Dev_Instal_Date");
  pvToolTip(p,obj49,"Level1/Dev_Instal_Date");

  pvQLabel(p,obj50,obj4);
  pvSetGeometry(p,obj50,5,160,710,15);
  pvSetText(p,obj50,"Level1/Dev_Message");
  pvToolTip(p,obj50,"Level1/Dev_Message");

  pvQLabel(p,obj52,obj4);
  pvSetGeometry(p,obj52,5,190,725,15);
  pvSetText(p,obj52,"Level1/Hi_Lim");
  pvToolTip(p,obj52,"Level1/Hi_Lim");

  pvQLabel(p,obj51,obj4);
  pvSetGeometry(p,obj51,5,175,710,15);
  pvSetText(p,obj51,"Level1/Out");
  pvToolTip(p,obj51,"Level1/Out");

  pvQLabel(p,obj53,obj4);
  pvSetGeometry(p,obj53,5,205,710,15);
  pvSetText(p,obj53,"Level1/Lo_LIM");
  pvToolTip(p,obj53,"Level1/Lo_LIM");

  pvQWidget(p,obj5,obj2);
  pvAddTab(p,obj2,obj5,"Level2");

  pvQLabel(p,obj54,obj5);
  pvSetGeometry(p,obj54,5,5,715,15);
  pvSetText(p,obj54,"Level2/DS_Devicename");
  pvToolTip(p,obj54,"Level2/DS_Devicename");

  pvQLabel(p,obj55,obj5);
  pvSetGeometry(p,obj55,5,20,715,15);
  pvSetText(p,obj55,"Level2/DS_DeviceID");
  pvToolTip(p,obj55,"Level2/DS_DeviceID");

  pvQLabel(p,obj56,obj5);
  pvSetGeometry(p,obj56,5,35,720,15);
  pvSetText(p,obj56,"Level2/DeviceType");
  pvToolTip(p,obj56,"Level2/DeviceType");

  pvQLabel(p,obj57,obj5);
  pvSetGeometry(p,obj57,5,50,715,15);
  pvSetText(p,obj57,"Level2/DS_Vendorname");
  pvToolTip(p,obj57,"Level2/DS_Vendorname");

  pvQLabel(p,obj58,obj5);
  pvSetGeometry(p,obj58,5,65,705,15);
  pvSetText(p,obj58,"Level2/ProfileID");
  pvToolTip(p,obj58,"Level2/ProfileID");

  pvQLabel(p,obj59,obj5);
  pvSetGeometry(p,obj59,5,80,720,15);
  pvSetText(p,obj59,"Level2/SW_Rev");
  pvToolTip(p,obj59,"Level2/SW_Rev");

  pvQLabel(p,obj60,obj5);
  pvSetGeometry(p,obj60,5,95,725,15);
  pvSetText(p,obj60,"Level2/HW_Rev");
  pvToolTip(p,obj60,"Level2/HW_Rev");

  pvQLabel(p,obj61,obj5);
  pvSetGeometry(p,obj61,5,110,710,15);
  pvSetText(p,obj61,"Level2/Ser_Num");
  pvToolTip(p,obj61,"Level2/Ser_Num");

  pvQLabel(p,obj62,obj5);
  pvSetGeometry(p,obj62,5,125,720,15);
  pvSetText(p,obj62,"Level2/Descriptor");
  pvToolTip(p,obj62,"Level2/Descriptor");

  pvQLabel(p,obj63,obj5);
  pvSetGeometry(p,obj63,5,140,720,15);
  pvSetText(p,obj63,"Level2/Dev_Instal_Date");
  pvToolTip(p,obj63,"Level2/Dev_Instal_Date");

  pvQLabel(p,obj64,obj5);
  pvSetGeometry(p,obj64,5,155,705,15);
  pvSetText(p,obj64,"Level2/Dev_Message");
  pvToolTip(p,obj64,"Level2/Dev_Message");

  pvQLabel(p,obj65,obj5);
  pvSetGeometry(p,obj65,5,170,705,15);
  pvSetText(p,obj65,"Level2/Out");
  pvToolTip(p,obj65,"Level2/Out");

  pvQLabel(p,obj66,obj5);
  pvSetGeometry(p,obj66,5,185,715,15);
  pvSetText(p,obj66,"Level2/Target");
  pvToolTip(p,obj66,"Level2/Target");

  pvQWidget(p,obj6,obj2);
  pvAddTab(p,obj2,obj6,"test");

  pvQLabel(p,testInt16,obj6);
  pvSetGeometry(p,testInt16,5,5,725,15);
  pvSetText(p,testInt16,"test/Int16");
  pvToolTip(p,testInt16,"test/Int16");

  pvQLabel(p,testInt32,obj6);
  pvSetGeometry(p,testInt32,5,20,720,15);
  pvSetText(p,testInt32,"test/Int32");
  pvToolTip(p,testInt32,"test/Int32");

  pvQLabel(p,testFloat,obj6);
  pvSetGeometry(p,testFloat,5,35,715,15);
  pvSetText(p,testFloat,"test/float");
  pvToolTip(p,testFloat,"test/float");

  pvQLabel(p,testDouble,obj6);
  pvSetGeometry(p,testDouble,5,50,690,15);
  pvSetText(p,testDouble,"test/double");
  pvToolTip(p,testDouble,"test/double");

  pvQLabel(p,testString,obj6);
  pvSetGeometry(p,testString,5,65,720,15);
  pvSetText(p,testString,"test/string");
  pvToolTip(p,testString,"test/string");

  pvQPushButton(p,buttonInt16,obj6);
  pvSetGeometry(p,buttonInt16,5,95,100,30);
  pvSetText(p,buttonInt16,"Incremt Int16");

  pvQPushButton(p,buttonInt32,obj6);
  pvSetGeometry(p,buttonInt32,110,95,100,30);
  pvSetText(p,buttonInt32,"Increment Int32");

  pvQPushButton(p,buttonFloat,obj6);
  pvSetGeometry(p,buttonFloat,215,95,100,30);
  pvSetText(p,buttonFloat,"Increment Float");

  pvQPushButton(p,buttonDouble,obj6);
  pvSetGeometry(p,buttonDouble,320,95,100,30);
  pvSetText(p,buttonDouble,"Increment Double");

  pvQPushButton(p,buttonHello,obj6);
  pvSetGeometry(p,buttonHello,425,95,100,30);
  pvSetText(p,buttonHello,"Hello");

  pvQPushButton(p,buttonWorld,obj6);
  pvSetGeometry(p,buttonWorld,530,95,100,30);
  pvSetText(p,buttonWorld,"World");

  pvQLabel(p,labelWriteErrorCount,obj6);
  pvSetGeometry(p,labelWriteErrorCount,5,130,620,15);
  pvSetText(p,labelWriteErrorCount,"writeErrorCount");

  pvQLabel(p,labelReadErrorCount,obj6);
  pvSetGeometry(p,labelReadErrorCount,5,145,625,15);
  pvSetText(p,labelReadErrorCount,"readErrorCount");

  pvQLabel(p,obj7,0);
  pvSetGeometry(p,obj7,10,10,1005,35);
  pvSetText(p,obj7,"OPC XML-DA Example using http://www.dopc.kassl.de/");
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
