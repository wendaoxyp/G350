/* 
 * File:   NVIC.c
 * Author: TURONG62
 *
 * Created on 2016年6月6日, 上午8:48
 */
#include "user.h"
#include "UART.h"
#include "SerialBuffer.h"
#include "RS485.h"
#include "25L64B.h"
#include "Miot1601.h"

struct FLag_Arg FLagArgbits;
struct TimeCount gTimeCount;
struct UART2_Arg UART2Argbits;
extern u8 gAlarmZeroLock; //
//u8 gLastPulseSta = 0; //记录脉冲的数量
//u32 gLastTCount = 0; //记录T1最后一次数据
u8 gGPRS_Fail_Count = 0; //复GPRS上传失败记数
float gGetVoltage = 0; //获取电压值
//u8 gTM2CNT = 0;

/*************************************
Function: 闹钟中断 
Description: 定时唤醒设备，进行时间计算
Input: 无 
Output: 无
 *************************************/
void __attribute__((__interrupt__, __auto_psv__)) _RTCCInterrupt(void) {
    OSCChange(0x00);
    gTimeCount.timeAlarm++; //单位为分钟
    gTimeCount.timeGprs++;
    gTimeCount.timeMp++;

    //    if ((gTimeCount.timeMp >= miotArgs.timemp - SettingSampleTime)&&(!FLagArgbits.PulseTimeFlag)) {//开启定时器1进行采集优先采集，进行6分钟
    //        FLagArgbits.T1CountFlag = 1;
    //        T1CONbits.TON = 1;
    //    }

    if (gTimeCount.timeMp >= miotArgs.timemp) {//采集数据，并写入FRAM
        gTimeCount.timeMp = 0;
        //        FLagArgbits.PulseTimeFlag = 0;
        //        FLagArgbits.T1CountFlag = 0; //避免没有获取到脉冲时间的时候，也关闭定时器
        T1CONbits.TON = 0; //关闭定时器1
        StartTime4();
        IFS1bits.T4IF = 1; //T4CONbits.TON = 1;进入定时器开始采集
        //        if (FLagArgbits.LowPowerGetDataFlag || FLagArgbits.TestGetDataFlag)
        //            CloseTime4();
    }

    if (gTimeCount.timeGprs >= miotArgs.timegprs) {//GPRS上传
        gTimeCount.timeGprs = 0;
        FLagArgbits.tgprsFlag = 1;
    }

    if (!(FLagArgbits.tgprsFlag || FLagArgbits.LowPoweralarmFlag || FLagArgbits.TestOnlieFlag)) {//上线过程中不进行电压采集
        GetMuilVoltage(&gGetVoltage); //采集电压值
        //进行判断是否要进行低压报警，A*(C*D+/B*/C)
        if ((miotArgs.AlarmVoltage > gGetVoltage)&&
                ((!gAlarmZeroLock && !miotArgs.timealarm) ||
                (miotArgs.timealarm && (gTimeCount.timeAlarm >= miotArgs.timealarm)))) {
            gTimeCount.timeAlarm = 0;
            FLagArgbits.LowPoweralarmFlag = 1;
        }
    }
    if (FLagArgbits.tgprsFlag || FLagArgbits.LowPoweralarmFlag)
        FLagArgbits.SleepExitFlag = 1;
    else
        FLagArgbits.SleepExitFlag = 0;
    IFS3bits.RTCIF = 0; //clear RTC标志位      
}

/*************************************
Function: 定时器中断 
Description: 用于计算瞬间量
Input: 无 
Output: 无
 *************************************/
//void __attribute__((__interrupt__, __auto_psv__, __shadow__)) _T1Interrupt(void) {
//
//    gT1Count++;
//    IFS0bits.T1IF = 0; //Reset Timer1 interrupt flag and Return from ISR
//}

/*************************************
Function: 定时器中断 
Description: 用于485通讯，时间延时
Input: 无 
Output: 无
 *************************************/

void __attribute__((__interrupt__, __auto_psv__, __shadow__)) _T2Interrupt(void) {

    while (!U1STAbits.RIDLE);
    PC_Cop();
    T2CONbits.TON = 0;
    TMR2 = 0;
    FLagArgbits.TestFlag = 0; //退出调试模式
    IFS0bits.T2IF = 0; //Reset Timer1 interrupt flag and Return from ISR
}

/*************************************
Function: 定时器中断 
Description: 用于在GPRS上线过程中，定时时间
Input: 无 
Output: 无
 *************************************/
void __attribute__((__interrupt__, __auto_psv__, __shadow__)) _T3Interrupt(void) {

    gT3Count++;
    IFS0bits.T3IF = 0; //Reset Timer1 interrupt flag and Return from ISR
}

