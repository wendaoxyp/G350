#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
typedef struct tagWGCCON0BITS {
    uint16_t Send_60s : 11; //����ʱ��,��λ������ 2^15=32768
    uint16_t None : 5; //δ����
} WGCCON0BITS;
extern volatile WGCCON0BITS WGCCON0bits;

typedef struct tagWGCCON1BITS {
    uint16_t Sample_5s : 15; //�ɼ�ʱ��,��λ���� �̶�5s
    uint16_t None : 1; //δ����
} WGCCON1BITS;
extern volatile WGCCON1BITS WGCCON1bits;

typedef struct tagWGCCON2BITS {
    uint16_t WGC_ID : 8; //WGC��ID�� 0-255
    uint16_t E41_Is_Use_For_Send_Data : 1; //�̳������Ƿ�������������
    uint16_t E41_Is_Use_For_Set_Arg : 1; //�̳������Ƿ������޸Ĳ���
    uint16_t Alarm_RST_FLAG : 1; //���¼������ڱ�־
    uint16_t Period_FLAG : 1; //rtcc��־λ
    uint16_t Sample_FLAG : 1; //������־λ
    uint16_t Send_FLAG : 1; //���ͱ�־λ
    uint16_t SET_TIME_TEST_FLAG : 1; //RTCC��ʱʱ�����
    uint16_t PC_Cop_FLAG : 1; //�û�ͨѶ��־λ
} WGCCON2BITS;
extern volatile WGCCON2BITS WGCCON2bits;
typedef struct tagWGCCON3BITS {
    uint32_t delay : 17; //0-131071s;
    uint32_t count : 15; //0-32767 �� �ɼ�ʱ�����Ϊ17280 ����ʱ�����Ϊ480 һ��֮��
} WGCCON3BITS;
//extern volatile WGCCON3BITS WGCCON3bits;

typedef struct tagWGCCON4BITS {
    uint32_t delay : 17; //0-131071s;
    uint32_t count : 15; //0-32767 �� �ɼ�ʱ�����Ϊ17280 ����ʱ�����Ϊ480 һ��֮��
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
        WGCCON3bits.delay = 10; //�ɼ�ʱ��
        WGCCON3bits.count = 6; //����ɼ��Ĵ���
        WGCCON4bits.delay = 0; //�����ϴ���ʱ�� ��ʱ��Ϊ12*3+3=39s
        WGCCON4bits.count = 0; //�ϴ��ۼƴ�������
#else
        WGCCON3bits.delay = WGCCON1bits.Sample_5s * 5; //�ɼ�ʱ��
        WGCCON3bits.count = WGCCON0bits.Send_60s * 12 / WGCCON1bits.Sample_5s; //����ɼ��Ĵ���
        WGCCON4bits.delay = (WGCCON0bits.Send_60s * 12 % WGCCON1bits.Sample_5s)*5; //�����ϴ���ʱ��
        WGCCON4bits.count = 0; //�ϴ��ۼƴ�������
#endif
        last_alarm_time = 0;
        alarm_time = WGCCON3bits.delay; //���ص�һ�βɼ�ʱ��
    } else {
        if (cnt < WGCCON3bits.count) {//���������ʱ�仹û�е�����ô��������ʱ����Ϊ�ɼ���ʱ��
            WGCCON2bits.Sample_FLAG = 1;
            StartTMR2();
            IFS0bits.T2IF = 1;
            cnt += 1;
#ifdef DEBUG_RTCC_TIME
            samplecount = cnt;
#endif
            alarm_time = WGCCON3bits.delay - last_alarm_time;
            last_alarm_time = alarm_time;
        } else {//����ɼ������͹涨��ʱ�������ͬ����ô��Ҫ�ж��Ƿ�ɼ�ʱ���Ƿ����ϴ�ʱ���������
            if (WGCCON4bits.delay) {//�������ʱ��պ��ǲɼ�ʱ����������Ļ��������ƼĴ���2��־Ϊ��1�������´ζ�ʱʱ��
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
                WGCCON4bits.count += 1; //���ߴ�����1
                alarm_time = WGCCON4bits.delay;
                last_alarm_time = alarm_time;
            } else {//��֮������ʱʱ������Ϊ������ʱ��������
#ifdef DEBUG_RTCC_TIME
                samplecount = cnt + 1;
#endif
                WGCCON2bits.Sample_FLAG = WGCCON2bits.Send_FLAG = 1;
                StartTMR2();
                IFS0bits.T2IF = 1;
                cnt = 0; //����ڲ�����
                return WGCCON3bits.delay;
            }
        }
    }
    if (!last_alarm_time) {//������һ�����õı���ʱ��Ϊ0�Ļ�����ôֱ��
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
