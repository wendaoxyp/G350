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
#include "p24FV32KA302.h"
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

#define PC 0
#define GPRS 1

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
#define REG_ARG_SIZE 54                     //�����ֽ���    
#define REG_ARG_NUM 23                     //Miot1601��������
#define REG_DATA_SZIE 41                    //���ݰ��ֽ���
#define REG_DATA_SECTION 42                 //���ݰ����� REG_DATA_SZIE+1
#define REG_DATA_ARG_NUM 9                  //1�����ݰ��������� 
#define DataPacket_ID 0x1FFF                //���ݰ�����λ�� 0-143
#define BOR_Pulse 0x1FF0                //�����������ݱ����ַ
#define RST_Data 0x1F00                 //��λ��������
#define RST_Time 0x1FA0                 //��λ����ʱ��
#define RST_Count 0x1FB0                //��λ�������
//#define BOR_Vm 0x1FF3                   //����������������
#define BUFFERMAX1  504      //42(41���ֽڲ�����1��Ԥ��)*12
#define DataPacketNum   144     //8192/REG_DATA_SECTION=195  6*24=144  10����һ��

#define UDP_A2_LENGTH 42 //36+1+2+3

#define DataSamples 0x00 
#define HighTempAlarm 0x01 
#define LowTempAlarm 0x02
#define HighPressureAlarm 0x03 
#define LowPressureAlarm 0x04 
#define LowPowerAlarm 0x05

enum Ptl_Type {
    V1_2 = 0, V1_3 = 1, A1 = 2, A2 = 3, A3 = 4, /*LUX=5,CPU=6,A4=7,*/Gprs = 5
}; //����Э������
extern volatile enum Ptl_Type pt;

enum MP_Varible {
    v1i = 0, v1a = 1, t1 = 2, s1 = 3, v2i = 4, v2s = 5, alarm1 = 6, status1 = 7, time1 = 8
};
extern volatile enum MP_Varible mpv;

struct Alarm_Arg {
    u16 ATF : 3;
    u16 APF : 3;
    u16 ATC : 8; //144
    u16 APC : 8;
};
extern struct Alarm_Arg AlarmArgbits;

struct FLag_Arg {
    u16 tgprsFlag : 1; //gprs���߱�־λ
    u16 talarmFlag : 1; //�������߱�־λ
    //    u16 tmpFlag : 1; //�ɼ���־λ
    u16 SleepExitFlag : 1; //����ģʽ�˳���־
    u16 CheckRTCCFlag : 1; //У��RTCb��־λ    
    u16 TestFlag : 1; //���Ա�־λ 
    u16 T1CountFlag : 1; //T1��ʼ��ʱ
    u16 T1CountLastFlag : 1; //T1��ʼ��ʱ
//    u16 LowPowerGPRSFlag : 1; //�͵�ѹ��־λ
    u16 LowPowerFlag : 1; //�͵�ѹ��־λ
    u16 AlarmDataFlag : 1; //������־λ
    //    u16 SPIReadFlag : 1; //SPI����������
    //    u16 SPIWriteFlag : 1; //SPIд��������
    //    u16 SPIReadFlag : 1; //SPI����־
    //    u16 SPIWriteFlag : 1; //SPIд��־
    //    u16 SPIReadFinishFlag : 1; //SPIд��־
    //    u16 SPIWriteFinishFlag : 1; //SPIд��־
};
extern struct FLag_Arg FLagArgbits;

//struct SPI2_Arg {
//    u16 add1;
//    u8* dat1;
//    u8 bytes1;
//};
//extern struct SPI2_Arg SPI2Argbits;

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

extern const u8 PTL_LOC[6][9]; //Э�������ַ

struct Reg1_Arg {
    vu8 Buffer_ID;
    vu16 Record;
}; 
extern struct Reg1_Arg Reg1Argbits;
//ֻ������
//extern vu32 gGPRSCount; //RTCC����1���ӱ�־�����ж�ʱ�䣨mp gprs alarm��
//extern vu32 gCount; //RTCC����1���ӱ�־�����ж�ʱ�䣨mp gprs alarm��
//extern vu32 gCheckUTCount;
extern vu16 gT3Count; //��ʱ100ms�Ĵ���
//extern vu16 gT2Count; //��ʱ100ms�Ĵ���
extern vu16 gT1Count; //��Ӷ�ʱ����Ĵ���

