/* 
 * File:   NVIC.c
 * Author: TURONG62
 *
 * Created on 2016年6月6日, 上午8:48
 */
//#include "UART2.h"
//#include "RS485.h"
//#include "UART3.h"
#include "SerialBuffer.h"
#include "includes.h"
#include "stdbool.h"
#include "stdio.h"
#include "RTCC.h"

extern OS_EVENT *sem_receive_pressure, *sem_set_alarm;
extern volatile uint8_t i2c1_state;
extern I2C1_Buffer i2c_buf;
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

void __attribute__((interrupt, no_auto_psv)) _ISR _RTCCInterrupt(void) {
    /* TODO : Add interrupt handling code */
    OSIntEnter();
    //    //    OSSemPost(sem_set_alarm);//notes :sem can't find here
    IFS3bits.RTCIF = false;
    OSIntExit();
//    OSSemPost(sem_set_alarm);
}

/*************************************
Function: 外部终端0
Description: 电压检测
Input: 无 
Output: 无
 *************************************/
void __attribute__((interrupt, no_auto_psv))_ISR _INT0Interrupt(void) {
    OSIntEnter();
    IFS0bits.INT0IF = 0;
    OSIntExit();
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

/*************************************
Function: UART1接收中断
Description: 485通讯
Input: 无 
Output: 无
 *************************************/
void __attribute__((__interrupt__, __auto_psv__)) _U1RXInterrupt(void) {
    OSIntEnter();
    uint8_t cnt = 0;
    for (cnt = 0; cnt < 4; cnt++)
        if (U1STAbits.URXDA == 1) //没有接收到
            BufferWrite_UART1();
    IFS0bits.U1RXIF = 0;
    OSIntExit();
}

/*************************************
Function: UART2接收中断
Description: GPRS通讯
Input: 无 
Output: 无
 *************************************/
void __attribute__((__interrupt__, __auto_psv__)) _U2RXInterrupt(void) {
    OSIntEnter();
    uint8_t cnt = 0;
    for (cnt = 0; cnt < 4; cnt++)
        if (U2STAbits.URXDA == 1) //没有接收到        
            BufferWrite_UART2();
    IFS1bits.U2RXIF = 0;
    OSIntExit();
}

/*************************************
Function: UART2接收中断
Description: GPRS通讯
Input: 无 
Output: 无
 *************************************/
void __attribute__((__interrupt__, __auto_psv__)) _U3RXInterrupt(void) {
    OSIntEnter();
    uint8_t cnt = 0;
    for (cnt = 0; cnt < 4; cnt++)
        if (U3STAbits.URXDA == 1) //没有接收到        
            BufferWrite_UART3();
    IFS5bits.U3RXIF = 0;
    OSIntExit();
}

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

/*************************************
Function: UART1错误终端
Description: 无
Input: 无 
Output: 无
 *************************************/
void __attribute__((interrupt, no_auto_psv)) _U1ErrInterrupt(void) {
    OSIntEnter();
    if (U1STAbits.OERR == 1)
        U1STAbits.OERR = 0;
    IFS4bits.U1ERIF = 0;
    OSIntExit();
}

/*************************************
Function: UART2错误中断
Description: 无
Input: 无 
Output: 无
 *************************************/
void __attribute__((interrupt, no_auto_psv)) _U2ErrInterrupt(void) {
    OSIntEnter();
    if (U2STAbits.OERR == 1)
        U2STAbits.OERR = 0;
    IFS4bits.U2ERIF = 0;
    OSIntExit();
}

/*************************************
Function: UART2错误中断
Description: 无
Input: 无 
Output: 无
 *************************************/
void __attribute__((interrupt, no_auto_psv)) _U3ErrInterrupt(void) {
    OSIntEnter();
    if (U3STAbits.OERR == 1)
        U3STAbits.OERR = 0;
    IFS5bits.U3ERIF = 0;
    OSIntExit();
}

/*************************************
Function: 默认终端
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

void __attribute__((interrupt, no_auto_psv)) _MI2C1Interrupt(void) {
    OSIntEnter();
    static uint16_t i2c_operatcode;
    static uint8_t* pi2c_buf_ptr;
    static uint16_t i2c_address;
    static uint8_t i2c_bytes_left;
    static I2C_Flag i2c_flag;
    static bool i2c_IsResart; //设备是否重启

    IFS1bits.MI2C1IF = 0; //清楚中断标志位
    if (I2C1STATbits.IWCOL) {//如果写冲突检测位为1，那么清楚错误位，并将状态设置为空闲
        I2C1STATbits.IWCOL = 0;
        //        i2c_address_restart = 0;
        //是否需要清楚数据
        return;
    }
    /* Handle the correct i2c state */
    switch (i2c1_state) {
        case S_MASTER_IDLE: /* In reset state, waiting for data to send */
        {
            if (i2c_bytes_left == 0) {//如果数据数据不为0的话
                //                I2C1CONbits.SEN = 1; // 发送启动条件
                //            } else {
                I2C1CONbits.SEN = 1; // 发送启动条件
                i2c_operatcode = i2c_buf.operatcode; //赋值操作码
                i2c_address = i2c_buf.address; //赋值地址
                i2c_bytes_left = i2c_buf.length; //赋值长度
                pi2c_buf_ptr = i2c_buf.pbuffer; //赋值数据地址
                i2c_flag = i2c_buf.flag; //将设备选择和工作模式均赋值
                i2c_IsResart = 0;
                i2c1_state = S_MASTER_SEND_ADDR; //状态设置为发送地址
            }
            break;
        }
        case S_MASTER_RESTART:
        {
            I2C1CONbits.RSEN = 1; // 发送启动条件
            i2c_bytes_left = i2c_buf.length; //赋值长度
            i2c1_state = S_MASTER_SEND_ADDR; //状态设置为发送地址
            break;
        }
        case S_MASTER_SEND_ADDR:
        {
            if (!i2c_flag.F_IsSelectiveMode) {//表示不带地址读取数据 && i2c_IsResart) {
                if (i2c_flag.F_WriteOrRead) {//如果是读指令=1，那么状态设置为地址ACK
                    I2C1TRN = i2c_operatcode | 0x01;
                    i2c1_state = S_MASTER_ACK_ADDR; //读操作
                } else {
                    I2C1TRN = i2c_operatcode;
                    i2c1_state = S_MASTER_SEND_DATA; //状态设置为发送数据
                }
            } else if (!i2c_IsResart) {//如果是重启后的操作码，则根据操作码最后一个字节处理；反之,这
                I2C1TRN = i2c_operatcode;
                i2c1_state = S_MASTER_SEND_ADDR_16BIT;
            } else {//就是跟读地址读写数据的后半段
                if (i2c_flag.F_WriteOrRead) {//如果是读指令=1，那么状态设置为地址ACK
                    I2C1TRN = i2c_operatcode | 0x01;
                    i2c1_state = S_MASTER_ACK_ADDR; //读操作                    
                } else {
                    I2C1TRN = i2c_operatcode;
                    i2c1_state = S_MASTER_SEND_DATA; //状态设置为发送数据
                }
            }
            break;
        }
        case S_MASTER_SEND_ADDR_16BIT:
        {
            if (I2C1STATbits.ACKSTAT) {//如果检测到上次NACK
                I2C1STATbits.ACKSTAT = 0; //复位ACK
                I2C1CONbits.PEN = 1; // 发送停止条件 
                IFS1bits.MI2C1IF = 0; //清除标志
                i2c1_state = S_MASTER_IDLE; //状态设置位空闲
            } else {
                if (i2c_flag.F_Is16bitsDevice) {
                    i2c_flag.F_Is16bitsDevice = 0;
                    I2C1TRN = (uint8_t) (i2c_address >> 8); //发送16位高地址 
                    i2c1_state = S_MASTER_SEND_ADDR_16BIT;
                    //                    break;
                } else {
                    I2C1TRN = (uint8_t) (i2c_address & 0x00FF); //发送16位低地址 
                    if (i2c_flag.F_WriteOrRead)//如果是读取指令的话
                    {
                        i2c_IsResart = 1;
                        //                        I2C1CONbits.RSEN = 1; // 发送启动条件
                        i2c_operatcode |= 0x01; //将地址设置为读取
                        i2c1_state = S_MASTER_RESTART;
                    } else
                        i2c1_state = S_MASTER_SEND_DATA;
                }
            }
            break;
        }
        case S_MASTER_SEND_DATA:
        {
            if (I2C1STATbits.ACKSTAT) {//如果检测到上次NACK
                I2C1STATbits.ACKSTAT = 0; //复位ACK
                I2C1CONbits.PEN = 1; // 发送停止条件 
                IFS1bits.MI2C1IF = 0; //清除标志
                i2c1_state = S_MASTER_IDLE; //状态设置位空闲
            } else {
                if (i2c_bytes_left-- == 0U) {//判断数据是否发送完毕
                    I2C1CONbits.PEN = 1; // I2C STOP control bit.   
                    IFS1bits.MI2C1IF = 0; //清除标志
                    i2c1_state = S_MASTER_SEND_STOP; //状态设置为空闲
                } else {
                    I2C1TRN = *pi2c_buf_ptr++; //发送数据
                }
                break;
            }
        }
        case S_MASTER_ACK_ADDR://如果是读操作的话，
        {
            if (I2C1STATbits.ACKSTAT) { //如果上次检测到NACK
                I2C1CONbits.PEN = 1; //启动停止条件
                IFS1bits.MI2C1IF = 0; //清除标志
                i2c1_state = S_MASTER_IDLE;
                I2C1STATbits.ACKSTAT = 0; //复位ACK
            } else {
                I2C1CONbits.RCEN = 1; //启动接受
                i2c1_state = S_MASTER_ACK_RCV_DATA; //状态为设置为接受数据
            }
            break;
        }
        case S_MASTER_RCV_DATA:
        {
            i2c1_state = S_MASTER_ACK_RCV_DATA; //发送接受数据ACK
            I2C1CONbits.RCEN = 1; //使能接收
            break;
        }
        case S_MASTER_ACK_RCV_DATA:
        {
            *pi2c_buf_ptr++ = I2C1RCV; //接收数据
            if (--i2c_bytes_left) {
                I2C1CONbits.ACKDT = 0; //发送ACK
                i2c1_state = S_MASTER_RCV_DATA; //启动接收
            } else {

                // Yes, it's the last byte.  Don't ack it
                // Flag that we will nak the data
                I2C1CONbits.ACKDT = 1; // I2C ACK data control bit.

                //            I2C1_FunctionComplete();
                i2c1_state = S_MASTER_RCV_STOP;
                //                break; //退出接收
            }

            // Initiate the acknowledge
            I2C1CONbits.ACKEN = 1; // I2C 发送ACK .
            break;
        }
        case S_MASTER_RCV_STOP:
        {
            I2C1CONbits.ACKDT = 0;
            I2C1CONbits.PEN = 1; // I2C STOP control bit.   
            //            IFS1bits.MI2C1IF = 0; //清除标志 
            i2c1_state = S_MASTER_Finish;
            break;
        }
        case S_MASTER_SEND_STOP:
        {
            I2C1CONbits.PEN = 1; // I2C STOP control bit.   
            //            IFS1bits.MI2C1IF = 0; //清除标志 
            i2c1_state = S_MASTER_Finish;
            break;
        }
        case S_MASTER_Finish:
        {
            i2c_operatcode = 0;
            pi2c_buf_ptr = NULL;
            i2c_address = 0;
            i2c_bytes_left = 0;
            i2c_flag.F_Is16bitsDevice = i2c_flag.F_IsSelectiveMode = i2c_flag.F_WriteOrRead = 0;
            i2c_IsResart = 0; //设备是否重启
            break;
        }

            //        default:
            //
            //            // This case should not happen, if it does then
            //            // terminate the transfer
            //            //    i2c1_object.i2cErrors++;
            //        {
            //            I2C1CONbits.PEN = 1; // I2C STOP control bit.  
            //            //            IFS1bits.MI2C1IF = 0; //清除标志
            //            //            i2c1_state = S_MASTER_IDLE;
            //            break;
            //        }
    }
    OSIntExit();
}
