#include "WGC.h"

#define TIMEOFFSET 1483200000
const uint8_t WGC[] = "WGC";
#define TimeRegAdd 0x00
#define GPRSRegAdd 0x06
#define IDRegAdd 0x08
#define IPRegAdd 0x09
#define PortRegAdd 0x0d
//#define TimeRegAdd 0x00
const uint8_t RegAdd[] = {0x00, 0x06, 0x0a, 0x0b, 0x0f, 0x11};
//const uint8_t RegNum[] = {0x06, 0x01, 0x01, 0x01, 0x04, 0x02};

//enum {Jan=31,Feb=30,Mar=31,Apr=30,May=31,Jun=30,Jul=31,Aug=31,Sep=30,Oct=31,Nov=30,Dec=31};
//const uint8_t Month[12] = {31, 30, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const uint8_t GetPressureInt[] = {0x01, 0x03, 0x00, 0x64, 0x00, 0x02, 0x85, 0xD4}; //��ȡѹ����ָ��
volatile WGCTIME0BITS WGCTIME0bits;
volatile WGCTIME1BITS WGCTIME1bits;
volatile WGCTIME2BITS WGCTIME2bits;
volatile WGCCON0BITS WGCCON0bits;
volatile WGCCON1BITS WGCCON1bits;
volatile WGCCON2BITS WGCCON2bits;
volatile WGCCON3BITS WGCCON3bits;
volatile WGCCON4BITS WGCCON4bits;
volatile WGCIPBITS WGCIPbits;
volatile WGCCNTBITS WGCCNTbits;
volatile uint16_t WGCPORT;
//volatile WGCPERIODBITS WGCPeriodbits;
volatile uint8_t WGC_Sta = 1;
float f_p;
//struct RTCC_Time_Node RT_node;

//static volatile struct RTCC_Time_Node rtcc_sample;
//static volatile struct RTCC_Time_Node rtcc_send;
static uint8_t MKSendString(uint8_t* tmp);
static uint8_t HandleArg(uint8_t funcode, uint8_t regadd, uint8_t *arg);
static void RefreshReg(void);

void WGC_Init(void) {
    WGCIPbits.IP3 = 183; //����IP��ַ
    WGCIPbits.IP2 = 246;
    WGCIPbits.IP1 = 74;
    WGCIPbits.IP0 = 68;
    WGCPORT = 5070; //���ö˿ں�
    WGCCON0bits.Send_60s = 1440; //����2���� mark1
    WGCCON1bits.Sample_5s = 2; //�ɼ�5��
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
    uint8_t tmp[20], bytes = 0, IsErr;
    HL6528_GetIP_Port(); //ÿ��ͨѶ��������IP��ַ�Ͷ˿ں�
    UART2_Open();
    Delay1s(5); //���⴮�ڼ�ⲻ�� ���ʹ��#ifdef
    WGC_Sta = GPRS_Dingling; //GPRS����

    IsErr = HL6528_DialingIsERR();
    //    RS485SendString1("GPRS ONline Now!!!");
    if (!IsErr) {
        LED_On();
        WGC_Sta = GPRS_Online; //GPRS��������
        Delay1s(1); //��ʱ1s
        LED_Off();
        //        CAT24C512_Read(1, tmp); //��ȡ����  !!!����ж� ���I2C����
        bytes = MKSendString(tmp);
        //��������
        UART2_SendString2(tmp, bytes); //���ʹ�������
        Delay1s(1); //��ʱ1s
#ifdef DEBUG_SEND
        RS485SendString1("GPRS ONline Now!!!");
#endif 
    } else {
        WGC_Sta = GPRS_Err; //GPRS����ʧ��
#ifdef DEBUG_SEND
        RS485SendString1("\r\nGPRS DialingFail!!!Code:");
        printnums(IsErr);
#endif
    }
    HL6528_Close(); //����ATָ�������}
    //    if (IsErr) {
    //        LED_On();
    //        Delay1s(1); //��ʱ1s
    //        LED_Off();
    //    }
}

