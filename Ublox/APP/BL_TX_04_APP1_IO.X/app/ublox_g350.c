
/***************************************************************************
 * Includes
 ***************************************************************************/
//#include "ublox_g350.h"
#include "TX04.h"
#include "G350_AT_Command.h"
#include <ctype.h>
//#include <stdlib.h>
#include "DefType.h"
#include "SerialBuffer.h"
#include "Common.h"
#include "TX04_Conf.h"
#include "UART1.h"
#include "UART2.h"


/***************************************************************************
 * Definitions
 ***************************************************************************/
GPRS_Arg G350_Arg;
typedef Bool(*GetModuleArg_pf)(char *dat, uint8_t dat_bytes);

/***************************************************************************
 * Variables
 ***************************************************************************/
extern volatile Bool gSMSInfo;

/***************************************************************************
 * Prototypes
 ***************************************************************************/

/***************************************************************************
 * Code 
 ***************************************************************************/

/***************************************************************************
 * Function: Get_UDP_Rec_Data 
 * Description: ͨ�ýӿ�:��?�Ƿ���ע��ɹ������أ�Զ�̶���ʵ��
 * Input: �жϵ�Դ���ݣ�Դ�����ֽ���
 * Output: �Ƿ��ȡ��
 * Return: True:��ȡ�����������ݣ�False:��ȡʧ��
 * Others: none
 ***************************************************************************/
//static Bool Get_UDP_Rec_Data(char *dat, uint8_t dat_bytes) {
//    uint8_t check_bytes = StrLen(Rec_URC), get_pos = 0, end_pos = 0;
//    Bool sta = False;
//    //    uint8_t tmp[6], getsize, offset;
//    uint8_t headpos_real, endpos_real, readnum_real, offset;
//    char port[8] = {'"', ',', 0, 0, 0, 0, 0, 0}, port_size;
//
//    port_size = my_itoa(RunArg.Port, ((uint8_t*) port + 2));
//
//    get_pos = Str_Find_Head(dat, Rec_URC, dat_bytes, check_bytes); //��ȡ+USORF:
//    if (get_pos) {//�ж��Ƿ��ȡ��ͷ���� 
//        end_pos = Str_Find_Head(dat + get_pos, _r_n, dat_bytes, 2) - 1;
//        if (end_pos) {
//            headpos_real = Str_Find_Head(dat, port, dat_bytes, port_size + 2); //��ȡ�˿ںŵ�λ��
//            offset = headpos_real - 1;
//            endpos_real = Str_Find_Head(dat + offset, ",\"", dat_bytes - offset, 2); //�ж���Ч���� 
//            offset += port_size + 3;
//            readnum_real = G350_Arg.UDP_BYTES = my_atoi((uint8_t*) dat + offset, endpos_real - 8); //ʵ�ʻ�ȡ�����ֽ���
//            offset += endpos_real - 6;
//            CopyDat(dat, dat + offset, readnum_real);
//        }
//    }
//    return sta;
//}

/***************************************************************************
 * Function: Get_UDP_Rec_Byte 
 * Description: ͨ�ýӿ�:��?�Ƿ���ע��ɹ������أ�Զ�̶���ʵ��
 * Input: �жϵ�Դ���ݣ�Դ�����ֽ���
 * Output: �Ƿ��ȡ��
 * Return: True:��ȡ�ɹ���False:��ȡʧ�� ���ݿ�ȫ�ֱ���UDP_BYTES
 * Others: none
 ***************************************************************************/
static Bool Get_UDP_Rec_Byte(char *dat, uint8_t dat_bytes) {
    uint8_t check_bytes = StrLen(Rec_URC), get_pos = 0, end_pos = 0;
    Bool sta = False;
    uint8_t tmp[6], getsize;


    get_pos = Str_Find_Head(dat, Rec_URC, dat_bytes, check_bytes); //��ȡ+USORF:
    if (get_pos) {//�ж��Ƿ��ȡ��ͷ���� 
        end_pos = Str_Find_Head(dat + get_pos, _r_n, dat_bytes, 2); //�ж��Ƿ��ȡ��β���� 
        if (end_pos) {
            check_bytes += 3;
            getsize = end_pos - check_bytes;
            check_bytes += get_pos - 1;
            CopyDat(tmp, dat + check_bytes, getsize); //��ȡ20���ֽ�
            G350_Arg.UDP_BYTES = my_atoi(tmp, getsize); //�ַ���ת��Ϊ����
            sta = True;
        }
    }
    return sta;
}

/***************************************************************************
 * Function: Check_CREG 
 * Description: ͨ�ýӿ�:��?�Ƿ���ע��ɹ������أ�Զ�̶���ʵ��
 * Input: �жϵ�Դ���ݣ�Դ�����ֽ���
 * Output: �Ƿ��ȡ��
 * Return: True:��ȡ�����������ݣ�False:��ȡʧ��
 * Others: none
 ***************************************************************************/
static Bool Check_CREG(char *dat, uint8_t dat_bytes) {
    uint8_t check_bytes = StrLen(Rec_CREG_1), get_pos = 0, get_bytes = sizeof (G350_Arg.LAC);
    Bool sta = False;

    get_pos = Str_Find_Head(dat, Rec_CREG_5, dat_bytes, check_bytes); //��ȡICCIDλ��
    if (get_pos) {//�ж��Ƿ���CREG:1  
        CopyDat(G350_Arg.LAC, dat + get_pos + check_bytes, get_bytes); //��ȡ20���ֽ�
        sta = True;
    } else {
        get_pos = Str_Find_Head(dat, Rec_CREG_1, dat_bytes, check_bytes); //�ж��Ƿ���CREG:5
        if (get_pos) {
            CopyDat(G350_Arg.LAC, dat + get_pos + check_bytes, get_bytes); //��ȡ20���ֽ�
            sta = True;
        }
    }
    return sta;
}

/***************************************************************************
 * Function: GetModule_CCID
 * Description:��ȡCCID
 * Input:�жϵ�Դ���ݣ�Դ�����ֽ���
 * Output: �Ƿ��ȡ��
 * Return: True:��ȡ�����������ݣ�False:��ȡʧ��
 * Others: none
 ***************************************************************************/
static Bool GetModule_CCID(char *dat, uint8_t dat_bytes) {
    uint8_t get_pos = 0, check_bytes = StrLen(Rec_ICCID), get_bytes = sizeof (G350_Arg.ICCID);
    Bool sta = False;

    get_pos = Str_Find_Head(dat, Rec_ICCID, dat_bytes, check_bytes); //��ȡICCIDλ��
    if (get_pos) {//�����ȡ��ICCID����һ���ж�    
        CopyDat(G350_Arg.ICCID, dat + get_pos + check_bytes - 1, get_bytes); //��ȡ20���ֽ�
        sta = True;
    }
    return sta;
}

/***************************************************************************
 * Function: GetModule_CSQ
 * Description:��ȡCSQ
 * Input:�жϵ�Դ���ݣ�Դ�����ֽ���
 * Output: �Ƿ��ȡ��
 * Return: True:��ȡ�����������ݣ�False:��ȡʧ��
 * Others: none
 ***************************************************************************/
static Bool GetModule_CSQ(char *dat, uint8_t dat_bytes) {
    uint8_t get_pos = 0, check_bytes = StrLen(Rec_CSQ), get_bytes = sizeof (G350_Arg.CSQ);
    Bool sta = False;

    get_pos = Str_Find_Head(dat, Rec_CSQ, dat_bytes, check_bytes); //��ȡICCIDλ��
    if (get_pos) {//�����ȡ��ICCID����һ���ж�    
        CopyDat(G350_Arg.CSQ, dat + get_pos + check_bytes - 1, get_bytes); //��ȡ20���ֽ�
        sta = True;
    }
    return sta;
}

