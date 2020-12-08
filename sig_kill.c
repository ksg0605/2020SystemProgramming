#include  <sys/types.h>
#include  <signal.h>
#include  <stdio.h>
#include  <stdlib.h>

int main(int argc, char **argv)
{
  int pid;
  int sig_num;

  if(argc !=3)
  {
    printf("usage %s [pid] [signum]\n", argv[0]);
    exit(0);
  }

  pid = atoi(argv[1]);
  sig_num = atoi(argv[2]);

  if(kill(pid, sig_num) != 0)
  {
    printf("Signal Send Error!\n");
    exit(1);
  }
}