//extern u16 gSendOKCount; //ͨ��GPRS���ͳɹ�����
extern u8 gOffsetAdd; //ÿ���ϵ�From
extern vu32 gNowCapture; //���벶������2
//extern vu32 gPulseTOffset;
//extern vu32 gPulseCount; //�����ۼ���

//extern u16 StackValue;

//#define CopPCDeadline 1000           //10s
//#define CopTCPDeadline 2000         //20s
//#define GPRS_ON_TIME  6000            //50s 5000*0.01
//#define GPRS_ON_CHECK  10000        //100s
//#define CopUDPDeadline 500          //3s
//#define CopUDPA2Sample 70              //0.7s

#define TIME_GPRS_MAX 1440   //1��
#define TIME_GPRS_MIN 60   //1Сʱ
#define TIME_MP_MAX 1440   //60���� 1��Сʱ
#define TIME_MP_MIN 3   //3����
#define TIME_ALARM_MAX 1440   //1��
#define TIME_ALARM_MIN 0  //0����

//extern u8 gSampleCount; //�ɼ�������¼ ���ڷ�������
//extern u8 gUARTtmp[2];
extern const u16 mi_arg_add[REG_ARG_NUM + 1];
//extern enum mi_arg_add_enum;
extern const u8 GPRS_Arg2[144];
extern const u8 GPRS_Arg3[144];
//extern u8 Register1[10][12];//���ڴ洢����
extern u8 AlarmData[61];
//extern u8 gCnt_Reg1; //��¼���õ�ͨ��
//#define SendUTC "+TURONG GPOT"
//#define UTCHead "UTC"

//miot����������ַ

extern enum mi_arg_add_enum {
    mi_add = 0, mi_id = 1, mp_add = 2, mp_id = 3, mi_year = 4, mi_month = 5,
    mi_day = 6, mi_hour = 7, mi_min = 8, mi_sec = 9, mi_tmp = 10,
    mi_tgprs = 11, mi_talarm = 12, mi_sp = 13, mi_arg1 = 14, mi_arg2 = 15, mi_mode = 16,
    mi_mp_po = 17, mi_hp_alarm = 18, mi_lp_alarm = 19,
    mi_ht_alarm = 20, mi_lt_alarm = 21, mi_ofst = 22
} enum_mi_arg_add;
//���ݰ�����������ַ

extern enum mi_dat_add_enum {
    mp_time = 0, mp_Qb = 1, mp_Vb = 2, mp_T = 3, mp_P = 4, mp_Qm = 5,
    mp_Vm = 6, mp_alarm = 7, mp_status = 8
} enum_mi_dat_add;

extern enum status_enum {
    Data_No_Ready = 0x80, Data_No_Receive = 0x81, Data_Error_Check_Sum = 0x82, Data_Error_MpId = 0x83,
    Data_Error_Fail = 0x84, Data_Timeover = 0x85,
    GMT_No_Ready = 0x90, GMT_No_Receive = 0x91, GMT_Error_Check_Sum = 0x92, GMT_Error_MpId = 0x93,
    GMT_Error_Fail = 0x94, GMT_Timeover = 0x95, GMT_Time_Error = 0x96, GMT_Unix_Time_Error = 0x97,
    GMT_Arg_Error = 0x98,
    Alarm_No_Ready = 0xA0, Alarm_No_Receive = 0xA1, Alarm_Error_Check_Sum = 0xA2, Alarm_Error_MpId = 0xA3,
    Alarm_Error_Fail = 0xA4, Alarm_Timeover = 0xA5,
    Change_Arg_No_Ready = 0xB0, Change_Arg_No_Receive = 0xB1, Change_Arg_Error_Fail = 0xB2,
    MIOT_Low_Power = 0x10, All_Right = 0
} enum_status;

typedef bool(*UARTn)(u8 *dat); //bool BufferRead_UART2(u8 *data) bool BufferRead_UART2(u8 *data) 
extern const u8 ReceiveOK[6];
extern const u8 Ver[5];
//extern u8 Buffer_uart1[256];
#endif	/* XC_HEADER_TEMPLATE_H */


