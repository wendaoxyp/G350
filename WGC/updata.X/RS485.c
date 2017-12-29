//#include"p24FV32KA301.h"
#include"UART.h"
#include"user.h"
#include"25L64B.h"

/*************************************
Function: RS485_Init 
Description: 485通讯初始化
Input: 无 
Output: 无
 *************************************/
void RS485_Init(void) {
    MC_CON_OUT; //控制口设置位输出
    RS485_TX_OUT;
    RS485_RX_IN;

    ANSBbits.ANSB2 = 0; //数字输入

    U1MODEbits.BRGH = 0;
    U1BRG = BRGVAL;

    U1MODEbits.USIDL = 1;
    U1MODEbits.UEN = 0;
    U1MODEbits.UARTEN = 1;
    IFS0bits.U1RXIF = 0; // Clear the Recieve Interrupt Flag
    U1STAbits.UTXEN = 1;

    IPC2bits.U1RXIP = 6;
    IPC16bits.U1ERIP=7;
    U1STAbits.URXISEL = 0;
    IEC0bits.U1RXIE = 1; //优先开启中断，用于设置参数
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
void RS485Send(const u8 dat) {
    RS485_CON = 1; //发送
    U1TXREG = dat;
    while (!U1STAbits.TRMT);
    Delay_Nop(20);
    RS485_CON = 0; //接收
    Delay_Nop(20);
}

/*************************************
Function: RS485_SendString 
Description: 485发送字符串
Input: 字符串 字符串长度 
Output: 无
 *************************************/
void RS485SendString(const u8* dat, u8 bytes) {
    u8 count = 0;

    RS485_CON = 1; //发送
    while (count < bytes) {
        U1TXREG = *(dat + count);
        while (U1STAbits.UTXBF);
        //        if(count==bytes-1)
        //            Delay100ms(1);                 //可以更短时间
        count++;
    }
    count = 0;
    //    if(count>30)
    while (!U1STAbits.TRMT);
    RS485_CON = 0; //接收
    Delay_Nop(20);
}

//void OpenRS485(void) {
//    IEC0bits.U1RXIE = 1;
//    U1STAbits.UTXEN = 1; //UARTx transmitter is enabled 关闭串口以免设备一串口供电??????????
//}

//void CloseRS485(void) {
//    IEC0bits.U1RXIE = 0;
//    U1STAbits.UTXEN = 0; //UARTx transmitter is enabled 关闭串口以免设备一串口供电??????????
//}
/*************************************
Function: RS485_test 
Description: 485通讯测试
Input: 无 
Output: 无
 *************************************/
//void RS485test(void)
//{
//    u8 dat='6';

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
bool RS485Receive(u8* dat) {

    bool b = true;
//    u8 timeCount;
    
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



