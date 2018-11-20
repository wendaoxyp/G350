/* 
 * File:   NVIC.c
 * Author: TURONG62
 *
 * Created on 2016年6月6日, 上午8:48
 */

#include "DefType.h"
#include <xc.h>
#include "SerialBuffer.h"
#include "Tasks.h"
#include "TX04.h"
#include "TIM.h"
#include "ublox_g350.h"
#include "UART2.h"
#include "DMA.h"
//#include "DMA_buffer.h"

static inline void GOTO(uint16_t addr) {
    __asm__("goto %0" : : "r"(addr));
}

/*************************************
Function: 外部中断1
Description: 实时时钟PCF的闹钟输入
Input: void 
Output: void
 * Note:c
 *************************************/
void __attribute__((interrupt, no_auto_psv)) _INT1Interrupt(void) {//need to test 8/2
    gExitSleep = 1; //退出睡眠模式
    if (!LDO_EN1_DEC) {//如果是下降延的话，且延时一段时间后还是低电平
        if (gGPRSIsONline) {
            UbloxCloseTCPClient(); //如果模块并且模式是TCP客服端模式，先AT指令关闭成功 先切换cmd模式
            UART2SendString(TX04_SEND_OFF, 7); //发送GPOFF
        }
        GLED = 0; //关闭LED灯
        gGPRSIsONline = 0; //清楚上线标志位
        USER_LK = 0; //LK置低      
        OR_CTRL_PWR = 0; //关闭ublox电源
        CloseUART2(); //关闭串口通讯,避免电流反灌
        do {//如果EN一直是关闭的状态，LED灯一直闪缩，直到电源消耗完毕
            LED_Blink(2, 5); //避免硬件上的重复进入该中断,消耗电容C22电量，EN下线
            if (LDO_EN1_DEC) {//EN再次拉高
                Delay10ms(2);
                if (LDO_EN1_DEC)//EN确定拉高
                    break;
            }
        } while (1); //10应该为放电的时间
        //        gGpch_Arg = 0; //必须加，防止切换中心失败
        CopyDat((uint8_t*) & RunArg, (uint8_t*) & TX04Arg_S, 130); //参数设置为参数一
        INTCON1bits.MATHERR = 1; //产生数学错误中断，复位
    }
    IFS1bits.INT1IF = 0;
}//274ms

/*************************************
Function: 定时器1中断 
Description: 用于在GPRS上线过程中，定时时间
Input: 无 
Output: 无
 *************************************/
void __attribute__((interrupt, no_auto_psv, shadow)) _T1Interrupt(void) {//1s定时
    //#define DeBug_Listen_Time 1
    //#define DeBug_Restart_Time 1
    gT1Count2++; //心跳时间和重启时间   
    if (gGPRSIsONline) {//模块上线以后
        if (RunArg.HeartTime && (RunArg.WorkMode != 0x31)) {//心跳包仅仅使用与TCP UDP客服端模式
            gT1Count_Heart++;
            if (!(gT1Count_Heart % RunArg.HeartTime)) {
                gT1Count_Heart = 0;
                gExitSleep = 1; //唤醒设备
                if ((gTX04Sta == TX04_Sta_TCP_Cop)) {//如果是TCP协议
                    UART1SendString(TX04_HEARTBEAT, 11);
                } else if ((gTX04Sta == TX04_Sta_UDP_Cop)) {//如果是UDP协议
                    UDPWriteStrByCmd(TX04_HEARTBEAT, 11);
                }
            }
        }
        if (RunArg.ListenTime && (RunArg.CSMode == 0x31)&&(RunArg.TCP_UDP == 0x30)) {//如果是服务端模式，且listen time ！=0 
            gT1Count_Listen++;
            if (RunArg.ListenTime <= gT1Count_Listen) {
                gExitSleep = 1; //唤醒设备
                //UbloxCloseTCPClient();
                gGPRSIsONline = 0;
#ifdef DeBug_Listen_Time
                DeBug_PrintInfo("\r\nIt's listen time over!!!\r\n");
#endif 
                ClearT1ArgCnt();
            }
        }
    }
    if (RunArg.RestartTime) {//重启时间不为0
        gT1Count_Reset++; //重启时间计算时间+1
        if (RunArg.RestartTime * 60 <= gT1Count_Reset) {
            gExitSleep = 1; //唤醒设备
            UbloxCloseTCPClient();
            if (gGPRSIsONline) {
                gGPRSIsONline = 0;
                UART2SendString(TX04_SEND_OFF, 7);
            }
#ifdef DeBug_Restart_Time
            DeBug_PrintInfo("\r\nIt's restart time over!!!\r\n");
#endif
            ClearT1ArgCnt();
        }
    } //计算报警时间任务 采集任务T3  
    IFS0bits.T1IF = 0; //Reset Timer1 interrupt flag and Return from ISR
}

/*************************************
Function: 定时器2中断 
Description:用于空闲模式下计数，判断指令  进入休眠定时
Input: 无 
Output: 无
 *************************************/
void __attribute__((__interrupt__, __auto_psv__, __shadow__)) _T2Interrupt(void) {
    gT2flag = 1;
    IFS0bits.T2IF = 0;
}

/*************************************
Function: UART1接收中断
Description: 485通讯
Input: 无 
Output: 无
 *************************************/
