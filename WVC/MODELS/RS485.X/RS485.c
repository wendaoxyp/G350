#include "RS485.h"

//#define RS485_TRIS TRISBbits.TRISB10
//#define RS485_CON LATBbits.LATB10 //TRISBbits.TRISB10 
//#define RS485_IN_TRIS TRISBbits.TRISB8
////#define RS485_IN LATBbits.LATB8
//#define RS485_OUT_TRIS TRISBbits.TRISB9
//#define RS485_OUT LATBbits.LATB9

/*************************************
Function: RS485_Init 
Description: 485通讯初始化
Input: 无 
Output: 无
 *************************************/

void RS485_Init(void) {
    RS485_RDE_TRIS = 0; //控制口设置位输出 485_CON
    RS485_RDE = 1; //使能接受，进入低功耗
    // STSEL 1; IREN disabled; PDSEL 8N; UARTEN enabled; RTSMD disabled; USIDL disabled; 
    // WAKE disabled; ABAUD disabled; LPBACK disabled; BRGH enabled; URXINV disabled; UEN TX_RX; 
    U2MODE = 0x0008; //设置U2的模式：UART2 disable;
    // UTXISEL0 TX_ONE_CHAR; UTXINV disabled; URXEN disabled; OERR NO_ERROR_cleared; 
    // URXISEL RX_3_4_BUF_FULL; UTXBRK COMPLETED; UTXEN disabled; ADDEN disabled; 
    U2STA = 0x0080;
    //关键波特率的误差
#ifdef OSC_Freq
    U2MODEbits.BRGH = 1;
    U2BRG = OSC_Freq / UART2_Baud / 4 - 1; //
#else
    U2MODEbits.BRGH = 0;
    U2BRG = 4000000 / UART2_Baud / 16 - 1; //使用内部晶振 
#endif    
    // ADMADDR 0; ADMMASK 0; 
    U2ADMD = 0x0000;
    //    IEC1bits.U2RXIE = 1;

    //Make sure to set LAT bit corresponding to TxPin as high before UART initialization
    IEC1bits.U2RXIE = 1; //开启接受中断
    IFS1bits.U2RXIF = 0; //清除接收中断
    IEC4bits.U2ERIE = 1; //开启错误中断
    IFS4bits.U2ERIF = 0; //清楚错误中断
    
    U2MODEbits.UARTEN = 1; // enabling UART ON bit
    U2STAbits.UTXEN = 1; //enableing UART transmit
    U2STAbits.URXEN = 1; //enableing UART receive
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
    RS485_RDE = 1; //发送
    //    OSTimeDlyHMSM(0, 0, 0, 30);
    U2TXREG = dat;
    while (!U2STAbits.TRMT); //while (!U2STAbits.TRMT);
    Delay10ms(1);
    RS485_RDE = 0; //接收;
}

/*************************************
Function: RS485_SendString 
Description: 485发送字符串
Input: 字符串 字符串长度 
Output: 无
 *************************************/
void RS485SendString(const uint8_t* dat, const uint8_t bytes) {
    uint8_t count;
#ifdef DeBug_RS485_Send_String
    uint8_t *ptr; //用于调试工具查看数据
#endif

    RS485_RDE = 1; //发送    
    Delay100ms(1);
    for (count = 0; count < bytes; count++) {
#ifdef DeBug_RS485_Send_String
        ptr = (uint8_t *) (dat + count);
#endif
        U2TXREG = *(dat + count);
        while (!U2STAbits.TRMT);
    }
    Delay100ms(1);
    RS485_RDE = 0; //接收
//    Delay100ms(5);
}

/*************************************
Function: OpenRS485 
Description: 打开485通讯
Input: 字符串 字符串长度 
Output: 无
 *************************************/
void OpenRS485(void) {
    IEC1bits.U2RXIE = 1;
    U2STAbits.UTXEN = 1; //UARTx transmitter is enabled 关闭串口以免设备一串口供电??????????
}

/*************************************
Function: RS485_SendString 
Description: 关闭485通讯
Input: 字符串 字符串长度 
Output: 无
 *************************************/
void CloseRS485(void) {
    IEC1bits.U2RXIE = 0;
    U2STAbits.UTXEN = 0; //UARTx transmitter is enabled 关闭串口以免设备一串口供电??????????
}

void GetLast4Bytes(void) {
    uint8_t cnt = 0;
    for (cnt = 0; cnt < 4; cnt++)
        if (U2STAbits.URXDA) //没有接收到        
            BufferWrite_UART2();
}
