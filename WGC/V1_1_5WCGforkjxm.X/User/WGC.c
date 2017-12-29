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
    WGCIPbits.IP3 = 139; //����IP��ַ
    WGCIPbits.IP2 = 196;
    WGCIPbits.IP1 = 122;
    WGCIPbits.IP0 = 159;
    WGCPORT = 5080; //���ö˿ں�
    WGCCON0bits.Send_60s = 0x01; //����2����
    WGCCON1bits.Sample_5s = 0x03; //�ɼ�5��
    WGCCON2bits.E41_Is_Use_For_Send_Data = 0; //�ر�E41
    WGCCON2bits.E41_Is_Use_For_Set_Arg = 0; //�ر�E41
    WGCCON2bits.WGC_ID = 0x03; //ID��
    //    RTCC_TIME_Init(); //��ʼ��RTCC_TIME���ݽṹ
    WGCCON2bits.Period_FLAG = 1; //��ʼ����ʼ����ʱ��
    //    WGCPeriodbits.CNT = 0;
    //    WGCCON2bits.Alarm_RST_FLAG = 0; //�ϵ�����¼���
}

//static void GetPressure(void) {
//    
//}

//bool WGC_CalcAlarmPeriod(void) {//�����´α���ʱ��
//    struct tm now_time1, now_time2;
//    uint32_t time1;
//    //��ȡ��ǰ��ʱ�䣬Ȼ�������ʱ��Ļ����ϼ�������
//    while (!RTC_Read_Time(&now_time1)); //�ݴ����
//    //    while (!RTC_Read_Time(&now_time1)); //�ݴ����
//    time1 = mktime(&now_time1);
//    time1 += 10;
//    now_time2 = *gmtime(&time1);
//
//    RTC_Set_Alarm(now_time1);
//}

void GPRS_Task(void) {
    uint8_t tmp[20];
    HL6528_GetIP_Port(); //ÿ��ͨѶ��������IP��ַ�Ͷ˿ں�
    UART2_Open();
    WGC_Sta = GPRS_Dingling; //GPRS����
    //        HL6528_GetIP_Port(tmp);
    if (!HL6528_DialingIsERR()) {
        WGC_Sta = GPRS_Online; //GPRS��������
        Delays(1); //��ʱ1s
        CAT24C512_Read(1, tmp); //��ȡ����  !!!����ж� ���I2C����
        //��������
        UART2_SendString2(tmp + 3, 4); //���ʹ�������
        Delays(1); //��ʱ1s
    } else
        WGC_Sta = GPRS_Err; //GPRS����ʧ��

    HL6528_Close(); //����ATָ�������}
}

