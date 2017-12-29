#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
typedef struct tagWGCCON0BITS {
    uint16_t Send_60s : 11; //发送时间,单位：分钟 2^15=32768
    uint16_t None : 5; //未定义
} WGCCON0BITS;
extern volatile WGCCON0BITS WGCCON0bits;

typedef struct tagWGCCON1BITS {
    uint16_t Sample_5s : 15; //采集时间,单位：秒 刻度5s
    uint16_t None : 1; //未定义
} WGCCON1BITS;
extern volatile WGCCON1BITS WGCCON1bits;

typedef struct tagWGCCON2BITS {
    uint16_t WGC_ID : 8; //WGC的ID号 0-255
    uint16_t E41_Is_Use_For_Send_Data : 1; //短程无线是否用来发送数据
    uint16_t E41_Is_Use_For_Set_Arg : 1; //短程无线是否用来修改参数
    uint16_t Alarm_RST_FLAG : 1; //重新计算周期标志
    uint16_t Period_FLAG : 1; //rtcc标志位
    uint16_t Sample_FLAG : 1; //采样标志位
    uint16_t Send_FLAG : 1; //发送标志位
    uint16_t SET_TIME_TEST_FLAG : 1; //RTCC定时时间测试
    uint16_t PC_Cop_FLAG : 1; //用户通讯标志位
} WGCCON2BITS;
extern volatile WGCCON2BITS WGCCON2bits;
typedef struct tagWGCCON3BITS {
    uint32_t delay : 17; //0-131071s;
    uint32_t count : 15; //0-32767 次 采集时间最大为17280 发送时间最大为480 一天之内
} WGCCON3BITS;
//extern volatile WGCCON3BITS WGCCON3bits;

typedef struct tagWGCCON4BITS {
    uint32_t delay : 17; //0-131071s;
    uint32_t count : 15; //0-32767 次 采集时间最大为17280 发送时间最大为480 一天之内
} WGCCON4BITS;
//extern volatile WGCCON4BITS WGCCON4bits;
volatile WGCCON0BITS WGCCON0bits;
volatile WGCCON1BITS WGCCON1bits;
volatile WGCCON2BITS WGCCON2bits;
volatile WGCCON3BITS WGCCON3bits;
volatile WGCCON4BITS WGCCON4bits;


uint32_t CalaAlarmTime(void) {
    static uint8_t cnt = 0;
    static uint32_t last_alarm_time = 0;
    uint32_t alarm_time = 0;

    if (WGCCON2bits.Period_FLAG) {
        WGCCON2bits.Period_FLAG = 0;
#ifdef DEBUG_RTCC_TIME
        WGCCON3bits.delay = 10; //采集时间
        WGCCON3bits.count = 6; //计算采集的次数
        WGCCON4bits.delay = 0; //计算上传的时间 总时间为12*3+3=39s
        WGCCON4bits.count = 0; //上传累计次数清零
#else
        WGCCON3bits.delay = WGCCON1bits.Sample_5s * 5; //采集时间
        WGCCON3bits.count = WGCCON0bits.Send_60s * 12 / WGCCON1bits.Sample_5s; //计算采集的次数
        WGCCON4bits.delay = (WGCCON0bits.Send_60s * 12 % WGCCON1bits.Sample_5s)*5; //计算上传的时间
        WGCCON4bits.count = 0; //上传累计次数清零
#endif
        last_alarm_time = 0;
        alarm_time = WGCCON3bits.delay; //返回第一次采集时间
    } else {
        if (cnt < WGCCON3bits.count) {//如果技术的时间还没有到，那么继续将定时设置为采集的时间
            WGCCON2bits.Sample_FLAG = 1;
            StartTMR2();
            IFS0bits.T2IF = 1;
            cnt += 1;
#ifdef DEBUG_RTCC_TIME
            samplecount = cnt;
#endif
            alarm_time = WGCCON3bits.delay - last_alarm_time;
            last_alarm_time = alarm_time;
        } else {//如果采集计数和规定的时间计数相同，那么需要判断是否采集时间是否是上传时间的整数倍
            if (WGCCON4bits.delay) {//如果发送时间刚好是采集时间的整数倍的话，将控制寄存器2标志为置1、设置下次定时时间
                if (WGCCON4bits.count) {
                    WGCCON4bits.count = 0;
                    WGCCON2bits.Send_FLAG = 1;
                    cnt = 0;
                    alarm_time = WGCCON3bits.delay - last_alarm_time;
                    last_alarm_time = alarm_time;
                }
#ifdef DEBUG_RTCC_TIME
                samplecount = cnt + 1;
#endif
                WGCCON4bits.count += 1; //上线次数加1
                alarm_time = WGCCON4bits.delay;
                last_alarm_time = alarm_time;
            } else {//反之，将定时时间设置为采样的时间整数倍
#ifdef DEBUG_RTCC_TIME
                samplecount = cnt + 1;
#endif
                WGCCON2bits.Sample_FLAG = WGCCON2bits.Send_FLAG = 1;
                StartTMR2();
                IFS0bits.T2IF = 1;
                cnt = 0; //清楚内部计数
                return WGCCON3bits.delay;
            }
        }
    }
    if (!last_alarm_time) {//如果最后一次设置的报警时间为0的话，那么直接
        alarm_time = WGCCON3bits.delay;
        last_alarm_time = 0;
    }
    return alarm_time;
}
int main()
{
    WGCCON3bits.
    CalaAlarmTime();
    printf("Hello world!\n");
    return 0;
}
