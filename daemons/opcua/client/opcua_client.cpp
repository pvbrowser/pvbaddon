/* nAuthor: pvbrowser 2015 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "rlsharedmemory.h"
#include "rlthread.h"
#include "rlmailbox.h"
#include "rlcutil.h"
#include "rlstring.h"
#ifdef NOT_AMALGATED
    #include "ua_types.h"
    #include "ua_client.h"
    #include "ua_nodeids.h"
    #include "networklayer_tcp.h"
    #include "logger_stdout.h"
#else
#include "open62541.h"
#endif

#ifdef _WIN32 
#define xmlFree free
#endif

#define MAX_LINE_LENGTH 65535
#define MAX_PATH_LENGTH 1024
#define URN             "opc.tcp://localhost:16664"

UA_Client *client = NULL;

/* command line options */
char itemlist[MAX_PATH_LENGTH] = "opcua.itemlist";
#ifdef _WIN32
char shm[MAX_PATH_LENGTH]      = "c:\\automation\\shm\\opcua.shm";
char mbx[MAX_PATH_LENGTH]      = "c:\\automation\\mbx\\opcua.mbx";
#else
char shm[MAX_PATH_LENGTH]      = "/srv/automation/shm/opcua.shm";
char mbx[MAX_PATH_LENGTH]      = "/srv/automation/mbx/opcua.mbx";
#endif
int  sleep              = 1000;
int  max_name_length    = 31;
int  num_items          = 0;
long shmsize            = 65536;
int  longname           = 0;
int  debug              = 0;
int  debug2             = 1;

/* shared memory header */
typedef struct
{
  char ident[4];          // must be "opc"
  int  maxItemNameLength; // maximum length of an item name
  int  maxNameLength;     // maximum length of the item value
  int  numItems;          // number of items in shared memory
  int  readErrorCount;    // 0...65536 incremented by each read error
  int  writeErrorCount;   // 0...65536 incremented by each write error
  int  spare[8];          // for future use
  char cspare[32];        // for future use
}SHM_HEADER;

void printusage(char *FileName)
{
  printf("Usage: %s [URL] [METHOD] <-itemlist=filename> <-shm=filename> <-mbx=filename> <-sleep=milliseconds> <-max_name_length=char> <-shmsize=bytes> <-debug>\n\n", FileName);

  printf("[URL] is the url of the OPC UA server.\n");
  printf("[METHOD] is the method to call. [METHOD] := Browse | Run\n");
  printf("[URL] and [METHOD] are mandatory and must be the first 2 parameters.\n\n");

  printf("Defaults:\n");
  printf("-itemlist=opcua.itemlist                                                        # may be created by Browse\n");
  printf("-shm=/srv/automation/shm/opcua.shm OR c:\\automation\\shm\\opcua.shm on windows # location of the shared memory\n");
  printf("-mbx=/srv/automation/mbx/opcua.mbx OR c:\\automation\\mbx\\opcua.mbx on windows # location of the mailbox\n");
  printf("-sleep=1000                                                                     # time between read calls\n");
  printf("-max_name_length=31                                                             # max length of result name\n"); 
  printf("-shmsize=65536                                                                  # total size of the shared memory\n\n");
  printf("-longname                                                                       # create long names when method==Browser\n\n");

  
  printf("Example for creating opcua.itemlist:\n");
  printf("%s opc.tcp://localhost:16664 Browse > opcua.itemlist\n", FileName);
}

// watchdog
static char startme[512] = "";
static int watchcnt1 = 0;
void *watchdog_thread(void *arg)
{
  int cnt1 = -1;

  if(debug) printf("watchdog thread starting\n");
  while(1)
  {
    rlsleep(10*sleep);
    if(cnt1 == watchcnt1) break;
    cnt1 = watchcnt1;
  }
  printf("startme again # %s\n",startme);
#ifdef unix
  rlexec(startme);
#endif
  exit(0); // pcontrol may start me again if rlexec fails
  return arg;
}

