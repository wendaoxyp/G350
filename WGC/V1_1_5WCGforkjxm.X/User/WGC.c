#include "WGC.h"

#define TIMEOFFSET 1483200000

//enum {Jan=31,Feb=30,Mar=31,Apr=30,May=31,Jun=30,Jul=31,Aug=31,Sep=30,Oct=31,Nov=30,Dec=31};
uint8_t Month[12] = {31, 30, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

volatile WGCTIME0BITS WGCTIME0bits;
volatile WGCTIME1BITS WGCTIME1bits;
volatile WGCTIME2BITS WGCTIME2bits;
volatile WGCCON0BITS WGCCON0bits;
volatile WGCCON1BITS WGCCON1bits;
volatile WGCCON2BITS WGCCON2bits;
volatile WGCCON3BITS WGCCON3bits;
volatile WGCCON4BITS WGCCON4bits;
volatile WGCIPBITS WGCIPbits;
volatile uint16_t WGCPORT;
//volatile WGCPERIODBITS WGCPeriodbits;
volatile uint8_t WGC_Sta = 1;
//struct RTCC_Time_Node RT_node;

//static volatile struct RTCC_Time_Node rtcc_sample;
//static volatile struct RTCC_Time_Node rtcc_send;

void WGC_Init(void) {
    WGCIPbits.IP3 = 139; //设置IP地址
    WGCIPbits.IP2 = 196;
    WGCIPbits.IP1 = 122;
    WGCIPbits.IP0 = 159;
    WGCPORT = 5080; //设置端口号
    WGCCON0bits.Send_60s = 0x01; //发送2分钟
    WGCCON1bits.Sample_5s = 0x03; //采集5秒
    WGCCON2bits.E41_Is_Use_For_Send_Data = 0; //关闭E41
    WGCCON2bits.E41_Is_Use_For_Set_Arg = 0; //关闭E41
    WGCCON2bits.WGC_ID = 0x03; //ID号
    //    RTCC_TIME_Init(); //初始化RTCC_TIME数据结构
    WGCCON2bits.Period_FLAG = 1; //初始化开始计算时间
    //    WGCPeriodbits.CNT = 0;
    //    WGCCON2bits.Alarm_RST_FLAG = 0; //上电成重新计算
}

//static void GetPressure(void) {
//    
//}

//bool WGC_CalcAlarmPeriod(void) {//设置下次报警时间
//    struct tm now_time1, now_time2;
//    uint32_t time1;
//    //获取当前的时间，然后在这个时间的基础上加上秒数
//    while (!RTC_Read_Time(&now_time1)); //容错设计
//    //    while (!RTC_Read_Time(&now_time1)); //容错设计
//    time1 = mktime(&now_time1);
//    time1 += 10;
//    now_time2 = *gmtime(&time1);
//
//    RTC_Set_Alarm(now_time1);
//}

void GPRS_Task(void) {
    uint8_t tmp[20];
    HL6528_GetIP_Port(); //每次通讯都更新下IP地址和端口号
    UART2_Open();
    WGC_Sta = GPRS_Dingling; //GPRS拨号
    //        HL6528_GetIP_Port(tmp);
    if (!HL6528_DialingIsERR()) {
        WGC_Sta = GPRS_Online; //GPRS发送数据
        Delays(1); //延时1s
        CAT24C512_Read(1, tmp); //获取数据  !!!添加判断 如果I2C错误
        //处理数据
        UART2_SendString2(tmp + 3, 4); //发送传输数据
        Delays(1); //延时1s
    } else
        WGC_Sta = GPRS_Err; //GPRS拨号失败

    HL6528_Close(); //发送AT指令传输数据}
}

void Sample_Task(void) {
    uint8_t Sendstr[] = {0x01, 0x03, 0x00, 0x64, 0x00, 0x02, 0x85, 0xD4}; //获取压力的指令
    StrCmp pressure;
    uint8_t Getstr[20] = {0x01, 0x03, 0x04}; //用于保存接收的数据
    uint8_t Savstr[50] = {0x00}; //uart获取缓冲区数据
    RS485SendString(Sendstr, 8);

    Delays(1); //延时1s 需要测试下
    pressure.CheckData = Getstr;
    pressure.Check_len = 3;
    pressure.GetData = Getstr;
    pressure.Get_len = 9;
    pressure.SourceData = Savstr;
    pressure.Source_len = UARTGetData(BufferRead_UART1, Savstr, 50);

    if (UARTDataIsRight(&pressure)) {
        //        WGC_Sta = Sample_Send_Flag;
        //        CAT24C512_Write(1, Savstr);
    } else {
        //        WGC_Sta = Sample_Err;
    }
}



//    if (WGCCON2bits.Alarm_RST_FLAG) {//如果需要重启的话,那么重新计算周期参数；反之，设置下次报警的时间
//        WGCCON2bits.Alarm_RST_FLAG = 0; //清楚标志为
//        if (WGCCON0bits.Send_60s < 3)//发送阈值判断
//            WGCCON0bits.Send_60s = 3;
//        else if (WGCCON0bits.Send_60s > 1440)
//            WGCCON0bits.Send_60s = 1440;
//        if (WGCCON1bits.Sample_5s < 1)//采集阈值判断
//            WGCCON1bits.Sample_5s = 1;
//        else if (WGCCON1bits.Sample_5s > 17280)
//            WGCCON1bits.Sample_5s = 17280;
//
//        if (WGCCON1bits.Sample_5s > (WGCCON0bits.Send_60s * 12))//如果采集时间大于发送时间，那么将采集时间设置为发送时间
//            WGCCON1bits.Sample_5s = WGCCON0bits.Send_60s * 12;
//        WGCPeriodbits.B1 = (WGCCON0bits.Send_60s * 12) / WGCCON1bits.Sample_5s; //倍数
//        WGCPeriodbits.Y2 = (WGCCON0bits.Send_60s * 12) % WGCCON1bits.Sample_5s; //余数     
//        WGCPeriodbits.CNT = 0; //清楚计数
//    }



//    if (WGCPeriodbits.CNT == WGCPeriodbits.B1) {//下个时间就是发送的时间
//        //设置报警时间为余数的时间
//        if (!WGCPeriodbits.Y2) {//如果余数为0的话，那么直接设置下次采集时间（上传时间已经到了），反之，设置下次计算上传时间
//            now_second += (WGCCON1bits.Sample_5s * 5); //设置下次报警的时间
//            //开始调用GPRS上传数据
//            WGCCON2bits.Send_FLAG = 1; //采集时间和发送时间均到了
//            WGCPeriodbits.CNT = 0;
//        } else {
//            now_second += WGCPeriodbits.Y2 * 5; //设置上传时间
//            WGCPeriodbits.CNT += 1;
//        }
//    } else if (WGCPeriodbits.CNT > WGCPeriodbits.B1) {
//        now_second += (WGCCON1bits.Sample_5s * 5); //设置下次报警的时间
//        //开始调用GPRS上传数据
//        WGCPeriodbits.CNT = 0;
//    } else {
//        //设置报警时间为采集的时间
//        WGCCON2bits.Sample_FLAG = 1;
//        now_second += (WGCCON1bits.Sample_5s * 5); //加上报警的时间
//        WGCPeriodbits.CNT += 1;
//    }

uint32_t CalaAlarmTime(void) {
    static uint8_t cnt = 0;
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
        WGCCON4bits.delay = WGCCON0bits.Send_60s * 12 % WGCCON1bits.Sample_5s; //计算上传的时间
        WGCCON4bits.count = 0; //上传累计次数清零
#endif
        return WGCCON3bits.delay;
    } else {
        if (cnt < WGCCON3bits.count - 1) {//如果技术的时间还没有到，那么继续将定时设置为采集的时间
            WGCCON2bits.Sample_FLAG = 1;
            cnt += 1;
#ifdef DEBUG_RTCC_TIME
            samplecount = cnt;
#endif
            return WGCCON3bits.delay;
        } else {//如果采集计数和规定的时间计数相同，那么需要判断是否采集时间是否是上传时间的整数倍
            //            cnt += 1;
            //#ifdef DEBUG_RTCC_TIME
            //            samplecount = cnt;
            //#endif
            if (WGCCON4bits.delay)//如果发送时间刚好是采集时间的整数倍的话，将控制寄存器2标志为置1、设置下次定时时间
            {
                if (WGCCON4bits.count) {
                    WGCCON4bits.count = 0;
                    WGCCON2bits.Send_FLAG = 1;
                    cnt = 0;
                    return WGCCON3bits.delay - WGCCON4bits.delay;
                }
#ifdef DEBUG_RTCC_TIME
                samplecount = cnt + 1;
#endif
                WGCCON4bits.count += 1; //上线次数加1
                return WGCCON4bits.delay;
            } else//反之，将定时时间设置为采样的时间
            {
#ifdef DEBUG_RTCC_TIME
                samplecount = cnt + 1;
#endif
                WGCCON2bits.Sample_FLAG = WGCCON2bits.Send_FLAG = 1;
                cnt = 0; //清楚内部计数
                return WGCCON3bits.delay;
            }
        }
    }
}

void SetNextAlarm(uint32_t sample_sec) {
    struct tm time1;
    uint32_t tmp, tmp1;

    enum {
        sec, min, hour, day, mon, year
    };

    while (!RTC_Read_Time(&time1)); //容错设计
    tmp = (time1.tm_sec + sample_sec); //计算秒数
    time1.tm_sec = tmp % 60;
    tmp1 = tmp / 60; //分钟是否溢出
    if (tmp1 > 0)//如果累加的时间大于60s
    {
        tmp = (time1.tm_min + tmp1);
        time1.tm_min = tmp % 60;
        tmp1 = tmp / 60;
        if (tmp1 > 0) {
            tmp = (time1.tm_hour + tmp1);
            time1.tm_hour = tmp % 24;
            tmp1 = tmp / 24;
        }
    }

    RTC_Set_Alarm(time1); //每日一次闹钟
}