/***************************************************************************
 * Function: GetModule_ClientIP
 * Description:��ȡ��ͷIP
 * Input:�жϵ�Դ���ݣ�Դ�����ֽ���
 * Output: �Ƿ��ȡ��
 * Return: True:��ȡ�����������ݣ�False:��ȡʧ��
 * Others: none
 ***************************************************************************/
static Bool GetModule_ClientIP(char *dat, uint8_t dat_bytes) {
    uint8_t get_pos = 0, get_pos1, check_bytes = StrLen(REC_UPSND), offset = 0; // get_bytes = sizeof (G350_Arg.Client_IP);
    Bool sta = False;

    get_pos = Str_Find_Head(dat, REC_UPSND, dat_bytes, check_bytes); //�ж��Ƿ��ȡ��
    if (get_pos) {//�����ȡ��ICCID����һ���ж�    
        get_pos1 = Str_Find_Head(dat + get_pos, __r_n, dat_bytes - get_pos, 3); //��ȡICCIDλ��
        if (get_pos1) {
            offset = get_pos1 - check_bytes;
            CopyDat(G350_Arg.Client_IP, dat + get_pos + check_bytes - 1, offset); //��ȡ20���ֽ�
            *(G350_Arg.Client_IP + offset) = '\0';
            sta = True;
        }
    }
    return sta;
}

/***************************************************************************
 * Function: GetModule_ClientIP
 * Description:��ȡDNSת��IP
 * Input:�жϵ�Դ���ݣ�Դ�����ֽ���
 * Output: �Ƿ��ȡ��
 * Return: True:��ȡ�����������ݣ�False:��ȡʧ��
 * Others: none
 ***************************************************************************/
static Bool GetModule_DNS2IP(char *dat, uint8_t dat_bytes) {
    uint8_t get_pos = 0, get_pos1, check_bytes = StrLen(Rec_SET_DNS), offset = 0;
    Bool sta = False;

    //    while (BufferRead_UART1((uint8_t*) dat + dat_bytes++)); //��ȡʣ�µ�����
    get_pos = Str_Find_Head(dat, Rec_SET_DNS, dat_bytes, check_bytes); //��ȡICCIDλ��
    if (get_pos) {//�����ȡ��ICCID����һ���ж�    
        get_pos1 = Str_Find_Head(dat + get_pos, __r_n, dat_bytes - get_pos, 3); //��ȡICCIDλ��
        if (get_pos1) {
            offset = get_pos1 - check_bytes;
            CopyDat(G350_Arg.Server_IP, dat + get_pos + check_bytes - 1, offset); //��ȡ20���ֽ�
            *(G350_Arg.Server_IP + offset) = '\0';
            sta = True;
        }
    }
    return sta;
}

/***************************************************************************
 * Function: TX04Arg2GPRSArg
 * Description: GPRS��IPת���ַ���
 * Input: �жϵ�Դ���ݣ�Դ�����ֽ���
 * Output: 
 * Return: ��ȡ���ֽ���
 * Others: 
 ***************************************************************************/
static uint8_t TX04Arg2GPRSArg(char* output_s) {
    uint8_t cnt, getbytes = 0;

    for (cnt = 0; cnt < 4; cnt++) {
        getbytes += my_itoa(RunArg.IP[cnt], (uint8_t*) (output_s + getbytes));
        if (cnt < 3) {
            output_s[getbytes++] = '.';
        }
    }
    output_s[getbytes++] = '\0';
    return getbytes;
}

/***************************************************************************
Function: UbloxSendATCmd 
Description: ����AT�����Ublox
Input: ss(�������ݵ�ַ);cs(�Ա����ݵ�ַ);csl(�Ա����ݳ���);cnt(��������)
Output: void
Return: True:���ͳɹ���False:����ʧ��
Others: source_str�ĳ���Ҫ����check_str�����붼���ַ���
 ***************************************************************************/
static Bool UbloxSendATCmd(const char *source_str, const char* check_str, GetModuleArg_pf arg_pf, const uint16_t dly_10ms) {
    uint8_t send_cnt = 0, get_bytes = 0, head_pos = 0; //, check_bytes; //, cnt;
    Bool b_sta = False;
    uint8_t tmp[256];

    ClearDat(tmp, 0xff, 50); //���������
    //    check_bytes = StrLen(check_str);
    do {
        if (source_str != Null) {
            UART1SendString(source_str, StrLen(source_str)); //����ATָ�� 
#ifdef DEBUG_AT_TEST 
            UART2SendString((uint8_t*) "Send:", 5); //����ATָ��  
            UART2SendString((uint8_t*) source_str, StrLen(source_str)); //����ATָ��          
#endif
        }
        Idle(); //��������ģʽ        
        get_bytes += UARTGetDat(BufferRead_UART1, tmp + get_bytes, sizeof (tmp) - get_bytes, dly_10ms);
#ifdef DEBUG_AT_TEST  
        if (get_bytes) {
            UART2SendString((uint8_t*) "Receive:", 8); //����ATָ��  
            UART2SendString((uint8_t*) tmp, get_bytes);
            UART2SendChar('\n');
        } else
            UART2SendString((uint8_t*) "No Receive!\n", 12); //����ATָ�� 
#endif
        head_pos = Str_Find_Head(tmp, check_str, get_bytes, StrLen(check_str));
        if (head_pos) {//�жϵ�һ���ֽ� 
            if (arg_pf) {
                b_sta = (*arg_pf)((char*) tmp, get_bytes) ? True : False;
            } else {
                b_sta = True;
            }
            if (b_sta)
                break;
        }
    } while (5 > send_cnt++);
    return b_sta;
}


/***************************************************************************
Function: UbloxWaitServer //��̬2 ����CPOS�� OK  +CREG:1
Description: ����AT�����Ublox
Input: void
Output: Bool��True:���߳ɹ� False������
Return: True:���ͳɹ���False:����ʧ��
Others: none
 problem:1�������Ĺ����д��ڷ��ͺܶ�����������
 **************************************************************************
static Bool UbloxWaitServer(void) {
    uint8_t get_bytes = 0, find_cnt = 0, op = 0; //, length = 0x
    Bool b_sta = False; //, flag = True;
    uint8_t tmp[256]; //ATE exist AT Command depend on max size

    ClearDat(tmp, 0xff, 50); //���������
    //    CloseUblox(); //�ر�ublox
    //    LP_Delay(30); //��ʱ5s
    //    OpenUblox(); //����ublox
    //    LP_Delay(10); //��ʱ5s
    //    UART1SendString(Send_COPS, sizeof (Send_COPS) - 1); //������ӣ���ֹ���ݵ�һ�η������ݴ���
    //    UART1SendString(Send_COPS, sizeof (Send_COPS) - 1); //������ӣ���ֹ���ݵ�һ�η������ݴ���
    //    UART1SendString(Send_COPS, sizeof (Send_COPS) - 1); //������ӣ���ֹ���ݵ�һ�η������ݴ���

    gT2flag = 0; //   
    StartTMR2(500);
    while (!gT2flag) {
        Idle();
        //        if (gResetFlag)//�ȴ���������˵�ʱ������
        //            break;
        //        U1GetLast4Bytes(); //��ȡ���4���ֽ�
        //        while (BufferRead_UART1(tmp + get_bytes))
        //            get_bytes++;
        //        get_bytes
        get_bytes += UARTGetDat(BufferRead_UART1, tmp + get_bytes, 0); //�涨10msʱ���ڣ���ȡ4���ֽ�
        if (get_bytes >= 9) {//"+UUSOAOC:"
            find_cnt = Str_Find_Head(tmp, Rec_Server_URC, get_bytes, sizeof (Rec_Server_URC) - 1);
            if (find_cnt) {//�жϵ�һ���ֽ� 
                op = find_cnt;
                b_sta = True;
                break;
            }
        }
    }
    //    Delay100ms(1);
    gT2flag = 0;
    StopTMR2();
#ifdef DEBUG_AT_TEST
    if (get_bytes) {
        UART2SendString((uint8_t*) "Receive:", 8); //����ATָ��  
        UART2SendString((uint8_t*) tmp, get_bytes);
        UART2SendChar('\n');
    } else
        UART2SendString((uint8_t*) "No Receive!\n", 12); //����ATָ�� 
#endif
    //    get_bytes = 0; //�����ʷ��������

    return b_sta;
}
 */
