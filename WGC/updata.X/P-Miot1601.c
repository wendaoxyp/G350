/* 
 * File:   Miot1601.c
 * Author: TURONG62
 *
 * Created on 2016��8��17��, ����4:48
 */
#include "user.h"
#include "P-Miot1601.h"
#include "GPRS.h"
#include "CheckData.h"
#include "TIM.h"
#include "SerialBuffer.h"
#include "Miot1601.h"
#include "math.h"
#include "Common.h"


//extern enum REG2_Add_enum enum_REG2_Add;
//extern enum REG1_Add_enum enum_REG1_Add;
//struct Alarm_Arg AlarmArgbits;
struct Status Statusbits;
//extern u8 bufferRptr_uart2;
//extern u8 bufferWptr_uart2;
//extern u8 Buffer_uart2[256];
extern const u8 ReadArg[14];
extern const u8 ArgRe[5];
extern const u8 Ver[5];
//static bool DUPDataChange(u8 *source_dat);
//static void TCP_02_Reply(u8 source);
static void TCP_03_Reply(u8 source, u8 start_ID, u8 nums);
//static void TCP_04_Reply(u16 reg_add, u8 arg_num, u8 source);
static void TCP_10_Reply(u16 reg_add, u8 arg_num, u8 source);
//static void TCP_11_Reply(u8* dat);
static void TCP_32_Reply(void);
static void TCP_33_Reply(u8* dat);
static void TCP_34_Reply(void);
static void TCP_43_Reply(void);
void TCP_Error_Relay(u8 code, u8 err, u8 source);
//u8 AlarmData[61]; //��������ͨ��
//u8 TestData[61] = { 0x41,0x32,0x7F,0xF9,0x02,0x01,0x00,0x00,0x00,0x16,
//                    0x00,0x3D,0x00,0x01,0x80,0xF4,0xE6,0x58,0x08,0x03,
//                    0x25,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//                    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//                    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//                    0x00,0x00,0x00,0x00,0x40,0x66,0x66,0x66,0xE2,0x8C,0x04}; //��������ͨ��

/*************************************
Function: CopFun 
Description: ѡ��ͨѶ���ܣ����ͨѶ�ɹ�������TCP_XX_Reply,
Input: ԭʼ����ָ��dat����������source
Output: 1
 *************************************/
