/* 
 * File:   
 * Author: 
 * Comments:define IO
 * Revision history: 
 * V0.1 �޸�MP_CON������
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef _USER_H
#define	_USER_H
/******************* ****************Header Include*************************************/
#include "p24F32KA302.h"
#include "stdbool.h"
#include "stddef.h"
#include "string.h"
#include "stdint.h"
/******************* ****************define type*************************************/
typedef unsigned char u8;
typedef unsigned int u16;
typedef unsigned long u32;

typedef volatile unsigned char vu8;
typedef volatile unsigned int vu16;
typedef volatile unsigned long vu32;

typedef u16(*FP_CRC)(u8*, const u8);
//typedef bool (*FP_UART)(u8 *);

/*************************************IO Define***************************************/
//��ѹ����
//#define BAT_DEC_IN (TRISBbits.TRISB14=1)
//#define BAT_DEC PORTBbits.RB14

//���벶���ж�
#define INPUT_PULSE_IN (TRISBbits.TRISB9=1)
#define INPUT_PULSE PORTBbits.RB9

//RS485 ����������ƽ�F
#define MC_CON_OUT (TRISBbits.TRISB3=0)
#define RS485_CON LATBbits.LATB3 
#define RS485_TX_OUT (TRISBbits.TRISB7 = 0);
#define RS485_RX_IN (TRISBbits.TRISB2 = 1);
#define RS485_RX_READ (PORTBbits.RB2)

//UART2 ����������ƽ�
#define TX2_OUT (TRISBbits.TRISB0 = 0);
#define RX2_IN (TRISBbits.TRISB1 = 1);

//SPI2ͨ�Ž�
#define SCK2_TRIS TRISBbits.TRISB5
#define SCK2 LATBbits.LATB5
#define SDO2_TRIS TRISBbits.TRISB6
#define SDO2 LATBbits.LATB6
#define SDI2_TRIS TRISAbits.TRISA7
#define SDI2 PORTAbits.RA7
#define SS2_TRIS TRISBbits.TRISB12
#define SS2 LATBbits.LATB12

//��ѹ���ƽ�
#define MP_CON_OUT (TRISAbits.TRISA2 = 0)
#define MP_ON (LATAbits.LATA2 = 1)
#define MP_OFF (LATAbits.LATA2 = 0)


//GPRSģ��ENʹ��
#define GP_CON_OUT (TRISAbits.TRISA3 = 0)
#define GPRS_ON (LATAbits.LATA3 = 1)
#define GPRS_OFF (LATAbits.LATA3 = 0)

//GPRSģ��LK
#define LK_IN (TRISBbits.TRISB13 = 1)
#define LK_OUT (TRISBbits.TRISB13 = 0)
#define LK PORTBbits.RB13

//���벶��S1
#define S1_IN (TRISBbits.TRISB9 = 1)
#define S1 PORTBbits.RB9

//���벶��S2
#define S2_IN (TRISBbits.TRISB8 = 1)
#define S2 PORTBbits.RB8

//����IO��
#define TST_IN (TRISBbits.TRISB15 = 1)
#define TST PORTBbits.RB15

//ADC�����
#define ADC0_IN (TRISAbits.TRISA2 = 1)//A0
#define ADC0 PORTAbits.RA2
/*************************************User Variable***************************************/
//���ò�����
#define FP 4000000//9.22 4000000Hz
#define BAUDRATE 9600
#define BRGVAL ((FP/BAUDRATE)/16) - 1

#define Reset() {__asm__ volatile("reset");}//��λ�豸
#define Disi() {__asm__ volatile("disi");}//��ֹ�ж�
//���ݺͲ���
#define REG1_BYTES 46               //����洢�����ֽ��� ����������ѹ������
#define REG1_ARG_NUM 11             //����洢���ݲ������� 
#define REG2_BYTES 58               //MIOT���������ֽ���
#define REG2_ARG_NUM 24             //MIOT�������ݲ�������
#define REG3_BYTES 25               //���ͻ����������ֽ���
#define REG3_BUF1_CNT 24           //���ͻ�����1������
#define REG3_ARG_NUM 6             //���ͻ������Ĳ�������
#define DataPacketNum   144         //8192/REG3_BYTES=195  6*24=144  10����һ��
#define UDP_A2_LENGTH 42            //36+1+2+3
//#define REG3_BUF1_CNT 24     //�����ϴβɼ����ݵ�������������ڴ洢�ϴεĲɼ�����
//#define REG1_ARG_BYTES 24    //���ڴ���Э����Ч������ֻ��mi_time,mp_Qm,mp_Vm,mp_Vbat,mp_status����7+4+8+4+1�ֽ�

