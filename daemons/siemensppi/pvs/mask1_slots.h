//###############################################################
//# mask1_slots.h for ProcessViewServer created: Do Jan 17 17:06:13 2008
//# please fill out these slots
//# here you find all possible events
//# Yours: Lehrig Software Engineering
//###############################################################

// todo: uncomment me if you want to use this data acquisiton
// also uncomment this classes in main.cpp and pvapp.h
// also remember to uncomment rllib in the project file
//extern rlModbusClient     modbus;
//extern rlSiemensTCPClient siemensTCP;
//extern rlPPIClient        ppi;

extern rlDataAcquisition *acqui;

typedef struct // (todo: define your data structure here)
{
  int val[32];
  int testval;
}
DATA;

static int slotInit(PARAM *p, DATA *d)
{
  if(p == NULL || d == NULL) return -1;
  memset(d,0,sizeof(DATA));
  return 0;
}

static int slotNullEvent(PARAM *p, DATA *d)
{
  if(p == NULL || d == NULL) return -1;
  for(int i=ID_MAIN_WIDGET+1; i<ID_END_OF_WIDGETS; i++)
  {
    if(strlen(toolTip[i]) > 0)
    {
      pvPrintf(p,i,"%s=%d", toolTip[i], acqui->intValue(toolTip[i]));
    }
  }
  return 0;
}

static int slotButtonEvent(PARAM *p, int id, DATA *d)
{
  if(p == NULL || id == 0 || d == NULL) return -1;
  int i;
  if(id == buttonList)
  {
    const char *var = acqui->firstVariable();
    i = 0;
    while(var != NULL)
    {
      printf("var[%d] %s=%s\n", i++, var, acqui->stringValue(var));
      var = acqui->nextVariable();
    }
  }
  if(id == buttonSet0)
  {
    acqui->writeStringValue("db(2,1,0)","0");
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
  return 0;
}

static int slotSliderEvent(PARAM *p, int id, DATA *d, int val)
{
  if(p == NULL || id == 0 || d == NULL || val < -1000) return -1;
  int slave, dbnum, adr;
  char var[80], value[80];

  slave = 2;
  dbnum = 1;
  adr   = 0;
  if(id == spinBit)
  {    
    sprintf(var,"db(%d,%d,%d)", slave, dbnum, adr);
    sprintf(value,"%d",val);
    acqui->writeStringValue(var,value);
  }
  if(id == spinByte)
  {
    sprintf(var,"db(%d,%d,%d)", slave, dbnum, adr);
    sprintf(value,"%d",val);
    acqui->writeStringValue(var,value);
  }
  if(id == spinInt)
  {
    sprintf(var,"db(%d,%d,%d)", slave, dbnum, adr);
    sprintf(value,"%d,%d",val,val);
    acqui->writeStringValue(var,value);
  }
  if(id == spinFloat)
  {
    sprintf(var,"db(%d,%d,%d)", slave, dbnum, adr);
    sprintf(value,"%d,%d,%d,%d",val,val,val,val);
    acqui->writeStringValue(var,value);
  }
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
  char var[80], value[80];
  int val;

  if(id == bit_0_1_2)
  {
    if(strcmp(text,"(1)") == 0)
    {
      acqui->writeStringValue("db(2,1,8)","1");
      acqui->writeStringValue("db(2,1,9)","1");
      acqui->writeStringValue("db(2,1,10)","1");
    }
    else
    {
      acqui->writeStringValue("db(2,1,8)","0");
      acqui->writeStringValue("db(2,1,9)","0");
      acqui->writeStringValue("db(2,1,10)","0");
    }    
    return 0;
  }

  val = 0;
  if(strcmp(text,"(1)") == 0) val = 1;
  sprintf(value,"%d",val);

  if(id == bit0) sprintf(var,"db(2,1,0)"); 
  if(id == bit1) sprintf(var,"db(2,1,1)"); 
  if(id == bit2) sprintf(var,"db(2,1,2)"); 
  if(id == bit3) sprintf(var,"db(2,1,3)"); 
  if(id == bit4) sprintf(var,"db(2,1,4)"); 
  if(id == bit5) sprintf(var,"db(2,1,5)"); 
  if(id == bit6) sprintf(var,"db(2,1,6)"); 
  if(id == bit7) sprintf(var,"db(2,1,7)"); 
  acqui->writeStringValue(var,value);
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
