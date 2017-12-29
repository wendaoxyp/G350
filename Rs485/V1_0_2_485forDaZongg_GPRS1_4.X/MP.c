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
#include "Status.h"
//#include "Queue.h"

#define PULSE_MAX 100000000 

vu32 gPulseTime = 0; //���벶������2 ��λ��ms
vu32 gPulseCount = 0; //�����ۼ���
static u8 gOverFlag = 0;
u8 mi_SSP[3] = {1, 10, 100};
static u8 Read13[20] = {
    0xCC, 0x02, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0x00, 0xEE
};
static uint8_t TX13Head[3] = {0xCC, 0x02, 0x30};
//static u8 Register1[REG1_BYTES];
u8 AlarmType; //����ȷ����������
/*************************************
Function: PulseIsOver 
Description: �������Ƿ����
Input: ��
Output: ��
 *************************************/
//static bool PulseIsOver(void) {
//    bool b = false;
//    while (gPulseCount >= PULSE_MAX) {
//        gPulseCount -= PULSE_MAX; //����
//        b = true;
//    }
//    return b;
//}

/*************************************
Function: Get_Q
Description: ��ȡ˲����
Input: ��
Output: ��
 *************************************/
//static void Get_Q(const unsigned long nowPulse, float *f) {
//    u8 tmp = 0;
//    u32 pulse_time = gPulseTime; //����ʱ�� ���������ʱ������豸
//    gPulseTime = 0; //����ϴ�����
//    Register2Read(&tmp, REG2_Arg_Postion[reg2_mi_arg2], 1); //ssp=
//    if (tmp > 2) tmp = 0;
//    if (!pulse_time)//�����ȡ����ʱ��Ϊ0�Ļ���
//        *f = 0;
//    else {
//        if (nowPulse < 2) {//�����������С��2�Ļ�
//            *f = (gOverFlag) ? (1.0 * mi_SSP[tmp] * 360000 / pulse_time) : 0; //1*0.1[ssp]/(pulse_time/(3600*1000))
//        } else {
//            *f = 1.0 * mi_SSP[tmp] * 360000 / pulse_time;
//        }
//    }
//}

/*************************************
Function: Get_V 
Description: ��ȡ����
Input: ��
Output: ��
 *************************************/
//static void Get_V(const unsigned long nowPulse, float*tmp) {
//    //float tmp[2];
//    if (nowPulse != 0) {
//        u8 tmp1 = 0;
//        Register2Read(&tmp1, REG2_Arg_Postion[reg2_mi_arg2], 1);
//        if (tmp1 > 2)tmp1 = 0;
//        switch (mi_SSP[tmp1]) {
//            case 1://SSP=0.1
//            {
//                *tmp = floor(nowPulse / 10 / 10000); //��ʼֵΪ124889  =1
//                *(tmp + 1) = nowPulse % 100000 * 1.0 / 10; //  =2488.9
//                break;
//            }
//            case 10:
//            {
//                *tmp = floor(nowPulse / 10000);
//                *(tmp + 1) = nowPulse % 10000;
//                break;
//            }
//            case 100:
//            {
//                *tmp = floor(nowPulse * 10 / 10000);
//                *(tmp + 1) = nowPulse * 10 % 10000;
//                break;
//            }
//        }
//    } else
//        *tmp = *(tmp + 1) = 0;
//}

