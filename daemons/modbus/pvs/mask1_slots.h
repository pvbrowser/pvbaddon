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
      pvPrintf(p,i,"%s=%X Hex", toolTip[i], acqui->intValue(toolTip[i]));
    }
  }
  pvPrintf(p,ReadErrorCount,"ReadErrorCount=%d",acqui->readErrorCount());
  pvPrintf(p,WriteErrorCount,"WriteErrorCount=%d",acqui->writeErrorCount());
  pvPrintf(p,LifeCounter,"LifeCounter=%d",acqui->lifeCounter());
  return 0;
}

static int slotButtonEvent(PARAM *p, int id, DATA *d)
{
  if(p == NULL || id == 0 || d == NULL) return -1;
  int i;
  if(id == buttonIncrement0)
  {
    i = 0;
    pvPrintf(p,buttonIncrement0,"out[0]=%d",d->val[i]);
    acqui->writeIntValue("coil(1,0)", d->val[i]);
    d->val[i] += 1;
    if(d->val[i] > 1) d->val[i] = 0;
  }
  if(id == buttonIncrement1)
  {
    i = 1;
    pvPrintf(p,buttonIncrement1,"out[1]=%d",d->val[i]);
    acqui->writeIntValue("coil(1,1)", d->val[i]);
    d->val[i] += 1;
    if(d->val[i] > 1) d->val[i] = 0;
  }
  if(id == buttonIncrement2)
  {
    i = 2;
    pvPrintf(p,buttonIncrement2,"out[2]=%d",d->val[i]);
    acqui->writeIntValue("coil(1,2)", d->val[i]);
    d->val[i] += 1;
    if(d->val[i] > 1) d->val[i] = 0;
  }
  if(id == buttonIncrement3)
  {
    i = 3;
    pvPrintf(p,buttonIncrement3,"out[2]=%d",d->val[i]);
    acqui->writeIntValue("coil(1,3)", d->val[i]);
    d->val[i] += 1;
    if(d->val[i] > 1) d->val[i] = 0;
  }
  if(id == buttonList)
  {
    const char *var = acqui->firstVariable();
    int i = 0;
    while(var != NULL)
    {
      printf("var[%d] %s=%s\n", i++, var, acqui->stringValue(var));
      var = acqui->nextVariable();
    }
  }
  if(id == buttonRegister)
  {
    pvPrintf(p,buttonRegister,"register(1,0)=0x%X",d->testval);
    acqui->writeIntValue("register(1,0)", d->testval);
    d->testval += 1;
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
