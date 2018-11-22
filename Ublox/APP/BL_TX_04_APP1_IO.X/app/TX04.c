#include "TX04.h"
#include "Flash.h"
#include "config.h"
#include "ublox_g350.h"
#include "UART2.h"

/***************************************************************************
 * Defines
 ***************************************************************************/
const char USER_READY[] = {"READY\r\n"}; //������ָ��//����ָ�������
const char TX04_SEND_OFF[] = {"GPOFF\r\n"};
const char TX04_SEND_OFF1[] = {"GPOFF1\r\n"};
const char TX04_SEND_OFF2[] = {"GPOFF2\r\n"};
const char TX04_TXYBJT[] = {"+TXYBJT "}; //TX04���߽���֡ͷ
const char TX04_TURONG[] = {"+TURONG "}; //TX04���߽���֡ͷ
const char TX04_TESTW0_Rec[] = {"+RECW0"};
const char TX04_TESTW2_Rec[] = {"+RECW2"};
const char TX04_TECH_Rec[] = {"DTU Software,VERdowa_v01.07\r\n"};
const char TX04_CMD_ARRY[16][4] = {//ָ������
    "STW0", "STW2", "STR0", "STR2", "TECH",
    "GPON", "GPOF", "GPSQ", "PCH1", "PCH2",
    "GPSM", "GPSS", "GPST", "GRCH", "GROF",
    "GPID"
};
//const char TX04_ERRCODE[] = {"FAIL_"};
const char TX04_DISCONNECT[] = {"DISCONNECT\r\n"}; //TX04���߽���֡ͷ
const char TX04_CSQ[] = {"CSQ"};
const char TX04_TX[] = {"TX:"};
const char TX04_HEARTBEAT[] = {"HEARTBEAT\r\n"};

const unsigned long STORE_ARG1_ADD = 0xA600; //��������ڳ���洢���е�λ��
const unsigned long STORE_ARG2_ADD = 0xA700; //�������2�ڳ���洢���е�λ��
const uint16_t BaudRateArry[] = {4800, 9600, 19200, 1200, 2400}; //������

const uint8_t TX04DefualtArg[] = {//Ĭ�ϲ���
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x30, 0x0B,
    0x13, 0x84, 0x44, 0x44, 0x44, 0x5F, 0x0B, 0x13, 0x82, 0x22,
    0x22, 0x22, 0x0F, 0x30, 0x31, 0x33, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x30, 0x0D, 0x77, 0x77, 0x77, 0x2E, 0x62, 0x61,
    0x69, 0x64, 0x75, 0x2E, 0x63, 0x6F, 0x6D, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x05, 0x43, 0x4D, 0x4E, 0x45,
    0x54, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x31, 0x0B, 0x13,
    0x12, 0x44, 0x54, 0x11, 0x2F, 0x0B, 0x18, 0x86, 0x21, 0x44,
    0x20, 0x4F, 0x0B, 0x13, 0x01, 0x03, 0x60, 0x50, 0x0F, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x53, 0x41
};

extern enum CMD_TP cmd_tp; //����ָ��˳��
volatile Bool gRefreshArg = False; //
volatile Bool gMasteadType = False; //�Ƿ��Ǳ�ͷ
volatile Bool gReloadGPRS = False; //
volatile Bool gSMSInfo = False; //����һ
extern volatile uint16_t gT1Count_Reset;
extern volatile uint16_t gT1Count_Heart;
extern volatile uint16_t gT1Count_Listen;
extern const char BL_REMOTE_PASSWD[]; //Զ����������TR_10_

/***************************************************************************
 * States
 ***************************************************************************/

enum argposition {
    ip = 0, port = 4, workmode = 6, tcp_udp = 7, dnsmode = 8,
    smstargetnumber1length = 9, smstargetnumber1 = 10,
    smsmonitoringcenternumber1length = 16, smsmonitoringcenternumber1 = 17,
    signalqualityenable = 23, controlmode = 24,
    baudrate = 25, restarttime = 26, hearttime = 28,
    listentime = 30, csmode = 32, dnsdomainnamelength = 33,
    dnsdomainname = 34, apnnamelength = 65, apnname = 66,
    reporten = 97, simnumberlength = 98, simnumber = 99, smstargetnumber2length = 105,
    smstargetnumber2 = 106, smsmonitoringcenternumber2length = 112,
    smsmonitoringcenternumber2 = 113, connectcnt = 119, reserve = 120, end = 128//��ӽ����ֽ���
};
enum argposition p;
/***************************************************************************
 * Statement
 ***************************************************************************/
/*volatile */TX04ARG TX04Arg_S;
/*volatile */TX04ARG TX04Arg2_S; //�ṹ��
/*volatile */TX04ARG RunArg; //�ṹ��
volatile Bool gExitSleep = False;
volatile uint8_t gGPRSIsONline = 0; //���߱�־λ
volatile uint8_t gTX04Sta; //GPRS״̬ ����״̬  TCP״̬ UDP״̬ GSM״̬
extern const char Set_SMS_NEW_TIP[12];
//ȷ�����еĲ���
const uint8_t TX04_NET_FIND_CODE[G350_F_NET_SIZE] = {2, 1, 0, 5, 0}; //�һ�վ������ʾ
const uint8_t TX04_CONNECT_CODE[G350_TCP_Client_SIZE] = {4, 0, 0, 0, 0, 0, 6, 0}; //��TCP���Ӵ�����ʾ


/***************************************************************************
 * Code
 ***************************************************************************/

/***************************************************************************
Function: EnsureRunArg
Description: ����GPRS����
Input:������ַ
Output: 
Return: 
Others: none
 ***************************************************************************/
static void EnsureRunArg(void* tx04arg) {
    uint8_t *ptr;

    ptr = (uint8_t*) tx04arg; //��ȡ�����ĵ�ַ
    CopyDat((uint8_t*) & RunArg, ptr, 130); //�������� �������CRC ����GPCHָ��
}

/***************************************************************************
Function: EnsureRunArg
Description: ����GPRS����
Input:������ַ
Output: 
Return: 
Others: //33H?1200bps//34H?2400bps//30H?4800bps//31H?9600bps//32H?19200bp 
 ***************************************************************************/
void ChangeBaudRate(void) {
    uint16_t uart2_baud;
    if (RunArg.BaudRate > 0x34 && RunArg.BaudRate < 0x30)
        uart2_baud = 1200;
    else
        uart2_baud = BaudRateArry[RunArg.BaudRate - 0x30];
    U2BRG = OSC_Freq / uart2_baud / 4 - 1; //�ı䲨����
}

