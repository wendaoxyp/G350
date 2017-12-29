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
        Device            :  PIC24F32KA301
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
volatile uint8_t DealyTime1;
volatile uint8_t DelayTime2;

/*
                         Main application
 */
int main(void) {
    // initialize the device
    SYSTEM_Initialize();
    uint8_t inputW[] = {0x06, 0x02, 0x00, 0x00, 0xAA, 0x04};
    uint8_t inputR[] = {0x06, 0x03, 0x00, 0x00, 0x00, 0x04};
    uint8_t output[10] = {};
    uint8_t inputW1[] = {0x01, 0x00};
    uint8_t inputW2[] = {0x05, 0x00};
    //    uint8_t num = 0;
    //    SS_SetHigh();
    LK_SetHigh();
    TMR1_Start();
    TMR2_Start();
//    LK_SetLow();
//    SPI2_Exchange8bit(0x05); //(inputW1, 2, output);
//    LK_SetHigh();

    //    TMR1_Stop();
    while (1) {
        SS_SetLow();
        SPI2_Exchange8bit(0x05); //(inputW1, 2, output);
        SS_SetHigh();
//        TMR1=TMR2=0;
//        DelayTime2 = 1;
//        while(DelayTime2);
        SS_SetLow();
        SPI2_Exchange8bitBuffer(inputR+1, 4, output);
        SS_SetHigh();
        //        SS_SetLow();
        //        SPI2_Exchange8bit(0x06);
        //        SS_SetHigh();
        //        DealyTime = 1;
        //        while (DealyTime);
        //        SS_SetLow();
        //        SPI2_Exchange8bitBuffer(inputR, 5, output);
        //        //        DealyTime = 1;
        //        //        while (DealyTime);
        //        SS_SetHigh();
        //        DealyTime = 1;
        //        while (DealyTime);
        //        SS_SetLow();
        //        //        DealyTime = 1;
        //        //        while (DealyTime);
        //        SPI2_Exchange8bitBuffer(inputW, 6, output);
        //        //        DealyTime = 1;
        //        //        while (DealyTime);
        //        SS_SetHigh();
        DealyTime1 = 1;
        while (DealyTime1);
        LK_Toggle();
        //        SPI2BUF=0xAA;
        //        SPI2_Exchange8bit(0xAA);// Add your application code
    }

    return -1;
}
/**
 End of File
 */