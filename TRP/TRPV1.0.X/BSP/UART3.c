//#include "includes.h"
#include "UART3.h"
#include <xc.h>

void UART3_Init(void) {
    TRISGbits.TRISG8 = 1; //����Ϊ����
    TRISGbits.TRISG7 = 0; //����Ϊ���
    ANSGbits.ANSG7 = 0; //�Ѿ�Ϊ���ֶ˿�
    ANSGbits.ANSG8 = 0;
    ODCGbits.ODG8 = 1; //©����·���
    //    TRISDbits.TRISD3 = 1; //����Ϊ����
    //    TRISDbits.TRISD2 = 0; //����Ϊ���

    U3MODEbits.BRGH = 0; //������ʹ�ñ�׼ģʽ1:16
    U3BRG = 0x19; //19200 103; //16000000/9600/16-1
    U3MODEbits.PDSEL = 00; //����żУ��
    U3MODEbits.STSEL = 0; //1λֹͣλ

    U3MODEbits.UARTEN = 1; //ʹ�ܴ���

    U3STAbits.URXISEL = 3; //�� 4 �������ַ����жϱ�־λ�� 1
    IFS5bits.U3RXIF = 0; //��������ж�  
    IPC20bits.U3RXIP = 6;
    IEC5bits.U3RXIE = 1; //���������ж�
    IFS5bits.U3ERIF = 0;
    IPC20bits.U3ERIP = 7;
    IEC5bits.U3ERIE = 1;
    U3STAbits.UTXEN = 1; //ʹ�ܷ��� ������ʹ�ܴ��� �ڷ�������
}

void UART3_Open(void) {
    U3MODEbits.UARTEN = 1; //ʹ�ܴ���
    U3STAbits.UTXEN = 1; //ʹ�ܷ��� ������ʹ�ܴ��� �ڷ�������
    // IEC1bits.U3TXIE=1;
    IEC5bits.U3RXIE = 1;
}

void UART3_Close(void) {
    // IEC1bits.U3TXIE=0;
    IEC5bits.U3RXIE = 0;
    U3STAbits.UTXEN = 1; //ʹ�ܷ��� ������ʹ�ܴ��� �ڷ�������
    U3MODEbits.UARTEN = 0; //ʹ�ܴ��ڷ���    
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

void U3Rx4Byte(void) {//��ȡ�ն��������󼸸����ݣ�ÿ4���ֽ��ж�
    uint8_t cnt;
    for (cnt = 0; cnt < 4; cnt++)//��������ĸ��ֽ�û�н��ܵ����ж�ԭ��
        if (U3STAbits.URXDA) //û�н��յ�
            BufferWrite_UART3();
}



