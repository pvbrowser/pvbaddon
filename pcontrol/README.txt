This is a pvserver that allows you to
- view event log messages from different processes
- start/stop/monitor daemons

Default password: pvbrowser

Test with:
./pvs
pvbrowser pv://localhost

within other terminal run:
./client  
If you want to see event log messages.

If you want to handle your whole automation with pcontrol:

su
cp startscript /etc/init.d/pcontrol
exit

Now link pcontrol to runlevel rc5.d in order to start it when bootin.
On openSUSE you can do that using YaST->Runlevel Editor
pcontrol will now startup all components you need for your automation.
(your pvs..., xy_client for all your data aquisitions, ...)

