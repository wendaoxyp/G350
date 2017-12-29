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
        if (Reg3_Buf1_Recordbits.Record) {//����вɼ�����������Ļ�)
            if (CopUDPTask(SampleData, 3, 3)) //GPRS����ͨѶ����     
                gGPRS_Fail_Count = 0;
            else
                gGPRS_Fail_Count++;
        }
        FLagArgbits.tgprsFlag = 0;
    }
    if (FLagArgbits.tLowPoweralarmFlag) { //GPRS����ʱ��
        u8 tmp[2] = {0, 0};
        Register2Read(tmp, REG2_Arg_Postion[mi_talarm], 2);
        if (tmp[0] || tmp[1]) {//�������ֵ��Ϊ0�Ļ�
            CopUDPTask(LowPowerData, 3, 3); //GPRS���߱���
        } else {
            if (!gAlarmZeroLock) {
                gAlarmZeroLock = 1;
                CopUDPTask(LowPowerData, 3, 3); //GPRS���߱���
            }
        }
        FLagArgbits.tLowPoweralarmFlag = 0;
    }    
}


