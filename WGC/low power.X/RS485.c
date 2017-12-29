//#include"p24FV32KA301.h"
#include"UART.h"
#include"user.h"
#include"25L64B.h"

/*************************************
Function: RS485_Init 
Description: 485ͨѶ��ʼ��
Input: �� 
Output: ��
 *************************************/
void RS485_Init(void) {
    MC_CON_OUT; //���ƿ�����λ���
    RS485_TX_OUT;
    RS485_RX_IN;

    ANSBbits.ANSB2 = 0; //��������

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
    IEC0bits.U1RXIE = 1; //���ȿ����жϣ��������ò���
}

//void OpenAwake485(void) {//CN6��ƽ֪ͨ�жϻ����豸
//    RS485_RX_IN;
//    CNEN1bits.CN6IE = 1; //RX1����
//}

//void CloseAwake485(void) {
//    CNEN1bits.CN6IE = 0;
//}

/*************************************
Function: RS485_Send ���޸� 
Description: 485��������ָ��
Input: ���͵����� 
Output: 1:���ͳɹ�
 *************************************/
void RS485Send(const u8 dat) {
    RS485_CON = 1; //����
    U1TXREG = dat;
    while (!U1STAbits.TRMT);
    Delay_Nop(20);
    RS485_CON = 0; //����
    Delay_Nop(20);
}

/*************************************
Function: RS485_SendString 
Description: 485�����ַ���
Input: �ַ��� �ַ������� 
Output: ��
 *************************************/
void RS485SendString(const u8* dat, u8 bytes) {
    u8 count = 0;

    RS485_CON = 1; //����
    while (count < bytes) {
        U1TXREG = *(dat + count);
        while (U1STAbits.UTXBF);
        //        if(count==bytes-1)
        //            Delay100ms(1);                 //���Ը���ʱ��
        count++;
    }
    count = 0;
    //    if(count>30)
    while (!U1STAbits.TRMT);
    RS485_CON = 0; //����
    Delay_Nop(20);
}

//void OpenRS485(void) {
//    IEC0bits.U1RXIE = 1;
//    U1STAbits.UTXEN = 1; //UARTx transmitter is enabled �رմ��������豸һ���ڹ���??????????
//}

//void CloseRS485(void) {
//    IEC0bits.U1RXIE = 0;
//    U1STAbits.UTXEN = 0; //UARTx transmitter is enabled �رմ��������豸һ���ڹ���??????????
//}
/*************************************
Function: RS485_test 
Description: 485ͨѶ����
Input: �� 
Output: ��
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
Function: RS485_Receive  ���޸�
Description: 485��������ָ��
Input: �������ݵ�ָ�� 
Output: 1�����յ�����
 ************************************
bool RS485Receive(u8* dat) {

    bool b = true;
//    u8 timeCount;
    
//    RS485_CON = 0; //����

    if (U1STAbits.OERR)
        U1STAbits.OERR = 0;
    
//    gT23Count=0;
//    T2CONbits.TON = 1;//����ʱ�� ���ͨѶ�ȶ���
   
    while (!U1STAbits.URXDA) //û�н��յ�
    {
//        timeCount = gT23Count;
//        if( T100msIsOver(timeCount,10) ) {//1sû�н��յ�����
//            b = false;
//            break;
//        }
    }
//    T2CONbits.TON = 0;//�ض�ʱ��
//    gT23Count=0;           //�������
//    TMR3 = 0x0000; //Clear contents of the timer3 register
//    TMR2 = 0x0000;
    
//    if(b)
//        *dat = U1RXREG;

    return b;
}*/



