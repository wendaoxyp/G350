/**
  System Interrupts Generated Driver File 

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.c

  @Summary:
    This is the generated manager file for the MPLAB(c) Code Configurator device.  This manager
    configures the pins direction, initial state, analog setting.
    The peripheral pin select, PPS, configuration is also handled by this manager.

  @Description:
    This source file provides implementations for MPLAB(c) Code Configurator interrupts.
    Generation Information : 
        Product Revision  :  MPLAB(c) Code Configurator - 4.35
        Device            :  PIC24FJ64GA702
    The generated drivers are tested against the following:
        Compiler          :  XC16 1.32
        MPLAB             :  MPLAB X 3.61

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


/**
    Section: Includes
 */
#include <xc.h>
#include "pin_manager.h"
#include "..\Common.h"

/**
    void PIN_MANAGER_Initialize(void)
 */
void PIN_MANAGER_Initialize(void) {
    /****************************************************************************
     * Setting the Output Latch SFR(s)
     ***************************************************************************/
    LATA = 0x0000;
    LATB = 0x0000;

    /****************************************************************************
     * Setting the GPIO Direction SFR(s)
     ***************************************************************************/
    TRISA = 0x001F;
    TRISB = 0xEFFF;

    /****************************************************************************
     * Setting the Weak Pull Up and Weak Pull Down SFR(s)
     ***************************************************************************/
    IOCPDA = 0x0000;
    IOCPDB = 0x0000;
    IOCPUA = 0x0002;
    IOCPUB = 0x4000;

    /****************************************************************************
     * Setting the Open Drain SFR(s)
     ***************************************************************************/
    ODCA = 0x0000;
    ODCB = 0x0000;

    /****************************************************************************
     * Setting the Analog/Digital Configuration SFR(s)
     ***************************************************************************/
    ANSA = 0x0009; //0000 0000 0000 1011(1001)
    ANSB = 0xB20C; //1011(1010) 0010 0000 1100



    /****************************************************************************
     * Interrupt On Change for group IOCFA - flag
     ***************************************************************************/
    IOCFAbits.IOCFA1 = 0; // Pin : RA1

    /****************************************************************************
     * Interrupt On Change for group IOCFB - flag
     ***************************************************************************/
    IOCFBbits.IOCFB14 = 0; // Pin : RB14

    /****************************************************************************
     * Interrupt On Change for group IOCNA - negative
     ***************************************************************************/
    IOCNAbits.IOCNA1 = 0; // Pin : RA1

    /****************************************************************************
     * Interrupt On Change for group IOCNB - negative
     ***************************************************************************/
    IOCNBbits.IOCNB14 = 0; // Pin : RB14

    /****************************************************************************
     * Interrupt On Change for group IOCPA - positive
     ***************************************************************************/
    IOCPAbits.IOCPA1 = 1; // Pin : RA1

    /****************************************************************************
     * Interrupt On Change for group IOCPB - positive
     ***************************************************************************/
    IOCPBbits.IOCPB14 = 1; // Pin : RB14

    /****************************************************************************
     * Interrupt On Change for group PADCON - config
     ***************************************************************************/
    PADCONbits.IOCON = 1;

    IEC1bits.IOCIE = 1; // Enable IOCI interrupt 
}

/* Interrupt service routine for the IOCI interrupt. */
void __attribute__((interrupt, no_auto_psv)) _IOCInterrupt(void) {
    if (IFS1bits.IOCIF == 1) {
        // Clear the flag
        IFS1bits.IOCIF = 0;
        // interrupt on change for group IOCFA
        Nop();
        if (!PORTAbits.RA0) {
            //key handle
            Delay10ms(1);
            if (!PORTAbits.RA0) {//表示确实是按下了
                //add GPON code 
                Nop();
            }
//            do {
//                Delay10ms(1);
//            } while (!PORTAbits.RA0);
            //            IOCFAbits.IOCFA1 = 0;
            //            LATBbits.LATB12 ^= 1; // Add handler code here for Pin - RA1
        }
        // interrupt on change for group IOCFB
        if (!PORTBbits.RB14) {//为什么放前面就号多了
            //            IOCFBbits.IOCFB14 = 0;
            Delay10ms(1);
            if (!PORTBbits.RB14) {
                LATBbits.LATB12 ^= 1; // Add handler code here for Pin - RB14
            }
            do {//确保按键松开
                Delay10ms(1);
            } while (!PORTBbits.RB14);

        }
    }
}

void __attribute__((interrupt, no_auto_psv)) _DefaultInterrupt(void) {
    Nop();

}

