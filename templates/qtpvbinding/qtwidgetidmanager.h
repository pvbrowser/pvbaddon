//
// Qt binding class for pv functions
// begin: 03-mar-2011
//
#ifndef QT_WIDGET_MANAGER_H
#define QT_WIDGET_MANAGER_H

#include "processviewserver.h"
#include <qstring.h>

class WidgetIdManager : public pvWidgetIdManager
{
  public:
    WidgetIdManager();
    ~WidgetIdManager();
    int newId(const QString &name);
    int newId(const char *name);
    int deleteWidget(PARAM *p, const QString &name);
    int deleteWidget(PARAM *p, const char *name);
    int id(const QString &name);
    int id(const char *name);
    int isInMap(const QString &name);
    int isInMap(const char *name);
};

#endif
