#!/bin/bash
echo '##############################################'
echo 'Here we show a WebSocket Plugin for a pvserver'
echo 'The pvserver can be used from a normal pvbrowser client (identified by "initial(")'
echo 'The pvserver can also be used by a WebSocket client (identified by Socket Upgrade protocol)'
echo ''
echo 'For pvbrowser testing run' 
echo 'pvbrowser localhost:5050'
echo ''
echo 'For WebSocket client testing run' 
echo 'firefox html/test2.html' 
echo ''
echo 'within another terminal'
echo 'Watch from JavaScript Console in your internet browser'
echo 'For specifications see: https://tools.ietf.org/html/rfc6455'
echo 'For JavaScript Widgets see: http://www.uize.com/index.html'
echo 'or see: http://dojotoolkit.org/documentation/#widgets'
echo 'Javascript Tutorial: http://www.w3schools.com/js/default.asp'
echo '##############################################'
#cd /opt/pvb/pvsexample
#./pvsexample -http -communication_plugin=/home/lehrig/cc/priv/pvbaddon/templates/pvb_com_plugin/wslay/libpvs_com_plugin.so -use_communication_plugin
cd pvs
./pvs -http -communication_plugin=/home/lehrig/cc/priv/pvbaddon/templates/pvb_com_plugin/wslay/libpvs_com_plugin.so -use_communication_plugin
