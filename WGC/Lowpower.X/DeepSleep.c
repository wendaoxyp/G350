/* 
 * File:   DeepSleep.c
 * Author: TURONG62
 *
 * Created on 2016年7月2日, 下午2:00
 */

#include "user.h"
//#include "p24FV32KA301.h"

void Start_Sleep(void) {
    //    asm("disi #4");
    //    asm("bset DSCON, #15");
    //    asm("nop");
    //    asm("nop");
    //    asm("nop");
    //    asm("pwrsav #0");
    //    Sleep();
    //    asm("PWRSV #SLEEP_MODE");
    //    asm("bset DSCON, #15");
    //    Nop();
    //    Nop();
    //    Nop();
    //    asm("pwrsav #0");


    //Disable Interrupts For 5 instructions

    asm volatile("disi #5");
    //Issue Unlock Sequence
    asm("mov #0x55, W0");
    asm("mov W0, NVMKEY");
    asm("mov #0xAA, W1");
    asm("mov W1, NVMKEY");
    asm("bset DSCON,#15");
    //    Nop();
    //    Nop();
    //    Nop();
    //    asm("nop");
    //    asm("nop");
    asm("nop");
    asm("pwrsav #0");
    //    Sleep
    //    asm("pwrsav #0");
}

void Start_nod(void)//进入打盹模式
{

    CLKDIVbits.DOZEN = 1;
    //    CLKDIVbits.DOZE//1:1 是默认设置
    //关闭部分时钟源
    PMD1bits.T2MD = 1;
    PMD1bits.T3MD = 1;
    PMD1bits.SPI1MD = 1;
    //    PMD1bits.U1MD=1;
    PMD1bits.U2MD = 1;
    //    PMD2bits.IC2MD=0;

}

void Start_idle(void) {
    Idle();
    //关闭部分时钟源
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

void OSCSTL(void) {
    //Place the new oscillator selection in W0
    //OSCCONH (high byte) Unlock Sequence
    __builtin_write_OSCCONH(0x65);
    //;Set new oscillator selection
    //    asm("MOV.b WREG, OSCCONH");
    //;OSCCONL (low byte) unlock sequence
    __builtin_write_OSCCONL(0x65);
    //;Start oscillator switch operation
    OSCCONbits.OSWEN = 1; //asm("BSET OSCCON,#0");
    Delay100ms(5);
}


