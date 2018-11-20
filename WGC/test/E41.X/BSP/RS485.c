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
    RS485_TRIS = 0; //���ƿ�����λ��� 485_CON
    RS485_IN_TRIS = 0; //����Ϊ����/
    RS485_OUT_TRIS = 1; //����Ϊ���
    __builtin_write_OSCCONL(OSCCON & 0xbf); // unlock PPS
    RPOR4bits.RP8R = 0x03; // B9->UART1:U1TX
    RPINR18bits.U1RXR = 0x09; // B8->UART1:U1RX 
    //    RPINR18bits.U1RXR = 0x08; // RB8->UART1:U1RX
    //    RPOR4bits.RP9R = 0x03; // RB9->UART1:U1TX
    __builtin_write_OSCCONL(OSCCON | 0x40); // lock   PPS
    ANSBbits.ANSB8 = 0; //��������
    ANSBbits.ANSB9 = 0;
    U1MODEbits.BRGH = 0; //16
    U1BRG = 51; //16000000/9600/16-1

    U1MODEbits.PDSEL = 00; //����żУ��
    U1MODEbits.STSEL = 0; //1λֹͣλ

    U1MODEbits.UARTEN = 1; //ʹ�ܴ���

    U1STAbits.UTXEN = 1; //ʹ�ܷ��� ������ʹ�ܴ��� �ڷ�������
//    U1STAbits.URXISEL = 3; //�� 4 �������ַ����жϱ�־λ�� 1
//    IEC0bits.U1RXIE = 1; //���������ж�
//    IFS0bits.U1RXIF = 0; //��������ж�
//    IEC4bits.U1ERIE = 1; //���������ж�
//    IFS4bits.U1ERIF = 0; //��������ж�
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
void RS485Send(const uint8_t dat) {
    RS485_CON = 1; //����
    OSTimeDlyHMSM(0, 0, 0, 10);
    U1TXREG = dat;
    while (!U1STAbits.TRMT); //while (!U2STAbits.TRMT);
    OSTimeDlyHMSM(0, 0, 0, 10);
    RS485_CON = 0; //����
    OSTimeDlyHMSM(0, 0, 0, 10);
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
    while (count < bytes) {
        U1TXREG = *(dat + count);
        while (U1STAbits.UTXBF);
        count++;
    }
    OSTimeDlyHMSM(0, 0, 0, 10);
    RS485_CON = 0; //����
    OSTimeDlyHMSM(0, 0, 0, 10);
}

/*************************************
Function: OpenRS485 
Description: ��485ͨѶ
Input: �ַ��� �ַ������� 
Output: ��
 *************************************/
void OpenRS485(void) {
    IEC0bits.U1RXIE = 1;
    U1STAbits.UTXEN = 1; //UARTx transmitter is enabled �رմ��������豸һ���ڹ���??????????
}

/*************************************
Function: RS485_SendString 
Description: �ر�485ͨѶ
Input: �ַ��� �ַ������� 
Output: ��
 *************************************/
void CloseRS485(void) {
    IEC0bits.U1RXIE = 0;
    U1STAbits.UTXEN = 0; //UARTx transmitter is enabled �رմ��������豸һ���ڹ���??????????
}
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


