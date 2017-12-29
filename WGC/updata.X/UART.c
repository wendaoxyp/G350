#include "user.h"

/*************************************
Function: UART2_Configuration 
Description: ����2��ʼ��
Input: �� 
Output: ��
 *************************************/
void UART2_Configuration(void) {
    RX2_IN;
    //    CNPD1bits.CN6PDE = 1; //�����������
    TX2_OUT;
    ANSBbits.ANSB1 = 0; //��������             
    U2MODEbits.BRGH = 0; //1��High Baudrate
    U2BRG = BRGVAL; //19200 0.15%BRGVAL ((FP/BAUDRATE)/4) - 1
    U2MODEbits.USIDL = 0; //1 = �������������ģʽʱ��ģ��ֹͣ����
    U2MODEbits.UARTEN = 0;//UART�ܿ���

    U2STAbits.UTXEN = 1; //UARTx transmitter is enabled �رմ��������豸һ���ڹ���??????????
    IPC7bits.U2RXIP = 6;
    IPC7bits.U2TXIP = 4;
    IPC16bits.U2ERIP = 7;
    IEC1bits.U2RXIE = 1; //�����ж�??????????????
    IEC1bits.U2TXIE = 1; //�����ж�??????????????
    U2STAbits.UTXISEL0 = 0;
    U2STAbits.UTXISEL1 = 0;
    U2STAbits.URXISEL = 3; //3/4��ʱ������ж�һ��

    IFS1bits.U2RXIF = 0; // Clear the Recieve Interrupt Flag
    IFS1bits.U2TXIF = 0; // Clear the Recieve Interrupt Flag
    //    U2TXREG=0x00;//�����һ��
}

/*************************************
Function: UART2Send 
Description: ����2���͵�������
Input: u8�������� 
Output: 1 ���ͳɹ�
 *************************************/
//void UART2Send(const u8 dat) {
//    U2TXREG = dat;
//    while (!U2STAbits.TRMT);
//}

/*************************************
Function: UART2SendString 
Description: ����2�����ַ���
Input: ָ��u8���͵�����
Output: ��
 *************************************/
void UART2SendString(const u8* ch, u8 bytes) {
    UART2Argbits.dat2 = (u8*) ch;
    UART2Argbits.bytes2 = bytes;
    IFS1bits.U2TXIF = 1;
    while (IFS1bits.U2TXIF); //�ȴ����ͽ���
}

void Open_UART2(void) {
    U2MODEbits.UARTEN = 1; //�رմ��������豸һ���ڹ���
    IFS1bits.U2RXIF = 0; // Clear the Recieve Interrupt Flag
    IFS1bits.U2TXIF = 0; // Clear the Recieve Interrupt Flag
    IEC1bits.U2RXIE = 1; //�����ж�
    U2STAbits.UTXEN = 1;
}

void Close_UART2(void) {
    IEC1bits.U2RXIE = 0; //�����ж�
    U2STAbits.UTXEN = 0;
    IFS1bits.U2RXIF = 0; // Clear the Recieve Interrupt Flag
    IFS1bits.U2TXIF = 0; // Clear the Recieve Interrupt Flag
    U2MODEbits.UARTEN = 0; //�رմ��������豸һ���ڹ���
}

///*************************************
//Function: UART2_Receive 
//Description: ��ȡʵʱʱ�ӵ�ʱ��
//Input: 4��u16�������� 
//Output: 1���ճɹ�
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
