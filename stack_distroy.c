#include  <stdio.h>

void f1()
{
  int i;

  printf("In func1\n");
}

void f2()
{
  int j, *ptr;

  printf("In func2\n");

  ptr = &j;
  //*(ptr + 2) = f1;
}

void f3()
{
  printf("In func3\n");
  printf("Before invoke f2\n");

  f2();
  printf("After invoke f2\n");
}

int main()
{
  f3();
}