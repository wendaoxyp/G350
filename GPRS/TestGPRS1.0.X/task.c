#include "user.h"
#include "Mp.h"
#include "GPRS.h"
#include "P-Miot1601.h"
#include "Miot1601.h"

extern const u8 Ver[5];
extern u8 gGPRS_Fail_Count;
extern const u8 GPRS_Arg1[144];
extern u8 gAlarmZeroLock;

void Task_TimeUp(void)//进入先读取 发送一次数据
{
    if (FLagArgbits.tgprsFlag) { //GPRS通讯时间
        if (Reg1Argbits.Record) {//如果有采集到的数据组的话)
            if (CopUDPTask(DataSamples)) //GPRS上线通讯数据     
                gGPRS_Fail_Count = 0;
            else
                gGPRS_Fail_Count++;
        }
        FLagArgbits.tgprsFlag = 0;
    }
    if (FLagArgbits.talarmFlag) { //GPRS报警时间
        u8 tmp[2] = {0, 0};
        Register2Read(tmp, mi_arg_add[mi_talarm], 2);
        if (tmp[0] || tmp[1]) {//如果报警值不为0的话
            CopUDPTask(LowPowerAlarm); //GPRS上线报警
        } else {
            if (!gAlarmZeroLock) {
                gAlarmZeroLock = 1;
                CopUDPTask(LowPowerAlarm); //GPRS上线报警
            }
        }
        FLagArgbits.talarmFlag = 0;
    }
    //    if (FLagArgbits.CheckRTCCFlag) {
    //        GetGMTTimeTask();
    //        ChangeGPRSArg(GPRS_Arg2); //写入参数避免参数修改成功但是校时失败的情况
    //        FLagArgbits.CheckRTCCFlag = 0;
    //    }
}


