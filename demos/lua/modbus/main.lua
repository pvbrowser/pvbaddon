-------------------------------------------------------------------------------------
-- pvserver in lua     run: pvslua -port=5050 -cd=/your/directory/with/your/lua/code
-------------------------------------------------------------------------------------
trace = 1              -- here you may put variables global for all your masks
-- declare the data acquisition class for connecting to modbus
-- this class communicates with the modus_daemon via a shared memeory and a mailbox
--                                                Mailbox                         Shared Memory  ShmSize  
mb = rllib.rlDataAcquisition("/srv/automation/mbx/modbus1.mbx","/srv/automation/shm/modbus1.shm",65536)

qtdb = pv.qtDatabase() -- declare a Qt Database

dofile("mask1.lua")    -- include your masks here

-------------------------------------------------------------------------------------
function luaMain(ptr)  -- pvserver Lua Main Program

  p = pv.getParam(ptr) -- get the PARAM structure

  pv.pvSetCaption(p,string.format("Hello Modbus from Lua pvserver %3.1f",0.1))
  pv.pvResize(p,0,1280,1024)
  pv.pvGetInitialMask(p)
  print("Inital mask = ", p.initial_mask)

  -- open the database
  ret = qtdb.open(qtdb,"QMYSQL","localhost","information_schema","","")
  print("qtdb.open() ret=", ret)

  print(string.format("Shared Memory %s: key=%x (hex) id=%d (dec)","/srv/automation/shm/modbus1.shm",
                      mb.shmKey(mb), mb.shmId(mb)))

  -- show the masks
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
