/* 
 * File:   DeepSleep.c
 * Author: TURONG62
 *
 * Created on 2016��7��2��, ����2:00
 */

#include "user.h"
//#include "p24FV32KA301.h"

void Start_Sleep(void) {
    //    DSCONbits.DSEN=1;
    //    Sleep();//#define Sleep() {__asm__ volatile ("pwrsav #0");}

    asm("bset DSCON, #15");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("pwrsav #0");

    //    asm("disi #4");
    //    asm("bset DSCON, #15");
    //    asm("nop");
    //    asm("nop");
    //    asm("btss INTTREG, #15");
    //    asm("pwrsav #0");

}

void Start_nod(void)//�������ģʽ
{
    CLKDIVbits.DOZEN = 1;
    //    CLKDIVbits.DOZE//1:1 ��Ĭ������
    //�رղ���ʱ��Դ
    PMD1bits.T2MD = 1;
    PMD1bits.T3MD = 1;
    PMD1bits.SPI1MD = 1;
    //    PMD1bits.U1MD=1;
    PMD1bits.U2MD = 1;
    //    PMD2bits.IC2MD=0;

}

void Start_idle(void) {
    Idle();
    //�رղ���ʱ��Դ
    //    PMD1bits.T2MD=1;
    //    PMD1bits.T3MD=1;
    PMD1bits.SPI1MD = 1;
    PMD1bits.ADC1MD = 1;
    PMD1bits.I2C1MD = 1;
    PMD1bits.SPI2MD = 1;
    PMD1bits.T4MD = 1;
    PMD1bits.T5MD = 1;
    //    PMD1bits.T1MD=1;//?
    PMD1bits.U1MD = 1; //?
    //    PMD2bits.IC2MD=1;//?    
    //    PMD3bits.RTCCMD=1; 
    //    PMD1bits.U2MD=1;
    PMD2bits.IC1MD = 1;
    PMD2bits.IC3MD = 1;
    PMD2bits.OC1MD = 1;
    PMD2bits.OC2MD = 1;
    PMD2bits.OC3MD = 1;
    PMD3bits.CRCPMD = 1;
    PMD3bits.I2C2MD = 1;
    PMD3bits.CMPMD = 1;
}

void OSCChange(u8 NOSCH) {
    __builtin_write_OSCCONH(NOSCH);
    __builtin_write_OSCCONL(OSCCON | 0x06);
    OSCCONbits.OSWEN = 1;
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
}

//u8 GetNowOSC(void) {
//    return (u8) (OSCCON >> 12);
//}