/***************************************************************************
Function: TX04_Init
Description: TX04��Ʒ��ʼ��1
Input:
Output:
Return:
Othe1rs:
 ***************************************************************************/
void TX04_Init(void) {
    OSCILLATOR_Init(); //��ʼ��ʱ��   
    PIN_MANAGER_Init(); //��ʼ��IO
    INTERRUPT_Init(); //��ʼ���ж�
    TMR1_Init(); //��ʱ��1��ʼ�� ���ڿ���`ָ��
    TMR2_Init(); //��ʱ��2��ʼ�� ���ڽ���˯��
    //    TMR3_Init(); //��ʱ��3��ʼ�� ����������������
    UART1_Init(); //��ʼ��ģ��ͨѶ
    //    INT0_Init(); //��ʼ���ⲿ�ж�0 �½��Ӵ���
    INT1_Init(); //��ʼ���ⲿ�ж�1 �½��Ӵ��� ��ѹ���裬�жϵ�Դ��ѹ�������ѹ�͸�λ�豸
    TX04GetRunArg(); //ȷ�����в���
    UART2_Init(); //��ʼ���û�ͨѶ ע�������GetRunArg���棬�����ж϶�ȡ���� �����ȡд���������
    U2TXREG = '\0'; //���һ���ֽڣ������һ����������
    StartTMR1(); //������ʱ��:��������ʱ�� ����ʱ�䡢����ʱ�䡢ǿ�ƶ���5s
}

/***************************************************************************
Function: TX04Sleep
Description: TX04����˯��ģʽ
Input:
Output:
Return:
Others:
 ***************************************************************************/
void TX04Sleep(void) {//�������� ����Ϊ�ϴ��� ���� IO���� ����
    //�ر�UART1���������ã���������ʱ������IO��Ϊ���0���˳�����ʱ�����ô���ͨѶ
    GLED = 0; //
    //�������˯��
    //��ֹ���ֵ�ѹ��ѹ���� RETEN��RCON<12>�� = 0�� LPCFG��FPOR<2>�� = 1��
    //ʹ�ܱ��ֵ�ѹ��ѹ���� RETEN��RCON<12>�� = 1�� LPCFG��FPOR<2>�� = 0��
    RCONbits.RETEN = 0;
    RCONbits.VREGS = 0; //���ٻ���    
    while (!U1STAbits.RIDLE); //�ȴ��������
    while (!U2STAbits.RIDLE); //�ȴ��������
    U1MODEbits.WAKE = 1; //�жϻ����豸
    U2MODEbits.WAKE = 1;
    gExitSleep = 0;
    while (!gExitSleep) {//�ȴ��жϻ����豸
        Sleep(); //Ҫ���ζ�ʱ��1���ж�
    }
    U1MODEbits.WAKE = 0;
    U2MODEbits.WAKE = 0;
    //ָ����豸  ����ָʾ��
    GLED = 1;
    Delay100ms(1); //�ȴ���ѹ�ȶ�
}

/***************************************************************************
Function: TCP_Bootloader
Description: Զ������������bootloaderģʽ
Input:�������ݣ����ݳ���
Output:
Return:
Others:
 ***************************************************************************/
static void TCP_Bootloader(uint8_t *Ublox_2_buf, uint8_t getsize2) {
    uint8_t cnt;
    if (Str_Find_Head(Ublox_2_buf, BL_REMOTE_PASSWD, getsize2, 6)) {
        for (cnt = 0; cnt < 10; cnt++) {//ָʾ����ʾ 100ms��˸ 5��
            GLED ^= 1;
            Delay100ms(1);
        }
        GLED = 0;
        T1CONbits.TON = 0; //�رն�ʱ��1�����������豸�ͷ���������
        if (BootLoader()) {
            UbloxCloseTCPClient(); //ͨ��ATָ��ر�ģ��                
            USER_LK = 0; //LK�õ�
            GLED = 0;
            UART2SendString((uint8_t*) TX04_SEND_OFF, 7);
            gGPRSIsONline = 0;
            INTCON1bits.ADDRERR = 1; //������ѧ�����жϣ���λ  //IFS1bits.INT1IF = 1; //�����жϣ����븴λ
        }
        T1CONbits.TON = 1; //������ʱ��1��������ʼ��������ʱ��ͷ���������ʱ��
    }
}

/***************************************************************************
Function: TCP_IsDisconnect
Description: TCP�ͷ���ģʽ�£�������Ƿ�Ͽ�(����DISCONNECT)
Input:�������ݣ����ݳ���
Output: �Ƿ�Ͽ�
Return: �Ƿ�Ͽ�
Others: none
 ***************************************************************************/
static Bool TCP_IsDisconnect(uint8_t* Ublox_2_buf, uint8_t getsize2) {
    Bool is_disconnnect = False;

    if (Str_Find_Head(Ublox_2_buf, "D", getsize2, 1) > 0) {//�����ȡ��+�ַ� hjksdfa+TXYBJT TECH
        getsize2 += UARTGetDat(BufferRead_UART1, Ublox_2_buf + getsize2, 0xff - getsize2, 8); //120
        if (Str_Find_Head(Ublox_2_buf, TX04_DISCONNECT, getsize2, sizeof (TX04_DISCONNECT) - 1)) {//������Ӽ������ʧ�ܣ����������ر��豸
            PrintErr(15); //��ӡ������ʾFAIL15
            is_disconnnect = True;
        }
    }
    return is_disconnnect;
}

/***************************************************************************
Function: OnlineHandleData
Description: ���ߴ������ݣ�����TCP�ͷ��ˣ�����ˣ�����ӣ���UDP�ͷ��ˣ�����
Input:ģʽmode
Output: �Ƿ���ͨѶ
Return: �Ƿ���ͨѶ
Others: none
 ***************************************************************************/
