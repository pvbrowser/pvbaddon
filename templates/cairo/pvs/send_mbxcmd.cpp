#include "pvapp.h"
rlMailbox loopmbx(LOOPMBX);

int main(int ac, char **av)
{
  if(ac != 2)
  {
    printf("usage: send_mbxcmd string\n");
    return -1;
  }
  printf("sending: %s\n", av[1]);
  loopmbx.printf("%s\n", av[1]);  
  return 0;
}
