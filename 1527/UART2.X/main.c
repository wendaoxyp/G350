/* 
 * File:   main.c
 * Author: Administrator
 *
 * Created on 2017年12月5日, 下午3:31
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/eusart2.h"
#include "mcc_generated_files/interrupt_manager.h"
// CONFIG1
//#pragma config FOSC = ECH       // Oscillator Selection (ECH, External Clock, High Power Mode (4-20 MHz): device clock supplied to CLKIN pin)
//#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
//#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
//#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
//#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
//#pragma config BOREN = OFF      // Brown-out Reset Enable (Brown-out Reset disabled)
//#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
//#pragma config IESO = ON        // Internal/External Switchover (Internal/External Switchover mode is enabled)
//#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is enabled)
//
//// CONFIG2
//#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
//#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
//#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
//#pragma config LPBOR = OFF      // Low-Power Brown Out Reset (Low-Power BOR is disabled)
//#pragma config LVP = ON         // Low-Voltage Programming Enable (Low-voltage programming enabled)

/*
 * 
 */
extern volatile uint8_t Flag_Time1;
void Delay(void);
void UART1_SendString(const uint8_t *dat);

int main(int argc, char** argv) {
    SYSTEM_Initialize();
    GREEN_LED_TRIS = 0;
    PWR_CON_TRIS = 0;
    EN_MCU_TRIS = 0;
    STATUS_TRIS = 1;
    EN_MCU_SetHigh();
    PWR_CON_SetHigh();

    while (1) {
        if (STATUS_GetValue()) {//去抖动
            while (!Flag_Time1);
            Flag_Time1 = 0;
            if (STATUS_GetValue())
                break;
        }
        //        while (!STATUS_GetValue());
    }
    //    EN_MCU_SetHigh();

    PWR_CON_SetLow();


    while (1) {
        while (!Flag_Time1);
        Flag_Time1 = 0;
        //        eusart1TxBufferRemaining = 8;
        EUSART1_Write('A');
        EUSART1_Write('T');
        EUSART1_Write('+');
        EUSART1_Write('I');
        EUSART1_Write('P');
        EUSART1_Write('R');
        EUSART1_Write('=');
        EUSART1_Write('1');
        EUSART1_Write('9');
        EUSART1_Write('2');
        EUSART1_Write('0');
        EUSART1_Write('0');
        EUSART1_Write('\n');
        //        UART1_SendString("AT+IPR=19200\n");
        //        GREEN_LED_Toggle();
        //        while (!Flag_Time1);
        //        Flag_Time1 = 0;
        //        UART1_SendString("AT+IPR=9600\n");
    }
}

//void Delay(void) {
//    unsigned int i, j;
//    for (i = 0; i < 500; i++)
//        for (j = 0; j < 100; j++)
//            asm("nop()");
//}

void UART1_SendString(const uint8_t *dat) {
    uint8_t cnt = 0;
    eusart1TxBufferRemaining = 8;
    while (*(dat + cnt) != '\0') {
        EUSART1_Write(*(dat + cnt));
        cnt++;
    }
}

