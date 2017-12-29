/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using MPLAB? Code Configurator

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB? Code Configurator - v2.25.2
        Device            :  PIC24FJ64GA310
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.24
        MPLAB             :  MPLAB X v2.35 or v3.00
 */

/*
Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 */

#include "mcc_generated_files/mcc.h"

uint8_t T1_1s_Flag;
void Delay10ms(void);

/*
                         Main application
 */
int main(void) {
    // initialize the device
    SYSTEM_Initialize();
    //关闭定时器

    IEC0bits.T1IE = false;
    T1CONbits.TON = false;
    T1_1s_Flag = false;

    uint8_t cnt, cnt1, flag = 0;
    //LED 初始化
    for (cnt = 0; cnt < 20; cnt++) {
        LED_R_Toggle();
        LED_B_Toggle();
        LED_G_Toggle();
        for (cnt1 = 0; cnt1 < 50; cnt1++)
            Delay10ms();
    }
    LED_R_SetLow();
    LED_G_SetLow();
    LED_B_SetLow();
//    cnt = flag = 0;
    while (1) {
        flag = 1;
        cnt = 0;
        if (!IN1_GetValue()) {
            do {
                Delay10ms();
                if (cnt++ > 10) {
                    flag = 0;
                    break;
                }
            } while (!IN1_GetValue());
            if (flag) LED_R_Toggle();
        }
        flag = 1;
        cnt = 0;
        if (!IN2_GetValue()) {
//            Delay10ms();
            do {
                Delay10ms();
                if (cnt++ > 10) {
                    flag = 0;
                    break;
                }
            } while (!IN2_GetValue());
            if (flag) LED_G_Toggle();
        }
        flag = 1;
        cnt = 0;
        if (!IN3_GetValue()) {
            do {
                Delay10ms();
                if (cnt++ > 10) {
                    flag = 0;
                    break;
                }
            } while (!IN3_GetValue());
            if (flag) LED_B_Toggle();
        }
        //        flag = 1;
        //        cnt = 0;
    }

    return -1;
}

/**
 End of File
 */
void Delay10ms(void) {
    TMR1 = 0;
    IFS0bits.T1IF = false;
    IEC0bits.T1IE = true;
    T1CONbits.TON = true;
    while (!T1_1s_Flag);
    T1_1s_Flag = false;
    T1CONbits.TON = false;
    IEC0bits.T1IE = false;
}

