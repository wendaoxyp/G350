//#include "includes.h"
#include "UART2.h"

void UART2_Init(void) {
    //�Ѿ�Ϊ���ֶ˿ڣ�
    TRISDbits.TRISD2 = 1; //����Ϊ����
    TRISDbits.TRISD3 = 0; //����Ϊ���
    //    TRISDbits.TRISD3 = 1; //����Ϊ����
    //    TRISDbits.TRISD2 = 0; //����Ϊ���

    U2MODEbits.BRGH = 0; //������ʹ�ñ�׼ģʽ1:16
    U2BRG = 51; //19200 103; //16000000/9600/16-1
    U2MODEbits.PDSEL = 00; //����żУ��
    U2MODEbits.STSEL = 0; //1λֹͣλ

    U2MODEbits.UARTEN = 1; //ʹ�ܴ���

    U2STAbits.UTXEN = 1; //ʹ�ܷ��� ������ʹ�ܴ��� �ڷ�������
    U2STAbits.URXISEL = 3; //�� 4 �������ַ����жϱ�־λ�� 1
    IEC1bits.U2RXIE = 1; //���������ж�
    IFS1bits.U2RXIF = 0; //��������ж�
    IEC4bits.U2ERIE = 1;
    IFS4bits.U2ERIF = 0;
}

void UART2_Open(void) {
    U2MODEbits.UARTEN = 1; //ʹ�ܴ���
    U2STAbits.UTXEN = 1; //ʹ�ܷ��� ������ʹ�ܴ��� �ڷ�������
    // IEC1bits.U2TXIE=1;
    IEC1bits.U2RXIE = 1;
}

void UART2_Close(void) {
    // IEC1bits.U2TXIE=0;
    IEC1bits.U2RXIE = 0;
    U2STAbits.UTXEN = 1; //ʹ�ܷ��� ������ʹ�ܴ��� �ڷ�������
    U2MODEbits.UARTEN = 0; //ʹ�ܴ��ڷ���    
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

void U2Rx4Byte(void) {//��ȡ�ն��������󼸸����ݣ�ÿ4���ֽ��ж�
    uint8_t cnt;
    for (cnt = 0; cnt < 4; cnt++)//��������ĸ��ֽ�û�н��ܵ����ж�ԭ��
        if (U2STAbits.URXDA) //û�н��յ�
            BufferWrite_UART2();
}



