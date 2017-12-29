/* 
 * File:   Print.c
 * Author: TURONG62
 *
 * Created on 2016年8月10日, 上午9:28
 */
#include "user.h"
//#include "Modbus.h"
#include "string.h"

//'\0' = ASCII 0
//u8* StringEncryption(u8*ch);

//u8 DEVICE_VALUE[10]={0x60,0x63,0x63,0x61,0x65,0x60,0x60,0x60,0x60,0x62};
//u8 BUSINESS_VALUE[10]={0x60,0x63,0x63,0x61,0x65,0x60,0x60,0x60,0x60,0x62};
//u8 VERSION_VALUE[4]={0x86,0x61,0x5E,0x60};
////常量设置
////"device":"的加密代码
//const u8 DEVICE[10]={0x52,0x94,0x95,0xA6,0x99,0x93,0x95,0x52,0x6A,0x52}; 
////","business":"的加密代码
//const u8 BUSINESS[14]={0x52,0x5C,0x52,0x92,0xA5,0xA3,0x99,0x9E,0x95,0xA3,0xA3,0x52,0x6A,0x52}; 
////","version":"V1.0的加密代码
//const u8 VERSION[13]={0x52,0x5C,0x52,0xA6,0x95,0xA2,0xA3,0x99,0x9F,0x9E,0x52,0x6A,0x52}; 
////","session":\0的加密代码
//const u8 SESSION[12]={0x52,0x5C,0x52,0xA3,0x95,0xA3,0xA3,0x99,0x9F,0x9E,0x52,0x6A};
////,"command":"\0的加密代码
//const u8 COMMAND[12]={0x5C,0x52,0x93,0x9F,0x9D,0x9D,0x91,0x9E,0x94,0x52,0x6A,0x52};
////","content":\0的加密代码
//const u8 CONTENT[12]={0x52,0x5C,0x52,0x93,0x9F,0x9E,0xA4,0x95,0x9E,0xA4,0x52,0x6A};
////{"measure":[\0的加密代码
//const u8 MEASURE[12]={0xAB,0x52,0x9D,0x95,0x91,0xA3,0xA5,0xA2,0x95,0x52,0x6A,0x8B,};
////{"name":"\0的加密代码
//const u8 NAME[9]={0xAB,0x52,0x9E,0x91,0x9D,0x95,0x52,0x6A,0x52};
////","datatype":"\0的加密代码
//const u8 DATATYPE[14]={0x52,0x5C,0x52,0x94,0x91,0xA4,0x91,0xA4,0xA9,0xA0,0x95,0x52,0x6A,0x52};
////","alarmtype":\0的加密代码
//const u8 ALRAMTYPE[14]={0x52,0x5C,0x52,0x91,0x9C,0x91,0xA2,0x9D,0xA4,0xA9,0xA0,0x95,0x52,0x6A};
////,"ret":"\0的加密代码
//const u8 RET[8]={0x5C,0x52,0xA2,0x95,0xA4,0x52,0x6A,0x52};
////[{"t":"\0的加密代码
//const u8 T[7]={0x8B,0xAB,0x52,0xA4,0x52,0x6A,0x52};
////,"v":\0的加密代码
//const u8 V[5]={0x5C,0x52,0xA6,0x52,0x6A};
//
//const u8 FLOAT[5]={0x96,0x9C,0x9F,0x91,0xA4};
//const u8 INTER[8]={0x99,0x9E,0xA4,0x95,0xA2,0x97,0x95,0xA2};
//
//const u8 GET1[11]={0x97,0x95,0xA4,0x8F,0x9F,0xA0,0xA4,0x8F,0x9E,0xA5,0x9D};
//const u8 GET3[17]={0x97,0x95,0xA4,0x8F,0xA3,0x95,0xA2,0xA6,0x95,0xA2,0x8F,0x93,0x98,0x91,0x9E,0x97,0x95};
//const u8 GET5[18]={0x97,0x95,0xA4,0x8F,0xA3,0x95,0xA2,0xA6,0x95,0xA2,0x8F,0x9D,0x95,0x91,0xA3,0xA5,0xA2,0x95};
//
//
//
//const u16 MONTH[12]={0,31,59,90,120,151,181,212,243,273,304,334};
//const u16 LEAPYEAR[23]={0,2012,2016,2020,2024,2028,2032,2036,2040,2044,2048,
//                     2052,2056,2060,2064,2068,2072,2076,2080,2084,2088,
//                     2092,2096};
//u8 gLYxb=0; 
//u32 gUnixTime=0;//记录当前年份最近的一个闰年 2010.1.1 0:0:0 1262304000

