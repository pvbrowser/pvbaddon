//
// Qt binding class for pv functions
// begin: 03-mar-2011
//

#include "qtmask.h"
#include <stdio.h>

QtMask::QtMask()
{
  _iCounter = 0;
}

QtMask::~QtMask()
{
}

int QtMask::init(PARAM *p, int id_start, const char *mask_cpp_name)
{
  printf("init id_start=%d mask_cpp_name=%s\n", id_start, mask_cpp_name);
  pv.setParam(p);
  mgr.init(p, id_start);
  if(mask_cpp_name != NULL) mgr.readEnumFromMask(mask_cpp_name);
  return 0;
}

// TODO: add slot functions as needed
int QtMask::slotNullEvent() 
{
  printf("slotNullEvent %d\n", _iCounter);
  QString name = "buttonHello";
  pv.Printf(mgr.id(name), "Hello %d", _iCounter);
  _iCounter++;
  return 0;
}

int QtMask::slotButtonEvent(int id)
{
  printf("slotButtonEvent id=%d name=%s\n", id, mgr.name(id));
  pv.StatusMessage(0,255,0,"slotButtonEvent id=%d name=%s\n", id, mgr.name(id));
  return 0;
}


