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

// get/set STATUS aliases
#define STATUS_TRIS               TRISB1
#define STATUS_LAT                LATB1
#define STATUS_PORT               RB1
#define STATUS_WPU                WPUB1
#define STATUS_ANS                ANSB1
#define STATUS_SetHigh()    do { LATB1 = 1; } while(0)
#define STATUS_SetLow()   do { LATB1 = 0; } while(0)
#define STATUS_Toggle()   do { LATB1 = ~LATB1; } while(0)
#define STATUS_GetValue()         RB1
#define STATUS_SetDigitalInput()    do { TRISB1 = 1; } while(0)
#define STATUS_SetDigitalOutput()   do { TRISB1 = 0; } while(0)

#define STATUS_SetPullup()    do { WPUB1 = 1; } while(0)
#define STATUS_ResetPullup()   do { WPUB1 = 0; } while(0)
#define STATUS_SetAnalogMode()   do { ANSB1 = 1; } while(0)
#define STATUS_SetDigitalMode()   do { ANSB1 = 0; } while(0)
// get/set RTS aliases
#define RTS_TRIS               TRISB2
#define RTS_LAT                LATB2
#define RTS_PORT               RB2
#define RTS_WPU                WPUB2
#define RTS_ANS                ANSB2
#define RTS_SetHigh()    do { LATB2 = 1; } while(0)
#define RTS_SetLow()   do { LATB2 = 0; } while(0)
#define RTS_Toggle()   do { LATB2 = ~LATB2; } while(0)
#define RTS_GetValue()         RB2
#define RTS_SetDigitalInput()    do { TRISB2 = 1; } while(0)
#define RTS_SetDigitalOutput()   do { TRISB2 = 0; } while(0)

#define RTS_SetPullup()    do { WPUB2 = 1; } while(0)
#define RTS_ResetPullup()   do { WPUB2 = 0; } while(0)
#define RTS_SetAnalogMode()   do { ANSB2 = 1; } while(0)
#define RTS_SetDigitalMode()   do { ANSB2 = 0; } while(0)
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

// get/set PWR_CON aliases
#define PWR_CON_TRIS               TRISD5
#define PWR_CON_LAT                LATD5
#define PWR_CON_PORT               RD5
#define PWR_CON_WPU                WPUD5
#define PWR_CON_SetHigh()    do { LATD5 = 1; } while(0)
#define PWR_CON_SetLow()   do { LATD5 = 0; } while(0)
#define PWR_CON_Toggle()   do { LATD5 = ~LATD5; } while(0)
#define PWR_CON_GetValue()         RD5
#define PWR_CON_SetDigitalInput()    do { TRISD5 = 1; } while(0)
#define PWR_CON_SetDigitalOutput()   do { TRISD5 = 0; } while(0)

#define PWR_CON_SetPullup()    do { WPUD5 = 1; } while(0)
#define PWR_CON_ResetPullup()   do { WPUD5 = 0; } while(0)
// get/set EN_MCU aliases
#define EN_MCU_TRIS               TRISD6
#define EN_MCU_LAT                LATD6
#define EN_MCU_PORT               RD6
#define EN_MCU_WPU                WPUD6
#define EN_MCU_SetHigh()    do { LATD6 = 1; } while(0)
#define EN_MCU_SetLow()   do { LATD6 = 0; } while(0)
#define EN_MCU_Toggle()   do { LATD6 = ~LATD6; } while(0)
#define EN_MCU_GetValue()         RD6
#define EN_MCU_SetDigitalInput()    do { TRISD6 = 1; } while(0)
#define EN_MCU_SetDigitalOutput()   do { TRISD6 = 0; } while(0)

#define EN_MCU_SetPullup()    do { WPUD6 = 1; } while(0)
#define EN_MCU_ResetPullup()   do { WPUD6 = 0; } while(0)
// get/set GREEN_LED aliases
#define GREEN_LED_TRIS               TRISD7
#define GREEN_LED_LAT                LATD7
#define GREEN_LED_PORT               RD7
#define GREEN_LED_WPU                WPUD7
#define GREEN_LED_SetHigh()    do { LATD7 = 1; } while(0)
#define GREEN_LED_SetLow()   do { LATD7 = 0; } while(0)
#define GREEN_LED_Toggle()   do { LATD7 = ~LATD7; } while(0)
#define GREEN_LED_GetValue()         RD7
#define GREEN_LED_SetDigitalInput()    do { TRISD7 = 1; } while(0)
#define GREEN_LED_SetDigitalOutput()   do { TRISD7 = 0; } while(0)

#define GREEN_LED_SetPullup()    do { WPUD7 = 1; } while(0)
#define GREEN_LED_ResetPullup()   do { WPUD7 = 0; } while(0)

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