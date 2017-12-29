//#include<p24FV32KA301.h>
#include"UART.h"
#include "user.h"
#include "Common.h"

u16 gRTCCDate[4]; //用于存放日期参数

/*************************************
Function: RTC_Configuration 
Description: 实时时钟和闹钟初始化
Input: 无
Output: 无
 *************************************/
void RTC_Configuration(void) {
    //    RTCPWCbits.RTCCLK=1;            //RTCC 时钟选择位:RTCC 时钟选择位
    //    RCFGCALbits.RTCOE=0;            //禁止 RTCC 输出
    //    RCFGCALbits.RTCSYNC=0;          //RTCC 值寄存器读同步位  
    //    RCFGCALbits.CAL=0;              //RTC 漂移校准位
    u8 rtcc_tmp[7] = {0, 0, 0, 0, 0, 0, 0};
//    Register2Read(rtcc_tmp, mi_arg_add[mi_year], 7);
    asm volatile ("push w7"); //将 RTCWREN 位置 1
    asm volatile ("push w8");
    asm volatile ("disi #5");
    asm volatile ("mov #0x55, w7");
    asm volatile ("mov w7, _NVMKEY");
    asm volatile ("mov #0xAA, w8");
    asm volatile ("mov w8, _NVMKEY");
    asm volatile ("bset _RCFGCAL, #13"); //set the RTCWREN bit
    asm volatile ("pop w8");
    asm volatile ("pop w7");

    RCFGCALbits.RTCPTR = 3; //RTCC 值寄存器窗口指针位
    RTCVAL = rtcc_tmp[1] & 0x00FF; //0x0016; //年份  2016.6.1. 3 13:10:10
    RTCVAL = (rtcc_tmp[2] << 8) + rtcc_tmp[3]; //0x1022; //月份 日期
    RTCVAL = rtcc_tmp[4] & 0x00FF; //0x0008; //星期  小时
    RTCVAL = (rtcc_tmp[5] << 8) + rtcc_tmp[6]; //0x3050; //分钟 秒 

    ALCFGRPTbits.AMASK = 0b0011; //1s// 0010:10s//闹钟掩码设置 0x11每分钟闹钟中断一次
    ALCFGRPTbits.CHIME = 1; //1 = 使能响铃； ARPT<7:0> 允许从 00h 进位到 FFh
    ALCFGRPTbits.ALRMPTR = 3; //闹钟值寄存器窗口指针位
    ALRMVAL = 0x0000; //none       
    ALRMVAL = 0x0000; //month day 0001
    ALRMVAL = 0x0000; //week hour
    ALRMVAL = 0x0000; //minute second  0000
    //    ALCFGRPTbits.ARPT=0;
    ALCFGRPTbits.ALRMEN = 1; //闹钟已使能 （每当 ARPT<7:0> = 00 和 CHIME = 0 时，发生闹钟事件后都自动清零）    

    RTCPWCbits.RTCCLK = 0; //SOSC 1; //RTCC 时钟选择位:RTCC 时钟选择位
    RCFGCALbits.RTCOE = 0; //禁止 RTCC 输出
    RCFGCALbits.RTCSYNC = 0; //RTCC 值寄存器读同步位  
    RCFGCALbits.CAL = 0; //RTC 漂移校准位
    IPC15bits.RTCIP = 4;
    IFS3bits.RTCIF = 0; //外设相关的中断标志状态位清零
    IEC3bits.RTCIE = 1; //开中断 =1

    RCFGCALbits.RTCEN = 1; //使能 RTCC 模块
}

/*************************************
Function: RTC_ReadTime 
Description: 获取实时时钟的时间
Input: 4个u16类型数据 
Output: 无
 *************************************/
void RTCReadTime(u8* dat) {
    u16 tmp[4];

    while (1) {
        if (RCFGCALbits.RTCSYNC)//等待进入安全读取域
            continue;
//        __builtin_write_RTCWEN(); //开启写使能
        RCFGCALbits.RTCPTR = 3; //RTCC 值寄存器窗口指针位
        tmp[0] = RTCVAL; //获取年份 17 or 23   [17] 0000 0000 0001 0001
        RCFGCALbits.RTCPTR = 2;
        tmp[1] = RTCVAL; //获取月日[20a]
        RCFGCALbits.RTCPTR = 1;
        tmp[2] = RTCVAL; //获取小时[1]
        RCFGCALbits.RTCPTR = 0;
        tmp[3] = RTCVAL; //获取分钟 秒[1D03]
//        RCFGCALbits.RTCWREN = 0; //关闭写使能
        *(dat) = 0x20;
        *(dat + 1) = (u8) (tmp[0] & 0X00FF); //年份   屏蔽高8位    2016.6.1. 3 13:10:10
        *(dat + 2) = (u8) (tmp[1] >> 8);
        *(dat + 3) = (u8) (tmp[1] & 0X00FF); //月份 日期
        *(dat + 4) = (u8) (tmp[2] & 0x00FF); //星期  小时   
        *(dat + 5) = (u8) (tmp[3] >> 8);
        *(dat + 6) = (u8) (tmp[3] & 0x00FF); //分钟 秒 
        break;
    }
}

