/* 
 * File:   NVIC.c
 * Author: TURONG62
 *
 * Created on 2016��6��6��, ����8:48
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
//Function: �����ж� 
//Description: ��ʱ�����豸������ʱ�����
//Input: �� 
//Output: ��
// *************************************/
//void __attribute__((__interrupt__, __auto_psv__)) _RTCCInterrupt(void) {
//    OSCChange(0x00);
//    gTimeCount.timeAlarm++; //��λΪ����
//    gTimeCount.timeGprs++;
//    gTimeCount.timeMp++;
//
//    if ((gTimeCount.timeMp >= miotArgs.timemp - SettingSampleTime)&&(!FLagArgbits.PulseTimeFlag)) {//������ʱ��1���вɼ����Ȳɼ�������6����
//        FLagArgbits.T1CountFlag = 1;
//        T1CONbits.TON = 1;
//    }
//
//    if (gTimeCount.timeMp >= miotArgs.timemp) {//�ɼ����ݣ���д��FRAM
//        gTimeCount.timeMp = 0;
//        FLagArgbits.PulseTimeFlag = 0;
//        FLagArgbits.T1CountFlag = 0; //����û�л�ȡ������ʱ���ʱ��Ҳ�رն�ʱ��
//        T1CONbits.TON = 0; //�رն�ʱ��1
//        StartTime4();
//        IFS1bits.T4IF = 1; //T4CONbits.TON = 1;���붨ʱ����ʼ�ɼ�
//    }
//
//    if (gTimeCount.timeGprs >= miotArgs.timegprs) {//GPRS�ϴ�
//        gTimeCount.timeGprs = 0;
//        FLagArgbits.tgprsFlag = 1;
//    }
//
//    //    FLagArgbits.LowPowerFlag = !BAT_DEC; //��ÿ���ȡ����
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
//    IFS3bits.RTCIF = 0; //clear RTC��־λ      
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
Function: �ⲿ�ն�0
Description: ��ѹ���
Input: �� 
Output: ��
 *************************************/
void __attribute__((interrupt, no_auto_psv))_ISR _INT0Interrupt(void) {
    //    OSIntEnter();
    IFS0bits.INT0IF = 0;
    //    OSIntExit();
    //    OSSemPost(sem_receive_pressure);
}
/*************************************
Function: ��ʱ���ж� 
Description: ������GPRS���߹����У���ʱʱ��
Input: �� 
Output: ��
 *************************************/
//void __attribute__((__interrupt__, __auto_psv__, __shadow__)) _T3Interrupt(void) {
//    gT3Count++;
//    IFS0bits.T3IF = 0; //Reset Timer1 interrupt flag and Return from ISR
//}

/*************************************
Function: ��ʱ���ж� 
Description: ����485ͨѶ��ʱ����ʱ
Input: �� 
Output: ��
 *************************************/
//void __attribute__((__interrupt__, __auto_psv__, __shadow__)) _T2Interrupt(void) {
//    while (!U1STAbits.RIDLE);
//    PC_Cop();
//    T2CONbits.TON = 0;
//    TMR2 = 0;
//    FLagArgbits.TestFlag = 0; //�˳�����ģʽ
//    IFS0bits.T2IF = 0; //Reset Timer1 interrupt flag and Return from ISR
//}

/*************************************
Function: ��ʱ���ж� 
Description: ���ڼ���˲����
Input: �� 
Output: ��
 *************************************/
//void __attribute__((__interrupt__, __auto_psv__, __shadow__)) _T1Interrupt(void) {
//    gT1Count++;
//    IFS0bits.T1IF = 0; //Reset Timer1 interrupt flag and Return from ISR
//}

/*************************************
Function: ��ʱ��t4�ж� 
Description: ���ڲɼ����ݵ�����
Input: �� 
Output: ��
 *************************************/
//void __attribute__((__interrupt__, __auto_psv__, __shadow__)) _T4Interrupt(void) {
//    if (FLagArgbits.LowPowerGetDataFlag) {
//        FLagArgbits.LowPowerGetDataFlag = 0;
//        GetValueTask(LowPowerData); //��ȡ����ʱ�Ǳ��ͨѶ����
//    } else if (FLagArgbits.TestGetDataFlag) {
//        FLagArgbits.TestGetDataFlag = 0;
//        GetValueTask(TestData); //��ȡ����ʱ�Ǳ��ͨѶ����
//    } else
//        GetValueTask(SampleData); //��ȡ�Ǳ��ͨѶ����
//    FM25L64B_Write(BOR_Pulse, (u8*) (&gPulseCount), 4); //������������
//
//    IFS1bits.T4IF = 0; //Reset Timer1 interrupt flag and Return from ISR 
//    CloseTime4();
//}

/*************************************
Function: ��ƽ�仯�ж� 
Description: ��ȡ���������
Input: �� 
Output: ��
 *************************************/
