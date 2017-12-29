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

vu32 gPulseTime = 0; //���벶������2 ��λ��ms
vu32 gPulseCount = 0; //�����ۼ���
static u8 gOverFlag = 0;
u8 mi_SSP[3] = {1, 10, 100};
static u8 Read13[] = {
    0xCC, 0x02, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0x00, 0xEE
};
static uint8_t TX13Head[3] = {0xCC, 0x02, 0x30};
//static u8 Register1[REG1_BYTES];

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
static void Get_Q(const unsigned long nowPulse, float *f) {
    u8 tmp = 0;
    u32 pulse_time = gPulseTime; //����ʱ�� ���������ʱ������豸
    gPulseTime = 0; //����ϴ�����
    Register2Read(&tmp, REG2_Arg_Postion[mi_arg2], 1); //ssp=
    if (tmp > 2) tmp = 0;
    if (!pulse_time)//�����ȡ����ʱ��Ϊ0�Ļ���
        *f = 0;
    else {
        if (nowPulse < 2) {//�����������С��2�Ļ�
            *f = (gOverFlag) ? (1.0 * mi_SSP[tmp] * 360000 / pulse_time) : 0; //1*0.1[ssp]/(pulse_time/(3600*1000))
        } else {
            *f = 1.0 * mi_SSP[tmp] * 360000 / pulse_time;
        }
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
        Register2Read(&tmp1, REG2_Arg_Postion[mi_arg2], 1);
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

void SaveSampleData(u8*dat) {
    u16 OffsetAdd1 = gOffsetAdd * REG1_BYTES; //ͳһʹ��ƫ����

    *(dat + mp_sumcheck) = Sum_Check(dat, REG1_BYTES - 1); //����У���
    FM25L64B_Write(OffsetAdd1, dat, REG1_BYTES); //��ȡʱ��1 ע����Ҫ��ʹ��SPI�ж�д�������������ݴ���

    FM25L64B_Write(DataPacket_ID, &gOffsetAdd, 1); //д�����ݰ����
    gOffsetAdd += 1; //���ݰ����+1  
    gOffsetAdd = gOffsetAdd % DataPacketNum; //һ��������Ϊ252 12*21; 
}

/*************************************
Function: GetValueTask
Description: ��ȡMP�й���˲�����͹�������
Input: ��
Output: ��
 *************************************/
void GetValueTask(u8 InputSource) {
    u8 tmp_reg1[REG1_BYTES]; //���ڴ�Ųɼ�������
    u8 tmp_reg3[REG3_BYTES]; //���ڴ�ŷ�������
    float Qm_f = 0, Vbat_f = 0; //����˲��������ѹ��
    float Vm_f[2] = {0, 0}; //�����ĸ�8λ�͵�8λ

    ClearDat(tmp_reg1, 0, REG1_BYTES); //�������
    if (PulseIsOver() && !gOverFlag) gOverFlag = 1; //�ж����������Ƿ��������������    
    Get_Q(gPulseCount, &Qm_f); //�������˲���������浽Qm_f������
    if (Qm_f > 50) Qm_f = 0; //����������������50�Ļ���˵����������
    Get_V(gPulseCount, Vm_f); //�����ʱ����ֵ������û����������ʾ���幤��˲����
    GetMuilVoltage(&Vbat_f); //�ɼ���ѹֵ
    
    RTCReadTime(tmp_reg3 + sb_time); //��ȡʱ�������ͻ�����reg3buffer1��
    CopyDat(tmp_reg1 + mp_time, tmp_reg3 + sb_time, 7); //��ֵ���ݵ��������ݵ�reg1��

    FloatToChar(&Qm_f, tmp_reg3 + sb_Qm); //��ȡ����˲���������ͻ�����reg3buffer1��
    CopyDat(tmp_reg1 + mp_Qm, tmp_reg3 + sb_Qm, 4); //�������ݵ��������ݵ�reg1��

    FloatToChar(Vm_f, tmp_reg3 + sb_Vm); //��ȡ�������������ͻ�����reg3buffer1��
    FloatToChar(Vm_f + 1, tmp_reg3 + sb_Vm + 4);
    CopyDat(tmp_reg1 + mp_Vm, tmp_reg3 + sb_Vm, 8);

    FloatToChar(&Vbat_f, tmp_reg3 + sb_Vbat); //��ȡ��ص�ѹ�����ͻ�����reg3buffer1��
    CopyDat(tmp_reg1 + mp_Vbat, tmp_reg3 + sb_Vbat, 4);
    switch (InputSource) {
        case SampleData:
        {
            tmp_reg1[mp_status] = SampleData; //�������ֵ����λ����ʾ������Ϊ��������
            EnRegister1(REG3_BUF1, tmp_reg3);
            break;
        }
        case LowPowerData:
        {
            tmp_reg1[mp_status] = LowPowerData; //�������ֵ����λ����ʾ������Ϊ�ֳ��ɼ�һ�ε�����        
            EnRegister1(REG3_BUF2, tmp_reg3);
            break;
        }
        case TestData:
        {
            tmp_reg1[mp_status] = TestData; //�������ֵ����λ����ʾ������Ϊ���Ե�����
            EnRegister1(REG3_BUF2, tmp_reg3);
            break;
        }
        default:break;
    }
    SaveSampleData(tmp_reg1); //������д��FROM��
}

/*************************************
Function: PacketData2A2
Description: ѡ��ָ����ͨ�������A2
Input: ָ������ͨ����0-12�� dat ���A2Э�����REG3Buf �ɼ���������
Output:��
02 03 18 41 10 00 00 40 F0 FC 46 00 00 00 00 00 00 00 00 41 A0 00 00 42 CA A6 00 BA A2
 **************************************/
void PacketData2A2(u8 *dat, u8*REG3Buf) {
    u16 CRCtmp;

    Register2Read(dat, REG2_Arg_Postion[mi_add], 1); //�豸��ַ  
    *(dat + A2_ID) = 0x03; //������    
    *(dat + A2_Bytes) = UDP_A2_LENGTH - 5; //�ֽ��� ��ȥ������ ��ַ CRCУ��2λ- ����1λ    
    ClearDat(dat + A2_Vb, 0, 8); //�������
    ClearDat(dat + A2_Qb, 0, 4); //���˲����
    CopyDat(dat + A2_Vm, REG3Buf + sb_Vm, 8); //��������
    CopyDat(dat + A2_Qm, REG3Buf + sb_Qm, 4); //����˲����
    ClearDat(dat + A2_T, 0, 4); //�¶�
    ClearDat(dat + A2_P, 0, 4); //ѹ��
    *(dat + A2_Sta) = 0; //�������ֵ
    if (FLagArgbits.LowPoweralarmFlag) //�豸״̬
        *(dat + A2_Sta) |= (1 << 4); //��һ
    else
        *(dat + A2_Sta) &= ~(1 << 4); //����
//    if (FLagArgbits.TestOnlieFlag) //�豸״̬
//        *(dat + A2_Sta) |= (1 << 5); //��һ
//    else
//        *(dat + A2_Sta) &= ~(1 << 5); //����
    CopyDat(dat + A2_Vbat, REG3Buf + sb_Vbat, 4); //��ѹֵ

    CRCtmp = CRC16_Check(dat, UDP_A2_LENGTH - 2); //CRCУ��
    *(dat + A2_CRC16) = (u8) (CRCtmp & 0x00FF);
    *(dat + A2_CRC16 + 1) = (u8) (CRCtmp >> 8);
}

/************************************����������*********************************/
bool TX13IsOK(u8 *output) {
    uint8_t cnt = 0;
    uint8_t tmp[50] = {0, 0, 0};
    do {
        RS485SendString(Read13, 20); //����1.3Э�����ݻ�ȡ�ɼ�����
        Delay100ms(1);
        if (cnt++ > 3)
            return false;
    } while (!UARTIsGet(BufferRead_UART1, tmp, 46, TX13Head, 3));
    CopyDat(output, tmp, 46);

    return true;
}


