//
// Template for pvserver event handler class
// myeventhandler.h
//
#ifndef _PV_EVENT_HANDLER_H_
#define _PV_EVENT_HANDLER_H_

#include "processviewserver.h"

class pvEventHandler
{
public:
  pvEventHandler();
  virtual ~pvEventHandler();
  static  int additionalWidgetsNeeded() { return 0; }
  virtual int slotInit(PARAM *_p);
  virtual int slotNullEvent();
  virtual int slotButtonEvent(int id);
  virtual int slotButtonPressedEvent(int id);
  virtual int slotButtonReleasedEvent(int id);
  virtual int slotTextEvent(int id, const char *text);
  virtual int slotSliderEvent(int id, int val);
  virtual int slotCheckboxEvent(int id, const char *text);
  virtual int slotRadioButtonEvent(int id, const char *text);
  virtual int slotGlInitializeEvent(int id);
  virtual int slotGlPaintEvent(int id);
  virtual int slotGlResizeEvent(int id, int width, int height);
  virtual int slotGlIdleEvent(int id);
  virtual int slotTabEvent(int id, int val);
  virtual int slotTableTextEvent(int id, int x, int y, const char *text);
  virtual int slotTableClickedEvent(int id, int x, int y, int button);
  virtual int slotSelectionEvent(int id, int val, const char *text);
  virtual int slotClipboardEvent(int id, int val);
  virtual int slotRightMouseEvent(int id, const char *text);
  virtual int slotKeyboardEvent(int id, int val, int modifier);
  virtual int slotMouseMovedEvent(int id, float x, float y);
  virtual int slotMousePressedEvent(int id, float x, float y);
  virtual int slotMouseReleasedEvent(int id, float x, float y);
  virtual int slotMouseOverEvent(int id, int enter);
  virtual int slotUserEvent(int id, const char *text);
protected:
  PARAM *p;
};

#endif