void __attribute__((interrupt, auto_psv)) _U1RXInterrupt(void) {
    uint8_t cnt = 0;
    for (cnt = 0; cnt < 4; cnt++)
        if (U1STAbits.URXDA) //没有接收到
            BufferWrite_UART1();
    //    if (TX04IsSleepSta())//如果是睡眠模式 唤醒设备
    gExitSleep = 1; //唤醒设备
    IFS0bits.U1RXIF = 0;
}

//void __attribute__((interrupt, no_auto_psv)) _U1TXInterrupt(void) {
//    //    static uint16_t cnt = 0;
//    if (!UART1_W_BUF_BYTE)
//        IEC0bits.U1TXIE = 0; //开启接受中断
//    while (!(U1STAbits.UTXBF == 1)) {
//        //        else {
//        U1TXREG = *UART1_W_BUF;
//        UART1_W_BUF++;
//        UART1_W_BUF_BYTE--;
//        if (!UART1_W_BUF_BYTE)
//            break;
//    }
//    //    while (!U1STAbits.TRMT);
//    //        if (UART1_W_BUF_BYTE)
//    //            break;
//    //}
//    IFS0bits.U1TXIF = False;
//}

/*************************************
Function: UART2接收中断
Description: GPRS通讯
Input: 无 
Output: 无
 *************************************/
void __attribute__((interrupt, auto_psv)) _U2RXInterrupt(void) {
    uint8_t cnt = 0;
    for (cnt = 0; cnt < 4; cnt++)
        if (U2STAbits.URXDA) //没有接收到
            BufferWrite_UART2();
    gExitSleep = 1; //唤醒设备
    IFS1bits.U2RXIF = 0;
}

///*************************************
//Function: UART1错误终端
//Description: 无
//Input: 无 
//Output: 无
// *************************************/

void __attribute__((interrupt, no_auto_psv)) _U1ErrInterrupt(void) {
    //    OSIntEnter();
    if (U1STAbits.OERR) {
        BufferWrite_UART1();
        U1STAbits.OERR = 0;
        //        DeBug_PrintInfo("U1 OEER!!!\r\n");
    }
    if (U1STAbits.FERR) {
        BufferWrite_UART1();
        U1STAbits.FERR = 0;
        //        DeBug_PrintInfo("U1 FEER!!!\r\n");
    }
    if (U1STAbits.PERR) {
        U1STAbits.PERR = 0;
        //        DeBug_PrintInfo("U1 PEER!!!\r\n");
    }
    IFS4bits.U1ERIF = 0;
}

/*************************************
Function: UART2错误中断
Description: 无
Input: 无 
Output: 无
 *************************************/
void __attribute__((interrupt, no_auto_psv)) _U2ErrInterrupt(void) {
    //    OSIntEnter();
    if (U2STAbits.OERR) {
        BufferWrite_UART2();
        U2STAbits.OERR = 0;
        //        DeBug_PrintInfo("U2 OEER!!!\r\n");
    }
    if (U2STAbits.FERR) {
        BufferWrite_UART2();
        U2STAbits.FERR = 0;
        //        DeBug_PrintInfo("U2 FEER!!!\r\n");
    }
    if (U2STAbits.PERR) {
        U1STAbits.PERR = 0;
        //        DeBug_PrintInfo("U2 PEER!!!\r\n");
    }
    IFS4bits.U2ERIF = 0;
}

/*************************************
Function: _DMA0Interrupt
Description: DMA0传输UART1
Input: 无 
Output: 无
 *************************************/
//void __attribute__((interrupt, no_auto_psv, shadow)) _DMA0Interrupt(void) {
//    if (DMAINT0bits.HIGHIF) {//超出高地址中断标志
//        DMAINT0bits.HIGHIF = 0;
//        DMADST0 = DMA0_UART1_START;
//    }
//    BufferWrite_DMA0();
//    IFS0bits.DMA0IF = 0;
//}

/*************************************
Function: _DMA1Interrupt
Description: DMA1传输UART2
Input: 无 
Output: 无
 *************************************/
//void __attribute__((interrupt, no_auto_psv, shadow)) _DMA1Interrupt(void) {
//    if (DMAINT1bits.HIGHIF) {//超出高地址中断标志
//        DMAINT1bits.HIGHIF = 0;
//        DMADST1 = DMA1_UART2_START;
//    }
//    BufferWrite_DMA1();
//    IFS0bits.DMA1IF = 0;
//}

/*************************************
Function: 默认中断
Description: 无
Input: 无 
Output: 无
 *************************************/
//void __attribute__((interrupt, no_auto_psv)) _DefaultInterrupt(void) {
//    if (INTCON1bits.STKERR) {
//        UART2SendString((uint8_t*) "DeaultInterrup stkerr!!!\r\n", 26);
//        INTCON1bits.STKERR = 0;
//    }
//    if (INTCON1bits.ADDRERR) {
//        UART2SendString((uint8_t*) "DeaultInterrup addrerr!!!\r\n", 26);
//        INTCON1bits.ADDRERR = 0; //err1
//    }
//    if (INTCON1bits.MATHERR) {
//        UART2SendString((uint8_t*) "DeaultInterrup matherr!!!\r\n", 26);
//        INTCON1bits.MATHERR = 0;
//    }
//    GOTO(0); //自动复位
//}

void __attribute__((interrupt, no_auto_psv)) _OscillatorFail(void) {
    _OSCFAIL = 0; //触摸谐振电容导致复位
}

void __attribute__((interrupt, no_auto_psv)) _AddressError(void) {
    _ADDRERR = 0;
}

