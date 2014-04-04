#!/bin/bash

cd foreign
find . -name "*.o" -exec rm "{}" ";"

# make csoap
cd csoap/libsoap-1.1.0
make clean
cd ../..

# make tuxeip
cd tuxeip/tuxeip-1.0/src
rm *.o
rm *.a
cd ../../../

cd ..