void SaveSampleData(u8*dat) {
    u16 OffsetAdd1 = gOffsetAdd * REG1_BYTES; //ͳһʹ��ƫ����

    *(dat + mp_sumcheck) = Sum_Check256(dat, REG1_BYTES - 1); //����У���
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
bool GetValueTask(u8 InputSource) {
    u8 tmp_reg1[REG1_BYTES]; //���ڴ�Ųɼ�������        
    u8 tmp_reg3[REG3_BYTES]; //���ڴ�ŷ�������
    u8 tmp[50]; //���ڽ����Ǳ�˵�����
    u8 cnt, cnt1 = 0; //ѭ������
    bool Is_Get = true; //�ж��Ƿ��ȡ������
    u16 check_sum = 0; //У���
    float f_tmp = 0; //��ʱ����
    double d_tmp = 0; //

    ClearDat(tmp_reg1, 0, REG1_BYTES); //�������
    TX13Head[1] = miotArgs.mp_add; //��ȡ֡ͷ�еĵ�ַ����
    check_sum = Sum_Check(Read13, 17); //ǰ17�����ֵ�У����
    Read13[17] = (u8) (check_sum & 0x00ff);
    Read13[18] = (u8) (check_sum >> 8); //��ֵУ����
    LATAbits.LATA2 = 1; //ʹ��485ͨѶ��Դ
    do {
        RS485SendString(Read13, 20); //����1.3Э�����ݻ�ȡ�ɼ����� 20���ֽ�
        Delay100ms(2);
        if (cnt++ > 9) {
            Is_Get = false;
            break;
        }//CC 08 30 1C 00 20 06 06 05 16 16 44 05 7B 86 80 00 00 0E 45 98 01 05 50 00 00 07 65 03 00 AA 5E 80 79 06 EE
        for (cnt1 = 0; cnt1 < 4; cnt1++)//��������ĸ��ֽ�û�н��ܵ����ж�ԭ��
            if (U1STAbits.URXDA == 1) //û�н��յ�
                BufferWrite_UART1();
    } while (!UARTIsGet(BufferRead_UART1, tmp, REG1_BYTES, TX13Head, 3)); //�����յ������ݴ���REG1��С��������
    LATAbits.LATA2 = 0; //ʧ��485ͨѶ��Դ
    if (Is_Get) {
        //����ɼ�ʱ��
        GetUnixTime_Char(tmp + 5, tmp_reg3 + reg3_timestamp);
        //        CopyDat(tmp + 5, tmp_reg3 + reg3_timestamp, 7); //���ɼ�����ʱ�丳ֵ���ݵ��������ݵ�reg1��
        //����ۻ�����V1_acc //��13Э�������ת��ΪIEEE745������ 
        TX2Float(&f_tmp, tmp + 18);
        d_tmp = 2000000 * ((*(tmp + 16) << 8)+ *(tmp + 17)) + (double) f_tmp;
        if (d_tmp >= 1000000) //test
        {
            f_tmp = d_tmp / 1000000;
            FloatToChar(&f_tmp, tmp_reg3 + reg3_Vb);
            d_tmp -= f_tmp * 1000000;
        } else
            ClearDat(tmp_reg3 + reg3_Vb, 0, 4);
        f_tmp = d_tmp;
        FloatToChar(&f_tmp, tmp_reg3 + reg3_Vb + 4);

        //���˲ʱ����V1_ins 
        TX2Float(&f_tmp, tmp + 12);
        FloatToChar(&f_tmp, tmp_reg3 + reg3_Qb);

        //�¶�
        TX2Float(&f_tmp, tmp + 22);
        FloatToChar(&f_tmp, tmp_reg3 + reg3_T);
        if (InputSource == AlarmData) {
            if (f_tmp < miotArgs.AlarmLT)//��ӱ�������
                AlarmType = 2;
            else if (f_tmp > miotArgs.AlarmHT)
                AlarmType = 1;
        }
        //ѹ��
        TX2Float(&f_tmp, tmp + 26);
        FloatToChar(&f_tmp, tmp_reg3 + reg3_P);
        if (InputSource == AlarmData) {
            if (f_tmp < miotArgs.AlarmLP)
                AlarmType = 4;
            else if (f_tmp > miotArgs.AlarmHP)
                AlarmType = 3;
        }
        //״̬��
        tmp_reg3[reg3_sta] = tmp[32];
        //��ص�ѹ
        GetMuilVoltage(&gGetVoltage); //�ɼ���ѹֵ
        FloatToChar(&gGetVoltage, tmp_reg3 + reg3_Vbat);

        //��������ֵ�����������ݱ���������
        CopyDat(tmp_reg1 + mp_time, tmp + 5, 7); //ʱ��        
        ClearDat(tmp_reg1 + mp_Qb, 0, 4); //���˲����
        ClearDat(tmp_reg1 + mp_Vb, 0, 8); //�������
        CopyDat(tmp_reg1 + mp_Qb, tmp_reg3 + reg3_Qb, 4); //����˲����
        CopyDat(tmp_reg1 + mp_Vb, tmp_reg3 + reg3_Vb, 8); //��������
        CopyDat(tmp_reg1 + mp_T, tmp_reg3 + reg3_T, 4); //�¶�
        CopyDat(tmp_reg1 + mp_P, tmp_reg3 + reg3_P, 4); //ѹ��
        CopyDat(tmp_reg1 + mp_Vbat, tmp_reg3 + reg3_Vbat, 4); //��ѹֵ
        CopyDat(tmp_reg1 + mp_status, tmp_reg3 + reg3_sta, 1); //״̬��
        CopyDat(tmp_reg1 + mp_alarm, tmp + 30, 1); //������
        EnRegister1(InputSource, tmp_reg3); //���ɼ�������д�뷢��ͨ����
        SaveSampleData(tmp_reg1); //������д��FROM��
    } //else {//���ʹ������
    Statusbits.staGPRS = (Is_Get) ? MP_GetData_OK : MP_GetData_Fail; //��������ͨѶʧ��
    //}
    return Is_Get;
}

/*************************************
Function: PacketData2A2
Description: ѡ��ָ����ͨ�������A2
Input: ָ������ͨ����0-12�� dat ���A2Э�����REG3Buf �ɼ���������
Output:��
02 03 18 41 10 00 00 40 F0 FC 46 00 00 00 00 00 00 00 00 41 A0 00 00 42 CA A6 00 BA A2
 **************************************/
void PacketData2A2(u8 *A2Dat, u8*REG3Buf) {
    u16 CRCtmp;
    *(A2Dat + A2_Add) = miotArgs.mi_add; //�豸��ַ  
    *(A2Dat + A2_ID) = 0x03; //������    
    *(A2Dat + A2_Bytes) = UDP_A2_LENGTH - 5; //�ֽ��� ��ȥ������ ��ַ CRCУ��2λ- ����1λ    
    ClearDat(A2Dat + A2_Vm, 0, 8); //�������
    ClearDat(A2Dat + A2_Qm, 0, 4); //���˲����
    CopyDat(A2Dat + A2_Vb, REG3Buf + reg3_Vb, 8); //��������
    CopyDat(A2Dat + A2_Qb, REG3Buf + reg3_Qb, 4); //����˲����
    CopyDat(A2Dat + A2_T, REG3Buf + reg3_T, 4); //�¶�
    CopyDat(A2Dat + A2_P, REG3Buf + reg3_P, 4); //ѹ��
    *(A2Dat + A2_Sta) = *(REG3Buf + reg3_sta); //�������ֵ
    //    if (FLagArgbits.LowPoweralarmFlag) //�豸״̬//A2����û�б���ֵ
    //        *(A2Dat + A2_Ala) |= (1 << 4); //��һ
    //    else
    //        *(A2Dat + A2_Ala) &= ~(1 << 4); //����
    //    if (FLagArgbits.TestOnlieFlag) //�豸״̬
    //        *(A2Dat + A2_Sta) |= (1 << 5); //��һ
    //    else
    //        *(A2Dat + A2_Sta) &= ~(1 << 5); //����
    CopyDat(A2Dat + A2_Vbat, REG3Buf + reg3_Vbat, 4); //��ѹֵ

    CRCtmp = CRC16_Check(A2Dat, UDP_A2_LENGTH - 2); //CRCУ��
    *(A2Dat + A2_CRC16) = (u8) (CRCtmp & 0x00FF);
    *(A2Dat + A2_CRC16 + 1) = (u8) (CRCtmp >> 8);
}
//����ȡ��������ת��Ϊ13Э��

//void PacketData213(u8 *dat, u8*REG3Buf) {
//    *dat = 0xcc;
//    Register2Read(dat + 1, REG2_Arg_Postion[mi_add], 1); //�豸��ַ  
//    *(dat + 2) = 0x03; //������    
//    *(dat + 3) = UDP_13_LENGTH - 6; //�ֽ��� ��ȥ������ ��ַ CRCУ��2λ- ����1λ    
//    *(dat + 4) = 0;
//    CopyDat(dat + 5, REG3Buf, UDP_13_LENGTH - 6);
//    *(dat + 35) = 0xee;
//}



