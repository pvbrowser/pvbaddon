//
// Template for pvserver event handler class
// myeventhandler.cpp
//

#include "myeventhandler.h"

myEventHandler::myEventHandler()
               :pvEventHandler()
{
  myId1 = 0;
  myId2 = 0;
  count = 0;
}

myEventHandler::~myEventHandler()
{
}

int myEventHandler::slotInit(PARAM *_p, int _myId1, int _myId2)
{
  pvEventHandler::slotInit(_p);
  if(trace) printf("myEventHandler::slotInit(%d,%d)\n", _myId1, _myId1);
  myId1 = _myId1;
  myId2 = _myId2;
  return 0;
}

int myEventHandler::slotNullEvent()
{
  if(trace) printf("myEventHandler::slotNullEvent()\n");
  return 0;
}

int myEventHandler::slotButtonEvent(int id)
{
  if(id == 0) return 0;
  if(id == myId1) pvPrintf(p, myId2, pvtr("Click %d"), count++);
  return 0;
}

int myEventHandler::slotButtonPressedEvent(int id)
{
  if(id == 0) return 0;
  return 0;
}

int myEventHandler::slotButtonReleasedEvent(int id)
{
  if(id == 0) return 0;
  return 0;
}

int myEventHandler::slotTextEvent(int id, const char *text)
{
  if(id == 0 || text == NULL) return 0;
  return 0;
}

int myEventHandler::slotSliderEvent(int id, int val)
{
  if(id == 0 || val < -1000) return 0;
  return 0;
}

int myEventHandler::slotCheckboxEvent(int id, const char *text)
{
  if(id == 0 || text == NULL) return 0;
  return 0;
}

int myEventHandler::slotRadioButtonEvent(int id, const char *text)
{
  if(id == 0 || text == NULL) return 0;
  return 0;
}

int myEventHandler::slotGlInitializeEvent(int id)
{
  if(id == 0) return 0;
  return 0;
}

int myEventHandler::slotGlPaintEvent(int id)
{
  if(id == 0) return 0;
  return 0;
}

int myEventHandler::slotGlResizeEvent(int id, int width, int height)
{
  if(id == 0 || width < -1000 || height < -1000) return 0;
  return 0;
}

int myEventHandler::slotGlIdleEvent(int id)
{
  if(id == 0) return 0;
  return 0;
}

int myEventHandler::slotTabEvent(int id, int val)
{
  if(id == 0 || val < -1000) return 0;
  return 0;
}

int myEventHandler::slotTableTextEvent(int id, int x, int y, const char *text)
{
  if(id == 0 || text == NULL || x < -1000 || y < -1000) return 0;
  return 0;
}

int myEventHandler::slotTableClickedEvent(int id, int x, int y, int button)
{
  if(id == 0 || x < -1000 || y < -1000 || button == -1000) return 0;
  return 0;
}

int myEventHandler::slotSelectionEvent(int id, int val, const char *text)
{
  if(id == 0 || val == -1000 || text == NULL) return 0;
  return 0;
}

int myEventHandler::slotClipboardEvent(int id, int val)
{
  if(id == 0 || val == -1000) return 0;
  return 0;
}

int myEventHandler::slotRightMouseEvent(int id, const char *text)
{
  if(id == 0 || text == NULL) return 0;
  return 0;
}

int myEventHandler::slotKeyboardEvent(int id, int val, int modifier)
{
  if(id == 0 || val == -1000 || modifier == -1000) return 0;
  return 0;
}

int myEventHandler::slotMouseMovedEvent(int id, float x, float y)
{
  if(id == 0 || x < -1000 || y < -1000) return 0;
  return 0;
}

int myEventHandler::slotMousePressedEvent(int id, float x, float y)
{
  if(id == 0 || x < -1000 || y < -1000) return 0;
  return 0;
}

int myEventHandler::slotMouseReleasedEvent(int id, float x, float y)
{
  if(id == 0 || x < -1000 || y < -1000) return 0;
  return 0;
}

int myEventHandler::slotMouseOverEvent(int id, int enter)
{
  if(id == 0 || enter < -1000) return 0;
  return 0;
}

int myEventHandler::slotUserEvent(int id, const char *text)
{
  if(id == 0 || text == NULL) return 0;
  return 0;
}
