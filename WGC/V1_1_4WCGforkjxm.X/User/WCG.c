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
    WGCIPbits.IP3 = 139; //����IP��ַ
    WGCIPbits.IP2 = 196;
    WGCIPbits.IP1 = 122;
    WGCIPbits.IP0 = 159;
    WGCPORT = 5080; //���ö˿ں�
    WGCCON0bits.Send_60s = 0x01; //����2����
    WGCCON1bits.Sample_5s = 0x01; //�ɼ�5��
    WGCCON2bits.E41_Is_Use_For_Send_Data = 0; //�ر�E41
    WGCCON2bits.E41_Is_Use_For_Set_Arg = 0; //�ر�E41
    WGCCON2bits.WGC_ID = 0x03; //ID��
    WGCPeriodbits.CNT = 0;
    WGCCON2bits.Alarm_RST_FLAG = 1;
}

bool WGC_CalcAlarmPeriod(void) {//�����´α���ʱ��
    struct tm now_time;
    struct tm *set_time; //ʱ������
    time_t now_second; //��ǰ����
    uint8_t cnt;

    if (WGCCON2bits.Alarm_RST_FLAG) {//�����Ҫ�����Ļ�,��ô���¼������ڲ�������֮�������´α�����ʱ��
        WGCCON2bits.Alarm_RST_FLAG = 0; //�����־Ϊ
        if (WGCCON0bits.Send_60s < 3)//������ֵ�ж�
            WGCCON0bits.Send_60s = 3;
        else if (WGCCON0bits.Send_60s > 1440)
            WGCCON0bits.Send_60s = 1440;
        if (WGCCON1bits.Sample_5s < 1)//�ɼ���ֵ�ж�
            WGCCON1bits.Sample_5s = 1;
        else if (WGCCON1bits.Sample_5s > 17280)
            WGCCON1bits.Sample_5s = 17280;

        if (WGCCON1bits.Sample_5s > (WGCCON0bits.Send_60s * 12))//����ɼ�ʱ����ڷ���ʱ�䣬��ô���ɼ�ʱ������Ϊ����ʱ��
            WGCCON1bits.Sample_5s = WGCCON0bits.Send_60s * 12;
        WGCPeriodbits.B1 = (WGCCON0bits.Send_60s * 12) / WGCCON1bits.Sample_5s; //����
        WGCPeriodbits.Y2 = (WGCCON0bits.Send_60s * 12) % WGCCON1bits.Sample_5s; //����     
        WGCPeriodbits.CNT = 0; //�������
    }
    //��ȡ��ǰ��ʱ�䣬Ȼ�������ʱ��Ļ����ϼ�������
    while (!RTC_Read_Time(&now_time)) {//�ݴ����
        cnt++;
        //LCD��ʾ���� LED��ʾ���� �������01
        if (cnt > 10)
            return false;
    } //ȷ����ȡ��ǰ��ʱ������һ��
    now_second = mktime(&now_time); //���㵱ǰ��ʱ��
    if (WGCPeriodbits.CNT == WGCPeriodbits.B1) {//�¸�ʱ����Ƿ��͵�ʱ��
        //���ñ���ʱ��Ϊ������ʱ��
        if (!WGCPeriodbits.Y2) {//�������Ϊ0�Ļ�����ôֱ�������´βɼ�ʱ�䣨�ϴ�ʱ���Ѿ����ˣ�����֮�������´μ����ϴ�ʱ��
            now_second += (WGCCON1bits.Sample_5s * 5); //�����´α�����ʱ��
            //��ʼ����GPRS�ϴ�����
            WGCPeriodbits.CNT = 0;
        } else {
            now_second += WGCPeriodbits.Y2 * 5; //�����ϴ�ʱ��
            WGCPeriodbits.CNT += 1;
        }
    } else if (WGCPeriodbits.CNT > WGCPeriodbits.B1) {
        now_second += (WGCCON1bits.Sample_5s * 5); //�����´α�����ʱ��
        //��ʼ����GPRS�ϴ�����
        WGCPeriodbits.CNT = 0;
    } else {
        //���ñ���ʱ��Ϊ�ɼ���ʱ��
        now_second += (WGCCON1bits.Sample_5s * 5); //���ϱ�����ʱ��
        WGCPeriodbits.CNT += 1;
    }
    set_time = gmtime(&now_second); //ת��Ϊʱ��ṹ
    RTC_Set_Alarm(*set_time); //���ñ���ʱ��
    PrintTime();
    return true;
}


