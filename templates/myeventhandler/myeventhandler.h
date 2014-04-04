//
// Template for pvserver event handler class
// myeventhandler.h
//
#ifndef _MY_EVENT_HANDLER_H_
#define _MY_EVENT_HANDLER_H_

#include "pvapp.h"
#include "pveventhandler.h"

class myEventHandler : public pvEventHandler
{
public:
  myEventHandler();
  virtual ~myEventHandler();
  static  int additionalWidgetsNeeded() { return 0 + pvEventHandler::additionalWidgetsNeeded(); }
  virtual int slotInit(PARAM *_p, int _myId1, int _myId2);                    // call this
  virtual int slotNullEvent();
  virtual int slotButtonEvent(int id);                                        // call this
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
private:
  int myId1, myId2; // init these id's with your GUI widget id's
  int count;
};

#endif
