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
#include "I2C_S.h"
//#define LED_G LATBbits.LATB12
#define FCY 8000000UL

/*
 * CAT24C512 64K
 */
int main(void) {
    SYSTEM_Initialize();
    uint8_t I2C_Test_tmp = 0xf0, cnt = 0;
    //    return (EXIT_SUCCESS);
    TRISBbits.TRISB4 = 0;
    LATBbits.LATB4 = 0; //wp=0
    I2C_Init();
    //I2C write 0x0000 0xaa
    Delay1ms(1);
    I2C_Start();
    I2C_WriteICAdd(I2C_TEST_ADD, I2C_WRITE);
    if (I2C_ACK() == I2C_ERR_NO_ACK)
        Nop(); // continue; //send ERR
    I2C_WriteOpretAdd(0x00); //高位地址
    if (I2C_ACK() == I2C_ERR_NO_ACK)
        Nop(); //continue; //send ERR
    I2C_WriteOpretAdd(0x01); //低位地址
    if (I2C_ACK() == I2C_ERR_NO_ACK)
        Nop(); //continue; //send ERR
    I2C_WriteData(0xaa); //写0xaa数据
    if (I2C_ACK() == I2C_ERR_NO_ACK)
        Nop(); // continue; //send ERR
    I2C_Stop();
    //    LATBbits.LATB4 = 1; //wp=1
    //i2c write end
    Nop();
    while (1) {
        //I2C read start
        Nop();
        //        LATBbits.LATB4 = 0; //wp=0
        Delay1ms(1);
        I2C_Start();
        cnt = 1;
        cnt += 1;
        I2C_WriteICAdd(I2C_TEST_ADD, I2C_WRITE);
        cnt += 1;
        if (I2C_ACK() == I2C_ERR_NO_ACK)
            continue; //send ERR
        cnt += 1;
        I2C_WriteOpretAdd(0x00); //高位地址
        cnt += 1;
        if (I2C_ACK() == I2C_ERR_NO_ACK)
            continue; //send ERR
        cnt += 1;
        I2C_WriteOpretAdd(0x00); //低位地址
        cnt += 1;
        if (I2C_ACK() == I2C_ERR_NO_ACK)
            continue; //send ERR
        cnt += 1;
        I2C_Start(); //restatt
        cnt += 1;
        I2C_WriteICAdd(I2C_TEST_ADD, /*I2C_WRITE); //*/ I2C_READ); //读取
        cnt += 1; //10
        if (I2C_ACK() == I2C_ERR_NO_ACK)
            continue; //send ERR
        cnt += 1;
        I2C_Test_tmp = I2C_ReadData(); //
        cnt += 1;
        I2C_NACK();
        cnt += 1;
        I2C_Stop();
        cnt += 1;
        //        cnt+=1;
        //i2C read end 
        Nop();
        Delay100ms(1);
        //        LATBbits.LATB4 = 1; //wp=1
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



