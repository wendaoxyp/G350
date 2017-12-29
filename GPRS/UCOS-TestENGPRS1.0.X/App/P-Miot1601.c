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

extern const u8 mi_dat_add[REG_DATA_ARG_NUM + 1];
extern const u16 mi_arg_add[REG_ARG_NUM + 1];
extern enum mi_arg_add_enum enum_mi_arg_add;
extern enum mi_dat_add_enum enum_mi_dat_add;
struct Alarm_Arg AlarmArgbits;
struct Status Statusbits;
extern u8 bufferRptr_uart2;
extern u8 bufferWptr_uart2;
extern u8 Buffer_uart2[256];
//static bool DUPDataChange(u8 *source_dat);
static void TCP_03_Reply(u8 source);
static void TCP_04_Reply(u16 reg_add, u8 arg_num, u8 source);
static void TCP_10_Reply(u16 reg_add, u8 arg_num, u8 source);
static void TCP_11_Reply(u8* dat);
static void TCP_43_Reply(void);
void TCP_Error_Relay(u8 code, u8 err, u8 source);

/*************************************
Function: CopFun 
Description: ѡ��ͨѶ����
Input: ���� ���͸�
Output: 
 *************************************/
u8 CopFun(u8*dat, u8 source) {
    u16 reg_add = 0; //��ȡ�����Ĵ�����ַ   
    u8 arg_num = 0; //BCD ��������  
    u8 tmp[5];
    //�жϹ�����
    switch (*(dat + 1)) {//��ȡ���ݰ�
        case 0x03:
        {
            reg_add = (*(dat + 2) << 8) + *(dat + 3); //��ȡ���ݰ��Ĵ�����ַ  
            arg_num = *(dat + 4); //BCD �������� 
            //������ݵ�ַ��Χ����0-503(����ÿ��41����һ��Ԥ���ռ�),���ͷǷ����ݵ�ַ
            if (!DataIsVaild(reg_add, 144, 0)) //�ж�������Ч��
            {
                TCP_Error_Relay(0x03, Dat_Add_Err, source);
                break;
            }
            //�������ֵ����1-5֮�䣬���ͷǷ�����ֵ
            if (!DataIsVaild(arg_num, 9, 1)) //
            {
                TCP_Error_Relay(0x03, Dat_Val_Err, source);
                break;
            }
            TCP_03_Reply(source);
            //            }
            break;
        }
        case 0x04://��ȡ����
        {
            reg_add = (* (dat + 2) << 8) + *(dat + 3); //��ȡ�����Ĵ�����ַ   
            arg_num = *(dat + 4); // >> 4)*10 + (*(dat + 4) & 0x0F); //BCD ��������                 
            //���������ַ����0x200-0x212�����ͷǷ����ݵ�ַ
            if (!DataIsVaild(reg_add, mi_arg_add[REG_ARG_NUM - 1], mi_arg_add[0])) //
            {
                TCP_Error_Relay(0x04, Dat_Add_Err, source);
                break;
            }
            //���������������1-18�����ͷǷ�����ֵ
            if (!DataIsVaild(arg_num, REG_ARG_NUM, 1)) //????????????��������
            {
                TCP_Error_Relay(0x04, Dat_Val_Err, source);
                break;
            }
            TCP_04_Reply(reg_add, arg_num, source);
            break;
        }
        case 0x10://����Miot1601����
        {
            reg_add = (* (dat + 2) << 8) + *(dat + 3); //��ȡ�����Ĵ�����ַ  (*(uint16_t *)(tmp+8)<<8)+10)
            arg_num = *(dat + 4); //(*(dat + 4) >> 4)*10 + (*(dat + 4)&0x0F); //BCD �������� 
            //���������ַ����0x200-0x212���������ݵ�ַ����
            if (!DataIsVaild(reg_add, mi_arg_add[REG_ARG_NUM - 1], mi_arg_add[0])) //
            {
                TCP_Error_Relay(0x10, Dat_Add_Err, source);
                break;
            }
            //���������������1-18�����ͷǷ�����ֵ
            if (!DataIsVaild(arg_num, REG_ARG_NUM, 1)) //
            {
                TCP_Error_Relay(0x10, Dat_Val_Err, source);
                break;
            }
            //���ʱ���С���ٹ涨�ķ�Χ��
            SetVaildData(dat + 28, TIME_MP_MAX, 1); //��ȡ�ɼ�ʱ�䲢���
            SetVaildData(dat + 30, TIME_GPRS_MAX, 2); //��ȡGPRS����ʱ�䲢���
            SetVaildData(dat + 32, TIME_ALARM_MAX, TIME_ALARM_MIN); //��ȡGPRS����ʱ�䲢���

            //д��Ĵ���2�ĵ�ַ
            Register2Write(dat + 5, reg_add, GetSize(reg_add, arg_num));
            FM25L64B_Write(RST_Time, dat + 5 + mi_arg_add[mi_year] - 0x200, 7); //д��ʱ��
            StopRTCC(); //refresh RTCC time
            CheckRTCC(); //д��RTCC��
            StartRTCC();
            tmp[3] = *(dat + 55); // 5 + mi_arg_add[mi_ofst] - 0x200);
            tmp[2] = *(dat + 56);
            tmp[1] = *(dat + 57);
            tmp[0] = *(dat + 58);
            gPulseCount = tmp[0]+((u16) tmp[1] << 8)+((u32) tmp[2] << 16)+((u32) tmp[3] << 24); //����д��
            FM25L64B_Write(BOR_Pulse, (u8*) (&gPulseCount), 4); //������������
            TCP_10_Reply(reg_add, arg_num, source);
            break;
        }
        case 0x11://����GPRS����
        {//�����жϷ�����λ������ ��֧��TRG1601            
            if (source == GPRS) {//GPRS���߷�������
                TCP_Error_Relay(0x11, Fun_Err, GPRS);
                break;
            }
            TCP_11_Reply(dat);
            tmp[0] = *(dat + 15) - 0x30; //��ȡGPRS����ģʽ
            break;
        }
        case 0x40:
        {//��������������
            u8 tmp[2] = {0, 0};
            tmp[0] = (u8) (U2STA >> 8);
            tmp[1] = (u8) (U2STA & 0x00FF);
            RS485SendString("AAAAAAAAAA", 10);
            RS485SendString(&bufferWptr_uart2, 1);
            RS485SendString("BBBBBBBBBB", 10);
            RS485SendString(&bufferRptr_uart2, 1);
            RS485SendString("CCCCCCCCCC", 10);
            RS485SendString(&tmp, 2);
            RS485SendString("DDDDDDDDDD", 10);
            RS485SendString(Buffer_uart2, 255);
            break;
        }

        case 0x43:
        {//��ȡ����汾��
            TCP_43_Reply();
            break;
        }
            //        case 0x60:
            //        {
            //            return 'b';
            //        }
        default:
        {
            TCP_Error_Relay(0, Fun_Err, source);
            break;
        }
    }
    return 1;
}

