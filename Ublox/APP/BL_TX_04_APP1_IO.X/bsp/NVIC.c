/* 
 * File:   NVIC.c
 * Author: TURONG62
 *
 * Created on 2016��6��6��, ����8:48
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
Function: �ⲿ�ж�1
Description: ʵʱʱ��PCF����������
Input: void 
Output: void
 * Note:c
 *************************************/
void __attribute__((interrupt, no_auto_psv)) _INT1Interrupt(void) {//need to test 8/2
    gExitSleep = 1; //�˳�˯��ģʽ
    if (!LDO_EN1_DEC) {//������½��ӵĻ�������ʱһ��ʱ����ǵ͵�ƽ
        if (gGPRSIsONline) {
            UbloxCloseTCPClient(); //���ģ�鲢��ģʽ��TCP�ͷ���ģʽ����ATָ��رճɹ� ���л�cmdģʽ
            UART2SendString(TX04_SEND_OFF, 7); //����GPOFF
        }
        GLED = 0; //�ر�LED��
        gGPRSIsONline = 0; //������߱�־λ
        USER_LK = 0; //LK�õ�      
        OR_CTRL_PWR = 0; //�ر�ublox��Դ
        CloseUART2(); //�رմ���ͨѶ,�����������
        do {//���ENһֱ�ǹرյ�״̬��LED��һֱ������ֱ����Դ�������
            LED_Blink(2, 5); //����Ӳ���ϵ��ظ�������ж�,���ĵ���C22������EN����
            if (LDO_EN1_DEC) {//EN�ٴ�����
                Delay10ms(2);
                if (LDO_EN1_DEC)//ENȷ������
                    break;
            }
        } while (1); //10Ӧ��Ϊ�ŵ��ʱ��
        //        gGpch_Arg = 0; //����ӣ���ֹ�л�����ʧ��
        CopyDat((uint8_t*) & RunArg, (uint8_t*) & TX04Arg_S, 130); //��������Ϊ����һ
        INTCON1bits.MATHERR = 1; //������ѧ�����жϣ���λ
    }
    IFS1bits.INT1IF = 0;
}//274ms

/*************************************
Function: ��ʱ��1�ж� 
Description: ������GPRS���߹����У���ʱʱ��
Input: �� 
Output: ��
 *************************************/
