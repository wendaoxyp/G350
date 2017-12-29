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
#define BAT_DEC_IN (TRISBbits.TRISB14=1)
#define BAT_DEC PORTBbits.RB14

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

//SPI1ͨ�Ž�
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
#define REG1_BYTES 46               //����洢�����ֽ���
#define REG1_ARG_NUM 11             //����洢���ݲ������� 
#define REG2_BYTES 60               //MIOT���������ֽ���
#define REG2_ARG_NUM 26             //MIOT�������ݲ�������
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
#define RST_Time 0x1FA0             //��λ����ʱ��
#define RST_Count 0x1FB0            //��λ�������

#define TIME_GPRS_MAX 1440          //1��
#define TIME_GPRS_MIN 60            //1Сʱ
#define TIME_MP_MAX 1440            //60���� 1��Сʱ
#define TIME_MP_MIN 7               //3����
#define TIME_ALARM_MAX 1440         //1��
#define TIME_ALARM_MIN 0            //0����
#define SettingSampleTime 6         //�ɼ�ʱ��

#define PC 0
#define GPRS 1

#define REG3_BUF1 1     //����Ĵ���������1�����Ҫ�ϴεĶ�ʱ�ɼ�����
#define REG3_BUF2 2     //����Ĵ���������2�����Ҫ�ϴεı�������������

extern vu16 gT3Count; //��ʱ��3����ֵ
extern vu16 gT1Count; //��ʱ��1����ֵ
extern u8 gOffsetAdd; //FROM�е�ƫ������ÿ���ϵ��From��ȡ
extern vu32 gPulseTime; //��ȡ����ʱ��
extern vu32 gPulseCount; //�����ۼ���

struct FLag_Arg {
    u16 tgprsFlag : 1; //gprs���߱�־λ
    u16 tLowPoweralarmFlag : 1; //�������߱�־λ
    u16 SleepExitFlag : 1; //����ģʽ�˳���־
    u16 CheckRTCCFlag : 1; //У��RTCb��־λ    
    u16 TestFlag : 1; //���Ա�־λ 
    u16 T1CountFlag : 1; //T1��ʼ��ʱ
    u16 T1CountLastFlag : 1; //T1��ʼ��ʱ
    u16 LowPowerGetDataFlag : 1; //�͵�ѹ��־λ
    u16 TestGetDataFlag : 1; //�������ݱ�־λ�������Ͳ��ԣ�
    u16 TestOnlieFlag : 1; //���߱�־λ�������Ͳ��ԣ�
};
extern struct FLag_Arg FLagArgbits;

struct UART2_Arg {
    //    u16 add1;
    u8* dat2;
    u8 bytes2;
};
extern struct UART2_Arg UART2Argbits;

struct Status {
    //    u8 staCheckRTCC : 1; //У��RTC״̬λ
    u8 staMp;
    u8 staGPRS;
    u8 staMiot; //: 1; //����״̬λ   
    //    u8 staBat : 1; //���û�籨��״̬λ
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

extern enum status_enum {
    Data_No_Ready = 0x80, Data_No_Receive = 0x81, Data_Error_Check_Sum = 0x82, Data_Error_MpId = 0x83,
    Data_Error_Fail = 0x84, Data_Timeover = 0x85,
    GMT_No_Ready = 0x90, GMT_No_Receive = 0x91, GMT_Error_Check_Sum = 0x92, GMT_Error_MpId = 0x93,
    GMT_Error_Fail = 0x94, GMT_Timeover = 0x95, GMT_Time_Error = 0x96, GMT_Unix_Time_Error = 0x97,
    GMT_Arg_Error = 0x98,
    Alarm_No_Ready = 0xA0, Alarm_No_Receive = 0xA1, Alarm_Error_Check_Sum = 0xA2, Alarm_Error_MpId = 0xA3,
    Alarm_Error_Fail = 0xA4, Alarm_Timeover = 0xA5,
    Change_Arg_No_Ready = 0xB0, Change_Arg_No_Receive = 0xB1, Change_Arg_Error_Fail = 0xB2,
    GPRS_Unline_No_Ready = 0xC0,
    MIOT_Low_Power = 0x10, All_Right = 0
} enum_status;

extern enum sendDataType {
    SampleData = 0, LowPowerData = 1, TestData = 2
} SDT;
//extern volatile enum sendDataType SDT;

//enum AlarmArgSetting {
//    HighTemp = 0x01, //���±���
//    LowTemp = 0x02, //���±���
//    HighPressure = 0x03, //��ѹ������
//    LowPressure = 0x04, //��ѹ������
//    HighPower = 0x05, //�ߵ�ѹ����
//    LowPower = 0x06, //��ѹ������
//};
//extern volatile enum AlarmArgSetting;

//enum Ptl_Type {
//    V1_2 = 0, V1_3 = 1, A1 = 2, A2 = 3, A3 = 4, /*LUX=5,CPU=6,A4=7,*/Gprs = 5
//};//����Э������
//extern volatile enum Ptl_Type pt;

enum Cop_Fun_Num {
    /*GetMuiltSampDat = 0x02, */GetSampDat = 0x03, GetMIOTArg = 0x04, SetMIOTArg = 0x10,
    GetGPRSArg = 0x20, SetGPRSArg = 0x21, TestGPRS = 0x22, UnlineUpdateGPRS = 0x23, GetMIOTVer = 0x43
};
extern volatile enum Cop_Fun_Num CFN;

typedef bool(*UARTn)(u8 *dat); //bool BufferRead_UART2(u8 *data) bool BufferRead_UART2(u8 *data) 

#endif	/* XC_HEADER_TEMPLATE_H */


