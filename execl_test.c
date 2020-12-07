#include  <stdio.h>
#include  <stdlib.h>
#include  <sys/types.h>
#include  <unistd.h>

int main(int argc, char *argv[])
{
  pid_t pid, d_pid;
  int exit_status;

  pid = fork();

  if(pid == -1)
  {
    perror("fork error");
    exit(1);
  }
  else if (pid == 0)
  {
    execl("/bin/ls", "ls", "-l", (char *)0);
    printf("[Child] pid = %d, ppid = %d\n", getpid(), getppid());
    exit(1);
  }
  else
  {
    printf("pid = %d\n", pid);
    d_pid = wait(&exit_status);
    printf("exit status of task %d is %d\n", d_pid, exit_status);
  }
}