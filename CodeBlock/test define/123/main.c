#include <stdio.h>
#include <stdlib.h>

#define adc(x,y) TRIS##x##bits.TRIS##x##y
struct TR{
   int TRISD1;
}
TRISDbits;

#define TIRSD(x) TRISDbits.TRISD##x

int main()
{
    TIRSD(1)=3;

    printf("Hello world!\n");
    printf("%d",adc(D,1));
    return 0;
}