u8 CopFun(u8*dat, u8 source) {//
    u16 CRC_Result = 0; //��ȡ�����Ĵ�����ַ   
    u8 reg_add = 0, arg_num = 0; //BCD ��������  
    u8 add_base = 0;
    u8 tmp[REG2_BYTES + 10];
    //�жϹ�����GetMuiltSampDat = 0x02, GetSingleSampDat = 0x03, GetMIOTArg = 0x04, SetMIOTArg = 0x10, 
    //GetGPRSArg = 0x20, SetGPRSArg = 0x21, TestGPRSArg = 0x22, UnlineUpdataGPRS = 0x23, GetMIOTVer = 043
    switch (*(dat + 1)) {//��ȡ���ݰ�
        case GetSampDat:
        {
            reg_add = *(dat + 2); //��ʼ���
            arg_num = *(dat + 3); //BCD �������� 

            if (reg_add == 0xFF) { //������ݵ�ַ��Χ����0-503(����ÿ��41����һ��Ԥ���ռ�),���ͷǷ����ݵ�ַ
                reg_add = gOffsetAdd;
            } else {
                if (!DataIsVaild(reg_add, DataPacketNum - 1, 0)) //�������ֵ����1-5֮�䣬���ͷǷ�����ֵ
                {
                    TCP_Error_Relay(GetSampDat, Dat_Add_Err, source);
                    break;
                }
            }
            if (!DataIsVaild(arg_num, DataPacketNum, 1)) //�������ֵ����1-5֮�䣬���ͷǷ�����ֵ
            {
                TCP_Error_Relay(GetSampDat, Dat_Val_Err, source);
                break;
            }
            TCP_03_Reply(source, reg_add, arg_num);
            break;
        }
        case GetMIOTArg://��ȡ����
        {
            reg_add = *(dat + 2); //��ȡ�����Ĵ�����ַ   
            arg_num = *(dat + 3); // >> 4)*10 + (*(dat + 4) & 0x0F); //BCD ��������                 

            if (!DataIsVaild(reg_add, REG2_Arg_Postion[REG2_ARG_NUM - 1], REG2_Arg_Postion[0])) //���������ַ����0x200-0x212�����ͷǷ����ݵ�ַ
            {
                TCP_Error_Relay(GetMIOTArg, Dat_Add_Err, source);
                break;
            }

            if (!DataIsVaild(arg_num, REG2_ARG_NUM, 1)) ////���������������1-24�����ͷǷ�����ֵ????????????��������
            {
                TCP_Error_Relay(GetMIOTArg, Dat_Val_Err, source);
                break;
            }
            Register2Read(tmp, REG2_Arg_Postion[mi_add], 1); //��ֵMiot1601��ַ
            tmp[1] = 0X04; //��ֵ������                   
            tmp[2] = GetSize(reg_add, arg_num); //��ֵ�ֽ���
            add_base = tmp[2];
            Register2Read(tmp + 3, reg_add, add_base); //��ȡregister2�Ĵ���ֵ

            CRC_Result = CRC16_Check(tmp, add_base + 3); //����CRC���
            tmp[add_base + 3] = (u8) (CRC_Result & 0x00ff); //��ֵCRC��8λ
            tmp[add_base + 4] = (u8) ((CRC_Result >> 8)&0x00ff); //��ֵCRC��8λ

            TCP_SendData(source, tmp, add_base + 5); //�������ݵ���Ӧ����
            break;
        }
        case SetMIOTArg://����Miot1601����
        {
            add_base = 0x04;
            reg_add = *(dat + 2); //��ȡ�����Ĵ�����ַ  (*(uint16_t *)(tmp+8)<<8)+10)
            arg_num = *(dat + 3); //(*(dat + 4) >> 4)*10 + (*(dat + 4)&0x0F); //BCD �������� 
            //���������ַ����0x200-0x212���������ݵ�ַ����
            if (!DataIsVaild(reg_add, REG2_Arg_Postion[REG2_ARG_NUM - 1], REG2_Arg_Postion[0])) //
            {
                TCP_Error_Relay(SetMIOTArg, Dat_Add_Err, source);
                break;
            }
            //���������������1-18�����ͷǷ�����ֵ
            if (!DataIsVaild(arg_num, REG2_ARG_NUM, 1)) //
            {
                TCP_Error_Relay(SetMIOTArg, Dat_Val_Err, source);
                break;
            }
            SetVaildData(dat + REG2_Arg_Postion[mi_tmp] + add_base, TIME_MP_MAX, TIME_MP_MIN); //��ȡ�ɼ�ʱ�䲢��� 27
            SetVaildData(dat + REG2_Arg_Postion[mi_tgprs] + add_base, TIME_GPRS_MAX, TIME_GPRS_MIN); //��ȡGPRS����ʱ�䲢���
            SetVaildData(dat + REG2_Arg_Postion[mi_talarm] + add_base, TIME_ALARM_MAX, TIME_ALARM_MIN); //��ȡGPRS����ʱ�䲢��� 

            Register2Write(dat + add_base, reg_add, GetSize(reg_add, arg_num));
            StopRTCC(); //refresh RTCC time
            CheckRTCC(); //д��RTCC��
            StartRTCC();
            CopyDat(tmp, dat + add_base + REG2_Arg_Postion[mi_ofst], 4);
            gPulseCount = tmp[3]+((u16) tmp[2] << 8)+((u32) tmp[1] << 16)+((u32) tmp[0] << 24); //����д��
            FM25L64B_Write(BOR_Pulse, (u8*) (&gPulseCount), 4); //������������
            TCP_10_Reply(reg_add, arg_num, source);
            break;
        }
        case GetGPRSArg://��ȡGPRS����//
        {//�����жϷ�����λ������ ��֧��TRG1601      
            if (source == GPRS) {//GPRS���߷�������
                TCP_Error_Relay(GetGPRSArg, Fun_Err, GPRS);
                break;
            }
            Open_UART2();
            GPRS_ON;
            TCP_32_Reply();
            GPRS_OFF;
            Close_UART2();
            break;
        }
        case SetGPRSArg://����GPRS����
        {//�����жϷ�����λ������ ��֧��TRG1601            
            if (source == GPRS) {//GPRS���߷�������
                TCP_Error_Relay(SetGPRSArg, Fun_Err, GPRS);
                break;
            }
            Open_UART2();
            GPRS_ON;
            TCP_33_Reply(dat + 2);
            GPRS_OFF;
            Close_UART2();
            while (BufferRead_UART2(dat)); //���������
            while (BufferRead_UART1(dat)); //���������
            //            Nop();
            break;
        }
        case TestGPRS://����GPRS
        {//�����жϷ�����λ������ ��֧��TRG1601            
            if (source == GPRS) {//GPRS���߷�������
                TCP_Error_Relay(TestGPRS, Fun_Err, GPRS);
                break;
            }
            if (FLagArgbits.tgprsFlag) {
                TCP_Error_Relay(TestGPRS, Do_Err, PC);
                break;
            }
            FLagArgbits.TestOnlieFlag = 1;
            TCP_34_Reply();
            //        }
            break;
        }
            //        case UnlineUpdateGPRS://��������GPRS
            //        {//�����жϷ�����λ������ ��֧��TRG1601            
            //            if (source == GPRS) {//GPRS���߷�������
            //                TCP_Error_Relay(UnlineUpdateGPRS, Fun_Err, GPRS);
            //                break;
            //            }
            //            TCP_35_Reply();
            //            tmp[0] = *(dat + 15) - 0x30; //��ȡGPRS����ģʽ
            //            break;
            //        }
        case GetMIOTVer:
        {//��ȡ����汾��
            TCP_43_Reply();
            break;
        }
        default:
        {
            TCP_Error_Relay(*(dat + 1), Fun_Err, source);
            break;
        }
    }
    return 1;
}

