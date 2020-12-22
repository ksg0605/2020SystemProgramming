#include  <stdio.h>

int a, incr_a;
short sword;
char sbyte;
int arr[10];

int main()
{
  a = 64;
  incr_a = a + 1;
  sword = a;
  sbyte = incr_a;
  arr[2] = 7;

  printf("sword = %hd\n", sword);
  printf("sbyte = %c\n", sbyte);
}