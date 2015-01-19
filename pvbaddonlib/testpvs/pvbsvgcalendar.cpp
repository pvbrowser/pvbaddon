/***************************************************************************
                       pvbcalendar.h  -  description
                             -------------------
    begin                : Thu Sep 23 2014
    copyright            : (C) Lehrig Software Enigineering
    email                : lehrig@t-online.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU LESSER GENERAL PUBLIC LICENSE as        *
 *   published by the Free Software Foundation                             *
 *                                                                         *
 ***************************************************************************/
#include "pvbsvgcalendar.h"
#include "rltime.h"

pvbSvgCalendar::pvbSvgCalendar()
{
	debug = 0;
  mId = -1;
  selectedDay = -1;
  selectedMonth = -1;
  selectedYear = -1;
	currentMonth = -1;
	currentYear = -1;
  for(int x=0; x<8; x++)
  {
    for(int y=0; y<7; y++)
    {
      currentDays[y][x] = -1;
    }
  }
  selectedObject[0] = '\0';
}

pvbSvgCalendar::~pvbSvgCalendar()
{
}

void pvbSvgCalendar::splitLine(const char *line)
{
  d1[0] = d2[0] = d3[0] = d4[0] = d5[0] = d6[0] = d7[0] = '\0';
  if(line == NULL)  return;
  if(*line == '\n') return;
  d1[0] = *line++;
  d1[1] = *line++;
  d1[2] = '\0';
  if(*line == '\n') return;
  line++;
  d2[0] = *line++;
  d2[1] = *line++;
  d2[2] = '\0';
  if(*line == '\n') return;
  line++;
  d3[0] = *line++;
  d3[1] = *line++;
  d3[2] = '\0';
  if(*line == '\n') return;
  line++;
  d4[0] = *line++;
  d4[1] = *line++;
  d4[2] = '\0';
  if(*line == '\n') return;
  line++;
  d5[0] = *line++;
  d5[1] = *line++;
  d5[2] = '\0';
  if(*line == '\n') return;
  line++;
  d6[0] = *line++;
  d6[1] = *line++;
  d6[2] = '\0';
  if(*line == '\n') return;
  line++;
  d7[0] = *line++;
  d7[1] = *line++;
  d7[2] = '\0';

  if(d1[0] == ' ') { d1[0] = d1[1]; d1[1] = '\0'; }
  if(d2[0] == ' ') { d2[0] = d2[1]; d2[1] = '\0'; }
  if(d3[0] == ' ') { d3[0] = d3[1]; d3[1] = '\0'; }
  if(d4[0] == ' ') { d4[0] = d4[1]; d4[1] = '\0'; }
  if(d5[0] == ' ') { d5[0] = d5[1]; d5[1] = '\0'; }
  if(d6[0] == ' ') { d6[0] = d6[1]; d6[1] = '\0'; }
  if(d7[0] == ' ') { d7[0] = d7[1]; d7[1] = '\0'; }
}

void pvbSvgCalendar::setSvg(int id, int month, int year, int createLinkToOther)
{
  spawn(id, month, year, createLinkToOther);
}

