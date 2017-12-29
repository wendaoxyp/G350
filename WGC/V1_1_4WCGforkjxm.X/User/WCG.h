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
    uint16_t Send_60s : 11; //����ʱ��,��λ������ 2^15=32768 
    uint16_t None : 4; //δ����
} WGCCON0BITS;
extern volatile WGCCON0BITS WGCCON0bits;

typedef struct tagWGCCON1BITS {
    uint16_t Sample_5s : 15; //�ɼ�ʱ��,��λ���� �̶�5s
    uint16_t None : 1; //δ����
} WGCCON1BITS;
extern volatile WGCCON1BITS WGCCON1bits;

typedef struct tagWGCCON2BITS {
    uint16_t WGC_ID : 8; //WGC��ID�� 0-255
    uint16_t E41_Is_Use_For_Send_Data : 1; //�̳������Ƿ�������������    
    uint16_t E41_Is_Use_For_Set_Arg : 1; //�̳������Ƿ������޸Ĳ���    
    uint16_t Alarm_RST_FLAG : 1; //���¼������ڱ�־
    uint16_t None : 5; //δ����
} WGCCON2BITS;
extern volatile WGCCON2BITS WGCCON2bits;

typedef struct tagWGCIPBITS {
    uint32_t IP0 : 8; //IP��ַ��3λ
    uint32_t IP1 : 8; //IP��ַ��2λ
    uint32_t IP2 : 8; //IP��ַ��1λ
    uint32_t IP3 : 8; //IP��ַ��0λ
} WGCIPBITS;
extern volatile WGCIPBITS WGCIPbits;

//typedef struct tagWGCPORTBITS {
//    uint16_t HighAddr : 8; //��λ��ַ
//    uint16_t LowAddr : 8; //��λ��ַ
//} WGCPORTBITS;
extern volatile uint16_t WGCPORT;

typedef struct tagWGCPERIODBITS {
    uint16_t B1 ; //���ڱ���
    uint16_t Y2 ; //�������� 
    uint16_t CNT ; //����ѭ������ 
//    uint16_t RST_FLAG : 1; //���¼������ڱ�־
} WGCPERIODBITS;
extern volatile WGCPERIODBITS WGCPeriodbits;

extern void WGC_Init(void);
extern bool WGC_CalcAlarmPeriod(void);
//extern void WGC_CalcAlarmPeriod(void) ;
#endif


