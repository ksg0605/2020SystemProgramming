#include  <unistd.h>
#include  <stdio.h>

int main()
{
  int pid;

  printf("[Before fork]\n");
  printf("my pid is %d\n", getpid());

  pid = fork();

  if(pid < 0)
  {
    printf("fork error\n");
  }
  else if (pid == 0)
  {
    printf("[Child]\n");
    printf("my pid is %d\n", getpid());
  }
  else
  {
    printf("[Parent]");
    printf("my pid is %d\n", getpid());
  }
}