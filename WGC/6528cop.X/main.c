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
        Device            :  PIC16LF1527
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC8 v1.34
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
//#include ""
#include "mcc_generated_files/mcc.h"
#include <string.h>
#include "Common.h"
#include "ATCommand.h"
#include "HL6528.h"
#include "StringDeal.h"
//#include "string.h"

/*
                         Main application
 */
void main(void) {
    // initialize the device
    SYSTEM_Initialize();
    uint8_t RightID = 0;
    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //    INTERRUPT_PeripheralInterruptDisable();
    //    INTCONbits.TMR0IE = 1;
    PIE4bits.RC2IE = 1;
    USER_EN_SetDigitalInput();
    HL6528_PW_SetHigh(); //使能GPRS
    Delay1s(2);
    HL6528_SLP_SetLow(); //退出低功耗
    HL6528_RTS_SetLow(); //请求发送数据

    StringCmpInit(&ATString);

    //    ATString.cmpSrt=0;
    while (1) {
        RightID = EUSART2_Read();
        if (RightID)
            GPRSDialing(&ATString, RightID);
        if (!USER_EN_GetValue()) {
            CloseGPRS(&ATString);
            HL6528_RTS_SetHigh(); //请求发送数据
            HL6528_SLP_SetHigh(); //退出低功耗
            HL6528_PW_SetLow(); //使能GPRS
        }
    }
}

//void GPRS_AT_Cop_Task(void) {
//    uint8_t
//}


/**
 End of File
 */



