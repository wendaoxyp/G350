/* 
 * File:   UDP-TANCY RTU PROTOCOL FOR DAZHONG GAS.c
 * Author: TURONG62
 *
 * Created on 2016��9��8��, ����12:53
 */
//#include 
#include "user.h"
//#include "p24FV32KA301.h"
#include "GPRS.h"
#include "CheckData.h"
#include "P-Miot1601.h"
#include "time.h"
#include "SerialBuffer.h"
#include "MP.h"
#include "RTCC.h"
#include "TIM.h"
#include "Miot1601.h"
//#include "TypeConvert.h"
//#include "TCP-Miot1601.h"
#include "Common.h"
#include "UDP-TANCY_RTU_PROTOCOL_FOR_DAZHONG_GAS.h"
#include "GPRS.h"

//u8 gMpCopDataForUDP[29];

extern const u8 mi_dat_add[REG_DATA_ARG_NUM + 1];
extern const u16 mi_arg_add[REG_ARG_NUM + 1];
//extern const u16 DataPacke_Add[DataPacketNum];
extern enum mi_arg_add_enum enum_mi_arg_add;
extern enum mi_dat_add_enum enum_mi_dat_add;
//vu16 gAlarm_Arg;
struct Alarm_Arg AlarmArgbits;

//extern u8 gRefreshFlag; //ˢ�¼��� ����0 % n����

//u8 gAlarmTempFlag; //�¶ȱ�����־λ
//u8 gAlarmPresFlag; //ѹ��������־λ


static bool DUPDataChange(u8 *source_dat);

void UDPSendData(u8 packetType, u8 OffSet) {
    u8 sendBuffer[14]; //A2[2]+EID[8]+LEN[2]+T[1]+N[1]
    u8 sendBuffer2[UDP_A2_LENGTH + 4];
    u8 rtcTime[7];
    u8 cnt, channel, number, sumCheck = 0;
    u16 length;
    //������ݰ�������Data Samples,��֮���Ǳ�������
    if (!packetType) {
        // ��ȡδ���͵����ݰ�����
        number = gSampleCount;
        gSampleCount = 0; //���Ҫ���͵�����
        //�ж����ݰ������Ƿ���ȷ
        if (number > DataPacketNum) number = DataPacketNum;
    } else
        number = 1;
    //A2֡ͷ
    sendBuffer[0] = 'A';
    sendBuffer[1] = '2';
    //EID
    Register2Read(sendBuffer + 2, mi_arg_add[mp_id], 8);
    //�����ܳ�
    length = 15 + (UDP_A2_LENGTH + 4) * number; //2+8+2+1+1+(UDP_A2_LENGTH+4)*number+1;
    sendBuffer[10] = length >> 8;
    sendBuffer[11] = (u8) (length & 0x00FF);
    //��������
    sendBuffer[12] = packetType;
    //��ֵ���ݰ�����
    sendBuffer[13] = number;
    //�ֿ���������
    TCP_SendData(GPRS, sendBuffer, 14);
    //��ȡУ���
    sumCheck = Sum_Check256(sendBuffer, 14);
    //��ֵ���ݰ�������  
    for (cnt = 0; cnt < number; cnt++) {
        //���㿪ʼͨ����ƫ�Ƶ�ַ  
        channel = (OffSet + 24 - number + cnt) % DataPacketNum;
        //��ȡʱ��� 08 16 1 1 0 0 0 ʱ���������
        FM25L64B_Read(mi_dat_add[mp_time] + channel * REG_DATA_SECTION, rtcTime, 7);
        GetUnixTime_Char(rtcTime, sendBuffer2);
        //��ȡЭ�� ��ֵ�����ݰ�  A2����+ʱ���
        PacketData2A2(channel, sendBuffer2 + 4);
        //��������
        TCP_SendData(GPRS, sendBuffer2, UDP_A2_LENGTH + 4);
        //��ȡ��У��
        sumCheck += Sum_Check256(sendBuffer2, UDP_A2_LENGTH + 4);
    }
    //����У����  
    TCP_SendData(GPRS, &sumCheck, 1);
}

void UDPReceiveData(void) {
    //00 00 78 01 01 2C 02 00 78 03 42 C8 00 00 04 41 20 00 00 05 42 48 00 00 06 40 A0 00 00
    //A 2
    u8 receiveBuffer[50];
    u8 bytes = 0;
    u8 head[8] = {0};
    
    //��ȡ����֡ͷ
    Register2Read(head, mi_arg_add[mp_id], 8);
    //У������
    bytes = SerialDataIsGet(BufferRead_UART2, receiveBuffer, head, 8, CopUDPDeadline);
    //�ж��Ƿ���ܵ�����
    if (bytes) {
        //�жϺ�У���Ƿ���ȷ
        if (receiveBuffer[bytes - 1] == Sum_Check256(receiveBuffer, bytes - 1)) {
            //���������ȷ��ģ������
            GPRS_OFF;
            DUPDataChange(receiveBuffer);
        }
    }
    GPRS_OFF;
}

