#include "RS485.h"



/*************************************
Function: RS485_Init 
Description: 485通讯初始化
Input: 无 
Output: 无
 *************************************/
void RS485_Init(void) {
    RS485_TRIS = 0; //控制口设置位输出 485_CON
    RS485_IN_TRIS = 1; //设置为输入/
    RS485_OUT_TRIS = 0; //设置为输出
    ANSBbits.ANSB8 = 1; //数字输入
    //    ANSBbits.ANSB9 = 1;

    U1MODEbits.BRGH = 0; //16
    U1BRG = 103; //16000000/9600/16-1

    U1MODEbits.PDSEL = 00; //无奇偶校验
    U1MODEbits.STSEL = 0; //1位停止位
    U1MODEbits.UARTEN = 1; //使能串口

    U1STAbits.UTXEN = 1; //使能发送 必须先使能串口 在发送数据
    //    U1STAbits.URXISEL = 3; //有 4 个数据字符，中断标志位置 1
    //    IEC0bits.U1RXIE = 1; //开启接受中断
    //    IFS0bits.U1RXIF = 0; //清除接收中断
    //    IEC4bits.U1ERIE = 1; //开启错误中断
    //    IFS4bits.U1ERIF = 0; //清楚错误中断
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
    //    OSTimeDlyHMSM(0, 0, 0, 30);
    U1TXREG = dat;
    while (!U1STAbits.TRMT); //while (!U2STAbits.TRMT);
    OSTimeDlyHMSM(0, 0, 0, 10);
    RS485_CON = 0; //接收
    //    OSTimeDlyHMSM(0, 0, 0, 1);
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
    OSTimeDlyHMSM(0, 0, 0, 100);
    while (count < bytes) {
        U1TXREG = *(dat + count);
        while (!U1STAbits.TRMT);
        count++;
    }
    OSTimeDlyHMSM(0, 0, 0, 100);
    RS485_CON = 0; //接收
    OSTimeDlyHMSM(0, 0, 0, 1);
}

/*************************************
Function: OpenRS485 
Description: 打开485通讯
Input: 字符串 字符串长度 
Output: 无
 *************************************/
void OpenRS485(void) {
    IEC0bits.U1RXIE = 1;
    U1STAbits.UTXEN = 1; //UARTx transmitter is enabled 关闭串口以免设备一串口供电??????????
}

/*************************************
Function: RS485_SendString 
Description: 关闭485通讯
Input: 字符串 字符串长度 
Output: 无
 *************************************/
void CloseRS485(void) {
    IEC0bits.U1RXIE = 0;
    U1STAbits.UTXEN = 0; //UARTx transmitter is enabled 关闭串口以免设备一串口供电??????????
}
/*************************************
Function: RS485_test 
Description: 485通讯测试
Input: 无 
Output: 无
 *************************************/
//void RS485test(void)
//{
//    uint8_t dat='6';

//RS485Send('T');
//    if(!RS485Receive(&dat))
//    {
//        RS485Send(dat);
//        RS485Send('T');
//    }
//}

/*************************************
Function: RS485_Receive  待修改
Description: 485接收数据指令
Input: 接收数据的指针 
Output: 1：接收到数据
 ************************************
bool RS485Receive(uint8_t* dat) {

    bool b = true;
//    uint8_t timeCount;
    
//    RS485_CON = 0; //接收

    if (U1STAbits.OERR)
        U1STAbits.OERR = 0;
    
//    gT23Count=0;
//    T2CONbits.TON = 1;//开定时器 提高通讯稳定性
   
    while (!U1STAbits.URXDA) //没有接收到
    {
//        timeCount = gT23Count;
//        if( T100msIsOver(timeCount,10) ) {//1s没有接收到数据
//            b = false;
//            break;
//        }
    }
//    T2CONbits.TON = 0;//关定时器
//    gT23Count=0;           //清除计数
//    TMR3 = 0x0000; //Clear contents of the timer3 register
//    TMR2 = 0x0000;
    
//    if(b)
//        *dat = U1RXREG;

    return b;
}*/