static Bool OnlineHandleData(uint8_t mode) {
    CMDTYPE cmdtype = 0; //���巵��ָ������
    uint16_t getsize = 0, headsize = 0; //, opcnt = 1; //, cnt;
    uint8_t Ublox_buf[1024]; //�����û��Ľ���
    uartsendstring senddat_f, reccmd_f;
    BufferRead_UARTn readbuf_f;
    Bool has_Cop = False, isneedget = True;

    switch (mode) {
        case TX04_GSM_Work_Mode_S:
        {
            reccmd_f = UART2SendString;
            senddat_f = GSMSendMessage; //GSM
            readbuf_f = BufferRead_UART2;
            break;
        }
        case TX04_GSM_Work_Mode_R:
        {
            reccmd_f = SMSWriteStrByCmd; //����CMD
            senddat_f = SMSWriteRecUser; //�޸�
            readbuf_f = BufferRead_UART1;
            getsize = UbloxSMSGetURC(Ublox_buf, sizeof (Ublox_buf)); //��ȡ��Ч����
            isneedget = False;
            break;
        }
        case TX04_GPRS_UDP_Work_Mode_S:
        {
            reccmd_f = UART2SendString;
            senddat_f = UDPSendDat2Sever;
            readbuf_f = BufferRead_UART2;
            break;
        }
        case TX04_GPRS_UDP_Work_Mode_R:
        {
            reccmd_f = UDPWriteStrByCmd;
            senddat_f = UART2SendString;
            readbuf_f = BufferRead_UART1;
            getsize = UbloxUDPGetURC(Ublox_buf, sizeof (Ublox_buf)); //��ȡ��Ч����
            isneedget = False;
            break;
        }
        case TX04_GPRS_TCP_Work_Client_Mode_S:
        {
            reccmd_f = UART2SendString;
            senddat_f = UART1SendString;
            readbuf_f = BufferRead_UART2;
            break;
        }
        case TX04_GPRS_TCP_Work_Client_Mode_R:
        {
            reccmd_f = UART1SendString;
            senddat_f = UART2SendString;
            readbuf_f = BufferRead_UART1;
            break;
        }
    }
    //    ����60msˢ�£�ʱ��̫���������ݷ��ͺͽ��յ�ʱ�����׵���TCP�������ݶ�ʧ�����������������
    if (isneedget)//�Ƿ���Ҫͨ������ֱ�ӻ�ȡ���ݣ�
        getsize = UARTGetDat(readbuf_f, Ublox_buf, sizeof (Ublox_buf), 6); //��ȡ���� 

    //    if (Str_Find_Head(Ublox_buf, "+", getsize, 1) > 0) {//�����ȡ��+�ַ� +TXYBJT TECH12           
    //        getsize += UARTGetDat(readbuf_f, Ublox_buf + getsize, sizeof (Ublox_buf) - getsize, 12); //120
    //    }
    if (getsize) {//����ֽ��жϣ����ˢ��Ч�ʣ�����ģʽ�¿��ܴ�������
        if (mode == TX04_GPRS_TCP_Work_Client_Mode_R) {
            if (TCP_IsDisconnect(Ublox_buf, getsize)) { //���ӳ��� �жϷ�����Ƿ�ر�
                gGPRSIsONline = 0;
                return True; //TCP������Ƿ�ر����ӵ㣬���Թر�ģ��,��ͨѶ������Ҫ��������ģʽ
            } else
                TCP_Bootloader(Ublox_buf, getsize); //�ж�Զ��Զ�����
        }
        //�ж��Ƿ���ָ�� �Լ���ָ��Ϊ��
        headsize = IsGetMasthead(Ublox_buf, getsize);
        if (headsize) {//Ѱ��+TXYBJT
            cmdtype = TX04GetCMDType(Ublox_buf, getsize); //�ж�ָ����������;  
            if (CMDRec_HandleCmd(reccmd_f, cmdtype, Ublox_buf + headsize - 1)) {
                ClearT1ArgCnt();
                gGPRSIsONline = 0;
            }
            has_Cop = True; //�������ݽ���
        } else {
            if (getsize) {//������ܵ��ֽ�����,�������ݸ���������
                senddat_f(Ublox_buf, getsize);
                has_Cop = True;
            }
        }
    }
    return has_Cop;
}

/*************************************
 * Function: GSMCop5s
 * Description: д���ݵ�Flash��
 * Input:������ַ�����ڷ��ͺ��������յ�������
 * Output: 
 * Note:����1�Ͳ���2��ͬһ�������ڣ����Բ����Ļ�����Ҫ��ȡ����һ��������Ȼ�����
 *************************************/
static Bool GSMCop5s(const uint8_t smsinfo) {//Bool=True:��ʾͨѶ�������
    uint8_t getsize = 0, smsinfo_tmp = gSMSInfo;
    uint8_t Ublox_buf[256]; //�����û��Ľ���
    uint16_t delay_time = gT1Count2 + 6;

    //�����еĲ���1�����������number����number_size
    gSMSInfo = smsinfo; //��ʽ���
    while (gT1Count2 <= delay_time) {//TCP��������   ��Ѱ����  
        // ********************(0)********************�û��˵ķ�������ֵ������
        GSMSendMessage(Ublox_buf, getsize);
        // ********************(1)********************����˵Ľ������ݴӷ�����
        getsize = UbloxSMSGetURC(Ublox_buf, getsize); //��ȡ��Ч����
        if (getsize)
            SMSWriteStrByCmd(Ublox_buf, getsize);
    }
    //������Ϻ󣬻�ԭ����1�Ķ��Ų���
    gSMSInfo = smsinfo_tmp;
    return True;
}

/*************************************
 * Function: TX04WriteArgByCMD
 * Description: д���ݵ�Flash��
 * Input:������ַ�����ڷ��ͺ��������յ�������
 * Output: 
 * Note:����1�Ͳ���2��ͬһ�������ڣ����Բ����Ļ�����Ҫ��ȡ����һ��������Ȼ�����
 *************************************/
