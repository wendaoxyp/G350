#include "RTCC.h"
#include "WGC.h"
#include "RS485.h"
#include <xc.h>

/*************************************
Function: RTC_Configuration 
Description: 实时时钟和闹钟初始化
Input: 无
Output: 无
 *************************************/
void RTC_Init(void) {
    uint8_t rtcc_tmp[7] = {0x20, 0x17, 0x10, 0x30, 0x12, 0x59, 0x00};
    // Set the RTCWREN bit
    __builtin_write_RTCWEN(); //unlock sequence

    RCFGCALbits.RTCPTR = 3; //RTCC 值寄存器窗口指针位
    RTCVAL = rtcc_tmp[1] & 0x00FF; //0x0016; //年份  2016.6.1. 3 13:10:10
    RTCVAL = (rtcc_tmp[2] << 8) + rtcc_tmp[3]; //0x1022; //月份 日期
    RTCVAL = rtcc_tmp[4] & 0x00FF; //0x0008; //星期  小时
    RTCVAL = (rtcc_tmp[5] << 8) + rtcc_tmp[6]; //0x3050; //分钟 秒 

    // PWCPOL disabled; PWCEN disabled; RTCLK SOSC; PWCPRE disabled; RTCOUT Alarm Pulse; PWSPRE disabled; 
    //    RTCPWC = 0x0000;

    //    ALCFGRPTbits.AMASK = 0b0110; //每日中断//0b0011; -1s 闹钟掩码设置 0x11每分钟闹钟中断一次
    //    ALCFGRPTbits.CHIME = 1; //1 = 使能响铃； ARPT<7:0> 允许从 00h 进位到 FFh
    ALCFGRPTbits.ALRMEN = 0; //关闭报警
    ALCFGRPTbits.ALRMPTR = 2; //闹钟值寄存器窗口指针位
    //        ALRMVAL = 0x0000; //none       
    ALRMVAL = 0x0000; //month day 0001
    ALRMVAL = 0x0000; //week hour
    ALRMVAL = 0x0000; //minute second  0000
    //    ALRMVAL = rtcc_tmp[1] & 0x00FF; //0x0016; //年份  2016.6.1. 3 13:10:10
    //    ALRMVAL = (rtcc_tmp[2] << 8) + rtcc_tmp[3]; //0x1022; //月份 日期
    //    ALRMVAL = rtcc_tmp[4] & 0x00FF; //0x0008; //星期  小时
    //    ALRMVAL = (rtcc_tmp[5] << 8) + 0x25; //rtcc_tmp[6] ; //0x3050; //分钟 秒 
    //    ALCFGRPTbits.ARPT=0;
    //    ALCFGRPTbits.ALRMEN = 1; //闹钟已使能 （每当 ARPT<7:0> = 00 和 CHIME = 0 时，发生闹钟事件后都自动清零）    

    // ALRMEN enabled; ARPT 0; AMASK Every Second; CHIME enabled; ALRMPTR MIN_SEC; 
    ALCFGRPT = 0xD800; //    every day once 
    //    ALCFGRPT = 0xC800;
    // PWCPOL disabled; PWCEN disabled; RTCLK SOSC; PWCPRE disabled; RTCOUT Alarm Pulse; PWSPRE disabled; 
    RTCPWC = 0x0000;
    IPC15bits.RTCIP = 6;
    IFS3bits.RTCIF = 0; //外设相关的中断标志状态位清零
    IEC3bits.RTCIE = 1; //开中断 =1

    RCFGCALbits.RTCEN = 1; //使能 RTCC 模块
    RCFGCALbits.RTCWREN = 0; //关闭RTCC写使能
}

void RTC_Set_Alarm(struct tm initialTime) {//, uint8_t mask) {
    //只能在禁止闹钟 （ALRMEN = 0）时更改定时器和闹钟值。建议在RTCSYNC = 0 时更改 ALCFGRPT 寄存器和 CHIME 位。
    __builtin_write_RTCWEN(); //unlock sequence

    ALCFGRPTbits.ALRMEN = 0; //关闭闹钟
    while (RCFGCALbits.RTCSYNC); //等待同步位

    ALCFGRPTbits.ALRMPTR = 2; //闹钟值寄存器窗口指针位
    ALRMVAL = ((initialTime.tm_mon) << 8) + (initialTime.tm_mday);
    ALRMVAL = ((initialTime.tm_wday) << 8) + (initialTime.tm_hour);
    ALRMVAL = ((initialTime.tm_min) << 8) + (initialTime.tm_sec);
    RCFGCALbits.RTCWREN = 0; //关闭RTCC写使能
    ALCFGRPTbits.ALRMEN = 1; //开启闹钟
}

