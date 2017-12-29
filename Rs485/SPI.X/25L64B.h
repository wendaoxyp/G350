/* 
 * File:   25L04B.h
 * Author: TURONG62
 *
 * Created on 2016年6月7日, 下午3:35
 */

#ifndef _25L04B_H
#define	_25L04B_H

#define WREN 0x06//0b00000110//Set Write Enable Latch
#define WRDI 0x04//0b00000100//Write Disable
#define RDSR 0x05//0b00000101//Read Status Register 
#define WRSR 0x01//0b00000001//Write Status Register  will clear WEL
#define READ 0x03//0b00000011//Read Memory Data 
#define WRITE 0x02//0b00000010//Write Memory Data
//#define ADD9 0x08//0b00001000//Address 9bits


extern void FM25L64B_Init(void);
//extern void BufferWrite_SPI(u8* dat);
//extern bool BufferRead_SPI(u8 *data);
//extern void FROM_ReadN(u8*dat);
extern void FM25L64B_Read(u16 add, u8 *dat, u8 bytes);
extern void FM25L64B_Write(u16 add, u8* dat, u8 bytes);
//extern void PostSPIWriteFlag(u16 add, u8* dat, u8 bytes);
//extern void PostSPIReadFlag(u16 add, u8* dat, u8 bytes);
//extern void FROM_WriteDPNum(void);
extern void FROM_EN(void);
extern void FROM_WRSR(void);
extern void FROM_Arg_Setting(void);


#endif	/* 25L04B_H */