//static void TCP_02_Reply(u8 source) {
//    u8 sendBuffer1[REG3_BYTES]; //�������ͻ�����������
//    u8 sendBuffer2[5], cnt; //�ظ���������
//    u16 CRC_Result = 0; //CRCУ����
//
//    Register2Read(sendBuffer2, REG2_Arg_Postion[mi_add], 1); //��ֵMiot1601��ַ
//    sendBuffer2[1] = GetMuiltSampDat; //��ֵ������ �жϹ�����GetMuiltSampDat      
//    sendBuffer2[2] = 0x90; //114������
//    CRC_Result = CRC16_Check(sendBuffer2, 3); //����CRC���
//    sendBuffer2[3] = (u8) (CRC_Result & 0x00ff);
//    sendBuffer2[4] = (u8) ((CRC_Result >> 8)&0x00ff);
//    //�������ݵ���Ӧ����
//    for (cnt = 0; cnt < 144; cnt++) {
//        FM25L64B_Read((cnt % 144) * REG3_BYTES, sendBuffer1, REG3_BYTES); //�ȴ����
//        TCP_SendData(source, sendBuffer1, 42); //���Ͳɼ���������
//    }
//}

static void TCP_03_Reply(u8 source, u8 start_ID, u8 nums) {//�ָ��ɼ�����
    //    u16 vaildBytes = 0; //��Ч�ֽ���
    u8 sendBuffer[REG1_BYTES + 2], cnt; //�������ͻ�����������
    u16 CRC_Result = 0; //CRCУ����

    Register2Read(sendBuffer, REG2_Arg_Postion[mi_add], 1); //��ֵMiot1601��ַ
    sendBuffer[1] = 0X03; //��ֵ������        
    sendBuffer[2] = nums; //��ȡ�ֽ���
    //CRCУ��
    CRC_Result = CRC16_Check(sendBuffer, 3); //����CRC���
    sendBuffer[3] = (u8) (CRC_Result & 0x00ff); //��ֵCRC��8λ
    sendBuffer[4] = (u8) ((CRC_Result >> 8)&0x00ff); //��ֵCRC��8λ
    TCP_SendData(source, sendBuffer, 5);
    if (nums == 1) {
        FM25L64B_Read((start_ID + 143) % 144 * REG1_BYTES, sendBuffer, REG1_BYTES); //�ȴ����
        //�������ݵ���Ӧ����
        TCP_SendData(source, sendBuffer, REG1_BYTES);
    } else {
        Delay100ms(3);
        for (cnt = 0; cnt < nums; cnt++) {
            FM25L64B_Read((start_ID + 143 + cnt) % 144 * REG1_BYTES, sendBuffer, REG1_BYTES); //�ȴ����
            //�������ݵ���Ӧ����
            TCP_SendData(source, sendBuffer, REG1_BYTES);
        }
    }
}