Bool TX04WriteArgByCMD(const uint32_t argadd, uartsendstring uart, uint8_t * Ublox_buf) {
    uint8_t Send_Buf[300];
    uint16_t offset = 0; // 128;
    uint8_t save_arg1_Buf[520];
    uint8_t save_arg2_Buf[520];
    uint8_t cnt, cnt1;
    uint32_t other_arg = argadd;
    Bool isArg1 = STORE_ARG1_ADD == argadd;
    char *send_ptr;
    TX04ARG *arg_ptr;

    if (CRCIsRight(Ublox_buf, 128, Ublox_buf + 128)) {//�ж�CRCУ���Ƿ���ȷ        
        other_arg = (isArg1) ? STORE_ARG2_ADD : STORE_ARG1_ADD; //�жϽ�����Ҫд������λ�� 
        send_ptr = (isArg1) ? (char *) TX04_TESTW0_Rec : (char *) TX04_TESTW2_Rec;
        arg_ptr = (isArg1) ? &TX04Arg_S : &TX04Arg2_S; //���ò��� д��Flash
        CopyDat(arg_ptr, Ublox_buf, 130); //���ò��� д��Flash
        offset = StrLen(TX04_TESTW0_Rec);
        CopyDat(Send_Buf, send_ptr, offset); //��ֵ���صĿ�ͷ����

        ClearDat(save_arg1_Buf, 0xFF, 512); //
        ClearDat(save_arg2_Buf, 0xFF, 512); //

        ReadArgFromFlash(other_arg, save_arg2_Buf, 176); //��ͬһ�����ڣ������������ݶ�ʧ�����ȶ�ȡ����һ������
        Erase(0, STORE_ARG1_ADD); //����
        for (cnt = 0, cnt1 = 0; cnt < 173; cnt += 4, cnt1 += 3) {
            CopyDat(save_arg1_Buf + cnt, Ublox_buf + cnt1, 3); //��������һ
            *(save_arg1_Buf + cnt + 3) = 0x00;
        }
        save_arg1_Buf[cnt++] = *(Ublox_buf + cnt1++); //���4���ֽ�
        save_arg1_Buf[cnt++] = *(Ublox_buf + cnt1);
        save_arg1_Buf[cnt++] = 0x00;
        save_arg1_Buf[cnt] = 0x00;
        WriteFlashByRow(argadd, save_arg1_Buf, 1); //Ҫ����Ĳ���д��FLash
        WriteFlashByRow(other_arg, save_arg2_Buf, 1); //���ݵ�����һ������д��FLash        

        if ((gTX04Sta == TX04_Sta_GSM_Cop)&&(uart != UART2SendString))//���ŷ��ز������ݵĻ�����Ҫ���Ϊ�ַ���    
            offset += Hex2Char(Ublox_buf, 130, Send_Buf + offset);
        else {
            CopyDat(Send_Buf + offset, Ublox_buf, 130); //��ֵ���� ��CRC
            offset += 130;
        }
        CopyDat(Send_Buf + offset, "\r\n", 2);
        offset += 2;
        uart(Send_Buf, offset); //��������
        Delay100ms(5); //����UDPģʽ
        return True;
    }
    return False;
}

/*************************************
 * Function: TX04ReadArgByCMD
 * Description: ��ȡ����ͨ��ָ��
 * Input:���ڷ��ͺ�����ָ����͵�����
 * Output: 
 * Note:
 *************************************/
void TX04ReadArgByCMD(uartsendstring uart, CMDTYPE cmd, TX04ARG * tx04arg) {
    uint8_t Send_Buf[300]; //, Dat_Buf[150];
    uint16_t offset = StrLen(TX04_TESTW2_Rec);

    if (cmd == CMD_TESTR2)
        CopyDat(Send_Buf, TX04_TESTW2_Rec, offset); //���ɷ�������
    else
        CopyDat(Send_Buf, TX04_TESTW0_Rec, offset); //���ɷ�������
    //����������أ������Ƕ���ƽ̨�����ֻ������Ͷ�ȡ����ָ��Ļ�
    if ((gTX04Sta == TX04_Sta_GSM_Cop)&&(uart != UART2SendString))
        offset += Hex2Char((uint8_t*) tx04arg, 130, Send_Buf + offset);
    else {//�ͻ��˻�ȡ
        CopyDat(Send_Buf + offset, tx04arg, 130); //���ò���
        offset += 130;
    }
    CopyDat(Send_Buf + offset, "\r\n", 2);
    offset += 2;
    uart(Send_Buf, offset); //��������
    //    Delay10ms(1);
}
//ͨ��ָ���ȡ����汾��

/***************************************************************************
Function: TX04ReadSofewareVersionByCMD
Description: ����AT�����Ublox
Input: v
Output: void
Return: True:���ͳɹ���False:����ʧ��
Others: step���ܴ���Ublox_F_NET_ATTACHE��5��
 ***************************************************************************/
void TX04ReadSofewareVersionByCMD(uartsendstring uart, Bool sta) {
    uint8_t tmp[40], bytes = sizeof (TX04_TXYBJT) - 1;

    if (sta)
        CopyDat(tmp, (uint8_t*) TX04_TXYBJT, bytes); //��������
    else
        CopyDat(tmp, (uint8_t*) TX04_TURONG, bytes); //��������  
    CopyDat(tmp + bytes, (uint8_t*) TX04_TECH_Rec, sizeof (TX04_TECH_Rec) - 1); //��������
    bytes += sizeof (TX04_TECH_Rec) - 1;
    uart(tmp, bytes);
}

/***************************************************************************
Function: TX04ReadCSQByCMD
Description: ����AT�����Ublox
Input: ����
Output: void
Return: True:���ͳɹ���False:����ʧ��
Others: step���ܴ���Ublox_F_NET_ATTACHE��5��
 ***************************************************************************/
void TX04ReadCSQByCMD(uartsendstring uart) {

    uint8_t tmp[15], bytes = sizeof (TX04_CSQ) - 1;

    CopyDat(tmp, TX04_CSQ, bytes); //����CSQ
    tmp[bytes++] = '_';
    tmp[bytes++] = ((((uint8_t) G350_Arg.CSQ[0]) - 0x30) << 4)+(((uint8_t) G350_Arg.CSQ[1]) - 0x30);
    tmp[bytes++] = '\r'; //(TX04Cmd.CSQ & 0x0f) + 0x31;
    tmp[bytes++] = '\n'; //(TX04Cmd.CSQ & 0x0f) + 0x31;
    uart(tmp, bytes);
}

/***************************************************************************
Function: TX04ReadLocInfoByCMD
Description: ����AT�����Ublox
Input: ����
Output: void
Return: True:���ͳɹ���False:����ʧ��
Others: step���ܴ���Ublox_F_NET_ATTACHE��5��
 ***************************************************************************/
void TX04ReadLocInfoByCMD(uartsendstring uart) {

    uint8_t tmp[30], bytes = sizeof (TX04_TX) - 1, copy_size = sizeof (G350_Arg.LAC);

    CopyDat(tmp, TX04_TX, bytes);
    CopyDat(tmp + bytes, G350_Arg.LAC, copy_size);
    bytes += copy_size;
    tmp[bytes++] = ',';
    tmp[bytes++] = '\"';
    CopyDat(tmp + bytes, RunArg.APNName, RunArg.APNNameLength);
    bytes += RunArg.APNNameLength;
    tmp[bytes++] = '\"';
    tmp[bytes++] = '\r';
    tmp[bytes++] = '\n';
    uart(tmp, bytes);
}

