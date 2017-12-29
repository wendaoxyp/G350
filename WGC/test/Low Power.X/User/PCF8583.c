#include <PCF8583.h>
#include <I2C.h>
#include "Common.h"

#define PCF_ADD 0xA2//设置地址
#define PCF_CON_STA 0x00//PCF8583的控制状态寄存器

//typedef enum {
//    con = 0, /* sec_100 = 1, sec = 2, min = 3, hours = 4, year = 5, months = 6, */timer = 7,
//    alarm_con = 8, alarm_reg = 9
//} PCF_Reg;

void PCF8583_Init(void) {
    TRISBbits.TRISB13 = 1; //外部RTCC闹钟中断设置为输入

}

void PCF8583_SetTime(uint32_t* timestamp) {//时间戳单位是1s，报警时间单位是2s
    struct tm time_tmp;
    time_tmp = *gmtime((time_t*) timestamp);
    uint8_t tmp[8] = {0x85, 00}; // 05
    tmp[2] = DCH(time_tmp.tm_sec);
    tmp[3] = DCH(time_tmp.tm_min);
    tmp[4] = DCH(time_tmp.tm_hour) & 0x3F;
    tmp[5] = (GetMod(time_tmp.tm_year + 1900, 2) << 6) + (DCH(time_tmp.tm_mday) & 0x3F);
    tmp[6] = (DCH(time_tmp.tm_wday) << 5)+(DCH(time_tmp.tm_mon + 1) & 0x1F); //注意tm结构的数据，1月份表示0
    tmp[7] = 0; //设置定时器
    //    tmp[8] = 0xB0; //0x90; //设置报警控制器
    //    tmp[9] = 00; //报警百分秒
    //    tmp[10] = 4; //GetMod(alarmtime, 30); //报警秒
    //    tmp[11] = 0; //GetMod(alarmtime / 30, 60); //报警分钟
    //    tmp[12] = 0; //GetMod(alarmtime / 1800, 60); //报警小时
    //    tmp[13] = tmp[14] = 0; //报警日期和月份=0
    //    uint8_t tmp1[4] = {CAT_ADD, 0x00, 0x00, 0x00};    
    i2c1_state = S_MASTER_IDLE;//123
    i2c_buf.operatcode = PCF_ADD;
    i2c_buf.address = PCF_CON_STA;
    i2c_buf.length = sizeof (tmp) / sizeof (uint8_t);
    i2c_buf.pbuffer = tmp;
    i2c_buf.flag.F_IsSelectiveMode = 1;
    i2c_buf.flag.F_WriteOrRead = 0;
    i2c_buf.flag.F_Is16bitsDevice = 0;
    IFS1bits.MI2C1IF = 1;

    while (i2c1_state != S_MASTER_Finish); //等待发送完成，避免重复发送数据
    //    while (IFS1bits.MI2C1IF);
    //    while (i2c1_state != S_MASTER_IDLE);
}

void PCF8583_SetAlarmTime(struct tm alarmtime) {
    uint8_t tmp[7] = {0x90, 00}; //调试cat24c512 地址0xA8写操作地址 05
    //    tmp[8] = 0xB0; //0x90; //设置报警控制器
    //    tmp[9] = 00; //报警百分秒
    tmp[2] = DCH(alarmtime.tm_sec); //GetMod(alarmtime, 30); //报警秒
    tmp[3] = DCH(alarmtime.tm_min); //GetMod(alarmtime / 30, 60); //报警分钟
    tmp[4] = DCH(alarmtime.tm_hour); //GetMod(alarmtime / 1800, 60); //报警小时
    tmp[5] = tmp[6] = 0; //报警日期和月份=0
    //    uint8_t tmp1[4] = {CAT_ADD, 0x00, 0x00, 0x00};
    i2c_buf.operatcode = PCF_ADD;
    i2c_buf.address = PCF_CON_STA + 8;
    i2c_buf.length = sizeof (tmp) / sizeof (uint8_t);
    i2c_buf.pbuffer = tmp;
    i2c_buf.flag.F_IsSelectiveMode = 1;
    i2c_buf.flag.F_WriteOrRead = 0;
    i2c_buf.flag.F_Is16bitsDevice = 0;
    i2c1_state = S_MASTER_IDLE;
    IFS1bits.MI2C1IF = 1;

    while (i2c1_state != S_MASTER_Finish); //等待发送完成，避免重复发送数据
}

