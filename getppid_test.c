#include  <unistd.h>
#include  <stdio.h>
#include  <stdlib.h>

int main()
{
  pid_t pid;

  pid = fork();

  if(pid<0)
  {
    printf("fork error");
    exit(1);
  }
  else if (pid == 0)
  {
    printf("[child]");
    printf("my pid is %d\n", getpid());
    printf("my ppid is %d\n", getppid());
  }
  else
  {
    printf("[parent]");
    printf("my pid is %d\n", getpid());
    printf("my ppid is %d\n", getppid());
  }
}