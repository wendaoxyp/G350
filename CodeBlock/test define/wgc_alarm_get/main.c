#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <stdbool.h>

typedef struct tagWGCCON0BITS {
    uint16_t Send_60s : 11; //����ʱ��,��λ������ 2^15=32768
    uint16_t None : 4; //δ����
} WGCCON0BITS;
volatile WGCCON0BITS WGCCON0bits;

typedef struct tagWGCCON1BITS {
    uint16_t Sample_5s : 15; //�ɼ�ʱ��,��λ���� �̶�5s
    uint16_t None : 1; //δ����
} WGCCON1BITS;
volatile WGCCON1BITS WGCCON1bits;

typedef struct tagWGCPERIODBITS {
    uint64_t B1 : 16; //���ڱ���
    uint64_t Y2 : 16; //��������
    uint64_t CNT : 16; //����ѭ������
    uint64_t RST_FLAG : 1; //���¼������ڱ�־
} WGCPERIODBITS;
 volatile WGCPERIODBITS WGCPeriodbits;



bool WGC_CalcAlarmPeriod(void) {//�����´α���ʱ��
    struct tm now_time, set_time; //ʱ������
    time_t now_second; //��ǰ����
    uint8_t cnt;

    if (WGCPeriodbits.RST_FLAG) {//�����Ҫ�����Ļ�,��ô���¼������ڲ�������֮�������´α�����ʱ��
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
        WGCPeriodbits.B1 = WGCCON1bits.Sample_5s / (WGCCON0bits.Send_60s * 12); //����
        WGCPeriodbits.Y2 = WGCCON1bits.Sample_5s % (WGCCON0bits.Send_60s * 12); //����
        WGCPeriodbits.CNT = 0; //�������
    } else {
        //��ȡ��ǰ��ʱ�䣬Ȼ�������ʱ��Ļ����ϼ�������
        while (!RTC_Read_Time(&now_time)) {//�ݴ����
            cnt++;
            //LCD��ʾ���� LED��ʾ���� �������01
            if (cnt > 10)
                return false;
        } //ȷ����ȡ��ǰ��ʱ������һ��
        now_second = mktime(&now_time); //���㵱ǰ��ʱ��
        if (WGCPeriodbits.CNT >= WGCPeriodbits.B1) {//�¸�ʱ����Ƿ��͵�ʱ��
            //���ñ���ʱ��Ϊ������ʱ��
            now_second += WGCPeriodbits.Y2 * 5; //���ϱ�����ʱ��
            WGCPeriodbits.CNT = 0;
        } else {
            //���ñ���ʱ��Ϊ�ɼ���ʱ��
            now_second += WGCCON1bits.Sample_5s * 5; //���ϱ�����ʱ��
            WGCPeriodbits.CNT += 1;
        }
        set_time = *gmtime(now_second); //ת��Ϊʱ��ṹ
//        RTC_Set_Alarm(set_time); //���ñ���ʱ��
    }
    return true;
}


int main()
{
    printf("Hello world!\n");
    return 0;
}
