#include  <errno.h>
#include  <fcntl.h>
#include  <stdio.h>
#include  <stdlib.h>
#include  <unistd.h>

#define MAX_BUF 64

char fname[] = "test.txt";

int main()
{
  int fd, read_size, write_size;
  char buf[MAX_BUF];

  fd = open(fname, O_RDONLY);
  if(fd<0)
  {
   printf("Can't open %s file with errno %d\n", fname, errno);
   exit(1); 
  }

  read_size = read(fd, buf, MAX_BUF);
  if(read_size<0)
  {
    printf("Can't read from file %s, read_size = %d\n", fname, read_size);
    exit(1);
  }

  write_size = write(1, buf, read_size);
  printf("\nwrite_size: %d\n", write_size);
  if(write_size<0)
  {
    printf("Can't write, write_size = %d\n", write_size);
    exit(1);
  }
  close(fd);
}
