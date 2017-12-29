#include "user.h"
#include "RS485.h"
#include "UART.h"
#include "Protocal.h"
#include "CheckData.h"
#include "TIM.h"
#include "Mp.h"
#include "P-Miot1601.h"
#include "SerialBuffer.h"
#include "math.h"
#include "Miot1601.h"
#include "Common.h"
//#include "Queue.h"

#define PULSE_MAX 100000000 
//extern QUEUE line; //��������
/*********************************ģ����PCͨѶ�Ĳ���**********************************/
//vu32 gNowCapture = 0; //���벶������2 ��λ��ms
//vu32 gPulseTOffset = 0; //����ʱ��ƫ����
//vu32 gPulseCount = 0; //�����ۼ���
u8 gAlarmVoltageAdd;
u8 gOverFlag = 0;
static u8 mi_SSP[3] = {1, 10, 100};
/**********************************ģ����豸ͨѶ�Ĳ���****************************/

/*********************************��������**********************************/

/*************************************
Function: ClrData 
Description: �������
Input: dat�����ݵ�ַ bytes���ֽ���
Output: ��
 *************************************/
void ClrData(u8 *dat, u8 bytes) {
    u8 count = 0;

    while (count < bytes) {
        *(dat + count) = 0;
        count++;
    }
}

/*************************************
Function: PulseIsOver 
Description: �������Ƿ����
Input: ��
Output: ��
 *************************************/
static bool PulseIsOver(void) {
    bool b = false;
    while (gPulseCount >= PULSE_MAX) {
        gPulseCount -= PULSE_MAX; //����
        b = true;
    }
    return b;
}

/*************************************
Function: Get_Q
Description: ��ȡ˲����
Input: ��
Output: ��
 *************************************/
static float Get_Q(const unsigned long nowPulse) {
    u8 tmp = 0;
    u32 pulse_time = gNowCapture; //����ʱ�� ���������ʱ������豸
    gNowCapture = 0; //����ϴ�����
    Register2Read(&tmp, mi_arg_add[mi_arg2], 1); //ssp=
    if (tmp > 2) tmp = 0;
    if (!pulse_time)
        return 0;
    if (nowPulse < 2) {
        return (gOverFlag) ? (1.0 * mi_SSP[tmp] * 360000 / pulse_time) : 0; //1*0.1[ssp]/(pulse_time/(3600*1000))
    } else {
        return 1.0 * mi_SSP[tmp] * 360000 / pulse_time;
    }
}

/*************************************
Function: Get_V 
Description: ��ȡ����
Input: ��
Output: ��
 *************************************/
static void Get_V(const unsigned long nowPulse, float*tmp) {
    //float tmp[2];
    if (nowPulse != 0) {
        u8 tmp1 = 0;
        Register2Read(&tmp1, mi_arg_add[mi_arg2], 1);
        if (tmp1 > 2)tmp1 = 0;
        switch (mi_SSP[tmp1]) {
            case 1://SSP=0.1
            {
                *tmp = floor(nowPulse / 10 / 10000); //��ʼֵΪ124889  =1
                *(tmp + 1) = nowPulse % 100000 * 1.0 / 10; //  =2488.9
                break;
            }
            case 10:
            {
                *tmp = floor(nowPulse / 10000);
                *(tmp + 1) = nowPulse % 10000;
                break;
            }
            case 100:
            {
                *tmp = floor(nowPulse * 10 / 10000);
                *(tmp + 1) = nowPulse * 10 % 10000;
                break;
            }
        }
    } else
        *tmp = *(tmp + 1) = 0;
}

/*************************************
Function: GetValueTask
Description: ��ȡMP�й���˲�����͹�������
Input: ��
Output: ��
 *************************************/
