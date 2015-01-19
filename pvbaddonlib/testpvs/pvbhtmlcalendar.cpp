/***************************************************************************
                       pvbhtmlcalendar.h  -  description
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
#include "pvbhtmlcalendar.h"
#include "rltime.h"

pvbHtmlCalendar::pvbHtmlCalendar()
{
	debug = 0;
  mId = -1;
  selectedDay = -1;
  selectedMonth = -1;
  selectedYear = -1;
  mHeader  = "<html>\n<head><meta charset=\"utf-8\">\n<title>pvbHtmlCalendar</title>\n</head><body>\n";
  // mStyle inspired by
  // http://www.cssflow.com/snippets/dark-datepicker
  // which has MIT license
  // Original PSD by Alexey Anatolievich.
  mStyle   = "<style type=\"text/css\">\n";
  mStyle  += "body {\n";
  mStyle  += "  font: 12px/20px 'Lucida Grande', Verdana, sans-serif;\n";
  mStyle  += "  color: #404040;\n";
  mStyle  += "  background: #313944;\n";
  mStyle  += "}\n";
  mStyle  += ".pvbHtmlCalendar {\n";
  mStyle  += "  position: relative;\n";
  mStyle  += "  margin: 0px auto;\n";
  mStyle  += "  padding: 4px;\n";
  mStyle  += "  font-size: 16px;\n";  // original 10px
  mStyle  += "  text-align: center;\n";
  mStyle  += "  background: #242930;\n";
  mStyle  += "  border: 1px solid #0e1013;\n";
  mStyle  += "  border-collapse: separate;\n";
  mStyle  += "  border-radius: 4px 4px 3px 3px;\n";
  mStyle  += "  box-shadow: 0 1px #181c21, 0 2px #14171b, 0 3px 3px rgba(0, 0, 0, 0.3);\n";
  mStyle  += "}\n";
  mStyle  += ".pvbHtmlCalendar-caption {\n";
  mStyle  += "  display: block;\n";
  mStyle  += "  position: relative;\n";
  mStyle  += "  line-height: 29px;\n";
  mStyle  += "  background: #333941;\n";
  mStyle  += "  border: 1px solid #1b1e24;\n";
  mStyle  += "  border-bottom-color: #181b21;\n";
  mStyle  += "  border-radius: 3px 3px 0 0;\n";
  mStyle  += "  background-image: linear-gradient(to bottom, #414b56, #323841 50%, #2b323a 50%, #252a31);\n";
  mStyle  += "  box-shadow: inset 0 1px rgba(255, 255, 255, 0.1), 0 1px 2px rgba(0, 0, 0, 0.2);\n";
  mStyle  += "}\n";
  mStyle  += ".pvbHtmlCalendar-prev,\n";
  mStyle  += ".pvbHtmlCalendar-next {\n";
  mStyle  += "  position: absolute;\n";
  mStyle  += "  top: 0;\n";
  mStyle  += "  bottom: 0;\n";
  mStyle  += "  width: 28px;\n";
  mStyle  += "  font: 0/0 a;\n";
  mStyle  += "  color: transparent;\n";
  mStyle  += "}\n";
  mStyle  += ".pvbHtmlCalendar-prev:before, .pvbHtmlCalendar-prev:after,\n";
  mStyle  += ".pvbHtmlCalendar-next:before,\n";
  mStyle  += ".pvbHtmlCalendar-next:after {\n";
  mStyle  += "  content: '';\n";
  mStyle  += "  position: absolute;\n";
  mStyle  += "  top: 50%;\n";
  mStyle  += "  left: 50%;\n";
  mStyle  += "  width: 0;\n";
  mStyle  += "  height: 0;\n";
  mStyle  += "  margin-top: -6px;\n";
  mStyle  += "  border: 6px solid transparent;\n";
  mStyle  += "}\n";
  mStyle  += ".pvbHtmlCalendar-prev:before,\n";
  mStyle  += ".pvbHtmlCalendar-next:before {\n";
  mStyle  += "  margin-top: -5px;\n";
  mStyle  += "}\n";
  mStyle  += "\n";
  mStyle  += ".pvbHtmlCalendar-prev {\n";
  mStyle  += "  left: 0;\n";
  mStyle  += "}\n";
  mStyle  += ".pvbHtmlCalendar-prev:before, .pvbHtmlCalendar-prev:after {\n";
  mStyle  += "  margin-left: -9px;\n";
  mStyle  += "}\n";
  mStyle  += ".pvbHtmlCalendar-prev:before {\n";
  mStyle  += "  border-right-color: rgba(255, 255, 255, 0.1);\n";
  mStyle  += "}\n";
  mStyle  += ".pvbHtmlCalendar-prev:after {\n";
  mStyle  += "  border-right-color: #181b21;\n";
  mStyle  += "}\n";
  mStyle  += "\n";
  mStyle  += ".pvbHtmlCalendar-next {\n";
  mStyle  += "  right: 0;\n";
  mStyle  += "}\n";
  mStyle  += ".pvbHtmlCalendar-next:before, .pvbHtmlCalendar-next:after {\n";
  mStyle  += "  margin-left: -3px;\n";
  mStyle  += "}\n";
  mStyle  += ".pvbHtmlCalendar-next:before {\n";
  mStyle  += "  border-left-color: rgba(255, 255, 255, 0.1);\n";
  mStyle  += "}\n";
  mStyle  += ".pvbHtmlCalendar-next:after {\n";
  mStyle  += "  border-left-color: #181b21;\n";
  mStyle  += "}\n";
  mStyle  += ".pvbHtmlCalendar-title {\n";
  mStyle  += "  display: inline-block;\n";
  mStyle  += "  vertical-align: top;\n";
  mStyle  += "  line-height: 18px;\n";
  mStyle  += "  margin: 4px 0;\n";
  mStyle  += "  padding: 0 8px 1px;\n";
  mStyle  += "  font-weight: bold;\n";
  mStyle  += "  color: #8a99af;\n";
  mStyle  += "  text-shadow: 0 1px 1px rgba(0, 0, 0, 0.5);\n";
  mStyle  += "  background: #242930;\n";
  mStyle  += "  border: 1px solid;\n";
  mStyle  += "  border-color: #151a1f #191c21 #1c2025;\n";
  mStyle  += "  border-radius: 2px;\n";
  mStyle  += "  box-shadow: inset 0 1px 2px rgba(0, 0, 0, 0.2), 0 1px rgba(255, 255, 255, 0.08);\n";
  mStyle  += "}\n";
  mStyle  += "\n";
  mStyle  += ".pvbHtmlCalendar-head {\n";
  mStyle  += "  display: block;\n";
  mStyle  += "  background: #2a3139;\n";
  mStyle  += "  border: 1px solid #1b1e25;\n";
  mStyle  += "  border-width: 0 1px;\n";
  mStyle  += "}\n";
  mStyle  += "\n";
  mStyle  += ".pvbHtmlCalendar-th {\n";
  mStyle  += "  width: 28px;\n";
  mStyle  += "  line-height: 24px;\n";
  mStyle  += "  padding-bottom: 1px;\n";
  mStyle  += "  font-weight: bold;\n";
  mStyle  += "  color: #18b165;\n";
  mStyle  += "  text-shadow: 0 1px 1px rgba(0, 0, 0, 0.5);\n";
  mStyle  += "  border-bottom: 1px solid #232833;\n";
  mStyle  += "}\n";
  mStyle  += "\n";
  mStyle  += ".pvbHtmlCalendar-body {\n";
  mStyle  += "  display: block;\n";
  mStyle  += "  background: #404854;\n";
  mStyle  += "  border: 1px solid #1b1e25;\n";
  mStyle  += "  border-top: 0;\n";
  mStyle  += "  border-radius: 0 0 3px 3px;\n";
  mStyle  += "}\n";
  mStyle  += "\n";
  mStyle  += ".pvbHtmlCalendar-td {\n";
  mStyle  += "  width: 28px;\n";
  mStyle  += "  line-height: 26px;\n";
  mStyle  += "  padding-bottom: 1px;\n";
  mStyle  += "  color: #8ba0b8;\n";
  mStyle  += "  text-shadow: 0 1px 1px rgba(0, 0, 0, 0.3);\n";
  mStyle  += "  border-bottom: 1px solid #323841;\n";
  mStyle  += "  box-shadow: inset 0 1px rgba(255, 255, 255, 0.06);\n";
  mStyle  += "}\n";
  mStyle  += ".pvbHtmlCalendar-td > a {\n";
  mStyle  += "  display: block;\n";
  mStyle  += "  color: inherit;\n";
  mStyle  += "  text-decoration: none;\n";
  mStyle  += "}\n";
  mStyle  += ".pvbHtmlCalendar-td > a:hover {\n";
  mStyle  += "  color: #1dd87e;\n";
  mStyle  += "}\n";
  mStyle  += ".pvbHtmlCalendar-td.today {\n";
  mStyle  += "  color: white;\n";
  mStyle  += "  text-shadow: 0 1px 1px rgba(0, 0, 0, 0.3), 0 0 14px rgba(255, 255, 255, 0.6);\n";
  mStyle  += "}\n";
  mStyle  += ".pvbHtmlCalendar-td.selected {\n";
  mStyle  += "  color: #00ff00;\n";
  mStyle  += "  text-shadow: 0 1px 1px rgba(0, 0, 0, 0.3), 0 0 14px rgba(255, 255, 255, 0.6);\n";
  mStyle  += "}\n";
  mStyle  += ".pvbHtmlCalendar-td.off {\n";
  mStyle  += "  color: #677387;\n";
  mStyle  += "  text-shadow: 0 1px 1px rgba(0, 0, 0, 0.1);\n";
  mStyle  += "}\n";
  mStyle  += "tr:last-child > .pvbHtmlCalendar-td {\n";
  mStyle  += "  border-bottom: 0;\n";
  mStyle  += "}\n";
  mStyle  += "</style>";
  mTrailer = "\n</body></html>";
}

pvbHtmlCalendar::~pvbHtmlCalendar()
{
}

void pvbHtmlCalendar::splitLine(const char *line)
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

void pvbHtmlCalendar::setHtml(int id, int month, int year, int createLinkToOther)
{
  setMonth(id, month, year, createLinkToOther);
  mHtml  = mHeader;
  mHtml += mStyle;
  mHtml += mTitleText;
  mHtml += mMonth;
  mHtml += mTrailer;
}

void pvbHtmlCalendar::setMonth(int id, int month, int year, int createLinkToOther)
{
  mId = id;
  spawn(id, month, year, createLinkToOther);
}

void pvbHtmlCalendar::spawn(int id, int month, int year, int createLinkToOther)
{
  rlTime now;
  now.getLocalTime();
  if(month < 0) month = now.month;
  if(year < 0) year = now.year;
  char option[16];
  char pattern[32];
  char thispattern[32];
  char nowpattern[32];
  sprintf(nowpattern,"(%d,%d,%d)",now.day,now.month,now.year);
  option[0] = '\0';
  rlString buf;
  const char *cptr;
  buf.printf("cal %d %d", month, year);
  sp.spawn(buf.text());
  mMonth  = "<table class=\"pvbHtmlCalendar\">\n";
  mMonth += "  <caption class=\"pvbHtmlCalendar-caption\">\n";
  if(createLinkToOther)
  {
    buf.printf("    <a href=\"pvb://cal/previous?id=%d&month=%d&year=%d\" class=\"pvbHtmlCalendar-prev\">❮</a>\n", id, month, year);
    mMonth += buf;
  }  
  cptr = sp.readLine();
  buf.printf("    <span class=\"pvbHtmlCalendar-title\">%s</span>\n", cptr);
  mMonth += buf;
  if(createLinkToOther)
  {
    buf.printf("    <a href=\"pvb://cal/next?id=%d&month=%d&year=%d\" class=\"pvbHtmlCalendar-next\">❯</a>\n", id, month, year);
    mMonth += buf;
  }
  mMonth += "  </caption>\n";
  mMonth += "  <thead class=\"pvbHtmlCalendar-head\">\n";
  mMonth += "    <tr>\n";
  splitLine(sp.readLine());
  buf.printf("      <th class=\"pvbHtmlCalendar-th\">%s</th>\n", d1);
  mMonth += buf;
  buf.printf("      <th class=\"pvbHtmlCalendar-th\">%s</th>\n", d2);
  mMonth += buf;
  buf.printf("      <th class=\"pvbHtmlCalendar-th\">%s</th>\n", d3);
  mMonth += buf;
  buf.printf("      <th class=\"pvbHtmlCalendar-th\">%s</th>\n", d4);
  mMonth += buf;
  buf.printf("      <th class=\"pvbHtmlCalendar-th\">%s</th>\n", d5);
  mMonth += buf;
  buf.printf("      <th class=\"pvbHtmlCalendar-th\">%s</th>\n", d6);
  mMonth += buf;
  buf.printf("      <th class=\"pvbHtmlCalendar-th\">%s</th>\n", d7);
  mMonth += buf;
  mMonth += "    </tr>\n";
  mMonth += "  </thead>\n";
  mMonth += "  <tbody class=\"pvbHtmlCalendar-body\">\n";
  sprintf(pattern,"(%d,%d,%d)",selectedDay,selectedMonth,selectedYear);
  while((cptr = sp.readLine()) != NULL && *cptr > '\n')
  {
    mMonth += "    <tr>\n";
    splitLine(cptr);
    sprintf(thispattern,"(%s,%d,%d)",d1,month,year);
    option[0] = '\0';
    if(strcmp(thispattern,nowpattern) == 0) strcpy(option," today");
    if(strcmp(thispattern,pattern) == 0) strcpy(option," selected");
    buf.printf("    <td class=\"pvbHtmlCalendar-td%s\"><a href=\"pvb://cal?id=%d&day=%s&month=%d&year=%d\">%s</a></td>\n", option, id, d1, month, year, d1);
    mMonth += buf;
    sprintf(thispattern,"(%s,%d,%d)",d2,month,year);
    option[0] = '\0';
    if(strcmp(thispattern,nowpattern) == 0) strcpy(option," today");
    if(strcmp(thispattern,pattern) == 0) strcpy(option," selected");
    buf.printf("    <td class=\"pvbHtmlCalendar-td%s\"><a href=\"pvb://cal?id=%d&day=%s&month=%d&year=%d\">%s</a></td>\n", option, id, d2, month, year, d2);
    mMonth += buf;
    sprintf(thispattern,"(%s,%d,%d)",d3,month,year);
    option[0] = '\0';
    if(strcmp(thispattern,nowpattern) == 0) strcpy(option," today");
    if(strcmp(thispattern,pattern) == 0) strcpy(option," selected");
    buf.printf("    <td class=\"pvbHtmlCalendar-td%s\"><a href=\"pvb://cal?id=%d&day=%s&month=%d&year=%d\">%s</a></td>\n", option, id, d3, month, year, d3);
    mMonth += buf;
    sprintf(thispattern,"(%s,%d,%d)",d4,month,year);
    option[0] = '\0';
    if(strcmp(thispattern,nowpattern) == 0) strcpy(option," today");
    if(strcmp(thispattern,pattern) == 0) strcpy(option," selected");
    buf.printf("    <td class=\"pvbHtmlCalendar-td%s\"><a href=\"pvb://cal?id=%d&day=%s&month=%d&year=%d\">%s</a></td>\n", option, id, d4, month, year, d4);
    mMonth += buf;
    sprintf(thispattern,"(%s,%d,%d)",d5,month,year);
    option[0] = '\0';
    if(strcmp(thispattern,nowpattern) == 0) strcpy(option," today");
    if(strcmp(thispattern,pattern) == 0) strcpy(option," selected");
    buf.printf("    <td class=\"pvbHtmlCalendar-td%s\"><a href=\"pvb://cal?id=%d&day=%s&month=%d&year=%d\">%s</a></td>\n", option, id, d5, month, year, d5);
    mMonth += buf;
    sprintf(thispattern,"(%s,%d,%d)",d6,month,year);
    option[0] = '\0';
    if(strcmp(thispattern,nowpattern) == 0) strcpy(option," today");
    if(strcmp(thispattern,pattern) == 0) strcpy(option," selected");
    buf.printf("    <td class=\"pvbHtmlCalendar-td%s\"><a href=\"pvb://cal?id=%d&day=%s&month=%d&year=%d\">%s</a></td>\n", option, id, d6, month, year, d6);
    mMonth += buf;
    sprintf(thispattern,"(%s,%d,%d)",d7,month,year);
    option[0] = '\0';
    if(strcmp(thispattern,nowpattern) == 0) strcpy(option," today");
    if(strcmp(thispattern,pattern) == 0) strcpy(option," selected");
    buf.printf("    <td class=\"pvbHtmlCalendar-td%s\"><a href=\"pvb://cal?id=%d&day=%s&month=%d&year=%d\">%s</a></td>\n", option, id, d7, month, year, d7);
    mMonth += buf;
    mMonth += "    </tr>\n";
  }

  mMonth += "  </tbody>\n";
  mMonth += "</table>\n";

  if(debug) printf("mMonth=\n%s\n", mMonth.text());
}

int pvbHtmlCalendar::slotInit(PARAM *p, int id, int month, int year, int createLinkToOther)
{
  setHtml(id, month, year, createLinkToOther);
  pvSetText(p,id,mHtml.text());
  return 0;
}

int pvbHtmlCalendar::slotTextEvent(PARAM *p, int id, const char *text)
{
  int pid, month, year;
  if(id != mId) return -1;
  if(strstr(text,"pvb://cal/next") != NULL)
  {
    sscanf(text,"pvb://cal/next?id=%d&month=%d&year=%d", &pid, &month, &year);
    printf("goto next current(%d,%d)\n", month, year);
    month++;
    if(month > 12) { month=1; year++; }
    setHtml(id,month,year);
    pvSetText(p,id,mHtml.text());
    return NEXT;
  }
  else if(strstr(text,"pvb://cal/previous") != NULL)
  {
    sscanf(text,"pvb://cal/previous?id=%d&month=%d&year=%d", &pid, &month, &year);
    printf("goto previous current(%d,%d)\n", month, year);
    month--;
    if(month < 1) { month=12; year--; }
    setHtml(id,month,year);
    pvSetText(p,id,mHtml.text());
    return PREVIOUS;
  }
  else if(strstr(text,"pvb://cal") != NULL)
  {
    sscanf(text,"pvb://cal?id=%d&day=%d&month=%d&year=%d", &pid, &selectedDay, &selectedMonth, &selectedYear);
    printf("selected current(%d,%d,%d)\n", selectedDay, selectedMonth, selectedYear);
    setHtml(id,selectedMonth,selectedYear);
    pvSetText(p,id,mHtml.text());
    return SELECTED;
  }
  return 0;
}