/*************************************
Function: Check_RTCC 
Description: 从仪表获取时间 赋值给RTCC
Input: 6个u8类型数据
Output: 无
 *************************************/
void CheckRTCC(void) {
    //    IEC3bits.RTCIE = 0; //关闭中断 
    //    RCFGCALbits.RTCEN = 0; //关闭 RTCC 模块

    u8 rtcc_tmp[7] = {0, 0, 0, 0, 0, 0, 0};
//    Register2Read(rtcc_tmp, mi_arg_add[mi_year], 7); //0x14 0x11
    //    rtcc_tmp[0] = DCH(rtcc_tmp[0]); //20->0x20
    //    rtcc_tmp[1] = DCH(rtcc_tmp[1]);
    //    rtcc_tmp[2] = DCH(rtcc_tmp[2]);
    //    rtcc_tmp[3] = DCH(rtcc_tmp[3]);
    //    rtcc_tmp[4] = DCH(rtcc_tmp[4]);
    //    rtcc_tmp[5] = DCH(rtcc_tmp[5]);
    //    rtcc_tmp[6] = DCH(rtcc_tmp[6]);
    //    Nop();
    asm volatile ("push w7"); //将 RTCWREN 位置 1
    asm volatile ("push w8");
    asm volatile ("disi #5");
    asm volatile ("mov #0x55, w7");
    asm volatile ("mov w7, _NVMKEY");
    asm volatile ("mov #0xAA, w8");
    asm volatile ("mov w8, _NVMKEY");
    asm volatile ("bset _RCFGCAL, #13"); //set the RTCWREN bit
    asm volatile ("pop w8");
    asm volatile ("pop w7");

    RCFGCALbits.RTCPTR = 3; //RTCC 值寄存器窗口指针位
    RTCVAL = rtcc_tmp[1] & 0x00FF; //0x0016; //年份  2016.6.1. 3 13:10:10
    RTCVAL = (rtcc_tmp[2] << 8) + rtcc_tmp[3]; //0x1022; //月份 日期
    RTCVAL = rtcc_tmp[4] & 0x00FF; //0x0008; //星期  小时
    RTCVAL = (rtcc_tmp[5] << 8) + rtcc_tmp[6]; //0x3050; //分钟 秒 
//    RCFGCALbits.RTCWREN = 0;//关闭读写使能
    //    Nop();
    //    IEC3bits.RTCIE = 1; //开启中断
    //    RCFGCALbits.RTCEN = 1; //开启RTCC
    //    Nop();
}

/*************************************
Function: StartRTCC 
Description: 
Input: 
Output: 
 *************************************/
void StartRTCC(void) {

    IEC3bits.RTCIE = 1; //开启中断
    ALCFGRPTbits.ALRMEN = 1;
    RCFGCALbits.RTCEN = 1; //开启RTCC
}

/*************************************
Function: StopRTCC 
Description: 
Input: 
Output: 
 *************************************/
void StopRTCC(void) {
    IEC3bits.RTCIE = 0; //关闭中断 
    ALCFGRPTbits.ALRMEN = 0;
    RCFGCALbits.RTCEN = 0; //关闭 RTCC 模块
}

/*************************************
Function: OutputData 
Description: 通过串口2打印4*u16类型的数据
Input: 4个u16类型数据 
Output: 无
 *************************************/
//void OutputData(u16* dat)
//{
//    u8 count=0;
//    *dat|=0x2000;        
//    while(count<4)
//    {
//        UART2Send(RTC_NumProcess(dat+count,12));
//        UART2Send(RTC_NumProcess(dat+count,8));
//        UART2Send(RTC_NumProcess(dat+count,4));
//        UART2Send(RTC_NumProcess(dat+count,0));
//        UART2Send(' ');
//        count++;
//    }
//    UART2Send('\n');
//}
/*************************************
Function: RTC_NumProcess 
Description: 输入数据和右移数，获得对应ASC数值
Input: 4个u16类型数据 ，位移数
Output: 输出ASCII
 *************************************/
//static u8 RTCNumProcess(u16*d,u8 s)
//{
//    return (u8)(((*d>>s)&0x000f)+0x30);
//}




