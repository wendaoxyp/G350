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

/*
 * 
 */
int main(void) {
    SYSTEM_Initialize();
    //    TRISBbits.TRISB12 = 0;
    //    return (EXIT_SUCCESS);
    while (1) {
        LED_G ^= 1;
        while (!IFS0bits.T1IF);
        IFS0bits.T1IF = 0;
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



