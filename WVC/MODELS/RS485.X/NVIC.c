/* 
 * File:   NVIC.c
 * Author: TURONG62
 *
 * Created on 2016年6月6日, 上午8:48
 */
//#include "UART2.h"
//#include "RS485.h"
//#include "UART3.h"
//#include "includes.h"
#include <stdbool.h>
#include <stdint.h>
#include <xc.h>
#include "SerialBuffer.h"
//#include "RTCC.h"

//extern OS_EVENT *sem_receive_pressure, *sem_set_alarm;
//extern volatile uint8_t i2c1_state;
//extern I2C1_Buffer i2c_buf;
//extern OS_FLAG_GRP *sem_F;
///*************************************
//Function: 闹钟中断 
//Description: 定时唤醒设备，进行时间计算
//Input: 无 
//Output: 无
// *************************************/
//void __attribute__((__interrupt__, __auto_psv__)) _RTCCInterrupt(void) {
//    OSCChange(0x00);
//    gTimeCount.timeAlarm++; //单位为分钟
//    gTimeCount.timeGprs++;
//    gTimeCount.timeMp++;
//
//    if ((gTimeCount.timeMp >= miotArgs.timemp - SettingSampleTime)&&(!FLagArgbits.PulseTimeFlag)) {//开启定时器1进行采集优先采集，进行6分钟
//        FLagArgbits.T1CountFlag = 1;
//        T1CONbits.TON = 1;
//    }
//
//    if (gTimeCount.timeMp >= miotArgs.timemp) {//采集数据，并写入FRAM
//        gTimeCount.timeMp = 0;
//        FLagArgbits.PulseTimeFlag = 0;
//        FLagArgbits.T1CountFlag = 0; //避免没有获取到脉冲时间的时候，也关闭定时器
//        T1CONbits.TON = 0; //关闭定时器1
//        StartTime4();
//        IFS1bits.T4IF = 1; //T4CONbits.TON = 1;进入定时器开始采集
//    }
//
//    if (gTimeCount.timeGprs >= miotArgs.timegprs) {//GPRS上传
//        gTimeCount.timeGprs = 0;
//        FLagArgbits.tgprsFlag = 1;
//    }
//
//    //    FLagArgbits.LowPowerFlag = !BAT_DEC; //在每秒获取数据
//    if (gTimeCount.timeAlarm >= miotArgs.timealarm) {
//        float getvoltage = 0;
//        gTimeCount.timeAlarm = 0;
//        GetVoltage(&getvoltage);
//        if (miotArgs.AlarmVoltage > getvoltage) {
//            FLagArgbits.LowPoweralarmFlag = 1; 
//        }
//    }
//    if (FLagArgbits.tgprsFlag || FLagArgbits.LowPoweralarmFlag)
//        FLagArgbits.SleepExitFlag = 1;
//    else
//        FLagArgbits.SleepExitFlag = 0;
//    IFS3bits.RTCIF = 0; //clear RTC标志位      
//}

/* Function:
    void __attribute__ ( ( interrupt, no_auto_psv ) ) _ISR _RTCCInterrupt( void )

  Summary:
    Interrupt Service Routine for the RTCC Peripheral

  Description:
    This is the interrupt service routine for the RTCC peripheral. Add in code if 
    required in the ISR. 
 */

//void __attribute__((interrupt, no_auto_psv)) _ISR _RTCCInterrupt(void) {
//    /* TODO : Add interrupt handling code */
//    OSIntEnter();
//    //    //    OSSemPost(sem_set_alarm);//notes :sem can't find here
//    IFS3bits.RTCIF = false;
//    OSIntExit();
//    OSSemPost(sem_set_alarm);
//}

/*************************************
Function: 外部终端0
Description: 电压检测
Input: 无 
Output: 无
 *************************************/
void __attribute__((interrupt, no_auto_psv))_ISR _INT0Interrupt(void) {
    //    OSIntEnter();
    IFS0bits.INT0IF = 0;
    //    OSIntExit();
    //    OSSemPost(sem_receive_pressure);
}
/*************************************
Function: 定时器中断 
Description: 用于在GPRS上线过程中，定时时间
Input: 无 
Output: 无
 *************************************/
//void __attribute__((__interrupt__, __auto_psv__, __shadow__)) _T3Interrupt(void) {
//    gT3Count++;
//    IFS0bits.T3IF = 0; //Reset Timer1 interrupt flag and Return from ISR
//}

/*************************************
Function: 定时器中断 
Description: 用于485通讯，时间延时
Input: 无 
Output: 无
 *************************************/
//void __attribute__((__interrupt__, __auto_psv__, __shadow__)) _T2Interrupt(void) {
//    while (!U1STAbits.RIDLE);
//    PC_Cop();
//    T2CONbits.TON = 0;
//    TMR2 = 0;
//    FLagArgbits.TestFlag = 0; //退出调试模式
//    IFS0bits.T2IF = 0; //Reset Timer1 interrupt flag and Return from ISR
//}

/*************************************
Function: 定时器中断 
Description: 用于计算瞬间量
Input: 无 
Output: 无
 *************************************/
