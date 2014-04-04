#!/bin/bash
echo enter root password because we need access to /dev/ttyUSB0
sudo chmod ugo+rw /dev/ttyUSB0
xterm -e modbus_client modbus.ini &
xterm -e pvslua &
