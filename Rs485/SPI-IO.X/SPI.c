//#include <p24FV32KA301.h>
//#include "type.h"
#include "SPI.h"
#include "user.h"

u8 gOffsetAdd = 0; //16位数据包

static void SPI_Nop(void) {
    u8 i; //, j;
    for (i = 0; i < 36; i++)
        //        for (j = 0; j < 10; j++)
        Nop();
    //    Nop();
}

void SPI2_Configuration(void) {
    SCK2_TRIS = 1;
    SDO2_TRIS = 0; //BF 1(bit7)01(bit5)1 1111
    SDI2_TRIS = 0;
    //    ANSAbits.
    SS2_TRIS = 0;
    SS2 = 1;
    //    ANSBbits.ANSB12 = 1;
    ////        ANSAbits.
    IFS2bits.SPI2IF = 0;
    //    IEC2bits.SPI2IE = 0;
    //    IPC8bits.SPI2IP = 2;
    //    // SPI Frequency = 1,000,000 Hz; PPRE 1:1; SMP Sample at Middle; MSTEN enabled; MODE16 disabled; DISSCK disabled; SPRE 4:1; CKE Active to Idle; DISSDO disabled; CKP Idle:Low, Active:High; 
    //    SPI2CON1 = 0x0133;
    //    // SPIFPOL disabled; SPIBEN enabled; SPIFE disabled; 
    //    SPI2CON2 = 0x0001;
    //    // SISEL SPI_INT_SPIRBF; SPIEN enabled; SPISIDL disabled; SPIROV disabled; 
    //    SPI2STAT = 0x8004; //800C
    // SPI Frequency = 1,000,000 Hz; PPRE 4:1; SMP Sample at Middle; MSTEN enabled; MODE16 disabled; DISSCK disabled; SPRE 1:1; CKE Active to Idle; DISSDO disabled; CKP Idle:Low, Active:High; 
    SPI2CON1 = 0x013E; //0x0133;
    // SPIFPOL disabled; SPIBEN enabled; SPIFE disabled; 
    SPI2CON2 = 0x0001; //0001
    // SISEL SPI_INT_SPIRBF; SPIEN enabled; SPISIDL disabled; SPIROV disabled; 
    SPI2STAT = 0x800C;
}

void SPI_Write(u8 dat, u8*dat1) {
    //    while (SPI2STATbits.SPITBF == true);
    //    SPI2BUF = *((u8*) dat);
    SPI2BUF = dat;
    while (SPI2STATbits.SR1MPT);
    //    while (SPI2STATbits.SPIRBF == false);
    *((u8*) dat1) = SPI2BUF;
}

void SPI_Read(u8* dat) {
    //    while (SPI2STATbits.SPIRBF == true);
    //    SPI2BUF = 0;
    //    while (SPI2STATbits.SR1MPT == false);
    *(u8*) dat = SPI2BUF;
    Nop();
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

    SS2 = 0; //片选CS置低
    SPI_Write(WREN, dat); //0x06
    SS2 = 1; //片选CS置低
    SS2 = 0; //片选CS置低
    SPI_Write(READ, dat + 1); //0x02
    SPI_Write(addH, dat + 2); //0x1F 0x1FF0
    SPI_Write(addL, dat + 3); //0xF0
    SS2 = 1; //片选CS置低
    //    SPI_Write(1, dat); //0x06
    //    SPI_Write(2, dat + 1); //0x02
    //    SPI_Write(3, dat + 2); //0x1F 0x1FF0
    //    SPI_Write(4, dat + 3); //0xF0
    //    //    Delay_Nop(1);
    //    //    Delay_Nop(1);//9.22
    //    //    while (count < bytes) {
    //    //        SPI_Write(*(dat + count));
    //    //        //        Delay_Nop(1);
    //    //        count++;
    //    //    }
    //    //    while (SPI2STATbits.SPITBF == true);
    //    SPI_Nop();
    //    SS2 = 1;
    //    Delay_Nop(1);
    //    SS1 = 0;
    //    Delay_Nop(1);
    //    SPI_Write(WRDI);
    //    Delay_Nop(1);
    //    SS1 = 1;
    //    Delay_Nop(1);
}

/*************************************
Function: FM25L64B_Read 
Description: FM25L64B通讯读指令
Input: 地址1，接收的数据,字节数
Output: 无
 *************************************/
//static void FM25L64B_Read(u16 add, u8 *dat, u8 bytes) { 

void FM25L64B_Read(u16 add, u8 *dat, u8 bytes) {
    u8 count = 0;
    u8 addL = (u8) (add & 0x00FF);
    u8 addH = (u8) ((add >> 8) & 0x00FF);

    SS2 = 0; //片选CS置低

    SPI_Write(WREN, dat); //0x06
    SPI_Write(READ, dat + 1); //0x02
    SPI_Write(addH, dat + 2); //0x1F 0x1FF0
    SPI_Write(addL, dat + 3); //0xF0
    //    SPI_Nop();
    SPI_Write(0, dat); //0x06
    SPI_Write(0, dat + 1); //0x02
    SPI_Write(0, dat + 2); //0x1F 0x1FF0
    SPI_Write(0, dat + 3); //0xF0
    //    if (IFS2bits.SPI2IF) {
    //        *((u8*) dat) = SPI2BUF;
    //        *((u8*) dat+1) = SPI2BUF;
    //        *((u8*) dat+2) = SPI2BUF;
    //        *((u8*) dat+3) = SPI2BUF;
    //        IFS2bits.SPI2IF = 0;
    //        Nop();
    //    }
    SPI_Nop();
    //        Delay_Nop(1);
    SS2 = 1;
}

///*************************************
//Function:  FROM_WriteDPNum
//Description: 更新数据包序号
//Input: 无
//Output: 无
// *************************************/
//void FROM_WriteDPNum(void) {
//    //    u8 tmp[2];
//    //    tmp[0] = (gOffsetAdd >> 8)&0x00ff;
//    //    tmp[1] = gOffsetAdd & 0x00ff;
//    FM25L64B_Write(DataPacket_ID, &gOffsetAdd, 1); //写入数据包序号
//    gOffsetAdd += 1; //数据包序号+1  
//    gOffsetAdd = gOffsetAdd % DataPacketNum; //一个环数据为252 12*21
//}

/*************************************
Function:  FROM_EN
Description: 使能写
Input: 无
Output: 无
 *************************************/
void FROM_EN(void) {
    u8 tmp;
    SPI_Write(WREN, &tmp);
}

/*************************************
Function:  FROM_WRSR
Description: 写保护区
Input: 无
Output: 无
 *************************************/
void FROM_WRSR(void) {
    u8 tmp;
    SS2 = 0;
    Delay_Nop(1);
    SPI_Write(WRSR, &tmp);
    Delay_Nop(1);
    SPI_Write(0x00, &tmp);
    Delay_Nop(1);
    SS2 = 1;
    Delay_Nop(1);
}

//void FROM_Arg_Setting(void) {
//    u8 tmp[4] = {4, 3, 2, 1};
//    FM25L64B_Write(BOR_Pulse, tmp, 4);
//    gPulseCount = ((u32) tmp[0] << 24)+((u32) tmp[1] << 16)+((u16) tmp[2] << 8) + tmp[3];
//    //    FM25L64B_Write(BOR_Vm,&,4);
//}