static void TCP_03_Reply(u8 source) {
    //    u16 vaildBytes = 0; //��Ч�ֽ���
    u8 sendBuffer[REG_DATA_SZIE + 10]; //�������ͻ�����������
    u16 CRC_Result = 0; //CRCУ����

    Register2Read(sendBuffer, mi_arg_add[mi_add], 1); //��ֵMiot1601��ַ
    sendBuffer[1] = 0X03; //��ֵ������        
    sendBuffer[2] = 0x29; //��ȡ�ֽ���

    FM25L64B_Read((gOffsetAdd + 143) % 144 * REG_DATA_SECTION, sendBuffer + 3, REG_DATA_SECTION); //�ȴ����

    //CRCУ��
    CRC_Result = CRC16_Check(sendBuffer, 44); //����CRC���
    sendBuffer[44] = (u8) (CRC_Result & 0x00ff); //��ֵCRC��8λ
    sendBuffer[45] = (u8) ((CRC_Result >> 8)&0x00ff); //��ֵCRC��8λ
    //    vaildBytes += 2;
    //�������ݵ���Ӧ����
    TCP_SendData(source, sendBuffer, 46);
}

static void TCP_04_Reply(u16 reg_add, u8 arg_num, u8 source) {
    u16 vaildBytes = 0; //��Ч�ֽ���
    u8 sendBuffer[REG_ARG_SIZE + 10]; //�������ͻ�����������
    u16 CRC_Result = 0; //CRCУ����

    Register2Read(sendBuffer, mi_arg_add[mi_add], 1); //��ֵMiot1601��ַ
    sendBuffer[1] = 0X04; //��ֵ������                   
    sendBuffer[2] = GetSize(reg_add, arg_num); //��ֵ�ֽ���
    vaildBytes = sendBuffer[2] + 3; //Register2������54+��ַ+������+�ֽ���
    //��ȡregister2�Ĵ���ֵ
    Register2Read(&sendBuffer[3], reg_add, sendBuffer[2]);

    CRC_Result = CRC16_Check(sendBuffer, vaildBytes); //����CRC���
    sendBuffer[vaildBytes] = (u8) (CRC_Result & 0x00ff); //��ֵCRC��8λ
    sendBuffer[vaildBytes + 1] = (u8) ((CRC_Result >> 8)&0x00ff); //��ֵCRC��8λ
    vaildBytes += 2;
    //�������ݵ���Ӧ����
    TCP_SendData(source, sendBuffer, vaildBytes);
}
//�޸�miot����

