#include "user.h"
#include "Mp.h"
#include "GPRS.h"
#include "P-Miot1601.h"
#include "Miot1601.h"

extern const u8 Ver[5];
extern u8 gGPRS_Fail_Count;
extern const u8 GPRS_Arg1[144];
extern u8 gAlarmZeroLock;

void Task_TimeUp(void)//�����ȶ�ȡ ����һ������
{
    if (FLagArgbits.tgprsFlag) { //GPRSͨѶʱ��
        if (Reg1Argbits.Record) {//����вɼ�����������Ļ�)
            if (CopUDPTask(DataSamples)) //GPRS����ͨѶ����     
                gGPRS_Fail_Count = 0;
            else
                gGPRS_Fail_Count++;
        }
        FLagArgbits.tgprsFlag = 0;
    }
    if (FLagArgbits.talarmFlag) { //GPRS����ʱ��
        u8 tmp[2] = {0, 0};
        Register2Read(tmp, mi_arg_add[mi_talarm], 2);
        if (tmp[0] || tmp[1]) {//�������ֵ��Ϊ0�Ļ�
            CopUDPTask(LowPowerAlarm); //GPRS���߱���
        } else {
            if (!gAlarmZeroLock) {
                gAlarmZeroLock = 1;
                CopUDPTask(LowPowerAlarm); //GPRS���߱���
            }
        }
        FLagArgbits.talarmFlag = 0;
    }
    //    if (FLagArgbits.CheckRTCCFlag) {
    //        GetGMTTimeTask();
    //        ChangeGPRSArg(GPRS_Arg2); //д�������������޸ĳɹ�����Уʱʧ�ܵ����
    //        FLagArgbits.CheckRTCCFlag = 0;
    //    }
}