/***************************************************************************
Function: UbloxWaitClient //��̬2 ����CPOS�� OK  +CREG:1
Description: ����AT�����Ublox
Input: void
Output: Bool��True:���߳ɹ� False������
Return: True:���ͳɹ���False:����ʧ��
Others: none
 **************************************************************************
static Bool UbloxWaitClient(void) {
    //#define  DeBug_Break_Out     
    uint8_t get_bytes = 0, find_cnt = 0, op = 0; //, length = 0x
    Bool b_sta = False; //, flag = True;
    uint8_t tmp[256]; //ATE exist AT Command depend on max size

    ClrUARTnBuf(BufferRead_UART1);
    ClearDat(tmp, 0xff, 50); //���������

    while (1) {
        Idle();
        //        Delay100ms(1); //1920/10=
        //        U1GetLast4Bytes(); //��ȡ���4���ֽ�        
        //        while (BufferRead_UART1(tmp + get_bytes))
        //            get_bytes++;
        get_bytes += UARTGetDat(BufferRead_UART1, tmp + get_bytes,  10); //�涨100msʱ���ڣ���ȡ4���ֽ�
        if (get_bytes >= 9) {//"+UUSOAOC:"
            find_cnt = Str_Find_Head(tmp, Rec_Client_URC, get_bytes, sizeof (Rec_Client_URC) - 1);
            if (find_cnt) {//�жϵ�һ���ֽ� 
                op = find_cnt;
                b_sta = True;
#ifdef DeBug_Break_Out
                DeBug_PrintInfo("\r\nFound_Break_Out!!!\r\n");
#endif
#ifdef DEBUG_AT_TEST
                if (get_bytes) {
                    UART2SendString((uint8_t*) "Receive:", 8); //����ATָ��  
                    UART2SendString((uint8_t*) tmp, get_bytes);
                    UART2SendChar('\n');
                } else
                    UART2SendString((uint8_t*) "No Receive!\n", 12); //����ATָ�� 
#endif
                break;
            }
        }
    }
    //    Delay100ms(1);
    //#ifdef DEBUG_AT_TEST
    //    if (get_bytes) {
    //        UART2SendString((uint8_t*) "Receive:", 8); //����ATָ��  
    //        UART2SendString((uint8_t*) tmp, get_bytes);
    //        UART2SendChar('\n');
    //    } else
    //        UART2SendString((uint8_t*) "No Receive!\n", 12); //����ATָ�� 
    //#endif
    //    get_bytes = 0; //�����ʷ��������
    return b_sta;
}
 */




/***************************************************************************
Function: UbloxGetServerPort
Description: ����AT�����Ublox
Input: ����
Output: void
Return: True:���ͳɹ���False:����ʧ��
Others: none
 **************************************************************************
static uint8_t UbloxGetServerPort(uint8_t * port_str) {
    uint8_t sendportcmd[256], bytes_offset = 0;

    ClearDat(sendportcmd, 0, 256);
    bytes_offset = 11;
    CopyDat(sendportcmd, Send_SET_PORT, bytes_offset); //����11bytes
    bytes_offset += GetPort(RunArg.Port, sendportcmd + bytes_offset);
    CopyDat(sendportcmd + bytes_offset, (uint8_t*) "\r\n", 3);
    bytes_offset += 3;
    CopyDat(port_str, sendportcmd, bytes_offset); //����APN

    return bytes_offset;
}*/

/***************************************************************************
Function: UbloxGetServerIP
Description: ����AT�����Ublox
Input: ����
Output: void
Return: True:���ͳɹ���False:����ʧ��
Others: none
 **************************************************************************
static uint8_t UbloxGetServerIP(uint8_t * ip_str) {
    uint8_t sendipcmd[256], bytes_offset = 0;

    ClearDat(sendipcmd, 0, 256);
    bytes_offset = 12;
    CopyDat(sendipcmd, Send_SET_WHITE_LIST, bytes_offset); //����11bytes
    //    CopyDat(sendipcmd, RunArg.IP, bytes_offset); //����11bytes
    bytes_offset += GetIP(RunArg.IP, sendipcmd + bytes_offset);
    CopyDat(sendipcmd + bytes_offset, (uint8_t*) "\r\n", 3);
    bytes_offset += 3;
    CopyDat(ip_str, sendipcmd, bytes_offset); //����APN

    return bytes_offset;
}*/

/***************************************************************************
Function: GetAPNCmd
Description: ��ȡAT��������ANPָ��
Input: ���� APN�Ĳ���
Output: void
Return: ����ָ���
Others: none
 ***************************************************************************/
static uint8_t GetAPNCmd(char * apn_str) {
    uint8_t bytes_offset = StrLen(Send_SET_APN);

    CopyDat(apn_str, Send_SET_APN, bytes_offset); //"AT+UPSD=0,1,\"CMNET\"\r\n"
    CopyDat(apn_str + bytes_offset, RunArg.APNName, RunArg.APNNameLength);
    bytes_offset += RunArg.APNNameLength;
    CopyDat(apn_str + bytes_offset, __r_n, 4);
    bytes_offset += 4;

    return bytes_offset;
}

/***************************************************************************
Function: GetIPPortCmd
Description: ��ȡAT���������IP��ַ�Ͷ˿ں�ָ��
Input: ����
Output: void
Return: True:���ͳɹ���False:����ʧ��
Others: none
 ***************************************************************************/
static uint8_t GetIPPortCmd(char *output_s) {//note:headstr_bytes-1
    uint8_t offset = 0, getbytes = StrLen(G350_Arg.Server_IP);

    offset = StrLen(Send_SET_IP_PORT);
    CopyDat(output_s, Send_SET_IP_PORT, offset);
    *(output_s + offset++) = '\"';
    CopyDat(output_s + offset, G350_Arg.Server_IP, getbytes); //����IP��ַ
    offset += getbytes;
    *(output_s + offset++) = '\"';
    *(output_s + offset++) = ',';
    getbytes = my_itoa(G350_Arg.PORT, (uint8_t*) (output_s + offset));
    offset += getbytes;
    CopyDat(output_s + offset, _r_n, 3);
    offset += 3;
    return offset;
}

/***************************************************************************
Function: GetDNSCmd
Description: ��ȡAT��������ANPָ��
Input: ���� APN�Ĳ���
Output: void
Return: ����ָ���
Others: none
 ***************************************************************************/
static uint8_t GetDNSCmd(char * dns_str) {
    uint8_t bytes_offset = StrLen(Send_SET_DNS);

    CopyDat(dns_str, Send_SET_DNS, bytes_offset); //"AT+UPSD=0,1,\"CMNET\"\r\n"
    *(dns_str + bytes_offset) = '\"';
    bytes_offset++;
    CopyDat(dns_str + bytes_offset, RunArg.DNSDomainName, RunArg.DNSDomainNameLength);
    bytes_offset += RunArg.DNSDomainNameLength;
    CopyDat(dns_str + bytes_offset, __r_n, 4);
    bytes_offset += 4;

    return bytes_offset;
}

/***************************************************************************
Function: OpenUblox
Description: ͨ��IO�ڴ�6310
Input: void
Output: void
Return: void
Others: none
 ***************************************************************************/