/***************************************************************************
Function: TX04ReadSIMIDByCMD
Description: ����AT�����Ublox
Input: ����
Output: void
Return: True:���ͳɹ���False:����ʧ��
Others: step���ܴ���Ublox_F_NET_ATTACHE��5��
 ***************************************************************************/
void TX04ReadSIMIDByCMD(uartsendstring uart) {//��ӡ��ȡICCID

    uint8_t tmp[30], bytes = sizeof (TX04_TX) - 1, copy_size = sizeof (G350_Arg.ICCID);

    CopyDat(tmp, TX04_TX, bytes);
    tmp[bytes++] = '\"';
    CopyDat(tmp + bytes, G350_Arg.ICCID, copy_size);
    bytes += copy_size;
    tmp[bytes++] = '\"';
    tmp[bytes++] = '\r';
    tmp[bytes++] = '\n';
    uart(tmp, bytes);
}

/***************************************************************************
Function: TX04GetArgByDialing
Description: ���� ͨ��ATָ���ȡ�������
Input:����
Output: �Ƿ��ȡ�ɹ�
Return: 
Others: none
 ***************************************************************************/
Bool TX04GetArgByDialing(uint8_t arg) {//ͨ�����Ż�ȡICCID������״̬����+TXYBJT GPID
    Bool b_sta = False; //����״̬����
    uint8_t step = 0;

    OpenUblox(); //����Ublox 
    OpenUART1(); //�ڴ�Ublox��������ж�
    Delay100ms(15); //�ȴ��豸��ȫ����
    step = Ublox_Find_Network(arg); //���Ż�ȡ
    if (step == arg) {
        b_sta = True;
        switch (arg) {
            case G350_GET_CCID:
                TX04ReadSIMIDByCMD(UART2SendString);
                break;
            case G350_GET_CSQ:
                TX04ReadCSQByCMD(UART2SendString);
                break;
            case G350_GET_LOC:
                TX04ReadLocInfoByCMD(UART2SendString);
                break;
        }
    }
    CloseUART1(); //�رմ���1
    CloseUblox(); //�ر�Ublox 
    Delay100ms(15); //�ȴ��豸��ȫ�ر�
    UART2SendString((uint8_t*) USER_READY, 7); //���;���״̬

    return b_sta;
}

/***************************************************************************
Function: IntoGSM5S 
Description: GPRS�������ģʽ
Input:ģʽmode ���Ĳ���smsinfo
Output:����ɹ�
Return:
Others:
 ***************************************************************************/
static Bool IntoGSM5S(const uint8_t mode, const uint8_t smsinfo) {//uint8_t sta) {
    Bool sta = False, ready_enter = False;
    uint8_t sms_info[20] = {"ENTER_SMS1\r\n"};

    if (smsinfo)//����Ƕ���2�Ļ� smsinfo=1
        sms_info[9] = smsinfo + 0x31;
    switch (mode) {
        case TX04_Sta_TCP_Cop:
        {
            if (UbloxSwitchFlow(DATA2CMD))
                ready_enter = True;
            break;
        }
        case TX04_Sta_UDP_Cop:
        {
            ready_enter = True;
            break;
        }
        case TX04_Sta_GSM_Cop:
        {
            UART2SendString((uint8_t*) sms_info + 6, 6); //��ʾ�л��ɹ�
            gSMSInfo = smsinfo;
            sta = True;
            break;
        }
    }
    //�Ƿ�������ģʽ�������л�������ģʽ�ɹ�
    if (ready_enter && (Ublox_GSM_Dialing(G350_GSM_Client_SIZE) == G350_GSM_Client_SIZE)) { //�л�������ģʽ
        UART2SendString(sms_info, 12); //��ʾ�л��ɹ�
        USER_LK = 0; //LK�õ�
        GLED = 1; //�̵���
        if (GSMCop5s(smsinfo)) {
            //�����UDPģʽ������ͨѶ�ɹ��������TCPģʽ���л�������ģʽ������ͨѶ�ɹ�        
            if ((mode == TX04_Sta_UDP_Cop) ||
                    ((mode == TX04_Sta_TCP_Cop)&& (UbloxSwitchFlow(CMD2DATA))))//�л����ģ��л���͸��ģʽ  ~+++
                sta = True;
        }
        USER_LK = 1; //LK�ø�
        GLED = 0; //�̵���
    }
    return sta;
}

/***************************************************************************
Function: LED_Blink 
Description: ����LED��˸
Input: ���������ʱ��
Output:
Return:
Others:���ʱ�䵥λ100ms
 ***************************************************************************/
void LED_Blink(uint8_t Cnt, uint8_t Dly100ms) {
    uint8_t cnt;

    GLED = 1;
    for (cnt = 0; cnt < Cnt; cnt++) {
        Delay100ms(Dly100ms); //����Ӳ���ϵ��ظ�������ж�
        GLED ^= 1; //���ĵ���C22������EN����
    }
    GLED = 0; //���һ��Ҫ�ӣ�������������£��Ƴ���
}

/***************************************************************************
Function: IsGetMasthead 
Description: �ж����Ƿ��Ǳ�ͷ//�ж�֡ͷ�Ƿ���TXYBJT,
Input: ����ָ�룬�����ֽ���
Output:�������ڵ��ֽ�λ��+1
Return: �ֽ���
Others: none
 ***************************************************************************/
uint8_t IsGetMasthead(const uint8_t * Ublox_buf, const uint8_t bytes) {
    uint8_t getsize;

    gMasteadType = 1; //��TXYBJT
    getsize = Str_Find_Head(Ublox_buf, TX04_TXYBJT, bytes, sizeof (TX04_TXYBJT) - 1);
    if (!getsize) {
        getsize = Str_Find_Head(Ublox_buf, TX04_TURONG, bytes, sizeof (TX04_TURONG) - 1);
        gMasteadType = 0; //��TURONG
    }
    return getsize;
}

/*************************************
Function: TX04GetCMDType 
Description: ��ȡ�����ܵ�ָ������
Input: �ַ���ָ��Ublox_buf �ַ�������bytes 
Output: �������ʹ���
 *************************************/
CMDTYPE TX04GetCMDType(const uint8_t* Ublox_buf, const uint8_t bytes) {
    int8_t cnt;
    for (cnt = sizeof (TX04_CMD_ARRY); cnt >= 0; cnt--) {//debug�鿴�Ƿ���15������
        if (Str_Find_Head(Ublox_buf, TX04_CMD_ARRY[cnt], bytes, 4)) {
            return cnt;
        }
    }
    return CMD_NO_CMD;
}

