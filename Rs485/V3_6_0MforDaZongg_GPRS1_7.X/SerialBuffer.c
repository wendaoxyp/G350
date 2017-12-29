#include "user.h"
#include "string.h"
//#include "p24FV32KA301.h"

/**********************************����****************************************/
#define BUFFERMAX 256
//static u8 Buffer_uart1[BUFFERMAX];
u8 Buffer_uart1[BUFFERMAX];
static u8 bufferWptr_uart1 = 0;
static u8 bufferRptr_uart1 = 0;

//static u8 Buffer_uart2[BUFFERMAX];
u8 Buffer_uart2[BUFFERMAX];
/*static*/ u8 bufferWptr_uart2 = 0;
/*static*/ u8 bufferRptr_uart2 = 0;

/*************************************
Function: BufferWrite 
Description: д���ݵ����λ�����
Input: ���ںţ�1��2 
Output: ��
 *************************************/
void BufferWrite_UART1(void) {
    u8 tmp;
    if (bufferWptr_uart1 == (bufferRptr_uart1 - 1)) {//������������� д���ٶȱȶ����ٶȿ�
        tmp = U1RXREG; //����������ݣ�����
        return;
    }
    Buffer_uart1[bufferWptr_uart1] = U1RXREG;
    bufferWptr_uart1++;
    bufferWptr_uart1 = bufferWptr_uart1 - ((bufferWptr_uart1 >> 8) << 8);
    //bufferWptr_uart1 % BUFFERMAX; //bufferWptr_uart1 - (bufferWptr_uart1 >> 8) << 8; //// X - (X >> n) << n ȡ����
    //    if (bufferWptr_uart1 >= 6)
    //        Nop();
}

/*************************************
Function: BufferWrite 
Description: д���ݵ����λ�����
Input: ���ںţ�1��2 
Output: ��
 *************************************/
void BufferWrite_UART2(void) {
    u8 tmp = 0;
    if (bufferWptr_uart2 == (bufferRptr_uart2 - 1)) {//������������� д���ٶȱȶ����ٶȿ�
        tmp = U2RXREG; //����������ݣ�����
        return;
    }
    Buffer_uart2[bufferWptr_uart2] = U2RXREG;
    bufferWptr_uart2++;
    bufferWptr_uart2 = bufferWptr_uart2 - ((bufferWptr_uart2 >> 8) << 8); //bufferWptr_uart2%BUFFERMAX
    //X - (X >> n) << n ȡ����bufferWptr_uart2 - (bufferWptr_uart2 >> 8) << 8; 
}

/*************************************
Function:  BufferRead
Description: �����λ�����
Input: ���ݵ�ַ 
Output: 1����ȡ�ɹ���0����ȡʧ��
 *************************************/
bool BufferRead_UART1(u8 *data) {
    if (bufferRptr_uart1 == bufferWptr_uart1) {
        return 0;
    }
    *data = Buffer_uart1[bufferRptr_uart1];
    bufferRptr_uart1++;
    bufferRptr_uart1 = bufferRptr_uart1 - ((bufferRptr_uart1 >> 8) << 8); //bufferRptr_uart1 % BUFFERMAX; 
    //bufferRptr_uart1 - (bufferRptr_uart1 >> 8) << 8; // // X - (X >> n) << n ȡ����
    return 1;
}

/*************************************
Function:  BufferRead
Description: �����λ�����
Input: ���ݵ�ַ 
Output: 1����ȡ�ɹ���0����ȡʧ��
 *************************************/
bool BufferRead_UART2(u8 *data) {
    if (bufferRptr_uart2 == bufferWptr_uart2) {
        if (U2STAbits.OERR)
            U2STAbits.OERR = 0; //д����������FIFO�������û���������������û��
        return 0;
    }
    *data = Buffer_uart2[bufferRptr_uart2];
    bufferRptr_uart2++;
    bufferRptr_uart2 = bufferRptr_uart2 - ((bufferRptr_uart2 >> 8) << 8);
    //bufferRptr_uart2 % BUFFERMAX;//bufferRptr_uart2-(bufferRptr_uart2>>8)<<8;
    return 1;
}

/*************************************
Function: UARTnDataIsGet  
Description: deadlineʱ���ڣ��Ӵ��ڻ�����ȡbytes���ֽ����ݣ��ж�֡ͷhead 
 * У�鷽ʽ ֡ͷ+CRC16
Input: 
Output: �Ƿ��ȡ������
Notice���ֽ������ܴ���256 ȡ���ݵ�ʱ����ܶ�   
 *************************************/
u8 UARTIsGet(UARTn f_uart, u8*Get_Source, const u8 get_size, const u8 *head, const u8 head_size) {//ע��'\0'
    bool IsFind = false; //��¼�ֽ���
    u8 cnt = 0, byte = 0;
    u8 UART_Tmp = 0; //��ʱ������������
    u8 UART_Tm[10];

    while (f_uart(&UART_Tmp)) {//��ȡһ������
        if (UART_Tmp == *head) {//�������==head�Ļ�
            UART_Tm[0] = UART_Tmp;
            for (cnt = 1; cnt < head_size; cnt++)
                f_uart(UART_Tm + cnt);
            if (ValueIsEqual(head, UART_Tm, head_size)) {
                IsFind = true;
                break;
            }
        }
    }
    if (IsFind) {
        byte = head_size;
        for (cnt = 0; cnt < head_size; cnt++)//��ȡ֡ͷ����
            *(Get_Source + cnt) = UART_Tm[cnt];
        for (cnt = head_size; cnt < get_size; cnt++) //��ȡʣ������
            if (!f_uart(Get_Source + byte++))
                break;
    }
    return byte;
}


