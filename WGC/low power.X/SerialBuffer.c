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
        tmp = U2RXREG; //����������ݣ�����
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
    u8 first_cnt = 0; //��¼�ֽ���
    u8 cnt = 0, byte = 0;
    u8 UART_Tmp[200]; //��ʱ������������

    while (cnt < 20)
        UART_Tmp[cnt++] = 0; //void head=08
    cnt = 0;
    while (f_uart(UART_Tmp + cnt++))
        if (cnt >= 200) break; //��ȡ���� +1
    byte = cnt - 1; //��ȥ�����һ���ֽ�  ����������
    for (first_cnt = 0; first_cnt < byte; first_cnt++) { //�������в���֡ͷ
        if (*(UART_Tmp + first_cnt) == *head) {//Ѱ��֡ͷ�ĵ�һ������
            for (cnt = 0; cnt < head_size; cnt++) {//�ж�һ��֡ͷ����
                if (*(UART_Tmp + first_cnt + cnt) != *(head + cnt))
                    break; //�������û����ȷ��������ǰѭ��
                else if (cnt == head_size - 1) {//��ȷ�Ļ�����������
                    if (get_size <= byte)//��ȡ��Ч�ֽ�����
                        byte = get_size;
                    for (cnt = 0; cnt < byte; cnt++)//��ֵ
                        *(Get_Source + cnt) = *(UART_Tmp + first_cnt + cnt);
                    return byte;
                }
            }
        }
    }
    return 0;
}


