#include "WCG.h"



volatile WGCTIME0BITS WGCTIME0bits;
volatile WGCTIME1BITS WGCTIME1bits;
volatile WGCTIME2BITS WGCTIME2bits;
volatile WGCCON0BITS WGCCON0bits;
volatile WGCCON1BITS WGCCON1bits;
volatile WGCCON2BITS WGCCON2bits;
volatile WGCIPBITS WGCIPbits;
volatile uint16_t WGCPORT;

void WGC_Init(void) {
    WGCIPbits.IP3 = 139; //����IP��ַ
    WGCIPbits.IP2 = 196;
    WGCIPbits.IP1 = 122;
    WGCIPbits.IP0 = 159;
    WGCPORT = 5080; //���ö˿ں�
    WGCCON0bits.Send_Second = 0x01; //����5��
    WGCCON1bits.Sample_Minute = 0x02; //�ɼ�2����
    WGCCON2bits.E41_Is_Use_For_Send_Data = 0; //�ر�E41
    WGCCON2bits.E41_Is_Use_For_Set_Arg = 0; //�ر�E41
    WGCCON2bits.WGC_ID = 0x03; //ID��
}

void WGC_SetNextAlarmTime(void) {//�����´α���ʱ��
    uint16_t beishu;
    SetVaildData((uint16_t*) (& WGCCON0bits.Send_Second), 17280, 1);
    SetVaildData((uint16_t*) (& WGCCON1bits.Sample_Minute), 1440, 3);
    beishu = (WGCCON1bits.Sample_Minute * 12 / WGCCON0bits.Send_Second); //����

    if (beishu < 1) {
        //������ʱ������Ϊ�ɼ�ʱ��
        WGCCON1bits.Sample_Minute = WGCCON0bits.Send_Second * 12;
        SetVaildData((uint16_t*) (& WGCCON1bits.Sample_Minute), 1440, 3);
    }
    yushu = (WGCCON1bits.Sample_Minute * 12 % WGCCON0bits.Send_Second); //����


}


