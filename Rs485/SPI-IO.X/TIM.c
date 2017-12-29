#include"type.h"
#include"user.h"
#include"time.h"
#include"string.h"

vu16 gT3Count = 0;
vu16 gT1Count = 0; //记录溢出的次数 =1避免上线定时器在中断开启的时间短

/*************************************
Function: TIM1_Configuration 
Description: 16位定时器初始化 
Input: 无 
Output: 无
 *************************************/
void TIM1_Configuration(void) {
    T1CONbits.TON = 1;
    T1CONbits.TSIDL = 0; //0 = 模块在空闲模式下继续工作
    T1CONbits.TCKPS = 0; //64us一个脉冲2(自动倍频)*500K/2=250k=2us 2us*256=512us=0.512ms
    T1CONbits.TCS = 1; //=1 T1ECS决定
    T1CONbits.T1ECS = 0x00; //=0 SOSC
    T1CONbits.TGATE = 0;
    //    T1CONbits.TSYNC = 0;
    PR1 = 0x8000; //1s  
    IPC0bits.T1IP = 6; //Setup Timer3 interrupt for desired priority level
    //(this example assigns level 1 priority)
    IFS0bits.T1IF = 0; //Clear the Timer3 interrupt status flag
    IEC0bits.T1IE = 1; //Enable Timer3 interrupts
    TMR1 = 0;
    T1CONbits.TON = 0; //=0!!!!!!
}

/*************************************
Function: TIM4_Configuration 
Description: 16位定时器初始化 
Input: 无 
Output: 无
 *************************************/
void TIM2_Configuration(void) {
    T2CONbits.TON = 1;
    T2CONbits.TSIDL = 0;
    T2CONbits.TCKPS = 2; //1=1:8  2.56s 10(2)=1:64  11(3)=1:256
    T2CONbits.TCS = 0; //=1 内部时钟/2
    T2CONbits.TGATE = 0;
    T2CONbits.T32 = 0; //16位独立
    PR2 = 12500; //200ms   1/（4/256*1000000）*?=1500/1000ms 【100ms】?=6250
    IPC1bits.T2IP = 2; //Setup Timer3 interrupt for desired priority level
    //(this example assigns level 1 priority)
    IFS0bits.T2IF = 0; //Clear the Timer3 interrupt status flag
    IEC0bits.T2IE = 1; //Enable Timer3 interrupts
    TMR2 = 0;
    T2CONbits.TON = 0; //=0!!!!!!
}

/*************************************
Function: TIM4_Configuration 
Description: 16位定时器初始化 
Input: 无 
Output: 无
 *************************************/
void TIM3_Configuration(void) {
    T3CONbits.TON = 1;
    T3CONbits.TSIDL = 1;
    T3CONbits.TCKPS = 0; //1:1
    T3CONbits.TCS = 0; //=1 内部时钟/2
    T3CONbits.TGATE = 0;
    //    T3CONbits.T32 = 0; //16位独立
    PR3 = 40000; //4000 1ms    
    IPC2bits.T3IP = 1; //Setup Timer3 interrupt for desired priority level
    //(this example assigns level 1 priority)
    IFS0bits.T3IF = 0; //Clear the Timer3 interrupt status flag
    IEC0bits.T3IE = 1; //Enable Timer3 interrupts
    TMR3 = 0;
    T3CONbits.TON = 0; //=0!!!!!!
}

/*************************************
Function: TIM4_Configuration 
Description: 16位定时器初始化 
Input: 无 
Output: 无
 *************************************/
void TIM4_Configuration(void) {
    T4CONbits.TON = 1;
    T4CONbits.TSIDL = 1;
    T4CONbits.TCKPS = 0; //1:1
    T4CONbits.TCS = 0; //=1 内部时钟/2
    T4CONbits.TGATE = 0;
    T4CONbits.T32 = 0; //16位独立
    PR4 = 125; //4000 1ms    
    IPC6bits.T4IP = 3; //Setup Timer3 interrupt for desired priority level
    //(this example assigns level 1 priority)
    IFS1bits.T4IF = 0; //Clear the Timer3 interrupt status flag
    IEC1bits.T4IE = 0; //Enable Timer3 interrupts
    TMR4 = 0;
    T4CONbits.TON = 0; //=0!!!!!!
}

void StartTime3(void) {
    gT3Count = 0;
    IEC0bits.T3IE = 1; //Enable Timer3 interrupts
    T3CONbits.TON = 1; //开定时器 提高通讯稳定性
}

void CloseTime3(void) {
    IEC0bits.T3IE = 0; //Enable Timer3 interrupts
    T3CONbits.TON = 0; //关定时器
    gT3Count = 0; //清除计数
    TMR3 = 0x0000;
}

void StartTime4(void) {
    IEC1bits.T4IE = 1; //Enable Timer3 interrupts
    T4CONbits.TON = 1; //开定时器 提高通讯稳定性
}

void CloseTime4(void) {
    IEC1bits.T4IE = 0; //Enable Timer3 interrupts
    T4CONbits.TON = 0; //关定时器
}

bool T3IsOver(const u16 deadline) {//放在循环中判断是否是个死循环 使用之前需要清除Tcount
    //    ClrWdt();
    return (gT3Count > deadline) ? 1 : 0;
}

void GetUnixTime_Char(u8* timeptr, u8* output) {
    u8 cnt;
    time_t times_l;
    struct tm gmt;
    void * ptr;

    gmt.tm_year = HCD(*(timeptr + 1)) + 100; //1900年开始 (u16) (HCD(*timeptr))*100; //2000-1900
    gmt.tm_mon = HCD(*(timeptr + 2)) - 1; //去除减一
    gmt.tm_mday = HCD(*(timeptr + 3));
    gmt.tm_hour = HCD(*(timeptr + 4));
    gmt.tm_min = HCD(*(timeptr + 5));
    gmt.tm_sec = HCD(*(timeptr + 6));
    gmt.tm_isdst = 0;
    gmt.tm_wday = 0;
    gmt.tm_yday = 0;

    times_l = mktime(&gmt); // - 28800; //相差28000s减去
    ptr = &times_l;

    for (cnt = 0; cnt < 4; cnt++)// {
        *(output + cnt) = *((u8*) ptr + cnt);
}

/*************************************
Function: delay_nop 
Description: 用于调整SPI通讯的延时
Input: 延时数量
Output: 无
 *************************************/
void Delay_Nop(int count) {
    while (count--)
        Nop();
}

