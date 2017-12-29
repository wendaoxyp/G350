/* 
 * File:   main.c
 * Author: TURONG62
 *
 * Created on 2016年6月6日, 下午3:04
 * note ：Fosc=8MHz  Fcy=2MHz
 */
#include "AllInclude.h"
/*************************函数申明*****************************/
void NVIC_Configuration(void);
void OSC_Configuration(void);

/*************************主函数*****************************/
int main(void) {
    //    OSC_Configuration();
    //    FM25L64B_Init();
    //    NVIC_Configuration();
    //    TIM1_Configuration();
    //    TIM2_Configuration();
    //    TIM3_Configuration();
    //    TIM4_Configuration();
    //    UART2_Configuration();
    //    GPRS_Init();
    //    RS485_Init();
    //    ICN_Configuration();
    //    Refresh_RTCC_Pulse();
    //    RTC_Configuration();
    ////    ChangeGPRSArg(GPRS_Arg2); //修改GPRS参数
    //    INT_Configuration();
    CLKDIVbits.RCDIV = 0;
    DSWAKEbits.DSMCLR = 1;
    OSCCONbits.SOSCEN = 1;

    //    Start_idle();
    while (1) {
        //        FLagArgbits.SleepExitFlag=0;
        //        while (!FLagArgbits.SleepExitFlag && !FLagArgbits.TestFlag) {
        //            U1MODEbits.WAKE = 1;
        RCONbits.PMSLP = 0;
        TRISB = TRISA = 0x00;
        LATA = LATB = 0;
        LATBbits.LATB3 = 0; // LATBbits.LATB12 = 1;
        TRISAbits.TRISA0 = 1;
//        TRISBbits.TRISB14 = 1;
        LATBbits.LATB14=1;
        IEC0 = IEC1 = IEC2 = IEC3 = IEC4 = IEC5 = 0;
        //        OSCSTL();
        //                while (1)
        //        Sleep();
        Start_Sleep();
        //        Start_idle();
        //        Idle();
        //            Sleep();
        //        }
        //        if (FLagArgbits.SleepExitFlag)
        //            Task_TimeUp();
    }
}

/*************************************
Function: NVIC_Configuration 
Description: 中断配置
Input: 无 
Output: 无
 *************************************/
void NVIC_Configuration(void) {
    INTCON1bits.NSTDIS = 0; //允许嵌套中断
    //    IEC1bits.U2RXIE = 1;
    //    IEC1bits.CNIE=1;//CNI使能中断
    //    IEC0bits.T1IE = 1; //Enable Timer1 interrupts
}

/*************************************
 * Function: NVIC_Configuration 
 * Description: 中断配置
 * Input: 无 
 * Output: 无
 *************************************/
void OSC_Configuration(void) {
    __builtin_write_OSCCONH(0x00);
    __builtin_write_OSCCONL(OSCCON | 0x06);
    OSCCONbits.OSWEN = 1;
    //    OSCCONbits.SOSCDRV = 1;//辅助振荡器驱动强度位
    //    OSCCONbits.SOSCEN = 1;//32 kHz 辅助振荡器 （ SOSC）使能位   
    //    CLKDIVbits.RCDIV = 0b011; //1 MHz （ 8 分频）
}

//void DISI(void) {
//    //    IEC1bits.CNIE = ;//禁止输入
//    //    IEC1bits.
//}
//
//void ENI(void)
//{
//    IEC0bits.IC2IE=0;
//    IEC0bits.
//}




