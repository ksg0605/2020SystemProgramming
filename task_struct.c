#include  <stdlib.h>
#include  <stdio.h>

int glob1, glob2;

int func2()
{
  int f2_local1, f2_local2;

  printf("func2 local: \n \t%p, \n \t%p\n", &f2_local1, &f2_local2);
}

int func1()
{
  int f1_local1, f1_local2;

  printf("func1 local: \n \t%p, \n \t%p\n", &f1_local1, &f1_local2);
  func2();
}

int main()
{
  int m_local1, m_local2;
  int *dynamic_addr;

  printf("main local: \n \t%p, \n \t%p\n", &m_local1, &m_local2);
  func1();

  dynamic_addr = malloc(16);

  printf("dynamic: \n\t\%p\n", dynamic_addr);
  printf("global: \n\t%p, \n\t%p\n", &glob2, &glob1);
  printf("functions: \n\t%p, \n\t%p, \n\t%p\n", main, func1, func2);
}