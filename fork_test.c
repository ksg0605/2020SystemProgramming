#include  <stdio.h>
#include  <stdlib.h>
#include  <sys/types.h>
#include  <unistd.h>

int main()
{
  pid_t pid;

  printf("Before fork(): pid = %d\n", getpid());

  pid = fork();

  if(pid<0)
  {
    perror("fork error");
    exit(1);
  }
  else if (pid == 0)
  {
    printf("After fork(): \n");
    printf("[child] pid = %d, ppid = %d\n", getpid(), getppid());
  }
  else
  {
    printf("After fork(): \n");
    printf("[parent] I create child with pid = %d\n", pid);
  }

  printf("\tBye, my pid is %d\n", getpid());
  
  
}