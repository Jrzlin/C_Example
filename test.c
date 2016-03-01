#include <stdio.h>
#include <stdlib.h>

#define PI 3.14
void Roundness(float, float *, float *);
int main(void)
{
  float r = 0, area = 0, circumference = 0;
  printf("Input n:");
  scanf("%f", &r);

  Roundness(r, &area, &circumference);
  printf("半徑: %f 單位 \n面積: %f 平方單位 \n周長: %f 單位\n\n\n", r, area, circumference);

  return 0;
}

void Roundness(float r, float *area, float *perimeter)
{
  *area = r*r*PI;
  *perimeter=r*2*PI;
}