Bool OpenUblox(void) {//��������ʹ��UART1�Ľ���������Ҫ
    uint8_t cnt = 0;
    OR_CTRL_PWR = 1;
    //�ȴ����ݳ�����
    UB_PWRON = 1; //����ublox
    Delay10ms(1);
    UB_PWRON = 0;
    while (!UB_STA) {
        Delay10ms(1);
        cnt++;
        if (cnt > 10)

            return False;
    }
    return True;
}

/***************************************************************************
Function: CloseUblox
Description: ͨ��IO�ر�Ublox
Input: void
Output: void
Return: void
Others: none
 ***************************************************************************/
void CloseUblox(void) {//��������ʹ��UART1�Ľ���������Ҫ

    UB_PWRON = 0;
    OR_CTRL_PWR = 0;
    Delay100ms(5);
}

/***************************************************************************
Function: Ublox_Find_Network
Description: ����AT�����Ublox
Input: ����
Output: void
Return: True:���ͳɹ���False:����ʧ��
Others: step���ܴ���Ublox_F_NET_ATTACHE��5��
 ***************************************************************************/
uint8_t Ublox_Find_Network(uint8_t step) {
    Bool sta = False; //����ublox״̬Ϊ�����ʼ��
    int8_t cnt;

    const char* send_cmd[G350_F_NET_SIZE] = {CREG_2, Send_CPIN, Send_ICCID, Null, Send_CSQ};
    const char* check_cmd[G350_F_NET_SIZE] = {Rec_OK, Rec_OK, Rec_OK, Rec_CREG, Rec_OK};
    //    const uint8_t needbytes[G350_F_NET_SIZE] = {2, 16, 38, 22, 12};
    const GetModuleArg_pf pf_th [G350_F_NET_SIZE] = {Null, Null, GetModule_CCID, Check_CREG, GetModule_CSQ};
    const uint16_t delay_10ms[G350_F_NET_SIZE] = {100, 100, 100, 800, 60}; //���ܴ���1691.25 10ms

    for (cnt = 0; cnt < step; cnt++) {
        sta = UbloxSendATCmd(send_cmd[cnt], check_cmd[cnt], pf_th[cnt], delay_10ms[cnt]) ? True : False;
        ClrUARTnBuf(BufferRead_UART1);
        if (!sta) break;
    }
    return cnt;
}

/***************************************************************************
Function: Ublox_UDP_Client_Dialing
Description: ����AT�����Ublox
Input: ����
Output: void
Return: True:���ͳɹ���False:����ʧ��
Others: none
 **************************************************************************/
uint8_t Ublox_UDP_Client_Dialing(uint8_t step) {
    char getIPcmd[256]; //, bytes = 0;
    char getAPN[256]; //, apn_bytes = 0;
    char getDNS[256]; //, apn_bytes = 0;
    Bool sta = False; //����ublox״̬Ϊ�����ʼ��
    int8_t cnt;
    Bool isDNS = RunArg.DNSMode == 0x31;

    ClearDat(getIPcmd, '\0', 256);
    ClearDat(getAPN, '\0', 256);
    ClearDat(getDNS, '\0', 256);

    char* send_cmd[G350_UDP_Client_SIZE] = {
        getAPN,
        (char*) Send_ACTIVE_ARG,
        getDNS,
        (char*) Send_SET_UDP, //Send_SET_TCP,
        (char*) Send_UPSND
    };
    char* check_cmd[G350_UDP_Client_SIZE] = {(char*) Rec_OK, (char*) Rec_OK, (char*) Rec_OK, (char*) Rec_OK, (char*) Rec_OK};
    //    const uint8_t needbytes[G350_UDP_Client_SIZE] = {4, 2, 28, 17, 30, 2};
    GetModuleArg_pf pf_th [G350_UDP_Client_SIZE] = {Null, Null, GetModule_DNS2IP, Null, GetModule_ClientIP,};
    uint16_t delay_10ms[G350_UDP_Client_SIZE] = {80, 150, 100, 300, 50};

    GetAPNCmd(getAPN); //��ȡAPN
    TX04Arg2GPRSArg(G350_Arg.Server_IP); //��ȡIP

    G350_Arg.PORT = RunArg.Port; //��ȡ�˿ں�
    if (isDNS) GetDNSCmd(getDNS); //��������������Ļ�����ȡ������ATָ��

    for (cnt = 0; cnt < step; cnt++) {
        if (cnt == G350_SET_TCP_IP)//���ָ�����IP��PORT����ô���»�ȡָ��
            GetIPPortCmd(getIPcmd);
        if ((!isDNS) &&(cnt == G350_GET_DNS))//�ж��Ƿ���Ҫ��������
            continue;
        sta = UbloxSendATCmd(send_cmd[cnt], check_cmd[cnt], pf_th[cnt], delay_10ms[cnt]) ? True : False;
        ClrUARTnBuf(BufferRead_UART1);
        if (!sta) break;
    }
    return cnt; // == G350_UDP_Client_SIZE) ? True : False;
}

/***************************************************************************
Function: Ublox_TCP_Client_Dialing
Description: ����AT�����Ublox
Input: ���� RunArg.DNSMode == 0x31) {//30H-�̶�IP 31H-��������
Output: void
Return: True:���ͳɹ���False:����ʧ��
Others: none
 ***************************************************************************/
Bool Ublox_TCP_Client_Dialing(uint8_t step) {
    char getIPcmd[256]; //, bytes = 0;
    char getAPN[256]; //, apn_bytes = 0;
    char getDNS[256]; //, apn_bytes = 0;
    Bool sta = False; //����ublox״̬Ϊ�����ʼ��
    int8_t cnt;
    Bool isDNS = RunArg.DNSMode == 0x31;

    ClearDat(getIPcmd, '\0', 256);
    ClearDat(getAPN, '\0', 256);
    ClearDat(getDNS, '\0', 256);

    char* send_cmd[G350_TCP_Client_SIZE] = {
        getAPN,
        (char*) Send_ACTIVE_ARG,
        getDNS,
        (char*) Send_SET_TCP,
        (char*) Send_UPSND,
        (char*) Send_SET_DLINK_TIME,
        getIPcmd,
        (char*) Send_START_CONNECT
    };
    char* check_cmd[G350_TCP_Client_SIZE] = {(char*) Rec_OK, (char*) Rec_OK, (char*) Rec_SET_DNS, (char*) Rec_OK,
        (char*) Rec_OK, (char*) Rec_OK, (char*) Rec_OK, (char*) Rec_CONNECT};
    //    uint8_t needbytes[G350_TCP_Client_SIZE] = {4, 2, 28, 17, 30, 2, 2, 10};
    GetModuleArg_pf pf_th [G350_TCP_Client_SIZE] = {Null, Null, GetModule_DNS2IP, Null, GetModule_ClientIP, Null, Null, Null};
    uint16_t delay_10ms[G350_TCP_Client_SIZE] = {300, 300, 100, 100, 100, 100, 50, 300}; //��ʾ����04����

    GetAPNCmd(getAPN); //��ȡAPN
    TX04Arg2GPRSArg(G350_Arg.Server_IP); //��ȡIP

    G350_Arg.PORT = RunArg.Port; //��ȡ�˿ں�
    if (isDNS) GetDNSCmd(getDNS); //��������������Ļ�����ȡ������ATָ��

    for (cnt = 0; cnt < step; cnt++) {
        if (cnt == G350_SET_TCP_IP)//���ָ�����IP��PORT����ô���»�ȡָ��
            GetIPPortCmd(getIPcmd);
        if ((!isDNS) &&(cnt == G350_GET_DNS))//�ж��Ƿ���Ҫ��������
            continue;
        sta = UbloxSendATCmd(send_cmd[cnt], check_cmd[cnt], pf_th[cnt], delay_10ms[cnt]) ? True : False;
        ClrUARTnBuf(BufferRead_UART1);
        if (!sta) break;
    }
    return cnt; //) ? True : False;
}

