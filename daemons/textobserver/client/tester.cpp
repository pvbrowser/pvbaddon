#include <stdio.h>
#include <unistd.h>
static int        linebufferReady = 0;

#ifdef _WIN32
#include <windows.h>
#include <conio.h>
static const int  MAXLINE = 1024;
static HANDLE     stdinHandle = NULL;
static char       linebuffer[MAXLINE];
static DWORD      numberOfBytesToRead = MAXLINE;
static OVERLAPPED overlapped;
VOID CALLBACK fileIOCompletionRoutine(
                DWORD dwErrorCode,
                DWORD dwNumberOfBytesTransfered,
                LPOVERLAPPED lpOverlapped
              )
{
  linebufferReady = 1;
  //printf("async got dwErrorCode=%d\n", dwErrorCode);
  return;
}
#else
#include <sys/select.h>
#endif


int inputAvailable()
{
#ifdef _WIN32
  // Windows bullshit does not work like described in MSDN
  BOOL ret;
  // If the function succeeds, the return value is nonzero (TRUE).
  // If the function fails, or is completing asynchronously, the return value is zero (FALSE).
  if(linebufferReady == 1)
  {
    return 1;
  }
  else if(linebufferReady == 0)
  {
    linebufferReady = -1;
    ret = ReadFileEx(stdinHandle, linebuffer, numberOfBytesToRead, &overlapped,  fileIOCompletionRoutine);
  }
  else
  {
    return 0;
  }
  return (int) ret;
#else
  struct timeval timout;
  fd_set wset,rset,eset;
  int ret,maxfdp1;
  int s = 0;
  /* setup sockets to read */
  maxfdp1 = s+1;
  FD_ZERO(&rset);
  FD_SET (s,&rset);
  FD_ZERO(&wset);
  FD_ZERO(&eset);
  timout.tv_sec = 0;
  timout.tv_usec = 0;
  ret = ::select(maxfdp1,&rset,&wset,&eset,&timout);
  if(ret == 0) return 0; /* timeout */
  return 1;
#endif  
}

int main()
{
#ifdef _WIN32
  COMMTIMEOUTS commTimeouts; // A value of MAXDWORD, combined with zero values for both the ReadTotalTimeoutConstant and ReadTotalTimeoutMultiplier members, 
                             // specifies that the read operation is to return immediately with the bytes that have already been received, 
                             // even if no bytes have been received.
  commTimeouts.ReadIntervalTimeout         = 0; // The maximum time allowed to elapse before the arrival of the next byte on the communications line
  commTimeouts.ReadTotalTimeoutMultiplier  = 0; // The multiplier used to calculate the total time-out period for read operations, in milliseconds.
  commTimeouts.ReadTotalTimeoutConstant    = 0; // The multiplier used to calculate the total time-out period for read operations, in milliseconds.
  commTimeouts.WriteTotalTimeoutMultiplier = 0;
  commTimeouts.WriteTotalTimeoutConstant   = 0;
  stdinHandle = GetStdHandle(STD_INPUT_HANDLE);
  SetCommTimeouts(stdinHandle,&commTimeouts);
#endif  
  char line[4096];
  for(int i=0; i<1024; i++)
  {
    if(inputAvailable())
    {
#ifdef _WIN32
      strncpy(line,linebuffer,sizeof(line));
      line[sizeof(line)-1] = '\0';
      linebufferReady = 1;
#else
      fgets(line,sizeof(line)-1,stdin);
#endif      
      printf("got line=%s", line);
    }
    printf("<html><body><pre>\n");
    printf("line1   i=%d linebufferReady=%d\n", i, linebufferReady);
    printf("line2\n");
    printf("line3\n");
    printf("line...\n");
    //printf("EndOfFrame\n");
    printf("</pre></body></html>\n");
    fprintf(stderr,"Frame %d\n", i);
    fflush(stdout);
    sleep(1);
  }
}
