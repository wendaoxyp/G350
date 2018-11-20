/* 
 * File:   main.c
 * Author: wendaoxyp
 *
 * Created on 2018年01月04日, 下午12:54
 */
#include "TX04_Conf.h"

/*************************************
Function: OSCILLATOR_Init 
Description: 时钟初始化
Input: void
Output: void
 *************************************/
void OSCILLATOR_Init(void) {
    // CF no clock failure; NOSC FRC; SOSCEN disabled; POSCEN disabled; CLKLOCK unlocked; OSWEN Switch is Complete; IOLOCK not-active; 
    //    __builtin_write_OSCCONL((uint8_t) (0x0000 & 0x00FF));
    // CF no clock failure; NOSC FRC; SOSCEN disabled; POSCEN disabled; CLKLOCK unlocked; OSWEN Switch is Complete; IOLOCK not-active; 
    //    __builtin_write_OSCCONH(0x07); //外部晶振
    __builtin_write_OSCCONH(0x02); //外部晶振010 = 主振荡器（XT、HS和EC）
    __builtin_write_OSCCONL(0x05);
    // CPDIV 1:1; PLLEN disabled; DOZE 1:8; RCDIV FRC; DOZEN disabled; ROI disabled; 
    CLKDIV = 0x3200;
    // STOR disabled; STORPOL Interrupt when STOR is 1; STSIDL disabled; STLPOL Interrupt when STLOCK is 1; STLOCK disabled; STSRC SOSC; STEN disabled; TUN Center frequency; 
    OSCTUN = 0x0000;
    // ROEN disabled; ROSEL FOSC; ROSIDL disabled; ROSWEN disabled; ROOUT disabled; ROSLP disabled; 
    REFOCONL = 0x0000;
    // RODIV 0; 
    REFOCONH = 0x0000;
    // ROTRIM 0; 
    REFOTRIML = 0x0000;
    // DCOTUN 0; 
    DCOTUN = 0x0000;
    // DCOFSEL 8; DCOEN disabled; 
    DCOCON = 0x0700;
    // DIV 0; 
    OSCDIV = 0x0000; //0分频
    // TRIM 0; 
    OSCFDIV = 0x0000;
}

/*************************************
Function: PIN_MANAGER_Init 
Description: IO口初始化
Input: void
Output: void
 *************************************/
void PIN_MANAGER_Init(void) {
    /****************************************************************************
     * Setting the GPIO Direction SFR(s)
     ***************************************************************************/
    TRISA = 0x000D; //RA0(RDE,0)
    TRISB = 0x4588; //RB13(Ublox_PWRKEY,0)RB12（LED_G,0）RB7（INTE,1）RB9(Ublox_EN,0) RB2(UART2TX,0) RB3(UART2RX,1) 

    LDO_EN1_DEC_IS_IN;
    USER_RX_IS_IN;
    USER_TX_IS_OUT;
    NONE1_IS_OUT;
    UB_RESET_IS_OUT;
    INT0_IS_IN;
    UB_PWRON_IS_OUT;
    UB_STA_IS_IN;
    UB_U1_RX_IS_IN;
    UB_U1_TX_IS_OUT;
    UB_U1_CTS_IS_IN;
    UB_U1_RTS_IS_OUT;
    //    UB_U1_RTS = 0;//
    OR_CTRL_PWR_IS_OUT;
    GLED_IS_OUT;
    USER_LK_IS_OUT;
    //    LDO_EN1_DEC = 1;
    /****************************************************************************
     * Setting the Output Latch SFR(s)
     ***************************************************************************/
    LATA = 0x0000; //RA0(RDE,1)  LK方向
    LATB = 0x0000; //RB2(UART2TX,0) RB3(UART2RX,1),RB7（INTE,0）,RB10(U1RX,0),RB11(U1TX,1)

    /****************************************************************************
     * Setting the Weak Pull Up and Weak Pull Down SFR(s)
     ***************************************************************************/
    IOCPDA = 0x0000;
    IOCPDB = 0x0000;
    IOCPUA = 0x0000;
    IOCPUB = 0x0000; // 0x0008;

    /****************************************************************************
     * Setting the Open Drain SFR(s)
     ***************************************************************************/
    ODCA = 0x0000;
    ODCB = 0x0000;

    /****************************************************************************
     * Setting the Analog/Digital Configuration SFR(s) 1/0
     ***************************************************************************/
    ANSA = 0x000C;
    ANSB = 0xE004; //F404 RB2(UART2TX,1) RB3(UART2RX,0)RB7（INTE,0） RB10(U1RX,0),RB11(U1TX,1)

    /****************************************************************************
     * Setting the PPS
     ***************************************************************************/
    __builtin_write_OSCCONL(OSCCON & 0xbf); // unlock PPS

    RPOR5bits.RP11R = 0x0003; //RB11->UART1:U1TX;
    RPOR6bits.RP13R = 0x0004; //RB13->UART1:U1RTS
    RPINR18bits.U1RXR = 0x000A; //RB10->UART1:U1RX;
    RPINR18bits.U1CTSR = 0x000C; //RB12->UART1:U1CTS
    //    RPOR1bits.RP3R = 0x0005; //RB3->UART2:U2TX
    //    RPINR19bits.U2RXR = 0x0002; //RB2->UART2:U2RX
    RPOR1bits.RP2R = 0x0005; //RB2->UART2:U2TX
    RPINR19bits.U2RXR = 0x0003; //RB3->UART2:U2RX

    RPINR0bits.INT1R = 0x001A; //RA0->INT1
    //RPINR18bits.U1CTSR = 0x000C;   //RB12->UART1:U1CTS;
    //    RPOR5bits.RP11R = 0x0003;   //RB11->UART1:U1TX;
    //    RPOR6bits.RP13R = 0x0004;   //RB13->UART1:U1RTS;
    //    RPINR18bits.U1RXR = 0x000A;   //RB10->UART1:U1RX;
    __builtin_write_OSCCONL(OSCCON | 0x40); // lock   PPS
}

/*************************************
Function: INTERRUPT_Init 
Description: 中断优先级初始化
Input: void
Output: void
 *************************************/
void INTERRUPT_Init(void) {
    IPC16bits.U2ERIP = 7;

    //    IPC7bits.U2RXIP = 4; //接收数据优先

    IPC16bits.U1ERIP = 7;

    //    IPC2bits.U1RXIP = 6; //必须添加 必须大于INT1中断
    IPC1bits.DMA0IP = 5; //DMA0 UART1传输数据

    IPC3bits.DMA1IP = 4; //DMA1 UART2传输数据
    //    _U1TXIP = 6; //必须添加
    //    IPC0bits.INT0IP = 2;

    IPC5bits.INT1IP = 3;

    IPC0bits.T1IP = 2;

    IPC1bits.T2IP = 6; // 必须大于INT1中断

    //    IPC2bits.T3IP = 1;
}



