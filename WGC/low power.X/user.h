/* 
 * File:   
 * Author: 
 * Comments:define IO
 * Revision history: 
 * V0.1 修改MP_CON的引脚
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
//电压检测脚
#define BAT_DEC_IN (TRISBbits.TRISB14=1)
#define BAT_DEC PORTBbits.RB14

//输入捕获中断
#define INPUT_PULSE_IN (TRISBbits.TRISB9=1)
#define INPUT_PULSE PORTBbits.RB9

//RS485 输入输出控制脚F
#define MC_CON_OUT (TRISBbits.TRISB3=0)
#define RS485_CON LATBbits.LATB3 
#define RS485_TX_OUT (TRISBbits.TRISB7 = 0);
#define RS485_RX_IN (TRISBbits.TRISB2 = 1);
#define RS485_RX_READ (PORTBbits.RB2)

//UART2 输入输出控制脚
#define TX2_OUT (TRISBbits.TRISB0 = 0);
#define RX2_IN (TRISBbits.TRISB1 = 1);

//SPI1通信脚
#define SCK2_TRIS TRISBbits.TRISB5
#define SCK2 LATBbits.LATB5
#define SDO2_TRIS TRISBbits.TRISB6
#define SDO2 LATBbits.LATB6
#define SDI2_TRIS TRISAbits.TRISA7
#define SDI2 PORTAbits.RA7
#define SS2_TRIS TRISBbits.TRISB12
#define SS2 LATBbits.LATB12

//升压控制脚
#define MP_CON_OUT (TRISAbits.TRISA2 = 0)
#define MP_ON (LATAbits.LATA2 = 1)
#define MP_OFF (LATAbits.LATA2 = 0)


//GPRS模块EN使能
#define GP_CON_OUT (TRISAbits.TRISA3 = 0)
#define GPRS_ON (LATAbits.LATA3 = 1)
#define GPRS_OFF (LATAbits.LATA3 = 0)

//GPRS模块LK
#define LK_IN (TRISBbits.TRISB13 = 1)
#define LK_OUT (TRISBbits.TRISB13 = 0)
#define LK PORTBbits.RB13

//输入捕获S1
#define S1_IN (TRISBbits.TRISB9 = 1)
#define S1 PORTBbits.RB9

//输入捕获S2
#define S2_IN (TRISBbits.TRISB8 = 1)
#define S2 PORTBbits.RB8

//测试IO口
#define TST_IN (TRISBbits.TRISB15 = 1)
#define TST PORTBbits.RB15

//ADC输出口
#define ADC0_IN (TRISAbits.TRISA2 = 1)//A0
#define ADC0 PORTAbits.RA2
/*************************************User Variable***************************************/
//设置波特率
#define FP 4000000//9.22 4000000Hz
#define BAUDRATE 9600
#define BRGVAL ((FP/BAUDRATE)/16) - 1

#define Reset() {__asm__ volatile("reset");}//复位设备
#define Disi() {__asm__ volatile("disi");}//禁止中断
//数据和参数
#define REG1_BYTES 46               //铁电存储数据字节数
#define REG1_ARG_NUM 11             //铁电存储数据参数个数 
#define REG2_BYTES 60               //MIOT参数数据字节数
#define REG2_ARG_NUM 26             //MIOT参数数据参数个数
#define REG3_BYTES 25               //发送缓冲区数据字节数
#define REG3_BUF1_CNT 24           //发送缓冲区1的组数
#define REG3_ARG_NUM 6             //发送缓冲区的参数个数
#define DataPacketNum   144         //8192/REG3_BYTES=195  6*24=144  10分钟一条
#define UDP_A2_LENGTH 42            //36+1+2+3
//#define REG3_BUF1_CNT 24     //定义上次采集数据的最大组数，用于存储上次的采集数据
//#define REG1_ARG_BYTES 24    //对于大众协议有效的数据只有mi_time,mp_Qm,mp_Vm,mp_Vbat,mp_status，共7+4+8+4+1字节

#define DataPacket_ID 0x1FFF        //数据包最后的位置 0-143
#define BOR_Pulse 0x1FF0            //掉电脉冲数据保存地址
#define RST_Data 0x1F00             //复位保存数据
#define RST_Time 0x1FA0             //复位保存时间
#define RST_Count 0x1FB0            //复位保存计数