/***************************************************************************
Function: Ublox_GSM_Dialing
Description: GSM����ģʽ
Input: ����
Output: void
Return: ���͵������±�
Others: none
 ***************************************************************************/
uint8_t Ublox_GSM_Dialing(uint8_t step) {
    Bool sta = False;
    int8_t cnt; //����ublox״̬Ϊ�����ʼ��

    const char* send_cmd[G350_GSM_Client_SIZE] = {
        Set_SMS_MODE,
        Set_SMS_CNMI,
        Set_SMS_CSMS
    };
    const char* check_cmd[G350_GSM_Client_SIZE] = {Rec_OK, Rec_OK, Rec_OK};
    const GetModuleArg_pf pf_th [G350_GSM_Client_SIZE] = {Null, Null, Null};
    const uint16_t delay_10ms[G350_GSM_Client_SIZE] = {20, 20, 20};

    for (cnt = 0; cnt < step; cnt++) {
        sta = UbloxSendATCmd(send_cmd[cnt], check_cmd[cnt], pf_th[cnt], delay_10ms[cnt]) ? True : False;
        ClrUARTnBuf(BufferRead_UART1);
        if (!sta) break;
    }
    return cnt; //
}

/***************************************************************************
Function: Ublox_GPRS_TCP_Server_Dialing
Description: ����AT�����Ublox
Input: ����
Output: void
Return: True:���ͳɹ���False:����ʧ��
Others: none
 ***************************************************************************/
//uint8_t Ublox_GPRS_TCP_Server_Dialing(void) {
//    //#define DeBug_Server
//    uint8_t sta;
//    uint8_t getip[256], ip_bytes = 0;
//    uint8_t getAPN[256], apn_bytes = 0;
//    //    uint8_t getIPcmd[256], bytes = 0;
//    uint8_t getport[256], port_bytes = 0;
//
//    ClearDat(getip, '\0', 256);
//    ClearDat(getAPN, '\0', 256);
//    ClearDat(getport, '\0', 256);
//
//    apn_bytes = UbloxGetAPN(getAPN);
//    if (UbloxSendATCmd(getAPN, apn_bytes - 1, Rec_OK, 2, 5, 2)) {
//        ClrUARTnBuf(BufferRead_UART1);
//        if (UbloxSendATCmd(Send_ACTIVE_ARG1, sizeof (Send_ACTIVE_ARG1) - 1, Rec_OK, 2, 3, 15)) {
//            ClrUARTnBuf(BufferRead_UART1);
//            if (UbloxSendATCmd(Send_SET_SERVER, sizeof (Send_SET_SERVER) - 1, Rec_OK, 2, 5, 2)) {
//                ClrUARTnBuf(BufferRead_UART1);
//                port_bytes = UbloxGetServerPort(getport);
//                if (UbloxSendATCmd(getport, port_bytes, Rec_OK, 2, 5, 1)) {
//                    ClrUARTnBuf(BufferRead_UART1);
//                    ip_bytes = UbloxGetServerIP(getip);
//                    //����IP��ַ����
//                    if (UbloxSendATCmd(getip, ip_bytes, Rec_OK, 2, 3, 5)) {
//                        ClrUARTnBuf(BufferRead_UART1);
//                        //��������
//                        if (UbloxSendATCmd(Send_SET_SERVER_TCP, sizeof (Send_SET_SERVER_TCP) - 1, Rec_OK, 2, 5, 1)) {
//                            ClrUARTnBuf(BufferRead_UART1);
//                            if (UbloxSendATCmd(Send_START_SAO, sizeof (Send_START_SAO) - 1, Rec_OK, 2, 5, 1)) {
//                                ClrUARTnBuf(BufferRead_UART1);
//                                if (UbloxSendATCmd(Send_SAVE_ARG, sizeof (Send_SAVE_ARG) - 1, (uint8_t*) "OK\r\n\0", 5, 5, 15)) {
//                                    ClrUARTnBuf(BufferRead_UART1);
//                                    if (UbloxSendATCmd(Send_CREG_Equ_2, sizeof (Send_CREG_Equ_2) - 1, Rec_OK, 2, 5, 15)) {//�����
//                                        ClrUARTnBuf(BufferRead_UART1);
////                                        UART1SendString(Send_COPS, sizeof (Send_COPS) - 1);
//                                        if (UbloxWaitServer()) {
//                                            //                                            gGPRSIsONline = 1; //˵��ģ���Ѿ�������
//                                            gTX04Sta = TX04_Sta_TCP_Server_Cop; //����ʱ����Ч
//                                            if (UbloxWaitClient())
//                                                sta = Ublox_CONNECTED;
//                                            else {
//                                                User_PrintErrCode(UART2SendString, Ublox_USER_FAIL_09);
//                                                sta = Ublox_GPRS_TCP_CONNECT_NO_FAIL;
//                                            }
//                                        } else {
//                                            User_PrintErrCode(UART2SendString, Ublox_USER_FAIL_08);
//                                            sta = 102;
//                                        }
//                                    } else
//                                        sta = 103;
//                                } else
//                                    sta = 101;
//                            } else
//                                sta = 100;
//                        } else
//                            sta = 99;
//                    } else {
//                        sta = Ublox_GPRS_TCP_SET_IP_PORT_NO_REC;
//                        User_PrintErrCode(UART2SendString, Ublox_USER_FAIL_06);
//                    }
//                } else
//                    sta = Ublox_GPRS_TCP_SET_IP_PORT_NO_REC;
//            } else
//                sta = Ublox_GPRS_TCP_SET_TCP_NO_REC;
//        } else
//            sta = Ublox_GPRS_TCP_ATCTIVE_ARG_NO_FAIL;
//    } else {
//        sta = Ublox_GPRS_TCP_SET_APN_NO_REC;
//        User_PrintErrCode(UART2SendString, Ublox_USER_FAIL_17);
//    }
//#ifdef DeBug_Server
//    DeBug_PrintInfo("server end\r\n");
//    DeBug_PrintStrNum("sta", sta);
//#endif
//
//    return sta;
//}

/***************************************************************************
Function: UDPWriteStrByCmd
Description: ͨ��AT�����UDP���ݸ������
Input:����ָ���ַ�����ݳ���
Output: void
Return: 
Others: //AT+USOST=0,"122.228.138.254",5061,29
 ***************************************************************************/
void UDPWriteStrByCmd(const void * dat, const uint16_t bytes) {
    //#define UDP_IP_TEST //�������ɵ�����
    char getIPcmd[256];
    uint16_t offset, getbytes = 0; //��ȡIP�ı����Լ��ֽ���
    //    uint8_t bytesstr[6]; //�˿ںŵ��ַ����Լ��ֽ���

    offset = StrLen(Send_UDP_SEND_DAT);
    CopyDat(getIPcmd, Send_UDP_SEND_DAT, offset); //����AT+USOST=0,
    *(getIPcmd + offset++) = '"';
    offset += TX04Arg2GPRSArg(getIPcmd + offset) - 1; //����IP��ַ
    CopyDat(getIPcmd + offset, "\",", 2);
    offset += 2;
    //    getbytes = my_itoa(RunArg.Port, bytesstr); //����PORT
    //    CopyDat(getIPcmd + offset, bytesstr, getbytes);
    getbytes = my_itoa(RunArg.Port, (uint8_t*) getIPcmd + offset);
    offset += getbytes;
#ifdef UDP_IP_TEST //�ϵ�1
    DeBug_PrintInfo("\r\nThis is UDP Send String 1 bk:\t");
    DeBug_PrintString(getIPcmd, all_bytes);
    DeBug_Print_rn();
#endif
    getIPcmd [offset++] = ',';
    //    getbytes = my_itoa(bytes, bytesstr);
    //    CopyDat(getIPcmd + offset, bytesstr, getbytes); ////���Ʒ��͵����ݳ���
    getbytes = my_itoa(bytes, (uint8_t*) getIPcmd + offset);
    offset += getbytes; //�����ֽ���
    CopyDat(getIPcmd + offset, _r_n, 3);
    offset += 3;
#ifdef UDP_IP_TEST //�ϵ�2
    DeBug_PrintInfo("\r\nThis is UDP Send String 2 bk:\t");
    DeBug_PrintString(getIPcmd, all_bytes);
    DeBug_Print_rn();
#endif
    if (UbloxSendATCmd(getIPcmd, _a, Null, 10)) {//����udp�����ֽڵ�ATָ��
        //        CopyDat(getIPcmd, dat, bytes);
        //        *(getIPcmd + bytes) = '\0'; //D
        //        UbloxSendATCmd(getIPcmd, Rec_OK, Null, 50); //�������� ���Ͳ��Բ�����ʱ�����\0
        UART1SendString(dat, bytes); //���Է������ݲ���\0������           
    }
}