bool Sample_Task(void) {
    StrCmp pressure;
    struct tm nowtime;
    uint8_t Getstr[50] = {0x01, 0x03, 0x04}; //���ڱ�����յ�����
    uint8_t Savstr[60] = {0x00}; //uart��ȡ����������01 03 04 3E F4 00 00 B6 29
    uint8_t Senstr[30] = {0};
    uint8_t cnt = 0; //����

    //    RS485SendString(Sendstr, 8);
    //    //    RS485SendString(Sendstr, 8);
    //    //    RS485SendString(Sendstr, 8);
    //    Delay1s(1); //��ʱ1s ��Ҫ������
    //    RS485SendString(Sendstr, 8);
    //    //    RS485SendString(Sendstr, 8);
    //    //    RS485SendString(Sendstr, 8);
    //    Delay1s(1); //��ʱ1s ��Ҫ������
    pressure.CheckData = Getstr;
    pressure.Check_len = 3;
    pressure.GetData = Getstr;
    pressure.Get_len = 9;
    pressure.SourceData = Savstr;
    do {
        cnt++;
        if (cnt > 5)
            return false; //ѭ��5�κ󣬻�δ��ȡ����Ч��ѹ��ֵ��ֱ�ӷ���false ��Ӵ�����ʾ
        RS485SendString(GetPressureInt, 8);
        Delay1s(1); //��ʱ1s 
        pressure.Source_len = UARTGetData(BufferRead_UART1, Savstr, 50);

    } while (!UARTDataIsRight(&pressure));
    CharToFloat(&f_p, Getstr + 3);
#ifdef DEBUG_PRESSURE
    RS485SendString1("\r\nGet Pressure!!!\r\n10Mp:");
    CharToFloat(&f_p, Getstr + 3);
    f_p *= 10;
    printnums((uint32_t) (f_p));
    RS485SendString1("\r\n");
    PrintTime(); //��ӡʱ��
#endif
    RTC_Read_Time(&nowtime);
    Senstr[0] = 0x20;
    Senstr[1] = nowtime.tm_year & 0x00ff;
    Senstr[2] = nowtime.tm_mon;
    Senstr[3] = nowtime.tm_mday;
    Senstr[4] = nowtime.tm_hour;
    Senstr[5] = nowtime.tm_min;
    Senstr[6] = nowtime.tm_sec;
    CopyDat(Senstr + 7, Getstr + 3, 4); //��ֵ����
    Senstr[11] = Sum_Check(Senstr, 11);
    CAT24C512_Write(Savstr); //�洢����
    return true;

    //#ifdef DEBUG_PRESSURE
    //    RS485SendString1("\r\nCan't get pressure!!!\r\n");
    //#endif

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
    static uint32_t all_alarm_time = 0;
    uint32_t alarm_time = 0; //, tmp;

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
        WGCCON4bits.delay = WGCCON0bits.Send_60s * 60; //(WGCCON0bits.Send_60s * 12 % WGCCON1bits.Sample_5s)*5; //�����ϴ���ʱ��
        WGCCON4bits.count = 0; //�ϴ��ۼƴ�������
#endif
        //        WGCCON2bits.Cala_Time_Is_Mod = WGCCON4bits.delay % WGCCON3bits.delay;
        alarm_time = WGCCON3bits.delay; //���ص�һ�βɼ�ʱ��
        all_alarm_time = alarm_time; //���ۼ�ֵ��ʼ��
    } else {
        if (cnt < WGCCON3bits.count - 1) {//���������ʱ�仹û�е�����ô��������ʱ����Ϊ�ɼ���ʱ��
            WGCCON2bits.Sample_FLAG = 1;
            StartTMR2();
            IFS0bits.T2IF = 1;
            cnt += 1;
#ifdef DEBUG_RTCC_TIME
            samplecount = cnt;
#endif
            alarm_time = WGCCON3bits.delay; //1160
            all_alarm_time += alarm_time;
        } else {//����ɼ������͹涨��ʱ�������ͬ����ô��Ҫ�ж��Ƿ�ɼ�ʱ���Ƿ����ϴ�ʱ���������
            //            tmp = WGCCON3bits.delay * cnt + last_alarm_time; //
            if (WGCCON4bits.delay != all_alarm_time) {//�������ʱ��պ��ǲɼ�ʱ����������Ļ��������ƼĴ���2��־Ϊ��1�������´ζ�ʱʱ��
                if (WGCCON4bits.count) {
                    WGCCON4bits.count = 0;
                    WGCCON2bits.Send_FLAG = 1;
                    cnt = 0;
                    //                    alarm_time = WGCCON3bits.delay - all_alarm_time;
                    all_alarm_time += WGCCON3bits.delay;
                    alarm_time = all_alarm_time % WGCCON4bits.delay;
                    all_alarm_time = alarm_time;
                    WGCCON3bits.count = (WGCCON4bits.delay - all_alarm_time) / WGCCON3bits.delay + 1; //���¼������ߵĴ���
                } else {//һ�����ڵ����һ�βɼ�����
#ifdef DEBUG_RTCC_TIME
                    samplecount = cnt + 1;
#endif 
                    WGCCON2bits.Sample_FLAG = 1;
                    StartTMR2();
                    IFS0bits.T2IF = 1;
                    WGCCON4bits.count += 1; //���ߴ�����1
                    alarm_time = WGCCON4bits.delay - all_alarm_time; //��ʾ��n������ϴ���ʱ��
                    //                    all_alarm_time += ;
                }
            } else {//��֮������ʱ��==����ʱ��
#ifdef DEBUG_RTCC_TIME
                samplecount = cnt + 1;
#endif
                WGCCON2bits.Sample_FLAG = WGCCON2bits.Send_FLAG = 1;
                StartTMR2();
                IFS0bits.T2IF = 1;
                cnt = 0; //����ڲ�����
                alarm_time = WGCCON3bits.delay;
                all_alarm_time = WGCCON3bits.delay;
                WGCCON3bits.count = WGCCON4bits.delay / WGCCON3bits.delay; //���¼������ߵĴ���
            }
        }
    }
    //    if (!last_alarm_time) {//������һ�����õı���ʱ��Ϊ0�Ļ�����ôֱ��
    //        alarm_time = WGCCON3bits.delay;
    //        last_alarm_time = 0;
    //    }
