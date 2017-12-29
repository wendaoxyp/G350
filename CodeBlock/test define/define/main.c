#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct a
{
    unsigned a1:8;
    unsigned a2:3;
    unsigned a3:5;
} ABITS;

int main()
{
    ABITS abits;
    abits.a1=0xff;
    abits.a2=1;
    abits.a3=1;
    abits.a3=1;
        printf("Hello world!\n%d",abits.a1|(abits.a2<<8)|(abits.a3<<11));
    return 0;
}