/***************************************************************************
Function: UDPMakeReadATCmd
Description: ͨ��UDP����AT����
Input:���ݣ�����ָ��
Output: ���͵��ֽ���
Return: 
Others: //AT+USOST=0,"122.228.138.254",5061,29
 ***************************************************************************/
static uint8_t UDPMakeReadATCmd(uint16_t readnum, uint8_t*atcmd) {
    char readcmd[50];
    uint8_t readbytes = 0, cmdbytes = 0; //readdat[6],

    cmdbytes = sizeof (Send_UDP_Read) - 1;
    CopyDat(readcmd, Send_UDP_Read, cmdbytes); //����ָ������
    //    readbytes = my_itoa(readnum, readdat); //��123=>"123"
    //    CopyDat(readcmd + cmdbytes, readdat, readbytes); //��������
    readbytes = my_itoa(readnum, (uint8_t*) readcmd + cmdbytes);
    cmdbytes += readbytes; //���������ֽ���
    CopyDat(readcmd + cmdbytes, _r_n, 3); //��������
    cmdbytes += 3;
    CopyDat(atcmd, readcmd, cmdbytes);
    return cmdbytes;
}

/***************************************************************************
Function: UDPReadStrByCmd
Description: ͨ��AT�����ȡUDPЭ����������͹������ݣ�����ú����Ƿ������ݵĳ���AT+USORF=0,10
Input: ���ݵ��ֽ��������ݻ�������
Output: ʵ�ʷ����ֽ���
Return: 
Others: none =0��ʾ���Ի�ȡ���ֽ���
 ***************************************************************************/
uint16_t UDPReadStrByCmd(uint8_t * Ublox_buf) {
    uint8_t readcmd[50];
    uint16_t readbytes = 0, cmdbytes = 0, getbytes = 0; //readdat[6], 
    uint16_t headpos_real, endpos_real, readnum_real = 0, offset;
    char port[8] = {'"', ',', 0, 0, 0, 0, 0, 0}, port_size = 0;


    cmdbytes = UDPMakeReadATCmd(0, readcmd); // AT+USORF=0,0 make
    if (UbloxSendATCmd((char*) readcmd, Rec_OK, Get_UDP_Rec_Byte, 200)) {// AT+USORF=0,0send
        readbytes = G350_Arg.UDP_BYTES; //ȫ�ֱ�����UDP��������Get_UDP_Rec_Byte����
        if (readbytes) {//0
            if (readbytes > 200) {//����������
                readbytes = 200;
            }
            cmdbytes = UDPMakeReadATCmd(readbytes, readcmd); // AT+USORF=0,n make
            if (cmdbytes) {
                UART1SendString(readcmd, cmdbytes);
                getbytes = UARTGetDat(BufferRead_UART1, Ublox_buf, 0xFF, 100);
                if (getbytes) {
                    port_size = my_itoa(RunArg.Port, ((uint8_t*) port + 2));
                    headpos_real = Str_Find_Head(Ublox_buf, port, getbytes, port_size + 2); //��ȡ�˿ںŵ�λ��
                    offset = headpos_real - 1;
                    endpos_real = Str_Find_Head(Ublox_buf + offset, ",\"", getbytes - offset, 2); //�ж���Ч���� 
                    offset += port_size + 3;
                    readnum_real = G350_Arg.UDP_BYTES = my_atoi((uint8_t*) Ublox_buf + offset, endpos_real - 8); //ʵ�ʻ�ȡ�����ֽ���
                    offset += endpos_real - 6;
                    CopyDat(Ublox_buf, Ublox_buf + offset, readnum_real);
                }
            }
        }
    }
    return readnum_real;
}

/***************************************************************************
Function: SMSWriteStrByCmd
Description: ���Ͷ��� ָ��ص�����
Input: ����
Output: void
Return: True:���ͳɹ���False:����ʧ��
Others: 
 ***************************************************************************/
void SMSWriteStrByCmd(const void *sms, const uint16_t smssize) {
    //#define DEBUG_SMS_Write_Test
    char tmp_send[256];
    uint16_t offset = 0, cnt = 0;
    Bool sta = False;
    uint8_t tmp_number[15] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    uint8_t cnt1 = 0, tmp = 0, size = 0;
    uint8_t sms_bytes;
    uint8_t sms_num[6];

    if (gSMSInfo) {
        CopyDat(sms_num, RunArg.SMSTargetNumber2, 6);
        size = HCD(RunArg.SMSTargetNumber2Length) / 2 + HCD(RunArg.SMSTargetNumber2Length) % 2;
        sms_bytes = RunArg.SMSTargetNumber2Length;
    } else {//Ĭ�ϣ�����һ
        CopyDat(sms_num, RunArg.SMSTargetNumber1, 6);
        size = HCD(RunArg.SMSTargetNumber1Length) / 2 + HCD(RunArg.SMSTargetNumber1Length) % 2;
        sms_bytes = RunArg.SMSTargetNumber1Length;
    }

    for (cnt = 0; cnt < size; cnt++) {//��ȡ���ź����ַ���
        tmp = *(sms_num + cnt);
        tmp_number[cnt1++] = (tmp >> 4) + 0x30;
        if (toupper(tmp_number[cnt1 - 1]) == 'F')
            break;
        tmp_number[cnt1++] = (tmp & 0x0f) + 0x30;
        if (toupper(tmp_number[cnt1 - 1]) == 'F')
            break;
    }
    offset = sizeof (Set_SMS_SEND) - 1; //��ȡƫ����
    CopyDat(tmp_send, (uint8_t*) Set_SMS_SEND, offset); //�����ַ��� AT+CMGS=
    CopyDat((tmp_send + offset), (uint8_t*) "\"+86", 4); //�����ַ��� "+86
    offset += 4; //ƫ����+4
    CopyDat((tmp_send + offset), (uint8_t*) tmp_number, sms_bytes); //�����ֻ�����
    offset += sms_bytes; //ƫ����+�ֻ�����
    CopyDat((tmp_send + offset), (uint8_t*) "\"\r\0", 3); //�����ַ��� ��<CR>    
    offset = smssize;
    cnt = 0;
    do {
        Delay100ms(10); //������Ƿ���Ҫ�����ʱ
        if (UbloxSendATCmd((char*) tmp_send, Rec_Allow_Write, Null, 50)) { //����ATָ��ȴ����ء�>��            
            if (offset > 160) {//�ֽ�������200 �����������   
                UART1SendString(sms + cnt, 160); //���Ͷ�����Ϣ������ʹ��UbloxSendATCmd�������а���\0FFF
                offset -= 160;
                cnt += 160;
            } else {
                UART1SendString(sms + cnt, offset); //���Ͷ�����Ϣ������ʹ��UbloxSendATCmd�������а���\0FFF
                sta = True;
            }
            UART1SendChar(0x1a); //���Ͷ��Ž���
            UART1SendChar('\0');
            Delay100ms(50); //������Ƿ���Ҫ�����ʱ
            if (sta)
                break;
        }
    } while (1);
}
//#ifdef DEBUG_AT_TEST
//UART2SendString(sms, smssize);
//UART2SendChar((const uint8_t) 0x1a); //ctrl+z
//#endif
//}

