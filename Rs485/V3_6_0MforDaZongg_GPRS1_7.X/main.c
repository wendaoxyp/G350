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
static void SystemInit(void);

/*************************������*****************************/
int main(void) {
    SystemInit();

    while (1) {
        while (!FLagArgbits.SleepExitFlag && !FLagArgbits.TestFlag && !FLagArgbits.TestOnlieFlag) {
            OSCChange(0x02); //�л���Ƶ
            TRISAbits.TRISA1 = TRISBbits.TRISB8/* = TRISBbits.TRISB14 */ = TRISBbits.TRISB15 = 0;
            LATAbits.LATA1 = LATAbits.LATA7 = LATBbits.LATB8 /*= LATBbits.LATB14 */ = LATBbits.LATB15 = 0;
            CloseRS485();
//            IEC1bits.INT1IE = 1;
//            IFS1bits.INT1IF = 0;
            Statusbits.staMiot = MIOT_Sleep;
            Sleep();
        }
        if (FLagArgbits.SleepExitFlag) {//����һ�ݷ����Ժ��Ż�����ģʽ           
            Task_TimeUp();
            FLagArgbits.SleepExitFlag = 0;
        } else if (FLagArgbits.TestOnlieFlag) {
            Statusbits.staMiot = MIOT_Test;
            CopUDPTask(TestData, 1, 1);
            FLagArgbits.TestOnlieFlag = 0;
        }
//        u16 tmp = TMR2;
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
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    //    Delay100ms(5);
    //    OSCCONbits.SOSCDRV = 1;//������������ǿ��λ
    //    OSCCONbits.SOSCEN = 1;//32 kHz �������� �� SOSC��ʹ��λ   
    //    CLKDIVbits.RCDIV = 0b011; //1 MHz �� 8 ��Ƶ��
}

static void SystemInit(void) {
    RefreshMiotArg();
    SPI2_Configuration();
    FM25L64B_Init();
    NVIC_Configuration();
    TIM1_Configuration();
    TIM2_Configuration();
    TIM3_Configuration();
    TIM4_Configuration();
    UART2_Configuration();
    GPRS_Init();
    RS485_Init();
    ICN_Configuration();
    Refresh_RTCC();
    Refresh_Pulse();
    RTC_Configuration();
    INT_Configuration();
    ADC_Init();
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