uint32_t PCF8583_ReadTime(void) {
    struct tm time_tmp; //timestamp

    uint8_t tmp[5] = {0x03, 00}; //调试cat24c512 地址0xA8写操作地址 
    i2c_buf.operatcode = PCF_ADD;
    i2c_buf.address = PCF_CON_STA + 2; //从秒开始读取
    i2c_buf.length = sizeof (tmp) / sizeof (uint8_t);
    i2c_buf.pbuffer = tmp;
    i2c_buf.flag.F_IsSelectiveMode = 1;
    i2c_buf.flag.F_WriteOrRead = 1;
    i2c_buf.flag.F_Is16bitsDevice = 0;
    i2c1_state = S_MASTER_IDLE;
    IFS1bits.MI2C1IF = 1;
    while (i2c1_state != S_MASTER_Finish); //等待发送完成，避免重复发送数据

    time_tmp.tm_sec = HCD(tmp[0]); //秒
    time_tmp.tm_min = HCD(tmp[1]); //分
    time_tmp.tm_hour = HCD(tmp[2]&0x3F); //小时
    time_tmp.tm_mday = HCD(tmp[3]&0x3F); //天
    time_tmp.tm_mon = HCD(tmp[4]&0x1F) - 1; //月
    time_tmp.tm_year = (uint16_t) (tmp[3] >> 6) + 2016 - 1900; //注意是否需要更新年份见2016这个变量放入E2ROM

    return mktime(&time_tmp);
}

void PCF8583_SetStatusReg(uint8_t reg) {//包含
    //    uint8_t tmp = 0x05; //开始计时 05
    i2c_buf.operatcode = PCF_ADD;
    i2c_buf.address = PCF_CON_STA;
    i2c_buf.length = 1;
    i2c_buf.pbuffer = &reg;
    i2c_buf.flag.F_IsSelectiveMode = 1;
    i2c_buf.flag.F_WriteOrRead = 0;
    i2c_buf.flag.F_Is16bitsDevice = 0;
    i2c1_state = S_MASTER_IDLE;
    IFS1bits.MI2C1IF = 1;
    while (i2c1_state != S_MASTER_Finish); //等待发送完成，避免重复发送数据
}

void PCF8583_ReadStatus(uint8_t *tmp) {
    //    struct tm time_tmp; //timestamp

    //    uint8_t tmp[16] = {0x03, 00}; //调试cat24c512 地址0xA8写操作地址 
    i2c_buf.operatcode = PCF_ADD;
    i2c_buf.address = PCF_CON_STA; //从秒开始读取
    i2c_buf.length = 16;
    i2c_buf.pbuffer = tmp;
    i2c_buf.flag.F_IsSelectiveMode = 1;
    i2c_buf.flag.F_WriteOrRead = 1;
    i2c_buf.flag.F_Is16bitsDevice = 0;
    i2c1_state = S_MASTER_IDLE;
    IFS1bits.MI2C1IF = 1;
    while (i2c1_state != S_MASTER_Finish); //等待发送完成，避免重复发送数据

    //    time_tmp.tm_sec = HCD(tmp[0]); //秒
    //    time_tmp.tm_min = HCD(tmp[1]); //分
    //    time_tmp.tm_hour = HCD(tmp[2]&0x3F); //小时
    //    time_tmp.tm_mday = HCD(tmp[3]&0x3F); //天
    //    time_tmp.tm_mon = HCD(tmp[4]&0x1F) - 1; //月
    //    time_tmp.tm_year = (uint16_t) (tmp[3] >> 6) + 2016 - 1900; //注意是否需要更新年份见2016这个变量放入E2ROM

    //    return mktime(&time_tmp);
}

//void PCF8583_CelarFlag(void) {
//    uint8_t tmp = 0x05; //开始计时 05
//    i2c_buf.operatcode = PCF_ADD;
//    i2c_buf.address = PCF_CON_STA;
//    i2c_buf.length = 1;
//    i2c_buf.pbuffer = &tmp;
//    i2c_buf.flag.F_IsSelectiveMode = 1;
//    i2c_buf.flag.F_WriteOrRead = 0;
//    i2c_buf.flag.F_Is16bitsDevice = 0;
//    i2c1_state = S_MASTER_IDLE;
//    IFS1bits.MI2C1IF = 1;
//    while (i2c1_state != S_MASTER_Finish); //等待发送完成，避免重复发送数据
//}


