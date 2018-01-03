/* 
 * File:   I2C_S.h
 * Author: Administrator
 *
 * Created on December 29, 2017, 3:35 PM
 */

#ifndef I2C_S_H
#define	I2C_S_H

/***************************************************************************
 * Includes
 ***************************************************************************/
#include <xc.h>
//#include <libpic30.h>
#include <stdint.h>
#include "Common.h"
#include <stdbool.h>
/***************************************************************************
 * Definitions
 ***************************************************************************/

#define I2C_DELAY(x) Delay1ms(x)
#define I2C_SCL             LATBbits.LATB6
#define I2C_SDA             LATBbits.LATB5
#define I2C_SCL_DIR         TRISBbits.TRISB6
#define I2C_SDA_DIR         TRISBbits.TRISB5
#define I2C_R_SDA           PORTBbits.RB5
#define I2C_WRITE                       0
#define I2C_READ                        1
//#endif
#define I2C_ERR_NO_ACK                  1
#define I2C_GET_ACK                     2
//需要设置成数字输入

/***************************************************************************
 * Prototypes
 ***************************************************************************/
extern void I2C_Init(void);
extern void I2C_Start(void);
//extern void I2C_Restart(void);
extern void I2C_Stop(void);
extern void I2C_WriteICAdd(const uint8_t add, const uint8_t opreation);
extern void I2C_WriteOpretAdd(const uint8_t add);
extern void I2C_WriteOpretAdd16(const uint16_t add);
extern void I2C_WriteData(const uint8_t dat);
extern uint8_t I2C_ReadData(void);
extern uint8_t I2C_ACK(void);
extern void I2C_NACK(void);


#endif	/* I2C_S_H */

//i2C wirte
/*    LATBbits.LATB4 = 0; //wp=0
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
    //    LATBbits.LATB4 = 1; //wp=1*/

//i2c read
/*
    //LATBbits.LATB4 = 0; //wp=0
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
    I2C_WriteICAdd(I2C_TEST_ADD,  I2C_READ); //读取
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
 */

