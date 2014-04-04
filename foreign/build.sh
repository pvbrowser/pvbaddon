#!/bin/bash

cd foreign

# make csoap
cd csoap/libsoap-1.1.0
qmake libcsoap.pro.foreign
make
cd libcsoap
make
cd ..
cd ../..

#make tuxeip
cd tuxeip/tuxeip-1.0/src
qmake tuxeip.pro.foreign
make
cd ../../..

cd ..
