#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

typedef  unsigned char u8;

void GetUnixTime_YYYYMMDD(const u8* input, u8 *output);
void CopyDat( u8* output,u8 *input,const u8 bytes) ;


int main()
{
    uint8_t tmp[4]= { 0x28, 0xA0, 0x37,0x59};
    uint8_t tmp1[7];
    GetUnixTime_YYYYMMDD((const u8*)&tmp,(u8*)&tmp1);
    printf("Hello world!\n");
    return 0;
}

void CopyDat( u8* output,u8 *input,const u8 bytes)
{
    u8 num;
    for (num = 0; num < bytes; num++)
        *(output + num) = *(input + num);
}
void GetUnixTime_YYYYMMDD(const u8* input, u8 *output)
{
    //    u8 cnt;
    time_t tmp;
    struct tm* gmt;

    CopyDat((u8*) & tmp, input, 4); //´ý²âÊÔ
    gmt = gmtime(&tmp);
    *output = gmt->tm_year >> 8;
    *(output + 1) = gmt->tm_year & 0x00FF;
    *(output + 2) = (gmt->tm_mon + 1);
    *(output + 3) = gmt->tm_mday;
    *(output + 4) = gmt->tm_hour;
    *(output + 5) = gmt->tm_min;
    *(output + 6) = gmt->tm_sec;
}
