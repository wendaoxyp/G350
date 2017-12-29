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
//#include <includes.h>
//#include "Configbits.h"
//#include "HL6528.h"
//#include "UART.h"
//#include <xc.h>
#include "mcc.h"
//volatile uint8_t TMR1_CNT;

//OS_STK LEDStk[64];
//OS_STK HL6528Stk[128];
//OS_STK PCCopStk[32];
//OS_EVENT* sem1, *sem2;
//
//static void Task1Led(void* p_arg);
//static void Task2CopGPRS(void* p_arg);

/*
                         Main application
 */
CPU_INT16S main(void) {
    // initialize the device
    SYSTEM_Initialize();
    //    TMR1_Stop();
    //    TMR1_Stop();
    //    BSP_Init();
    //    OSInit();
    //    sem1 = OSSemCreate(0);
    //    sem2 = OSSemCreate(0);
    //    OSTaskCreate(Task1Led, (void*) 0, (OS_STK *) & LEDStk[0], 3);
    //    OSTaskCreate(HL6528_Dialing, (void*) 0, (OS_STK *) & HL6528Stk[0], 8);
    //    OSTaskCreate(PCCopTask, (void*) 0, (OS_STK*) & PCCopStk[0], 7);
    //    OSStart();
    //    return -1;
    while (1) {
        UART1_Write(0xaa);
    }
}

/**
 End of File
 */

//void Task1Led(void* p_arg) {
//    //    INT8U err;
//    //    OS_EVENT sem1;
//    while (1) {
//        //        OSSemPend(sem1, 0, &err); //等待UART2数据发送成功
//        LED_Toggle();
//        while (1)
//            RS485Send(0xaa);
//        OSTimeDlyHMSM(0, 0, 1, 0); //延时1s
//    }
//}




