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
    WGCIPbits.IP3 = 139; //设置IP地址
    WGCIPbits.IP2 = 196;
    WGCIPbits.IP1 = 122;
    WGCIPbits.IP0 = 159;
    WGCPORT = 5080; //设置端口号
    WGCCON0bits.Send_Second = 0x01; //发送5秒
    WGCCON1bits.Sample_Minute = 0x02; //采集2分钟
    WGCCON2bits.E41_Is_Use_For_Send_Data = 0; //关闭E41
    WGCCON2bits.E41_Is_Use_For_Set_Arg = 0; //关闭E41
    WGCCON2bits.WGC_ID = 0x03; //ID号
}

void WGC_SetNextAlarmTime(void) {//设置下次报警时间
    uint16_t beishu;
    SetVaildData((uint16_t*) (& WGCCON0bits.Send_Second), 17280, 1);
    SetVaildData((uint16_t*) (& WGCCON1bits.Sample_Minute), 1440, 3);
    beishu = (WGCCON1bits.Sample_Minute * 12 / WGCCON0bits.Send_Second); //倍数

    if (beishu < 1) {
        //将发送时间设置为采集时间
        WGCCON1bits.Sample_Minute = WGCCON0bits.Send_Second * 12;
        SetVaildData((uint16_t*) (& WGCCON1bits.Sample_Minute), 1440, 3);
    }
    yushu = (WGCCON1bits.Sample_Minute * 12 % WGCCON0bits.Send_Second); //余数


}


