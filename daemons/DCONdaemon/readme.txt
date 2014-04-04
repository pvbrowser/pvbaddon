#
# contributed by "rkl099" in messages displayed in the pvbrowser forum
#

Contents:
readme.txt	this file
DCONdaemon.h
DCONdaemon.cpp
DCONdaemon.sh	compile DCONdaemon

DCONdaemon can be run in a user terminal window
Tested with UBUNTU 8.04


How to use in pvserver:

Ex to read data from shared memory

in main program or a slot:

#include "DCONdaemon.h"  
#include "rlmailbox.h"
#include "rlsharedmemory.h"
rlMailbox rlmailbox(DCON_MAILBOX);
rlSharedMemory rlsharedMemory(DCON_SHARED_MEMORY,DCON_SHARED_MEMORY_SIZE);


// The data is received from shared memory as character array. 
// Each channel is 9 characters, in ascii decimal format, and is converted to a float.

float read_shared_memory_channel(int channel)
{
 unsigned char buf1[BUFFERSIZE];
 int num;
	num = rlsharedMemory.read(channel*9,buf1,9); 
	buf1[9]='\0';
	return atof((char *) buf1);
}




Ex to send commands to modules via mailbox

In a slot:

#include "rlmailbox.h"
extern rlMailbox rlmailbox;



static int slotButtonPressedEvent(PARAM *p, int id, DATA *d)
{
  if(p == NULL || id == 0 || d == NULL) return -1;
  if (id == obj1) {
    return 1;
  }
  if (id == obj2) {
    rlmailbox.write("@07DO00\r",8); //Set 7080 outputs to 00
  }
  if (id == obj3) {
    rlmailbox.write("@07DO01\r",8); //Set 7080 output to 01
  }
  return 0;
}

