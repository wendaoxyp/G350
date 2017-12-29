//#include "p24FV32KA301.h"
#include "type.h"
#include "user.h"

//vu32 gPulseCount = 0;

void IC_Configuration(void) {
    //    IC2CON1bits.ICBNE = 0;
    IC2CON2bits.SYNCSEL = 0b00000; //10100 = 输入捕捉 2 无同步
    IC2CON1bits.ICSIDL = 0; //0 = 输入捕捉模块将在 CPU 空闲模式下继续工作
    IC2CON1bits.IC2TSEL = 0b100; //100 = TIMER1    9.26 111
    IC2CON1bits.ICI = 0; //每次捕捉事件中断一次
    IC2CON2bits.ICTRIG = 0; //使 ICx 与 SYNCSELx 位指定的源同步
    IC2CON2bits.TRIGSTAT = 1; //定时器源未被触发，保持清零状态
    IC2BUF = 0;
    IC2TMR = 0;
    IC2CON1bits.ICM = 0b111; //中断模式 简单捕捉模式：每个上升沿捕捉一次， 
    IPC1bits.IC2IP = 6; // Setup Input Capture 1 interrupt for desired priority
    // level (this example assigns level 1 priority)
    IFS0bits.IC2IF = 0; // Clear the IC1 interrupt status flag
    IEC0bits.IC2IE = 1; // Enable IC1 interrupts
    S1_IN;
    //    IC2CON1bits.ICBNE = 1;
    //ICI<1:0> 位不控制此模式下中断的产生
    //    IC1CON2 = 0x00A4; // Turn on Input Capture 1 Module 
    //    T1CONbits.TON=1;
}