/*************************************
Function: CMDRec_HandleCmd 
Description:���ݶ�Ӧ��ָ�������ʾ��Ϣ��������ָ��ж�GPRS�Ƿ�Ҫ���� �������²���
Input: ����n���պ���uart��ָ������cmdtype���ַ���ָ��Ublox_buf 
Output: �Ƿ���Ҫ����
 *************************************/
Bool CMDRec_HandleCmd(uartsendstring uart, CMDTYPE cmdtype, uint8_t * Ublox_buf) {//ָ��ظ�
    uint8_t sta = gTX04Sta;
    Bool is_need_restart = False; // isArg1 = False;
    TX04ARG RunArg1;
    TX04ARG* runarg = &RunArg1;

    switch (cmdtype) {
        case CMD_TESTW0:
        {
            if (TX04WriteArgByCMD(STORE_ARG1_ADD, uart, Ublox_buf + 14)) //����д����1ָ��
            {
                EnsureRunArg(&TX04Arg_S); //�������в���
                switch (sta) {
                    case TX04_Sta_Ready:
                    {//����Ǿ���״̬��д�����һ
                        UART2SendString((uint8_t*) USER_READY, 7); //������ʾ
                        break;
                    }
                    case TX04_Sta_TCP_Cop://ע�� �������break
                    {
                        UbloxCloseTCPClient(); //ͨ��ATָ��ر�ģ��
                    }
                    default:
                    {
                        is_need_restart = True;
                        USER_LK = 0; //LK�õ�
                        GLED = 0;
                        UART2SendString((uint8_t*) TX04_SEND_OFF, 7);
                        break;
                    }
                }
                ChangeBaudRate(); //�ı䲨����
            }
            break;
        }
        case CMD_TESTW2:
        {
            if (TX04WriteArgByCMD(STORE_ARG2_ADD, uart, Ublox_buf + 14)) //����д����2ָ��
            {
                switch (sta) {
                    case TX04_Sta_Ready:
                    {//����Ǿ���״̬��д�����һ
                        UART2SendString((uint8_t*) USER_READY, 7); //������ʾ
                        break;
                    }
                    case TX04_Sta_TCP_Cop://ע�� �������break
                    {
                        UbloxCloseTCPClient(); //ͨ��ATָ��ر�ģ��
                    }
                    default:
                    {
                        is_need_restart = True;
                        USER_LK = 0; //LK�õ�
                        GLED = 0;
                        UART2SendString((uint8_t*) TX04_SEND_OFF, 7);
                        break;
                    }
                }
            }
            break;
        }
        case CMD_TESTR0:
        {
            TX04ReadArgByCMD(uart, CMD_TESTR0, &TX04Arg_S);
            break;
        }
        case CMD_TESTR2:
        {
            TX04ReadArgByCMD(uart, CMD_TESTR2, &TX04Arg2_S);
            break;
        }
        case CMD_TECH:
        {
            TX04ReadSofewareVersionByCMD(uart, gMasteadType);
            break;
        }
        case CMD_GPON:
        {
            if (sta == TX04_Sta_Ready) {//������ʼ��ѭ��  ramark �޸Ĳź������� �Լ�Ӧ�øú���GPOFFָ��������
                is_need_restart = True;
            }
            break; //�ⲿ�������������벦��ģʽ
        }
        case CMD_GPOF:
        {
            if (TX04IsWorkSta(sta)) {
                if ((sta == TX04_Sta_TCP_Cop)) {//�����TCPģʽ
                    UbloxCloseTCPClient(); //ͨ��ATָ��ر�ģ��                    
                }
                USER_LK = 0; //LK�õ�
                UART2SendString(TX04_SEND_OFF, 7);
                LED_Blink(6, 5);
                is_need_restart = True;
            }
            break;
        }
        case CMD_GPSQ:
        {
            if (TX04IsWorkSta(sta)) //����ǲ���״̬����GPRS����ģʽ
                TX04ReadCSQByCMD(uart); //�����ź�ǿ��
            else if (sta == TX04_Sta_Ready) //����Ǿ���״̬�Ļ�������Ҫ��������
                TX04GetArgByDialing(G350_GET_CSQ);
            break;
        }
        case CMD_GPCH1:
        {
            if (sta == TX04_Sta_Ready) {//����Ǿ���״̬
                UART2SendString(TX04_SEND_OFF1, sizeof (TX04_SEND_OFF1) - 1); //����GPOFF1
                EnsureRunArg(&TX04Arg_S);
                ChangeBaudRate();
                UART2SendString(USER_READY, sizeof (USER_READY) - 1); //8�ֽڣ�����ͻ��ж�READY\r\n
                is_need_restart = True; //��Ҫ����ģ��
            }
            if (TX04IsWorkSta(sta)) {//����ǹ���ģʽ                          
                UbloxCloseTCPClient(); //�����TCPģʽ���ȹر����ӵ�
                UbloxDisablePSD(); //�л�������ģʽ
                UART2SendString(TX04_SEND_OFF1, sizeof (TX04_SEND_OFF1)); //����GPOFF1
                EnsureRunArg(&TX04Arg_S);
                ChangeBaudRate(); //�ı䲨����
                gReloadGPRS = True;
                is_need_restart = True;
            }
            break;
        }
        case CMD_GPCH2:
        {
            if ((TX04Arg2_S.Port != 0)&&(TX04Arg2_S.IP[0] + TX04Arg2_S.IP[1] + TX04Arg2_S.IP[2] + TX04Arg2_S.IP[3] != 0)) {//�������������Ч������IP��0,0,0,0 Port:0��
                if (sta == TX04_Sta_Ready) {//����Ǿ���״̬
                    UART2SendString(TX04_SEND_OFF2, sizeof (TX04_SEND_OFF2) - 1); //����GPOFF2
                    EnsureRunArg(&TX04Arg2_S);
                    ChangeBaudRate();
                    UART2SendString(USER_READY, sizeof (USER_READY) - 1); //8�ֽڣ�����ͻ��ж�READY\r\n
                    is_need_restart = True; //��Ҫ����ģ��
                }
                if (TX04IsWorkSta(sta)) {//����ǹ���ģʽ                              
                    UbloxCloseTCPClient(); //�����TCPģʽ���ȹر����ӵ�
                    UbloxDisablePSD(); //�л�������ģʽ
                    UART2SendString(TX04_SEND_OFF2, sizeof (TX04_SEND_OFF2) - 1); //����GPOFF2
                    EnsureRunArg(&TX04Arg2_S);
                    ChangeBaudRate(); //�ı䲨����
                    gReloadGPRS = True;
                    is_need_restart = True;
                }
            }
            break;
        }
        case CMD_GPSM:
        {
            if (sta == TX04_Sta_Ready) {
                CopyDat((uint8_t*) runarg, (uint8_t*) & TX04Arg_S, 130); //��������
                gSMSInfo = 0; //���Ͳ���һ
                runarg->WorkMode = TX04_ARG_WORK_MODE_GSM; //����ģʽ����Ϊ����ģʽ
                EnsureRunArg(runarg); //ȷ�����в���
                gRefreshArg = 1; //����������ǿ�ƶ��ţ�ģ�����ߣ���Ҫ�����������
                is_need_restart = True; //��Ҫ����ģ��
            } else {
                IntoGSM5S(sta, 0); //����ǿ�ƶ���ģʽ
            }
            break;
        }
        case CMD_GPSS:
        {
            if (sta == TX04_Sta_Ready) {
                CopyDat((uint8_t*) runarg, (uint8_t*) & TX04Arg_S, 130); //��������
                gSMSInfo = 1; //���Ͳ�����
                runarg->WorkMode = TX04_ARG_WORK_MODE_GSM; //����ģʽ����Ϊ����ģʽ
                EnsureRunArg(runarg); //ȷ�����в���
                gRefreshArg = 1; //����������ǿ�ƶ��ţ�ģ�����ߣ���Ҫ�����������
                is_need_restart = True;
            } else {
                IntoGSM5S(sta, 1); //����ǿ�ƶ���ģʽ
            }
            break;
        }
        case CMD_GPST:
        {
            if (TX04IsWorkSta(sta))//����ǲ���ת̨����GPRS����ģʽ
                TX04ReadLocInfoByCMD(uart);
            else if (sta == TX04_Sta_Ready) //����Ǿ���״̬�Ļ�������Ҫ��������
                TX04GetArgByDialing(G350_GET_LOC);
            break;
        }
        case CMD_GPID://��ȡID
        {
            if (TX04IsWorkSta(sta))//����ǲ���ת̨����GPRS����ģʽ
                TX04ReadSIMIDByCMD(uart);
            else if (sta == TX04_Sta_Ready) //����Ǿ���״̬�Ļ������Ż�ȡ
                TX04GetArgByDialing(G350_GET_CCID);

            break;
        }
    }
    return is_need_restart;
}

