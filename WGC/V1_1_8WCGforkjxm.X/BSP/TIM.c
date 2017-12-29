#include <TIM.h>
//用于显示LCD

void TMR1_Initialize(void) {
    //TSIDL disabled; TGATE disabled; TCS External; TSYNC disabled; TCKPS 1:1; TECS SOSC; TON enabled; 
    T1CON = 0x0002;
    //TMR1 0; 
    TMR1 = 0x0000;
    //PR1 20; 
    PR1 = 0x7918; //1s// 0xF230; //2s 
    T1CONbits.TON = 1;
    IPC0bits.T1IP = 5;
    IFS0bits.T1IF = 0;
    IEC0bits.T1IE = 1;
}
//用于基本延时

void TMR2_Initialize(void) {
    //TSIDL disabled; TGATE disabled; TCS FOSC/2; TCKPS 1:256; T32 disabled; TON enabled; 
    T2CON = 0x8030;
    //TMR2 0; 
    TMR2 = 0x0000;
    //Period Value = 10.000 ms; PR2 20000; 
    PR2 = 0xffff; //0x4E20;
    IPC1bits.T2IP = 1;
    T2CONbits.TON = 0;
    IFS0bits.T2IF = 0;
}

void StartTMR2(void) {
    IEC0bits.T2IE = 1;
    T2CONbits.TON = 1;
}

void StopTMR2(void) {
    IEC0bits.T2IE = 0;
    T2CONbits.TON = 0;
}

//void StartTMR2Int(void)
//{
//    
//}