//void __attribute__((__interrupt__, __auto_psv__)) _CNInterrupt(void) { //���Ѹ������
//    if (S1) {//ͨ���ڶ���������ȡ����
//        gPulseCount++; //������+1
//        if (FLagArgbits.T1CountFlag && FLagArgbits.T1CountLastFlag) {//�������T1��ʱ�������ǵڶ��ν��룬��ɼ�����
//            gPulseTime = gT1Count * 1000 + (((u32) TMR1) * 1000 >> 15) + 100; //��λms
//            if (gPulseTime < 2000)//�ɼ�ʱ��С��2s
//                gPulseTime = 0;
//            else {
//                FLagArgbits.PulseTimeFlag = 1; // ����Ѿ���ȡ������ʱ�䣬��ô��Ҫ�رն�ʱ��
//                FLagArgbits.T1CountFlag = 0;
//                T1CONbits.TON = 0;
//            }
//        }
//        TMR1 = 0;
//        gT1Count = 0;
//        FLagArgbits.T1CountLastFlag = FLagArgbits.T1CountFlag; //ͨ�������أ��ر�FLagArgbits.T1CountLastFlag
//    }
//    IFS1bits.CNIF = 0;
//}

///*************************************
//Function: UART1�����ж�
//Description: 485ͨѶ
//Input: �� 
//Output: ��
// *************************************/
//void __attribute__((__interrupt__, __auto_psv__)) _U1RXInterrupt(void) {
//    //    OSIntEnter();
//    uint8_t cnt = 0;
//    for (cnt = 0; cnt < 4; cnt++)
//        if (U1STAbits.URXDA == 1) //û�н��յ�
//            BufferWrite_UART1();
//    IFS0bits.U1RXIF = 0;
//    //    OSIntExit();
//}

/*************************************
Function: UART2�����ж�
Description: GPRSͨѶ
Input: �� 
Output: ��
 *************************************/
void __attribute__((__interrupt__, __auto_psv__)) _U2RXInterrupt(void) {
    //    OSIntEnter();
    uint8_t cnt = 0;
    for (cnt = 0; cnt < 4; cnt++)
        if (U2STAbits.URXDA == 1) //û�н��յ�        
            BufferWrite_UART2();
    IFS1bits.U2RXIF = 0;
    //    OSIntExit();
}

///*************************************
//Function: UART2�����ж�
//Description: GPRSͨѶ
//Input: �� 
//Output: ��
// *************************************/
//void __attribute__((__interrupt__, __auto_psv__)) _U3RXInterrupt(void) {
//    OSIntEnter();
//    uint8_t cnt = 0;
//    for (cnt = 0; cnt < 4; cnt++)
//        if (U3STAbits.URXDA == 1) //û�н��յ�        
//            BufferWrite_UART3();
//    IFS5bits.U3RXIF = 0;
//    OSIntExit();
//}

/*************************************
Function: UART2�����ж�
Description: GPRSͨѶ
Input: �� 
Output: ��
 *************************************/
//void __attribute__((interrupt, no_auto_psv)) _U2TXInterrupt(void) {
//    u8 cnt = 0;
//    while ((cnt < UART2Argbits.bytes2) && (!(U2STAbits.UTXBF == 1))) {
//        U2TXREG = *(UART2Argbits.dat2 + cnt); //��������
//
//        while (!U2STAbits.TRMT);
//        cnt++;
//    }
//    IFS1bits.U2TXIF = 0;
//}

///*************************************
//Function: UART1�����ն�
//Description: ��
//Input: �� 
//Output: ��
// *************************************/
//void __attribute__((interrupt, no_auto_psv)) _U1ErrInterrupt(void) {
//    OSIntEnter();
//    if (U1STAbits.OERR == 1)
//        U1STAbits.OERR = 0;
//    IFS4bits.U1ERIF = 0;
//    OSIntExit();
//}

/*************************************
Function: UART2�����ж�
Description: ��
Input: �� 
Output: ��
 *************************************/
void __attribute__((interrupt, no_auto_psv)) _U2ErrInterrupt(void) {
    //    OSIntEnter();
    if (U2STAbits.OERR)
        U2STAbits.OERR = 0;
    if (U2STAbits.FERR)
        if (U2STAbits.URXDA == 1) //û�н��յ�        
            BufferWrite_UART2();
    IFS4bits.U2ERIF = 0;
    //    OSIntExit();
}

/*************************************
Function: Ĭ���ж�
Description: ��
Input: �� 
Output: ��
 *************************************/
void __attribute__((interrupt, no_auto_psv)) _DefaultInterrupt(void) {
    if (INTCON1bits.STKERR)INTCON1bits.STKERR = 0;
    if (INTCON1bits.ADDRERR)INTCON1bits.ADDRERR = 0;
    if (INTCON1bits.MATHERR)INTCON1bits.MATHERR = 0;
    asm("GOTO __reset");
}


