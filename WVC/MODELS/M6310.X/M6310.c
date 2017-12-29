/*************************************************
Copyright (C), 1988-1999, Tech. Co., Ltd.
File name: M6310.c
Author: xx13
Version: 1.0
Date: 2017/12/29
Description: ͨ�� API����
Others: ��Ҫ�õ��Զ����
History: None
1. Date:
Author:
Modification:
2. ...
 *************************************************/


/***************************************************************************
 * Includes
 ***************************************************************************/
#include "M6310.h"
#include <string.h>
#include <stdlib.h>
#include  <libq.h>
#include "mcc_generated_files/mcc.h"
#include "Common.h"


/***************************************************************************
 * Definitions
 ***************************************************************************/
const uint8_t D0[] = {"AT&D0\r\n"}; //{"AT&K3\r\n"};
const uint8_t AT[] = {"AT\r\n"};
const uint8_t QIURC[] = {"AT+QIURC=0\r\n"}; //AT+QIURC
const uint8_t CREG_2[] = {"AT+CREG=2\r\n"};
const uint8_t OK[] = {"OK"};
const uint8_t CPIN[] = {"AT+CPIN?\r\n"};
const uint8_t READY[] = {"+CPIN: READY"};
const uint8_t CIMI[] = {"AT+CIMI\r\n"};
const uint8_t CREG[] = {"AT+CREG?\r\n"};
const uint8_t CGREG[] = {"AT+CGREG?\r\n"};
const uint8_t CGATT[] = {"AT+CGATT?\r\n"};
const uint8_t _5[] = {",5"};
const uint8_t _1[] = {",1"};
const uint8_t QICSGP[] = {"AT+QICSGP=1,\"CMNET\"\r\n"};
const uint8_t QIMODE[] = {"AT+QIMODE=1\r\n"};
const uint8_t QITCFG[] = {"AT+QITCFG=3,2,512,1\r\n"};
const uint8_t KTCPSTART[] = {"AT+KTCPSTART=1\r\n"};
const uint8_t CONNECT[] = {"CONNECT OK"};
const uint8_t SEND[] = {"SEND"};
const uint8_t QICLOSE[] = {"AT+QICLOSE\r\n"}; //AT+QICLOSE 
const uint8_t CLOSE[] = {"CLOSE OK\r\n"};


/***************************************************************************
 * Prototypes
 ***************************************************************************/
extern void UART1_SendString(uint8_t* tmp);
extern void U1Rx4Byte(void);
static bool M6310SendCmd(const uint8_t *ss, const uint8_t* cs1, const uint8_t csl, const uint8_t cnt);

/***************************************************************************
 * Variables
 ***************************************************************************/
uint8_t QIOPEN[] = {"AT+QIOPEN=\"TCP\",\"183.246.74.68\",\"5070\"\r\n"};


/***************************************************************************
 * Code 
 ***************************************************************************/

/***************************************************************************
Function: M6310_Init
Description: ��ʼ��M6310�Ŀ���IO��
Input: void
Output: void
Return: void
Others: none
 ***************************************************************************/
void M6310_Init(void) {
    //��ʼ��IO
}

/***************************************************************************
Function: OpenM6310
Description: ͨ��IO�ڴ�6310
Input: void
Output: void
Return: void
Others: none
 ***************************************************************************/
void OpenM6310(void) {//��������ʹ��UART1�Ľ���������Ҫ
    PWRKEY_SetHigh();
    GPRS_EN_SetHigh();
}

/***************************************************************************
Function: CloseM6310
Description: ͨ��IO�ر�M6310
Input: void
Output: void
Return: void
Others: none
 ***************************************************************************/
void CloseM6310(void) {//��������ʹ��UART1�Ľ���������Ҫ
    PWRKEY_SetLow();
    GPRS_EN_SetLow();
}

/***************************************************************************
Function: M6310_AT_Close
Description:ͨ��ATָ��ر�M6310
Input: void
Output: void
Return: ture:close success ;false:close��fail
Others: none
 ***************************************************************************/
bool M6310_AT_Close(void) {
    uint8_t sta;
    ClrUART1Buf();
    sta = M6310SendCmd(QICLOSE, CLOSE, 8, 2); //close tcp and return result
    return sta;
}

/***************************************************************************
Function: M6310_DialingIsERR
Description: M6310��ʼ���ţ�������M6310��״̬
Input: void
Output: void
Return: M6310��״̬
Others: none
 ***************************************************************************/
