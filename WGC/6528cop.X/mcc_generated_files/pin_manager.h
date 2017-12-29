/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using MPLAB? Code Configurator

  @Description:
    This header file provides implementations for pin APIs for all pins selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB? Code Configurator - v2.25.2
        Device            :  PIC16LF1527
        Version           :  1.01
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

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set P1527_U2 aliases
#define P1527_U2_TRIS               TRISB0
#define P1527_U2_LAT                LATB0
#define P1527_U2_PORT               RB0
#define P1527_U2_WPU                WPUB0
#define P1527_U2_ANS                ANSB0
#define P1527_U2_SetHigh()    do { LATB0 = 1; } while(0)
#define P1527_U2_SetLow()   do { LATB0 = 0; } while(0)
#define P1527_U2_Toggle()   do { LATB0 = ~LATB0; } while(0)
#define P1527_U2_GetValue()         RB0
#define P1527_U2_SetDigitalInput()    do { TRISB0 = 1; } while(0)
#define P1527_U2_SetDigitalOutput()   do { TRISB0 = 0; } while(0)

#define P1527_U2_SetPullup()    do { WPUB0 = 1; } while(0)
#define P1527_U2_ResetPullup()   do { WPUB0 = 0; } while(0)
#define P1527_U2_SetAnalogMode()   do { ANSB0 = 1; } while(0)
#define P1527_U2_SetDigitalMode()   do { ANSB0 = 0; } while(0)
// get/set HL6528_RTS aliases
#define HL6528_RTS_TRIS               TRISB2
#define HL6528_RTS_LAT                LATB2
#define HL6528_RTS_PORT               RB2
#define HL6528_RTS_WPU                WPUB2
#define HL6528_RTS_ANS                ANSB2
#define HL6528_RTS_SetHigh()    do { LATB2 = 1; } while(0)
#define HL6528_RTS_SetLow()   do { LATB2 = 0; } while(0)
#define HL6528_RTS_Toggle()   do { LATB2 = ~LATB2; } while(0)
#define HL6528_RTS_GetValue()         RB2
#define HL6528_RTS_SetDigitalInput()    do { TRISB2 = 1; } while(0)
#define HL6528_RTS_SetDigitalOutput()   do { TRISB2 = 0; } while(0)

#define HL6528_RTS_SetPullup()    do { WPUB2 = 1; } while(0)
#define HL6528_RTS_ResetPullup()   do { WPUB2 = 0; } while(0)
#define HL6528_RTS_SetAnalogMode()   do { ANSB2 = 1; } while(0)
#define HL6528_RTS_SetDigitalMode()   do { ANSB2 = 0; } while(0)
// get/set HL6528_SLP aliases
#define HL6528_SLP_TRIS               TRISB4
#define HL6528_SLP_LAT                LATB4
#define HL6528_SLP_PORT               RB4
#define HL6528_SLP_WPU                WPUB4
#define HL6528_SLP_ANS                ANSB4
#define HL6528_SLP_SetHigh()    do { LATB4 = 1; } while(0)
#define HL6528_SLP_SetLow()   do { LATB4 = 0; } while(0)
#define HL6528_SLP_Toggle()   do { LATB4 = ~LATB4; } while(0)
#define HL6528_SLP_GetValue()         RB4
#define HL6528_SLP_SetDigitalInput()    do { TRISB4 = 1; } while(0)
#define HL6528_SLP_SetDigitalOutput()   do { TRISB4 = 0; } while(0)

#define HL6528_SLP_SetPullup()    do { WPUB4 = 1; } while(0)
#define HL6528_SLP_ResetPullup()   do { WPUB4 = 0; } while(0)
#define HL6528_SLP_SetAnalogMode()   do { ANSB4 = 1; } while(0)
#define HL6528_SLP_SetDigitalMode()   do { ANSB4 = 0; } while(0)
// get/set TX1 aliases
#define TX1_TRIS               TRISC6
#define TX1_LAT                LATC6
#define TX1_PORT               RC6
#define TX1_SetHigh()    do { LATC6 = 1; } while(0)
#define TX1_SetLow()   do { LATC6 = 0; } while(0)
#define TX1_Toggle()   do { LATC6 = ~LATC6; } while(0)
#define TX1_GetValue()         RC6
#define TX1_SetDigitalInput()    do { TRISC6 = 1; } while(0)
#define TX1_SetDigitalOutput()   do { TRISC6 = 0; } while(0)

// get/set RX1 aliases
#define RX1_TRIS               TRISC7
#define RX1_LAT                LATC7
#define RX1_PORT               RC7
#define RX1_SetHigh()    do { LATC7 = 1; } while(0)
#define RX1_SetLow()   do { LATC7 = 0; } while(0)
#define RX1_Toggle()   do { LATC7 = ~LATC7; } while(0)
#define RX1_GetValue()         RC7
#define RX1_SetDigitalInput()    do { TRISC7 = 1; } while(0)
#define RX1_SetDigitalOutput()   do { TRISC7 = 0; } while(0)

