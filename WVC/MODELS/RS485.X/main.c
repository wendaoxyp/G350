/* 
 * File:   main.c
 * Author: Administrator
 *
 * Created on 2017年12月21日, 下午12:54
 */

#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "RS485.h"
//#include "mcc_generated_files/mcc.h"
#define LED_G LATBbits.LATB12
extern void OSCILLATOR_Init(void);
extern void PIN_MANAGER_Init(void);
//extern void Set_PPS(void);
void Set_IPC(void);

/*
 * 
 */
int main(void) {
    //    SYSTEM_Initialize();
    OSCILLATOR_Init();
    PIN_MANAGER_Init();
    Set_IPC();
    RS485_Init();

    TRISBbits.TRISB12 = 0;
    //    return (EXIT_SUCCESS);
    while (1) {
        //        if()
        RS485SendString((const uint8_t *) "Hell123456", 10);
        LATBbits.LATB12 ^= 1;
        Delay1s(1);
    }
}

/*
void Timer0_Init(void)
{
    T1CONbits.TON=0;//关闭定时器1
    T1CONbits.TECS=0b10;//使用LPRC 晶振
    TMR1=0;
    PR1=0x7918;//1s定时
    IFS0bits.T1IF=0;
//    IECbits.
//    IPCbits.
}
 */

void OSCILLATOR_Init(void) {
    // CF no clock failure; NOSC FRC; SOSCEN disabled; POSCEN disabled; CLKLOCK unlocked; OSWEN Switch is Complete; IOLOCK not-active; 
    __builtin_write_OSCCONL((uint8_t) (0x0000 & 0x00FF));
    // CPDIV 1:1; PLLEN disabled; DOZE 1:8; RCDIV FRC; DOZEN disabled; ROI disabled; 
    CLKDIV = 0x3000;
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
    OSCDIV = 0x0000;
    // TRIM 0; 
    OSCFDIV = 0x0000;
}

void PIN_MANAGER_Init(void) {
    /****************************************************************************
     * Setting the Output Latch SFR(s)
     ***************************************************************************/
    LATA = 0x0000;
    LATB = 0x0004; //RB2(UART2TX) RB3(UART2RX)

    /****************************************************************************
     * Setting the GPIO Direction SFR(s)
     ***************************************************************************/
    TRISA = 0x001F;
    TRISB = 0xEFFB; //RB2(UART2TX) RB3(UART2RX)

    /****************************************************************************
     * Setting the Weak Pull Up and Weak Pull Down SFR(s)
     ***************************************************************************/
    IOCPDA = 0x0000;
    IOCPDB = 0x0000;
    IOCPUA = 0x0000;
    IOCPUB = 0x0000;

    /****************************************************************************
     * Setting the Open Drain SFR(s)
     ***************************************************************************/
    ODCA = 0x0000;
    ODCB = 0x0000;

    /****************************************************************************
     * Setting the Analog/Digital Configuration SFR(s) 1/0
     ***************************************************************************/
    ANSA = 0x000F;
    ANSB = 0xF204; //RB2(UART2TX) RB3(UART2RX)

    /****************************************************************************
     * Setting the PPS
     ***************************************************************************/
    __builtin_write_OSCCONL(OSCCON & 0xbf); // unlock PPS

    //    RPOR5bits.RP11R = 0x0003; //RB11->UART1:U1TX;
    //    RPINR18bits.U1RXR = 0x000A; //RB10->UART1:U1RX;
    RPOR1bits.RP2R = 0x0005; //RB2->UART2:U2TX
    RPINR19bits.U2RXR = 0x0003; //RB3->UART2:U2RX

    __builtin_write_OSCCONL(OSCCON | 0x40); // lock   PPS

}

void Set_IPC(void) {
    IPC7bits.U2RXIP = 3;
    IPC16bits.U2ERIP = 6;
}



