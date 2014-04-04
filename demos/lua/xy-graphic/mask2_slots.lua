-------------------------------------------------------------------------------------
-- mask2_slots.lua       Please edit this file in order to define your logic
-------------------------------------------------------------------------------------
-- QWT Widget
                         -- here you may define variables local for your mask
                         -- also see the variables in the generated maskX.lua
function initDiagram(p)
  -- qwt plot begin ---------------------------------------------
  pv.qpwSetCanvasBackground(p,qwtWidget,239,239,239)
  pv.qpwEnableAxis(p,qwtWidget,pv.yLeft)
  pv.qpwEnableAxis(p,qwtWidget,pv.xBottom)
  pv.qpwSetTitle(p,qwtWidget,"The title of the diagram")

  pv.qpwEnableOutline(p,qwtWidget,1)
  pv.qpwSetOutlinePen(p,qwtWidget,255,0,0)

  -- legend
  pv.qpwSetAutoLegend(p,qwtWidget,1)
  pv.qpwEnableLegend(p,qwtWidget,1)
  pv.qpwSetLegendPos(p,qwtWidget,pv.BottomLegend)
  pv.qpwSetLegendFrameStyle(p,qwtWidget,pv.Sunken)

  -- axes
  pv.qpwSetAxisTitle(p,qwtWidget,pv.xBottom, "X-Axis")
  pv.qpwSetAxisTitle(p,qwtWidget,pv.yLeft, "Test")

  -- curves
  pv.qpwInsertCurve(p,qwtWidget, 0, "Test Function1")
  pv.qpwSetCurvePen(p,qwtWidget, 0, 0,0,255, 1, pv.DashDotLine)
  pv.qpwSetCurveYAxis(p,qwtWidget, 0, pv.yLeft)
  pv.qpwSetCurveSymbol(p,qwtWidget, 0, pv.MarkerDiamond, 255, 0, 0, 0, 255, 0, 10, 10)

  pv.qpwInsertCurve(p,qwtWidget, 1, "Test Function2")
  pv.qpwSetCurvePen(p,qwtWidget, 1, 255,0,0, 1, pv.DotLine)
  pv.qpwSetCurveYAxis(p,qwtWidget, 1, pv.yLeft)
  pv.qpwSetCurveSymbol(p,qwtWidget, 1, pv.MarkerRect, 255, 0, 255, 0, 0, 0, 10, 10)
  -- qwt plot end --------------------------------------------------
  return 0
end

function slotInit(p)     -- this function will be called before the event loop starts
  initDiagram(p)
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
  pv.qpwSetBufferedCurveData(p, qwtWidget, 0) -- draw the curve
  pv.pvXYAllocate(p,3)    -- allocate xy array for 3 coordinates
  pv.pvSetXY(p,0,0.0,1.0) -- set some coordinates
  pv.pvSetXY(p,1,2.0,3.0)
  pv.pvSetXY(p,2,4.0,1.0)
  pv.qpwSetBufferedCurveData(p, qwtWidget, 1) -- draw the curve
  pv.qpwReplot(p,qwtWidget)
  return 0
end

function slotNullEvent(p)
  return 0
end

function slotButtonEvent(p,id)
  if(id == pushButtonDraw) then return 1 end -- call mask 1
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