void GetValueTask(void) {
    u8 tmp_ch[19]; //��ʱ4Ϊ������IEE745���ַ�
    float Qm_f; //˲����
    float Vm_f[2]; //�����ĸ�8λ�͵�8λ
    u16 OffsetAdd1 = gOffsetAdd * REG_DATA_SECTION; //ͬ��ʹ��ƫ����
    //���㹤������
    if (PulseIsOver() && !gOverFlag)
        gOverFlag = 1;
    //    if (gNowCapture)
    Qm_f = Get_Q(gPulseCount);
    //    else
    //        Qm_f = 0;
    if (Qm_f > 50) Qm_f = 50;
    Get_V(gPulseCount, Vm_f);
    //    gNowCapture = 0; //�����ʱ����ֵ������û����������ʾ���幤��˲����
    //������д�������
    FloatToChar(&Qm_f, tmp_ch); //����˲����
    FloatToChar(Vm_f, tmp_ch + 4); //��������1
    FloatToChar(Vm_f + 1, tmp_ch + 8); //��������2
    RTCReadTime(tmp_ch + 12); //7�ֽ�ʱ��
    //    EnQueue(tmp_ch, &line);
    EnRegister1(tmp_ch);

    //д���˲����  change
    FM25L64B_Write((mi_dat_add[mp_Qm] + OffsetAdd1), tmp_ch, 4);
    //��ȡ��������ת���ַ�������д��FRAM  
    FM25L64B_Write((mi_dat_add[mp_Vm] + OffsetAdd1), tmp_ch + 4, 4);
    FM25L64B_Write((mi_dat_add[mp_Vm] + OffsetAdd1 + 4), tmp_ch + 8, 4);
    //��ȡʱ�䣬��д��FRAM
    FM25L64B_Write((mi_dat_add[mp_time] + OffsetAdd1), tmp_ch + 12, 7);
    //��ֵ����ֵ
    tmp_ch[0] = tmp_ch[1] = tmp_ch[2] = tmp_ch[3] = 0;
    FM25L64B_Write(mi_dat_add[mp_T] + OffsetAdd1, tmp_ch, 4);
    FM25L64B_Write((mi_dat_add[mp_P] + OffsetAdd1), tmp_ch, 4);
    FM25L64B_Write((mi_dat_add[mp_Qb] + OffsetAdd1), tmp_ch, 4);
    FM25L64B_Write((mi_dat_add[mp_Vb] + OffsetAdd1), tmp_ch, 4);
    FM25L64B_Write((mi_dat_add[mp_Vb] + OffsetAdd1 + 4), tmp_ch, 4);

    FM25L64B_Write((mi_dat_add[mp_status] + OffsetAdd1), tmp_ch, 1);
    //    �������ݰ�����
    FROM_WriteDPNum(); //�������ݰ�����
}

/*************************************
Function: GetAlarmValue
Description: ��ȡMP�й���˲�����͹�������
Input: ��
Output: ��
 *************************************/
void GetAlarmValue(void) {
    u8 tmp_ch[19]; //��ʱ4Ϊ������IEE745���ַ�
    float Vm_f[2]; //�����ĸ�8λ�͵�8λ
    u16 OffsetAdd1 = gOffsetAdd * REG_DATA_SECTION; //ͬ��ʹ��ƫ����
    u16 length = 19 + UDP_A2_LENGTH, CRCtmp;
    u8 rtcc_tmp[7] = {0, 0, 0, 0, 0, 0, 0};
    u8 cnt; //����ѭ��
    for (cnt = 0; cnt < length; cnt++)//���AlarmData��������
        *(AlarmData + cnt) = 0;
    //���㹤������
    if (PulseIsOver() && !gOverFlag)
        gOverFlag = 1;
    Get_V(gPulseCount, Vm_f);
    //������д�������
    AlarmData[0] = 'A'; //A2֡ͷ
    AlarmData[1] = '2';
    Register2Read(AlarmData + 2, mi_arg_add[mi_id], 8); //EID
    AlarmData[10] = (u8) (length >> 8); //�����ܳ�15+A2+4
    AlarmData[11] = (u8) (length & 0x00FF);
    AlarmData[12] = 0; //�������� ʹ���������ݴ���
    AlarmData[13] = 1; //��ֵ���ݰ�����
    RTCReadTime(rtcc_tmp); //7�ֽ�ʱ��
    GetUnixTime_Char(rtcc_tmp, AlarmData + 14); //��ȡʱ���
    Register2Read(AlarmData + 18, mi_arg_add[mi_add], 1); //��ȡ��ַ
    *(AlarmData + 19) = 0x03; //������
    //�ֽ��� ��ȥ������ ��ַ CRCУ��2λ- ����1λ
    *(AlarmData + 20) = UDP_A2_LENGTH - 5;
    //�������+8 21-28
    //���˲����+4 29-32
    //��������+8 33-40
    FloatToChar(Vm_f, AlarmData + 33); //��������1 +4
    FloatToChar(Vm_f + 1, AlarmData + 37); //��������2 +4
    //����˲����+4 41-44
    //�¶�+4 45-48
    //ѹ��+4 49-52
    //�豸״̬
    *(AlarmData + 53) = 0x10; //״̬λ �����ȡ���ĵ�ѹΪ
    *(AlarmData + 54) = 0x40; //״̬λ=1�Ļ����3.0V  
    *(AlarmData + 55) = 0x40;
    *(AlarmData + 56) = 0x00;
    *(AlarmData + 57) = 0x00;
    CRCtmp = CRC16_Check(AlarmData + 18, UDP_A2_LENGTH - 2); //CRCУ��
    *(AlarmData + 58) = (u8) (CRCtmp & 0x00FF);
    *(AlarmData + 59) = (u8) (CRCtmp >> 8);
    *(AlarmData + 60) = Sum_Check(AlarmData, length);
    //д����˲����  change
    //��ȡ��������ת���ַ�������д��FRAM  
    FM25L64B_Write((mi_dat_add[mp_Vm] + OffsetAdd1), AlarmData + 33, 4);
    FM25L64B_Write((mi_dat_add[mp_Vm] + OffsetAdd1 + 4), AlarmData + 37, 4);
    //��ȡʱ�䣬��д��FRAM
    FM25L64B_Write((mi_dat_add[mp_time] + OffsetAdd1), rtcc_tmp, 7);
    //��ֵ����ֵ
    tmp_ch[0] = tmp_ch[1] = tmp_ch[2] = tmp_ch[3] = 0;
    FM25L64B_Write(mi_dat_add[mp_T] + OffsetAdd1, tmp_ch, 4);
    FM25L64B_Write((mi_dat_add[mp_P] + OffsetAdd1), tmp_ch, 4);
    FM25L64B_Write((mi_dat_add[mp_Qb] + OffsetAdd1), tmp_ch, 4);
    FM25L64B_Write((mi_dat_add[mp_Vb] + OffsetAdd1), tmp_ch, 4);
    FM25L64B_Write((mi_dat_add[mp_Vb] + OffsetAdd1 + 4), tmp_ch, 4);
    FM25L64B_Write((mi_dat_add[mp_Qm] + OffsetAdd1), tmp_ch, 4);

    FM25L64B_Write((mi_dat_add[mp_status] + OffsetAdd1), tmp_ch, 1);
    //    �������ݰ�����
    FROM_WriteDPNum(); //�������ݰ�����
}