/***************************************************************************
Function: SMSWriteRecUser
Description: ���ͽ��յĵ���������ʾ
Input: ����
Output: void
Return: True:���ͳɹ���False:����ʧ��
Others: 
+CMGR: "REC UNREAD","+8618657158149",,"18/10/11,09:10:26+50"
00680065006C006C006F00200077006F0072006C0064FF01
OK 
SM:123454678989165;+8618653214721;16/10/21,08:59:38;"
SM:123454678989165;+8618657158149;18/10/11,13:16:49;"
 ***************************************************************************/
void SMSWriteRecUser(const void *sms, const uint16_t smssize) {
    uint8_t buffer[256], sendbyte = 0, offset;
    uint8_t get_data_start_op, get_data_end_op, get_phone_op, get_time_op;

    CopyDat(buffer, Send_User_SMS, 3);
    sendbyte = 3;
    get_data_start_op = Str_Find_Head(sms, "\"\r\n", smssize, 3); //��ȡ���� 
    if (get_data_start_op) {
        get_data_end_op = Str_Find_Head(sms + get_data_start_op, _r_n2_OK, smssize, 6); //��ȡ���� 
        if (get_data_end_op) {
            offset = get_data_end_op - 4;
            CopyDat(buffer + sendbyte, sms + get_data_start_op + 2, offset);
            sendbyte += offset;
            *(buffer + sendbyte++) = ';';
            get_phone_op = Str_Find_Head(sms, "\"+", smssize, 2); //��ȡ�ֻ��� 
            get_time_op = Str_Find_Head(sms, "\",,\"", smssize, 4); //��ȡʱ�� 
            if (get_phone_op && get_time_op && get_phone_op < get_time_op) {
                offset = get_time_op - get_phone_op - 1;
                CopyDat(buffer + sendbyte, get_phone_op + sms, offset); //��ȡ�ֻ��� 
                sendbyte += offset;
                *(buffer + sendbyte++) = ';';
                offset = get_data_start_op - get_time_op - 7;
                CopyDat(buffer + sendbyte, sms + get_time_op + 3, offset); //��ȡʱ��
                sendbyte += offset;
                CopyDat(buffer + sendbyte, ";\"\r\n", 4); //��ȡ�ֻ��� 
                sendbyte += 4;
                UART2SendString(buffer, sendbyte); //���Ͷ̽��յ������ݸ��û�����
            }
        }
    }
}

/***************************************************************************
Function: SMSReadStrByCmd
Description: ���ɶ�ȡ���ŵ�AT������͸�ģ��
Input: ���ŵ�ID��
Output: void
Return: ��ȡ���������ֽ�
Others: none
 ***************************************************************************/
static uint16_t SMSReadStrByCmd(const uint16_t id, uint8_t* Ublox_buf) {
    uint8_t send_getSMS[50], id_str[6], id_str_size = 0, offset = 0;
    uint8_t databuf[240]; //�������ĳ�����160����+��ʾURC62+8�ֽ�\r\n\r\nOK\r\n
    uint16_t get_offset = 0, getbytes = 0, end_op = 0, URC_op = 0, buf_getbytes = 0;

    CopyDat(send_getSMS, '\0', 50); //�������
    offset = sizeof (Set_SMS_READ) - 1; //���㷢���ֽ�
    CopyDat(send_getSMS, Set_SMS_READ, offset); //����ATָ��
    id_str_size = my_itoa(id, id_str); //���㷢���ֽ�
    CopyDat(send_getSMS + offset, id_str, id_str_size); //����ID��
    offset += id_str_size; //���㷢���ֽ�
    CopyDat(send_getSMS + offset, (const uint8_t*) "\r\n", 2); //׷�ӻس�����
    offset += 2; //���㷢���ֽ�
    UART1SendString(send_getSMS, offset); //���ͻ�ȡ����ATָ��

    buf_getbytes = UARTGetDat(BufferRead_UART1, databuf, 240, 300); //�涨300msʱ���ڻ�ȡ��������
    if (buf_getbytes) {
        offset = StrLen(SMS_CKC_CMGR);
        URC_op = Str_Find_Head(databuf, SMS_CKC_CMGR, buf_getbytes, offset);
        end_op = Str_Find_Head(databuf, _r_n2_OK, buf_getbytes, 6);
        if (URC_op && end_op) {
            offset += URC_op; //�����ƫ��������ʼ��ȡ��λ��
            get_offset = end_op - offset + 5; //�����ȡ���ֽ���
            CopyDat(Ublox_buf, databuf + offset, get_offset);
            getbytes += get_offset; // += getbytes;
        }
    }
    return getbytes;
}

/***************************************************************************
Function: UDPSendDat2Sever
Description: UDP�ͷ���ģʽ�£����ݷ��ͷ���ˣ�������������
Input:Ublox_buf��getsize
Output: none
Return: none
Others: ����200�ֽڷֶη��ͣ��������ݷֻ����η���
 ***************************************************************************/
void UDPSendDat2Sever(const void *buffer, uint16_t getsize) {
    uint16_t getbytes = getsize, cnt = 0;

    do {//��������
        if (getbytes > 200) {//�ֽ�������200 �����������   
            UDPWriteStrByCmd(buffer + cnt, 200);
            getbytes -= 200;
        } else {
            UDPWriteStrByCmd(buffer + cnt, getbytes);
            break;
        }
        cnt += 200;
    } while (1);
}

/***************************************************************************
Function: GSMSendMessage
Description: GMSģʽ�£����ݷ��Ͷ���
Input:Ublox_buf��getsize
Output: none
Return: none
Others: ���ͳɹ�Ҫ����OK
 ***************************************************************************/
void GSMSendMessage(const void *Ublox_buf, uint16_t getsize) {
    Bool sta = True;
    //��ȡ����������
    do {
        if (U2STAbits.URXDA) {//�����һ���ֽڣ���ô���ֽ�����ȡ���������жϺ���,����Ҫ��ʱ
            BufferWrite_UART2();
        } else {
            Delay10ms(1); //1200bit/s
            if (U2STAbits.URXDA) {//�����һ���ֽڣ���ô���ֽ�����ȡ���������жϺ���,����Ҫ��ʱ
                BufferWrite_UART2();
            } else
                sta = False;
        }
        while (BufferRead_UART2((uint8_t*) Ublox_buf + getsize)) {
            getsize++;
            if (getsize >= 160) {//�ֽ�������200 �����������   
                SMSWriteStrByCmd(Ublox_buf, 160); //������70,Ӣ��140��
                getsize = 0;
                break;
            }
        }
    } while (sta);
    if (getsize) {
        SMSWriteStrByCmd(Ublox_buf, getsize);
        UART2SendString((const uint8_t*) "SMS_OK\r\n", 8);
    }
}

/***************************************************************************
Function: UbloxUDPGetURC
Description: ����AT�����Ublox
Input: ����
Output: void
Return: True:���ͳɹ���False:����ʧ��
Others: none
 ***************************************************************************/
uint16_t UbloxUDPGetURC(uint8_t *Ublox_buf, uint16_t bytes) {
    return UDPReadStrByCmd(Ublox_buf); //������ȡ���յ����ֽ���
}