//static void TCP_04_Reply(u16 reg_add, u8 arg_num, u8 source) {//��ȡmiot����
//    u16 vaildBytes = 0; //��Ч�ֽ���
//    u8 sendBuffer[REG2_BYTES + 10]; //�������ͻ�����������
//    u16 CRC_Result = 0; //CRCУ����
//
//    Register2Read(sendBuffer, REG2_Arg_Postion[mi_add], 1); //��ֵMiot1601��ַ
//    sendBuffer[1] = 0X04; //��ֵ������                   
//    sendBuffer[2] = GetSize(reg_add, arg_num); //��ֵ�ֽ���
//    vaildBytes = sendBuffer[2] + 3; //Register2������54+��ַ+������+�ֽ���
//    //��ȡregister2�Ĵ���ֵ
//    Register2Read(&sendBuffer[3], reg_add, sendBuffer[2]);
//
//    CRC_Result = CRC16_Check(sendBuffer, vaildBytes); //����CRC���
//    sendBuffer[vaildBytes] = (u8) (CRC_Result & 0x00ff); //��ֵCRC��8λ
//    sendBuffer[vaildBytes + 1] = (u8) ((CRC_Result >> 8)&0x00ff); //��ֵCRC��8λ
//    vaildBytes += 2;
//    //�������ݵ���Ӧ����
//    TCP_SendData(source, sendBuffer, vaildBytes);
//}

static void TCP_10_Reply(u16 reg_add, u8 arg_num, u8 source) {//�޸�miot����
    u8 sendBuffer[7];
    u16 CRC_Result = 0; //CRCУ����

    Register2Read(sendBuffer, REG2_Arg_Postion[mi_add], 1); //��ֵMiot1601��ַ
    sendBuffer[1] = 0x10;
    sendBuffer[2] = (u8) ((reg_add >> 8)&0x00ff);
    sendBuffer[3] = (u8) (reg_add & 0x00ff);
    sendBuffer[4] = arg_num; //    sendBuffer[4] = arg_num / 10 * 16 + arg_num % 10;
    CRC_Result = CRC16_Check(sendBuffer, 5); //����CRC���    
    sendBuffer[5] = (u8) (CRC_Result & 0x00ff);
    sendBuffer[6] = (u8) ((CRC_Result >> 8)&0x00ff);

    TCP_SendData(source, sendBuffer, 7);
}

static void TCP_32_Reply(void) {//��ȡGPRS����
    u8 receiveBuffer[144] = {0, 0, 0, 0};
    u16 CRC_Result = 0; //CRCУ����
    //    Open_UART2();
    Register2Read(receiveBuffer, REG2_Arg_Postion[0], 1); //��ֵMiot1601��ַ
    receiveBuffer[1] = 0x20;
    Delay100ms(5);
    TCP_SendData(GPRS, (u8*) ReadArg, 14);
    Delay100ms(5);
    if (UARTIsGet(BufferRead_UART2, receiveBuffer + 2, 136, ArgRe, 5) == 136) {
        CRC_Result = CRC16_Check(receiveBuffer, 138); //����CRC���   2b��ʼ
        receiveBuffer[138] = (u8) (CRC_Result & 0x00ff);
        receiveBuffer[139] = (u8) ((CRC_Result >> 8)&0x00ff);
        TCP_SendData(PC, receiveBuffer, 140);
    } else
        TCP_Error_Relay(GetGPRSArg, GPRS_UnLine, PC);
    //    Close_UART2();
}

