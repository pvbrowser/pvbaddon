//###############################################################
//# mask1_slots.h for ProcessViewServer created: Do Apr 12 12:10:56 2007
//# please fill out these slots
//# here you find all possible events
//# Yours: Lehrig Software Engineering
//###############################################################

// todo: uncomment me if you want to use this data aquisiton
// also uncomment this classes in main.cpp and pvapp.h
// also remember to uncomment rllib in the project file
//extern rlModbusClient     modbus;
//extern rlSiemensTCPClient siemensTCP;
//extern rlPPIClient        ppi;
extern rlEIBnetIP *eib;

typedef struct // (todo: define your data structure here)
{
  int val[ID_END_OF_WIDGETS];
}
DATA;

static int slotInit(PARAM *p, DATA *d)
{
  if(p == NULL || d == NULL) return -1;
  memset(d,0,sizeof(DATA));
  for(int id=0; id<ID_END_OF_WIDGETS; id++)
  {
    const char *t = toolTip[id];
    const char *w = whatsThis[id];
    if(t[0] == '/' && w[0] == '\0')
    {
      if(d->val[id] == EIB_OFF) 
      {
        d->val[id] = EIB_ON;
        pvSetPixmap(p,id,"on.png");
      }
      else 
      {
        d->val[id] = EIB_OFF;
        pvSetPixmap(p,id,"off.png");
      }
    }
  }
  return 0;
}

static int slotNullEvent(PARAM *p, DATA *d)
{
  if(p == NULL || d == NULL) return -1;
  for(int id=0; id<ID_END_OF_WIDGETS; id++)
  {
    const char *t = toolTip[id];
    const char *w = whatsThis[id];
    if     (w[0] == 's')          pvPrintf(p,id,"%d",eib->value(t));
    else if(w[0] == 'u')          pvPrintf(p,id,"%u",eib->valueUnsigned(t));
    else if(strcmp(w,"lcd") == 0) pvDisplayNum(p,id,eib->value(t));
    if(w[0] == '\0' && t[0] == '/')
    {
      int val = eib->value(t);
      if     (val == EIB_ON  && d->val[id] != EIB_ON)  pvSetPixmap(p,id,"on.png");
      else if(val == EIB_OFF && d->val[id] != EIB_OFF) pvSetPixmap(p,id,"off.png");
      if(val == EIB_ON || val == EIB_OFF) d->val[id] = val;
    }
  }
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
  const char *t = toolTip[id];
  const char *w = whatsThis[id];

  if(t[0] == '/' && w[0] == '\0')
  {
    if(d->val[id] == EIB_OFF) 
    {
      eib->setValue(t, EIB_ON);
      d->val[id] = EIB_ON;
      pvSetPixmap(p,id,"on.png");
    }
    else 
    {
      eib->setValue(t, EIB_OFF);
      d->val[id] = EIB_OFF;
      pvSetPixmap(p,id,"off.png");
    }
  }
  else if(isalpha(t[0]))
  {
    eib->setValuesFromCSV(t);
  }
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
  const char *t = toolTip[id];
  const char *w = whatsThis[id];
  if     (strcmp(w,"s2") == 0) eib->setValue(t,val,2);
  else if(strcmp(w,"u2") == 0) eib->setValueUnsigned(t,val,2);
  else if(strcmp(w,"s3") == 0) eib->setValue(t,val,3);
  else if(strcmp(w,"u3") == 0) eib->setValueUnsigned(t,val,3);
  else if(strcmp(w,"s4") == 0) eib->setValue(t,val,4);
  else if(strcmp(w,"u4") == 0) eib->setValueUnsigned(t,val,4);
  else if(w[0] == 's')         eib->setValue(t,val,2);
  else if(w[0] == 'u')         eib->setValueUnsigned(t,val);
  return 0;
}

static int slotCheckboxEvent(PARAM *p, int id, DATA *d, const char *text)
{
  if(p == NULL || id == 0 || d == NULL || text == NULL) return -1;
  int val;
  sscanf(text,"(%d)",&val);
  const char *t = toolTip[id];
  //const char *w = whatsThis[id];
  if(t[0] == '/')
  {
    if(val == 0) 
    {
      eib->setValue(t, EIB_ON);
      d->val[id] = EIB_ON;
    }
    else 
    {
      eib->setValue(t, EIB_OFF);
      d->val[id] = EIB_OFF;
    }
  }
  return 0;
}

static int slotRadioButtonEvent(PARAM *p, int id, DATA *d, const char *text)
{
  if(p == NULL || id == 0 || d == NULL || text == NULL) return -1;
  int val;
  sscanf(text,"(%d)",&val);
  const char *t = toolTip[id];
  //const char *w = whatsThis[id];
  if(t[0] == '/')
  {
    if(val == 0) 
    {
      eib->setValue(t, EIB_ON);
      d->val[id] = EIB_ON;
    }
    else 
    {
      eib->setValue(t, EIB_OFF);
      d->val[id] = EIB_OFF;
    }
  }
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
