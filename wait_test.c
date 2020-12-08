#include  <stdio.h>
#include  <stdlib.h>
#include  <sys/types.h>
#include  <unistd.h>

int glob = 6;

int main()
{
  int var = 88;
  pid_t pid;
  int status;

  pid = fork();
  
  if(pid<0)
  {
    perror("fork error");
    exit(1);
  }
  else if (pid == 0)
  {
    glob++;
    var++;
  }
  else
  {
    wait(&status);
  }

  printf("pid = %d, glob = %d, var = %d\n", getpid(), glob, var);
  exit(0);
}