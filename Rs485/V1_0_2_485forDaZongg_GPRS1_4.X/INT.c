/* 
 * File:   INT.c
 * Author: ASUS
 *
 * Created on 2016��12��23��, ����3:18
 */
#include "user.h"

void INT_Configuration(void) {//���ڻ���485ͨѶ
    ANSBbits.ANSB14 = 0; //����
    TRISBbits.TRISB14 = 1; //����
    IFS1bits.INT1IF = 0;
    INTCON2bits.INT1EP = 1; //1; //�½����ж�
    IPC5bits.INT1IP = 5;
    IEC1bits.INT1IE = 1; //���ж�
    //    IFS1bits.INT1IF = 0;
}

//void INT_Start(void) {
//
//}

