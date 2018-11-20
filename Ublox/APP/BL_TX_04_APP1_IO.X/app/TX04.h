/* 
 * File:   TX04.h
 * Author: Administrator
 *
 * Created on January 4, 2018, 10:40 AM
 */

#ifndef TX04_H
#define	TX04_H


/***************************************************************************
 * Includes
 ***************************************************************************/
#include "DefType.h"
#include "Common.h"
#include "UART2.h"
#include "UART1.h"
#include "INT.h"
#include "TIM.h"
#include "ublox_g350.h"
#include "CheckData.h"
#include "Debug.h"

/***************************************************************************
 * Defines
 ***************************************************************************/
extern const char USER_READY[]; // ������ָ���
extern const char TX04_TXYBJT[]; // = {"+TXYBJT "}; //TX04���߽���֡ͷ
extern const char TX04_TESTW0_Rec[]; // = {"+RECW0"};
extern const char TX04_TESTW2_Rec[]; // = {"+RECW2"};
extern const char TX04_TECH_Rec[]; // = {"+TXYBJT DTU Software,VERtrkj_v04.0\r\n"};
//extern const char TX04_GPSQ_Rec[]; // = {"CSQ_11"};
//extern const char TX04_GPST_Rec[]; //= {"DW: \"XXXX\",\"XXXX\",\"APN\""};
extern const char TX04_SEND_OFF[];
extern const char TX04_HEARTBEAT[];
extern const uint32_t STORE_ARG1_ADD; //= 0x00AD00; //��������ڳ���洢���е�λ��
extern const uint32_t STORE_ARG2_ADD; // = 0x00AE00; //�������2�ڳ���洢���е�λ��
extern volatile Bool gExitSleep; //˯�߱�־
extern volatile uint8_t gGPRSIsONline; //���߱�־λ
extern volatile uint8_t gTX04Sta; //GPRS״̬ ����״̬  TCP״̬ UDP״̬ GSM״̬

//Ublox��״̬
#define TX04_Sta_Ready                     0x70    //����״̬	
#define TX04_Sta_TCP_Server_Cop            0x76
#define TX04_Sta_TCP_Cop                   0x77    //TCP����״̬	
#define TX04_Sta_UDP_Cop                   0x78    //UDP����״̬							
#define TX04_Sta_GSM_Cop                   0x79    //GSM����״̬		

//#define TX04_ARG_CONTROL_MODE_SOFEWARE  0x30//�������
#define TX04_ARG_CONTROL_MODE_HARDWARE  0x31//EN����
#define TX04_ARG_TCP_UDP_TCP            0x30//TCPЭ��
#define TX04_ARG_TCP_UDP_UDP            0x31//UDPЭ��
#define TX04_ARG_WORK_MODE_GPRS         0x30//����Э��
#define TX04_ARG_WORK_MODE_GSM          0x31//����ͨѶ

//#define TX04_GSM_Work_Mode              0x60    //���Ź���ģʽ
#define TX04_GSM_Work_Mode_S            0x61    //���Ź���ģʽ����ģʽ
#define TX04_GSM_Work_Mode_R            0x62    //���Ź���ģʽ����ģʽ
//#define TX04_GPRS_TCP_Work_Server_Mode  0x70    //TCP�����ģʽ
//#define TX04_GPRS_TCP_Work_Server_Mode_S  0x71    //TCP�����ģʽ
//#define TX04_GPRS_TCP_Work_Server_Mode_R  0x72    //TCP�����ģʽ
//#define TX04_GPRS_TCP_Work_Client_Mode  0x80    //TCP�ͷ���ģʽ
#define TX04_GPRS_TCP_Work_Client_Mode_S  0x81    //TCP�ͷ���ģʽ
#define TX04_GPRS_TCP_Work_Client_Mode_R  0x82    //TCP�ͷ���ģʽ
//#define TX04_GPRS_UDP_Work_Server_Mode  0x09    //UDP�����ģʽ
//#define TX04_GPRS_UDP_Work_Client_Mode  0x90    //UDP�ͷ���ģʽ
#define TX04_GPRS_UDP_Work_Mode_S  0x91    //UDP�ͷ���ģʽ
#define TX04_GPRS_UDP_Work_Mode_R  0x92    //UDP�ͷ���ģʽ


