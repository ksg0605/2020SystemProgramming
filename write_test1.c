#include  <errno.h>
#include  <fcntl.h>
#include  <unistd.h>
#include  <stdio.h>
#include  <stdlib.h>

#define MAX_BUF 64

char fname[] = "newfile.txt";
char dummy_data[] = "abcdefg\n";

int main()
{
  int fd, write_size, read_size;
  char buf[MAX_BUF];

  fd = open(fname, O_RDWR | O_CREAT | O_TRUNC, 0064);
  if(fd<0)
  {
    printf("Can't create %s file with errno %d\n", fname, errno);
    exit(1);
  }

  write_size = write(fd, dummy_data, sizeof(dummy_data));
  close(fd);

  fd = open(fname, O_RDONLY);
  if(fd<0)
  {
    printf("Can't open %s fiel with errno %d\n", fname, errno);
    exit(1);
  }

  read_size = read(fd, buf, MAX_BUF);
  if(read_size<0)
  {
    printf("Can't read from file %s, read_size = %d\n", fname, read_size);
    exit(1);
  }

  printf("read_size = %d\n", read_size);
  write_size = write(STDOUT_FILENO, buf, read_size);
  close(fd);
}