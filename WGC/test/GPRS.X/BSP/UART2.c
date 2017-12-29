//#include "includes.h"
#include "UART2.h"

void UART2_Init(void) {
    //已经为数字端口，
    TRISDbits.TRISD2 = 1; //设置为输入
    TRISDbits.TRISD3 = 0; //设置为输出
    //    TRISDbits.TRISD3 = 1; //设置为输入
    //    TRISDbits.TRISD2 = 0; //设置为输出

    U2MODEbits.BRGH = 0; //波特率使用标准模式1:16
    U2BRG = 51; //19200 103; //16000000/9600/16-1
    U2MODEbits.PDSEL = 00; //无奇偶校验
    U2MODEbits.STSEL = 0; //1位停止位

    U2MODEbits.UARTEN = 1; //使能串口

    U2STAbits.UTXEN = 1; //使能发送 必须先使能串口 在发送数据
    U2STAbits.URXISEL = 3; //有 4 个数据字符，中断标志位置 1
    IEC1bits.U2RXIE = 1; //开启接受中断
    IFS1bits.U2RXIF = 0; //清除接收中断
    IEC4bits.U2ERIE = 1;
    IFS4bits.U2ERIF = 0;
}

void UART2_Open(void) {
    U2MODEbits.UARTEN = 1; //使能串口
    U2STAbits.UTXEN = 1; //使能发送 必须先使能串口 在发送数据
    // IEC1bits.U2TXIE=1;
    IEC1bits.U2RXIE = 1;
}

void UART2_Close(void) {
    // IEC1bits.U2TXIE=0;
    IEC1bits.U2RXIE = 0;
    U2STAbits.UTXEN = 1; //使能发送 必须先使能串口 在发送数据
    U2MODEbits.UARTEN = 0; //使能串口发送    
}

void UART2_SendChar(uint8_t ch) {
    U2TXREG = ch;
    while (!U2STAbits.TRMT);
}

uint8_t UART2_SendString(const uint8_t *str) {
    uint8_t bytes = 0;
    while (*str != '\0') {
        UART2_SendChar(*str++);
        bytes++;
    }
    return bytes;
}

uint8_t UART2_SendString2(const uint8_t *str, uint8_t len) {
    uint8_t bytes = 0;
    while (bytes < len) {
        UART2_SendChar(*str++);
        bytes++;
    }
    return bytes;
}

bool UART2_ReceiveChar(uint8_t * ch) {
    if (U2STAbits.URXDA) {
        *ch = U2RXREG;
        return true;
    } else
        return false;
}

void U2Rx4Byte(void) {//获取终端里面的最后几个数据，每4个字节中断
    uint8_t cnt;
    for (cnt = 0; cnt < 4; cnt++)//串口最后四个字节没有接受到，中断原因
        if (U2STAbits.URXDA) //没有接收到
            BufferWrite_UART2();
}



