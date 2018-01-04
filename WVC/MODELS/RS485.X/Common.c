/*************************************************
Copyright (C), 1988-1999, Tech. Co., Ltd.
File name: Common.c
Author: xx13
Version: 1.0
Date: 2017/12/29
Description: Common API函数
Others: 需要用到自定义库
History: None
1. Date:
Author:
Modification:
2. ...
 *************************************************/
#include "Common.h"

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
    return (dat >> 4)*10 + GetMod(dat, 4);
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
void SetVaildData(uint16_t * dat, const uint32_t max, const uint16_t min) {
    uint16_t tmp = ((*dat) << 8) + *(dat + 1);

    if (tmp > max) {
        *dat = max;
    } else if (tmp < min) {
        *dat = min;
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

void Delay1ms(char time) {
    uint16_t i;
    while (time-- > 0)
        for (i = 0; i < 144; i++)
            Nop();
}

void Delay10ms(char time) {
    uint16_t i;
    while (time-- > 0)
        for (i = 0; i < 1440; i++)
            Nop();
}

void Delay100ms(char time) {
    uint32_t i;
    while (time-- > 0)
        for (i = 0; i < 14400; i++)
            Nop();
}

void Delay1s(char time) {
    uint32_t i; //,j;
    while (time-- > 0)
        for (i = 0; i < 144000; i++)
            Nop();
}

void CopyDat(uint8_t* output, const uint8_t *input, const uint8_t bytes) {
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

//快速去余数

uint8_t GetMod(uint16_t num, uint8_t mod_num) {
    return num - ((num >> mod_num) << mod_num);
}

//16位整数转化为字符串

uint8_t my_itoa(uint16_t i, uint8_t *str) {
    uint8_t buf[6];
    uint8_t cnt = 0, len;
    uint16_t tmp = i;
    if (!tmp) {
        *str = '0';
        *(str + 1) = '\0';
        len = 1;
    } else {
        while (tmp) {
            *(buf + cnt++) = tmp % 10 + 0x30;
            tmp /= 10;
        }
        len = cnt;
        cnt += 1;
        while (cnt--) {
            *(str + cnt - 1) = *(buf + len - cnt);
        }
        *(str + len) = '\0';
    }
    return len;
}

void CmpStr(const uint8_t* str1, const uint8_t* str2, uint8_t bytes) {

}

/*************************************
Function: UARTDataIsRight
Description: 根据结构体的内容获取有效数据和有效长度
Input: 数据结构体
Output: 是否获取到数据
Notice：字节数不能大于256 取数据的时间可能短   
 *************************************/
//bool UARTDataIsRight(StrCmp * strcmp) {//注意
//    bool IsFind = false; //记录字节数
//    uint8_t cnt = 0/*校验寻找循环地址*/, cnt1 = 0/*校验判断循环地址*/, cnt2/*赋值地址*/, /*offset,*/ byte = 0;

//    if (!(strcmp->Check_len) || !(strcmp->Source_len))//如果设置的字节数为0的话，返回错误
//        return false; //为获取

//被对比的str1，对比的str2，str1字节数

uint8_t Str_Find_Head(const uint8_t* str1, const uint8_t *str2, uint8_t str1_bytes, uint8_t str2_bytes) {
    uint8_t cnt = 0, cnt1 = 0;
    uint8_t position = 0;
    bool is_find = false;
    uint8_t *ptr = (uint8_t *) str1;
    if (str2_bytes > str1_bytes)//规定判断字符字节数不能大于源数据的字节数
        return 0;

    if (str1_bytes == 1) {//如果一个字节的情况下
        if (*ptr == *str2)
            return true;
        else
            return false;
    }
    while (cnt < str1_bytes) {
        ptr = (uint8_t *) str1 + cnt;
        if (*ptr == *str2) {//如果数据==head的话 
            for (cnt1 = 1; cnt1 < str2_bytes; cnt1++) {
                if (*(str1 + cnt1 + cnt) != *(str2 + cnt1)) {
                    is_find = false;
                    break;
                } else
                    is_find = true;
            }
            if (is_find) {
                position = cnt + 1;
                break;
            }
        }
        cnt += 1;
    }
    return position;
}

//uint8_t Str_Cut(uint8_t* str1, uint8_t * str2, uint8_t str1_bytes, uint8_t str2_bytes) {
//    if(str2_bytes<str1_bytes)
//        return 1;//STRING_HANDLE_ERR_NO_SIZE
//    CopyDat
//}

//if (IsFind) break; //如果找到数据，退出寻找帧头程序
//cnt++; //校验位置加1
//}
//}
//if (IsFind) {//如果存在接受的字节数且找到帧头
//    if (strcmp->Get_len < strcmp->Check_len) {
//        byte = strcmp->Get_len; //获取字节小于校验字节,比如只需要校验不需要获取数据
//        for (cnt2 = 0; cnt2 < byte; cnt2++) //获取帧头数据
//            *(strcmp->GetData + cnt2) = *(strcmp->CheckData + cnt2);
//    } else {//如果要获取的字节数大于帧头数据，需要判断有效的剩余字节数数量
//        if (strcmp->Source_len - cnt < strcmp->Get_len)//如果获取数据大于有效数据，
//            for (cnt2 = 0; cnt2 < strcmp->Source_len - cnt; cnt2++) //获取剩余数据
//                *(strcmp->GetData + cnt2) = *(strcmp->SourceData + cnt + cnt2);
//        else
//            for (cnt2 = 0; cnt2 <= strcmp->Get_len; cnt2++) //获取剩余数据
//                *(strcmp->GetData + cnt2) = *(strcmp->SourceData + +cnt + cnt2);
//    }
//    strcmp->Real_len = cnt2; //实际获取到的长度
//    return true;
//}
//strcmp->Real_len = 0;
//return false;
//}


