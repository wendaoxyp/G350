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
    OSC_Configuration();
    //    FM25L64B_Init();
    NVIC_Configuration();
    TIM1_Configuration();
    //    TIM2_Configuration();
    //    TIM3_Configuration();
    //    TIM4_Configuration();
    UART2_Configuration();
    GPRS_Init();
    RS485_Init();
    //    ICN_Configuration();
    //    Refresh_RTCC_Pulse();
    //    RTC_Configuration();
    //    ChangeGPRSArg(GPRS_Arg2); //修改GPRS参数
    //    INT_Configuration();
    char status = -1;
    TRISBbits.TRISB8 = 0;
    while (1) {
        
        LATBbits.LATB8 = 1;
        RS485_CON = 1;
        printf("Start GPRS Test Now!!!\n");
        Delay10ms(1);
        RS485_CON = 0;
        if ((status = GetGPRSBaudRate()) != -1) {
            RS485_CON = 1;
            printf("GPRS BaudRate is %d\n", status);
            printf("[0:1200\t1:2400\t2:4800\t3:9600\t4:19200]\n");
            Delay10ms(1);
            RS485_CON = 0;
        }//继续下一步
        else {//返回错误
            RS485_CON = 1;
            printf("Don't Connect GPRS!!!\n");
            Delay10ms(1);
            RS485_CON = 0;
        }

        if (ChangeGPRSArg(TX_GPRS_Arg1)) {
            RS485_CON = 1;
            printf("Set Arg Test:Finish!!!\n");
            Delay10ms(1);
            RS485_CON = 0;
        }

        if (CopUDPTask()) {//GPRS Test
            status = 0;
            RS485_CON = 1;
            printf("GPRS Online Test: Finish!!!\n");
            Delay10ms(1);
            RS485_CON = 0;
        } else {
            RS485_CON = 1;
            printf("GPRS Online Test: Fail!!!\n");
            Delay10ms(1);
            RS485_CON = 0;
        }
        LATBbits.LATB8 = 0;
        Delay1s(1);
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




