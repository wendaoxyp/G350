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
        Device            :  PIC24FJ64GA306
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


#include <includes.h>
#include "Configbits.h"


OS_STK SleepStk[128];

static void Task1Sleep(void* p_arg);

/*
                         Main application
 */
CPU_INT16S main(void) {
    INT8U err;
    BSP_Init(); //底层驱动初始化

    OSInit();

    OSTaskCreate(Task1Sleep, (void*) 0, (OS_STK *) & SleepStk[0], 3);
    OSStart();
    return -1;

}

/**
 End of File
 */

void Task1Sleep(void* p_arg) {
    INT8U err;
    //E41休眠模式
    M0_TRIS = 0;
    M1_TRIS = 0;
    M0 = M1 = 1;
    //RS485休眠模式
    RS485_TRIS = 0;
    RS485_CON = 0;

    //EEROM休眠 外部上拉，无需设置
    TRISGbits.TRISG2 = TRISGbits.TRISG3 = 0;
    TRISBbits.TRISB12 = 0;
    LATBbits.LATB12 = 1;
    LATGbits.LATG2 = LATGbits.LATG3 = 1;
    //GPRS
    TRISDbits.TRISD6 = TRISDbits.TRISD7 = 0;
    LATDbits.LATD6 = 0;
    LATDbits.LATD7 = 0;
    //关闭串口
    U1MODEbits.UARTEN = 0;
    U2MODEbits.UARTEN = 0;
    U3MODEbits.UARTEN = 0;
    //    TRISB = TRISC = TRISD = TRISE = TRISF = TRISG = 0;
    //    LATB = LATC = LATD = LATE = LATF = LATG = 0;
    while (1) {//90uA 关闭外部设备即可 未焊接E41
        //进入低功耗晶振
//        __builtin_write_OSCCONH(0x35);
//        __builtin_write_OSCCONL(OSCCON | 0x06);
//        OSCCONbits.OSWEN = 1;
//        OSTimeDlyHMSM(0, 0, 0, 2);
//        Sleep();
        DeepSleep();
    }
}






