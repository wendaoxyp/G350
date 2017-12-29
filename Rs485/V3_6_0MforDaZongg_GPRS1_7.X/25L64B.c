#include "SPI.h"
#include "user.h"
#include "25L64B.h"
#include "UART.h"
#include "TIM.h"
#include "P-Miot1601.h"
#include "Miot1601.h"

u16 bufferWptr_spi = 0;
u16 bufferRptr_spi = 0;
u8 gOffsetAdd = 0; //16λ���ݰ�
uint8_t SPI_tmp = 0;

/*************************************
Function: FM25L64B_Init 
Description: FM25L64B��ʼ��
Input: ��
Output: ��
 *************************************/
void FM25L64B_Init(void) {
//    u8 tmp[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    SS2_TRIS = 0;
    SS2 = 1; //����ߵ�ƽ

    //��д������
    FROM_WRSR(); //02
    //��ȡ���ݵ�ַƫ����
    //while (BAT_DEC != 1); //�ȴ�����  �����ʾ
    FM25L64B_Read(DataPacket_ID, &gOffsetAdd, 1);

    LoadMiotArg();
    //    FM25L64B_Read(BOR_Pulse, tmp, 4);//��ȡ������
    //    DataReverse(tmp, 4); //�����ݷ�ת 00 00 FF 01  <==> 01 FF 00 00
    //    Register2Write(tmp, REG2_Arg_Postion[mi_ofst], 4);
    //    FM25L64B_Read(RST_Time, tmp, 7);
    //    if (tmp[0] == 0x20)
    //        Register2Write(tmp, REG2_Arg_Postion[mi_year], 7); //д��Regster2�� ����   
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
Description: FM25L64BͨѶ��ָ��
Input: ��ַ1�����յ�����,�ֽ���
Output: ��
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
Description: д������
Input: ��
Output: ��
 *************************************/
void FROM_WRSR(void) {
    SS2 = 0;
    SPI2_Exchange(WRSR);
    SS2 = 1;
    SS2 = 0;
    SPI2_Exchange(0x00);
    SS2 = 1;
}


