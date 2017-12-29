#include "SPI.h"
#include "user.h"
#include "25L64B.h"
//#include "p24FV32KA301.h"
#include "UART.h"
#include "TIM.h"
#include "P-Miot1601.h"
#include "Miot1601.h"

u16 bufferWptr_spi = 0;
u16 bufferRptr_spi = 0;
u8 gOffsetAdd = 0; //16位数据包

//struct SPI2_Arg SPI2Argbits;

static void SPI_Read(u8 *dat);
static void SPI_Write(u8 dat);
//static void Delay_Nop(u8 count);

//const u16 DataPacke_Add[DataPacketNum] = {
//    0x0000, 0x002A, 0x0054, 0x007E, 0x00A8, 0x00D2,
//    0x00FC, 0x0126, 0x0150, 0x017A, 0x01A4, 0x01CE,
//    
//};
//static const u16 OverFlag_Add=0x1FE;
//static const u16 DataPacket_ID = 0x1FF;
//static void FROMFindOffsetAdd(void);

/*************************************
Function: FM25L64B_Init 
Description: FM25L64B初始化
Input: 无
Output: 无
 *************************************/
void FM25L64B_Init(void) {
    u8 tmp[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    SDO2_TRIS = 0; //单片机输出
    SDI2_TRIS = 1; //单片机输入
    SCK2_TRIS = 0;
    SS2_TRIS = 0;
    ANSBbits.ANSB14 = 0; //数字输入
    CNPD1bits.CN12PDE = 1;
    SS2 = 1; //输出高电平
    SCK2 = 0;
    SDO2 = 0;

    //无写保护区
    FROM_WRSR(); //02
    //获取数据地址偏移量
    while (BAT_DEC != 1); //等待供电  添加提示
    FM25L64B_Read(DataPacket_ID, &gOffsetAdd, 1);

    FM25L64B_Read(BOR_Pulse, tmp, 4);
    DataReverse(tmp, 4); //将数据反转 00 00 FF 01  <==> 01 FF 00 00
    Register2Write(tmp, mi_arg_add[mi_ofst], 4);
    FM25L64B_Read(RST_Time, tmp, 7);
    if (tmp[0] == 0x20)
        Register2Write(tmp, mi_arg_add[mi_year], 7); //写入Regster2中 调试   
}

/*************************************
Function: SPI_Write 
Description: 软件SPI写数据指令
Input: SPI通讯数据
Output: 无
 *************************************/
static void SPI_Write(u8 dat) {
    char count;
    for (count = 7; count >= 0; count--) {
        SDO2 = (dat >> count)&0x01;
        Delay_Nop(1);
        SCK2 = 1;
        Delay_Nop(1); //9.22 3
        SCK2 = 0;
        //        Delay_Nop(1);
    }
    SDO2 = 0;
}

/*************************************
Function: SPI_Read 
Description: 软件SPI的读取数据指令
Input: 无
Output: 从机发送过来的数据
 *************************************/
static void SPI_Read(u8 *dat) {
    char count = 0;
    *dat = 0x00; //清除原始数据
    for (count = 7; count >= 0; count--) {
        Delay_Nop(1);
        SCK2 = 1;
        *dat |= (SDI2 << count);
        Delay_Nop(1);
        SCK2 = 0;
    }
}

/*************************************
Function: FM25L64B_Write 
Description: FM25L64B通讯写数据
Input: 地址，第9位地址bit8，发送的数据
Output: 无
 *************************************/
void FM25L64B_Write(u16 add, u8* dat, u8 bytes) {
    u8 count = 0;
    u8 addL = (u8) (add & 0x00FF);
    u8 addH = (u8) ((add >> 8) & 0x00FF);

    FROM_EN();
    SS2 = 0;
    Delay_Nop(1);
    SPI_Write(WRITE);
    Delay_Nop(1);
    SPI_Write(addH);
    Delay_Nop(1);
    SPI_Write(addL);
    Delay_Nop(1);
    //    Delay_Nop(1);//9.22
    while (count < bytes) {
        SPI_Write(*(dat + count));
        Delay_Nop(1);
        count++;
    }
    SS2 = 1;
}

/*************************************
Function: FM25L64B_Read 
Description: FM25L64B通讯读指令
Input: 地址1，接收的数据,字节数
Output: 无
 *************************************/
void FM25L64B_Read(u16 add, u8 *dat, u8 bytes) {
    //    disi
    u8 count = 0;
    u8 addL = (u8) (add & 0x00FF);
    u8 addH = (u8) ((add >> 8) & 0x00FF);

    FROM_EN();
    SS2 = 0;
    Delay_Nop(1);
    SPI_Write(READ);
    Delay_Nop(1);
    SPI_Write(addH); //0x03
    Delay_Nop(1);
    SPI_Write(addL); //0x07
    Delay_Nop(1);
    while (count < bytes) {//0xa1
        SPI_Read(dat + count);
        Delay_Nop(1);
        count++;
    }
    SS2 = 1;
}

/*************************************
Function:  FROM_WriteDPNum
Description: 更新数据包序号
Input: 无
Output: 无
 *************************************/
void FROM_WriteDPNum(void) {
    FM25L64B_Write(DataPacket_ID, &gOffsetAdd, 1); //写入数据包序号
    gOffsetAdd += 1; //数据包序号+1  
    gOffsetAdd = gOffsetAdd % DataPacketNum; //一个环数据为252 12*21
}

/*************************************
Function:  FROM_EN
Description: 使能写
Input: 无
Output: 无
 *************************************/
void FROM_EN(void) {
    SS2 = 0;
    Delay_Nop(1);
    SPI_Write(WREN);
    Delay_Nop(1);
    SS2 = 1;
    Delay_Nop(1);
}

/*************************************
Function:  FROM_WRSR
Description: 写保护区
Input: 无
Output: 无
 *************************************/
void FROM_WRSR(void) {
    SS2 = 0;
    Delay_Nop(1);
    SPI_Write(WRSR);
    Delay_Nop(1);
    SPI_Write(0x00);
    Delay_Nop(1);
    SS2 = 1;
    Delay_Nop(1);
}

//void PostSPIWriteFlag(u16 add, u8* dat, u8 bytes) {
//    while ( FLagArgbits.SPIWriteFlag); //等待读操作或是上次写操作完成 
//    FLagArgbits.SPIWriteFlag = 1;
//    SPI2Argbits.add1 = add;
//    SPI2Argbits.dat1 = dat;
//    SPI2Argbits.bytes1 = bytes;
//    
//    while (!FLagArgbits.SPIWriteFinishFlag); //等待发送完成
//    FLagArgbits.SPIWriteFlag = 0;
//    FLagArgbits.SPIWriteFinishFlag = 0;
//}

//void PostSPIReadFlag(u16 add, u8* dat, u8 bytes) {
//    while (FLagArgbits.SPIWriteFlag || FLagArgbits.SPIReadFlag); //等待写操作完成
//    FLagArgbits.SPIReadFlag = 1;
//    SPI2Argbits.add1 = add;
//    SPI2Argbits.dat1 = dat;
//    SPI2Argbits.bytes1 = bytes;
//    while (!FLagArgbits.SPIReadFinishFlag); //等待读取完成
//    FLagArgbits.SPIReadFlag = 0;
//    FLagArgbits.SPIReadFinishFlag = 0;
//}


