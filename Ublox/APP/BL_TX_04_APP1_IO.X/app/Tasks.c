//#include "Tasks.h"
#include "TX04.h"
#include "DefType.h"
#include <xc.h>

//static volatile uint8_t gCmdType = CMD_NO_CMD;
extern volatile uint8_t gGPRSIsONline; //���߱�־λ;
//extern volatile uint8_t gTX04WorkMode;
extern volatile Bool gRefreshArg;
extern volatile Bool gMasteadType;
extern volatile Bool gReloadGPRS;
extern volatile Bool gSMSInfo; //����һ
extern GPRS_Arg G350_Arg;
extern const uint8_t TX04_NET_FIND_CODE[];
extern const uint8_t TX04_CONNECT_CODE[];
extern uint16_t GetT1Count(void);
extern void PrintErr(uint8_t);

/***************************************************************************
Function: Task1Upload 
Description: ����ָ��
Input: ����ָ��
Output: void
Return: none
Others: none
 ***************************************************************************/
Bool Task1Upload(void *arg) {//TX04FCON upload_TX04f) {
    TX04ARG tx04arg = *((TX04ARG*) arg); //��ȡTX04����
    uint8_t Ub_online_code = 0, finish_code = 0; //Ublox״̬
    Bool sta = False;

    //    if (gTX04Sta == TX04_Sta_TCP_Server_Cop) {//����Ƿ���˵Ļ����������������ָ�ʼ������;��֮����ʼ������
    //        Ub_online_code = G350_F_NET_SIZE;
    //    } else
    Ub_online_code = Ublox_Find_Network(G350_F_NET_SIZE); //��������
    if (Ub_online_code == G350_F_NET_SIZE) {//���ݲ��������󣬲�������
        if (tx04arg.SignalQualityEnable == 0x31) {//�Ƿ�ʼ�ź�ǰ��
            TX04ReadCSQByCMD(UART2SendString); //�û����ڷ����ź�ǿ��
        }
        do {//�л����Ĳ���������Ҫ�����һ�վ
            gReloadGPRS = False; //����һֱѭ��
            gTX04Sta = TX04GetWorkMode(RunArg); //��ȡ����״̬
            if (!TX04SMSArgIsRight(gTX04Sta)) {//���ź��볤���ж�
                break;
            }
            Ub_online_code = TX04Connect(gTX04Sta, &finish_code); //���ݹ���ģʽ����ʼ��������
            if (Ub_online_code == finish_code) {//������߳ɹ��Ļ�����������            
                gGPRSIsONline = 1;
                GLED = 1; //��������ָʾ��
                USER_LK = 1; //LK�ø�
                TX04ReportMasthead(gTX04Sta); //���ͱ�ͷ
                UART2SendString((uint8_t*) "OK\r\n", 4); //������ʾ��Ϣ
                Delay100ms(1); //��ʱһ��ʱ��ȴ�����
                TX04DataInterchange(gTX04Sta); //��������  
                sta = True;
            } else
                PrintErr(TX04_CONNECT_CODE[Ub_online_code]);
        } while (gReloadGPRS);
    } else {
        PrintErr(TX04_NET_FIND_CODE[Ub_online_code]);
    }
    if (gRefreshArg) {//GPRS���ߣ����ģ����Ҫ������������Ļ�����־λ����������ز���
        gRefreshArg = 0;
        gSMSInfo = 0;
        CopyDat((uint8_t*) & RunArg, (uint8_t*) & TX04Arg_S, 130); //ˢ�²����������ظ��������ģʽ
    }
    gGPRSIsONline = 0; //���߱�־���
    CloseUART1(); //�رմ��� ע��˳�򣬲�Ȼ�ᵼ��UARTERR�ж�
    CloseUblox(); //�ر�Ublox
    //    Delay100ms(20);
    return sta;
}

/***************************************************************************
Function: Task3InitWriteArg
Description: ����AT�����Ublox
Input: ss(�������ݵ�ַ);cs(�Ա����ݵ�ַ);csl(�Ա����ݳ���);cnt(��������)
Output: void
Return: True:���ͳɹ���False:����ʧ��
Others: none
 ***************************************************************************/
void Task3InitWriteArg(void) {
    ////    #define Debug_10s
    Bool TECH_is_get = False; //�ж��Ƿ�һֱ�ǵȴ�����д���״̬ ��10s��ʱ��������
    uint8_t getsize = 0, headsize = 0; //��ȡ�����ֽ���������֡��ʼʶ���λ��
    uint8_t Ublox_buf[256]; //���շ�����������
    uint8_t gCmdType = CMD_NO_CMD; //���ָ��
    uint16_t NowT1Cnt = 0, StartT1Cut = 0;
#ifdef Debug_10s
    DeBug_PrintInfo("start of 10s!!!\r\n");
#endif
    StartT1Cut = GetT1Count(); //��ȡ��ǰʱ��
    NowT1Cnt = StartT1Cut;
    do {//����趨ʱ��û�����Ѿ���ѭ����
        Idle(); //��������ģʽ            
        getsize = UARTGetDat(BufferRead_UART2, Ublox_buf, sizeof (Ublox_buf), 6); //������ȡ������С�ֽ�����12->��+TURONG TECH��,������ȡ����ʱ��100ms->12/120
        if (getsize >= 12) {
            headsize = IsGetMasthead(Ublox_buf, getsize); //�жϵ�һ���ֽ� 
            if (headsize) {//�ж��Ƿ��ȡ��+TXYBJT������IsGetMasthead���ص�λ�ã������0�Ļ�����ʾû�н��յ�                                    
                gCmdType = TX04GetCMDType(Ublox_buf, getsize); //�ж�ָ����������
                getsize = 0; //�����ȡ���� 
                if (CMDRec_HandleCmd(UART2SendString, gCmdType, Ublox_buf + headsize - 1)) //����ָ������� tͨ��ָ���ж��Ƿ�Ҫ�˳�
                    break;
                if (CMDIsGetVer(gCmdType))//�Ƿ��Ǽ���ָ���ô��ʱ��ֹͣ��ʱ���ͻ�������һֱ����
                    TECH_is_get = True;
            }
        }
        if ((RunArg.ControlMode == TX04_ARG_CONTROL_MODE_HARDWARE) && !TECH_is_get) {//�����EN����ģʽ������techָ��û�н��ܵ�
            NowT1Cnt = GetT1Count();
            if (NowT1Cnt - StartT1Cut > 10)//���ʱ�����10s����ô�˳�
                break;
        }
        gCmdType = CMD_NO_CMD;
    } while (1); //����ѭ�������в�������  ����ʱ��С��0��EN����ģʽ������ѭ��
#ifdef Debug_10s
    DeBug_PrintInfo("End of 10s!!!\r\n");
#endif
    OpenUblox(); //����Ublox 
    OpenUART1(); //�ڴ�Ublox��������ж� ע��˳�򣬲�Ȼ�ᵼ��UARTERR�ж�
    LP_Delay(150); //�͹�����ʱ500ms���ȴ�ublox��������
}





