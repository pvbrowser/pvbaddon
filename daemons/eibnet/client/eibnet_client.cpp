/***************************************************************************
 *   client for EIBnet/KNX with pvbrowser                                  *
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
#include "rlmodbus.h"
#include "rleibnetip.h"
#include "rlthread.h"
#include "rlinifile.h"
#include "rlspreadsheet.h"
#include "rldataacquisitionprovider.h"
#include "rlmailbox.h"

// global values
static int                 debug                    = 1;    // 0 or 1
static int                 debug_eib                = 1;    // 0 or 1

// values for socket
static char                client_ip[80]            = "192.168.1.35";
static char                gateway_ip[80]           = "192.168.1.102";

// values for EIBnet
static int                 watch_eib                = 0;
rlEIBnetIP                *eib                      = NULL;
rlIpAdr                   *client                   = NULL;
rlIpAdr                   *server                   = NULL;

// values from rllib...
rlSpreadsheetRow          *namelist                 = NULL;    
int                       *namelist_count, *namelist_slave, *namelist_function, *namelist_start_adr, *namelist_datasize;
int                        num_cycles               = 0;
rlDataAcquisitionProvider *provider                 = NULL;
int                        max_name_length          = 31;
int                        shared_memory_size       = 65536;
rlThread                  *thread                   = NULL;
rlMailbox                 *mbx                      = NULL;

static int init(int ac, char **av)
{
  int ret;

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
  debug       = atoi(ini.text("GLOBAL","DEBUG"));
  debug_eib   = atoi(ini.text("GLOBAL","DEBUG_EIB"));
  watch_eib   = atoi(ini.text("GLOBAL","WATCH_EIB"));

  // init socket variables
  strcpy(client_ip,  ini.text("SOCKET","CLIENT_IP"));
  strcpy(gateway_ip, ini.text("SOCKET","GATEWAY_IP"));

  printf("%s starting with debug=%d debug_eib=%d client_ip=%s gateway_ip=%s\n",
         av[0],            debug,   debug_eib,   client_ip,   gateway_ip);

  // init values for rllib...
  max_name_length = atoi(ini.text("RLLIB","MAX_NAME_LENGTH"));
  if(max_name_length < 4)
  {
    printf("max_name_length=%d < 4\n", max_name_length);
    return -1;
  }
  if(debug) printf("max_name_length=%d\n", max_name_length);

  shared_memory_size = atoi(ini.text("RLLIB","SHARED_MEMORY_SIZE"));
  if(shared_memory_size < 64)
  {
    printf("shared_memory_size=%d < 64\n", shared_memory_size);
    return -1;
  }
  if(debug) printf("shared_memory_size=%d\n", shared_memory_size);

  provider = new rlDataAcquisitionProvider(max_name_length,
                                           ini.text("RLLIB","SHARED_MEMORY"),
                                           shared_memory_size 
                                          );
  if(provider->shmStatus() != 0)
  {
    printf("shared_memory_status ERROR\n");
    return -1;
  }
  provider->setAllowAddValues(1, max_name_length);

  thread = new rlThread();

  mbx = new rlMailbox(ini.text("RLLIB","MAILBOX"));
  if(mbx->status != rlMailbox::OK)
  {
    printf("mailbox_status ERROR\n");
    return -1;
  }

  // start eibnet
  eib    = new rlEIBnetIP(2, debug_eib, provider);
  client = new rlIpAdr;
  server = new rlIpAdr;
  client->setAdr(client_ip,rlEIBnetIP::PORT);
  server->setAdr(gateway_ip,rlEIBnetIP::PORT);
  ret = eib->setClient(client);
  if(ret < 0) return -1;
  ret = eib->setServer(server);
  if(ret < 0) return -1;
  eib->debug = debug_eib;
  eib->watch_eib = watch_eib;
  eib->startReading();

  return 0;
}

int main(int argc,char *argv[])
{
  char  buf[1024],*itemname,*itemvalue,*cptr;
  int   val;
  float fval;
  unsigned int uval;

  if(init(argc, argv) != 0) return -1;

  if(debug) printf("mailboxRead: starting\n");
  mbx->clear(); // clear old messages
  while(mbx->read(buf,sizeof(buf)) > 0)
  {
    itemname = itemvalue = &buf[0];  // parse buf begin
    cptr = strrchr(buf,',');
    if(cptr != NULL)
    {
      *cptr = '\0';
      cptr++;
      itemvalue = cptr;
      cptr = strchr(itemvalue,'\n');
      if(cptr != NULL) *cptr = 0;
    }                                // parse buf end
    if(debug) printf("mailboxReadThread: Write itemname=%s itemvalue=%s\n",itemname,itemvalue);
    eib->thread.lock();
    if     (strchr(itemvalue,'.') != NULL)
    {
      sscanf(itemvalue,"%f",&fval);
      eib->setValueFloat(itemname,fval);
    }
    else if(strchr(itemvalue,'-') != NULL)
    {
      sscanf(itemvalue,"%d",&val);
      eib->setValue(itemname,val);
    }
    else
    {
      sscanf(itemvalue,"%d",&uval);
      eib->setValueUnsigned(itemname,uval);
    }
    eib->thread.unlock();
  }
  return 0;
}