void __attribute__((interrupt, no_auto_psv, shadow)) _T1Interrupt(void) {//1s��ʱ
    //#define DeBug_Listen_Time 1
    //#define DeBug_Restart_Time 1
    gT1Count2++; //����ʱ�������ʱ��   
    if (gGPRSIsONline) {//ģ�������Ժ�
        if (RunArg.HeartTime && (RunArg.WorkMode != 0x31)) {//����������ʹ����TCP UDP�ͷ���ģʽ
            gT1Count_Heart++;
            if (!(gT1Count_Heart % RunArg.HeartTime)) {
                gT1Count_Heart = 0;
                gExitSleep = 1; //�����豸
                if ((gTX04Sta == TX04_Sta_TCP_Cop)) {//�����TCPЭ��
                    UART1SendString(TX04_HEARTBEAT, 11);
                } else if ((gTX04Sta == TX04_Sta_UDP_Cop)) {//�����UDPЭ��
                    UDPWriteStrByCmd(TX04_HEARTBEAT, 11);
                }
            }
        }
        if (RunArg.ListenTime && (RunArg.CSMode == 0x31)&&(RunArg.TCP_UDP == 0x30)) {//����Ƿ����ģʽ����listen time ��=0 
            gT1Count_Listen++;
            if (RunArg.ListenTime <= gT1Count_Listen) {
                gExitSleep = 1; //�����豸
                //UbloxCloseTCPClient();
                gGPRSIsONline = 0;
#ifdef DeBug_Listen_Time
                DeBug_PrintInfo("\r\nIt's listen time over!!!\r\n");
#endif 
                ClearT1ArgCnt();
            }
        }
    }
    if (RunArg.RestartTime) {//����ʱ�䲻Ϊ0
        gT1Count_Reset++; //����ʱ�����ʱ��+1
        if (RunArg.RestartTime * 60 <= gT1Count_Reset) {
            gExitSleep = 1; //�����豸
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
    } //���㱨��ʱ������ �ɼ�����T3  
    IFS0bits.T1IF = 0; //Reset Timer1 interrupt flag and Return from ISR
}

/*************************************
Function: ��ʱ��2�ж� 
Description:���ڿ���ģʽ�¼������ж�ָ��  �������߶�ʱ
Input: �� 
Output: ��
 *************************************/
void __attribute__((__interrupt__, __auto_psv__, __shadow__)) _T2Interrupt(void) {
    gT2flag = 1;
    IFS0bits.T2IF = 0;
}

/*************************************
Function: UART1�����ж�
Description: 485ͨѶ
Input: �� 
Output: ��
 *************************************/
void __attribute__((interrupt, auto_psv)) _U1RXInterrupt(void) {
    uint8_t cnt = 0;
    for (cnt = 0; cnt < 4; cnt++)
        if (U1STAbits.URXDA) //û�н��յ�
            BufferWrite_UART1();
    //    if (TX04IsSleepSta())//�����˯��ģʽ �����豸
    gExitSleep = 1; //�����豸
    IFS0bits.U1RXIF = 0;
}

//void __attribute__((interrupt, no_auto_psv)) _U1TXInterrupt(void) {
//    //    static uint16_t cnt = 0;
//    if (!UART1_W_BUF_BYTE)
//        IEC0bits.U1TXIE = 0; //���������ж�
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
Function: UART2�����ж�
Description: GPRSͨѶ
Input: �� 
Output: ��
 *************************************/
void __attribute__((interrupt, auto_psv)) _U2RXInterrupt(void) {
    uint8_t cnt = 0;
    for (cnt = 0; cnt < 4; cnt++)
        if (U2STAbits.URXDA) //û�н��յ�
            BufferWrite_UART2();
    gExitSleep = 1; //�����豸
    IFS1bits.U2RXIF = 0;
}

///*************************************
//Function: UART1�����ն�
//Description: ��
//Input: �� 
//Output: ��
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
Function: UART2�����ж�
Description: ��
Input: �� 
Output: ��
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
Description: DMA0����UART1
Input: �� 
Output: ��
 *************************************/
//void __attribute__((interrupt, no_auto_psv, shadow)) _DMA0Interrupt(void) {
//    if (DMAINT0bits.HIGHIF) {//�����ߵ�ַ�жϱ�־
//        DMAINT0bits.HIGHIF = 0;
//        DMADST0 = DMA0_UART1_START;
//    }
//    BufferWrite_DMA0();
//    IFS0bits.DMA0IF = 0;
//}

/*************************************
Function: _DMA1Interrupt
Description: DMA1����UART2
Input: �� 
Output: ��
 *************************************/
//void __attribute__((interrupt, no_auto_psv, shadow)) _DMA1Interrupt(void) {
//    if (DMAINT1bits.HIGHIF) {//�����ߵ�ַ�жϱ�־
//        DMAINT1bits.HIGHIF = 0;
//        DMADST1 = DMA1_UART2_START;
//    }
//    BufferWrite_DMA1();
//    IFS0bits.DMA1IF = 0;
//}

/*************************************
Function: Ĭ���ж�
Description: ��
Input: �� 
Output: ��
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
//    GOTO(0); //�Զ���λ
//}

void __attribute__((interrupt, no_auto_psv)) _OscillatorFail(void) {
    _OSCFAIL = 0; //����г����ݵ��¸�λ
}

void __attribute__((interrupt, no_auto_psv)) _AddressError(void) {
    _ADDRERR = 0;
}

