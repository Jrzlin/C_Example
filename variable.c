#include <stdio.h>
int main(void)
{
  printf("Case1: variable size(Byte) under this system\n");
  printf("       int (%d) char (%d)\n",sizeof(int),sizeof(char));
  printf("       long (%d) float (%d) double (%d)\n",sizeof(long),sizeof(float),sizeof(double));
  printf("       short (%d)\n",sizeof(short));

  int a = 15;
  printf("HEX : 0x%02x 0X%02X\n",a,a);
}
