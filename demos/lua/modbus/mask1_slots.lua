-------------------------------------------------------------------------------------
-- mask1_slots.lua       Please edit this file in order to define your logic
-------------------------------------------------------------------------------------
                          -- here you may define variables local for your mask
                          -- also see the variables in the generated maskX.lua
inp = {}                  -- declare some memory for inputs
inp[1] = rllib.rlPlcMem() -- these values are read in slotNullEvent
inp[2] = rllib.rlPlcMem() -- and can be used in any (other) slot

ani = rllib.rlSvgAnimator() -- class for handling a SVG

function drawSvg1(p)        -- helper function for drawing the SVG
  pv.gBeginDraw(p,svg1)
  ani.writeSocket(ani)
  pv.gEndDraw(p)
end

function slotInit(p)     -- this function will be called before the event loop starts
  pv.pvSetAlignment(p,label1,pv.AlignCenter)         -- set label text alignment
  pv.pvSetAlignment(p,label2,pv.AlignCenter)
  pv.pvSetAlignment(p,label3,pv.AlignCenter)
  pv.pvSetAlignment(p,label4,pv.AlignCenter)
  inp[1].i = mb.intValue(mb,"coilStatus(1,0)")       -- read modbus values
  inp[2].i = mb.intValue(mb,"coilStatus(1,8)")
  if inp[1].isSet(inp[1],rllib.BIT4) == 1            then -- init label1
    pv.pvSetPaletteBackgroundColor(p,label1,255,0,0) 
  else
    pv.pvSetPaletteBackgroundColor(p,label1,0,255,0)
  end
  if inp[1].isSet(inp[1],rllib.BIT5) == 1            then -- init label2
    pv.pvSetPaletteBackgroundColor(p,label2,255,0,0) 
  else
    pv.pvSetPaletteBackgroundColor(p,label2,0,255,0)
  end
  if inp[1].isSet(inp[1],rllib.BIT6) == 1            then -- init label3
    pv.pvSetPaletteBackgroundColor(p,label3,255,0,0) 
  else
    pv.pvSetPaletteBackgroundColor(p,label3,0,255,0)
  end
  if inp[1].isSet(inp[1],rllib.BIT7) == 1            then -- init label4
    pv.pvSetPaletteBackgroundColor(p,label4,255,0,0) 
  else
    pv.pvSetPaletteBackgroundColor(p,label4,0,255,0)
  end
  pv.pvSetPaletteBackgroundColor(p,button1,0,255,0)  -- show all button in green
  pv.pvSetPaletteBackgroundColor(p,button2,0,255,0)
  pv.pvSetPaletteBackgroundColor(p,button3,0,255,0)
  pv.pvSetPaletteBackgroundColor(p,button4,0,255,0)
  ani.setId(ani,svg1)                                -- load and draw a test SVG
  ani.setSocket(ani,pv.pvGetSocketPointer(p))
  ani.read(ani,"test1.svg")
  drawSvg1(p)
  -- read a mysql table and show it on screen
  qtdb.query(qtdb,p,"select *from tables") 
  qtdb.populateTable(qtdb,p,table1) 
  return 0
end

