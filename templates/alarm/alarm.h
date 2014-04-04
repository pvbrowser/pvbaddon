//
// alarm system
//
#ifndef _ALARM_H_
#define _ALARM_H_

#include "processviewserver.h"
#include "rlthread.h"
#include "rlspreadsheet.h"
#include "rlstring.h"
#include "rltime.h"
#include "rlevent.h"

class Alarm
{
  public:
    Alarm(int useEventLog=0);
    ~Alarm();
    int loadCSV(const char *filename);
    int set(const char *alarmId);
    int setInt(const char *alarmId, int i);
    int setFloat(const char *alarmId, float f);
    int ack(const char *alarmId);
    int reset(const char *alarmId);
    int ackAll();
    int resetAll();
    const char *text(const char *alarmId);
    int isSet(const char *alarmId);
    int count();
    int maxCount();
    int updateWidgetHTML(PARAM *p, int id, int *state);
  private:  
    const char *strip(const char *text);
    rlString txt1, txt2;
    rlTime time;
    rlSpreadsheetTable table;
    rlMutex mutex;
    int max_alarms, num_alarms, use_event_log;
};

#endif

