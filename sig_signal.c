#include  <unistd.h>
#include  <signal.h>
#include  <stdio.h>

void handler(int signum);

int main()
{
  signal(SIGTSTP, (void*)handler);

  while(1){}
}

void handler(int signum)
{
  printf("This is SIGTSTP(%d)'s new handler!\n", SIGTSTP);
}