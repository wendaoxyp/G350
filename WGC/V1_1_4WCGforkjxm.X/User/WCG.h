#ifndef WCG_H
#define WCG_H

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

typedef struct tagWGCTIME0BITS {
    uint16_t year : 8;
    uint16_t month : 8;
} WGCTIME0BITS;
extern volatile WGCTIME0BITS WGCTIME0bits;

typedef struct tagWGCTIME1BITS {
    uint16_t day : 8;
    uint16_t hour : 8;
} WGCTIME1BITS;
extern volatile WGCTIME1BITS WGCTIME1bits;

typedef struct tagWGCTIME2BITS {
    uint16_t minute : 8;
    uint16_t second : 8;
} WGCTIME2BITS;
extern volatile WGCTIME2BITS WGCTIME2bits;

//typedef struct tagWGCTIME3BITS {
//    uint16_t sendtime : 8;
//    uint16_t sampletime : 8;
//} WGCTIME3BITS;
//extern volatile WGCTIME3BITS WGCTIME3bits;

typedef struct tagWGCCON0BITS {
    uint16_t Send_60s : 11; //发送时间,单位：分钟 2^15=32768 
    uint16_t None : 4; //未定义
} WGCCON0BITS;
extern volatile WGCCON0BITS WGCCON0bits;

typedef struct tagWGCCON1BITS {
    uint16_t Sample_5s : 15; //采集时间,单位：秒 刻度5s
    uint16_t None : 1; //未定义
} WGCCON1BITS;
extern volatile WGCCON1BITS WGCCON1bits;

typedef struct tagWGCCON2BITS {
    uint16_t WGC_ID : 8; //WGC的ID号 0-255
    uint16_t E41_Is_Use_For_Send_Data : 1; //短程无线是否用来发送数据    
    uint16_t E41_Is_Use_For_Set_Arg : 1; //短程无线是否用来修改参数    
    uint16_t Alarm_RST_FLAG : 1; //重新计算周期标志
    uint16_t None : 5; //未定义
} WGCCON2BITS;
extern volatile WGCCON2BITS WGCCON2bits;

typedef struct tagWGCIPBITS {
    uint32_t IP0 : 8; //IP地址第3位
    uint32_t IP1 : 8; //IP地址第2位
    uint32_t IP2 : 8; //IP地址第1位
    uint32_t IP3 : 8; //IP地址第0位
} WGCIPBITS;
extern volatile WGCIPBITS WGCIPbits;

//typedef struct tagWGCPORTBITS {
//    uint16_t HighAddr : 8; //高位地址
//    uint16_t LowAddr : 8; //低位地址
//} WGCPORTBITS;
extern volatile uint16_t WGCPORT;

typedef struct tagWGCPERIODBITS {
    uint16_t B1 ; //周期倍数
    uint16_t Y2 ; //周期余数 
    uint16_t CNT ; //周期循环次数 
//    uint16_t RST_FLAG : 1; //重新计算周期标志
} WGCPERIODBITS;
extern volatile WGCPERIODBITS WGCPeriodbits;

extern void WGC_Init(void);
extern bool WGC_CalcAlarmPeriod(void);
//extern void WGC_CalcAlarmPeriod(void) ;
#endif


