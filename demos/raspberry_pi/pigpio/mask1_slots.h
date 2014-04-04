//###############################################################
//# mask1_slots.h for ProcessViewServer created: Do. Dez 27 11:02:01 2012
//# please fill out these slots
//# here you find all possible events
//# Yours: Lehrig Software Engineering
//###############################################################

extern char gpio[32];

typedef struct // (todo: define your data structure here)
{
  int portState[26];
}
DATA;

static const char *row1_text[] = { 
  "3.3V",
  "GPIO0 I2C SDA",
  "GPIO1I2C SCL",
  "GPIO4 (GPCLK0)",
  "NC",
  "GPIO17",
  "GPIO21 (PCM_DOUT)",
  "GPIO22",
  "NC",
  "GPIO10 SP10 MOSI",
  "GPIO9 SP10 MOSO",
  "GPIO11 SP10 SCLK",
  "NC"
};

static const char *row2_text[] = {
  "5V",
  "NC",
  "GROUND",
  "GPIO14 UART TxD",
  "GPIO15 UART RxD",
  "GPIO18 (PCM_CLK)",
  "NC",
  "GPIO23",
  "GPIO24",
  "NC",
  "GPIO25",
  "GPIO8 SP10 CE0",
  "GPIO7 SP10 CE1"
};

static const char grey[]     = "color(128,128,128)";
static const char white[]    = "color(255,255,255)";
static const char onGreen[]  = "color(0,255,0)";
static const char offGreen[] = "color(0,128,0)";

static int myPrintGPIO(PARAM *p, int portnumber, const char *color)
{
  int x,y;

  x = y = -1;
  switch(portnumber)
  {
    case 0:  x=1;  y=1;  break; // 1  I2C SDA
    case 1:  x=1;  y=2;  break; // 2  I2C SCL
    case 2:              break;
    case 3:              break;
    case 4:  x=1;  y=3;  break; // 3  GPCLKO 
    case 5:              break;
    case 6:              break;
    case 7:  x=2;  y=12; break; // 4  SP10 CE1
    case 8:  x=2;  y=11; break; // 5  SP10 CE0
    case 9:  x=1;  y=10; break; // 6  SP10 MOSI
    case 10: x=1;  y=9;  break; // 7  SP10 MOSO
    case 11: x=1;  y=11; break; // 8  SP10 SCLK
    case 12:             break;
    case 13:             break;
    case 14: x=2;  y=3;  break; // 9  UART TxD
    case 15: x=2;  y=4;  break; // 10 UART RxD
    case 16:             break;
    case 17: x=1;  y=5;  break; // 11 GPIO
    case 18: x=2;  y=5;  break; // 12 PCM_CLK
    case 19:             break;
    case 20:             break;
    case 21: x=1;  y=6;  break; // 13 PCM_DOUT
    case 22: x=1;  y=7;  break; // 14 GPIO
    case 23: x=2;  y=7;  break; // 15 GPIO
    case 24: x=2;  y=8;  break; // 16 GPIO
    case 25: x=2;  y=10; break; // 17 GPIO
    default:             break;            // 5 GPIO only and 17 multi function GPIO in total
  }
  if(x<0) return -1;
  if(y<0) return -1;
  if(x==1) pvTablePrintf(p,table,x,y,"%s%s",color,row1_text[y]);
  if(x==2) pvTablePrintf(p,table,x,y,"%s%s",color,row2_text[y]);
  return 0;
}

static int myUpdatePortState(PARAM *p, DATA *d, int portnumber, int state)
{
  if(portnumber < 0)  return -1;
  if(portnumber > 25) return -1;
  if(state != 0) state = 1;

  if(d->portState[portnumber] != state)
  {
    if(state == 0) myPrintGPIO(p, portnumber, offGreen);
    else           myPrintGPIO(p, portnumber, onGreen);
  }
  d->portState[portnumber] = state;
  return 0;
}

