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
static void SystemInit(void);

/*************************主函数*****************************/
int main(void) {
    SystemInit();
    //    while (1); //测试看门狗是否工作 000000021 ok
    while (1) {
        while (!FLagArgbits.SleepExitFlag && !FLagArgbits.TestFlag && !FLagArgbits.TestOnlieFlag) {
            OSCChange(0x02); //切换主频  导致看门狗技术清零 看门狗时间131s
            Statusbits.staMiot = MIOT_Sleep;
            TRISAbits.TRISA1 = TRISBbits.TRISB8/* = TRISBbits.TRISB14 */ = TRISBbits.TRISB15 = 0;
            LATAbits.LATA1 = LATAbits.LATA7 = LATBbits.LATB8 /*= LATBbits.LATB14 */ = LATBbits.LATB15 = 0;
            CloseRS485();
            IEC1bits.INT1IE = 1;
            Sleep();
        }
        if (FLagArgbits.SleepExitFlag) {//避免一份分钟以后会才会休眠模式  
            //            Statusbits.staMiot = MIOT_GPRS;
            Task_TimeUp();
            FLagArgbits.SleepExitFlag = 0;
        } else if (FLagArgbits.TestOnlieFlag) {
            Statusbits.staGPRS = All_Right;//避免一开始状态就是退出导致无法使用测试功能
            Statusbits.staMiot = MIOT_Test;
            FLagArgbits.TestGetDataFlag = 1; //获取报警数据
            Delay1s(1); //等待上位机通讯完成
            StartTime4(); //开始通过定时器4获取数据
            IFS1bits.T4IF = 1; //开启定时器4的中断
            while (IFS1bits.T4IF)
                StartTime4(); //等待获取采集数据
            CopUDPTask(TestData, 1, 1);
            FLagArgbits.TestOnlieFlag = 0;
        }
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

static void SystemInit(void) {
    SPI2_Configuration();
    FM25L64B_Init();
    OutputMiotArg(); //注意顺序
    NVIC_Configuration();
    //    TIM1_Configuration();
    TIM2_Configuration();
    TIM3_Configuration();
    TIM4_Configuration();
    UART2_Configuration();
    GPRS_Init();
    RS485_Init();
    //    ICN_Configuration();
    Refresh_RTCC_Pulse();
    RTC_Configuration();
    INT_Configuration();
    ADC_Init();
    TRISAbits.TRISA2 = 0;
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

