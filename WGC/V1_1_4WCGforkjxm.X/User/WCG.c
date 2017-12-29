#include "WCG.h"

#define TIMEOFFSET 1483200000

volatile WGCTIME0BITS WGCTIME0bits;
volatile WGCTIME1BITS WGCTIME1bits;
volatile WGCTIME2BITS WGCTIME2bits;
volatile WGCCON0BITS WGCCON0bits;
volatile WGCCON1BITS WGCCON1bits;
volatile WGCCON2BITS WGCCON2bits;
volatile WGCIPBITS WGCIPbits;
volatile uint16_t WGCPORT;
volatile WGCPERIODBITS WGCPeriodbits;

void WGC_Init(void) {
    WGCIPbits.IP3 = 139; //设置IP地址
    WGCIPbits.IP2 = 196;
    WGCIPbits.IP1 = 122;
    WGCIPbits.IP0 = 159;
    WGCPORT = 5080; //设置端口号
    WGCCON0bits.Send_60s = 0x01; //发送2分钟
    WGCCON1bits.Sample_5s = 0x01; //采集5秒
    WGCCON2bits.E41_Is_Use_For_Send_Data = 0; //关闭E41
    WGCCON2bits.E41_Is_Use_For_Set_Arg = 0; //关闭E41
    WGCCON2bits.WGC_ID = 0x03; //ID号
    WGCPeriodbits.CNT = 0;
    WGCCON2bits.Alarm_RST_FLAG = 1;
}

bool WGC_CalcAlarmPeriod(void) {//设置下次报警时间
    struct tm now_time;
    struct tm *set_time; //时间数据
    time_t now_second; //当前秒数
    uint8_t cnt;

    if (WGCCON2bits.Alarm_RST_FLAG) {//如果需要重启的话,那么重新计算周期参数；反之，设置下次报警的时间
        WGCCON2bits.Alarm_RST_FLAG = 0; //清楚标志为
        if (WGCCON0bits.Send_60s < 3)//发送阈值判断
            WGCCON0bits.Send_60s = 3;
        else if (WGCCON0bits.Send_60s > 1440)
            WGCCON0bits.Send_60s = 1440;
        if (WGCCON1bits.Sample_5s < 1)//采集阈值判断
            WGCCON1bits.Sample_5s = 1;
        else if (WGCCON1bits.Sample_5s > 17280)
            WGCCON1bits.Sample_5s = 17280;

        if (WGCCON1bits.Sample_5s > (WGCCON0bits.Send_60s * 12))//如果采集时间大于发送时间，那么将采集时间设置为发送时间
            WGCCON1bits.Sample_5s = WGCCON0bits.Send_60s * 12;
        WGCPeriodbits.B1 = (WGCCON0bits.Send_60s * 12) / WGCCON1bits.Sample_5s; //倍数
        WGCPeriodbits.Y2 = (WGCCON0bits.Send_60s * 12) % WGCCON1bits.Sample_5s; //余数     
        WGCPeriodbits.CNT = 0; //清楚计数
    }
    //获取当前的时间，然后在这个时间的基础上加上秒数
    while (!RTC_Read_Time(&now_time)) {//容错设计
        cnt++;
        //LCD显示报警 LED显示错误 错误代码01
        if (cnt > 10)
            return false;
    } //确保获取当前的时间数据一样
    now_second = mktime(&now_time); //计算当前的时间
    if (WGCPeriodbits.CNT == WGCPeriodbits.B1) {//下个时间就是发送的时间
        //设置报警时间为余数的时间
        if (!WGCPeriodbits.Y2) {//如果余数为0的话，那么直接设置下次采集时间（上传时间已经到了），反之，设置下次计算上传时间
            now_second += (WGCCON1bits.Sample_5s * 5); //设置下次报警的时间
            //开始调用GPRS上传数据
            WGCPeriodbits.CNT = 0;
        } else {
            now_second += WGCPeriodbits.Y2 * 5; //设置上传时间
            WGCPeriodbits.CNT += 1;
        }
    } else if (WGCPeriodbits.CNT > WGCPeriodbits.B1) {
        now_second += (WGCCON1bits.Sample_5s * 5); //设置下次报警的时间
        //开始调用GPRS上传数据
        WGCPeriodbits.CNT = 0;
    } else {
        //设置报警时间为采集的时间
        now_second += (WGCCON1bits.Sample_5s * 5); //加上报警的时间
        WGCPeriodbits.CNT += 1;
    }
    set_time = gmtime(&now_second); //转化为时间结构
    RTC_Set_Alarm(*set_time); //设置报警时间
    PrintTime();
    return true;
}


