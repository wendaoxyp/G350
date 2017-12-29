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
//电压检测脚
//#define BAT_DEC_IN (TRISBbits.TRISB14=1)
//#define BAT_DEC PORTBbits.RB14

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

//SPI2通信脚
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
#define REG1_BYTES 46               //铁电存储数据字节数 不进行数据压缩处理
#define REG1_ARG_NUM 11             //铁电存储数据参数个数 
#define REG2_BYTES 58               //MIOT参数数据字节数
#define REG2_ARG_NUM 24             //MIOT参数数据参数个数
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
//#define RST_Time 0x1FA0             //复位保存时间
//#define RST_Count 0x1FB0            //复位保存计数

#define TIME_GPRS_MAX 1440          //1天
#define TIME_GPRS_MIN 60            //1小时
#define TIME_MP_MAX 1440            //60分钟 1个小时
#define TIME_MP_MIN 7               //3分钟
#define TIME_ALARM_MAX 1440         //1天
#define TIME_ALARM_MIN 0            //0分钟
#define SettingSampleTime 6         //采集时间
//#define VoltageSampleCount 10        //采集电压的次数10 16通道
//#define K_Bat  3.056                //AD采集电压转化系数 3.05690375 

#define PC 0
#define GPRS 1

#define REG3_BUF1 1     //定义寄存器缓冲区1，存放要上次的定时采集数据
#define REG3_BUF2 2     //定义寄存器缓冲区2，存放要上次的报警、测试数据

extern vu16 gT3Count; //定时器3计数值
extern vu16 gT1Count; //定时器1计数值
extern u8 gOffsetAdd; //FROM中的偏移量，每次上电从From获取
extern vu32 gPulseTime; //获取脉冲时间
extern vu32 gPulseCount; //脉冲累加量
extern float gGetVoltage; //获取电压

struct FLag_Arg {
    vu16 tgprsFlag : 1; //gprs上线标志位
    vu16 LowPoweralarmFlag : 1; //报警上线标志位    
    vu16 LowPowerGetDataFlag : 1; //低电压标志位
    vu16 TestGetDataFlag : 1; //其他数据标志位（测试）
    vu16 TestOnlieFlag : 1; //测试上线标志位（测试）
    vu16 SleepExitFlag : 1; //休眠模式退出标志
    vu16 CheckRTCCFlag : 1; //校验RTCb标志位    
    vu16 TestFlag : 1; //调试标志位 
    vu16 T1CountFlag : 1; //T1开始计时
    vu16 T1CountLastFlag : 1; //T1开始计时
    vu16 PulseTimeFlag : 1; //脉冲的时间已经获取到了   
    vu16 TESTGetStatus : 1;//获取MIOT状态
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
    u8 staMiot; //报警状态位   
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