/*************************************
Function: RTC_ReadTime 
Description: 获取实时时钟的时间
Input: 4个u16类型数据 
Output: 无
 *************************************/
bool RTC_Read_Time(struct tm*currentTime) {
    uint16_t time_tmp;
    if (RCFGCALbits.RTCSYNC)//等待进入安全读取域
        return false;

    __builtin_write_RTCWEN(); // Set the RTCWREN bit

    RCFGCALbits.RTCPTR = 3; //RTCC 值寄存器窗口指针位
    time_tmp = RTCVAL; //获取年份 
    currentTime->tm_year = time_tmp;
    RCFGCALbits.RTCPTR = 2;
    time_tmp = RTCVAL; //获取月日
    currentTime->tm_mon = (time_tmp & 0xFF00) >> 8;
    currentTime->tm_mday = time_tmp & 0x00FF;
    RCFGCALbits.RTCPTR = 1;
    time_tmp = RTCVAL; //获取小时
    currentTime->tm_wday = (time_tmp & 0xFF00) >> 8;
    currentTime->tm_hour = time_tmp & 0x00FF;
    RCFGCALbits.RTCPTR = 0;
    time_tmp = RTCVAL; //获取分钟秒
    currentTime->tm_min = (time_tmp & 0xFF00) >> 8;
    currentTime->tm_sec = time_tmp & 0x00FF;
    //    RCFGCALbits.RTCPTR = 3; //RTCC 值寄存器窗口指针位
    //    time_tmp = RTCVAL; //获取年份 
    //    currentTime->tm_year = ((((time_tmp & 0x00FF) & 0xF0) >> 4)* 10 + ((time_tmp & 0x00FF) & 0x0F));
    //    RCFGCALbits.RTCPTR = 2;
    //    time_tmp = RTCVAL; //获取月日
    //    currentTime->tm_mon = (((((time_tmp & 0xFF00) >> 8) & 0xF0) >> 4)* 10 + (((time_tmp & 0xFF00) >> 8) & 0x0F));
    //    currentTime->tm_mday = ((((time_tmp & 0x00FF) & 0xF0) >> 4)* 10 + ((time_tmp & 0x00FF) & 0x0F));
    //    RCFGCALbits.RTCPTR = 1;
    //    time_tmp = RTCVAL; //获取小时
    //    currentTime->tm_wday = (((((time_tmp & 0xFF00) >> 8) & 0xF0) >> 4)* 10 + (((time_tmp & 0xFF00) >> 8) & 0x0F));
    //    currentTime->tm_hour = ((((time_tmp & 0x00FF) & 0xF0) >> 4)* 10 + ((time_tmp & 0x00FF) & 0x0F));
    //    RCFGCALbits.RTCPTR = 0;
    //    time_tmp = RTCVAL; //获取分钟秒
    //    currentTime->tm_min = (((((time_tmp & 0xFF00) >> 8) & 0xF0) >> 4)* 10 + (((time_tmp & 0xFF00) >> 8) & 0x0F));
    //    currentTime->tm_sec = ((((time_tmp & 0x00FF) & 0xF0) >> 4)* 10 + ((time_tmp & 0x00FF) & 0x0F));
    //    currentTime->tm_isdst
    RCFGCALbits.RTCWREN = 0;

    return true;
}

/*************************************
Function: Check_RTCC 
Description: 从仪表获取时间 赋值给RTCC
Input: 6个u8类型数据
Output: 无
 *************************************/
void RTC_Set_Time(struct tm initialTime) {
    __builtin_write_RTCWEN(); // Set the RTCWREN bit
    RCFGCALbits.RTCEN = 0; //Close RTCC

    IFS3bits.RTCIF = false;
    IEC3bits.RTCIE = 0;

    // set RTCC initial time
    RCFGCALbits.RTCPTR = 3; // start the sequence
    RTCVAL = (initialTime.tm_year); // YEAR
    RTCVAL = (initialTime.tm_mon) << 8 + (initialTime.tm_mday); // MONTH-1/DAY-1
    RTCVAL = (initialTime.tm_wday) << 8 + (initialTime.tm_hour); // WEEKDAY/HOURS
    RTCVAL = (initialTime.tm_min) << 8 + (initialTime.tm_sec); // MINUTES/SECONDS   

    // Enable RTCC, clear RTCWREN         
    RCFGCALbits.RTCEN = 1;
    RCFGCALbits.RTCWREN = 0;

    IEC3bits.RTCIE = 1;
}

