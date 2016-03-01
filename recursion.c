#include <stdio.h>

long fn(long n) 
{
  if(n<=0) {
    printf("error: n must > 0");
    return 0;
  }
  if(0 == n%2)
    return (n/2)*(-1);
  else
    return (n/2)*(-1)+n;
}

int fact(int n)
{
  if (n == 1){
    printf("%d = ",n);
    return n;
  }else{
    printf("%d * ",n);
    return fact(n-1)*n;
  }
}

int main(void)
{
  int num;
  long max_num;
  printf("Input N : ");
  scanf("%d",&num);
  int value = fact(num);
  printf("\n The factorial of [%d] is [%d]\n", num, value);

  printf("%ld\n", fn(5));
  return 0;
}
