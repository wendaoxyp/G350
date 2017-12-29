/* 
 * File:   SPI.h
 * Author: TURONG62
 *
 * Created on 2016年6月1日, 下午3:52
 */
#include "user.h"
#ifndef SPI_H
#define	SPI_H

#define WREN 0x06//0b00000110//Set Write Enable Latch
#define WRDI 0x04//0b00000100//Write Disable
#define RDSR 0x05//0b00000101//Read Status Register 
#define WRSR 0x01//0b00000001//Write Status Register  will clear WEL
#define READ 0x03//0b00000011//Read Memory Data 
#define WRITE 0x02//0b00000010//Write Memory Data

//#include"type.h"
extern void FM25L64B_Write(u16 add, u8* dat, u8 bytes);
extern void FM25L64B_Read(u16 add, u8 *dat, u8 bytes);
//extern void FROM_WriteDPNum(void);
extern void FROM_EN(void);
extern void FROM_WRSR(void);
extern void FROM_Arg_Setting(void);
extern void SPI2_Configuration(void);
//void SPI1_Configuration(void);
//extern void SPI_Read(u8*dat);
//extern void SPI_Write(u8 dat);
//void delay_nop(u8 count);
//void SPI1_Read1(u8* dat);

#endif	/* SPI_H */

