#include "user.h"
struct UART2_Arg UART2Argbits;
const u16 BAUD[5] = {1200, 2400, 4800, 9600, 19200};

/*************************************
Function: UART2_Configuration 
Description: 串口2初始化
Input: 无 
Output: 无
 *************************************/
void UART2_Configuration(void) {
    RX2_IN;
    CNPD1bits.CN6PDE = 1; //输入脚弱下拉
    TX2_OUT;
    ANSBbits.ANSB1 = 0; //数字输入             
    U2MODEbits.BRGH = 0; //1：High Baudrate
    U2BRG = BRGVAL; //19200 0.15%BRGVAL ((FP/BAUDRATE)/4) - 1
    U2MODEbits.USIDL = 0; //1 = 当器件进入空闲模式时，模块停止工作
    U2MODEbits.UARTEN = 1;

    U2STAbits.UTXEN = 1; //UARTx transmitter is enabled 关闭串口以免设备一串口供电??????????
    IPC7bits.U2RXIP = 6;
    IPC7bits.U2TXIP = 4;
    IPC16bits.U2ERIP = 7;
    IEC1bits.U2RXIE = 1; //开启中断??????????????
    //    IEC1bits.U2TXIE = 1; //开启中断??????????????
    U2STAbits.UTXISEL0 = 0;
    U2STAbits.UTXISEL1 = 0;
    U2STAbits.URXISEL = 3; //3/4的时候接受中断一次

    IFS1bits.U2RXIF = 0; // Clear the Recieve Interrupt Flag
    //    IFS1bits.U2TXIF = 0; // Clear the Recieve Interrupt Flag
    //    U2TXREG=0x00;//先填充一次
}

void SetGPRSBaudRate(u8 baudID) {
    IFS1bits.U2RXIF = 0; // Clear the Recieve Interrupt Flag
    IFS1bits.U2TXIF = 0; // Clear the Recieve Interrupt Flag
    U2MODEbits.UARTEN = 0;
    U2STAbits.UTXEN = 0; //UARTx transmitter is enabled 关闭串口以免设备一串口供电??????????
    IEC1bits.U2RXIE = 0; //开启中断??????????????
    //    IEC1bits.U2TXIE = 0; //开启中断??????????????
    //      U2MODEbits.BRGH = 0; //1：High Baudrate
    if (baudID > 4)
        baudID = 4;
    U2BRG = ((FP / BAUD[baudID]) / 16) - 1; //19200 0.15%BRGVAL ((FP/BAUDRATE)/4) - 1
    //    U2MODEbits.USIDL = 0; //1 = 当器件进入空闲模式时，模块停止工作
    //    U2MODEbits.UARTEN = 0;
    U2MODEbits.UARTEN = 1;
    U2STAbits.UTXEN = 1; //UARTx transmitter is enabled 关闭串口以免设备一串口供电??????????
    //    IPC7bits.U2RXIP = 6;
    //    IPC7bits.U2TXIP = 4;
    //    IPC16bits.U2ERIP = 7;
    IEC1bits.U2RXIE = 1; //开启中断??????????????
    //    IEC1bits.U2TXIE = 1; //开启中断??????????????
    //    U2STAbits.UTXISEL0 = 0;
    //    U2STAbits.UTXISEL1 = 0;
    //    U2STAbits.URXISEL = 3; //3/4的时候接受中断一次

    IFS1bits.U2RXIF = 0; // Clear the Recieve Interrupt Flag
    IFS1bits.U2TXIF = 0; // Clear the Recieve Interrupt Flag
}

/*************************************
Function: UART2Send 
Description: 串口2发送单个数据
Input: u8类型数据 
Output: 1 发送成功
 *************************************/
//void UART2Send(const u8 dat) {
//    U2TXREG = dat;
//    while (!U2STAbits.TRMT);
//}

/*************************************
Function: UART2SendString 
Description: 串口2发送字符串
Input: 指向u8类型的数据
Output: 无
 *************************************/
void UART2SendString(const u8* ch, u8 bytes) {
    u8 byte = 0;
    while (byte < bytes) {
        //        IFS1bits.U2TXIF = 1;
        U2TXREG = *(ch + byte); //发送数据
        while (!U2STAbits.TRMT);
        byte += 1;
        //        while (IFS1bits.U2TXIF); //等待发送结束
    }
}

/*************************************
Function: UART2SendString 
Description: 串口2发送字符串
Input: 指向u8类型的数据
Output: 无
 *************************************/
void UART2SendString2(const u8* ch) {
    //    UART2Argbits.dat2 = (u8*) ch;
    //    UART2Argbits.bytes2 = bytes;
    //    u8 byte = 0;
    while (*ch != '\0') {
        //        IFS1bits.U2TXIF = 1;
        U2TXREG = *ch; //发送数据
        while (!U2STAbits.TRMT);
        ch += 1;
        //        while (IFS1bits.U2TXIF); //等待发送结束
    }
}

void Open_UART2(void) {
    U2STAbits.UTXEN = 1; //关闭串口以免设备一串口供电
    IEC1bits.U2RXIE = 1; //开启中断
}

void Close_UART2(void) {
    U2STAbits.UTXEN = 0; //关闭串口以免设备一串口供电
    IEC1bits.U2RXIE = 0; //开启中断
}

///*************************************
//Function: UART2_Receive 
//Description: 获取实时时钟的时间
//Input: 4个u16类型数据 
//Output: 1接收成功
//*************************************/
// bool UART2Receive(u8* dat)
//{   
////    if(U2STAbits.OERR)
////        U2STAbits.OERR = 0;
//
//    if(U2STAbits.URXDA)//    while(!U2STAbits.URXDA)
//    {
//        *dat = U2RXREG;
//        return true;
//    }
//    else
//        return false;
//}