/***************************************************************************
Function: TX04Connect
Description: ���ݹ���ģʽ����ʼ��������
Input: ����ģʽ��workmode��
Output: Ublox��״̬[uint8_t]
Return: Ublox��״̬[uint8_t]
Others: uint8_t�ĵͼ�������ˣ�Ublox_User_ERR0��������ͳһ�����궨��
 ***************************************************************************/
uint8_t TX04Connect(uint8_t workmode, uint8_t * finish_code) {//��ʼ��������
    uint8_t sta = 0;
    switch (workmode) {
        case TX04_Sta_GSM_Cop:
        {
            sta = Ublox_GSM_Dialing(G350_GSM_Client_SIZE);
            *finish_code = G350_GSM_Client_SIZE;
            break;
        }
            //        case TX04_GPRS_TCP_Work_Server_Mode:
            //        {
            //            sta = Ublox_GPRS_TCP_Server_Dialing();
            //            break;
            //        }
        case TX04_Sta_TCP_Cop:
        {
            sta = Ublox_TCP_Client_Dialing(G350_TCP_Client_SIZE);
            *finish_code = G350_TCP_Client_SIZE;
            break;
        }
        case TX04_Sta_UDP_Cop:
        {
            sta = Ublox_UDP_Client_Dialing(G350_UDP_Client_SIZE);
            *finish_code = G350_UDP_Client_SIZE;

            break;
        }
    }
    return sta;
}

/***************************************************************************
Function: TX04GetWorkMode
Description: ������ת��Ϊ�ڲ����幤��ģʽ
Input: TX04������tx04arg��
Output: ����״̬[uint8_t]
Return: ����״̬[uint8_t]
Others: �����������û�����õĻ����ͻ���ʾ������TX04_Sta_Ready��
 ***************************************************************************/
uint8_t TX04GetWorkMode(TX04ARG tx04arg) {
    uint8_t sta = TX04_Sta_Ready;

    switch (tx04arg.WorkMode) {
        case TX04_ARG_WORK_MODE_GSM:
        {
            sta = TX04_Sta_GSM_Cop;
            break;
        }
        case TX04_ARG_WORK_MODE_GPRS:
        {
            switch (tx04arg.TCP_UDP) {
                case TX04_ARG_TCP_UDP_TCP:
                {
                    switch (tx04arg.CSMode) {
                        case 0x31:
                        {
                            sta = TX04_Sta_TCP_Server_Cop;
                            break;
                        }
                        case 0x30:
                        {
                            sta = TX04_Sta_TCP_Cop;
                            break;
                        }
                    }
                    break;
                }
                case TX04_ARG_TCP_UDP_UDP:
                {
                    sta = TX04_Sta_UDP_Cop;

                    break;
                }
            }
            break;
        }
    }
    return sta;
}

/***************************************************************************
Function: TX04DataInterchange
Description: ���ݹ���ģʽ����ʼ��������
Input: ����ģʽ��workmode��
Output: Ublox��״̬[uint8_t]
Return: Ublox��״̬[uint8_t]
Others: uint8_t�ĵͼ�������ˣ�Ublox_User_ERR0��������ͳһ�����궨��
 ***************************************************************************/
Bool TX04DataInterchange(uint8_t workmode) {//��ʼ��������
    Bool has_send_cop = False;
    Bool has_rec_cop = False;
    uint8_t mode1, mode2;

    switch (workmode) {
        case TX04_Sta_GSM_Cop:
        {
            mode1 = TX04_GSM_Work_Mode_S;
            mode2 = TX04_GSM_Work_Mode_R;
            break;
        }
        case TX04_Sta_TCP_Cop:
        {
            mode1 = TX04_GPRS_TCP_Work_Client_Mode_S;
            mode2 = TX04_GPRS_TCP_Work_Client_Mode_R;
            break;
        }
        case TX04_Sta_TCP_Server_Cop:
        {
            //             TCP_Server_Link_Cop();
            break;
        }
        case TX04_Sta_UDP_Cop:
        {
            mode1 = TX04_GPRS_UDP_Work_Mode_S;
            mode2 = TX04_GPRS_UDP_Work_Mode_R;
            break;
        }
    }

    do {//TCP��������   ��Ѱ���� 
        has_send_cop = OnlineHandleData(mode1); //����
        if (!gGPRSIsONline)
            break;
        has_rec_cop = OnlineHandleData(mode2); //����
        if (!has_send_cop && !has_rec_cop) {//������ͺ���������û�в������Ҷ�ʱ�����ڹر�״̬
            TX04Sleep(); //������T2�����־
        }
    } while (gGPRSIsONline); //ͨѶ�쳣����
    GLED = 0; //�رյ���  
    return True;
}

