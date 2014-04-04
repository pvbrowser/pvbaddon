-------------------------------------------------------------------------------------
-- pvserver in lua     run: pvslua -port=5050 -cd=/your/directory/with/your/lua/code
-------------------------------------------------------------------------------------
trace = 1                -- here you may put variables global for all your masks

dofile("translator.lua") -- include the language translator
dofile("mask1.lua")      -- include your masks here

-------------------------------------------------------------------------------------
function luaMain(ptr)    -- pvserver Lua Main Program

  p = pv.getParam(ptr)   -- get the PARAM structure

  -- show the usage of our translator
  readLanguageFile("text.ini")
  setLanguage("DEUTSCH")
  print("german:hello="   .. tr("hello"))
  print("german:world="   .. tr("world"))
  print("german:umlaute=" .. tr("umlaute"))
  print("german:unknown=" .. tr("unknown"))
  setLanguage("ENGLISH")
  print("english:hello="   .. tr("hello"))
  print("english:world="   .. tr("world"))
  print("english:umlaute=" .. tr("umlaute"))
  print("english:unknown=" .. tr("unknown"))

  pv.pvSetCaption(p,tr("umlaute"))
  pv.pvResize(p,0,1280,1024)
  pv.pvGetInitialMask(p)
  print("Inital mask = ", p.initial_mask)

  ret = 1
  while 1 do           -- show your masks
    if     (ret==1) then
      ret = showMask1(p)
    else
      ret = 1
    end
  end

  pv.pvThreadFatal(p,"Lua calling ThreadFatal")
  return 0

end
