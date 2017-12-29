/* 
 * File:   main.c
 * Author: Administrator
 *
 * Created on 2017��12��21��, ����12:54
 */

#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "mcc_generated_files/mcc.h"
#define LED_G LATBbits.LATB12
void LED_Twinkle(void);
void OpenM6310(void);
void UART1_SendString(uint8_t* tmp, uint8_t);

uint8_t FLAG_T1;
uint8_t AT[] = "AT\n";

/*
 * 
 */
int main(void) {
    //    uint8_t bytes = 0;
    SYSTEM_Initialize();
    //    TRISBbits.TRISB12 = 0;
    //    return (EXIT_SUCCESS);
    UART1_SetRxInterruptHandler(LED_Twinkle);
    IEC0bits.U1TXIE = false;
    //    UART1_SetTxInterruptHandler(UART1_Transmit_ISR);
    //    TMR1_Stop();
    OpenM6310();
    TMR1_Start();
    while (1) {
        //        if (PORTBbits.RB12)
        //            LED_G = 0;

        //        bytes = UART1_WriteBuffer(AT, 4);
        //        UART1_Write(bytes);
        //        LED_G ^= 1;
//        UART1_SendString(AT, 4);
        while (!FLAG_T1);
        //        while(FLAG)
        FLAG_T1 = 0;
//        TMR1 = 0;
        LED_G ^= 1;
    }
}

/*
void Timer0_Init(void)
{
    T1CONbits.TON=0;//�رն�ʱ��1
    T1CONbits.TECS=0b10;//ʹ��LPRC ����
    TMR1=0;
    PR1=0x7918;//1s��ʱ
    IFS0bits.T1IF=0;
//    IECbits.
//    IPCbits.
}
 */
void LED_Twinkle(void) {
    uint8_t tmp[20], bytes;
    LED_G = 1;
    //
    UART1_Receive_ISR();
    bytes = UART1_ReadBuffer(tmp, 10);
    //    UART1_Read();
    //    IFS0bits.U1RXIF = 0;
}

void OpenM6310(void) {//��������ʹ��UART1�Ľ���������Ҫ
    GPRS_EN_SetHigh(); //�򿪵�Դ
    /**********����ģ��**********/
    PWRKEY_SetHigh(); //

    //    TMR1_Start();
    //    while (!IFS0bits.T1IF); //��ʱ3s
    //    IFS0bits.T1IF = 0;
    //    while (!IFS0bits.T1IF);
    //    IFS0bits.T1IF = 0;
    //    while (!IFS0bits.T1IF);
    //    IFS0bits.T1IF = 0;
    //    while (!FLAG_T1);
    //    FLAG_T1 = 0;
    //    while (!FLAG_T1);
    //    FLAG_T1 = 0;
    //    while (!FLAG_T1);
    //    FLAG_T1 = 0;
    //    TMR1_Stop();

    //    PWRKEY_SetLow(); //
}

void UART1_SendString(uint8_t* tmp, uint8_t bytes) {
    uint8_t byte = 0;
    while (byte++ < bytes) {
        U1TXREG = *tmp;
        while (!U1STAbits.TRMT); //�ȴ��������
        tmp += 1;
    }
}

