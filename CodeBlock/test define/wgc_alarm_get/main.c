#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <stdbool.h>

typedef struct tagWGCCON0BITS {
    uint16_t Send_60s : 11; //发送时间,单位：分钟 2^15=32768
    uint16_t None : 4; //未定义
} WGCCON0BITS;
volatile WGCCON0BITS WGCCON0bits;

typedef struct tagWGCCON1BITS {
    uint16_t Sample_5s : 15; //采集时间,单位：秒 刻度5s
    uint16_t None : 1; //未定义
} WGCCON1BITS;
volatile WGCCON1BITS WGCCON1bits;

typedef struct tagWGCPERIODBITS {
    uint64_t B1 : 16; //周期倍数
    uint64_t Y2 : 16; //周期余数
    uint64_t CNT : 16; //周期循环次数
    uint64_t RST_FLAG : 1; //重新计算周期标志
} WGCPERIODBITS;
 volatile WGCPERIODBITS WGCPeriodbits;



bool WGC_CalcAlarmPeriod(void) {//设置下次报警时间
    struct tm now_time, set_time; //时间数据
    time_t now_second; //当前秒数
    uint8_t cnt;

    if (WGCPeriodbits.RST_FLAG) {//如果需要重启的话,那么重新计算周期参数；反之，设置下次报警的时间
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
        WGCPeriodbits.B1 = WGCCON1bits.Sample_5s / (WGCCON0bits.Send_60s * 12); //倍数
        WGCPeriodbits.Y2 = WGCCON1bits.Sample_5s % (WGCCON0bits.Send_60s * 12); //余数
        WGCPeriodbits.CNT = 0; //清楚计数
    } else {
        //获取当前的时间，然后在这个时间的基础上加上秒数
        while (!RTC_Read_Time(&now_time)) {//容错设计
            cnt++;
            //LCD显示报警 LED显示错误 错误代码01
            if (cnt > 10)
                return false;
        } //确保获取当前的时间数据一样
        now_second = mktime(&now_time); //计算当前的时间
        if (WGCPeriodbits.CNT >= WGCPeriodbits.B1) {//下个时间就是发送的时间
            //设置报警时间为余数的时间
            now_second += WGCPeriodbits.Y2 * 5; //加上报警的时间
            WGCPeriodbits.CNT = 0;
        } else {
            //设置报警时间为采集的时间
            now_second += WGCCON1bits.Sample_5s * 5; //加上报警的时间
            WGCPeriodbits.CNT += 1;
        }
        set_time = *gmtime(now_second); //转化为时间结构
//        RTC_Set_Alarm(set_time); //设置报警时间
    }
    return true;
}


int main()
{
    printf("Hello world!\n");
    return 0;
}