#define DataPacket_ID 0x1FFF        //���ݰ�����λ�� 0-143
#define BOR_Pulse 0x1FF0            //�����������ݱ����ַ
#define RST_Data 0x1F00             //��λ��������
//#define RST_Time 0x1FA0             //��λ����ʱ��
//#define RST_Count 0x1FB0            //��λ�������

#define TIME_GPRS_MAX 1440          //1��
#define TIME_GPRS_MIN 60            //1Сʱ
#define TIME_MP_MAX 1440            //60���� 1��Сʱ
#define TIME_MP_MIN 7               //3����
#define TIME_ALARM_MAX 1440         //1��
#define TIME_ALARM_MIN 0            //0����
#define SettingSampleTime 6         //�ɼ�ʱ��
//#define VoltageSampleCount 10        //�ɼ���ѹ�Ĵ���10 16ͨ��
//#define K_Bat  3.056                //AD�ɼ���ѹת��ϵ�� 3.05690375 

#define PC 0
#define GPRS 1

#define REG3_BUF1 1     //����Ĵ���������1�����Ҫ�ϴεĶ�ʱ�ɼ�����
#define REG3_BUF2 2     //����Ĵ���������2�����Ҫ�ϴεı�������������

extern vu16 gT3Count; //��ʱ��3����ֵ
extern vu16 gT1Count; //��ʱ��1����ֵ
extern u8 gOffsetAdd; //FROM�е�ƫ������ÿ���ϵ��From��ȡ
extern vu32 gPulseTime; //��ȡ����ʱ��
extern vu32 gPulseCount; //�����ۼ���
extern float gGetVoltage; //��ȡ��ѹ

struct FLag_Arg {
    vu16 tgprsFlag : 1; //gprs���߱�־λ
    vu16 LowPoweralarmFlag : 1; //�������߱�־λ    
    vu16 LowPowerGetDataFlag : 1; //�͵�ѹ��־λ
    vu16 TestGetDataFlag : 1; //�������ݱ�־λ�����ԣ�
    vu16 TestOnlieFlag : 1; //�������߱�־λ�����ԣ�
    vu16 SleepExitFlag : 1; //����ģʽ�˳���־
    vu16 CheckRTCCFlag : 1; //У��RTCb��־λ    
    vu16 TestFlag : 1; //���Ա�־λ 
    vu16 T1CountFlag : 1; //T1��ʼ��ʱ
    vu16 T1CountLastFlag : 1; //T1��ʼ��ʱ
    vu16 PulseTimeFlag : 1; //�����ʱ���Ѿ���ȡ����   
    vu16 TESTGetStatus : 1;//��ȡMIOT״̬
};
extern struct FLag_Arg FLagArgbits;

struct UART2_Arg {
    u8* dat2;
    u8 bytes2;
};
extern struct UART2_Arg UART2Argbits;

struct Status {
    u8 staMp;
    u8 staGPRS;
    u8 staMiot; //����״̬λ   
};
extern struct Status Statusbits;

struct TimeCount {
    vu32 timeMp; //mp
    vu32 timeGprs; //gprs
    vu32 timeAlarm; //����
    vu32 timeCheckTime; //
    //    vu8 timePulse; //IC2��ʱ����
};
extern struct TimeCount gTimeCount;

//extern const u8 PTL_LOC[6][9]; //Э�������ַ

struct Reg3_Record {
    vu8 Buffer_ID;
    vu16 Record;
};
extern struct Reg3_Record Reg3_Buf1_Recordbits; //

////miot����������ַ
//
//extern enum REG2_Add_enum enum_REG2_Add;
//
////����洢���ݰ���������˳�� REG1_Add_enum
//
//extern enum mp_arg_add_enum  enum_mp_arg_add;
//
////���ͻ������ݸ�������˳��
//
//extern enum send_buffer_enum  enum_send_buffer;
//
////A2Э���������˳��
//
//extern enum A2_arg_add_enum enum_A2_arg_add;

//״̬����ʹ��union

extern enum sendDataType {
    SampleData = 0, LowPowerData = 1, TestData = 2
} SDT;

struct MiotArgs {
    u16 timemp;
    u16 timegprs;
    u16 timealarm;
    float AlarmVoltage;
};
extern struct MiotArgs miotArgs;

enum Cop_Fun_Num {
    /*GetMuiltSampDat = 0x02, */GetSampDat = 0x03, GetMIOTArg = 0x04, SetMIOTArg = 0x10,
    GetGPRSArg = 0x20, SetGPRSArg = 0x21, TestGPRS = 0x22, UnlineUpdateGPRS = 0x23, GetMIOTVer = 0x43,
    GetMIOTSta = 0x26, GetHistoryError = 0x27
};
extern volatile enum Cop_Fun_Num CFN;

typedef bool(*UARTn)(u8 *dat); //bool BufferRead_UART2(u8 *data) bool BufferRead_UART2(u8 *data) 

#endif	/* XC_HEADER_TEMPLATE_H */


