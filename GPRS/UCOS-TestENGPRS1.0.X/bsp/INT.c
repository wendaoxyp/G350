/* 
 * File:   INT.c
 * Author: ASUS
 *
 * Created on 2016��12��23��, ����3:18
 */
//#include "user.h"
#include "xc.h"

void INT_Configuration(void) {
    ANSBbits.ANSB14 = 0; //����
    TRISBbits.TRISB14 = 1; //����
    IFS1bits.INT1IF = 0;
    IFS0bits.INT0IF = 0;
    INTCON2bits.INT1EP = 1; //�½����ж�
    IPC5bits.INT1IP = 6;
    IEC1bits.INT1IE = 1; //���ж�
}