/*************************************
Function: 定时器t4中断 
Description: 用于采集数据的任务
Input: 无 
Output: 无
 *************************************/
void __attribute__((__interrupt__, __auto_psv__, __shadow__)) _T4Interrupt(void) {
    if (FLagArgbits.LowPowerGetDataFlag) {
        GetValueTask(LowPowerData);
        FLagArgbits.LowPowerGetDataFlag = 0; //) ? false : true; //获取报警时仪表的通讯数据        
    } else if (FLagArgbits.AlarmGetDataFlag) {
        GetValueTask(AlarmData);
        FLagArgbits.AlarmGetDataFlag = 0; //获取报警时仪表的通讯数据     
    } else if (FLagArgbits.TestGetDataFlag) {
        Delay1s(1); //延时1s便于上位机获取数据
        GetValueTask(TestData);
        FLagArgbits.TestGetDataFlag = 0; //  ? false : true; //获取报警时仪表的通讯数据
    } else
        GetValueTask(SampleData); //获取仪表的通讯数据
    //    FM25L64B_Write(BOR_Pulse, (u8*) (&gPulseCount), 4); //保存脉冲总量
    IFS1bits.T4IF = 0; //Reset Timer1 interrupt flag and Return from ISR 
    CloseTime4(); //多处都会使用该全局变量
}

/*************************************
Function: 电平变化中断 
Description: 获取脉冲的任务
Input: 无 
Output: 无
 *************************************/
//void __attribute__((__interrupt__, __auto_psv__)) _CNInterrupt(void) { //提醒更换电池
//    if (S1) {//通过第二次上升获取数据
//        gPulseCount++; //脉冲数+1
//        if (FLagArgbits.T1CountFlag && FLagArgbits.T1CountLastFlag) {//如果开启T1定时器而且是第二次进入，则采集数据
//            gPulseTime = gT1Count * 1000 + (((u32) TMR1) * 1000 >> 15) + 100; //单位ms
//            if (gPulseTime < 2000)//采集时间小于2s
//                gPulseTime = 0;
//            else {
//
////                FLagArgbits.PulseTimeFlag = 1; // 如果已经获取到脉冲时间，那么需要关闭定时器
//                FLagArgbits.T1CountFlag = 0;
//                T1CONbits.TON = 0;
//            }
//        }
//        TMR1 = 0;
//        gT1Count = 0;
//        FLagArgbits.T1CountLastFlag = FLagArgbits.T1CountFlag; //通过上升沿，关闭FLagArgbits.T1CountLastFlag
//    }
//    IFS1bits.CNIF = 0;
//}

/*************************************
Function: UART1接收中断
Description: 485通讯
Input: 无 
Output: 无
 *************************************/
void __attribute__((__interrupt__, __auto_psv__)) _U1RXInterrupt(void) {
    //    GPRS_ON;
    //    OSCChange(0x00); //将主频切换回来
    //    GPRS_OFF;
    u8 cnt = 0;
    for (cnt = 0; cnt < 4; cnt++)

        if (U1STAbits.URXDA == 1) //没有接收到
            BufferWrite_UART1();
    //    IEC0bits.T2IE = 1;T2CONbits.TON = 1;
    IFS0bits.U1RXIF = 0;
}

/*************************************
Function: UART2接收中断
Description: GPRS通讯
Input: 无 
Output: 无
 *************************************/
void __attribute__((__interrupt__, __auto_psv__)) _U2RXInterrupt(void) {
    u8 cnt = 0;
    for (cnt = 0; cnt < 4; cnt++)

        if (U2STAbits.URXDA == 1) //没有接收到        
            BufferWrite_UART2();
    IFS1bits.U2RXIF = 0;
}

/*************************************
Function: UART2发送中断
Description: GPRS通讯
Input: 无 
Output: 无
 *************************************/
void __attribute__((interrupt, no_auto_psv)) _U2TXInterrupt(void) {
    u8 cnt = 0;
    while ((cnt < UART2Argbits.bytes2) && (!(U2STAbits.UTXBF == 1))) {
        U2TXREG = *(UART2Argbits.dat2 + cnt); //发送数据

        while (!U2STAbits.TRMT);
        cnt++;
    }
    IFS1bits.U2TXIF = 0;
}

/*************************************
Function: UART1错误终端
Description: 无
Input: 无 
Output: 无
 *************************************/
void __attribute__((interrupt, no_auto_psv)) _U1ErrInterrupt(void) {
    if (U1STAbits.OERR == 1)
        U1STAbits.OERR = 0;
    IFS4bits.U1ERIF = 0;
}