static void TCP_33_Reply(u8 * dat) {//����GPRS����
    u8 receiveBuffer[20];
    u16 CRC_Result = 0; //CRCУ����

    Register2Read(receiveBuffer, REG2_Arg_Postion[0], 1); //��ֵMiot1601��ַ
    receiveBuffer[1] = SetGPRSArg;
    Delay100ms(5);
    TCP_SendData(GPRS, dat, 144);
    //����GPRS����ֵ 
    Delay100ms(8); //�ȴ�100ms �������� �ж�
    //1s�ڴӴ���2�������� ����reciveBuffer+2�� ��֮����û��ָ�������
    if (UARTIsGet(BufferRead_UART2, receiveBuffer + 2, 10, ArgRe, 5)) {
        Close_UART2();
        CRC_Result = CRC16_Check(receiveBuffer, 2); //����CRC���    
        receiveBuffer[2] = (u8) (CRC_Result & 0x00ff);
        receiveBuffer[3] = (u8) ((CRC_Result >> 8)&0x00ff);
        TCP_SendData(PC, receiveBuffer, 4);
    } else
        TCP_Error_Relay(SetGPRSArg, Do_Err, PC);
}

static void TCP_34_Reply(void) {//����GPRS����
    u8 receiveBuffer[5];
    u16 CRC_Result = 0; //CRCУ����

    Register2Read(receiveBuffer, REG2_Arg_Postion[0], 1); //��ֵMiot1601��ַ
    receiveBuffer[1] = TestGPRS;
    CRC_Result = CRC16_Check(receiveBuffer, 2); //����CRC���    
    receiveBuffer[2] = (u8) (CRC_Result & 0x00ff);
    receiveBuffer[3] = (u8) ((CRC_Result >> 8)&0x00ff);
    TCP_SendData(PC, receiveBuffer, 4);
    //    GPRS_OFF;
}

//static void TCP_35_Reply(void) {//��������
//    u8 receiveBuffer[150];
//    u16 CRC_Result = 0; //CRCУ����
//
//    GPRS_ON;
//    //����GPRS����ֵ  
//    //    UART2SendString(dat + 2, 144);
//    //�ȴ�100ms �������� �ж�
//    Delay100ms(1);
//    //1s�ڴӴ���2�������� ����reciveBuffer+2�� ��֮����û��ָ�������
//    if (UARTIsGet(BufferRead_UART1, receiveBuffer + 2, 134, ArgRe,5)) {
//        Register2Read(receiveBuffer, 0x200, 1); //��ֵMiot1601��ַ
//        receiveBuffer[1] = 0x11;
//        CRC_Result = CRC16_Check(receiveBuffer, 136); //����CRC���    
//        receiveBuffer[136] = (u8) (CRC_Result & 0x00ff);
//        receiveBuffer[137] = (u8) ((CRC_Result >> 8)&0x00ff);
//        TCP_SendData(PC, receiveBuffer, 138);
//    } else
//        TCP_Error_Relay(0x11, Do_Err, PC);
//    GPRS_OFF;
//}

static void TCP_43_Reply(void) {
    u8 receiveBuffer[10] = {0, 0, 0, 0}, cnt = 0;
    u16 CRC_Result = 0; //CRCУ����
    Register2Read(receiveBuffer, 0, 1); //��ֵMiot1601��ַ
    receiveBuffer[1] = 0x43;
    for (cnt = 0; cnt < 5; cnt++)
        receiveBuffer[2 + cnt] = Ver[cnt];
    CRC_Result = CRC16_Check(receiveBuffer, 7); //����CRC���   2b��ʼ
    receiveBuffer[7] = (u8) (CRC_Result & 0x00ff);
    receiveBuffer[8] = (u8) ((CRC_Result >> 8)&0x00ff);
    TCP_SendData(PC, receiveBuffer, 9);
}

