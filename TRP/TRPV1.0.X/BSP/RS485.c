#include "RS485.h"

#define RS485_TRIS TRISBbits.TRISB10
#define RS485_CON LATBbits.LATB10 //TRISBbits.TRISB10 
#define RS485_IN_TRIS TRISBbits.TRISB8
//#define RS485_IN LATBbits.LATB8
#define RS485_OUT_TRIS TRISBbits.TRISB9
#define RS485_OUT LATBbits.LATB9

/*************************************
Function: RS485_Init 
Description: 485通讯初始化
Input: 无 
Output: 无
 *************************************/
void RS485_Init(void) {

    U1MODEbits.UARTEN = 1; //使能串口
    U1MODEbits.BRGH = 1; //16
    U1BRG = 0x0019; //103; //16000000/9600/16-1

    U1MODEbits.PDSEL = 00; //无奇偶校验
    U1MODEbits.STSEL = 0; //1位停止位
    U1MODEbits.USIDL = 0; //空闲模式下继续工作
    U1MODEbits.WAKE = 1; //休眠状态下继续工作
    //    U1MODEbits.UARTEN = 1; //使能串口
    U1STAbits.UTXEN = 0; //使能发送 必须先使能串口 在发送数据
    U1STAbits.URXISEL = 3; //有 4个数据字符，中断标志位置 1
    U1TXREG = 0;
    U1RXREG = 0;
    IPC2bits.U1RXIP = 7;
    IFS0bits.U1RXIF = 0; //清除接收中断
    IEC0bits.U1RXIE = 1; //开启接受中断
    IPC16bits.U1ERIP = 6;
    IFS4bits.U1ERIF = 0; //清楚错误中断
    IEC4bits.U1ERIE = 1; //开启错误中断    
    U1STAbits.UTXEN = 1; //使能发送 必须先使能串口 在发送数据

    //    U1MODE = 0x8008;
    //    // UTXEN disabled; UTXINV disabled; URXISEL RX_ONE_CHAR; ADDEN disabled; UTXISEL0 TX_ONE_CHAR; UTXBRK COMPLETED; OERR NO_ERROR_cleared; 
    //    U1STA = 0x0000;
    //    // U1TXREG 0x0000; 
    //    U1TXREG = 0x0000;
    //    // U1RXREG 0x0000; 
    //    U1RXREG = 0x0000;
    //    // Baud Rate = 9600; BRG 416; 
    //    U1BRG = 0x01A0;
    //
    //    IEC0bits.U1RXIE = 1;
    //
    //    U1STAbits.UTXEN = 1;
}

//void OpenAwake485(void) {//CN6电平通知中断唤醒设备
//    RS485_RX_IN;
//    CNEN1bits.CN6IE = 1; //RX1接受
//}

//void CloseAwake485(void) {
//    CNEN1bits.CN6IE = 0;
//}

/*************************************
Function: RS485_Send 待修改 
Description: 485发送数据指令
Input: 发送的数据 
Output: 1:发送成功
 *************************************/
void RS485SendChar(const uint8_t dat) {
    RS485_CON = 1; //发送
    U1TXREG = dat;
    while (!U1STAbits.TRMT);
    Delay10ms(1);
    RS485_CON = 0; //接收
}

/*************************************
Function: RS485_SendString 
Description: 485发送字符串
Input: 字符串 字符串长度 
Output: 无
 *************************************/
void RS485SendString(const uint8_t* dat, uint8_t bytes) {
    uint8_t count = 0;

    RS485_CON = 1; //发送    
    //    Delay10ms(1);
    while (count < bytes) {
        U1TXREG = *(dat + count);
        while (!U1STAbits.TRMT);
        count++;
    }
//    Delay1ms(10); //加一段延时
    RS485_CON = 0; //接收
}

//#ifdef DEBUG_485_SEND_STR

/*************************************
Function: RS485_SendString 
Description: 485发送字符串
Input: 字符串 字符串长度 
Output: 无
 *************************************/
void RS485SendString1(const uint8_t* dat) {
    uint8_t count = 0;

    RS485_CON = 1; //发送    
    Delay100ms(1);
    while (dat[count] != '\0') {
        U1TXREG = *(dat + count);
        while (!U1STAbits.TRMT);
        count++;
    }
    Delay100ms(1);
    RS485_CON = 0; //接收
    Delay10ms(1);
}

/*************************************
Function: U1Rx4Byte 
Description: 获取最后接收到的数据，因为4个字节一次中断，最后3个字节需要执行该函数获取
Input: 无
Output: 无
 *************************************/
void U1Rx4Byte(void) {//获取终端里面的最后几个数据，每4个字节中断
    uint8_t cnt;
    for (cnt = 0; cnt < 4; cnt++)//串口最后四个字节没有接受到，中断原因
        if (U1STAbits.URXDA) //没有接收到
            BufferWrite_UART1();
}