/*************************************
Function: UART2错误中断
Description: 无
Input: 无 
Output: 无
 *************************************/
void __attribute__((interrupt, no_auto_psv)) _U2ErrInterrupt(void) {
    if (U2STAbits.OERR == 1)
        U2STAbits.OERR = 0;
    IFS4bits.U2ERIF = 0;
}

/*************************************
Function: 外部终端1
Description: 电池电压检测
Input: 无 
Output: 无
 *************************************/
void __attribute__((interrupt, no_auto_psv)) _INT1Interrupt(void) {

    OSCChange(0x00); //将主频切换回来
    OpenRS485(); //开启485通讯
    FLagArgbits.TestFlag = 1; //进入调试模式
    T2CONbits.TON = 1; //开启定时器2进入参数设置
    //    IEC1bits.INT1IE = 0;
    //    while (!IFS0bits.T2IF) T2CONbits.TON = 1; //开启定时器2进入参数设置
    IFS1bits.INT1IF = 0;
}

/*************************************
Function: 默认终端
Description: 无
Input: 无 
Output: 无
 *************************************/
void __attribute__((interrupt, no_auto_psv)) _DefaultInterrupt(void) {
    u8 rtcc_time[7] = {0, 0, 0};
    RTCReadTime(rtcc_time);
    Register2Write(rtcc_time, REG2_Arg_Postion[reg2_mi_year], 7);

    SaveMiotArg();
    //    FM25L64B_Write(BOR_Pulse, (u8*) (&gPulseCount), 4); //保存脉冲总量
    //    RTCReadTime(tmp); //获取最新时间
    //    FM25L64B_Write(RST_Data, (u8*) & RCON, 2); //保存时间
    //    FM25L64B_Write(RST_Data + 2, (u8*) & IFS0, 2); //保存时间
    //    FM25L64B_Write(RST_Data + 4, (u8*) & IFS1, 2); //保存时间
    //    FM25L64B_Write(RST_Data + 6, (u8*) & IFS2, 2); //保存时间
    //    FM25L64B_Write(RST_Data + 8, (u8*) & IFS3, 2); //保存时间
    //    FM25L64B_Write(RST_Data + 10, (u8*) & IFS4, 2); //保存时间
    //    FM25L64B_Write(RST_Data + 12, (u8*) & IFS5, 2); //保存时间
    //    FM25L64B_Write(RST_Data + 14, (u8*) & IPC0, 2); //保存时间
    //    FM25L64B_Write(RST_Data + 16, (u8*) & IPC1, 2); //保存时间
    //    FM25L64B_Write(RST_Data + 18, (u8*) & IPC2, 2); //保存时间
    //    FM25L64B_Write(RST_Data + 20, (u8*) & IPC3, 2); //保存时间
    //    FM25L64B_Write(RST_Data + 22, (u8*) & IPC4, 2); //保存时间
    //    FM25L64B_Write(RST_Data + 24, (u8*) & IPC5, 2); //保存时间
    //    FM25L64B_Write(RST_Data + 26, (u8*) & IPC6, 2); //保存时间
    //    FM25L64B_Write(RST_Data + 28, (u8*) & IPC7, 2); //保存时间
    //    FM25L64B_Write(RST_Data + 30, (u8*) & IPC8, 2); //保存时间
    //    FM25L64B_Write(RST_Data + 32, (u8*) & IPC9, 2); //保存时间
    //    FM25L64B_Write(RST_Data + 34, (u8*) & IPC12, 2); //保存时间
    //    FM25L64B_Write(RST_Data + 36, (u8*) & IPC15, 2); //保存时间
    //    FM25L64B_Write(RST_Data + 38, (u8*) & IPC16, 2); //保存时间
    //    FM25L64B_Write(RST_Data + 40, (u8*) & IEC0, 2); //保存时间
    //    FM25L64B_Write(RST_Data + 42, (u8*) & IEC1, 2); //保存时间
    //    FM25L64B_Write(RST_Data + 44, (u8*) & IEC2, 2); //保存时间
    //    FM25L64B_Write(RST_Data + 46, (u8*) & IEC3, 2); //保存时间
    //    FM25L64B_Write(RST_Data + 48, (u8*) & IEC4, 2); //保存时间
    //    FM25L64B_Write(RST_Data + 50, (u8*) & IEC5, 2); //保存时间
    //    FM25L64B_Write(RST_Data+14, tmp, 2); //保存时间
    if (INTCON1bits.STKERR)INTCON1bits.STKERR = 0;
    if (INTCON1bits.ADDRERR)INTCON1bits.ADDRERR = 0;

    if (INTCON1bits.MATHERR)INTCON1bits.MATHERR = 0;
    Reset();
}