// get/set HL6528_PW aliases
#define HL6528_PW_TRIS               TRISD6
#define HL6528_PW_LAT                LATD6
#define HL6528_PW_PORT               RD6
#define HL6528_PW_WPU                WPUD6
#define HL6528_PW_SetHigh()    do { LATD6 = 1; } while(0)
#define HL6528_PW_SetLow()   do { LATD6 = 0; } while(0)
#define HL6528_PW_Toggle()   do { LATD6 = ~LATD6; } while(0)
#define HL6528_PW_GetValue()         RD6
#define HL6528_PW_SetDigitalInput()    do { TRISD6 = 1; } while(0)
#define HL6528_PW_SetDigitalOutput()   do { TRISD6 = 0; } while(0)

#define HL6528_PW_SetPullup()    do { WPUD6 = 1; } while(0)
#define HL6528_PW_ResetPullup()   do { WPUD6 = 0; } while(0)
// get/set USER_EN aliases
#define USER_EN_TRIS               TRISE0
#define USER_EN_LAT                LATE0
#define USER_EN_PORT               RE0
#define USER_EN_WPU                WPUE0
#define USER_EN_ANS                ANSE0
#define USER_EN_SetHigh()    do { LATE0 = 1; } while(0)
#define USER_EN_SetLow()   do { LATE0 = 0; } while(0)
#define USER_EN_Toggle()   do { LATE0 = ~LATE0; } while(0)
#define USER_EN_GetValue()         RE0
#define USER_EN_SetDigitalInput()    do { TRISE0 = 1; } while(0)
#define USER_EN_SetDigitalOutput()   do { TRISE0 = 0; } while(0)

#define USER_EN_SetPullup()    do { WPUE0 = 1; } while(0)
#define USER_EN_ResetPullup()   do { WPUE0 = 0; } while(0)
#define USER_EN_SetAnalogMode()   do { ANSE0 = 1; } while(0)
#define USER_EN_SetDigitalMode()   do { ANSE0 = 0; } while(0)
// get/set USER_LK aliases
#define USER_LK_TRIS               TRISF0
#define USER_LK_LAT                LATF0
#define USER_LK_PORT               RF0
#define USER_LK_ANS                ANSF0
#define USER_LK_SetHigh()    do { LATF0 = 1; } while(0)
#define USER_LK_SetLow()   do { LATF0 = 0; } while(0)
#define USER_LK_Toggle()   do { LATF0 = ~LATF0; } while(0)
#define USER_LK_GetValue()         RF0
#define USER_LK_SetDigitalInput()    do { TRISF0 = 1; } while(0)
#define USER_LK_SetDigitalOutput()   do { TRISF0 = 0; } while(0)

#define USER_LK_SetAnalogMode()   do { ANSF0 = 1; } while(0)
#define USER_LK_SetDigitalMode()   do { ANSF0 = 0; } while(0)
// get/set TX2 aliases
#define TX2_TRIS               TRISG1
#define TX2_LAT                LATG1
#define TX2_PORT               RG1
#define TX2_ANS                ANSG1
#define TX2_SetHigh()    do { LATG1 = 1; } while(0)
#define TX2_SetLow()   do { LATG1 = 0; } while(0)
#define TX2_Toggle()   do { LATG1 = ~LATG1; } while(0)
#define TX2_GetValue()         RG1
#define TX2_SetDigitalInput()    do { TRISG1 = 1; } while(0)
#define TX2_SetDigitalOutput()   do { TRISG1 = 0; } while(0)

#define TX2_SetAnalogMode()   do { ANSG1 = 1; } while(0)
#define TX2_SetDigitalMode()   do { ANSG1 = 0; } while(0)
// get/set RX2 aliases
#define RX2_TRIS               TRISG2
#define RX2_LAT                LATG2
#define RX2_PORT               RG2
#define RX2_ANS                ANSG2
#define RX2_SetHigh()    do { LATG2 = 1; } while(0)
#define RX2_SetLow()   do { LATG2 = 0; } while(0)
#define RX2_Toggle()   do { LATG2 = ~LATG2; } while(0)
#define RX2_GetValue()         RG2
#define RX2_SetDigitalInput()    do { TRISG2 = 1; } while(0)
#define RX2_SetDigitalOutput()   do { TRISG2 = 0; } while(0)

#define RX2_SetAnalogMode()   do { ANSG2 = 1; } while(0)
#define RX2_SetDigitalMode()   do { ANSG2 = 0; } while(0)

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    GPIO and peripheral I/O initialization
 * @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize(void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);

#endif // PIN_MANAGER_H
/**
 End of File
 */