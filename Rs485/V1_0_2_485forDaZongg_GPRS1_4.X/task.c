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

void Task_TimeUp(void)//进入先读取 发送一次数据
{
    if (FLagArgbits.tgprsFlag) { //GPRS通讯时间
        Statusbits.staMiot = MIOT_GPRS;
        if (Reg3_Buf1_Recordbits.Record) {//如果有采集到的数据组的话)
            if (CopUDPTask(SampleData, 3, 1)) //GPRS上线通讯数据     
                gGPRS_Fail_Count = 0;
            else
                gGPRS_Fail_Count++;
        }
        SaveMiotArg(); //保存数据
        FLagArgbits.tgprsFlag = 0;
    }
    if (FLagArgbits.LowPoweralarmFlag) { //GPRS报警时间
        FLagArgbits.LowPowerGetDataFlag = 1; //获取报警数据
        StartTime4(); //开始通过定时器4获取数据
        IFS1bits.T4IF = 1; //开启定时器4的中断
        while (IFS1bits.T4IF)
            StartTime4(); //while (!IFS1bits.T4IF); //等待读取数据完成
        Statusbits.staMiot = MIOT_Low_Power;
        CopUDPTask(LowPowerData, 3, 1); //GPRS上线报警
        FLagArgbits.LowPoweralarmFlag = 0;
    }
}


