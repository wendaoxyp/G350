//#include "user.h"
//#include "string.h"
//#include "p24FV32KA301.h"
#include "SerialBuffer.h"

/**********************************����****************************************/
#define BUFFERMAX 64
//static uint8_t Buffer_uart1[BUFFERMAX];
uint8_t Buffer_uart1[BUFFERMAX];
static uint8_t bufferWptr_uart1 = 0;
static uint8_t bufferRptr_uart1 = 0;

//static uint8_t Buffer_uart2[BUFFERMAX];
uint8_t Buffer_uart2[BUFFERMAX];
/*static*/ uint8_t bufferWptr_uart2 = 0;
/*static*/ uint8_t bufferRptr_uart2 = 0;

/*************************************
Function: BufferWrite 
Description: д���ݵ����λ�����
Input: ���ںţ�1��2 
Output: ��
 *************************************/
void BufferWrite_UART1(void) {
    uint8_t tmp;
    if (bufferWptr_uart1 == (bufferRptr_uart1 - 1)) {//������������� д���ٶȱȶ����ٶȿ�
        tmp = U1RXREG; //����������ݣ�����
        return;
    }
    Buffer_uart1[bufferWptr_uart1] = U1RXREG;
    bufferWptr_uart1++;
    bufferWptr_uart1 = bufferWptr_uart1 - ((bufferWptr_uart1 >> 6) << 6);
}

/*************************************
Function: BufferWrite 
Description: д���ݵ����λ�����
Input: ���ںţ�1��2 
Output: ��
 *************************************/
void BufferWrite_UART2(void) {
    uint8_t tmp = 0;
    if (bufferWptr_uart2 == (bufferRptr_uart2 - 1)) {//������������� д���ٶȱȶ����ٶȿ�
        tmp = U2RXREG; //����������ݣ�����
        return;
    }
    Buffer_uart2[bufferWptr_uart2] = U2RXREG;
    bufferWptr_uart2++;
    bufferWptr_uart2 = bufferWptr_uart2 - ((bufferWptr_uart2 >> 6) << 6); //bufferWptr_uart2%BUFFERMAX
}

/*************************************
Function:  BufferRead
Description: �����λ�����
Input: ���ݵ�ַ 
Output: 1����ȡ�ɹ���0����ȡʧ��
 *************************************/
bool BufferRead_UART1(uint8_t *data) {
    if (bufferRptr_uart1 == bufferWptr_uart1) {
        return 0;
    }
    *data = Buffer_uart1[bufferRptr_uart1];
    bufferRptr_uart1++;
    bufferRptr_uart1 = bufferRptr_uart1 - ((bufferRptr_uart1 >> 6) << 6); //bufferRptr_uart1 % BUFFERMAX; 
    return 1;
}

/*************************************
Function:  BufferRead
Description: �����λ�����
Input: ���ݵ�ַ 
Output: 1����ȡ�ɹ���0����ȡʧ��
 *************************************/
bool BufferRead_UART2(uint8_t *data) {
    if (bufferRptr_uart2 == bufferWptr_uart2) {
        if (U2STAbits.OERR)
            U2STAbits.OERR = 0; //д����������FIFO�������û���������������û��
        return 0;
    }
    *data = Buffer_uart2[bufferRptr_uart2];
    bufferRptr_uart2++;
    bufferRptr_uart2 = bufferRptr_uart2 - ((bufferRptr_uart2 >> 6) << 6);
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
uint8_t UARTIsGet(UARTn f_uart, uint8_t*Get_Source, const uint8_t get_size, const uint8_t *head, const uint8_t head_size) {//ע��'\0'
    bool IsFind = false; //��¼�ֽ���
    uint8_t cnt = 0, byte = 0;
    uint8_t UART_Tmp = 0; //��ʱ������������
    //    uint8_t UART_Tm[10];

    while (f_uart(&UART_Tmp)) {//��ȡһ������
        if (UART_Tmp == *head) {//�������==head�Ļ�
            //            UART_Tm[0] = UART_Tmp;
            for (cnt = 1; cnt < head_size; cnt++) {//��ȡ֡ͷ�����ݳ���
                f_uart(&UART_Tmp);
                if (UART_Tmp == *(head + cnt)) {//�����ȡ�����ݺ�֡ͷһ������ô������ȡ���ݣ���֮�˳�
                    IsFind = true;
                    continue;
                } else {
                    IsFind = false;
                    break;
                }
            }
        }
        if (IsFind) break; //����ҵ����ݣ��˳�Ѱ��֡ͷ����
    }
    if (!get_size && IsFind)
        return 0xFF; //��ʾ�ҵ�
    else if (IsFind) {//������ڽ��ܵ��ֽ������ҵ�֡ͷ
        byte = (get_size < head_size) ? get_size : head_size; //��ȡ�ֽ�С��У���ֽ�
        for (cnt = 0; cnt < byte; cnt++) //��ȡ֡ͷ����
            *(Get_Source + cnt) = *(head + cnt);
        for (cnt = head_size; cnt < get_size; cnt++) //��ȡʣ������
            if (!f_uart(Get_Source + byte++))
                break;
    }
    return byte;
}

void ClearBuffer2(void) {
    uint8_t tmp;
    while (BufferRead_UART2(&tmp));
}
