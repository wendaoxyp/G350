#include "INT.h"

void INT0_Init(void) {
    TRISFbits.TRISF6 = 1; //设置为输入
    INTCON2bits.INT0EP = 1; //  1 = 下降沿中断  0 = 上升沿中断
    IPC0bits.INT0IP = 7; //优先级为2
    IFS0bits.INT0IF = 0; //清除标志位
    IEC0bits.INT0IE = 1; //使能中断
}

void INT0_Open(void) {
    IFS0bits.INT0IF = 0; //清除标志位
    IEC0bits.INT0IE = 1;
}

void INT0_Close(void) {
    IFS0bits.INT0IF = 0; //清除标志位
    IEC0bits.INT0IE = 0;
}