/*************************************
Function: PacketData2A2
Description: ѡ��ָ����ͨ�������A2
Input: ָ������ͨ����0-12�� dat ���A2Э�����dat1 �ɼ���������
Output: A2���ַ�����
 *************************************/
// 02 03 18 41 10 00 00 40 F0 FC 46 00 00 00 00 00 00 00 00 41 A0 00 00 42 CA A6 00 BA A2

void PacketData2A2(u8 *dat, u8*dat1) {
    u8 cnt;
    u16 CRCtmp;
    //�豸��ַ
    Register2Read(dat, mi_arg_add[mi_add], 1);
    //������
    *(dat + 1) = 0x03;
    //�ֽ��� ��ȥ������ ��ַ CRCУ��2λ- ����1λ
    *(dat + 2) = UDP_A2_LENGTH - 5;
    //�������
    for (cnt = 0; cnt < 8; cnt++)
        *(dat + 3 + cnt) = 0;
    //���˲����
    for (cnt = 0; cnt < 4; cnt++)
        *(dat + 11 + cnt) = 0;
    //��������
    for (cnt = 0; cnt < 8; cnt++)
        *(dat + 15 + cnt) = *(dat1 + cnt + 4);
    //����˲����
    for (cnt = 0; cnt < 4; cnt++)
        *(dat + 23 + cnt) = *(dat1 + cnt);
    //�¶�
    for (cnt = 0; cnt < 4; cnt++)
        *(dat + 27 + cnt) = 0;
    //ѹ��
    for (cnt = 0; cnt < 4; cnt++)
        *(dat + 31 + cnt) = 0;
    //�豸״̬
    *(dat + 35) = (FLagArgbits.LowPowerFlag) << 4; //״̬λ �����ȡ���ĵ�ѹΪ
    if (*(dat + 35)) {//״̬λ=1�Ļ����3.0V  
        *(dat + 36) = 0x40;
        *(dat + 37) = 0x40;
        *(dat + 38) = 0x00;
        *(dat + 39) = 0x00;
    } else {//״̬λ=0�Ļ����3.6V  
        *(dat + 36) = 0x40;
        *(dat + 37) = 0x66;
        *(dat + 38) = 0x66;
        *(dat + 39) = 0x66;
    }
    CRCtmp = CRC16_Check(dat, UDP_A2_LENGTH - 2); //CRCУ��
    *(dat + 40) = (u8) (CRCtmp & 0x00FF);
    *(dat + 41) = (u8) (CRCtmp >> 8);
}

