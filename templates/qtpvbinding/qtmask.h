//
// Qt binding class for pv functions
// begin: 03-mar-2011
//
#ifndef QT_MASK_H
#define QT_MASK_H

#include "qtpvfunc.h"
#include "qtwidgetidmanager.h"

class QtMask
{
  public:
    QtMask();
    ~QtMask();
    int init(PARAM *p, int id_start, const char * mask_cpp_name = NULL);
    int slotNullEvent();         // TODO: add slot functions as needed
    int slotButtonEvent(int id); // TODO: add slot functions as needed
  private:
    WidgetIdManager mgr;
    PV pv;
    int _iCounter;               // TODO: add your member variales here
};

#endif