#define TIME_GPRS_MAX 1440          //1天
#define TIME_GPRS_MIN 60            //1小时
#define TIME_MP_MAX 1440            //60分钟 1个小时
#define TIME_MP_MIN 7               //3分钟
#define TIME_ALARM_MAX 1440         //1天
#define TIME_ALARM_MIN 0            //0分钟
#define SettingSampleTime 6         //采集时间

#define PC 0
#define GPRS 1

#define REG3_BUF1 1     //定义寄存器缓冲区1，存放要上次的定时采集数据
#define REG3_BUF2 2     //定义寄存器缓冲区2，存放要上次的报警、测试数据

extern vu16 gT3Count; //定时器3计数值
extern vu16 gT1Count; //定时器1计数值
extern u8 gOffsetAdd; //FROM中的偏移量，每次上电从From获取
extern vu32 gPulseTime; //获取脉冲时间
extern vu32 gPulseCount; //脉冲累加量

struct FLag_Arg {
    u16 tgprsFlag : 1; //gprs上线标志位
    u16 tLowPoweralarmFlag : 1; //报警上线标志位
    u16 SleepExitFlag : 1; //休眠模式退出标志
    u16 CheckRTCCFlag : 1; //校验RTCb标志位    
    u16 TestFlag : 1; //测试标志位 
    u16 T1CountFlag : 1; //T1开始计时
    u16 T1CountLastFlag : 1; //T1开始计时
    u16 LowPowerGetDataFlag : 1; //低电压标志位
    u16 TestGetDataFlag : 1; //其他数据标志位（报警和测试）
    u16 TestOnlieFlag : 1; //上线标志位（报警和测试）
};
extern struct FLag_Arg FLagArgbits;

struct UART2_Arg {
    //    u16 add1;
    u8* dat2;
    u8 bytes2;
};
extern struct UART2_Arg UART2Argbits;

struct Status {
    //    u8 staCheckRTCC : 1; //校验RTC状态位
    u8 staMp;
    u8 staGPRS;
    u8 staMiot; //: 1; //报警状态位   
    //    u8 staBat : 1; //电池没电报警状态位
};
extern struct Status Statusbits;

struct TimeCount {
    vu32 timeMp; //mp
    vu32 timeGprs; //gprs
    vu32 timeAlarm; //报警
    vu32 timeCheckTime; //
    //    vu8 timePulse; //IC2定时记数
};
extern struct TimeCount gTimeCount;

//extern const u8 PTL_LOC[6][9]; //协议参数地址

struct Reg3_Record {
    vu8 Buffer_ID;
    vu16 Record;
};
extern struct Reg3_Record Reg3_Buf1_Recordbits; //

////miot各个参数地址
//
//extern enum REG2_Add_enum enum_REG2_Add;
//
////铁电存储数据包各个参数顺序 REG1_Add_enum
//
//extern enum mp_arg_add_enum  enum_mp_arg_add;
//
////发送缓冲数据各个参数顺序
//
//extern enum send_buffer_enum  enum_send_buffer;
//
////A2协议各个参数顺序
//
//extern enum A2_arg_add_enum enum_A2_arg_add;

//状态参数使用union

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
//    HighTemp = 0x01, //高温报警
//    LowTemp = 0x02, //低温报警
//    HighPressure = 0x03, //高压力报警
//    LowPressure = 0x04, //低压力报警
//    HighPower = 0x05, //高电压报警
//    LowPower = 0x06, //低压力报警
//};
//extern volatile enum AlarmArgSetting;

//enum Ptl_Type {
//    V1_2 = 0, V1_3 = 1, A1 = 2, A2 = 3, A3 = 4, /*LUX=5,CPU=6,A4=7,*/Gprs = 5
//};//定义协议种类
//extern volatile enum Ptl_Type pt;

enum Cop_Fun_Num {
    /*GetMuiltSampDat = 0x02, */GetSampDat = 0x03, GetMIOTArg = 0x04, SetMIOTArg = 0x10,
    GetGPRSArg = 0x20, SetGPRSArg = 0x21, TestGPRS = 0x22, UnlineUpdateGPRS = 0x23, GetMIOTVer = 0x43
};
extern volatile enum Cop_Fun_Num CFN;

typedef bool(*UARTn)(u8 *dat); //bool BufferRead_UART2(u8 *data) bool BufferRead_UART2(u8 *data) 

#endif	/* XC_HEADER_TEMPLATE_H */