static void TCP_10_Reply(u16 reg_add, u8 arg_num, u8 source) {
    u8 sendBuffer[7];
    u16 CRC_Result = 0; //CRCУ����

    Register2Read(sendBuffer, mi_arg_add[mi_add], 1); //��ֵMiot1601��ַ
    sendBuffer[1] = 0x10;
    sendBuffer[2] = (u8) ((reg_add >> 8)&0x00ff);
    sendBuffer[3] = (u8) (reg_add & 0x00ff);
    sendBuffer[4] = arg_num; //    sendBuffer[4] = arg_num / 10 * 16 + arg_num % 10;
    CRC_Result = CRC16_Check(sendBuffer, 5); //����CRC���    
    sendBuffer[5] = (u8) (CRC_Result & 0x00ff);
    sendBuffer[6] = (u8) ((CRC_Result >> 8)&0x00ff);

    TCP_SendData(source, sendBuffer, 7);
}
//�޸�GPRS����

static void TCP_11_Reply(u8* dat) {
    u8 receiveBuffer[150];
    u16 CRC_Result = 0; //CRCУ����
    //    u8 tmp = 0x2B;

    GPRS_ON;
    //����GPRS����ֵ  
    UART2SendString(dat + 2, 144);
    //�ȴ�100ms �������� �ж�
    Delay100ms(1);
    //1s�ڴӴ���2�������� ����reciveBuffer+2�� ��֮����û��ָ�������
    if (UARTIsGet(BufferRead_UART1, receiveBuffer + 2, 134, ReceiveOK, 6)) {
        Register2Read(receiveBuffer, 0x200, 1); //��ֵMiot1601��ַ
        receiveBuffer[1] = 0x11;
        CRC_Result = CRC16_Check(receiveBuffer, 136); //����CRC���    
        receiveBuffer[136] = (u8) (CRC_Result & 0x00ff);
        receiveBuffer[137] = (u8) ((CRC_Result >> 8)&0x00ff);
        TCP_SendData(PC, receiveBuffer, 138);
    } else
        TCP_Error_Relay(0x11, Do_Err, PC);
    GPRS_OFF;
}

