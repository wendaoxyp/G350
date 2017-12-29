#include "INT.h"

void INT0_Init(void) {
    TRISFbits.TRISF6 = 1; //����Ϊ����
    INTCON2bits.INT0EP = 1; //  1 = �½����ж�  0 = �������ж�
    IPC0bits.INT0IP = 7; //���ȼ�Ϊ2
    IFS0bits.INT0IF = 0; //�����־λ
    IEC0bits.INT0IE = 1; //ʹ���ж�
}

void INT0_Open(void) {
    IFS0bits.INT0IF = 0; //�����־λ
    IEC0bits.INT0IE = 1;
}

void INT0_Close(void) {
    IFS0bits.INT0IF = 0; //�����־λ
    IEC0bits.INT0IE = 0;
}

