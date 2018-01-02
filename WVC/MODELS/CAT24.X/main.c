/* 
 * File:   main.c
 * Author: Administrator
 *
 * Created on 2017年12月21日, 下午12:54
 */

#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "CAT24C512.h"
#include "mcc_generated_files/mcc.h"
//#include "I2C_S.h"
//#define LED_G LATBbits.LATB12
#define FCY 8000000UL
uint8_t tmp_test[50], cnt;
#define TEST_Read_Byte 0
#define TEST_Write_Byte 0
/*
 * CAT24C512 64K
 */
int main(void) {
    SYSTEM_Initialize();
    I2C_Init();
    CAT24_Init();

    for (cnt = 0; cnt < sizeof (tmp_test); cnt++)
        tmp_test[cnt] = cnt;
#if TEST_Write_Byte
    CAT24_Write_Byte(0x1000, 0x0f);
#else
    CAT24_Write_Page(0x1000, tmp_test, 50);
#endif


    while (1) {
        for (cnt = 0; cnt < sizeof (tmp_test); cnt++)
            tmp_test[cnt] = cnt + 1;
#if TEST_Read_Byte
        CAT24_Read_Byte(0x1000, &tmp_test);
#else
        CAT24_Read_Page(0x1000, tmp_test, 50);
#endif
        Nop();
    }
}


/*
void Timer0_Init(void)
{
    T1CONbits.TON=0;//关闭定时器1
    T1CONbits.TECS=0b10;//使用LPRC 晶振
    TMR1=0;
    PR1=0x7918;//1s定时
    IFS0bits.T1IF=0;
//    IECbits.
//    IPCbits.
}
 */