//void __attribute__((__interrupt__, __auto_psv__, __shadow__)) _T1Interrupt(void) {
//    gT1Count++;
//    IFS0bits.T1IF = 0; //Reset Timer1 interrupt flag and Return from ISR
//}

/*************************************
Function: 定时器t4中断 
Description: 用于采集数据的任务
Input: 无 
Output: 无
 *************************************/
//void __attribute__((__interrupt__, __auto_psv__, __shadow__)) _T4Interrupt(void) {
//    if (FLagArgbits.LowPowerGetDataFlag) {
//        FLagArgbits.LowPowerGetDataFlag = 0;
//        GetValueTask(LowPowerData); //获取报警时仪表的通讯数据
//    } else if (FLagArgbits.TestGetDataFlag) {
//        FLagArgbits.TestGetDataFlag = 0;
//        GetValueTask(TestData); //获取报警时仪表的通讯数据
//    } else
//        GetValueTask(SampleData); //获取仪表的通讯数据
//    FM25L64B_Write(BOR_Pulse, (u8*) (&gPulseCount), 4); //保存脉冲总量
//
//    IFS1bits.T4IF = 0; //Reset Timer1 interrupt flag and Return from ISR 
//    CloseTime4();
//}

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
//                FLagArgbits.PulseTimeFlag = 1; // 如果已经获取到脉冲时间，那么需要关闭定时器
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

///*************************************
//Function: UART1接收中断
//Description: 485通讯
//Input: 无 
//Output: 无
// *************************************/
//void __attribute__((__interrupt__, __auto_psv__)) _U1RXInterrupt(void) {
//    //    OSIntEnter();
//    uint8_t cnt = 0;
//    for (cnt = 0; cnt < 4; cnt++)
//        if (U1STAbits.URXDA == 1) //没有接收到
//            BufferWrite_UART1();
//    IFS0bits.U1RXIF = 0;
//    //    OSIntExit();
//}

/*************************************
Function: UART2接收中断
Description: GPRS通讯
Input: 无 
Output: 无
 *************************************/
void __attribute__((__interrupt__, __auto_psv__)) _U2RXInterrupt(void) {
    //    OSIntEnter();
    uint8_t cnt = 0;
    for (cnt = 0; cnt < 4; cnt++)
        if (U2STAbits.URXDA == 1) //没有接收到        
            BufferWrite_UART2();
    IFS1bits.U2RXIF = 0;
    //    OSIntExit();
}

///*************************************
//Function: UART2接收中断
//Description: GPRS通讯
//Input: 无 
//Output: 无
// *************************************/
//void __attribute__((__interrupt__, __auto_psv__)) _U3RXInterrupt(void) {
//    OSIntEnter();
//    uint8_t cnt = 0;
//    for (cnt = 0; cnt < 4; cnt++)
//        if (U3STAbits.URXDA == 1) //没有接收到        
//            BufferWrite_UART3();
//    IFS5bits.U3RXIF = 0;
//    OSIntExit();
//}

/*************************************
Function: UART2发送中断
Description: GPRS通讯
Input: 无 
Output: 无
 *************************************/
//void __attribute__((interrupt, no_auto_psv)) _U2TXInterrupt(void) {
//    u8 cnt = 0;
//    while ((cnt < UART2Argbits.bytes2) && (!(U2STAbits.UTXBF == 1))) {
//        U2TXREG = *(UART2Argbits.dat2 + cnt); //发送数据
//
//        while (!U2STAbits.TRMT);
//        cnt++;
//    }
//    IFS1bits.U2TXIF = 0;
//}

///*************************************
//Function: UART1错误终端
//Description: 无
//Input: 无 
//Output: 无
// *************************************/
//void __attribute__((interrupt, no_auto_psv)) _U1ErrInterrupt(void) {
//    OSIntEnter();
//    if (U1STAbits.OERR == 1)
//        U1STAbits.OERR = 0;
//    IFS4bits.U1ERIF = 0;
//    OSIntExit();
//}

/*************************************
Function: UART2错误中断
Description: 无
Input: 无 
Output: 无
 *************************************/
void __attribute__((interrupt, no_auto_psv)) _U2ErrInterrupt(void) {
    //    OSIntEnter();
    if (U2STAbits.OERR)
        U2STAbits.OERR = 0;
    if (U2STAbits.FERR)
        if (U2STAbits.URXDA == 1) //没有接收到        
            BufferWrite_UART2();
    IFS4bits.U2ERIF = 0;
    //    OSIntExit();
}

/*************************************
Function: 默认中断
Description: 无
Input: 无 
Output: 无
 *************************************/
void __attribute__((interrupt, no_auto_psv)) _DefaultInterrupt(void) {
    if (INTCON1bits.STKERR)INTCON1bits.STKERR = 0;
    if (INTCON1bits.ADDRERR)INTCON1bits.ADDRERR = 0;
    if (INTCON1bits.MATHERR)INTCON1bits.MATHERR = 0;
    asm("GOTO __reset");
}