void pvbSvgCalendar::spawn(int id, int month, int year, int createLinkToOther)
{
  mId = id;
  rlTime now;
  now.getLocalTime();
  if(month < 0) month = now.month;
  if(year < 0) year = now.year;
  currentMonth = month;
  currentYear = year;
  char pattern[32];
  char thispattern[32];
  char nowpattern[32];
  sprintf(nowpattern,"(%d,%d,%d)",now.day,now.month,now.year);
  rlString buf;
  const char *cptr;
  buf.printf("cal %d %d", month, year);
  sp.spawn(buf.text());
  if(createLinkToOther == 0)
  {
    ani.show("PV.idPREV",0);
  }  
  cptr = sp.readLine();
  ani.svgTextPrintf("idMonth","%s",cptr);
  if(createLinkToOther == 0)
  {
    ani.show("PV.idNEXT",0);
  }
  splitLine(sp.readLine());
  ani.svgTextPrintf("PVxta01",d1);
  ani.svgTextPrintf("PVxta02",d2);
  ani.svgTextPrintf("PVxta03",d3);
  ani.svgTextPrintf("PVxta04",d4);
  ani.svgTextPrintf("PVxta05",d5);
  ani.svgTextPrintf("PVxta06",d6);
  ani.svgTextPrintf("PVxta07",d7);
  sprintf(pattern,"(%d,%d,%d)",selectedDay,selectedMonth,selectedYear);
  char object[16];
  int y=1;
  while((cptr = sp.readLine()) != NULL && *cptr > '\n')
  {
    int x=1;
    splitLine(cptr);
    if(d1[0]=='\0') currentDays[y][1] = -1;
    else            sscanf(d1,"%d",&currentDays[y][1]);
    if(d2[0]=='\0') currentDays[y][2] = -1;
    else            sscanf(d2,"%d",&currentDays[y][2]);
    if(d3[0]=='\0') currentDays[y][3] = -1;
    else            sscanf(d3,"%d",&currentDays[y][3]);
    if(d4[0]=='\0') currentDays[y][4] = -1;
    else            sscanf(d4,"%d",&currentDays[y][4]);
    if(d5[0]=='\0') currentDays[y][5] = -1;
    else            sscanf(d5,"%d",&currentDays[y][5]);
    if(d6[0]=='\0') currentDays[y][6] = -1;
    else            sscanf(d6,"%d",&currentDays[y][6]);
    if(d7[0]=='\0') currentDays[y][7] = -1;
    else            sscanf(d7,"%d",&currentDays[y][7]);
    sprintf(thispattern,"(%s,%d,%d)",d1,month,year);
    //printf("    pattern=%s\n", pattern);  
    //printf("thispattern=%s\n", thispattern);  
    //printf(" nowpattern=%s\n", nowpattern);  
    sprintf(object,"PV.ta%d%d", y, x++);
    ani.svgTextPrintf(object,"%s",d1);
    if     (strcmp(thispattern,pattern)    == 0) ani.svgChangeStyleOption(object,"fill:","#00ff00");
    else if(strcmp(thispattern,nowpattern) == 0) ani.svgChangeStyleOption(object,"fill:","#ffffff");
    else                                         ani.svgChangeStyleOption(object,"fill:","#000000");
    sprintf(thispattern,"(%s,%d,%d)",d2,month,year);
    sprintf(object,"PV.ta%d%d", y, x++);
    ani.svgTextPrintf(object,"%s",d2);
    if     (strcmp(thispattern,pattern)    == 0) ani.svgChangeStyleOption(object,"fill:","#00ff00");
    else if(strcmp(thispattern,nowpattern) == 0) ani.svgChangeStyleOption(object,"fill:","#ffffff");
    else                                         ani.svgChangeStyleOption(object,"fill:","#000000");
    sprintf(thispattern,"(%s,%d,%d)",d3,month,year);
    sprintf(object,"PV.ta%d%d", y, x++);
    ani.svgTextPrintf(object,"%s",d3);
    if     (strcmp(thispattern,pattern)    == 0) ani.svgChangeStyleOption(object,"fill:","#00ff00");
    else if(strcmp(thispattern,nowpattern) == 0) ani.svgChangeStyleOption(object,"fill:","#ffffff");
    else                                         ani.svgChangeStyleOption(object,"fill:","#000000");
    sprintf(thispattern,"(%s,%d,%d)",d4,month,year);
    sprintf(object,"PV.ta%d%d", y, x++);
    ani.svgTextPrintf(object,"%s",d4);
    if     (strcmp(thispattern,pattern)    == 0) ani.svgChangeStyleOption(object,"fill:","#00ff00");
    else if(strcmp(thispattern,nowpattern) == 0) ani.svgChangeStyleOption(object,"fill:","#ffffff");
    else                                         ani.svgChangeStyleOption(object,"fill:","#000000");
    sprintf(thispattern,"(%s,%d,%d)",d5,month,year);
    sprintf(object,"PV.ta%d%d", y, x++);
    ani.svgTextPrintf(object,"%s",d5);
    if     (strcmp(thispattern,pattern)    == 0) ani.svgChangeStyleOption(object,"fill:","#00ff00");
    else if(strcmp(thispattern,nowpattern) == 0) ani.svgChangeStyleOption(object,"fill:","#ffffff");
    else                                         ani.svgChangeStyleOption(object,"fill:","#000000");
    sprintf(thispattern,"(%s,%d,%d)",d6,month,year);
    sprintf(object,"PV.ta%d%d", y, x++);
    ani.svgTextPrintf(object,"%s",d6);
    if     (strcmp(thispattern,pattern)    == 0) ani.svgChangeStyleOption(object,"fill:","#00ff00");
    else if(strcmp(thispattern,nowpattern) == 0) ani.svgChangeStyleOption(object,"fill:","#ffffff");
    else                                         ani.svgChangeStyleOption(object,"fill:","#000000");
    sprintf(thispattern,"(%s,%d,%d)",d7,month,year);
    sprintf(object,"PV.ta%d%d", y, x++);
    ani.svgTextPrintf(object,"%s",d7);
    if     (strcmp(thispattern,pattern)    == 0) ani.svgChangeStyleOption(object,"fill:","#00ff00");
    else if(strcmp(thispattern,nowpattern) == 0) ani.svgChangeStyleOption(object,"fill:","#ffffff");
    else                                         ani.svgChangeStyleOption(object,"fill:","#000000");
    y++;
  }
  while(y<=6)
  {
    int x=1;
    sprintf(object,"PV.ta%d%d", y, x++);
    ani.svgTextPrintf(object,"");
    ani.svgChangeStyleOption(object,"fill:","#000000");
    sprintf(object,"PV.ta%d%d", y, x++);
    ani.svgTextPrintf(object,"");
    ani.svgChangeStyleOption(object,"fill:","#000000");
    sprintf(object,"PV.ta%d%d", y, x++);
    ani.svgTextPrintf(object,"");
    ani.svgChangeStyleOption(object,"fill:","#000000");
    sprintf(object,"PV.ta%d%d", y, x++);
    ani.svgTextPrintf(object,"");
    ani.svgChangeStyleOption(object,"fill:","#000000");
    sprintf(object,"PV.ta%d%d", y, x++);
    ani.svgTextPrintf(object,"");
    ani.svgChangeStyleOption(object,"fill:","#000000");
    sprintf(object,"PV.ta%d%d", y, x++);
    ani.svgTextPrintf(object,"");
    ani.svgChangeStyleOption(object,"fill:","#000000");
    sprintf(object,"PV.ta%d%d", y, x++);
    ani.svgTextPrintf(object,"");
    ani.svgChangeStyleOption(object,"fill:","#000000");
    y++;
  }
}

