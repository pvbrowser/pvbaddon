//###############################################################
//# mask5_slots.h for ProcessViewServer created: Sa Jan 26 06:41:05 2008
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

typedef struct // (todo: define your data structure here)
{
  char pass[80],pass_neu[80],pass_veri[80],pass_orig[80];
}
DATA;

static int passChange(PARAM *p, DATA *d)
{
  FILE *fp;

  if(d->pass_orig[0] != '\0')
  {
    if(strcmp(d->pass_orig,rlpass(d->pass)) == 0)
    {
      if(strcmp(d->pass_neu,d->pass_veri) == 0)
      {
        fp = fopen(BUS_ID,"w");
        if(fp != NULL)
        {
          fprintf(fp,"%s\n",rlpass(d->pass_neu));
          fclose(fp);
          return 1;
        }
        else
        {
          pvBeep(p);
          pvMessageBox(p,-1,BoxCritical,"Could not write password file",1,0,0);
          return -1;
        }
      }
      else
      {
        pvBeep(p);
        pvMessageBox(p,-1,BoxWarning,"The new password and\nthe verified password\nare not equal",1,0,0);
        return -1;
      }
    }
    else
    {
      pvBeep(p);
      pvMessageBox(p,-1,BoxWarning,"Wrong password",1,0,0);
      return -1;
    }
  }
  else
  {
    if(strcmp(d->pass_neu,d->pass_veri) == 0)
    {
      fp = fopen(BUS_ID,"w");
      if(fp != NULL)
      {
        fprintf(fp,"%s\n",rlpass(d->pass_neu));
        fclose(fp);
        return 1;
      }
      else
      {
        pvBeep(p);
        pvMessageBox(p,-1,BoxCritical,"Could not write password file",1,0,0);
        return -1;
      }
    }
    else
    {
      pvBeep(p);
      pvMessageBox(p,-1,BoxWarning,"The new password and\nthe verified password\nare not equal",1,0,0);
      return -1;
    }
  }
}

static int slotInit(PARAM *p, DATA *d)
{
  if(p == NULL || d == NULL) return -1;
  char *cptr;
  memset(d,0,sizeof(DATA));
  pvSetEchoMode(p,editOld,2);
  pvSetEchoMode(p,editNew,2);
  pvSetEchoMode(p,editVerify,2);
  FILE *fp = fopen(BUS_ID,"r");
  if(fp != NULL)
  {
    fgets(d->pass_orig,sizeof(d->pass_orig)-1,fp);
    cptr = strstr(d->pass_orig,"\n");
    if(cptr != NULL) *cptr = '\0';
    fclose(fp);
  }
  return 0;
}

static int slotNullEvent(PARAM *p, DATA *d)
{
  if(p == NULL || d == NULL) return -1;
  return 0;
}

static int slotButtonEvent(PARAM *p, int id, DATA *d)
{
  if(p == NULL || id == 0 || d == NULL) return -1;
  if(id == buttonCancel)
  {
    return 1; // call mask 1
  }
  if(id == buttonOk)
  {
    if(passChange(p,d) != -1) return 2; // login
    return 1; // call mask 1
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
  if(id == editOld)    rlstrncpy(d->pass,text,sizeof(d->pass)-1);
  if(id == editNew)    rlstrncpy(d->pass_neu,text,sizeof(d->pass_neu)-1);
  if(id == editVerify) rlstrncpy(d->pass_veri,text,sizeof(d->pass_veri)-1);
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