void TCP_Error_Relay(u8 code, u8 err, u8 source) {
    u8 sendBuffer[5]; //�������ͻ�����
    u16 CRC_Result; //����CRC���

    Register2Read(sendBuffer, REG2_Arg_Postion[0], 1); //��ֵMiot1601��ַ
    sendBuffer[1] = 0x80 + code;
    sendBuffer[2] = err;

    CRC_Result = CRC16_Check(sendBuffer, 3); //����CRC���
    sendBuffer[3] = (u8) (CRC_Result & 0x00ff);

    sendBuffer[4] = (u8) ((CRC_Result >> 8)&0x00ff);
    TCP_SendData(source, sendBuffer, 5); //��������
}

//input arg,01,7

void TCP_SendData(u8 source, u8 *dat, u8 bytes) {
    if (source)
        UART2SendString(dat, bytes); //��GPRS��������
    else
        RS485SendString(dat, bytes); //����Է�������
}
//for DAZONG

void UDPSendData(u8 packetType) {//, u8 OffSet, const u8 SampleCnt) {
    u8 sendBuffer1[14]; //��ʼ���� 15+46*REG3_BUF1_CNT=1119 REG3_BUF1_CNT=24
    u8 sendBuffer2[REG3_BYTES]; //�ɼ����ݱ���Register
    u8 sendBuffer3[47]; //�ɼ�����Register 47=UDP_A2_LENGTH + 4+1(sumcheck))
    u8 cnt, sumCheck = 0; // start_cnt = 0;
    u16 length = 0;
    u16 sampCnt = Reg3_Buf1_Recordbits.Record; //��ȡ�ɼ������ݴ���
    u8 startCnt = Reg3_Buf1_Recordbits.Buffer_ID; //��ȡ��ǰ��ʼ������ͷ
    //    Record = 23 Buffer_ID=23 [0-22] start_cnt = 0
    //    Record = 24 Buffer_ID=0  [0-23] start_cnt = 0
    //    Record = 25 Buffer_ID=1  [1--23-0] start_cnt = 1
    //    Record = 28 Buffer_ID=4  [4--23-3] start_cnt = 4
    //    Record = 47 Buffer_ID=23  [23--22] start_cnt = 23
    //    Record = 48 Buffer_ID=0   [0--23] start_cnt = 0
    sendBuffer1[0] = 'A'; //����A2��ͷ
    sendBuffer1[1] = '2';

    Register2Read(sendBuffer1 + 2, REG2_Arg_Postion[mi_id], 8); //��ȡEID����

    switch (packetType) {
        case SampleData:
        {
            if (sampCnt > REG3_BUF1_CNT)//�����ȡ��25�����ݵĻ�,�����͵����������ó�24
                sampCnt = REG3_BUF1_CNT; //else
            else
                startCnt = 0; //С�ڵ���24��      
            length = A2_Rec_Sample_Time + (UDP_A2_LENGTH + 4) * sampCnt; //2+8+2+1+1+(UDP_A2_LENGTH+4)*number+1; //�����ܳ�
            sendBuffer1[10] = (u8) (length >> 8);
            sendBuffer1[11] = (u8) (length & 0x00FF);
            sendBuffer1[12] = packetType; //�������� 
            sendBuffer1[13] = sampCnt; //��ֵ���ݰ����� 
            sumCheck = Sum_Check256(sendBuffer1, 14); //��ȡУ���
            TCP_SendData(GPRS, sendBuffer1, 14);
            for (cnt = 0; cnt < sampCnt; cnt++) {//������ݰ� //��ֵ���ݰ�������            
                GetRegister1(REG3_BUF1, sendBuffer2, (cnt + startCnt) % REG3_BUF1_CNT); //��ȡ����
                GetUnixTime_Char(sendBuffer2, sendBuffer3); //46=A2(42)+ʱ���(4)//��ȡʱ��� 08 16 1 1 0 0 0 ʱ���������
                PacketData2A2(sendBuffer3 + 4, sendBuffer2); //��ȡЭ�� ��ֵ�����ݰ�  A2����+ʱ���18=����ͷ(14)+��ַλ��A2�е�λ��(4)
                sumCheck += Sum_Check256(sendBuffer3, 46); //��ȡ��У��

                if (sampCnt - 1 == cnt) {
                    sendBuffer3[46] = sumCheck;
                    TCP_SendData(GPRS, sendBuffer3, 47);
                } else {
                    TCP_SendData(GPRS, sendBuffer3, 46);
                    Delay100ms(5);
                }
            }
            break;
        }
        case LowPowerData:
        {
            sendBuffer1[10] = 0; //�����ܳ�
            sendBuffer1[11] = 61;
            sendBuffer1[12] = 0; //�������� 
            sendBuffer1[13] = 1; //��ֵ���ݰ����� 
            sumCheck = Sum_Check256(sendBuffer1, 14); //��ȡУ���
            TCP_SendData(GPRS, sendBuffer1, 14);
            FLagArgbits.LowPowerGetDataFlag = 1; //��ȡ��������
            StartTime4();
            IFS1bits.T4IF = 1; //������ʱ��4���ж�
            while (!IFS1bits.T4IF); //�ȴ���ȡ�������
            GetRegister1(REG3_BUF2, sendBuffer2, 1); //��ȡ����
            GetUnixTime_Char(sendBuffer2, sendBuffer3); //46=A2(42)+ʱ���(4)//��ȡʱ��� 08 16 1 1 0 0 0 ʱ���������
            PacketData2A2(sendBuffer3 + 4, sendBuffer2); //��ȡЭ�� ��ֵ�����ݰ�  A2����+ʱ���18=����ͷ(14)+��ַλ��A2�е�λ��(4)
            sumCheck += Sum_Check256(sendBuffer3, 46); //��ȡ��У��
            sendBuffer3[46] = sumCheck;
            TCP_SendData(GPRS, sendBuffer3, 47);

            break;
        }
        case TestData:
        {
            sendBuffer1[10] = 0; //�����ܳ�
            sendBuffer1[11] = 61;
            sendBuffer1[12] = 0; //�������� 
            sendBuffer1[13] = 1; //��ֵ���ݰ����� 
            sumCheck = Sum_Check256(sendBuffer1, 14); //��ȡУ���
            TCP_SendData(GPRS, sendBuffer1, 14);
            FLagArgbits.TestGetDataFlag = 1; //��ȡ��������
            StartTime4();
            IFS1bits.T4IF = 1; //������ʱ��4���ж�
            while (!IFS1bits.T4IF); //�ȴ���ȡ�������
            GetRegister1(REG3_BUF2, sendBuffer2, (cnt + startCnt) % REG3_BUF1_CNT); //��ȡ����
            GetUnixTime_Char(sendBuffer2, sendBuffer3); //46=A2(42)+ʱ���(4)//��ȡʱ��� 08 16 1 1 0 0 0 ʱ���������
            PacketData2A2(sendBuffer3 + 4, sendBuffer2); //��ȡЭ�� ��ֵ�����ݰ�  A2����+ʱ���18=����ͷ(14)+��ַλ��A2�е�λ��(4)
            sumCheck += Sum_Check256(sendBuffer3, 46); //��ȡ��У��
            sendBuffer3[46] = sumCheck;
            TCP_SendData(GPRS, sendBuffer3, 47);
            break;
        }
        default:
            break;
    }
}

