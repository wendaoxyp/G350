//#include "user.h"
//#include "string.h"
//#include "p24FV32KA301.h"
#include "SerialBuffer.h"

/**********************************����****************************************/
#define BUFFERMAX 64
//static uint8_t Buffer_uart1[BUFFERMAX];
uint8_t Buffer_uart1[BUFFERMAX];
/*static*/ uint8_t bufferWptr_uart1 = 0;
/*static */uint8_t bufferRptr_uart1 = 0;

//static uint8_t Buffer_uart2[BUFFERMAX];
uint8_t Buffer_uart2[BUFFERMAX];
/*static*/ uint8_t bufferWptr_uart2 = 0;
/*static*/ uint8_t bufferRptr_uart2 = 0;

uint8_t Buffer_uart3[BUFFERMAX];
/*static*/ uint8_t bufferWptr_uart3 = 0;
/*static*/ uint8_t bufferRptr_uart3 = 0;

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
Function: BufferWrite 
Description: д���ݵ����λ�����
Input: ���ںţ�1��2 
Output: ��
 *************************************/
void BufferWrite_UART3(void) {
    uint8_t tmp = 0;
    if (bufferWptr_uart3 == (bufferRptr_uart3 - 1)) {//������������� д���ٶȱȶ����ٶȿ�
        tmp = U3RXREG; //����������ݣ�����
        return;
    }
    Buffer_uart3[bufferWptr_uart3] = U3RXREG;
    bufferWptr_uart3++;
    bufferWptr_uart3 = bufferWptr_uart3 - ((bufferWptr_uart3 >> 6) << 6); //bufferWptr_uart3%BUFFERMAX
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
Function:  BufferRead
Description: �����λ�����
Input: ���ݵ�ַ 
Output: 1����ȡ�ɹ���0����ȡʧ��
 *************************************/
bool BufferRead_UART3(uint8_t *data) {
    if (bufferRptr_uart3 == bufferWptr_uart3) {
        if (U3STAbits.OERR)
            U3STAbits.OERR = 0; //д����������FIFO�������û���������������û��
        return 0;
    }
    *data = Buffer_uart3[bufferRptr_uart3];
    bufferRptr_uart3++;
    bufferRptr_uart3 = bufferRptr_uart3 - ((bufferRptr_uart3 >> 6) << 6);
    //bufferRptr_uart3 % BUFFERMAX;//bufferRptr_uart3-(bufferRptr_uart3>>8)<<8;
    return 1;
}

/*************************************
Function: UARTDataIsRight
Description: ���ݽṹ������ݻ�ȡ��Ч���ݺ���Ч����
Input: ���ݽṹ��
Output: �Ƿ��ȡ������
Notice���ֽ������ܴ���256 ȡ���ݵ�ʱ����ܶ�   
 *************************************/
bool UARTDataIsRight(StrCmp * strcmp) {//ע��
    bool IsFind = false; //��¼�ֽ���
    uint8_t cnt = 0/*У��Ѱ��ѭ����ַ*/, cnt1 = 0/*У���ж�ѭ����ַ*/, cnt2/*��ֵ��ַ*/, /*offset,*/ byte = 0;

    if (!(strcmp->Check_len) || !(strcmp->Source_len))//������õ��ֽ���Ϊ0�Ļ������ش���
        return false; //Ϊ��ȡ

    while (cnt < strcmp->Source_len) {
        if (*(strcmp->SourceData + cnt) == *(strcmp->CheckData)) {//�������==head�Ļ�           
            for (cnt1 = 1; cnt1 < strcmp->Check_len; cnt1++) {//��ȡ֡ͷ�����ݳ���               
                if (*(strcmp->SourceData + cnt + cnt1) == *(strcmp->CheckData + cnt1)) {//�����ȡ�����ݺ�֡ͷһ������ô������ȡ���ݣ���֮�˳�
                    IsFind = true;
                    continue;
                } else {
                    IsFind = false;
                    break;
                }
            }
        }
        if (IsFind) break; //����ҵ����ݣ��˳�Ѱ��֡ͷ����
        cnt++; //У��λ�ü�1
    }

    if (IsFind) {//������ڽ��ܵ��ֽ������ҵ�֡ͷ
        if (strcmp->Get_len < strcmp->Check_len) {
            byte = strcmp->Get_len; //��ȡ�ֽ�С��У���ֽ�,����ֻ��ҪУ�鲻��Ҫ��ȡ����
            for (cnt2 = 0; cnt2 < byte; cnt2++) //��ȡ֡ͷ����
                *(strcmp->GetData + cnt2) = *(strcmp->CheckData + cnt2);
        } else {//���Ҫ��ȡ���ֽ�������֡ͷ���ݣ���Ҫ�ж���Ч��ʣ���ֽ�������
            if (strcmp->Source_len - cnt < strcmp->Get_len)//�����ȡ���ݴ�����Ч���ݣ�
                for (cnt2 = 0; cnt2 < strcmp->Source_len - cnt; cnt2++) //��ȡʣ������
                    *(strcmp->GetData + cnt2) = *(strcmp->SourceData + cnt + cnt2);
            else
                for (cnt2 = 0; cnt2 <= strcmp->Get_len; cnt2++) //��ȡʣ������
                    *(strcmp->GetData + cnt2) = *(strcmp->SourceData + +cnt + cnt2);
        }
        strcmp->Real_len = cnt2; //ʵ�ʻ�ȡ���ĳ���
        return true;
    }
    strcmp->Real_len = 0;
    return false;
}

/*************************************
Function: UARTGetData  
Description: ͨ��ָ�����ڻ�ȡ��������ȡ���ݱ��������ݵ�ַ
Input: UARTn��ȡ��������ȡ���ݵĵ�ַ
Output: �ֽ���
Notice���ֽ������ܴ���256    
 *************************************/
uint8_t UARTGetData(UARTn f_uart, uint8_t*Get_Data, uint8_t bytes) {//, const uint8_t get_size) {//ע��'\0'
    uint8_t byte = 0;
    while (bytes > byte) {
        if (f_uart(Get_Data + byte))
            byte++;
        else
            break;
    }
    return byte;
}

/*************************************
Function: ClearBuffer
Description: �������������
Input: ָ������Ĵ���
Output: ��
Notice��������ڻ�����
 *************************************/
void ClearBuffer(UARTn f_uart) {
    uint8_t tmp;
    while (f_uart(&tmp));
}
//��UARTGetData��

//bool UARTIsGet(UARTn f_uart, uint8_t*Get_Source, const uint8_t get_size, const uint8_t *head, const uint8_t head_size) {
//    StrCmp stcp;
//    uint8_t Source_tmp[50]; //��ʱ����
//    //    bool b = false;
//
//    stcp->Source_len = UARTGetData(f_uart, Source_tmp);
//    if (stcp->Source_len>sizeof (Source_tmp) / sizeof (uint8_t))//���ƴ������βɼ����ݴ���50���ֽڣ��������50���ֽڣ���ô����Ϊ50���ֽ�
//        stcp->Source_len = 50;
//    stcp->SourceData = Source_tmp;
//    stcp->CheckData = head;
//    stcp->Check_len = head_size;
//    stcp->GetData = Get_Source;
//    stcp->Get_len = get_size;
//
//    return UARTDataIsRight(stcp);
//}