int pvbSvgCalendar::drawSVG(PARAM *p)
{
  //if(ani.isModified == 0) return 0;
  gBeginDraw(p,mId);
  ani.writeSocket();
  gEndDraw(p);
  return 0;
}

int pvbSvgCalendar::slotInit(PARAM *p, int id, const char *svgfile, float scale, int month, int year, int createLinkToOther)
{
  mId = id;
	ani.setSocket(&p->s);
  ani.setId(mId);
  ani.read(svgfile);
  setSvg(mId,month,year,createLinkToOther);
  if(scale != 1.0f)
  {
    rlSvgPosition pos;
    pos.scale(scale);
    ani.setMatrix("idMain",pos);
  }  
  drawSVG(p);
  return 0;
}

int pvbSvgCalendar::slotTextEvent(PARAM *p, int id, const char *text)
{
	const char *cptr;
  int month, year;
  if(id != mId) return -1;
  if(strstr(text,"svgPressedLeftButton") == NULL) return -1;
  if((cptr = strstr(text,"PV.idNext")) != NULL)
  {
    month = currentMonth;
    year  = currentYear;
    printf("goto next current(%d,%d)\n", month, year);
    month++;
    if(month > 12) { month=1; year++; }
    setSvg(mId,month,year);
    drawSVG(p);
    return NEXT;
  }
  else if((cptr = strstr(text,"PV.idPrev")) != NULL)
  {
    month = currentMonth;
    year  = currentYear;
    printf("goto previous current(%d,%d)\n", month, year);
    month--;
    if(month < 1) { month=12; year--; }
    setSvg(mId,month,year);
    drawSVG(p);
    return PREVIOUS;
  }
  else if((cptr = strstr(text,"PV.ra")) != NULL)
  {
    int x,y;
    sscanf(cptr,"PV.ra%1d%1d", &y, &x);
    selectedDay   = currentDays[y][x];
    selectedMonth = currentMonth;
    selectedYear  = currentYear;
    printf("PV.ra  selected current(%d,%d,%d) x=%d y=%d\n", selectedDay, selectedMonth, selectedYear, x, y);
    setSvg(mId,selectedMonth,selectedYear);
    drawSVG(p);
    return SELECTED;
  }
  /*
  else if((cptr = strstr(text,"PV.TA")) != NULL)
  {
    int x,y;
    sscanf(cptr,"PV.TA%1d%1d", &y, &x);
    selectedDay   = currentDays[y][x];
    selectedMonth = currentMonth;
    selectedYear  = currentYear;
    printf("PV.TA selected current(%d,%d,%d) x=%d y=%d\n", selectedDay, selectedMonth, selectedYear, x, y);
    setSvg(mId,selectedMonth,selectedYear);
    drawSVG(p);
    return SELECTED;
  }
  */
  else if((cptr = strstr(text,"PVxidClose")) != NULL)
  {
    return CLOSE;
  }
  return 0;
}
