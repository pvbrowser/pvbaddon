############################################
# OPC XML-DA Client for use with pvbrowser #
############################################

This client uses the following libraries:
rllib                                   # comes with pvbrowser
libxml2 http://xmlsoft.org/             # normally comes with your distribution
csoap   http://csoap.sourceforge.net/   # soap library in pure C (we include a snapshot of the csoap library in here, it also includes nanohttp)

For Linux 64 Bit and Windows the executables are included in here.
For Linux 32 Bit you have to recompile.

When you recompile you have todo:
cd csoap/libsoap-1.1.0
make clean
make
cd ../..
cd client
make clean
make
cd ..

The usage for opcxmlda_client is as follows:
############################################
Usage: ./opcxmlda_client [URL] [METHOD] <-itemlist=filename> <-shm=filename> <-mbx=filename> <-sleep=milliseconds> <-max_name_length=char> <-shmsize=bytes> <-debug>

[URL] is the url of the OPC XML-DA server.
[METHOD] is the method to call. [METHOD] := GetStatus | Browse | Run
[URL] and [METHOD] are mandatory and must be the first 2 parameters.

Defaults:
-itemlist=opcxmlda.itemlist                                                        # may be created by Browse
-shm=/srv/automation/shm/opcxmlda.shm OR c:\automation\shm\opcxmlda.shm on windows # location of the shared memory
-mbx=/srv/automation/mbx/opcxmlda.mbx OR c:\automation\mbx\opcxmlda.mbx on windows # location of the mailbox
-sleep=1000                                                                        # time between read calls in milliseconds
-max_name_length=31                                                                # max length of result name
-shmsize=65536                                                                     # total size of the shared memory

Example for creating opcxmlda.itemlist:
./opcxmlda_client http://server/opcxmlda/xmldaserver Browse > opcxmlda.itemlist
############################################

Howto use opcxmlda_client:

First you should test if the OPC XML-DA server is running.
Example:
./opcxmlda_client http://192.168.1.13/opcxmlda/isopc.simopcserver.3 GetStatus

You should verify that the server is running.

Now browse the server to create an itemlist.
Example:
./opcxmlda_client http://192.168.1.13/opcxmlda/isopc.simopcserver.3 Browse > opcxmlda.itemlist

You can edit opcxmlda.itemlist and comment the variables you do not want to read.
By default all available items will be read.

Now you can start opcxmlda_client in Run mode.
Example:
./opcxmlda_client http://192.168.1.13/opcxmlda/isopc.simopcserver.3 Run

You can see what the client is reading by adding the -debug switch.
Example:
./opcxmlda_client http://192.168.1.13/opcxmlda/isopc.simopcserver.3 Run -debug

When in Run mode opcxmlda_client will poll the OPC XML-DA server forever.
The variables will be written to the shared memory.
Your pvserver can read this shared memory using rlOpcXmlDa class from rllib.
The opcxmlda_client has a second thread, that will be waiting on the mailbox.
Your pvserver may send variables to this mailbox using rlOpcXmlDa from rllib.
opcxmlda_client will read the mailbox and send the Write command to the OPC XML-DA server.

##################
# Test pvserver: #
##################
In subdirectory pvs there is a test pvserver
that runs with dOPC XGate from kassl.
http://www.dopc.kassl.de/
http://www.ifak-system.de/swt/opc/index.php?level=swtOPCToolkit

Please note that the variable names are input in "toolTip" within the graphical designer.
No manual programming is needed for simple visualizations.
In "slotNullEvent" all objects that have such a toolTip are output with rlPrintf().

