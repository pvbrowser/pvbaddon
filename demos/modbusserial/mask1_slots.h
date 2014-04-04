//###############################################################
//# mask1_slots.h for ProcessViewServer created: Mi Mrz 28 18:50:07 2007
//# please fill out these slots
//# here you find all possible events
//# Yours: Lehrig Software Engineering
//###############################################################

// todo: uncomment me if you want to use this data aquisiton
// also uncomment this classes in main.cpp and pvapp.h
// also remember to uncomment rllib in the project file
extern rlModbusClient     modbus;
//extern rlSiemensTCPClient siemensTCP;
//extern rlPPIClient        ppi;

static int counter(int offset)
{
  return modbus.readByte(offset,1)*256 + modbus.readByte(offset,0);
}

typedef struct // (todo: define your data structure here)
{
  char s[6]; // switches
}
DATA;

static int slotInit(PARAM *p, DATA *d)
{
  if(p == NULL || d == NULL) return -1;
  memset(d,0,sizeof(DATA));
  printf("init start\n");
  d->s[0] = -1;
  d->s[1] = -1;
  d->s[2] = -1;
  d->s[3] = -1;
  d->s[4] = -1;
  d->s[5] = -1;
  pvTablePrintf(p,table1,-1,0,"L1");
  pvTablePrintf(p,table1,-1,1,"L2");
  pvTablePrintf(p,table1,-1,2,"L3");
  pvTablePrintf(p,table1,-1,3,"L4");
  pvTablePrintf(p,table1,-1,4,"L5");
  pvTablePrintf(p,table1,-1,5,"L6");
  pvTablePrintf(p,table1,0,-1,"Lamp");
  pvTablePrintf(p,table1,1,-1,"Switch");
  pvSetTablePixmap(p,table1,0,0,"on.png");
  pvSetTablePixmap(p,table1,0,1,"on.png");
  pvSetTablePixmap(p,table1,0,2,"on.png");
  pvSetTablePixmap(p,table1,0,3,"on.png");
  pvSetTablePixmap(p,table1,0,4,"on.png");
  pvSetTablePixmap(p,table1,0,5,"on.png");
  pvSetTableCheckBox(p,table1,1,0,0,"S1");
  pvSetTableCheckBox(p,table1,1,1,0,"S2");
  pvSetTableCheckBox(p,table1,1,2,0,"S3");
  pvSetTableCheckBox(p,table1,1,3,0,"S4");
  printf("init end\n");
  return 0;
}

static int slotNullEvent(PARAM *p, DATA *d)
{
  int i, val;
  if(p == NULL || d == NULL) return -1;
  for(i=0; i<6; i++)
  {
    val = modbus.readBit(0,i+4); // the first 4 bits are outputs
    if(d->s[i] != val)
    {
      printf("val[%d]=%d\n",i,val);
      if(val == 1) pvSetTablePixmap(p,table1,0,i,"on.png");
      else         pvSetTablePixmap(p,table1,0,i,"off.png");
      d->s[i] = val;
    }
  }
  pvPrintf(p,lifeCounter,    "lifeCounter = %d"    ,counter(modbusdaemon_LIFE_COUNTER_BASE));
  pvPrintf(p,readErrorCount, "readErrorCount = %d" ,counter(modbusdaemon_READ_ERROR_COUNT_BASE));
  pvPrintf(p,writeErrorCount,"writeErrorCount = %d",counter(modbusdaemon_WRITE_ERROR_COUNT_BASE));
  return 0;
}

static int slotButtonEvent(PARAM *p, int id, DATA *d)
{
  if(p == NULL || id == 0 || d == NULL) return -1;
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
  if(id == table1 && x == 1)
  {
    int val;
    sscanf(text,"%d",&val);
    modbus.writeSingleCoil(1,y,val);
  }
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
