#include "user.h"
#include "Mp.h"
#include "GPRS.h"
#include "P-Miot1601.h"
#include "Miot1601.h"
#include "Status.h"

extern const u8 Ver[5];
extern u8 gGPRS_Fail_Count;
//extern const u8 GPRS_Arg1[144];
extern u8 gAlarmZeroLock;

void Task_TimeUp(void)//�����ȶ�ȡ ����һ������
{
    if (FLagArgbits.tgprsFlag) { //GPRSͨѶʱ��
        Statusbits.staMiot = MIOT_GPRS;
        if (Reg3_Buf1_Recordbits.Record) {//����вɼ�����������Ļ�)
            if (CopUDPTask(SampleData, 3, 1)) //GPRS����ͨѶ����     
                gGPRS_Fail_Count = 0;
            else
                gGPRS_Fail_Count++;
        }
        SaveMiotArg(); //��������
        FLagArgbits.tgprsFlag = 0;
    }
    if (FLagArgbits.LowPoweralarmFlag) { //GPRS����ʱ��
        FLagArgbits.LowPowerGetDataFlag = 1; //��ȡ��������
        StartTime4(); //��ʼͨ����ʱ��4��ȡ����
        IFS1bits.T4IF = 1; //������ʱ��4���ж�
        while (IFS1bits.T4IF)
            StartTime4(); //while (!IFS1bits.T4IF); //�ȴ���ȡ�������
        Statusbits.staMiot = MIOT_Low_Power;
        CopUDPTask(LowPowerData, 3, 1); //GPRS���߱���
        FLagArgbits.LowPoweralarmFlag = 0;
    }
}


