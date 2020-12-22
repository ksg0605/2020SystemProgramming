#include  <stdio.h>

int func2();
extern func1();

int a = 7;
static int b = 2;
int c;
int d = 8;

int main()
{
  int local;

  a = 123;

  func1();
  func2();
}

int func2()
{
  c = d;
}