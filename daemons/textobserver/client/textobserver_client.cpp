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
#include "rlspawn.h"
#include "rlstring.h"
#include "rlbuffer.h"

// global values
static int                debug       = 0;    // 0 or 1
rlString                  separator;
rlString                  command;
int                       use_command = 0;    // 0 or 1

// values from rllib...
rlSharedMemory           *shm                      = NULL;
int                       shared_memory_size       = 65536;
rlSpawn                  *spawn                    = NULL;

// static variables
int itest = 0;

static int init(int ac, char **av)
{
  if(ac != 2)
  {
    printf("usage: %s inifile\n", av[0]);
    return -1;
  }

  rlIniFile ini;
  if(ini.read(av[1]) != 0)
  {
    printf("could not open %s\n", av[1]);
    return -1;
  }

  // init global variables
  debug      = atoi(ini.text("GLOBAL","DEBUG"));
  separator  = ini.text("GLOBAL","SEPARATOR");
  separator += "\n";
  command  = ini.text("GLOBAL","SPAWN");
  if(strlen(command.text()) > 0)
  {
    use_command = 1;
    spawn = new rlSpawn();
    spawn->spawn(command.text());
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
  return 0;
}

static int getBuffer(rlString *txt)
{
  char line[4096];

  if(debug) printf("start reading line\n");
  *txt = ""; 

  //itest++;
  //if(itest%10 == 0)
  //{
    if(use_command == 1)
    {
      printf("send something to spawned commandline app\n");
      spawn->printf("INPUT itest=%d\n", itest);
    }
  //}

  if(use_command == 1)
  {
    const char *lineptr;
    while((lineptr = spawn->readLine()) != NULL)
    {
      if(debug) printf("lineptr = %s", lineptr);
      *txt += lineptr;
      if(strncmp(lineptr,separator.text(),10) == 0)
      {
        break;
      }
    }
  }
  else
  {
    while(fgets(line,((int) sizeof(line))-1, stdin) != NULL)
    {
      if(debug) printf("line = %s", line);
      *txt += line;
      if(strcmp(line,separator.text()) == 0)
      {
        break;
      }
    }
  }
  return strlen(txt->text());
}

int main(int argc,char *argv[])
{
  rlString txt;
  int len;
  if(init(argc, argv) != 0)
  {
    return -1;
  }  
  if(debug) printf("start reading frames\n");
  while(1)                 // forever run the daemon
  {
    len = getBuffer(&txt);
    if(debug)   printf("txt = \n%s\n", txt.text());
    if(len > 0) 
    {
      if((len+1) < (int) shm->size()) shm->write(0, txt.text(), len+1);
      else                            printf("ERROR: txt len=%d is too long for shared memory size=%ld\n", (int) strlen(txt.text()), (long) shm->size());
    }  
    else if(len == EOF)
    {
      if(debug) printf("End of File\n");
      return 0;
    }
    else if(len < 0)       
    {
      printf("ERROR: getFrameBUffer len=%d\n", len);
    }  
  }
 return 0;
}