function slotNullEvent(p)
  inp[1].i_old = inp[1].i  -- read new input values from modbus slave=1
  inp[2].i_old = inp[2].i  -- inp may be used in all slot functions
  inp[1].i = mb.intValue(mb,"coilStatus(1,0)")
  inp[2].i = mb.intValue(mb,"coilStatus(1,8)")

  -- update color of label if input value changes
  -- and do some outputs within the SVG
  if inp[1].hasBeenSet(inp[1],rllib.BIT4) == 1           then
     pv.pvSetPaletteBackgroundColor(p,label1,255,0,0)
     ani.svgTextPrintf(ani,"text1", "bit4=1")            end
  if inp[1].hasBeenCleared(inp[1],rllib.BIT4) == 1       then
     pv.pvSetPaletteBackgroundColor(p,label1,0,255,0) 
     ani.svgTextPrintf(ani,"text1", "bit4=0")            end

  if inp[1].hasBeenSet(inp[1],rllib.BIT5) == 1           then
     pv.pvSetPaletteBackgroundColor(p,label2,255,0,0)
     ani.svgTextPrintf(ani,"text1", "bit5=1")            end
  if inp[1].hasBeenCleared(inp[1],rllib.BIT5) == 1       then
     pv.pvSetPaletteBackgroundColor(p,label2,0,255,0) 
     ani.svgTextPrintf(ani,"text1", "bit5=0")            end

  if inp[1].hasBeenSet(inp[1],rllib.BIT6) == 1           then
     pv.pvSetPaletteBackgroundColor(p,label3,255,0,0)
     ani.svgTextPrintf(ani,"text1", "bit6=1")            end
  if inp[1].hasBeenCleared(inp[1],rllib.BIT6) == 1       then
     pv.pvSetPaletteBackgroundColor(p,label3,0,255,0) 
     ani.svgTextPrintf(ani,"text1", "bit6=0")            end

  if inp[1].hasBeenSet(inp[1],rllib.BIT7) == 1           then
     pv.pvSetPaletteBackgroundColor(p,label4,255,0,0)
     ani.svgTextPrintf(ani,"text1", "bit7=1")            end
  if inp[1].hasBeenCleared(inp[1],rllib.BIT7) == 1       then
     pv.pvSetPaletteBackgroundColor(p,label4,0,255,0) 
     ani.svgTextPrintf(ani,"text1", "bit7=0")            end

  if inp[1].intChanged(inp[1]) == 1 or inp[2].intChanged(inp[2]) == 1  then
     drawSvg1(p) 
     end
     
  return 0
end

function slotButtonEvent(p,id)
  return 0
end

function slotButtonPressedEvent(p,id)
  -- write some outputs to modbus
  -- and do some outputs within the SVG
  if    (id == button1) then 
    pv.pvSetPaletteBackgroundColor(p,button1,255,0,0)
    mb.writeIntValue(mb,"coil(1,0)",1)
    ani.show(ani,"PV.circle1",0)
    drawSvg1(p)
  elseif(id == button2) then 
    pv.pvSetPaletteBackgroundColor(p,button2,255,0,0)
    mb.writeIntValue(mb,"coil(1,1)",1)
    ani.show(ani,"pv.monitor1",0)
    drawSvg1(p)
  elseif(id == button3) then 
    pv.pvSetPaletteBackgroundColor(p,button3,255,0,0)
    mb.writeIntValue(mb,"coil(1,2)",1)
    ani.svgTextPrintf(ani,"text1", "Hello")
    drawSvg1(p)
  elseif(id == button4) then 
    pv.pvSetPaletteBackgroundColor(p,button4,255,0,0)
    mb.writeIntValue(mb,"coil(1,3)",1)
    ani.svgTextPrintf(ani,"text1", "World")
    drawSvg1(p)
  end
  return 0
end

function slotButtonReleasedEvent(p,id)
  -- write some outputs to modbus
  -- and do some outputs within the SVG
  if    (id == button1) then 
    pv.pvSetPaletteBackgroundColor(p,button1,0,255,0)
    mb.writeIntValue(mb,"coil(1,0)",0)
    ani.show(ani,"PV.circle1",1)
    drawSvg1(p)
  elseif(id == button2) then 
    pv.pvSetPaletteBackgroundColor(p,button2,0,255,0)
    mb.writeIntValue(mb,"coil(1,1)",0)
    ani.show(ani,"pv.monitor1",1)
    drawSvg1(p)
  elseif(id == button3) then 
    pv.pvSetPaletteBackgroundColor(p,button3,0,255,0)
    mb.writeIntValue(mb,"coil(1,2)",0)
  elseif(id == button4) then 
    pv.pvSetPaletteBackgroundColor(p,button4,0,255,0)
    mb.writeIntValue(mb,"coil(1,3)",0)
  end
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
