/***************************************************************************
 *   client for motion jpeg webcam with pvbrowser                          *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "rlinifile.h"
#include "rlsharedmemory.h"
#include "rlwebcam.h"
#include "rlstring.h"
#include "rlbuffer.h"

// global values
static int                stdin_no;
static int                debug                    = 1;    // 0 or 1
static int                cycletime                = 1000; // milliseconds
static int                use_socket               = 1;
rlBuffer                  buffer;

// values for socket
rlWebcam                 *webcam                   = 0;

// values from rllib...
rlSharedMemory           *shm                      = NULL;
int                       shared_memory_size       = 65536;

static int init(int ac, char **av)
{
  if(ac != 2)
  {
    printf("usage: %s inifile\n", av[0]);
    return -1;
  }

  stdin_no = fileno(stdin);
  rlIniFile ini;
  if(ini.read(av[1]) != 0)
  {
    printf("could not open %s\n", av[1]);
    return -1;
  }

  // init global variables
  use_socket  = atoi(ini.text("GLOBAL","USE_SOCKET"));
  debug       = atoi(ini.text("GLOBAL","DEBUG"));
  cycletime   = atoi(ini.text("GLOBAL","CYCLETIME"));

  // init socket variables
  if(use_socket)
  {
    webcam = new rlWebcam();
    webcam->setUrl(ini.text("SOCKET","HREF"));
    webcam->debug = debug;
  }  

  // init values for rllib...
  shared_memory_size = atoi(ini.text("RLLIB","SHARED_MEMORY_SIZE"));
  if(debug) printf("shared_memory_size=%d\n", shared_memory_size);
  shm = new rlSharedMemory(ini.text("RLLIB","SHARED_MEMORY"), shared_memory_size);
  if(shm->status != 0)
  {
    printf("shared_memory_status ERROR\n");
    return -1;
  }
  buffer.resize(shared_memory_size);
  return 0;
}

static int stdin_getFrameBuffer(unsigned char *buffer, int maxlen)
{
  int ind = 0;
  int c1, c2;
  // search for startOfImage
  while(1)
  {
    if((c1 = getchar()) < 0) return c1;
    //if(debug) printf("%02x ", c1);
    if(c1 == 0x0ff)
    {
      if((c2 = getchar()) < 0) return c2;
      //if(debug) printf("%02x ", c2);
      if(c2 == 0x0d8)
      {
        if(debug) printf("\nrlWebcam::Found startOfImage\n");
        break;
      }
    }
  }
  buffer[ind++] = c1;
  buffer[ind++] = c2;
  // search for endOfImage
  while(1)
  {
    if(ind >= maxlen) return -3;
    if((c1 = getchar()) < 0) return c1;
    buffer[ind++] = c1;
    if(c1 == 0x0ff)
    {
      if((c2 = getchar()) < 0) return c2;
      buffer[ind++] = c2;
      if(c2 == 0x0d8)
      {
        if(debug) printf("\nrlWebcam::Found endOfImage\n");
        break;
      }
    }
  }
  return ind;
}

int main(int argc,char *argv[])
{
  int len;
  if(init(argc, argv) != 0)
  {
    return -1;
  }  
  while(1)                 // forever run the daemon
  {
    if(use_socket) len = webcam->getFrameBuffer(buffer.uc, buffer.size());
    else           len = stdin_getFrameBuffer(buffer.uc, buffer.size());
    if(debug)   printf("header = %x %x len=%d\n", buffer.uc[0], buffer.uc[1], len);
    if(len > 0) shm->write(0, buffer.adr, len);
    else        printf("ERROR: getFrameBUffer len=%d use_socket=%d\n", len, use_socket);
    if(use_socket == 0)
    {
      if(len == EOF)
      {
        printf("End of File\n");
        return 0;
      }
    }
    if(cycletime > 0) 
    {
      webcam->disconnect();
      rlsleep(cycletime);
    }  
  }
  return 0;
}

