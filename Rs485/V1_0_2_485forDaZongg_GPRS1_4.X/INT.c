/* 
 * File:   INT.c
 * Author: ASUS
 *
 * Created on 2016年12月23日, 下午3:18
 */
#include "user.h"

void INT_Configuration(void) {//用于唤醒485通讯
    ANSBbits.ANSB14 = 0; //数字
    TRISBbits.TRISB14 = 1; //输入
    IFS1bits.INT1IF = 0;
    INTCON2bits.INT1EP = 1; //1; //下降沿中断
    IPC5bits.INT1IP = 5;
    IEC1bits.INT1IE = 1; //开中断
    //    IFS1bits.INT1IF = 0;
}

//void INT_Start(void) {
//
//}