#define CMDIsGetVer(x)   ((x == CMD_TECH) ? True : False)
#define TX04IsWorkSta(x)    ((x == TX04_Sta_TCP_Cop) ||\
                            (x == TX04_Sta_GSM_Cop) ||\
                            (x == TX04_Sta_UDP_Cop) ||\
                            (x == TX04_Sta_TCP_Server_Cop))            //�ж��Ƿ���ת̨

/***************************************************************************
 * Typedef
 ***************************************************************************/
typedef struct TX04arg {
    uint8_t IP[4]; //IP��ַ
    uint16_t Port; //�˿�  ��β�ˣ�С�˴洢��ʽ little Endian��
    uint8_t WorkMode; //����ģʽ 0x31GSM
    uint8_t TCP_UDP; //TCP_UDP
    uint8_t DNSMode; //DNS������ʽ
    uint8_t SMSTargetNumber1Length; //����Ŀ�����1����
    uint8_t SMSTargetNumber1[6]; //����Ŀ�����1
    uint8_t SMSMonitoringCenterNumber1Length; //����Ϣ������ĺ���1����
    uint8_t SMSMonitoringCenterNumber1[6]; //����Ϣ������ĺ���1
    uint8_t SignalQualityEnable; //�ź�ǿ�ȼ��ʹ��
    uint8_t ControlMode; //30H:�������   31H:EN����
    uint8_t BaudRate; //ͨ�Ų�����
    uint16_t RestartTime; //����ʱ�� Low First ��β�ˣ�С�˴洢��ʽ little Endian��
    uint16_t HeartTime; //������ʱ�� ��β�ˣ�С�˴洢��ʽ little Endian��
    uint16_t ListenTime; //����ʱ�� ��β�ˣ�С�˴洢��ʽ little Endian��
    uint8_t CSMode; //�ͻ�����ģʽ
    uint8_t DNSDomainNameLength; //DNS��������
    uint8_t DNSDomainName[31]; //DNS����
    uint8_t APNNameLength; //APN���Ƴ���
    uint8_t APNName[31]; //APN����
    uint8_t ReportEN; //��ͷʹ��
    uint8_t SimNumberLength; //�������볤��
    uint8_t SimNumber[6]; //��������
    uint8_t SMSTargetNumber2Length; //����Ŀ�����2����
    uint8_t SMSTargetNumber2[6]; //����Ŀ�����2
    uint8_t SMSMonitoringCenterNumber2Length; //����Ϣ������ĺ���2����
    uint8_t SMSMonitoringCenterNumber2[6]; //����Ϣ������ĺ���2
    uint8_t Reserve[9]; //���� 
    uint16_t CRC16; //CRCУ��ֵ
} TX04ARG;
extern/* volatile*/ TX04ARG TX04Arg_S;
extern/* volatile*/ TX04ARG TX04Arg2_S;
extern TX04ARG RunArg; //�ṹ��

enum CMD_TP { //ָ�����Ͷ��� ע�����Ҫ���㿪ʼ����ƫ�������й�  //����������TX04_CMD_ARRY���Ͷ�Ӧ
    CMD_TESTW0 = 0x0 /*д����0*/, CMD_TESTW2 = 0x1 /*д����1*/, CMD_TESTR0 = 0x2 /*������0*/, CMD_TESTR2 = 0x3 /*������1*/, CMD_TECH = 0x4 /*��ȡ�汾��*/,
    CMD_GPON = 0x5 /*����*/, CMD_GPOF = 0x6 /*����*/, CMD_GPSQ = 0x7 /*����ǿ��*/, CMD_GPCH1 = 0x8 /*�л�����*/, CMD_GPCH2 = 0x9, /*�л�����*/
    CMD_GPSM = 0xA /*ǿ�ƶ���һ*/, CMD_GPSS = 0xB /*ǿ�ƶ��Ŷ�*/, CMD_GPST = 0xC /*��ȡ������Ϣ*/, CMD_GRCH = 0xD/*SMS�л�����*/, CMD_GROF = 0xE /*SMS����*/,
    CMD_GPID = 0xF /*��ȡICCID*/, CMD_NO_CMD = 0x10 /*û����Ч��ָ��*/
};
extern enum CMD_TP cmd_tp;