#ifdef DEBUG_RTCC_COUNT
    if (WGCCON2bits.Sample_FLAG)
        RS485SendString("/r/nsample:", 9);
    if (WGCCON2bits.Send_FLAG)
        RS485SendString("/r/nsend:", 7);
#endif
    return alarm_time;
}

void SetNextAlarm(uint32_t sample_sec) {
    struct tm time1;
    uint8_t tmp, tmp1;

    enum {
        sec, min, hour, day, mon, year
    };

    while (!RTC_Read_Time(&time1)); //�ݴ����
    tmp = (HCD(time1.tm_sec) + sample_sec); //��������
    time1.tm_sec = DCH(tmp % 60);
    tmp1 = tmp / 60; //�����Ƿ����
    if (tmp1 > 0)//����ۼӵ�ʱ�����60s
    {
        tmp = (HCD(time1.tm_min) + tmp1);
        time1.tm_min = DCH(tmp % 60);
        tmp1 = tmp / 60;
        if (tmp1 > 0) {
            tmp = (HCD(time1.tm_hour) + tmp1);
            time1.tm_hour = DCH(tmp % 24);
            tmp1 = tmp / 24;
        }
    }
    RTC_Set_Alarm(time1); //ÿ��һ������
}

//void WGCGetArg(void) {
//    do {
//
//    } while ();
//}

bool WGCPCCop(void) {
    StrCmp stcp;
    uint8_t tmp[50]; //���ڽ��ܵ�������
    uint8_t tmp1[50]; //��ȡ�������
    uint8_t tmp2[50]; //�����Ҫ���͵�����
    uint8_t cnt;

    stcp.SourceData = tmp;
    stcp.Source_len = UARTGetData(BufferRead_UART1, stcp.SourceData, 50); //��ȡmark
    stcp.CheckData = (uint8_t*) WGC;
    stcp.Check_len = 3;
    stcp.GetData = tmp1;
    stcp.Get_len = 30;
    stcp.Real_len = 0;

    if (UARTDataIsRight(&stcp) && CheckIsRight(CRC16_Check, tmp1, stcp.Real_len - 2)) {
        //���ݼĴ�����ַ�����������ݳ��Ⱥ�����,�жϽ�����������
        CopyDat(tmp2, tmp1, 4); //����֡ͷ+������  
        tmp2[4] = RegAdd[*(tmp1 + 4)+*(tmp1 + 5)] - RegAdd[*(tmp1 + 4)];
        switch (*(tmp1 + 3)) {
            case 0x04:
            {
                // * send: 57 47 43 04 00 05 17 12 10 12 10 20 00 03 00 20 05 B7 F6 4A 44 13 CE 1B FA
                // * rec: 57 47 43 04 11 17 12 10 12 10 20 00 03 00 20 05 B7 F6 4A 73 75 F2 54 69 
                CopyDat(tmp2 + 5, tmp1 + 6, tmp2[4]); //������������
                CRC16_Check(tmp2, tmp2[4] + 5); //����CRC
                for (cnt = 0; cnt < tmp1[5]; cnt++)
                    HandleArg(tmp1[3], tmp1[4] + cnt, tmp1);
                RTC_Refresh_Time();
                WGCCON2bits.Period_FLAG = 1; //���¼���RTCC
                IFS3bits.RTCIF = 1;
                RS485SendString(tmp2, tmp2[4] + 7); //�������� ע�����ݷ��Ͳ�Ҫ���ж�����
                break;
            }
            case 0x03:
            {
                // * send: 57 47 43 03 00 05 9C 74
                // * rec: 57 47 43 03 11 17 12 10 12 10 20 00 03 00 20 05 B7 F6 4A 44 12 CE 7A F2 
                RefreshReg(); //ˢ��Arg����RefreshReg
                for (cnt = 0; cnt < tmp1[5]; cnt++)
                    HandleArg(tmp1[3], tmp1[4] + cnt, tmp2);
                CRC16_Check(tmp2, tmp2[4] + 5); //����CRC
                RS485SendString(tmp2, tmp2[4] + 7); //�������� ע�����ݷ��Ͳ�Ҫ���ж�����
                break;
            }
        }
        return true;
    }
    return false;
}