/***************************************************************************
Function: GetGPRSArgFromFlash
Description: ͨ����ȡFlash��ȡGPRS����
Input: ��ַ
Output: ��
Return: ��
Others: ֧�ֲ���һ�Ͳ�����
 ***************************************************************************/
static void GetGPRSArgFromFlash(const uint32_t add) {
    uint8_t arg1[200], cnt = 0, cnt1 = 0;
    uint8_t argtmp[200];
    uint8_t * source_ptr;
    TX04ARG* arg_ptr;
    Bool isArg1 = (add == STORE_ARG1_ADD); //�Ƿ��ǲ���һ

    ReadArgFromFlash(add, arg1, 176); //���ݵ�ַadd����ȡ����
    for (cnt = 0, cnt1 = 0; cnt < 176; cnt += 4, cnt1 += 3) {//������Ч����
        CopyDat(argtmp + cnt1, arg1 + cnt, 3);
    }
    source_ptr = (CRCIsRight(argtmp, 128, argtmp + 128)) ? argtmp : (uint8_t *) TX04DefualtArg; //��ȡ���������ݽ���CRC16У��,
    arg_ptr = (isArg1) ? &TX04Arg_S : &TX04Arg2_S;
    CopyDat(arg_ptr, source_ptr, 130);
}

/***************************************************************************
Function: TX04GetRunArg
Description: ��ȡ���в���
Input: ��
Output: ��
Return: ��
Others: 
 ***************************************************************************/
void TX04GetRunArg(void) {
    GetGPRSArgFromFlash(STORE_ARG1_ADD);
    GetGPRSArgFromFlash(STORE_ARG2_ADD);
    EnsureRunArg(&TX04Arg_S); //ȷ�����еĳ���
    ChangeBaudRate(); //�޸Ĳ�����
}

/***************************************************************************
Function: TX04ReportMasthead
Description: ģ�����ߣ����ͱ�ͷ����
Input: ����ģʽ��workmode��
Output: ��
Return: ��
Others: ֧��UDP�Ͷ���
 ***************************************************************************/
void TX04ReportMasthead(uint8_t workmode) {
    uint8_t masthead_dat[50], masthead_bytes = 9; //��ͷ�����ݺ��ֽ�������
    if (RunArg.ReportEN == 0x31) {//�Ƿ�����ͷ
        masthead_bytes = TX04GetMasthead(masthead_dat); //���ͱ�ͷ����
        switch (workmode) {
            case TX04_Sta_TCP_Cop:
            {
                UART1SendString(masthead_dat, masthead_bytes); //���ͱ�ͷ����
                break;
            }
            case TX04_Sta_UDP_Cop:
            {
                UDPWriteStrByCmd(masthead_dat, masthead_bytes); //���ͱ�ͷ����                
                break;
            }
            case TX04_Sta_GSM_Cop:
            {
                SMSWriteStrByCmd(masthead_dat, masthead_bytes); //���ͱ�ͷ����

                break;
            }
        }
    }
}

/*************************************
 * Function: TX04GetMasthead
 * Description: ��ȡ��ͷ����
 * Input: ��ȡ��ͷ����
 * Output: ��ȡ��ͷ���ݵĳ���
 * Notice���ֽ������ܴ���256
 * ʾ����@@13588888888IP:��.��.��.��##36\r\n
 *************************************/
uint8_t TX04GetMasthead(uint8_t * masthead_dat) {
    uint8_t simtmp[40];
    uint8_t cnt = 0, cnt1 = 0;
    uint8_t length = RunArg.SimNumberLength;
    uint8_t copybytes = StrLen((char*) G350_Arg.Client_IP);

    CopyDat(simtmp, (uint8_t*) "@@", 2);
    if (length < 12) {//�ų�������0����� ���ݳ���Ϊ0xff�����
        for (cnt = 2; cnt <= length; cnt += 2) {
            simtmp[cnt] = ((RunArg.SimNumber[cnt1 ]) >> 4) + 0x30;
            simtmp[cnt + 1] = ((RunArg.SimNumber[cnt1 ]) &0x0f) + 0x30;
            cnt1 += 1;
        }
    } else
        length = 0;
    if (length % 2) {
        simtmp[cnt] = ((RunArg.SimNumber[cnt1]) >> 4) + 0x30;
        cnt += 1;
    }
    length += 2; //���@@
    CopyDat(simtmp + length, "IP:", 3);
    length += 3;
    CopyDat(simtmp + length, G350_Arg.Client_IP, copybytes); //�����ֽ���
    length += copybytes;
    CopyDat(simtmp + length, "##36\r\n", 6);
    length += 6;
    CopyDat(masthead_dat, simtmp, length);

    return length;
}

/***************************************************************************
Function: TX04SMSArgIsRight 
Description: ��֤���Ͷ��ţ����ṩ������ʾ
Input: GPRS����ģʽ
Output: �Ƿ����
Return: True:���ų�����ȷ��False:���ų�����ȷ
Others: none
 ***************************************************************************/
Bool TX04SMSArgIsRight(uint8_t workmode) {
    Bool b_sta = True;
    if (workmode == TX04_Sta_GSM_Cop) {//����Ƕ���ģʽ
        if (!DataIsVaild(RunArg.SMSTargetNumber1Length, 13, 1) ||
                !DataIsVaild(RunArg.SMSTargetNumber2Length, 13, 1)) {//����ֻ����볤��            
            PrintErr(11);
            //            if (gRefreshArg) {//GPRS���ߣ����ģ����Ҫ������������Ļ�����־λ����������ز���
            //                gRefreshArg = 0;
            //                CopyDat((uint8_t*) & RunArg, (uint8_t*) & TX04Arg_S, 130); //ˢ�²����������ظ��������ģʽ
            //            }
            b_sta = False;
        }
    }
    return b_sta;
}







