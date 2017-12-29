/* 
 * File:   main.c
 * Author: TURONG62
 *
 * Created on 2016年6月6日, 下午3:04
 * note ：Fosc=8MHz  Fcy=2MHz
 */
#include "AllInclude.h"
#include "stdint.h"
/*************************函数申明*****************************/
void NVIC_Configuration(void);
void OSC_Configuration(void);

/*************************主函数*****************************/
int main(void) {/*
    OSC_Configuration();*/
    FM25L64B_Init(); //进入低功耗
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
//    INT_Configuration();
//    ADC_Init();
    //     RS485_CON = 1; //发送
    uint8_t tmp;
    while (1) {
           FM25L64B_Read(0x0000,&tmp,1);
           Delay1s(1);
//        OSCChange(0x02); //
//        while (!FLagArgbits.SleepExitFlag && !FLagArgbits.TestFlag && !FLagArgbits.TestOnlieFlag) {
//            //TRISA=TRISB=0;   
//            //LATA=LATB=0; 
//            U1MODEbits.WAKE = 1;
//            //AD1CON3bits.ADRC = 1;
//            //LK设置为输入
//            Sleep();
//        }
//        if (FLagArgbits.SleepExitFlag) {//避免一份分钟以后会才会休眠模式
//            FLagArgbits.SleepExitFlag = 0;
//            Task_TimeUp();
//        } else if (FLagArgbits.TestOnlieFlag) {
//            CopUDPTask(TestData, 1, 2);
//            FLagArgbits.TestOnlieFlag = 0;
//        }
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
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    //    Delay100ms(5);
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