/*************************************
Function: RTC_Refresh_Time 
Description: 从仪表获取时间 赋值给RTCC
Input: 6个u8类型数据
Output: 无
 *************************************/

void RTC_Refresh_Time(void) {
    __builtin_write_RTCWEN(); // Set the RTCWREN bit
    RCFGCALbits.RTCEN = 0; //Close RTCC

    IFS3bits.RTCIF = false;
    IEC3bits.RTCIE = 0;

    // set RTCC initial time
    RCFGCALbits.RTCPTR = 3; // start the sequence
    RTCVAL = WGCTIME0bits.year; // YEAR
    RTCVAL = (WGCTIME0bits.month << 8) + WGCTIME1bits.day; // MONTH-1/DAY-1
    RTCVAL = WGCTIME1bits.hour; // WEEKDAY/HOURS
    RTCVAL = (WGCTIME2bits.min << 8) + WGCTIME2bits.sec; // MINUTES/SECONDS   
    // Enable RTCC, clear RTCWREN         
    RCFGCALbits.RTCEN = 1;
    RCFGCALbits.RTCWREN = 0;

    IEC3bits.RTCIE = 1;
}

/*************************************
Function: StartRTCC 
Description: 
Input: 
Output: 
 *************************************/
//void StartRTCC(void) {
//
//    IEC3bits.RTCIE = 1; //开启中断
//    ALCFGRPTbits.ALRMEN = 1;
//    RCFGCALbits.RTCEN = 1; //开启RTCC
//}

/*************************************
Function: StopRTCC 
Description: 
Input: 
Output: 
 *************************************/
//void StopRTCC(void) {
//    IEC3bits.RTCIE = 0; //关闭中断 
//    ALCFGRPTbits.ALRMEN = 0;
//    RCFGCALbits.RTCEN = 0; //关闭 RTCC 模块
//}

void PrintTime(void) {
    struct tm time1;
    uint8_t sendstr[20] = {"1234578901234567890"};
    while (!RTC_Read_Time(&time1));

    sendstr[0] = (time1.tm_year / 16) + 0x30;
    sendstr[1] = (time1.tm_year % 16) + 0x30;
    sendstr[2] = '/';
    sendstr[3] = ((time1.tm_mon + 1) / 16) + 0x30;
    sendstr[4] = ((time1.tm_mon + 1) % 16) + 0x30;
    sendstr[5] = '/';
    sendstr[6] = (time1.tm_mday / 16) + 0x30;
    sendstr[7] = (time1.tm_mday % 16) + 0x30;
    sendstr[8] = '-';
    sendstr[9] = (time1.tm_hour / 16) + 0x30;
    sendstr[10] = (time1.tm_hour % 16) + 0x30;
    sendstr[11] = ':';
    sendstr[12] = (time1.tm_min / 16) + 0x30;
    sendstr[13] = (time1.tm_min % 16) + 0x30;
    sendstr[14] = ':';
    sendstr[15] = (time1.tm_sec / 16) + 0x30;
    sendstr[16] = (time1.tm_sec % 16) + 0x30;
    sendstr[17] = '\n';
    //        sendstr[18] = '\n';
    //        sendstr[18] = '\0';
    RS485SendString(sendstr, 18);
    //        OSTimeDlyHMSM();
}
#ifdef DEBUG_RTCC_TIME

void printrtccArg(void) {
    uint8_t tmp[10];
    uint8_t strings[200] = {'\0'}; //clear history data

    strcat(strings, "S1_t:");
    my_itoa(WGCCON3bits.delay, tmp);
    strcat(strings, tmp);

    strcat(strings, ";\tS1_c:");
    my_itoa(WGCCON3bits.count, tmp);
    strcat(strings, tmp);


    strcat(strings, ";\r\nS2_t:");
    my_itoa(WGCCON4bits.delay, tmp);
    strcat(strings, tmp);

    strcat(strings, ";\tS2_c:");
    my_itoa(WGCCON4bits.count, tmp);
    strcat(strings, tmp);
    RS485SendString1(strings); //无法正确输出
}

#endif

void printnums(uint32_t settingtime) {
    uint8_t strings[50] = {'\0'}; //clear history data
    uint8_t tmp[10];
    //    strcat(strings, ch);
    my_itoa(settingtime, tmp); //最大16进制数
    strcat(strings, tmp);
    RS485SendString1(strings); //无法正确输出
    //    my_itoa(WGCCON3bits.count,tmp);
    //    strcat(strings,tmp);

    //    WGCCON3bits.delay;
    //    WGCCON4bits.count;
    //    WGCCON4bits.delay;

    //     my_itoa(); 
}


