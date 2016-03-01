#include <stdio.h>
#include <stdlib.h>

void Arithmetic(void)
{
  int a = 0,b = 0,c = 0;
  a = 60;
  b = 6;
  
  c = a + b;
  fprintf(stderr, "a + b = %d\n", c);
}

void main(void)
{
  int a = 1;
  int b = 15;
  printf("%d\n", a++);
  printf("%d\n", ++a);
  printf("%d\n", a++);
  printf("%d\n", a);
  printf("%x\n",b);

  unsigned char c = 205;
  unsigned char d = 0x9e; 

  printf("a = %c\n", c);
  printf("b = %c\n", d);

}