void *reader_thread(void *arg)
{
  char *itemname,*itemvalue,buf[1024], *cptr;
  int ret;
  long value;
  double fvalue;
  THREAD_PARAM *p = (THREAD_PARAM *) arg;
  rlMailbox rlmbx(mbx);

  // read mbx until it is empty
  rlmbx.clear();
  if(debug) printf("reader_thread starting\n");

  // wait for commands from clients
  while(1)
  {
    ret = rlmbx.read(buf,sizeof(buf)); // read "itemname,itemvalue\n"
    if(ret <= 0) continue;
    itemname = itemvalue = &buf[0];
    cptr = strchr(buf,',');
    if(cptr != NULL)
    {
      *cptr = '\0';
      cptr++;
      itemvalue = cptr;
      cptr = strchr(itemvalue,'\n');
      if(cptr != NULL) *cptr = 0;
    }
    if(debug) printf("reader_thread Write itemname=%s itemvalue=%s\n",itemname,itemvalue);

    p->thread->lock();
    // Write node's value
    UA_WriteRequest wReq;
    UA_WriteRequest_init(&wReq);
    wReq.nodesToWrite = UA_WriteValue_new();
    wReq.nodesToWriteSize = 1;

    rlString rltmp(itemname);
    cptr = strchr(rltmp.text(),'#');
    if(cptr != NULL)
    {
      *cptr = '\0';
      cptr++;
      char *end = strchr(cptr,'#');
      if(end != NULL) *end = '\0';
      int ns = 0;
      sscanf(rltmp.text(),"%d",&ns);
      if(debug) printf("\nWriting a value of node (%d, \"%s\"):\n", ns, cptr);
      wReq.nodesToWrite[0].nodeId = UA_NODEID_STRING_ALLOC(ns, cptr); // assume this node exists
      wReq.nodesToWrite[0].attributeId = UA_ATTRIBUTEID_VALUE;
      wReq.nodesToWrite[0].value.hasValue = UA_TRUE;

      int isNum = 1;
      const UA_DataType *uatype;
      uatype = &UA_TYPES[UA_TYPES_INT32];
      if     (strncmp(itemvalue,"Boolean:",8) == 0)         { uatype = &UA_TYPES[UA_TYPES_BOOLEAN]; isNum = 1; }
      else if(strncmp(itemvalue,"SByte:",6) == 0)           { uatype = &UA_TYPES[UA_TYPES_SBYTE]; isNum = 1; }
      else if(strncmp(itemvalue,"Byte:",5) == 0)            { uatype = &UA_TYPES[UA_TYPES_BYTE]; isNum = 1; }
      else if(strncmp(itemvalue,"Int16:",6) == 0)           { uatype = &UA_TYPES[UA_TYPES_INT16]; isNum = 1; }
      else if(strncmp(itemvalue,"UInt16:",7) == 0)          { uatype = &UA_TYPES[UA_TYPES_UINT16]; isNum = 1; }
      else if(strncmp(itemvalue,"Int32:",6) == 0)           { uatype = &UA_TYPES[UA_TYPES_INT32]; isNum = 1; }
      else if(strncmp(itemvalue,"UInt32:",7) == 0)          { uatype = &UA_TYPES[UA_TYPES_UINT32]; isNum = 1; }
      else if(strncmp(itemvalue,"Int64:",6) == 0)           { uatype = &UA_TYPES[UA_TYPES_INT64]; isNum = 1; }
      else if(strncmp(itemvalue,"UInt64:",7) == 0)          { uatype = &UA_TYPES[UA_TYPES_UINT64]; isNum = 1; }
      else if(strncmp(itemvalue,"Float:",6) == 0)           { uatype = &UA_TYPES[UA_TYPES_FLOAT]; isNum = 2; }
      else if(strncmp(itemvalue,"Double:",7) == 0)          { uatype = &UA_TYPES[UA_TYPES_DOUBLE]; isNum = 3; }
      else if(strncmp(itemvalue,"String:",7) == 0)          { uatype = &UA_TYPES[UA_TYPES_STRING]; isNum = 0; }
      else if(strncmp(itemvalue,"Guid:",5) == 0)            { uatype = &UA_TYPES[UA_TYPES_GUID]; isNum = 0; }
      else if(strncmp(itemvalue,"NodeId:",7) == 0)          { uatype = &UA_TYPES[UA_TYPES_NODEID]; isNum = 0; }
      else if(strncmp(itemvalue,"ExpandedNodeId:",15) == 0) { uatype = &UA_TYPES[UA_TYPES_EXPANDEDNODEID]; isNum = 0; }
      else if(strncmp(itemvalue,"QualifiedName:",14) == 0)  { uatype = &UA_TYPES[UA_TYPES_QUALIFIEDNAME]; isNum = 0; }
      else if(strncmp(itemvalue,"LocalizedText:",14) == 0)  { uatype = &UA_TYPES[UA_TYPES_LOCALIZEDTEXT]; isNum = 0; }
      else if(strncmp(itemvalue,"ExtensionObject:",16) == 0){ uatype = &UA_TYPES[UA_TYPES_EXTENSIONOBJECT]; isNum = 0; }
      else if(strncmp(itemvalue,"DataValue:",10) == 0)      { uatype = &UA_TYPES[UA_TYPES_DATAVALUE]; isNum = 0; }
      else if(strncmp(itemvalue,"Variant:",8) == 0)         { uatype = &UA_TYPES[UA_TYPES_VARIANT]; isNum = 0; }
      else if(strncmp(itemvalue,"DiagnosticInfo:",15) == 0) { uatype = &UA_TYPES[UA_TYPES_DIAGNOSTICINFO]; isNum = 0; }
      else
      {
	if(strchr(itemvalue,'.') != NULL) { uatype = &UA_TYPES[UA_TYPES_FLOAT]; isNum = 2; }
	else                              { uatype = &UA_TYPES[UA_TYPES_INT32]; isNum = 1; }
      }
      
      const char *cptr = strchr(itemvalue,':');
      if(cptr == NULL) cptr = itemvalue;
      else             cptr++;
      
      if(isNum)
      {
        if(isNum == 1)
        {
          value = atol(cptr);
          if(debug2) printf("try write value=%ld\n", value);
          wReq.nodesToWrite[0].value.value.type = uatype;
          wReq.nodesToWrite[0].value.value.storageType = UA_Variant::UA_VARIANT_DATA_NODELETE; //do not free the integer on deletion
          wReq.nodesToWrite[0].value.value.data = &value;
        }
        else
        {
          fvalue = atof(cptr);
          if(debug2) printf("try write fvalue=%f\n", fvalue);
          wReq.nodesToWrite[0].value.value.type = uatype;
          wReq.nodesToWrite[0].value.value.storageType = UA_Variant::UA_VARIANT_DATA_NODELETE; //do not free the integer on deletion
          wReq.nodesToWrite[0].value.value.data = &fvalue;
        }
      }
      else
      {
        UA_String ua_string;
        ua_string.length = strlen(cptr);
        ua_string.data = (UA_Byte *) cptr;
        if(debug2) printf("try write strvalue=%s\n", cptr);
        wReq.nodesToWrite[0].value.value.type = uatype;
        wReq.nodesToWrite[0].value.value.storageType = UA_Variant::UA_VARIANT_DATA_NODELETE; //do not free the integer on deletion
        wReq.nodesToWrite[0].value.value.data = &ua_string;
      }
    } 

    UA_WriteResponse wResp = UA_Client_write(client, &wReq);
    if(wResp.responseHeader.serviceResult == UA_STATUSCODE_GOOD)
    p->thread->unlock();

    UA_WriteRequest_deleteMembers(&wReq);
    UA_WriteResponse_deleteMembers(&wResp);
  }  
  return NULL;
}

