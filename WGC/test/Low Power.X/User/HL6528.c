#include "HL6528.h"
#include <string.h>
//#include <math.h>
//#include <stdlib.h>
//#include "includes.h"
//#include <stdbool.h>
//#include "cJSON.h"


//extern OS_EVENT* sem1, *sem2; //���߲��������־

//struct ATCommand {
const uint8_t K3[] = {"AT&K3\r\n"}; //{"AT&K3\r\n"};
const uint8_t D1[] = {"AT&D1\r\n"}; //{"AT&K3\r\n"};
const uint8_t AT[] = {"AT\r\n"};
const uint8_t CREG_2[] = {"AT+CREG=2\r\n"};
const uint8_t OK[] = {"OK"};
const uint8_t CPIN[] = {"AT+CPIN?\r\n"};
const uint8_t READY[] = {"+CPIN: READY"};
const uint8_t CIMI[] = {"AT+CIMI\r\n"};
const uint8_t CREG[] = {"AT+CREG?\r\n"};
const uint8_t CGREG[] = {"AT+CGREG?\r\n"};
const uint8_t _5[] = {",5"};
const uint8_t _1[] = {",1"};
const uint8_t CSCA[] = {"AT+CSCA\r\n"};
//const uint8_t KCNXCFG[] = {"AT+KCNXCFG"};
const uint8_t KCNXCFG[] = {"AT+KCNXCFG=1,\"GPRS\",\"CMNET\"\r\n"};
const uint8_t KTCPCFG[] = {"AT+KTCPCFG=1,0,\"};//139.196.122.159\",5080\r\n\n"};
static uint8_t KTCPCFG1[] = {"AT+KTCPCFG=1,0,\"183.230.40.40\",1811\r\n\n"};
//const uint8_t KTCPCFG[] = {"AT+KTCPCFG=1,0,\"183.246.74.68\",5070\r\n"};//TR 
//const uint8_t KTCPCFG[] = {"AT+KTCPCFG=1,0,\"183.230.40.40\",1811\r\n"};//�ƶ�ONENET
const uint8_t KTCPSTART[] = {"AT+KTCPSTART=1\r\n"};
const uint8_t CONNECT[] = {"CONNECT"};
const uint8_t KTCPCLOSE[] = {"AT+KTCPCLOSE=1,1\r\n"};
const uint8_t KTCPDEL[] = {"AT+KTCPDEL=1\r\n"};
//} ATCmd;

//struct AT_Arg {
//    //    uint8_t KCNXCFG[] = {"AT+KCNXCFG,\"GPRS\",\"CMNET\"\r\n"};
//    uint8_t time; //�涨ʱ����
//    uint8_t count; //�涨����
//    uint8_t *sendstr; //�����ַ���
//    uint8_t sendstrlen; //�����ַ�������
//    uint8_t *checkstr; //�Ա��ַ���
//    uint8_t checkstrlen; //�Ա��ַ�������
//    uint8_t errcode; //������
//};

//��������

static bool HL6528SendCmd(const uint8_t *ss, const uint8_t* cs, const uint8_t* cs1, const uint8_t csl, const uint8_t cnt);
//static void HL6528_IOStart(void);
//static void HL6528_IOClose(void);
static void HL6528_GetIP_Port(void);

void HL6528_Init(void) {
    //��ʼ���˿�
    PWRON_TRIS = 0; //PWN_ON 6528оƬ��Դ����
    PWR_TRIS = 0; //�ⲿ����6528оƬ��Դ
    DSR_TRIS = 0; //�����豸����    
    DTR_TRIS = 0; //�����ն�����
    RTS_TRIS = 0; //����������
    CTS_TRIS = 0; //�����������  
    PWR = 0;
    PWRON = 0;
    CTS = 0;
    RTS = 0;
    DSR = 0;
    DTR = 0;
    //    UART2_Init();
}

bool HL6528_DialingIsERR(void) {
    uint8_t sta; //, cnt, cnt1, IP_bytes, Port_bytes;
    //    uint8_t str_tmp[50]; //�洢�˿ں� [4]='\0'
    //
    //    HL6528_GetIP_Port(str_tmp);
    PWR = 1;
    PWRON = 1;
    CTS = 0;
    RTS = 0;
    DSR = 0;
    DTR = 0;
    OSTimeDlyHMSM(0, 0, 1, 0);
    if (HL6528SendCmd(D1, OK, NULL, 2, 2)) {
        if (HL6528SendCmd(CPIN, READY, NULL, 8, 2)) {
            if (HL6528SendCmd(CREG, _5, _1, 2, 10)) {//��������ģʽ
                if (HL6528SendCmd(KCNXCFG, OK, NULL, 2, 3)) {
                    HL6528_GetIP_Port();//ˢ��IP��ַ�Ͷ˿ں�
                    if (HL6528SendCmd(KTCPCFG1, OK, NULL, 2, 3)) {
                        if (HL6528SendCmd(KTCPSTART, CONNECT, NULL, 7, 5)) {
                            sta = 0;
                        } else
                            sta = 6; //δ����TCP��
                    } else
                        sta = 5; //����TCPʧ��
                } else
                    sta = 4; //����APN������
            } else
                sta = 3; //�ֻ��ź�δ�ҵ�
        } else
            sta = 2; //�ֻ���δ����
    } else
        sta = 1; //ģ����
    return sta;
}