/***************************************************************************
Function: SMSGetURC
Description: ����AT�����Ublox,��ȡURC������ATָ���ȡ���ţ����ض�ȡ��������
Input: ������Ϣ������
Output: ���������ݡ����ݴ�С������ID��
Return: ����ID��
Others: 
 ***************************************************************************/
static uint16_t SMSGetURC(uint8_t* Ublox_buf, uint16_t* buf_bytes) {
    uint8_t databuf[240], sms_id[6]; //, cmdtype; //�������ĳ�����160����+��ʾURC62+8�ֽ�\r\n\r\nOK\r\n
    uint16_t offset = 0, getbytes = 0, end_op = 0, URC_op = 0, buf_getbytes = 0, sms_ID = 0;

    buf_getbytes = UARTGetDat(BufferRead_UART1, databuf, 240, 100); //1sˢ���ֽ�
    if (buf_getbytes) {
        offset = StrLen(Rec_SMS_NEW_TIP);
        URC_op = Str_Find_Head(databuf, Rec_SMS_NEW_TIP, buf_getbytes, offset); //��ȡURC��ʾ+CMTI: "ME",90
        Delay100ms(20); //�ȴ���������һ��URC
        if (URC_op) {
            offset += URC_op - 1; //���ݳ��ȼ�һ
            end_op = Str_Find_Head(databuf + offset, _r_n, buf_getbytes, 2) - 1; //��ȡ���ݵĽ�β
            if (end_op) {//����ID
                CopyDat(sms_id, databuf + offset, end_op); //��ȡ���ŵ�ID�ַ���
                sms_ID = my_atoi(sms_id, end_op); //ID�ַ���ת��Ϊ����
                getbytes = SMSReadStrByCmd(sms_ID, Ublox_buf); //���ͻ�ȡ����ָ��
            }
        }
    }
    *buf_bytes = getbytes;
    return sms_ID;
}

/***************************************************************************
Function: UbloxSMSGetURC
Description: ����AT�����Ublox,��ȡURC������ATָ���ȡ���ţ����ض�ȡ��������
Input: ����
Output: void
Return: True:���ͳɹ���False:����ʧ��
Others: //ָ��ȫ������str  str->hex����Ҫ����
 ***************************************************************************/
uint16_t UbloxSMSGetURC(uint8_t* Ublox_buf, uint16_t bytes) {
    uint8_t cmdtype; //�������ĳ�����160����+��ʾURC62+8�ֽ�\r\n\r\nOK\r\n
    uint16_t offset = 0, getbytes = 0, end_op = 0, URC_op = 0, buf_getbytes = 0, sms_ID = 0, get_offset, cmd_op = 0;

    sms_ID = SMSGetURC(Ublox_buf, &buf_getbytes); //��ȡ��������
    //�ж��Ƿ���дָ������дָ��Ļ�����ô�ͼ�����ȡһ��ָ��
    cmd_op = IsGetMasthead(Ublox_buf, buf_getbytes); //Ѱ��+TXYBJT
    if (cmd_op) {
        cmdtype = TX04GetCMDType(Ublox_buf, buf_getbytes); //�ж�ָ������
        if ((cmdtype == CMD_TESTW0) || (cmdtype == CMD_TESTW2)) {//�����дָ��Ļ�
            buf_getbytes += SMSReadStrByCmd(sms_ID + 1, Ublox_buf + buf_getbytes); //���ͻ�ȡ����ָ��
            if (buf_getbytes > 370) {//�����ȡ���������ֽ�������370���ֽڵĻ�������ȡ���ڶ�������
                //���������ӣ���ʼ�жϵ�һ�����ŵ�λ��
                offset = cmd_op - 1;
                end_op = Str_Find_Head(Ublox_buf, _r_n2_OK, buf_getbytes, 6);
                if (end_op) {
                    get_offset = end_op - offset - 3; //�����ȡ���ֽ���
                    CopyDat(Ublox_buf, Ublox_buf + offset, get_offset); //������Ч���ֽ���
                    getbytes = get_offset; //���¿�ʼ�����ȡ���ֽ���
                    //�жϺ���һ�����ݵĿ�ʼ��ַ
                    offset = end_op + 5; //����ƫ������ȷ����ȡ����ȷ������
                    URC_op = Str_Find_Head(Ublox_buf + offset, __r_n, buf_getbytes, 3); //��ȡ�����ݵĿ�ʼ
                    end_op = Str_Find_Head(Ublox_buf + offset, _r_n2_OK, buf_getbytes, 6); //��ȡ���ݵĽ�β
                    if (URC_op && end_op) {//�ж��Ƿ񶼻�ȡ��
                        offset += URC_op + 2; //�����ƫ��������ʼ��ȡ��λ��
                        get_offset = end_op - URC_op - 5; //�����ȡ���ֽ���
                        CopyDat(Ublox_buf + getbytes, Ublox_buf + offset, get_offset);
                        getbytes += get_offset; // += getbytes;  
                        //ת������                        
                        offset = 14;
                        get_offset = Char2Hex(Ublox_buf + offset, getbytes - offset, Ublox_buf + offset);
                        getbytes = get_offset + offset; //�����ֽ���                                                
                    }
                }
            }
        } else//���������ָ��
            getbytes = buf_getbytes;
    } else {//����Ƕ�����Ϣ
        getbytes = buf_getbytes;
    }
    return getbytes;
}

/***************************************************************************
Function: UbloxCloseTCPClient
Description: �ر�Ublox��TCP���ӣ�
Input: ����ǰ��ʱ�����ͺ���ʱ
Output: �Ƿ�رճɹ�
Return: True:���ͳɹ���False:����ʧ��
Others: ��λ10ms
 ***************************************************************************/
Bool UbloxCloseTCPClient(void) {
    Bool sta = True;
    //���������
    if (gTX04Sta == TX04_Sta_TCP_Cop) {
        ClrUARTnBuf(BufferRead_UART1);
        LP_Delay(100); //�������ߺ�����EN�õ� ����+++���ݷ��͸�Զ�� 800ms
        if (UbloxSendATCmd(Send_ToAT, Rec_DISCONNECT, Null, 200)
                && UbloxSendATCmd(Send_CLOSE_CONNET, Rec_OK, Null, 200)) {
            LP_Delay(50); //�������ߺ�û�йر����ӵ� 500ms
        } else
            sta = False;
    }
    return sta;
}

/***************************************************************************
Function: UbloxSwitchFlow
Description: ����AT����,�л�ģʽ
Input: ��ʱʱ�䣬ģʽ
Output: �л��Ƿ�ɹ�
Return: True:�л��ɹ���False:�л�ʧ��
Others: none
 ***************************************************************************/
Bool UbloxSwitchFlow(const uint8_t mode) {
    Bool sta = False;

    LP_Delay(1); //�������ߺ�����EN�õ� ����+++���ݷ��͸�Զ��
    if (mode != DATA2CMD)
        sta = UbloxSendATCmd(Send_START_CONNECT, Rec_CONNECT, Null, 100);
    else
        sta = UbloxSendATCmd(Send_ToAT, Rec_DISCONNECT, Null, 200);
    LP_Delay(1); //�������ߺ�����EN�õ� ����+++���ݷ��͸�Զ��

    return sta;
}

/***************************************************************************
Function: UbloxDisablePSD
Description:ͨ��ATָ��ر�PSD=0�Ĳ���
Input: void
Output: void
Return: ture:close success ;False:close��fail
Others: none
 ***************************************************************************/
Bool UbloxDisablePSD(void) {
    uint8_t sta = False;

    if (UbloxSendATCmd(Send_DISABLE_ARG, Rec_OK, Null, 40)) {//close tcp and return result
        sta = True;
    }
    //    if (after_delay_ms)
    //        LP_Delay(after_delay_ms);
    return sta;
}