static bool DUPDataChange(u8 * source_dat) {
    u8 Data_Type = *(source_dat + 10); //��ȡ��һ�����ݵ����
    char bytes = *(source_dat + 9); //��ȡ���ݵĳ���
    // u16 time_tmp;//��ȡʱ�� 
    //7F F9 02 01 00 00 00 01 00 1D 00 00 3C 01 00 B4 02 00 3C 03 41 F0 00 00 04 41 20 00 00 05 43 48 00 00 06 42 48 00 00 81 
    if (!DataIsVaild((u16) Data_Type, 6, 0)) //�ж����������Ƿ񳬳���Χ
        return false;

    if (!DataIsVaild((u16) bytes, 29, 3)) //�ж��ֽ����Ƿ񳬳���Χ
        return false;

    if (!(*(source_dat + 8))) {//�������������ACK
        while (bytes > 0) {
            switch (Data_Type) {
                case 0x00:
                {// Save Period (seconds) ʱ��ı�ʾ��ʽ����                    
                    SetVaildData((source_dat + 11), TIME_MP_MAX, TIME_MP_MIN); //�������

                    Register2Write((source_dat + 11), mi_arg_add[mi_tmp], 1);
                    bytes -= 3;
                    Data_Type = *(source_dat + 13);
                    break;
                }
                case 0x01:
                {// Send Period (seconds)                   
                    SetVaildData((source_dat + 14), TIME_GPRS_MAX, TIME_GPRS_MIN); //��ȡGPRS����ʱ�䲢���

                    Register2Write((source_dat + 14), mi_arg_add[mi_tgprs], 1);
                    bytes -= 3;
                    Data_Type = *(source_dat + 16);
                    break;
                }
                case 0x02:
                {// Alarm Period (seconds)
                    SetVaildData((source_dat + 17), TIME_ALARM_MAX, TIME_ALARM_MIN); //��ȡGPRS����ʱ�䲢���

                    Register2Write((source_dat + 17), mi_arg_add[mi_talarm], 1);
                    bytes -= 3;
                    Data_Type = *(source_dat + 19);
                    break;
                }
                case 0x03:
                {// High Pressure Alarm ��Ҫ���ж�
                    Register2Write((source_dat + 20), mi_arg_add[mi_hp_alarm], 1);
                    bytes -= 5;
                    Data_Type = *(source_dat + 24);
                    break;
                }
                case 0x04:
                {// Low Pressure Alarm ��Ҫ���ж�
                    Register2Write((source_dat + 25), mi_arg_add[mi_lp_alarm], 1);
                    bytes -= 5;
                    Data_Type = *(source_dat + 29);
                    break;
                }
                case 0x05:
                {// High Temperature Alarm ��Ҫ���ж�
                    Register2Write((source_dat + 30), mi_arg_add[mi_ht_alarm], 1);
                    bytes -= 5;
                    Data_Type = *(source_dat + 34);
                    break;
                }
                case 0x06:
                {// Low Temperature Alarm ��Ҫ���ж�
                    Register2Write((source_dat + 35), mi_arg_add[mi_lt_alarm], 1);
                    bytes -= 5;
                    //                    Data_Type = *(source_dat + 24);
                    break;
                }
                default:
                {
                    bytes = 0;
                    break;
                }
            }
        }
        GetArgTime(); //ˢ������
        GetArgAlarm(); //��ȡ��ֵ
        FLagArgbits.talarmFlag=0;//�����־λ
        FLagArgbits.tgprsFlag=0;
        //        gRefreshFlag = 0; //ˢ��λ ��0
        return true;
    }
}

/*************************************
Function: UDPAlarmSend
Description: UDP��������
Input: 
Output: 
 *************************************/
void UDPAlarmTask(void) {
    //    if (gAlarmTempFlag) {
    //        CopUDPTask(gAlarmTempFlag);
    //        gAlarmTempFlag = 0;
    //    }
    //    if (gAlarmPresFlag) {
    //            CopUDPTask(gAlarmPresFlag);
    //        gAlarmPresFlag = 0;
    //    }
    //����б����Ĳ���
    if (AlarmArgbits.ATF || AlarmArgbits.APF) {

        GPRS_ON; //��GPRSģ��  

        if (LKIsHigh())//�ж�LK��60s���Ƿ�����
        {
            //        b = true;
            Delay100ms(1); //��ʱ100ms 
            IEC1bits.U2RXIE = 1; //�����ж�
            if (AlarmArgbits.ATF)
                UDPSendData(AlarmArgbits.ATF, AlarmArgbits.ATC);
            if (AlarmArgbits.APF)
                UDPSendData(AlarmArgbits.APF, AlarmArgbits.APC);
            UDPReceiveData();
            IEC1bits.U2RXIE = 0; //�ر��ж�
        }
        Delay100ms(1); //��ʱ500ms ��֤���ݷ��ͳɹ�        
        AlarmArgbits.ATF = 0;
        AlarmArgbits.APF = 0;

        GPRS_OFF; //�ر�GPRSģ��
    }
}





