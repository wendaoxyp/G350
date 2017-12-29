#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
    unsigned int ALRMVAL[3];
    struct tm initialTime;
    unsigned char cnt;

    initialTime.tm_mon=0x10;
    initialTime.tm_mday=0x20;
    initialTime.tm_wday=0;
    initialTime.tm_hour=0x10;
    initialTime.tm_min=0x30;
    initialTime.tm_sec=0x15;
    ALRMVAL[0] = /*0x1006;*/(initialTime.tm_mon << 8) + initialTime.tm_mday; // MONTH-1/DAY-1
    ALRMVAL[1] = /*0x0012;*/(initialTime.tm_wday << 8) + initialTime.tm_hour; // WEEKDAY/HOURS
    ALRMVAL[2] = /*0x3017;*/(initialTime.tm_min << 8) + initialTime.tm_sec; // MINUTES/S
    for(cnt=0;cnt<sizeof(ALRMVAL)/sizeof(unsigned int);cnt++)
        printf("ALRMVAL[%d]=%x\n",cnt,ALRMVAL[cnt]);
    return 0;
}
