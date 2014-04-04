//
// Qt binding class for pv functions
// begin: 03-mar-2011
//
#ifndef QT_WIDGET_ID_MANAGER_H
#define QT_WIDGET_ID_MANAGER_H

#include "qtwidgetidmanager.h"

WidgetIdManager::WidgetIdManager()
                :pvWidgetIdManager()
{
}

WidgetIdManager::~WidgetIdManager()
{
}

int WidgetIdManager::newId(const QString &name)
{
  return pvWidgetIdManager::newId(name.toUtf8());
}

int WidgetIdManager::newId(const char *name)
{
  return pvWidgetIdManager::newId(name);
}

int WidgetIdManager::deleteWidget(PARAM *p, const QString &name)
{
  return pvWidgetIdManager::deleteWidget(p, name.toUtf8());
}

int WidgetIdManager::deleteWidget(PARAM *p, const char *name)
{
  return pvWidgetIdManager::deleteWidget(p, name);
}

int WidgetIdManager::id(const QString &name)
{
  return pvWidgetIdManager::id(name.toUtf8());
}

int WidgetIdManager::id(const char *name)
{
  return pvWidgetIdManager::id(name);
}

int WidgetIdManager::isInMap(const QString &name)
{
  return pvWidgetIdManager::isInMap((const char *) name.toUtf8());
}

int WidgetIdManager::isInMap(const char *name)
{
  return pvWidgetIdManager::isInMap(name);
}

#endif