int run(const char *url, int maxItemNameLength)
{
  long shmsize_needed = ((maxItemNameLength+1)+(max_name_length+1))*num_items + sizeof(SHM_HEADER);
  FILE *fin;
  char buf[1024], *cptr;
  void *shmadr;
  SHM_HEADER *shmheader;
  int  i;

  if(url == NULL) return 1;

  // print shm parameters
  printf("maxItemNameLength=%d max_name_length=%d shmsize=%ld shmsize_needed=%ld num_items=%d shm=%s\n",
          maxItemNameLength,   max_name_length,   shmsize,    shmsize_needed,    num_items,   shm);
  if(shmsize_needed > shmsize)
  {
    printf("shmsize too small -> increase it\n");
    return 1;
  }
  if(maxItemNameLength <= 0 || max_name_length <= 0 || shmsize <= 0 || shmsize_needed <= 0)
  {
    printf("some values are negative or 0\n");
    return 1;
  }
  if(maxItemNameLength >= (int) (sizeof(buf) - 100) || max_name_length >= (int) (sizeof(buf) - 100))
  {
    printf("name is bigger than buf length = %d\n", (int) sizeof(buf));
    return 1;
  }

  // init shared memory
  rlSharedMemory rlshm = rlSharedMemory(shm, (unsigned long) shmsize);
  if(rlshm.status != rlSharedMemory::OK)
  {
    printf("shared memory status is not OK\n");
    return 1;
  }
  shmadr = rlshm.getUserAdr();
  if(shmadr == NULL)
  {
    printf("shmadr = NULL\n");
    return 1;
  }
  memset(shmadr,0,shmsize);

  // read itemlist to shared memory
  fin = fopen(itemlist,"r");
  if(fin == NULL)
  {
    printf("could not open itemlist %s\n",itemlist);
    return 1;
  }
  i = 0;
  while(fgets(buf,sizeof(buf)-1,fin) != NULL)
  {
    if(buf[0] > ' ' && buf[0] != '#')
    {
      cptr = strchr(buf,'\n');
      if(cptr != NULL) *cptr = '\0';
      cptr = (char *) shmadr;
      cptr += sizeof(SHM_HEADER) + (i*(maxItemNameLength+1 + max_name_length+1));
      strcpy(cptr,buf);
      if(debug || debug2) printf("create_itemlist i=%d name=%s\n", i, cptr);
      i++;
    }
  }
  fclose(fin);

  // init header in shared memory
  shmheader = (SHM_HEADER *) shmadr;
  shmheader->maxItemNameLength = maxItemNameLength;
  shmheader->maxNameLength     = max_name_length;
  shmheader->numItems          = num_items;
  shmheader->readErrorCount    = 0;
  shmheader->writeErrorCount   = 0;
  strcpy(shmheader->ident,"opc");

  rlString rltmp;
  UA_ReadRequest rReq;
  UA_ReadRequest_init(&rReq);
  void *idptr = UA_Array_new(&UA_TYPES[UA_TYPES_READVALUEID], num_items);
  rReq.nodesToRead = (UA_ReadValueId*) idptr;
  rReq.nodesToReadSize = num_items;
  //rReq.nodesToRead = UA_ReadValueId_new();
  //rReq.nodesToReadSize = 1;
  //rReq.nodesToRead[0].nodeId = UA_NODEID_STRING_ALLOC(1, "the.answer"); /* assume this node exists */
  //rReq.nodesToRead[0].attributeId = UA_ATTRIBUTEID_VALUE;
  for(i=0; i<shmheader->numItems; i++)
  {
    cptr = (char *) shmadr;
    cptr += sizeof(SHM_HEADER) + (i*(maxItemNameLength+1 + max_name_length+1));
    rltmp = cptr;
    cptr = strchr(rltmp.text(),'#');
    if(cptr != NULL)
    {
      *cptr = '\0';
      cptr++;
      char *end = strchr(cptr,'#');
      if(end != NULL) *end = '\0';
      int ns = 0;
      sscanf(rltmp.text(),"%d",&ns);
      if(debug2) printf("name=\"%s\" ns=%d\n",cptr,ns);
      if(isdigit(*cptr) == 0) // *type == 'A')
      {
        rReq.nodesToRead[i].nodeId = UA_NODEID_STRING_ALLOC(ns, cptr); // assume this node exists
        rReq.nodesToRead[i].attributeId = UA_ATTRIBUTEID_VALUE;
      }
      else // *type == 'N')
      {
        rReq.nodesToRead[i].nodeId = UA_NODEID_NUMERIC(ns, atoi(cptr)); // assume this node exists
        rReq.nodesToRead[i].attributeId = UA_ATTRIBUTEID_VALUE;
      }
    } 
  }
  
  // create reader thread and the watchdog
  rlThread reader,watchdog;
  reader.create(reader_thread,(void *) url);
  watchdog.create(watchdog_thread,NULL);

  // poll the OPC UA server forever
  rlString rltxt;
  while(1)
  {
    UA_ReadResponse rResp = UA_Client_read(client, &rReq);
    if(rResp.responseHeader.serviceResult == UA_STATUSCODE_GOOD && rResp.resultsSize > 0)
    {
      /* write the result to the shared memory */
      reader.lock();
      for(i=0; i<shmheader->numItems; i++)
      {
        if(debug) 
        {
          printf("rResp.results[%d].hasValue=%d\n",i,rResp.results[i].hasValue);
          printf("UA_Variant_isScalar(&rResp.results[%d].value=%d\n",i,UA_Variant_isScalar(&rResp.results[i].value));
        }  
        rltxt.printf("ERROR");
        if(rResp.results[i].hasValue && UA_Variant_isScalar(&rResp.results[i].value)) 
        {
          if(debug) printf("rResp.results[%d].value.type=%ld\n",i,(long) rResp.results[i].value.type);
          if(rResp.results[i].value.type == &UA_TYPES[UA_TYPES_BOOLEAN])
          {
            int val = *(UA_Boolean*)rResp.results[i].value.data;
            if(debug) printf("the value is: Boolean=%d\n", val);
            rltxt.printf("%d",val);
          }
          else if(rResp.results[i].value.type == &UA_TYPES[UA_TYPES_SBYTE])
          {
            int val = *(UA_SByte*)rResp.results[i].value.data;
            if(debug) printf("the value is: SByte=%d\n", val);
            rltxt.printf("%d",val);
          }
          else if(rResp.results[i].value.type == &UA_TYPES[UA_TYPES_BYTE])
          {
            int val = *(UA_Byte*)rResp.results[i].value.data;
            if(debug) printf("the value is: Byte=%d\n", val);
            rltxt.printf("%d",val);
          }
          else if(rResp.results[i].value.type == &UA_TYPES[UA_TYPES_INT16])
          {
            int val = *(UA_UInt16*)rResp.results[i].value.data;
            if(debug) printf("the value is: Int16=%d\n", val);
            rltxt.printf("%d",val);
          }
          else if(rResp.results[i].value.type == &UA_TYPES[UA_TYPES_UINT16])
          {
            unsigned int val = *(UA_UInt16*)rResp.results[i].value.data;
            if(debug) printf("the value is: UInt16=%d\n", val);
            rltxt.printf("%d",val);
          }
          else if(rResp.results[i].value.type == &UA_TYPES[UA_TYPES_INT32])
          {
            int val = *(UA_Int32*)rResp.results[i].value.data;
            if(debug) printf("the value is: Int32=%d\n", val);
            rltxt.printf("%d",val);
          }
          else if(rResp.results[i].value.type == &UA_TYPES[UA_TYPES_UINT32])
          {
            unsigned int val = *(UA_UInt32*)rResp.results[i].value.data;
            if(debug) printf("the value is: UInt32=%d\n", val);
            rltxt.printf("%d",val);
          }
          else if(rResp.results[i].value.type == &UA_TYPES[UA_TYPES_INT64])
          {
            long val = *(UA_Int64*)rResp.results[i].value.data;
            if(debug) printf("the value is: Int64=%ld\n", val);
            rltxt.printf("%ld",val);
          }
          else if(rResp.results[i].value.type == &UA_TYPES[UA_TYPES_UINT64])
          {
            unsigned long val = *(UA_UInt64*)rResp.results[i].value.data;
            if(debug) printf("the value is: UInt64=%ld\n", val);
            rltxt.printf("%ld",val);
          }
          else if(rResp.results[i].value.type == &UA_TYPES[UA_TYPES_FLOAT])
          {
            double val = *(UA_Double*)rResp.results[i].value.data;
            if(debug) printf("the value is: FLOAT=%f\n", (float) val);
            rltxt.printf("%f",(float) val);
          }
          else if(rResp.results[i].value.type == &UA_TYPES[UA_TYPES_DOUBLE])
          {
            double val = *(UA_Double*)rResp.results[i].value.data;
            if(debug) printf("the value is: DOUBLE=%f\n", (float) val);
            rltxt.printf("%f",(float) val);
          }
          else if(rResp.results[i].value.type == &UA_TYPES[UA_TYPES_STRING])
          {
            UA_Variant value = rResp.results[i].value;
            UA_String *ua_string = (UA_String*) value.data;
            //members:
            //  UA_Int32 length;
            //  UA_Byte *data;
            if(ua_string->length >= 0)
            {
              char txt[ua_string->length + 1];
              strncpy(txt,(const char *) ua_string->data,ua_string->length);
              txt[ua_string->length] = '\0';
              if(debug) printf("the value is: STRING=%s\n",txt);
              rltxt.printf("%s",txt);
            }
            else
            {
              printf("Error: ua_string->length=%d\n", ua_string->length);
            }
          }
          else if(rResp.results[i].value.type == &UA_TYPES[UA_TYPES_DATETIME])
          {
            long val = *(UA_Int64*)rResp.results[i].value.data;
            if(debug) printf("the value is: DATETIME Int64=%ld\n", val);
            rltxt.printf("%ld", val);
          }
          else if(rResp.results[i].value.type == &UA_TYPES[UA_TYPES_GUID])
          {
            printf("the value is: GUID (NOT IMPLEMENTED)\n");
          }
          else if(rResp.results[i].value.type == &UA_TYPES[UA_TYPES_BYTESTRING])
          {
            UA_Variant value = rResp.results[i].value;
            UA_String *ua_string = (UA_String*) value.data;
            //members:
            //  UA_Int32 length;
            //  UA_Byte *data;
            if(ua_string->length >= 0)
            {
              char txt[ua_string->length + 1];
              strncpy(txt,(const char *) ua_string->data,ua_string->length);
              txt[ua_string->length] = '\0';
              if(debug) printf("the value is: BYTESTRING=%s\n", txt);
              rltxt.printf("%s",txt);
            }
            else
            {
              printf("Error: ua_string->length=%d\n", ua_string->length);
            }
          }
          else if(rResp.results[i].value.type == &UA_TYPES[UA_TYPES_XMLELEMENT])
          {
            UA_Variant value = rResp.results[i].value;
            UA_String *ua_string = (UA_String*) value.data;
            //members:
            //  UA_Int32 length;
            //  UA_Byte *data;
            if(ua_string->length >= 0)
            {
              char txt[ua_string->length + 1];
              strncpy(txt,(const char *) ua_string->data,ua_string->length);
              txt[ua_string->length] = '\0';
              if(debug) printf("the value is: XMLELEMENT=%s\n", txt);
              rltxt.printf("%s",txt);
            }
            else
            {
              printf("Error: ua_string->length=%d\n", ua_string->length);
            }
          }
          else if(rResp.results[i].value.type == &UA_TYPES[UA_TYPES_NODEID])
          {
            printf("the value is: NODEID (NOT IMPLEMENTED)\n");
          }
          else if(rResp.results[i].value.type == &UA_TYPES[UA_TYPES_EXPANDEDNODEID])
          {
            printf("the value is: EXPANDEDNODEID (NOT IMPLEMENTED)\n");
          }
          else if(rResp.results[i].value.type == &UA_TYPES[UA_TYPES_STATUSCODE])
          {
            printf("the value is: STATUSCODE (NOT IMPLEMENTED)\n");
          }
          else if(rResp.results[i].value.type == &UA_TYPES[UA_TYPES_QUALIFIEDNAME])
          {
            printf("the value is: QUALIFIEDNAME (NOT IMPLEMENTED)\n");
          }
          else if(rResp.results[i].value.type == &UA_TYPES[UA_TYPES_LOCALIZEDTEXT])
          {
            printf("the value is: LOCALIZEDTEXT (NOT IMPLEMENTED)\n");
          }
          else if(rResp.results[i].value.type == &UA_TYPES[UA_TYPES_EXTENSIONOBJECT])
          {
            printf("the value is: EXTENSIONOBJECT (NOT IMPLEMENTED)\n");
          }
          else if(rResp.results[i].value.type == &UA_TYPES[UA_TYPES_DATAVALUE])
          {
            printf("the value is: DATAVALUE (NOT IMPLEMENTED)\n");
          }
          else if(rResp.results[i].value.type == &UA_TYPES[UA_TYPES_VARIANT])
          {
            printf("the value is: VARIANT (NOT IMPLEMENTED)\n");
          }
          else if(rResp.results[i].value.type == &UA_TYPES[UA_TYPES_DIAGNOSTICINFO])
          {
            printf("the value is: DIAGNOSTICINFO (NOT IMPLEMENTED)\n");
          }
          else
          {
            printf("the value is: NOT AN IMPLEMENTED TYPE\n");
          }
        }
        else
        {
          printf("the value is: NOT GOOD itemlist.item=%d\n", i);
        }

        /* write the result to the shared memory */
        char *shmnames  = (char *) shmadr; shmnames += sizeof(SHM_HEADER);
        char *itemname  = shmnames + i*(shmheader->maxItemNameLength+1 + shmheader->maxNameLength+1);
        char *itemvalue = itemname + shmheader->maxItemNameLength + 1;
        if(debug2) printf("WriteToSHM(%s) i=%d\n", rltxt.text(), i);
        if(strlen(rltxt.text()) <= (unsigned int) max_name_length)
        {
          strcpy(itemvalue,rltxt.text());
        }
        else
        {
          strcpy(itemvalue,"Error");
        }
      }
      reader.unlock();        
    }
    else if(rResp.responseHeader.serviceResult == UA_STATUSCODE_GOOD && rResp.resultsSize <= 0)
    {
      printf("UA_STATUSCODE_GOOD but resultSize=%d\n", rResp.resultsSize);      
    }
    else
    {
      printf("The response is: NOT GOOD\n");
      printf("rResp.responseHeader.serviceResult=%d\n",rResp.responseHeader.serviceResult);
      printf("rResp.resultsSize=%d\n",rResp.resultsSize);
      shmheader->readErrorCount++;
      if(shmheader->readErrorCount > 256*256) shmheader->readErrorCount = 0;
    }

    UA_ReadResponse_deleteMembers(&rResp);
    watchcnt1++;
    if(watchcnt1 > 256*256) watchcnt1 = 0;
    rlsleep(sleep);
    if(debug2) printf("\n\nnext request\n");;
  }
  UA_ReadRequest_deleteMembers(&rReq);
  return 0;
}