static uint8_t HandleArg(uint8_t funcode, uint8_t regadd, uint8_t * arg) {
    //    uint8_t bytes;
    //���ݼĴ�����ַ�����������ݳ��Ⱥ�����,�жϽ�����������
    //* send: 57 47 43 04 00 05 17 12 10 12 10 20 00 03 00 20 05 B7 F6 4A 44 12 CE 1A 6A
    //* rec: 57 47 43 04 10 17 12 10 12 10 20 03 20 05 B7 F6 4A 44 12 CE CRCL CRCH
    switch (funcode) {//���ݹ����봦������
        case 0x04://���ò���
        {
            switch (regadd) {//�Ĵ�����ַ
                case 0://ʱ���ַ
                {
                    WGCTIME0bits.year = (*(arg + 6));
                    WGCTIME0bits.month = (*(arg + 7));
                    WGCTIME1bits.day = (*(arg + 8));
                    WGCTIME1bits.hour = (*(arg + 9));
                    WGCTIME2bits.min = (*(arg + 10));
                    WGCTIME2bits.sec = (*(arg + 11));
                    //                    bytes = 6;
                    break;
                }
                case 1://�ɼ�ʱ��ͷ���ʱ��
                {
                    WGCCON0bits.Send_60s = ((uint16_t)*(arg + 12) << 8)+*(arg + 13); //ֱ��BCD��
                    WGCCON1bits.Sample_5s = ((uint16_t)*(arg + 14))+*(arg + 15); //ֱ��BCD��
                    //                    bytes = 2;
                    break;
                }
                case 2://ID��
                {
                    WGCCON2bits.WGC_ID = *(arg + 16);
                    //                    bytes = 1;
                    break;
                }
                case 3://IP��ַ
                {
                    WGCIPbits.IP0 = *(arg + 17);
                    WGCIPbits.IP1 = *(arg + 18);
                    WGCIPbits.IP2 = *(arg + 19);
                    WGCIPbits.IP3 = *(arg + 20);
                    //                    bytes = 4;
                    break;
                }
                case 4://�˿�
                {
                    WGCPORT = (*(arg + 21) << 8)+*(arg + 22); //�˿ں� 
                    //                    bytes = 2;
                    break;
                }
            }
            break;
        }
            // * send: 57 47 43 03 00 05 9C 74
            // * rec: 57 47 43 03 11 17 12 10 12 10 20 00 03 00 20 05 B7 F6 4A 44 12 CE 7A F2 
        case 0x03://��ȡ����
        {
            switch (regadd) {//�Ĵ�����ַ
                case 0:
                {//ʱ���ַ
                    arg[5] = WGCTIME0bits.year;
                    arg[6] = WGCTIME0bits.month;
                    arg[7] = WGCTIME1bits.day;
                    arg[8] = WGCTIME1bits.hour;
                    arg[9] = WGCTIME2bits.min;
                    arg[10] = WGCTIME2bits.sec;
                    break;
                }
                case 1:
                {//�ɼ��ͷ���ʱ��
                    arg[11] = WGCCON0bits.Send_60s >> 8;
                    arg[12] = (uint8_t) (WGCCON0bits.Send_60s & 0x00FF); //(WGCCON0bits.Sample_5s>>3);
                    arg[13] = WGCCON1bits.Sample_5s >> 8;
                    arg[14] = (uint8_t) (WGCCON1bits.Sample_5s & 0x00FF);
                    break;
                }
                case 2:
                {//ID��
                    arg[15] = WGCCON2bits.WGC_ID;
                    break;
                }
                case 3:
                {//IP��ַ
                    arg[16] = WGCIPbits.IP3;
                    arg[17] = WGCIPbits.IP2;
                    arg[18] = WGCIPbits.IP1;
                    arg[19] = WGCIPbits.IP0;
                    break;
                }
                case 4:
                {//�˿ں�
                    arg[20] = WGCPORT >> 8;
                    arg[21] = WGCPORT & 0x00ff;
                    break;
                }
            }
        }
    }
    //    return bytes;
    //���ݼĴ�����ַ������,�жϽ��ж�ȡ����
    //* send: 57 47 43 03 00 05 CRCL CRCH
    //* rec: 57 47 43 03 10 17 12 10 12 10 20 03 20 05 B7 F6 4A 44 12 CE CRCL CRCH
}

