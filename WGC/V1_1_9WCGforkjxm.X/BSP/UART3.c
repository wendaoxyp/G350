//#include "includes.h"
#include "UART3.h"
#include <xc.h>

void UART3_Init(void) {
    TRISGbits.TRISG8 = 1; //设置为输入
    TRISGbits.TRISG7 = 0; //设置为输出
    ANSGbits.ANSG7 = 0; //已经为数字端口
    ANSGbits.ANSG8 = 0;
    ODCGbits.ODG8 = 1; //漏极开路输出
    //    TRISDbits.TRISD3 = 1; //设置为输入
    //    TRISDbits.TRISD2 = 0; //设置为输出

    U3MODEbits.BRGH = 0; //波特率使用标准模式1:16
    U3BRG = 0x19; //19200 103; //16000000/9600/16-1
    U3MODEbits.PDSEL = 00; //无奇偶校验
    U3MODEbits.STSEL = 0; //1位停止位

    U3MODEbits.UARTEN = 1; //使能串口

    U3STAbits.URXISEL = 3; //有 4 个数据字符，中断标志位置 1
    IFS5bits.U3RXIF = 0; //清除接收中断  
    IPC20bits.U3RXIP = 6;
    IEC5bits.U3RXIE = 1; //开启接受中断
    IFS5bits.U3ERIF = 0;
    IPC20bits.U3ERIP = 7;
    IEC5bits.U3ERIE = 1;
    U3STAbits.UTXEN = 1; //使能发送 必须先使能串口 在发送数据
}

void UART3_Open(void) {
    U3MODEbits.UARTEN = 1; //使能串口
    U3STAbits.UTXEN = 1; //使能发送 必须先使能串口 在发送数据
    // IEC1bits.U3TXIE=1;
    IEC5bits.U3RXIE = 1;
}

void UART3_Close(void) {
    // IEC1bits.U3TXIE=0;
    IEC5bits.U3RXIE = 0;
    U3STAbits.UTXEN = 1; //使能发送 必须先使能串口 在发送数据
    U3MODEbits.UARTEN = 0; //使能串口发送    
}

void UART3_SendChar(uint8_t ch) {
    U3TXREG = ch;
    while (!U3STAbits.TRMT);
}

uint8_t UART3_SendString(const uint8_t *str, const uint8_t len) {
    uint8_t bytes = 0;
    for (bytes = 0; bytes < len; bytes++) {//(bytes++ < len) {
        UART3_SendChar(*(str + bytes));
        //        bytes++;
    }
    return bytes;
}

bool UART3_ReceiveChar(uint8_t * ch) {
    if (U3STAbits.URXDA) {
        *ch = U3RXREG;
        return true;
    } else
        return false;
}

void U3Rx4Byte(void) {//获取终端里面的最后几个数据，每4个字节中断
    uint8_t cnt;
    for (cnt = 0; cnt < 4; cnt++)//串口最后四个字节没有接受到，中断原因
        if (U3STAbits.URXDA) //没有接收到
            BufferWrite_UART3();
}



