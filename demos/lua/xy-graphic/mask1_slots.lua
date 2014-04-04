-------------------------------------------------------------------------------------
-- mask1_slots.lua       Please edit this file in order to define your logic
-------------------------------------------------------------------------------------
-- gDraw Widget
                         -- here you may define variables local for your mask
                         -- also see the variables in the generated maskX.lua
function drawXY(p)
  pv.gBeginDraw    (p,drawWidget);

  pv.gSetColor     (p,0,0,0);
  pv.gSetFont      (p,pv.TIMES,14,pv.Normal,0)
  pv.gBoxWithText  (p,100,50,750,450,14,"x-Axis", "testfunction","nil")
  pv.gXAxis        (p,0.0,0.5,4.0,1)
  pv.gYAxis        (p,0.0,0.5,4.0,1)

  pv.gSetStyle     (p,2)
  pv.gXGrid        (p)
  pv.gYGrid        (p)

  pv.gSetStyle     (p, 1)
  pv.gSetWidth     (p, 3)
  pv.gSetColor     (p,255,0,0)

  pv.pvXYAllocate(p,9)    -- allocate xy array for 9 coordinates
  pv.pvSetXY(p,0,0.0,0.0) -- set some coordinates
  pv.pvSetXY(p,1,0.5,2.0)
  pv.pvSetXY(p,2,1.0,3.0)
  pv.pvSetXY(p,3,1.5,3.5)
  pv.pvSetXY(p,4,2.0,3.8)
  pv.pvSetXY(p,5,2.5,3.5)
  pv.pvSetXY(p,6,3.0,3.0)
  pv.pvSetXY(p,7,3.5,2.0)
  pv.pvSetXY(p,8,4.0,0.0)
  pv.gBufferedLine (p)    -- draw the buffered line

  pv.gSetColor     (p,0,0,255)
  pv.gSetFont      (p,pv.TIMES,14,pv.Bold,0)
  pv.gText         (p,50,18, "This is a Diagram",pv.ALIGN_LEFT)

  pv.gEndDraw      (p)
  return 0
end

function slotInit(p)     -- this function will be called before the event loop starts
  drawXY(p)
  return 0
end

function slotNullEvent(p)
  return 0
end

function slotButtonEvent(p,id)
  if(id == pushButtonQwt) then return 2 end -- call mask 2
  return 0
end

function slotButtonPressedEvent(p,id)
  return 0
end

function slotButtonReleasedEvent(p,id)
  return 0
end

function slotTextEvent(p,id,text)
  return 0
end

function slotSliderEvent(p,id,val)
  return 0
end

function slotCheckboxEvent(p,id,text)
  return 0
end

function slotRadioButtonEvent(p,id,text)
  return 0
end

function slotGlInitializeEvent(p,id)
  return 0
end

function slotGlPaintEvent(p,id)
  return 0
end

function slotGlResizeEvent(p,id,width,height)
  return 0
end

function slotGlIdleEvent(p,id)
  return 0
end

function slotTabEvent(p,id,val)
  return 0
end

function slotTableTextEvent(p,id,x,y,text)
  return 0
end

function slotTableClickedEvent(p,id,x,y,button)
  return 0
end

function slotSelectionEvent(p,id,val,text)
  return 0
end

function slotClipboardEvent(p,id,val)
  return 0
end

function slotRightMouseEvent(p,id,text)
  return 0
end

function slotKeyboardEvent(p,id,val,modifier)
  return 0
end

function slotMouseMovedEvent(p,id,x,y)
  return 0
end

function slotMousePressedEvent(p,id,x,y)
  return 0
end

function slotMouseReleasedEvent(p,id,x,y)
  return 0
end

function slotMouseOverEvent(p,id,enter)
  return 0
end

function slotUserEvent(p,id,text)
  return 0
end