static uint8_t MKSendString(uint8_t * tmp) {//�������ݲ�С��20���ֽ�
    struct tm stm;
    uint8_t bytes = 0; //���֡ͷ
    uint16_t crc;
    tmp[0] = 'A';
    tmp[1] = '2';
    tmp[2] = 20; //���ʱ��
    while (!RTC_Read_Time(&stm));
    tmp[3] = (stm.tm_year);
    tmp[4] = (stm.tm_mon);
    tmp[5] = (stm.tm_mday);
    tmp[6] = (stm.tm_hour);
    tmp[7] = (stm.tm_min);
    tmp[8] = (stm.tm_sec);
    bytes = 9;
    FloatToChar(&f_p, tmp + 9); //ת��Ϊѹ��ֵ
    crc = CRC16_Check(tmp, 13);
    tmp[13] = crc >> 8;
    tmp[14] = crc - ((crc >> 8) << 8);
    bytes = 15;
    //    strcat(tmp, tm); //���ѹ��
    return bytes;
}

static void RefreshReg(void) {
    struct tm tm_tmp;
    while (!RTC_Read_Time(&tm_tmp));
    WGCTIME0bits.year = tm_tmp.tm_year;
    WGCTIME0bits.month = tm_tmp.tm_mon;
    WGCTIME1bits.day = tm_tmp.tm_mday;
    WGCTIME1bits.hour = tm_tmp.tm_hour;
    WGCTIME2bits.min = tm_tmp.tm_min;
    WGCTIME2bits.sec = tm_tmp.tm_sec;
}

//static void LoadReg(void) {
//    //    struct tm tm_tmp;
//    //    while (!RTC_Read_Time(&tm_tmp));
//    WGCTIME0bits.year; //= DCH(tm_tmp.tm_year);
//    WGCTIME0bits.month; // = DCH(tm_tmp.tm_mon);
//    WGCTIME1bits.day; //= DCH(tm_tmp.tm_mday);
//    WGCTIME1bits.hour; // = DCH(tm_tmp.tm_hour);
//    WGCTIME2bits.min; //= DCH(tm_tmp.tm_min);
//    WGCTIME2bits.sec; //= DCH(tm_tmp.tm_sec);
//}



/*uint8_t [year,mon,day,hour,min,sec,Send_60s,Sample_5s.WGC_ID,IP0,IP1,IP2,IP3,PORT]
 *send��WGC+fun_code+reg+reg_num+CRC
 *rec��WGC+fuc_code+data_num+data[17]+CRC
 * fun_code 03:��ȡ����
 * fun_code 04:���ò���
 * /////////��ȡ����
 *send��WGC+03+reg+reg_num+CRC
 *rec��WGC+03+dat_num+dat[dat_num]+CRC
 * send: 57 47 43 03 00 05 CRCL CRCH
 * rec: 57 47 43 03 10 17 12 10 12 10 20 03 20 05 B7 F6 4A 44 12 CE CRCL CRCH
 * 
 * fun_code 03:��ȡ����
 * fun_code 04:���ò���
 * /////////��ȡ����
 *send��WGC+04+reg+reg_num+dat+CRC
 *rec��WGC+04+dat_num+dat+CRC
 * send: 57 47 43 04 00 05 17 12 10 12 10 20 03 20 05 B7 F6 4A 44 12 CE 04 35
 * rec: 57 47 43 04 10 17 12 10 12 10 20 03 20 05 B7 F6 4A 44 12 CE CRCL CRCH
 * 
 * error handle:code 0x80
 * 
 */