static void TCP_43_Reply(void) {
    u8 receiveBuffer[10] = {0, 0, 0, 0}, cnt = 0;
    u16 CRC_Result = 0; //CRCУ����
    Register2Read(receiveBuffer, 0x200, 1); //��ֵMiot1601��ַ
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

    Register2Read(sendBuffer, 0x200, 1); //��ֵMiot1601��ַ
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
    u8 sendBuffer1[14]; //��ʼ���� 15+46*REG1_MAX_CNT=1119 REG1_MAX_CNT=24
    u8 sendBuffer2[19]; //�ɼ����ݱ���Register
    u8 sendBuffer3[47]; //�ɼ�����Register 47=UDP_A2_LENGTH + 4+1(sumcheck))
    u8 cnt, sumCheck = 0; // start_cnt = 0;
    u16 length = 0;
    u16 sampCnt = 1;//Reg1Argbits.Record; //��ȡ�ɼ������ݴ���
    u8 startCnt = Reg1Argbits.Buffer_ID; //��ȡ��ǰ��ʼ������ͷ
    //    Record = 23 Buffer_ID=23 [0-22] start_cnt = 0
    //    Record = 24 Buffer_ID=0  [0-23] start_cnt = 0
    //    Record = 25 Buffer_ID=1  [1--23-0] start_cnt = 1
    //    Record = 28 Buffer_ID=4  [4--23-3] start_cnt = 4
    //    Record = 47 Buffer_ID=23  [23--22] start_cnt = 23
    //    Record = 48 Buffer_ID=0   [0--23] start_cnt = 0
    if (packetType == LowPowerAlarm) {//������ݰ������Ǳ������ݵĻ�
        TCP_SendData(GPRS, AlarmData, UDP_A2_LENGTH + 19); //����һ��ɼ����ݰ�
    } else {
        if (sampCnt > REG1_MAX_CNT)//�����ȡ��25�����ݵĻ�,�����͵����������ó�24
            sampCnt = REG1_MAX_CNT; //else
        else
            startCnt = 0; //С�ڵ���24��
        sendBuffer1[0] = 'A'; //A2֡ͷ
        sendBuffer1[1] = '2';

        Register2Read(sendBuffer1 + 2, mi_arg_add[mi_id], 8); //EID

        length = 15 + (UDP_A2_LENGTH + 4) * sampCnt; //2+8+2+1+1+(UDP_A2_LENGTH+4)*number+1; //�����ܳ�
        sendBuffer1[10] = (u8) (length >> 8);
        sendBuffer1[11] = (u8) (length & 0x00FF);
        sendBuffer1[12] = packetType; //�������� 
        sendBuffer1[13] = sampCnt; //��ֵ���ݰ����� 
        sumCheck = Sum_Check256(sendBuffer1, 14); //��ȡУ���
        TCP_SendData(GPRS, sendBuffer1, 14);
        for (cnt = 0; cnt < sampCnt; cnt++) {//������ݰ� //��ֵ���ݰ�������            
            GetRegister1(sendBuffer2, (cnt + startCnt) % REG1_MAX_CNT); //��ȡ����
            GetUnixTime_Char(sendBuffer2 + 12, sendBuffer3); //46=A2(42)+ʱ���(4)//��ȡʱ��� 08 16 1 1 0 0 0 ʱ���������
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

                    Register2Write((source_dat + 15), mi_arg_add[mi_tmp], 2);
                    bytes -= 3;
                    Data_Type = *(source_dat + 17);
                    break;
                }
                case 0x01:
                {// Send Period (seconds)                   
                    SetVaildData((source_dat + 18), TIME_GPRS_MAX, TIME_GPRS_MIN); //��ȡGPRS����ʱ�䲢���

                    Register2Write((source_dat + 18), mi_arg_add[mi_tgprs], 2);
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
                    Register2Write((source_dat + 21), mi_arg_add[mi_talarm], 2);
                    bytes -= 3;
                    Data_Type = *(source_dat + 23);
                    break;
                }
                    //                case 0x03:
                    //                {// High Pressure Alarm ��Ҫ���ж�
                    //                    Register2Write((source_dat + 24), mi_arg_add[mi_hp_alarm], 4);
                    //                    bytes -= 5;
                    //                    Data_Type = *(source_dat + 28);
                    //                    break;
                    //                }
                    //                case 0x04:
                    //                {// Low Pressure Alarm ��Ҫ���ж�
                    //                    Register2Write((source_dat + 29), mi_arg_add[mi_lp_alarm], 4);
                    //                    bytes -= 5;
                    //                    Data_Type = *(source_dat + 33);
                    //                    break;
                    //                }
                    //                case 0x05:
                    //                {// High Temperature Alarm ��Ҫ���ж�
                    //                    Register2Write((source_dat + 34), mi_arg_add[mi_ht_alarm], 4);
                    //                    bytes -= 5;
                    //                    Data_Type = *(source_dat + 38);
                    //                    break;
                    //                }
                    //                case 0x06:
                    //                {// Low Temperature Alarm ��Ҫ���ж�
                    //                    Register2Write((source_dat + 39), mi_arg_add[mi_lt_alarm], 4);
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
    u8 Receive[65] = {0, 0};
    u8 Mp_id = 0;

    Register2Read(&Mp_id, mi_arg_add[mi_add], 1);
    byte = UARTIsGet(BufferRead_UART1, Receive, 61, &Mp_id, 1);
    if (byte && CheckIsRight(CRC16_Check, Receive, (const u8) (byte - 2))) {
        CopFun(Receive, PC);
    }
    Nop();
}