M6310_STA M6310_DialingIsERR(void) {
    M6310_STA sta;
    uint8_t tmp[50], length = 0;
    Delay1s(2);

    if (M6310SendCmd(AT, OK, 2, 2)) {
        ClrUART1Buf();
        if (M6310SendCmd(D0, OK, 2, 2)) {
            ClrUART1Buf();
            if (M6310SendCmd(QIURC, OK, 2, 2)) {
                ClrUART1Buf();
                if (M6310SendCmd(CPIN, READY, 8, 2)) {
                    ClrUART1Buf();
                    if (M6310SendCmd(CREG, _5, 2, 10)) {//��������ģʽ
                        ClrUART1Buf();
                        //M6310_GetIP_Port(); //ˢ��IP��ַ�Ͷ˿ں�
                        if (M6310SendCmd(QICSGP, OK, 2, 3)) {
                            ClrUART1Buf();
                            if (M6310SendCmd(QIOPEN, OK, 2, 5)) {
                                Delay1s(2); //�ж��Ƿ���ܵ�CONNECT OK   
                                U1Rx4Byte();
                                length = UARTGetData(BufferRead_UART1, tmp, 50); //Ϊʲô�ͻ�ȡ��9���ֽ�
                                if (length && Str_Find_Head(tmp, (const uint8_t *) "CONNECT OK", length, 10))
                                    sta = M6310_Daling_OK;
                                else
                                    sta = M6310_Daling_Ser_Socket_Fail;
                                ClrUART1Buf();
                            } else
                                sta = M6310_Daling_Socket_Fail;
                        } else
                            sta = M6310_Daling_APN_Fail;
                    } else
                        sta = M6310_Daling_Find_Net_Fail;
                } else
                    sta = M6310_Daling_SIM_Fail;
            } else
                sta = M6310_Daling_URC_Fail;
        } else
            sta = M6310_Daling_Serial_Control_Fail;
    } else
        sta = M6310_Daling_Broken_Fail;

    return sta;
}

/***************************************************************************
Function: M6310_Send
Description: �������ݸ�M6310
Input: arg��������
Output: void
Return: M6310״̬
Others: none
 ***************************************************************************/
M6310_STA M6310_Send(uint8_t * arg) {//, uint8_t byte) {
    uint8_t buf[64]; //use for uart1 buf
    uint8_t pos = 0;

    //    UART1_SendString(byte);//�ж��ֽڴ�С
    UART1_SendString((uint8_t*) "AT+QISEND=10\r\n");
    //    UART1_SendChar('<');    
    Delay1s(1); //at least 300ms waiting for M6310 Get AT Command
    UART1_SendString((uint8_t*) arg); //����ATָ�� 
    Delay1s(1); //at least 300ms waiting for ACK    
    //Get UART1 Data  and Find
    UARTGetData(BufferRead_UART1, buf, sizeof (buf));
    pos = Str_Find_Head((const uint8_t *) buf, (const uint8_t *) "SEND", sizeof (buf), 4); //
    if (pos) //if get SEND
    {
        if (Str_Find_Head((const uint8_t *) buf + pos, (const uint8_t *) "OK", sizeof (buf) - pos, 2))
            return M6310_SEND_OK; // M6310_SEND_OK
        else if (Str_Find_Head((const uint8_t *) buf + pos, (const uint8_t *) "FAIL", sizeof (buf) - pos, 4))
            return M6310_SEND_FAIL; // M6310_SEND_FAIL
        else
            return M6310_SEND_NO_BACK; // M6310_SEND_NO_BACK
    } else
        return M6310_SEND_ERR_NO_RECEIVE; //M6310_SEND_ERR_NO_RECEIVE;
}


/*��������������ַ�����ַss�������ַ���cs���Ա��ַ���csl���Ա��ַ�������csl�����ʹ���cnt**/
/***************************************************************************
Function: M6310SendCmd
Description: ����AT�����M6310
Input: ss(�������ݵ�ַ);cs(�Ա����ݵ�ַ);csl(�Ա����ݳ���);cnt(��������)
Output: void
Return: true:���ͳɹ���false:����ʧ��
Others: none
 ***************************************************************************/
static bool M6310SendCmd(const uint8_t *ss, const uint8_t* cs, const uint8_t csl, const uint8_t cnt) {
    uint8_t send_cnt = 0; //, find_cnt = 0; //, length = 0, get_bytes = 0;
    bool b_sta = false;
    uint8_t tmp[50]; //ATE exist AT Command depend on max size

    if (!csl || !cnt)//�����������Ϊ0�Ļ�
        return false;

    ClearDat(tmp, 0xff, 50); //���������

    do {
        send_cnt += 1;
        UART1_SendString((uint8_t*) ss); //����ATָ��        
        Delay1s(4); //��ʱһ��ʱ��
        U1Rx4Byte(); //��ȡ���4���ֽ�
        while (BufferRead_UART1(tmp)&&!b_sta) {//����л�ȡ������
            if (Str_Find_Head(tmp, cs, 1, 1)) {//�жϵ�һ���ֽ�
                Delay1s(2); //(0, 0, 3, 0); ��������CONNECT���ݶ�ʧ
                if (csl == 1)//����жϵ��ַ�����Ϊ1�Ļ�����ֱ�ӷ���1����֮����ȡֵ���ж�
                    b_sta = true;
                else {
                    if (UARTGetData(BufferRead_UART1, tmp + 1, csl - 1) == csl - 1) {
                        if (Str_Find_Head(tmp, cs, csl, csl)) //�ж��ַ��Ƿ�����                            
                            b_sta = true;
                        else
                            b_sta = false;
                    }
                }
            }
        }
        if (b_sta)
            break;
    } while (cnt > send_cnt);
    return b_sta;
}