extern volatile uint8_t gTX04Sta;
/***************************************************************************
 * Prototype
 ***************************************************************************/
extern void TX04_Init(void);
extern Bool TX04WriteArgByCMD(const uint32_t argadd, uartsendstring uart, uint8_t *Ublox_buf);
extern void TX04ReadArgByCMD(uartsendstring uart, CMDTYPE cmd, TX04ARG* tx04arg);
extern void TX04ReadSofewareVersionByCMD(uartsendstring uart, Bool);
extern void TX04ReadCSQByCMD(uartsendstring uart);
extern void TX04ReadLocInfoByCMD(uartsendstring uart);
extern void TX04ReadSIMIDByCMD(uartsendstring uart);
extern uint8_t IsGetMasthead(const uint8_t * Ublox_buf, const uint8_t bytes);
extern Bool IsDisconnect(const uint8_t * Ublox_buf, const uint8_t bytes);
extern CMDTYPE TX04GetCMDType(const uint8_t* Ublox_buf, const uint8_t bytes);
extern uint8_t TX04GetWorkMode(TX04ARG tx04arg);
extern uint8_t TX04Connect(uint8_t workmode, uint8_t *);
extern Bool TX04DataInterchange(uint8_t workmode);
//extern void User_PrintErrCode(uartsendstring uart, uint8_t errcode);
extern Bool ControlModeIsEN(void);
extern void TX04Sleep(void);
extern uint8_t TX04GetMasthead(uint8_t*);
extern void TX04GetRunArg(void);
extern void ChangeBaudRate(void);
extern Bool CMDRec_HandleCmd(uartsendstring uart, CMDTYPE cmdtype, uint8_t * Ublox_buf);
extern void TX04ReportMasthead(uint8_t workmode);
extern Bool BootLoader(void);
extern Bool TX04SMSArgIsRight(uint8_t workmode);
extern void LED_Blink(uint8_t Cnt, uint8_t Dly100ms);

#endif	/* WVC_H */
//�����û��Ĵ�����ʾ
//#define Ublox_USER_FAIL_01                1    //GPRSģ���ϵ��ʼ��ʧ�ܣ�δ�忨��GPRSоƬ�쳣����Դ��ѹ�쳣
//#define Ublox_USER_FAIL_02                2    //��ջ�򿪴��󣺿���GPRSģ�黵��δ������λ
//#define Ublox_USER_FAIL_03                3    //��GPRSʧ�ܣ����źŻ��������
//#define Ublox_USER_FAIL_04                4    //����APNʧ�ܣ�APN���ô�����������
//#define Ublox_USER_FAIL_05                5    //��ʼGPRSʧ�ܣ����źŻ��������
//#define Ublox_USER_FAIL_06                6    //TCP CLIENTģʽ����ʧ�ܣ������δ���߼���
//#define Ublox_USER_FAIL_07                7    //���Ӻ�����ͨ��ʧ�ܣ����źŻ��������
//#define Ublox_USER_FAIL_08                8    //TCP SERVERģʽ����������ʧ�ܣ�APN���ô����������ϻ�˿�����
//#define Ublox_USER_FAIL_09                9    //�����ģʽδ�������ͻ������ߣ��ͻ���δ���߳�ʱ�����ź�
//#define Ublox_USER_FAIL_10                10    //���߹��̸�λ����Դ��ѹ������λ
//#define Ublox_USER_FAIL_11                11    //���ź������ô�������
//#define Ublox_USER_FAIL_14                14    //���Ͷ���Ŀ����󣺵�Դ��ѹ�ͻ����������λ
//#define Ublox_USER_FAIL_15                15    //��������ֹͣ����, ��GPRS������������ֹͣ�������˳�����GPRS
//#define Ublox_USER_FAIL_16                16    //������·���ϣ���GPRS����������·���϶��˳�����GPRS
//#define Ublox_USER_FAIL_17                17    //��GPRSʧ�ܣ��ֻ���Ƿ�ѻ�ͣ��
//#define Ublox_USER_FAIL_18                18    //���ߴﵽ�������ﵽ�����еĹ涨���ߴ���
