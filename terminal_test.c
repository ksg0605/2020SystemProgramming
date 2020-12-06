#include  <stdio.h>
#include  <stdlib.h>
#include  <unistd.h>
#include  <errno.h>
#include  <fcntl.h>
#include  <sys/types.h>
#include  <sys/stat.h>

#define MAX_BUF 64

char fname[] = "test.txt";
char tmp_data[] = "abcdefghijk";

int main()
{
  int fd, size;
  char buf[MAX_BUF];

  fd = open(fname, O_RDWR | O_CREAT | S_IRUSR | S_IWUSR);
  if(fd<0)
  {
    printf("Can't open %s file with errno %d\n", fname, errno);
    exit(1);
  }
  write(fd, tmp_data, sizeof(tmp_data));
  close(fd);

  fd = open("/dev/pts/48", O_WRONLY);
  if(fd<0)
  {
    printf("Can't open with error %d\n", errno);
    exit(1);
  }
  write(fd, buf, MAX_BUF);
  close(fd);
}