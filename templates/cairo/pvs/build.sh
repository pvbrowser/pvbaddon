#!/bin/bash
make
g++ -o send_mbxcmd send_mbxcmd.cpp -I/usr/share/qt4/mkspecs/default -I. -I/opt/pvb/pvserver -I/opt/pvb/rllib/lib -I/usr/include/cairo -I../libpvcairo -lpthread /usr/lib/librllib.so /usr/lib64/libcairo.so ../libpvcairo/libpvcairo.a

