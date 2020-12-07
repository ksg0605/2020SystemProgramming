#include  <stdio.h>

int func2(int x ,int y)
{
  int f2_local1 = 21;
  int f2_local2 = 22;
  int *ptr;

  ptr = &f2_local1;

  printf("\t%p  \t%d\n", (ptr), *(ptr));
  printf("\t%p  \t%d\n", (ptr-1), *(ptr-1));
  printf("\t%p  \t%d\n", (ptr+2), *(ptr+2));

  *(ptr+1) = 333;

  printf("\t\t y \t\t %d\n", y);

  return 222;
}

void func1()
{
  int ret_val;
  int f1_local1 = 11;
  int f2_local2 = 12;

  ret_val = func2(111, 112);
}

int main()
{
  func1();
}