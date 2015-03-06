#include <stdio.h>
#include <arpa/inet.h> 
int main() {
    int a = 0x12345678;
    int b = htonl(a);
    char *ptr = (char *)&a;
    if (*ptr == 0x12)
        printf("Big Endian\n");
    else if(*ptr == 0x78)
        printf("Little Endian \n");


    if(b==a)
      printf("Big Endian\n");
    else
      printf("Little Endian b %d a %d\n",b,a);


    return 0;
}
