#ifndef WGC_H
#define WGC_H

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "HL6528.h"
#include "Debug.h"
#include "Common.h"
#include "CRC16.h"
#include "CAT24C512.h"


#define  BAT_TEST_DIR TRISBbits.TRISB11
#define  BAT_TEST_LAT LATBbits.LATB11
#define  BAT_TEST_PORT PORTBbits.RB11

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
    uint16_t min : 8;
    uint16_t sec : 8;
} WGCTIME2BITS;
extern volatile WGCTIME2BITS WGCTIME2bits;

//typedef struct tagWGCTIME3BITS {
//    uint16_t sendtime : 8;
//    uint16_t sampletime : 8;
//} WGCTIME3BITS;
//extern volatile WGCTIME3BITS WGCTIME3bits;

typedef struct tagWGCCON0BITS {
    uint16_t Send_60s : 11; //����ʱ��,��λ������ 2^15=32768 
    uint16_t None : 5; //δ����
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
    uint16_t Debug1 : 1; //�̳������Ƿ������޸Ĳ���    
    uint16_t Debug2 : 1; //����ʱ����Բɼ�ʱ���Ƿ�������
    uint16_t Period_FLAG : 1; //rtcc��־λ
    uint16_t Sample_FLAG : 1; //������־λ
    uint16_t Send_FLAG : 1; //���ͱ�־λ
    uint16_t SET_TIME_TEST_FLAG : 1; //RTCC��ʱʱ�����
    uint16_t PC_Cop_FLAG : 1; //�û�ͨѶ��־λ
} WGCCON2BITS;
extern volatile WGCCON2BITS WGCCON2bits;

typedef struct tagWGCCON3BITS {
    uint32_t delay : 17; //0-131071s;
    uint32_t count : 15; //0-32767 �� �ɼ�ʱ�����Ϊ17280 ����ʱ�����Ϊ480 һ��֮��
} WGCCON3BITS;
extern volatile WGCCON3BITS WGCCON3bits;

typedef struct tagWGCCON4BITS {
    uint32_t delay : 17; //0-131071s;
    uint32_t count : 15; //0-32767 �� �ɼ�ʱ�����Ϊ17280 ����ʱ�����Ϊ480 һ��֮��
} WGCCON4BITS;
extern volatile WGCCON4BITS WGCCON4bits;

typedef struct tagWGCIPBITS {
    uint32_t IP0 : 8; //IP��ַ��3λ
    uint32_t IP1 : 8; //IP��ַ��2λ
    uint32_t IP2 : 8; //IP��ַ��1λ
    uint32_t IP3 : 8; //IP��ַ��0λ
} WGCIPBITS;
extern volatile WGCIPBITS WGCIPbits;

typedef struct tagWGCCNTBITS {
    uint32_t Sample_CNT : 16;
    uint32_t Send_CNT : 16;
} WGCCNTBITS;
extern volatile WGCCNTBITS WGCCNTbits;
//typedef struct tagWGCPORTBITS {
//    uint16_t HighAddr : 8; //��λ��ַ
//    uint16_t LowAddr : 8; //��λ��ַ
//} WGCPORTBITS;
extern volatile uint16_t WGCPORT;

//typedef struct tagWGCPERIODBITS {
//    uint16_t B1; //���ڱ���
//    uint16_t Y2; //�������� 
//    uint16_t CNT; //����ѭ������ 
//    //    uint16_t RST_FLAG : 1; //���¼������ڱ�־
//} WGCPERIODBITS;
//extern volatile WGCPERIODBITS WGCPeriodbits;

typedef enum {
    Send_Flag, GPRS_Dingling, GPRS_Online, GPRS_Underline, GPRS_Senddata, GPRS_Receivedata, GPRS_Err,
    Sample_Flag, Sample_Data, Sample_Err, Sample_Send_Flag,
    E41_Senddata, E41_Receivedata, E41_Error,
    eerom_Writedata, eerom_Readdata, eerom_Writeerr, eerom_Readerr,
    LCD_Senderr
} WGC_STA;



//enum {
//    DATA, SENDTIME, SAMPLETIME, ID, IP, PORT
//};
//extern volatile struct RTCC_Time_Node rtcc_sample;
//extern volatile struct RTCC_Time_Node rtcc_send;
extern volatile uint8_t WGC_Sta;
extern float f_p;

extern void WGC_Init(void);
//extern bool WGC_CalcAlarmPeriod(void);
extern void GPRS_Task(void);
extern bool Sample_Task(void);
extern void SetNextAlarm(uint32_t sample_sec);
extern bool WGCPCCop(void);
#endif