void HL6528_Close(void) {
    uint8_t tmp[20];
    StrCmp stcp;
    ClearBuffer(BufferRead_UART2);
    do {
        DSR = 1; //�л�������AT����
        OSTimeDlyHMSM(0, 0, 1, 0); //��ʱ1s
        DSR = 0; //����������
        stcp.SourceData = tmp;
        stcp.Source_len = UARTGetData(BufferRead_UART2, stcp.SourceData); //��ȡmark
        stcp.CheckData = (uint8_t*) OK;
        stcp.Check_len = 2;
        stcp.GetData = NULL;
        stcp.Get_len = 0;
        stcp.Real_len = 0;
    } while (UARTDataIsRight(&stcp)); //�ȴ����ܳɹ����߷���OK
    if (HL6528SendCmd(KTCPCLOSE, OK, NULL, 2, 2))//�رղ�ɾ��TCP��IDͨ��
        HL6528SendCmd(KTCPDEL, OK, NULL, 2, 2);
    OSTimeDlyHMSM(0, 0, 1, 0); //��ʱ1s    
    PWR = 0; //��Դ����
    PWRON = 0; //��Դ�ر�
    CTS = 0; //�������
    RTS = 0; //������
    DSR = 0; //�豸
    DTR = 0; //�ն�
    UART2_Close();
}

/*��������������ַ�����ַss�������ַ����������ַ������ȡ������ַ������ȡ��Ա��ַ�����ַ���Ա��ַ������ȡ����ͼ��ʱ�䡢���ʹ���**/
static bool HL6528SendCmd(const uint8_t *ss, const uint8_t* cs, const uint8_t* cs1, const uint8_t csl, const uint8_t cnt) {
    uint8_t cnt_tmp = 0;
    bool b_sta = false;
    StrCmp stcp;
    uint8_t tmp[50];
    do {
        cnt_tmp += 1;
        UART2_SendString(ss); //����ATָ��                               
        OSTimeDlyHMSM(0, 0, 3, 0); //��ʱ1s
        U2Rx4Byte();
        stcp.SourceData = tmp;
        stcp.Source_len = UARTGetData(BufferRead_UART2, stcp.SourceData); //��ȡmark
        stcp.CheckData = (uint8_t*) cs;
        stcp.Check_len = csl;
        stcp.GetData = NULL;
        stcp.Get_len = 0;
        stcp.Real_len = 0;

        if (UARTDataIsRight(&stcp)) {
            b_sta = true;
            break;
        }

        if (cs1 != NULL) {//����ڶ���У�����ݲ���NULL����ô���еڶ�������ͷ�Ĵ����жϴ���
            stcp.CheckData = (uint8_t*) cs1;
            if (UARTDataIsRight(&stcp)) {
                b_sta = true;
                break;
            }
        }

    } while (cnt > cnt_tmp);
    ClearBuffer(BufferRead_UART2);
    return b_sta;
}

//static void HL6528_IOStart(void) {
//    PWR = 1;
//    PWRON = 1;
//    CTS = 0;
//    RTS = 0;
//    DSR = 0;
//    DTR = 0;
//}
//
//static void HL6528_IOClose(void) {
//    PWRON = 0;
//    PWR = 0;
//    CTS = 1;
//    RTS = 1;
//    DSR = 1;
//    DTR = 1;
//}

static void HL6528_GetIP_Port(void) {
    struct WGC_ARG arg_tmp;
    uint8_t str_tmp[5]; //�洢�˿ں�
    uint8_t IP_bytes, Port_bytes;
    //    uint8_t *ptr_tmp = dat;

    WGC_Get_Arg(&arg_tmp); //��ȡWGC����
    IP_bytes = strlen(arg_tmp.Net_arg.IP_Addr); //����WGC�������������IP��ַ���ֽ���
    Port_bytes = my_itoa(arg_tmp.Net_arg.Port, str_tmp); //��port��ת��Ϊ�ַ���
    CopyDat(KTCPCFG1, KTCPCFG, 16);
    CopyDat(KTCPCFG1 + 16, (const uint8_t*) arg_tmp.Net_arg.IP_Addr, IP_bytes);
    *(KTCPCFG1 + IP_bytes + 16) = '\"';
    *(KTCPCFG1 + IP_bytes + 17) = ',';
    CopyDat(KTCPCFG1 + IP_bytes + 18, (const uint8_t*) str_tmp, Port_bytes);
    //    for (cnt = 0; cnt < IP_bytes; cnt++)
    //        *(dat + cnt) = *(arg_tmp.Net_arg.IP_Addr + cnt);
    //    for (cnt = 0; cnt < Port_bytes; cnt++)
    //        *(dat + cnt) = *(str_tmp + cnt);
    *(KTCPCFG1 + IP_bytes + Port_bytes + 18) = '\r';
    *(KTCPCFG1 + IP_bytes + Port_bytes + 19) = '\n';
    *(KTCPCFG1 + IP_bytes + Port_bytes + 20) = '\0';
    //                    *(ptr_tmp + cnt + 3) = '\0'; 
}






