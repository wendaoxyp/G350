#include "SPI.h"
#include "user.h"
#include "25L64B.h"
//#include "p24FV32KA301.h"
#include "UART.h"
#include "TIM.h"
#include "P-Miot1601.h"
#include "Miot1601.h"
//#include����

u16 bufferWptr_spi = 0;
u16 bufferRptr_spi = 0;
u8 gOffsetAdd = 0; //16λ���ݰ�

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
Description: FM25L64B��ʼ��
Input: ��
Output: ��
 *************************************/
void FM25L64B_Init(void) {
    u8 tmp[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    SDO2_TRIS = 0; //��Ƭ�����
    SDI2_TRIS = 1; // 1; //��Ƭ������
    SCK2_TRIS = 0;
    SS2_TRIS = 0;
    ANSBbits.ANSB14 = 0; //��������
//    CNPD1bits.CN12PDE = 1;
    SS2 = 1; //����ߵ�ƽ
    SCK2 = 0;
    SDO2 = 0;

    //��д������
    FROM_WRSR(); //02
    //��ȡ���ݵ�ַƫ����
//    while (BAT_DEC != 1); //�ȴ�����  ������ʾ
    FM25L64B_Read(DataPacket_ID, &gOffsetAdd, 1);

    FM25L64B_Read(BOR_Pulse, tmp, 4);
    DataReverse(tmp, 4); //�����ݷ�ת 00 00 FF 01  <==> 01 FF 00 00
    Register2Write(tmp, REG2_Arg_Postion[mi_ofst], 4);
    FM25L64B_Read(RST_Time, tmp, 7);
    if (tmp[0] == 0x20)
        Register2Write(tmp, REG2_Arg_Postion[mi_year], 7); //д��Regster2�� ����   
}

/*************************************
Function: SPI_Write 
Description: ����SPIд����ָ��
Input: SPIͨѶ����
Output: ��
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
Description: ����SPI�Ķ�ȡ����ָ��
Input: ��
Output: �ӻ����͹���������
 *************************************/
static void SPI_Read(u8 *dat) {
    char count = 0;
    *dat = 0x00; //���ԭʼ����
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
Description: FM25L64BͨѶд����
Input: ��ַ����9λ��ַbit8�����͵�����
Output: ��
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
Description: FM25L64BͨѶ��ָ��
Input: ��ַ1�����յ�����,�ֽ���
Output: ��
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
Description: �������ݰ����
Input: ��
Output: ��
 *************************************/
//void FROM_WriteDPNum(void) {
//    FM25L64B_Write(DataPacket_ID, &gOffsetAdd, 1); //д�����ݰ����
//    gOffsetAdd += 1; //���ݰ����+1  
//    gOffsetAdd = gOffsetAdd % DataPacketNum; //һ��������Ϊ252 12*21
//}

/*************************************
Function:  FROM_EN
Description: ʹ��д
Input: ��
Output: ��
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
Description: д������
Input: ��
Output: ��
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
//    while ( FLagArgbits.SPIWriteFlag); //�ȴ������������ϴ�д������� 
//    FLagArgbits.SPIWriteFlag = 1;
//    SPI2Argbits.add1 = add;
//    SPI2Argbits.dat1 = dat;
//    SPI2Argbits.bytes1 = bytes;
//    
//    while (!FLagArgbits.SPIWriteFinishFlag); //�ȴ��������
//    FLagArgbits.SPIWriteFlag = 0;
//    FLagArgbits.SPIWriteFinishFlag = 0;
//}

//void PostSPIReadFlag(u16 add, u8* dat, u8 bytes) {
//    while (FLagArgbits.SPIWriteFlag || FLagArgbits.SPIReadFlag); //�ȴ�д�������
//    FLagArgbits.SPIReadFlag = 1;
//    SPI2Argbits.add1 = add;
//    SPI2Argbits.dat1 = dat;
//    SPI2Argbits.bytes1 = bytes;
//    while (!FLagArgbits.SPIReadFinishFlag); //�ȴ���ȡ���
//    FLagArgbits.SPIReadFlag = 0;
//    FLagArgbits.SPIReadFinishFlag = 0;
//}