bool DUPDataChange(u8 * source_dat) {
    u8 Data_Type = *(source_dat + 14); //��ȡ��һ�����ݵ����
    char bytes = *(source_dat + 13); //��ȡ���ݵĳ���
    // u16 time_tmp;//��ȡʱ�� 
    //41 32 7F F9 02 01 00 00 00 01
    //00 06 00 1D 00 00 78 01 02 58 
    //02 00 3C 03 42 C8 00 00 04 42 
    //C8 00 00 05 41 20 00 00 06 41 
    //20 00 00 0B 
    if (!DataIsVaild((u16) Data_Type, 6, 0)) //�ж����������Ƿ񳬳���Χ
        return false;

    if (!DataIsVaild((u16) bytes, 29, 3)) //�ж��ֽ����Ƿ񳬳���Χ
        return false;

    if (!(*(source_dat + 12))) {//�������������ACK
        while (bytes > 0) {
            switch (Data_Type) {
                case 0x00:
                {// Save Period (seconds) ʱ��ı�ʾ��ʽ����                    
                    SetVaildData((source_dat + 15), TIME_MP_MAX, TIME_MP_MIN); //�������

                    Register2Write((source_dat + 15), REG2_Arg_Postion[mi_tmp], 2);
                    bytes -= 3;
                    Data_Type = *(source_dat + 17);
                    break;
                }
                case 0x01:
                {// Send Period (seconds)                   
                    SetVaildData((source_dat + 18), TIME_GPRS_MAX, TIME_GPRS_MIN); //��ȡGPRS����ʱ�䲢���

                    Register2Write((source_dat + 18), REG2_Arg_Postion[mi_tgprs], 2);
                    bytes -= 3;
                    Data_Type = *(source_dat + 20);
                    break;
                }
                case 0x02:
                {// Alarm Period (seconds)
                    if (!(*(source_dat + 22)+ (*(source_dat + 21) << 8))) {//(*((uint16_t *)(tmp+8))<<8)+10)
                        SetVaildData((source_dat + 21), TIME_ALARM_MAX, TIME_ALARM_MIN); //��ȡGPRS����ʱ�䲢���
                    } else {
                        *(source_dat + 21) = 0;
                        *(source_dat + 22) = 0;
                    }
                    Register2Write((source_dat + 21), REG2_Arg_Postion[mi_talarm], 2);
                    bytes -= 3;
                    Data_Type = *(source_dat + 23);
                    break;
                }
                    //                case 0x03:
                    //                {// High Pressure Alarm ��Ҫ���ж�
                    //                    Register2Write((source_dat + 24), REG2_Arg_Postion[mi_hp_alarm], 4);
                    //                    bytes -= 5;
                    //                    Data_Type = *(source_dat + 28);
                    //                    break;
                    //                }
                    //                case 0x04:
                    //                {// Low Pressure Alarm ��Ҫ���ж�
                    //                    Register2Write((source_dat + 29), REG2_Arg_Postion[mi_lp_alarm], 4);
                    //                    bytes -= 5;
                    //                    Data_Type = *(source_dat + 33);
                    //                    break;
                    //                }
                    //                case 0x05:
                    //                {// High Temperature Alarm ��Ҫ���ж�
                    //                    Register2Write((source_dat + 34), REG2_Arg_Postion[mi_ht_alarm], 4);
                    //                    bytes -= 5;
                    //                    Data_Type = *(source_dat + 38);
                    //                    break;
                    //                }
                    //                case 0x06:
                    //                {// Low Temperature Alarm ��Ҫ���ж�
                    //                    Register2Write((source_dat + 39), REG2_Arg_Postion[mi_lt_alarm], 4);
                    //                    bytes -= 5;
                    //                    //                    Data_Type = *(source_dat + 24);
                    //                    break;
                    //                }
                default:
                {
                    bytes = 0;
                    break;
                }
            }
        }
        //        RefreshDaZong(); //ˢ������
        return true;
    }
    return false;
}

void PC_Cop(void) {
    u8 byte = 0;
    u8 Receive[150] = {0, 0};
    u8 Mp_id = 0;

    Register2Read(&Mp_id, REG2_Arg_Postion[mi_add], 1);
    byte = UARTIsGet(BufferRead_UART1, Receive, 148, &Mp_id, 1);
    if (byte && CheckIsRight(CRC16_Check, Receive, (const u8) (byte - 2))) {
        CopFun(Receive, PC);
    }
    //    Nop();
}

