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
#include "mcc_generated_files/mcc.h"
//#include "I2C_S.h"
#include "PCF8583.h"
//#define LED_G LATBbits.LATB12
#define FCY 8000000UL
uint8_t read_time[6];
uint8_t setarg;

/*
 * CAT24C512 64K
 */
int main(void) {
    SYSTEM_Initialize();
    I2C_Init();
    PCF8583_Init();

    TRISBbits.TRISB12 = 0;
    LATBbits.LATB12 = 1;
    Delay1s(1);
    LATBbits.LATB12 = 0;
    while (1) {
        //        PCF_Read_Time(read_time);
        Nop();
//        PCF8583_Read_S(PCF_CON_STA, &setarg, 1); //获取寄存器00的数据
//        PCF8583_Read_S(PCF_CON_ALARM, &setarg, 1); //获取寄存器00的数据
        if (!PORTBbits.RB7) {
            //清楚Alram_Flag标志位
            PCF8583_Read_S(PCF_CON_STA, &setarg, 1); //获取寄存器00的数据
            setarg &= ~PCF_D0_AlARM_FLAG; //清楚报警标志位
            setarg |= PCF_D0_ALARM_EN; //重新开启报警
            PCF8583_Write(PCF_CON_STA, &setarg, 1); //
            PCF_Read_Time(read_time);
            PCF_Set_Alarm(read_time, 30);
            LATBbits.LATB12 ^= 1;
        }
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



