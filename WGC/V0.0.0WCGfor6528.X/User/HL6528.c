//#include "HL6528.h"
#include "includes.h"
#include <stdbool.h>
//#include "cJSON.h"


extern OS_EVENT* sem1, *sem2; //���߲��������־

//struct ATCommand {
const uint8_t K3[] = {"AT&K3\r\n"}; //{"AT&K3\r\n"};
const uint8_t D1[] = {"AT&D1\r\n"}; //{"AT&K3\r\n"};
const uint8_t AT[] = {"AT\r\n"};
const uint8_t CREG_2[] = {"AT+CREG=2\r\n"};
const uint8_t OK[] = {"OK"};
const uint8_t CPIN[] = {"AT+CPIN?\r\n"};
const uint8_t READY[] = {"+CPIN: READY"};
const uint8_t CIMIp[] = {"AT+CIMI\r\n"};
const uint8_t CREG[] = {"AT+CREG?\r\n"};
const uint8_t CGREG[] = {"AT+CGREG?\r\n"};
const uint8_t _5[] = {",5"};
const uint8_t CSCA[] = {"AT+CSCA\r\n"};
//const uint8_t KCNXCFG[] = {"AT+KCNXCFG"};
const uint8_t KCNXCFG[] = {"AT+KCNXCFG=1,\"GPRS\",\"CMNET\"\r\n"};
//const uint8_t KTCPCFG[] = {"AT+KTCPCFG"};
const uint8_t KTCPCFG[] = {"AT+KTCPCFG=1,0,\"183.246.74.68\",5070\r\n"};
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

static bool HL6528SendCmd(const uint8_t *ss, uint8_t* rs, const uint8_t rsl, const uint8_t* cs, const uint8_t csl, const uint8_t second, const uint8_t cnt);
static void HL6528Start(void);
static void HL6528Close(void);

void HL6528_Init(void) {
    //��ʼ���˿�
    PWRON_TRIS = 0; //PWN_ON 6528оƬ��Դ����
    PWR_TRIS = 0; //�ⲿ����6528оƬ��Դ
    DSR_TRIS = 0; //�����豸����    
    DTR_TRIS = 0; //�����ն�����
    RTS_TRIS = 0; //����������
    CTS_TRIS = 0; //�����������    	
    UART2_Init();
}

void HL6528_Dialing(void* arg) {
    INT8U err;
    uint8_t errcode = 0; //, LastID;
    //    bool ATIsCompete = false;
    //    struct AT_Arg aarg;
    HL6528Start();
    while (1) {
        OSSemPend(sem2, 0, &err);

        if (HL6528SendCmd(D1, NULL, 0, OK, 2, 1, 3))
            if (HL6528SendCmd(CPIN, NULL, 0, READY, 8, 1, 3))
                if (HL6528SendCmd(CREG, NULL, 0, _5, 2, 1, 50))
                    //��������ģʽ
                    if (HL6528SendCmd(KCNXCFG, NULL, 0, OK, 2, 1, 3))
                        if (HL6528SendCmd(KTCPCFG, NULL, 0, OK, 2, 1, 3))
                            if (HL6528SendCmd(KTCPSTART, NULL, 0, CONNECT, 7, 6, 2))
                                errcode = 0;
                            else
                                errcode = 6; //δ����TCP��
                        else
                            errcode = 5; //����TCPʧ��
                    else
                        errcode = 4; //����APN������
                else
                    errcode = 3; //�ֻ��ź�δ�ҵ�
            else
                errcode = 2; //�ֻ���δ����
        else
            errcode = 1; //ģ����

        if (!errcode) {
            //������ųɹ�����ô���������²���
            UART2_SendString("hello world!!!");
            UART2_SendString("hello world!!!");
            UART2_SendString("hello world!!!");
            OSTimeDlyHMSM(0, 0, 1, 0); //��ʱ1
            DSR = 1;
            OSTimeDlyHMSM(0, 0, 1, 0); //��ʱ1s
            DSR = 0;
            OSTimeDlyHMSM(0, 0, 1, 0); //��ʱ1s
            if (HL6528SendCmd(KTCPCLOSE, NULL, 0, OK, 2, 1, 3))//�رղ�ɾ��TCP��IDͨ��
                HL6528SendCmd(KTCPDEL, NULL, 0, OK, 2, 1, 3);
        } else {
            UART2_SendString("ERRORCODE:");//����485ͨѶ
            UART2_SendChar(errcode + 0x30);
            UART2_SendString("\r\n");
        }
        HL6528Close();
        OSSemPost(sem1);
    }
}

/*��������������ַ�����ַss�������ַ����������ַ������ȡ������ַ������ȡ��Ա��ַ�����ַ���Ա��ַ������ȡ����ͼ��ʱ�䡢���ʹ���**/
static bool HL6528SendCmd(const uint8_t *ss, uint8_t* rs, const uint8_t rsl, const uint8_t* cs, const uint8_t csl, const uint8_t second, const uint8_t cnt) {
    uint8_t cnt_tmp = 0;
    do {
        cnt_tmp += 1;
        UART2_SendString(ss); //����ATָ��                               
        OSTimeDlyHMSM(0, 0, second, 0); //��ʱ1s
        U2Rx4Byte();
        if (UARTIsGet(BufferRead_UART2, rs, rsl, cs, csl) > 0) {
            return true;
            break;
        }
    } while (cnt > cnt_tmp);
    ClearBuffer2();
    return false;
}

static void HL6528Start(void) {
    PWR = 1;
    PWRON = 1;
    CTS = 0;
    RTS = 0;
    DSR = 0;
    DTR = 0;
}

static void HL6528Close(void) {
    PWRON = 0;
    PWR = 0;
    CTS = 1;
    RTS = 1;
    DSR = 1;
    DTR = 1;
}