//u32 DateToUnixTime(u16*);

/*************************************
Function: PrintInterIsFinish  
Description: 整数类型数据打印
Input: 数据地址，数据类型（char long），开始为0是否显示
Output: 打印成功
 ************************************/
bool PrintInterIsFinish(void* ch, u8 type, u8 show)//bit7 表示是否过滤开头0 bite0-3表示答应的类型
{

    u8 dat[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    u8 count = 0;
    u8 noZeroGlag = 1;

    switch (type)//如果开头位为‘0’，将其打印
    {
        case 'c'://char 
        {//char
            u8 tmp1 = *((u8*) ch);
            if (tmp1) {
                for (count = 0; count < 3; count++)//获取位数 
                {
                    dat[count] = tmp1 % 10;
                    tmp1 /= 10;
                }
                for (count = 3; count > 0; count--)//打印 
                {
                    if (noZeroGlag && !dat[count - 1] && !show)
                        continue;
                    else
                        noZeroGlag = 0;
                    UART2Send(dat[count - 1] + 0x30);
                }
            } else
                UART2Send(0x30);
            break;
        }
        case 0x6c://char‘l’
        {
            u32 tmp = *((u32*) ch);
            if (tmp) {
                for (count = 0; count < 10; count++)//获取位数 
                {
                    dat[count] = tmp % 10;
                    tmp /= 10;
                }
                for (count = 10; count > 0; count--)//打印 
                {
                    if (noZeroGlag && !dat[count - 1] && !show)
                        continue;
                    else
                        noZeroGlag = 0;
                    UART2Send(dat[count - 1] + 0x30);
                }
            }
            else
                UART2Send(0x30);
            break;
        }
        default:
            return false;
    }
    return true;
}

/*************************************
Function: PrintFloatIsFinish 
Description: 浮点数打印 通过串口2输出ASC数据 ch:数据类型
Input: 浮点数
Output: 无
 ************************************/
void PrintFloatIsFinish(void * dat, u8 ch) {
    u16 xs;
    u32 zs;

    switch (ch) {
        case'f':
        {
            float f = *((float*) dat) + 0.005;
            zs = (u32) f;
            PrintInterIsFinish(&zs, 'l', 0);
            xs = (u16) ((f - zs)*100);
            if (0 < xs && xs < 10) {
                UART2Send('.'); //输出小数点
                UART2Send('0'); //输出小数点
                PrintInterIsFinish(&xs, 'c', 0);
            } else if (xs > 10) {
                UART2Send('.'); //输出小数点
                PrintInterIsFinish(&xs, 'c', 0);
            }
            break;
        }
        case'd':
        {
            long double d = *((long double*) dat);
            zs = (u32) d;
            PrintInterIsFinish(&zs, 'l', 0);
            xs = (u8) ((d - zs)*100);
            if (0 < xs && xs < 10) {
                UART2Send('.'); //输出小数点
                UART2Send('0'); //输出小数点
                PrintInterIsFinish(&xs, 'c', 0);
            } else if (xs > 10) {
                UART2Send('.'); //输出小数点
                PrintInterIsFinish(&xs, 'c', 0);
            }
            break;
        }
        default:
            break;
    }
}


