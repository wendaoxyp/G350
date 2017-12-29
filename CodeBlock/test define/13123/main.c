#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

bool UART_Is_Get(uint8_t* sdata, uint8_t* cdata, const uint8_t sbytes, const uint8_t cbytes) {
    uint8_t sbyte, cbyte;
    bool b = false;
    for (sbyte = 0; sbyte < sbytes; sbyte++){
        if(*(sdata+sbyte)==*(cdata))
        for (cbyte = 0; cbyte < cbytes; cbyte++)
            if (*(sdata + sbyte + cbyte) == *(cdata + cbyte))
                b = true;
            else {
                b = false;
                break;
            }
    if(b) break;
}
    return b;
}
int main()
{
    uint8_t sdat[]="1234567890123465";
    uint8_t rdat[]="901";
    if(UART_Is_Get(sdat,rdat,15,3))
    printf("Hello world!\n");
    else
        printf("Not find!!\n");
    return 0;
}
