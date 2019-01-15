#!/bin/bash

cd foreign

# make csoap
cd csoap/libsoap-1.1.0
qmake-qt5 libcsoap.pro.foreign
make
cd libcsoap
make
cd ..
cd ../..

#make tuxeip
cd tuxeip/tuxeip-1.0/src
qmake-qt5 tuxeip.pro.foreign
make
cd ../../..

cd ..
