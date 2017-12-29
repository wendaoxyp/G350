#include "Common.h"
#include <xc.h>
/*************************************
Function: FloatToChar 
Description: 浮点数转化为char数组
Input: 输入浮点数 模式：4 单精度浮点数 8 双精度浮点数 
Output: 输出数值
 *************************************/
void FloatToChar(float *f, uint8_t *ch) {
    uint8_t count;
    void * pf;
    pf = f;

    for (count = 0; count < 4; count++) {
        *(ch + count) = *((uint8_t *) pf + 3 - count);
    }
}

/*************************************
Function: CharToFloat 
Description: char数组转化为浮点数 
Input: 输出数值    模式：4 单精度浮点数 8 双精度浮点数 
Output: 输入浮点数
 *************************************/
void CharToFloat(float *f, uint8_t *ch) {
    uint8_t count;
    void *pf;
    pf = f;

    for (count = 0; count < 4; count++) {
        *((uint8_t *) pf + count) = *(ch + 3 - count);
    }
}

/*************************************
Function: FloatToChar 
Description: 浮点数转化为char数组
Input: 输入浮点数 模式：4 单精度浮点数 8 双精度浮点数 
Output: 输出数值
 *************************************/
void DoubleToChar(long double *d, uint8_t *ch) {
    uint8_t count;
    void * pf;
    pf = d;

    for (count = 0; count < 8; count++) {
        *(ch + count) = *((uint8_t *) pf + 7 - count);
    }
}

/*************************************
Function: HCD 
Description: 16进制转化为10进制
Input: 数据，字节数
Output: 输出数值
 *************************************/
uint8_t HCD(uint8_t dat) {
    return ((dat >> 4)&0x0f)*10 + (dat & 0x0f);
}

/*************************************
Function: DCH 
Description: 10进制转化为16进制
Input: 数据，字节数
Output: 输出数值
 *************************************/
uint8_t DCH(uint8_t dat) { //0x11 17
    return ((dat / 10 << 4)&0xF0) | ((dat % 10)&0x0F);
}

//uint8_t D2Hex(uint8_t dat)//0x11（17）-> 0x17  
//{
//    if(dat>)
//}

/*************************************
Function: DataIsVaild 
Description: 判断数据是否有效
Input: 是否
Output: 输出数值
 *************************************/
bool DataIsVaild(uint16_t dat, const uint16_t max, const uint16_t min) {
    if (dat > max) return false;
    else if (dat < min) return false;
    return true;
}

/*************************************
Function: SetVaildData 
Description: 根据阀值设置参数
Input: 是否
Output: 输出数值
 *************************************/
void SetVaildData(uint8_t * dat, const uint32_t max, const uint16_t min) {
    uint16_t tmp = (* dat << 8) + *(dat + 1);

    if (tmp > max) {
        *dat = max >> 8;
        *(dat + 1) = max & 0x00ff;
    } else if (tmp < min) {
        *dat = min >> 8;
        *(dat + 1) = min & 0x00ff;
    }
}
//将数据反转

void DataReverse(uint8_t *dat, const uint8_t byte) {
    uint8_t tmp, cnt;

    for (cnt = 0; cnt < byte / 2; cnt++) {
        tmp = dat[cnt];
        dat[cnt] = dat[byte - 1 - cnt];
        dat[byte - 1 - cnt] = tmp;
    }
}

//8MHz-》4Mhz

//void Delay10ms(char time) {
//    uint16_t i;
//    while (time-- > 0)
//        for (i = 0; i < 6700; i++)
//            asm("Nop()");
//}

//void Delay100ms(char time) {
//    uint16_t i;
//    while (time-- > 0)
//        for (i = 0; i < 65500; i++)
//            asm("Nop()");
//}
//
void Delay1s(char time) {
    uint32_t i; //,j;
    while (time-- > 0)
        for (i = 0; i < 365000; i++)
            Nop();
}

void CopyDat(uint8_t* output, uint8_t *input, const uint8_t bytes) {
    uint8_t num;
    for (num = 0; num < bytes; num++)
        *(output + num) = *(input + num);
}

void ClearDat(uint8_t *output, const uint8_t dat, const uint8_t bytes) {
    uint8_t num;
    for (num = 0; num < bytes; num++)
        *(output + num) = dat;
}

bool ValueIsEqual(const uint8_t *str1, const uint8_t *str2, const uint8_t bytes) {
    uint8_t cnt;
    for (cnt = 0; cnt < bytes; cnt++)
        if (*(str1 + cnt) != *(str2 + cnt))
            return false;
    return true;
}

bool UART_Is_Get(uint8_t* sdata, uint8_t* cdata, const uint8_t sbytes, const uint8_t cbytes) {
    uint8_t sbyte, cbyte;
    bool b = false;
    for (sbyte = 0; sbyte < sbytes; sbyte++) {
        if (*(sdata + sbyte) == *(cdata))
            for (cbyte = 0; cbyte < cbytes; cbyte++)
                if (*(sdata + sbyte + cbyte) == *(cdata + cbyte))
                    b = true;
                else {
                    b = false;
                    break;
                }
        if (b) break;//如果检索到了帧头，直接退出循环
    }
    return b;
}


