#include  <stdio.h>

int a= 20, b = 30;
int c;

int main()
{
  a = 2;
  b = a;
  c = a + b;

  printf("c = %d\n", c);
}