void Sample_Task(void) {
    uint8_t Sendstr[] = {0x01, 0x03, 0x00, 0x64, 0x00, 0x02, 0x85, 0xD4}; //��ȡѹ����ָ��
    StrCmp pressure;
    uint8_t Getstr[20] = {0x01, 0x03, 0x04}; //���ڱ�����յ�����
    uint8_t Savstr[50] = {0x00}; //uart��ȡ����������
    RS485SendString(Sendstr, 8);

    Delays(1); //��ʱ1s ��Ҫ������
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



//    if (WGCCON2bits.Alarm_RST_FLAG) {//�����Ҫ�����Ļ�,��ô���¼������ڲ�������֮�������´α�����ʱ��
//        WGCCON2bits.Alarm_RST_FLAG = 0; //�����־Ϊ
//        if (WGCCON0bits.Send_60s < 3)//������ֵ�ж�
//            WGCCON0bits.Send_60s = 3;
//        else if (WGCCON0bits.Send_60s > 1440)
//            WGCCON0bits.Send_60s = 1440;
//        if (WGCCON1bits.Sample_5s < 1)//�ɼ���ֵ�ж�
//            WGCCON1bits.Sample_5s = 1;
//        else if (WGCCON1bits.Sample_5s > 17280)
//            WGCCON1bits.Sample_5s = 17280;
//
//        if (WGCCON1bits.Sample_5s > (WGCCON0bits.Send_60s * 12))//����ɼ�ʱ����ڷ���ʱ�䣬��ô���ɼ�ʱ������Ϊ����ʱ��
//            WGCCON1bits.Sample_5s = WGCCON0bits.Send_60s * 12;
//        WGCPeriodbits.B1 = (WGCCON0bits.Send_60s * 12) / WGCCON1bits.Sample_5s; //����
//        WGCPeriodbits.Y2 = (WGCCON0bits.Send_60s * 12) % WGCCON1bits.Sample_5s; //����     
//        WGCPeriodbits.CNT = 0; //�������
//    }



//    if (WGCPeriodbits.CNT == WGCPeriodbits.B1) {//�¸�ʱ����Ƿ��͵�ʱ��
//        //���ñ���ʱ��Ϊ������ʱ��
//        if (!WGCPeriodbits.Y2) {//�������Ϊ0�Ļ�����ôֱ�������´βɼ�ʱ�䣨�ϴ�ʱ���Ѿ����ˣ�����֮�������´μ����ϴ�ʱ��
//            now_second += (WGCCON1bits.Sample_5s * 5); //�����´α�����ʱ��
//            //��ʼ����GPRS�ϴ�����
//            WGCCON2bits.Send_FLAG = 1; //�ɼ�ʱ��ͷ���ʱ�������
//            WGCPeriodbits.CNT = 0;
//        } else {
//            now_second += WGCPeriodbits.Y2 * 5; //�����ϴ�ʱ��
//            WGCPeriodbits.CNT += 1;
//        }
//    } else if (WGCPeriodbits.CNT > WGCPeriodbits.B1) {
//        now_second += (WGCCON1bits.Sample_5s * 5); //�����´α�����ʱ��
//        //��ʼ����GPRS�ϴ�����
//        WGCPeriodbits.CNT = 0;
//    } else {
//        //���ñ���ʱ��Ϊ�ɼ���ʱ��
//        WGCCON2bits.Sample_FLAG = 1;
//        now_second += (WGCCON1bits.Sample_5s * 5); //���ϱ�����ʱ��
//        WGCPeriodbits.CNT += 1;
//    }

uint32_t CalaAlarmTime(void) {
    static uint8_t cnt = 0;
    if (WGCCON2bits.Period_FLAG) {
        WGCCON2bits.Period_FLAG = 0;
#ifdef DEBUG_RTCC_TIME
        WGCCON3bits.delay = 10; //�ɼ�ʱ��
        WGCCON3bits.count = 6; //����ɼ��Ĵ���
        WGCCON4bits.delay = 0; //�����ϴ���ʱ�� ��ʱ��Ϊ12*3+3=39s
        WGCCON4bits.count = 0; //�ϴ��ۼƴ�������
#else
        WGCCON3bits.delay = WGCCON1bits.Sample_5s * 5; //�ɼ�ʱ��
        WGCCON3bits.count = WGCCON0bits.Send_60s * 12 / WGCCON1bits.Sample_5s; //����ɼ��Ĵ���
        WGCCON4bits.delay = WGCCON0bits.Send_60s * 12 % WGCCON1bits.Sample_5s; //�����ϴ���ʱ��
        WGCCON4bits.count = 0; //�ϴ��ۼƴ�������
#endif
        return WGCCON3bits.delay;
    } else {
        if (cnt < WGCCON3bits.count - 1) {//���������ʱ�仹û�е�����ô��������ʱ����Ϊ�ɼ���ʱ��
            WGCCON2bits.Sample_FLAG = 1;
            cnt += 1;
#ifdef DEBUG_RTCC_TIME
            samplecount = cnt;
#endif
            return WGCCON3bits.delay;
        } else {//����ɼ������͹涨��ʱ�������ͬ����ô��Ҫ�ж��Ƿ�ɼ�ʱ���Ƿ����ϴ�ʱ���������
            //            cnt += 1;
            //#ifdef DEBUG_RTCC_TIME
            //            samplecount = cnt;
            //#endif
            if (WGCCON4bits.delay)//�������ʱ��պ��ǲɼ�ʱ����������Ļ��������ƼĴ���2��־Ϊ��1�������´ζ�ʱʱ��
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
                WGCCON4bits.count += 1; //���ߴ�����1
                return WGCCON4bits.delay;
            } else//��֮������ʱʱ������Ϊ������ʱ��
            {
#ifdef DEBUG_RTCC_TIME
                samplecount = cnt + 1;
#endif
                WGCCON2bits.Sample_FLAG = WGCCON2bits.Send_FLAG = 1;
                cnt = 0; //����ڲ�����
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

    while (!RTC_Read_Time(&time1)); //�ݴ����
    tmp = (time1.tm_sec + sample_sec); //��������
    time1.tm_sec = tmp % 60;
    tmp1 = tmp / 60; //�����Ƿ����
    if (tmp1 > 0)//����ۼӵ�ʱ�����60s
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

    RTC_Set_Alarm(time1); //ÿ��һ������
}