static int slotInit(PARAM *p, DATA *d)
{
  if(p == NULL || d == NULL) return -1;
  char buf[80];
  int i;
  //memset(d,0,sizeof(DATA));
  for(i=0; i<26; i++) d->portState[i] = -1; // allowed during operation 0 | 1
  pvSetNumRows(p,table,13);
  pvSetNumCols(p,table,4);
  pvSetTableButton(p,table,1,1,"");
  pvSetTableButton(p,table,1,2,"");
  pvTablePrintf(p,table,0,-1,"Left Pin");
  pvTablePrintf(p,table,1,-1,"1 Row");
  pvTablePrintf(p,table,2,-1,"2 Row");
  pvTablePrintf(p,table,3,-1,"Right Pin");
  int y = 0;
  for(i=1; i<14; i++)
  {
    pvTablePrintf(p,table,-1,y,"");
    sprintf(buf, "%02d", i*2 - 1);
    pvTablePrintf(p,table,0,y,buf);
    sprintf(buf, "%02d", i*2    );
    pvTablePrintf(p,table,3,y,buf);
    y++;
  }
  pvTablePrintf(p,table,1,0,"%s%s",grey,     row1_text[0]);
  pvTablePrintf(p,table,1,1,"%s%s",white,    row1_text[1]);
  pvTablePrintf(p,table,1,2,"%s%s",white,    row1_text[2]);
  pvTablePrintf(p,table,1,3,"%s%s",onGreen,  row1_text[3]);
  pvTablePrintf(p,table,1,4,"%s%s",grey,     row1_text[4]);
  pvTablePrintf(p,table,1,5,"%s%s",onGreen,  row1_text[5]);
  pvTablePrintf(p,table,1,6,"%s%s",offGreen, row1_text[6]);
  pvTablePrintf(p,table,1,7,"%s%s",onGreen,  row1_text[7]);
  pvTablePrintf(p,table,1,8,"%s%s",grey,     row1_text[8]);
  pvTablePrintf(p,table,1,9,"%s%s",white,    row1_text[9]);
  pvTablePrintf(p,table,1,10,"%s%s",white,   row1_text[10]);
  pvTablePrintf(p,table,1,11,"%s%s",white,   row1_text[11]);
  pvTablePrintf(p,table,1,12,"%s%s",grey,    row1_text[12]);

  pvTablePrintf(p,table,2,0,"%s%s",grey,     row2_text[0]);
  pvTablePrintf(p,table,2,1,"%s%s",grey,     row2_text[1]);
  pvTablePrintf(p,table,2,2,"%s%s",grey,     row2_text[2]);
  pvTablePrintf(p,table,2,3,"%s%s",white,    row2_text[3]);
  pvTablePrintf(p,table,2,4,"%s%s",white,    row2_text[4]);
  pvTablePrintf(p,table,2,5,"%s%s",onGreen,  row2_text[5]);
  pvTablePrintf(p,table,2,6,"%s%s",grey,     row2_text[6]);
  pvTablePrintf(p,table,2,7,"%s%s",onGreen,  row2_text[7]);
  pvTablePrintf(p,table,2,8,"%s%s",onGreen,  row2_text[8]);
  pvTablePrintf(p,table,2,9,"%s%s",grey,     row2_text[9]);
  pvTablePrintf(p,table,2,10,"%s%s",onGreen, row2_text[10]);
  pvTablePrintf(p,table,2,11,"%s%s",white,   row2_text[11]);
  pvTablePrintf(p,table,2,12,"%s%s",white,   row2_text[12]);

  //myPrintGPIO(p, 11, offGreen);
  //myUpdatePortState(p, d, 10, 0);
  return 0;
}

static int slotNullEvent(PARAM *p, DATA *d)
{
  if(p == NULL || d == NULL) return -1;
  int state;

  for(int portnumber=0; portnumber<26; portnumber++)
  {
    state = gpio[portnumber];
    //printf("update portnumber=%d state=%d\n", portnumber, state);
    myUpdatePortState(p, d, portnumber, state);
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
  int pin = -1;
  if(x==1)
  {
    if(y==1) pin = 0;
    if(y==2) pin = 1;
  }  
  if(pin >= 0)
  {
    if(gpio[pin]) piWriteGPIO(pin,0); // toggle pin
    else          piWriteGPIO(pin,1);
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
