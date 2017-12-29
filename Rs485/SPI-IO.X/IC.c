//#include "p24FV32KA301.h"
#include "type.h"
#include "user.h"

//vu32 gPulseCount = 0;

void IC_Configuration(void) {
    //    IC2CON1bits.ICBNE = 0;
    IC2CON2bits.SYNCSEL = 0b00000; //10100 = ���벶׽ 2 ��ͬ��
    IC2CON1bits.ICSIDL = 0; //0 = ���벶׽ģ�齫�� CPU ����ģʽ�¼�������
    IC2CON1bits.IC2TSEL = 0b100; //100 = TIMER1    9.26 111
    IC2CON1bits.ICI = 0; //ÿ�β�׽�¼��ж�һ��
    IC2CON2bits.ICTRIG = 0; //ʹ ICx �� SYNCSELx λָ����Դͬ��
    IC2CON2bits.TRIGSTAT = 1; //��ʱ��Դδ����������������״̬
    IC2BUF = 0;
    IC2TMR = 0;
    IC2CON1bits.ICM = 0b111; //�ж�ģʽ �򵥲�׽ģʽ��ÿ�������ز�׽һ�Σ� 
    IPC1bits.IC2IP = 6; // Setup Input Capture 1 interrupt for desired priority
    // level (this example assigns level 1 priority)
    IFS0bits.IC2IF = 0; // Clear the IC1 interrupt status flag
    IEC0bits.IC2IE = 1; // Enable IC1 interrupts
    S1_IN;
    //    IC2CON1bits.ICBNE = 1;
    //ICI<1:0> λ�����ƴ�ģʽ���жϵĲ���
    //    IC1CON2 = 0x00A4; // Turn on Input Capture 1 Module 
    //    T1CONbits.TON=1;
}


