#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
int main()
{
    uint8_t a[20];
    uint8_t *b;
    b=a;
    printf("Hello world! size is %d\n",sizeof(b));
    return 0;
}
