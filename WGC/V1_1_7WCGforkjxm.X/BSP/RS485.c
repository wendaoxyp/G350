#include "RS485.h"

#define RS485_TRIS TRISBbits.TRISB10
#define RS485_CON LATBbits.LATB10 //TRISBbits.TRISB10 
#define RS485_IN_TRIS TRISBbits.TRISB8
//#define RS485_IN LATBbits.LATB8
#define RS485_OUT_TRIS TRISBbits.TRISB9
#define RS485_OUT LATBbits.LATB9

/*************************************
Function: RS485_Init 
Description: 485ͨѶ��ʼ��
Input: �� 
Output: ��
 *************************************/
void RS485_Init(void) {

    U1MODEbits.UARTEN = 1; //ʹ�ܴ���
    U1MODEbits.BRGH = 0; //16
    U1BRG = 103; //16000000/9600/16-1

    U1MODEbits.PDSEL = 00; //����żУ��
    U1MODEbits.STSEL = 0; //1λֹͣλ
    U1MODEbits.USIDL = 0; //����ģʽ�¼�������
    U1MODEbits.WAKE = 1; //����״̬�¼�������
    //    U1MODEbits.UARTEN = 1; //ʹ�ܴ���
    U1STAbits.UTXEN = 0; //ʹ�ܷ��� ������ʹ�ܴ��� �ڷ�������
    U1STAbits.URXISEL = 3; //�� 4�������ַ����жϱ�־λ�� 1
    U1TXREG = 0;
    U1RXREG = 0;
    IPC2bits.U1RXIP = 7;
    IFS0bits.U1RXIF = 0; //��������ж�
    IEC0bits.U1RXIE = 1; //���������ж�
    IPC16bits.U1ERIP = 6;
    IFS4bits.U1ERIF = 0; //��������ж�
    IEC4bits.U1ERIE = 1; //���������ж�    
    U1STAbits.UTXEN = 1; //ʹ�ܷ��� ������ʹ�ܴ��� �ڷ�������

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
void RS485SendChar(const uint8_t dat) {
    RS485_CON = 1; //����
    U1TXREG = dat;
    while (!U1STAbits.TRMT); //while (!U2STAbits.TRMT);
    Delay10ms(1);
    RS485_CON = 0; //����
}

/*************************************
Function: RS485_SendString 
Description: 485�����ַ���
Input: �ַ��� �ַ������� 
Output: ��
 *************************************/
void RS485SendString(const uint8_t* dat, uint8_t bytes) {
    uint8_t count = 0;

    RS485_CON = 1; //����    
    //    Delay10ms(1);
    while (count < bytes) {
        U1TXREG = *(dat + count);
        while (!U1STAbits.TRMT);
        count++;
    }
    //    Delay1ms(10);//��һ����ʱ
    RS485_CON = 0; //����
    //    Delay10ms(1);
}

//#ifdef DEBUG_485_SEND_STR

/*************************************
Function: RS485_SendString 
Description: 485�����ַ���
Input: �ַ��� �ַ������� 
Output: ��
 *************************************/
void RS485SendString1(const uint8_t* dat) {
    uint8_t count = 0;

    RS485_CON = 1; //����    
    Delay100ms(1);
    while (dat[count] != '\0') {
        U1TXREG = *(dat + count);
        while (!U1STAbits.TRMT);
        count++;
    }
    Delay100ms(1);
    RS485_CON = 0; //����
    Delay10ms(1);
    //    OSTimeDlyHMSM(0, 0, 0, 1);
}
//#endif
///*************************************
//Function: OpenRS485 
//Description: ��485ͨѶ
//Input: �ַ��� �ַ������� 
//Output: ��
// *************************************/
//void OpenRS485(void) {
//    IEC0bits.U1RXIE = 1;
//    U1STAbits.UTXEN = 1; //UARTx transmitter is enabled �رմ��������豸һ���ڹ���??????????
//}
//
///*************************************
//Function: RS485_SendString 
//Description: �ر�485ͨѶ
//Input: �ַ��� �ַ������� 
//Output: ��
// *************************************/
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
//    uint8_t dat='6';

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
bool RS485Receive(uint8_t* dat) {

    bool b = true;
//    uint8_t timeCount;
    
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



