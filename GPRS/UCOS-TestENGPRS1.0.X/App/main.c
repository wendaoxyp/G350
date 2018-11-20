/* 
 * File:   main.c
 * Author: TURONG62
 *
 * Created on 2016��6��6��, ����3:04
 * note ��Fosc=8MHz  Fcy=2MHz
 */
#include "AllInclude.h"
/*************************��������*****************************/
void NVIC_Configuration(void);
void OSC_Configuration(void);

/*************************������*****************************/
int main(void) {
    OSC_Configuration();
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
////    ChangeGPRSArg(GPRS_Arg2); //�޸�GPRS����
//    INT_Configuration();
    while (1) {
//        FLagArgbits.SleepExitFlag=0;
//        while (!FLagArgbits.SleepExitFlag && !FLagArgbits.TestFlag) {
//            U1MODEbits.WAKE = 1;
//            Sleep();
//        }
//        GPRS_IS_Ready();
//            Task_TimeUp();
    }
}

/*************************************
Function: NVIC_Configuration 
Description: �ж�����
Input: �� 
Output: ��
 *************************************/
void NVIC_Configuration(void) {
    INTCON1bits.NSTDIS = 0; //����Ƕ���ж�
    //    IEC1bits.U2RXIE = 1;
    //    IEC1bits.CNIE=1;//CNIʹ���ж�
    //    IEC0bits.T1IE = 1; //Enable Timer1 interrupts
}

/*************************************
 * Function: NVIC_Configuration 
 * Description: �ж�����
 * Input: �� 
 * Output: ��
 *************************************/
void OSC_Configuration(void) {
    __builtin_write_OSCCONH(0x00);
    __builtin_write_OSCCONL(OSCCON | 0x06);
    OSCCONbits.OSWEN = 1;
    //    OSCCONbits.SOSCDRV = 1;//������������ǿ��λ
    //    OSCCONbits.SOSCEN = 1;//32 kHz �������� �� SOSC��ʹ��λ   
    //    CLKDIVbits.RCDIV = 0b011; //1 MHz �� 8 ��Ƶ��
}

//void DISI(void) {
//    //    IEC1bits.CNIE = ;//��ֹ����
//    //    IEC1bits.
//}
//
//void ENI(void)
//{
//    IEC0bits.IC2IE=0;
//    IEC0bits.
//}



