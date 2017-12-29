#include "SPI.h"
#include "user.h"
#include "25L64B.h"
#include "UART.h"
#include "TIM.h"
#include "P-Miot1601.h"
#include "Miot1601.h"

u16 bufferWptr_spi = 0;
u16 bufferRptr_spi = 0;
u8 gOffsetAdd = 0; //16位数据包
uint8_t SPI_tmp = 0;

/*************************************
Function: FM25L64B_Init 
Description: FM25L64B初始化
Input: 无
Output: 无
 *************************************/
void FM25L64B_Init(void) {
//    u8 tmp[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    SS2_TRIS = 0;
    SS2 = 1; //输出高电平

    //无写保护区
    FROM_WRSR(); //02
    //获取数据地址偏移量
    //while (BAT_DEC != 1); //等待供电  添加提示
    FM25L64B_Read(DataPacket_ID, &gOffsetAdd, 1);

    LoadMiotArg();
    //    FM25L64B_Read(BOR_Pulse, tmp, 4);//获取脉冲数
    //    DataReverse(tmp, 4); //将数据反转 00 00 FF 01  <==> 01 FF 00 00
    //    Register2Write(tmp, REG2_Arg_Postion[mi_ofst], 4);
    //    FM25L64B_Read(RST_Time, tmp, 7);
    //    if (tmp[0] == 0x20)
    //        Register2Write(tmp, REG2_Arg_Postion[mi_year], 7); //写入Regster2中 调试   
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

    SS2 = 0;
    SPI2_Exchange(WREN);
    SS2 = 1;
    SS2 = 0;
    SPI2_Exchange(WRITE);
    SPI2_Exchange(addH);
    SPI2_Exchange(addL);
    while (count < bytes) {
        SPI2_Exchange(*(dat + count));
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

    SS2 = 0;
    SPI2_Exchange(WREN);
    SS2 = 1;
    SS2 = 0;
    SPI2_Exchange(READ);
    SPI2_Exchange(addH); //0x03
    SPI2_Exchange(addL); //0x07
    while (count < bytes) {//0xa1
        *(dat + count) = SPI2_Exchange(0x00); //SPI2_Exchange(addL,SPI_tmp); //0x07
        count++;
    }
    SS2 = 1;
}

/*************************************
Function:  FROM_WRSR
Description: 写保护区
Input: 无
Output: 无
 *************************************/
void FROM_WRSR(void) {
    SS2 = 0;
    SPI2_Exchange(WRSR);
    SS2 = 1;
    SS2 = 0;
    SPI2_Exchange(0x00);
    SS2 = 1;
}