int getMaxItemNameLength()
{
  FILE *fin;
  char line[1024];
  int  ret,len;

  fin = fopen(itemlist,"r");
  if(fin == NULL)
  {
    printf("could not open itemlist %s\n",itemlist);
    return 0;
  }

  ret = num_items = 0;
  while(fgets(line,sizeof(line)-1,fin) != NULL)
  {
    if(line[0] > ' ' && line[0] != '#')
    {
      len = strlen(line);
      if(len > ret) ret = len;
      num_items++;
    }
  }

  fclose(fin);
  return ret;
}

static int conv2string(int length, const char *sou, char *dest)
{
  for(int i=0; i<length; i++) *dest++ = *sou++;
  *dest = '\0';
  return 0;
}

int main(int argc, char *argv[])
{
  char *url,*method,*arg;
  int i;

  /* check the command line parameters */
  if(argc < 3)
  {
    printusage(argv[0]);
    return 1;
  }
  arg = argv[0];
  strcpy(startme,arg);
  for(i=1; i<argc; i++)
  {
    arg = argv[i];
    strcat(startme," ");
    strcat(startme,arg);
  }
  url    = argv[1];
  method = argv[2];
  for(i=3; i<argc; i++)
  {
    arg = argv[i];
    if(strlen(arg) <= MAX_PATH_LENGTH)
    {
      if(strncmp(arg,"-itemlist=",10) == 0)
      {
        sscanf(arg,"-itemlist=%s",itemlist);
      }
      if(strncmp(arg,"-shm=",5) == 0)
      {
        sscanf(arg,"-shm=%s",shm);
      }
      if(strncmp(arg,"-mbx=",5) == 0)
      {
        sscanf(arg,"-mbx=%s",mbx);
      }
      if(strncmp(arg,"-sleep=",7) == 0)
      {
        sscanf(arg,"-sleep=%d",&sleep);
        if(sleep < 10) sleep = 10;
      }
      if(strncmp(arg,"-max_name_length=",17) == 0)
      {
        sscanf(arg,"-max_name_length=%d",&max_name_length);
        if(max_name_length < 31) max_name_length = 31;
      }
      if(strncmp(arg,"-shmsize=",8) == 0)
      {
        sscanf(arg,"-shmsize=%ld",&shmsize);
        if(shmsize < 1) shmsize = 1;
      }
      if(strcmp(arg,"-longname") == 0)
      {
        longname = 1;
      }
      if(strcmp(arg,"-debug") == 0)
      {
        debug = 1;
      }
    }
    else
    {
      printf("%s is too long.\n", arg);
      return 1;
    }
  }

  /* init UA client */
  client = UA_Client_new(UA_ClientConfig_standard, Logger_Stdout_new());
  UA_StatusCode retval = UA_Client_connect(client, ClientNetworkLayerTCP_connect, url);
  if(retval != UA_STATUSCODE_GOOD) 
  {
    UA_Client_delete(client);
    return retval;
  }

  if(strcmp(method,"GetStatus") == 0)
  {
    printf("GetStatus only implemented in OPCXMLDA ???\n");
    return 0;
  }
  else if(strcmp(method,"Browse") == 0)
  {
    UA_BrowseRequest bReq;
    UA_BrowseRequest_init(&bReq);
    bReq.requestedMaxReferencesPerNode = 0;
    bReq.nodesToBrowse = UA_BrowseDescription_new();
    bReq.nodesToBrowseSize = 1;
    bReq.nodesToBrowse[0].nodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER); //browse objects folder
    bReq.nodesToBrowse[0].resultMask = UA_BROWSERESULTMASK_ALL; //return everything

    UA_BrowseResponse bResp = UA_Client_browse(client, &bReq);
    //printf("%-9s %-16s %-16s %-16s\n", "NAMESPACE", "NODEID", "BROWSE NAME", "DISPLAY NAME");
    printf("####################################################\n");
    printf("#%s %s %s\n",argv[0],url,method);
    printf("#\n");
    printf("# Itemlist := %s#%s#%s#%s\n", "NAMESPACE", "NODEID", "BROWSE NAME", "DISPLAY NAME");
    printf("# Lines starting with # are treated as comment lines\n");
    printf("####################################################\n");
    for (int i = 0; i < bResp.resultsSize; ++i) 
    {
      for (int j = 0; j < bResp.results[i].referencesSize; ++j) 
      {
        UA_ReferenceDescription *ref = &(bResp.results[i].references[j]);
        int maxlen = ref->nodeId.nodeId.identifier.string.length;
        if(maxlen < ref->browseName.name.length)  maxlen = ref->browseName.name.length;
        if(maxlen < ref->displayName.text.length) maxlen = ref->displayName.text.length;
        maxlen += 1;
        char s1[maxlen], s2[maxlen], s3[maxlen];
        if(ref->nodeId.nodeId.identifierType ==  UA_NodeId::UA_NODEIDTYPE_NUMERIC) 
        {
          //printf("%-9d %-16d %-16.*s %-16.*s\n", ref->browseName.namespaceIndex,
          //       ref->nodeId.nodeId.identifier.numeric, ref->browseName.name.length,
          //       ref->browseName.name.data, ref->displayName.text.length, ref->displayName.text.data);
          conv2string(ref->browseName.name.length, (const char *) ref->browseName.name.data, s1);       
          conv2string(ref->displayName.text.length, (const char *) ref->displayName.text.data, s2);       
          if(longname) printf("%d#%d#%s#%s\n", ref->browseName.namespaceIndex, ref->nodeId.nodeId.identifier.numeric, s1, s2);
          else         printf("%d#%d\n", ref->browseName.namespaceIndex, ref->nodeId.nodeId.identifier.numeric);
        } 
        else if(ref->nodeId.nodeId.identifierType ==  UA_NodeId::UA_NODEIDTYPE_STRING) 
        {
          //printf("%-9d %-16.*s %-16.*s %-16.*s\n", ref->browseName.namespaceIndex,
          //       ref->nodeId.nodeId.identifier.string.length, ref->nodeId.nodeId.identifier.string.data,
          //       ref->browseName.name.length, ref->browseName.name.data, ref->displayName.text.length,
          //       ref->displayName.text.data);
          conv2string(ref->nodeId.nodeId.identifier.string.length, (const char *) ref->nodeId.nodeId.identifier.string.data, s1);       
          conv2string(ref->browseName.name.length, (const char *) ref->browseName.name.data, s2);       
          conv2string(ref->displayName.text.length, (const char *) ref->displayName.text.data, s3);       
          if(longname) printf("%d#%s#%s#%s\n", ref->browseName.namespaceIndex, s1, s2, s3);
          else         printf("%d#%s\n", ref->browseName.namespaceIndex, s1);
        }
        //TODO: distinguish further types
      }
    }
    UA_BrowseRequest_deleteMembers(&bReq);
    UA_BrowseResponse_deleteMembers(&bResp);
    return 0;
  }
  else if(strcmp(method,"Run") == 0)
  {
    i = getMaxItemNameLength();
    if(i > 0) i = run(url,i);
    return i;
  }
  else
  {
    printusage(argv[0]);
  }  

  UA_Client_disconnect(client);
  UA_Client_delete(client);
  return 0;
}
