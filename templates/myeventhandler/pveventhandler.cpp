//
// Template for pvserver event handler class
// pveventhandler.cpp
//

#include "pveventhandler.h"

pvEventHandler::pvEventHandler()
{
  p = NULL;
}

pvEventHandler::~pvEventHandler()
{
}

int pvEventHandler::slotInit(PARAM *_p)
{
  p = _p;
  return 0;
}

int pvEventHandler::slotNullEvent()
{
  return 0;
}

int pvEventHandler::slotButtonEvent(int id)
{
  if(id == 0) return 0;
  return 0;
}

int pvEventHandler::slotButtonPressedEvent(int id)
{
  if(id == 0) return 0;
  return 0;
}

int pvEventHandler::slotButtonReleasedEvent(int id)
{
  if(id == 0) return 0;
  return 0;
}

int pvEventHandler::slotTextEvent(int id, const char *text)
{
  if(id == 0 || text == NULL) return 0;
  return 0;
}

int pvEventHandler::slotSliderEvent(int id, int val)
{
  if(id == 0 || val < -1000) return 0;
  return 0;
}

int pvEventHandler::slotCheckboxEvent(int id, const char *text)
{
  if(id == 0 || text == NULL) return 0;
  return 0;
}

int pvEventHandler::slotRadioButtonEvent(int id, const char *text)
{
  if(id == 0 || text == NULL) return 0;
  return 0;
}

int pvEventHandler::slotGlInitializeEvent(int id)
{
  if(id == 0) return 0;
  return 0;
}

int pvEventHandler::slotGlPaintEvent(int id)
{
  if(id == 0) return 0;
  return 0;
}

int pvEventHandler::slotGlResizeEvent(int id, int width, int height)
{
  if(id == 0 || width < -1000 || height < -1000) return 0;
  return 0;
}

int pvEventHandler::slotGlIdleEvent(int id)
{
  if(id == 0) return 0;
  return 0;
}

int pvEventHandler::slotTabEvent(int id, int val)
{
  if(id == 0 || val < -1000) return 0;
  return 0;
}

int pvEventHandler::slotTableTextEvent(int id, int x, int y, const char *text)
{
  if(id == 0 || text == NULL || x < -1000 || y < -1000) return 0;
  return 0;
}

int pvEventHandler::slotTableClickedEvent(int id, int x, int y, int button)
{
  if(id == 0 || x < -1000 || y < -1000 || button == -1000) return 0;
  return 0;
}

int pvEventHandler::slotSelectionEvent(int id, int val, const char *text)
{
  if(id == 0 || val == -1000 || text == NULL) return 0;
  return 0;
}

int pvEventHandler::slotClipboardEvent(int id, int val)
{
  if(id == 0 || val == -1000) return 0;
  return 0;
}

int pvEventHandler::slotRightMouseEvent(int id, const char *text)
{
  if(id == 0 || text == NULL) return 0;
  return 0;
}

int pvEventHandler::slotKeyboardEvent(int id, int val, int modifier)
{
  if(id == 0 || val == -1000 || modifier == -1000) return 0;
  return 0;
}

int pvEventHandler::slotMouseMovedEvent(int id, float x, float y)
{
  if(id == 0 || x < -1000 || y < -1000) return 0;
  return 0;
}

int pvEventHandler::slotMousePressedEvent(int id, float x, float y)
{
  if(id == 0 || x < -1000 || y < -1000) return 0;
  return 0;
}

int pvEventHandler::slotMouseReleasedEvent(int id, float x, float y)
{
  if(id == 0 || x < -1000 || y < -1000) return 0;
  return 0;
}

int pvEventHandler::slotMouseOverEvent(int id, int enter)
{
  if(id == 0 || enter < -1000) return 0;
  return 0;
}

int pvEventHandler::slotUserEvent(int id, const char *text)
{
  if(id == 0 || text == NULL) return 0;
  return 0;
}

