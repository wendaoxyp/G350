/* 
 * File:   NVIC.c
 * Author: TURONG62
 *
 * Created on 2016��6��6��, ����8:48
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
//u8 gLastPulseSta = 0; //��¼���������
//u32 gLastTCount = 0; //��¼T1���һ������
u8 gGPRS_Fail_Count = 0; //��GPRS�ϴ�ʧ�ܼ���
float gGetVoltage = 0; //��ȡ��ѹֵ
//u8 gTM2CNT = 0;

/*************************************
Function: �����ж� 
Description: ��ʱ�����豸������ʱ�����
Input: �� 
Output: ��
 *************************************/
void __attribute__((__interrupt__, __auto_psv__)) _RTCCInterrupt(void) {
    OSCChange(0x00);
    gTimeCount.timeAlarm++; //��λΪ����
    gTimeCount.timeGprs++;
    gTimeCount.timeMp++;

    //    if ((gTimeCount.timeMp >= miotArgs.timemp - SettingSampleTime)&&(!FLagArgbits.PulseTimeFlag)) {//������ʱ��1���вɼ����Ȳɼ�������6����
    //        FLagArgbits.T1CountFlag = 1;
    //        T1CONbits.TON = 1;
    //    }

    if (gTimeCount.timeMp >= miotArgs.timemp) {//�ɼ����ݣ���д��FRAM
        gTimeCount.timeMp = 0;
        //        FLagArgbits.PulseTimeFlag = 0;
        //        FLagArgbits.T1CountFlag = 0; //����û�л�ȡ������ʱ���ʱ��Ҳ�رն�ʱ��
        T1CONbits.TON = 0; //�رն�ʱ��1
        StartTime4();
        IFS1bits.T4IF = 1; //T4CONbits.TON = 1;���붨ʱ����ʼ�ɼ�
        //        if (FLagArgbits.LowPowerGetDataFlag || FLagArgbits.TestGetDataFlag)
        //            CloseTime4();
    }

    if (gTimeCount.timeGprs >= miotArgs.timegprs) {//GPRS�ϴ�
        gTimeCount.timeGprs = 0;
        FLagArgbits.tgprsFlag = 1;
    }

    if (!(FLagArgbits.tgprsFlag || FLagArgbits.LowPoweralarmFlag || FLagArgbits.TestOnlieFlag)) {//���߹����в����е�ѹ�ɼ�
        GetMuilVoltage(&gGetVoltage); //�ɼ���ѹֵ
        //�����ж��Ƿ�Ҫ���е�ѹ������A*(C*D+/B*/C)
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
    IFS3bits.RTCIF = 0; //clear RTC��־λ      
}

/*************************************
Function: ��ʱ���ж� 
Description: ���ڼ���˲����
Input: �� 
Output: ��
 *************************************/
//void __attribute__((__interrupt__, __auto_psv__, __shadow__)) _T1Interrupt(void) {
//
//    gT1Count++;
//    IFS0bits.T1IF = 0; //Reset Timer1 interrupt flag and Return from ISR
//}

/*************************************
Function: ��ʱ���ж� 
Description: ����485ͨѶ��ʱ����ʱ
Input: �� 
Output: ��
 *************************************/

void __attribute__((__interrupt__, __auto_psv__, __shadow__)) _T2Interrupt(void) {

    while (!U1STAbits.RIDLE);
    PC_Cop();
    T2CONbits.TON = 0;
    TMR2 = 0;
    FLagArgbits.TestFlag = 0; //�˳�����ģʽ
    IFS0bits.T2IF = 0; //Reset Timer1 interrupt flag and Return from ISR
}

/*************************************
Function: ��ʱ���ж� 
Description: ������GPRS���߹����У���ʱʱ��
Input: �� 
Output: ��
 *************************************/
void __attribute__((__interrupt__, __auto_psv__, __shadow__)) _T3Interrupt(void) {

    gT3Count++;
    IFS0bits.T3IF = 0; //Reset Timer1 interrupt flag and Return from ISR
}

/*************************************
Function: ��ʱ��t4�ж� 
Description: ���ڲɼ����ݵ�����
Input: �� 
Output: ��
 *************************************/
void __attribute__((__interrupt__, __auto_psv__, __shadow__)) _T4Interrupt(void) {
    if (FLagArgbits.LowPowerGetDataFlag) {
        GetValueTask(LowPowerData);
        FLagArgbits.LowPowerGetDataFlag = 0; //) ? false : true; //��ȡ����ʱ�Ǳ��ͨѶ����        
    } else if (FLagArgbits.AlarmGetDataFlag) {
        GetValueTask(AlarmData);
        FLagArgbits.AlarmGetDataFlag = 0; //��ȡ����ʱ�Ǳ��ͨѶ����     
    } else if (FLagArgbits.TestGetDataFlag) {
        Delay1s(1); //��ʱ1s������λ����ȡ����
        GetValueTask(TestData);
        FLagArgbits.TestGetDataFlag = 0; //  ? false : true; //��ȡ����ʱ�Ǳ��ͨѶ����
    } else
        GetValueTask(SampleData); //��ȡ�Ǳ��ͨѶ����
    //    FM25L64B_Write(BOR_Pulse, (u8*) (&gPulseCount), 4); //������������
    IFS1bits.T4IF = 0; //Reset Timer1 interrupt flag and Return from ISR 
    CloseTime4(); //�ദ����ʹ�ø�ȫ�ֱ���
}

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
//
////                FLagArgbits.PulseTimeFlag = 1; // ����Ѿ���ȡ������ʱ�䣬��ô��Ҫ�رն�ʱ��
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

/*************************************
Function: UART1�����ж�
Description: 485ͨѶ
Input: �� 
Output: ��
 *************************************/
void __attribute__((__interrupt__, __auto_psv__)) _U1RXInterrupt(void) {
    //    GPRS_ON;
    //    OSCChange(0x00); //����Ƶ�л�����
    //    GPRS_OFF;
    u8 cnt = 0;
    for (cnt = 0; cnt < 4; cnt++)

        if (U1STAbits.URXDA == 1) //û�н��յ�
            BufferWrite_UART1();
    //    IEC0bits.T2IE = 1;T2CONbits.TON = 1;
    IFS0bits.U1RXIF = 0;
}

/*************************************
Function: UART2�����ж�
Description: GPRSͨѶ
Input: �� 
Output: ��
 *************************************/
void __attribute__((__interrupt__, __auto_psv__)) _U2RXInterrupt(void) {
    u8 cnt = 0;
    for (cnt = 0; cnt < 4; cnt++)

        if (U2STAbits.URXDA == 1) //û�н��յ�        
            BufferWrite_UART2();
    IFS1bits.U2RXIF = 0;
}

/*************************************
Function: UART2�����ж�
Description: GPRSͨѶ
Input: �� 
Output: ��
 *************************************/
void __attribute__((interrupt, no_auto_psv)) _U2TXInterrupt(void) {
    u8 cnt = 0;
    while ((cnt < UART2Argbits.bytes2) && (!(U2STAbits.UTXBF == 1))) {
        U2TXREG = *(UART2Argbits.dat2 + cnt); //��������

        while (!U2STAbits.TRMT);
        cnt++;
    }
    IFS1bits.U2TXIF = 0;
}

/*************************************
Function: UART1�����ն�
Description: ��
Input: �� 
Output: ��
 *************************************/
void __attribute__((interrupt, no_auto_psv)) _U1ErrInterrupt(void) {
    if (U1STAbits.OERR == 1)
        U1STAbits.OERR = 0;
    IFS4bits.U1ERIF = 0;
}

/*************************************
Function: UART2�����ж�
Description: ��
Input: �� 
Output: ��
 *************************************/
void __attribute__((interrupt, no_auto_psv)) _U2ErrInterrupt(void) {
    if (U2STAbits.OERR == 1)
        U2STAbits.OERR = 0;
    IFS4bits.U2ERIF = 0;
}

/*************************************
Function: �ⲿ�ն�1
Description: ��ص�ѹ���
Input: �� 
Output: ��
 *************************************/
void __attribute__((interrupt, no_auto_psv)) _INT1Interrupt(void) {

    OSCChange(0x00); //����Ƶ�л�����
    OpenRS485(); //����485ͨѶ
    FLagArgbits.TestFlag = 1; //�������ģʽ
    T2CONbits.TON = 1; //������ʱ��2�����������
    //    IEC1bits.INT1IE = 0;
    //    while (!IFS0bits.T2IF) T2CONbits.TON = 1; //������ʱ��2�����������
    IFS1bits.INT1IF = 0;
}

/*************************************
Function: Ĭ���ն�
Description: ��
Input: �� 
Output: ��
 *************************************/
void __attribute__((interrupt, no_auto_psv)) _DefaultInterrupt(void) {
    u8 rtcc_time[7] = {0, 0, 0};
    RTCReadTime(rtcc_time);
    Register2Write(rtcc_time, REG2_Arg_Postion[reg2_mi_year], 7);

    SaveMiotArg();
    //    FM25L64B_Write(BOR_Pulse, (u8*) (&gPulseCount), 4); //������������
    //    RTCReadTime(tmp); //��ȡ����ʱ��
    //    FM25L64B_Write(RST_Data, (u8*) & RCON, 2); //����ʱ��
    //    FM25L64B_Write(RST_Data + 2, (u8*) & IFS0, 2); //����ʱ��
    //    FM25L64B_Write(RST_Data + 4, (u8*) & IFS1, 2); //����ʱ��
    //    FM25L64B_Write(RST_Data + 6, (u8*) & IFS2, 2); //����ʱ��
    //    FM25L64B_Write(RST_Data + 8, (u8*) & IFS3, 2); //����ʱ��
    //    FM25L64B_Write(RST_Data + 10, (u8*) & IFS4, 2); //����ʱ��
    //    FM25L64B_Write(RST_Data + 12, (u8*) & IFS5, 2); //����ʱ��
    //    FM25L64B_Write(RST_Data + 14, (u8*) & IPC0, 2); //����ʱ��
    //    FM25L64B_Write(RST_Data + 16, (u8*) & IPC1, 2); //����ʱ��
    //    FM25L64B_Write(RST_Data + 18, (u8*) & IPC2, 2); //����ʱ��
    //    FM25L64B_Write(RST_Data + 20, (u8*) & IPC3, 2); //����ʱ��
    //    FM25L64B_Write(RST_Data + 22, (u8*) & IPC4, 2); //����ʱ��
    //    FM25L64B_Write(RST_Data + 24, (u8*) & IPC5, 2); //����ʱ��
    //    FM25L64B_Write(RST_Data + 26, (u8*) & IPC6, 2); //����ʱ��
    //    FM25L64B_Write(RST_Data + 28, (u8*) & IPC7, 2); //����ʱ��
    //    FM25L64B_Write(RST_Data + 30, (u8*) & IPC8, 2); //����ʱ��
    //    FM25L64B_Write(RST_Data + 32, (u8*) & IPC9, 2); //����ʱ��
    //    FM25L64B_Write(RST_Data + 34, (u8*) & IPC12, 2); //����ʱ��
    //    FM25L64B_Write(RST_Data + 36, (u8*) & IPC15, 2); //����ʱ��
    //    FM25L64B_Write(RST_Data + 38, (u8*) & IPC16, 2); //����ʱ��
    //    FM25L64B_Write(RST_Data + 40, (u8*) & IEC0, 2); //����ʱ��
    //    FM25L64B_Write(RST_Data + 42, (u8*) & IEC1, 2); //����ʱ��
    //    FM25L64B_Write(RST_Data + 44, (u8*) & IEC2, 2); //����ʱ��
    //    FM25L64B_Write(RST_Data + 46, (u8*) & IEC3, 2); //����ʱ��
    //    FM25L64B_Write(RST_Data + 48, (u8*) & IEC4, 2); //����ʱ��
    //    FM25L64B_Write(RST_Data + 50, (u8*) & IEC5, 2); //����ʱ��
    //    FM25L64B_Write(RST_Data+14, tmp, 2); //����ʱ��
    if (INTCON1bits.STKERR)INTCON1bits.STKERR = 0;
    if (INTCON1bits.ADDRERR)INTCON1bits.ADDRERR = 0;

    if (INTCON1bits.MATHERR)INTCON1bits.MATHERR = 0;
    Reset();
}



