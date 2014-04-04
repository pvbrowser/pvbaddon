-------------------------------------------------------------------------------------
-- mask1_slots.lua       Please edit this file in order to define your logic
-------------------------------------------------------------------------------------
                         -- here you may define variables local for your mask
                         -- also see the variables in the generated maskX.lua
header  = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\">\n" ..
          "<html>\n" ..
          "<head>\n" ..
          "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />\n" ..
          "<link rel=\"stylesheet\" type=\"text/css\" href=\"pvgrep.css\">\n" ..
          "<title>pvgrep results</title>\n" ..
          "</head>\n" ..
          "<body>\n" 
body    = "<h1>pvbrowser: grep in lua</h1>" ..
          "<p>grep for something ...</p>\n" ..
          "<pre>" ..
          "pvbrowser                    # search locally within directory grepdir\n" ..
          "pv://pvbrowser.org           # our demo pvserver\n" ..
          "http://pvbrowser.org         # a web page\n" ..
          "gg:pvbrowser                 # search with google\n" ..
          "wp:scada                     # search german wikipedia\n" ..
          "leo:cat                      # search cat in leo\n" ..
          "</pre>\n" ..
          "<p>ATTENTION: Because of grep and rlSpawn this will only work on Unix like systems not Windows !!!</p>\n"
trailer = "</body>\n" ..
          "</html>\n"
pattern = ""
gg      = "http://www.google.de/search?q=%s&ie=UTF-8&oe=UTF-8"
wp      = "http://de.wikipedia.org/wiki/Special:Search?search=%s&go=Go"
leo     = "http://dict.leo.org/?search=%s"

function parseLine(line)
  ret = "<hr>\n<p>"
  i = string.find(line,":")
  if(i == nil) then i = 0 end
  line = string.sub(line,i+1)
  while(string.len(line) > 0) do
    if (string.sub(line,1,5) == "pv://"   or
        string.sub(line,1,8) == "pvssh://" or
        string.sub(line,1,7) == "http://") then
      i = string.find(line," ")
      if(i == nil) then i = string.find(line,"\n") end
      if(i == nil) then i = string.len(line) end
      url = string.sub(line,1,i)
      ret = ret .. " <a href=\"" .. url .. "\">" .. url .. "</a>"
      line = string.sub(line,i+1)
    else
      ret = ret .. string.sub(line,1,1)
      line = string.sub(line,2)
    end
  end
  return ret .. "</a>"
end

function grep()
  sp = rllib.rlSpawn()
  body = "<p>grep results for \"" .. pattern .. "\":<p>\n"
  command = string.format("grep -iR \"%s\" grepdir", pattern)
  sp.spawn(sp,command)
  while (1) do
    line = sp.readLine(sp)
    if (line == nil) then break end
    body = body .. parseLine(line) -- append this line
  end
  pv.pvSetText(p,browserGrep,header .. body .. trailer)
  return 0
end

function slotInit(p)     -- this function will be called before the event loop starts
  pv.pvSetText(p,browserGrep,header .. body .. trailer)
  return 0
end

function slotNullEvent(p)
  return 0
end

function slotButtonEvent(p,id)
  if     (id == buttonGrep or id == lineEditGrep) then
    if (string.find(pattern,"gg:") ~= nil) then
      pattern = string.gsub(pattern," ","+")
      url = string.format(gg,string.sub(pattern,4))
      pv.pvHyperlink(p,url)
    elseif (string.find(pattern,"wp:") ~= nil) then
      pattern = string.gsub(pattern," ","+")
      url = string.format(wp,string.sub(pattern,4))
      pv.pvHyperlink(p,url)
    elseif (string.find(pattern,"leo:") ~= nil) then
      pattern = string.gsub(pattern," ","+")
      url = string.format(leo,string.sub(pattern,5))
      pv.pvHyperlink(p,url)
    elseif(string.find(pattern,"http://") ~= nil) then
      pv.pvHyperlink(p,pattern)
    elseif(string.find(pattern,"pv://") ~= nil) then
      pv.pvHyperlink(p,pattern)
    elseif(string.find(pattern,"pvssh://") ~= nil) then
      pv.pvHyperlink(p,pattern)
    else
      grep()
    end  
  end
  return 0
end

function slotButtonPressedEvent(p,id)
  return 0
end

function slotButtonReleasedEvent(p,id)
  return 0
end

function slotTextEvent(p,id,text)
  if (id == lineEditGrep) then
    pattern = text
  elseif (id == browserGrep) then
    if(string.find(text,"pv://") ~= nil) then
      pv.pvHyperlink(p,text)
    elseif(string.find(text,"pvssh://") ~= nil) then
      pv.pvHyperlink(p,text)
    end
  end
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
