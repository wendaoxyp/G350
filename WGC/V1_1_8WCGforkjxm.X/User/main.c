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

#ifdef DEBUG_MAIN_VAR
volatile uint32_t rtime;
uint8_t main_cnt = 0;
//uint32_t main_nums;
//volatile uint8_t samplecount;
//volatile uint8_t samplecount1;
#endif

/*
                         Main application
 */
void main(void) {
    //    uint32_t nums = 1;
    //    uint8_t tmp[10];    
    BSP_Init(); //�ײ�������ʼ��
    NUMS_SHOW(1, 0);
    IFS3bits.RTCIF = 1; //������ص��жϱ�־״̬λ����
    RS485SendString("Start", 5); //�ȷ���һ���ֽڣ�������մ���
    while (1) {
        //        Delay1s(5);
        //        WGCPCCop();
        //�Ż��͹��ģ��ر�ģ��
        while (!WGCCON2bits.PC_Cop_FLAG && !WGCCON2bits.Send_FLAG) {//�������ͨѶ�׶λ��Ƿ������ݵĻ�����ô������ѭ��
            U1MODEbits.WAKE = 1;
            Sleep();
            U1MODEbits.WAKE = 1;
        }
        //        if (WGCCON2bits.PC_Cop_FLAG)
        //            Delay1s(1);
        //        U1MODEbits.WAKE = 1;
        //#ifdef DEBUG_RTCC_TIME
        //        while (!WGCCON2bits.SET_TIME_TEST_FLAG);
        //        if (WGCCON2bits.SET_TIME_TEST_FLAG) {
        //            WGCCON2bits.SET_TIME_TEST_FLAG = 0; //�����־λ
        //            RS485SendString1("\r\n/*********************************************************\r\n");
        //            RS485SendString1("Nt:");
        //            PrintTime(); //��ӡ��ǰʱ��
        //            //            RS485SendString("\tSetting Alarm Time is ", 12);
        //            printrtccArg();
        //            printnums(rtime);
        //            RS485SendString1("\r\n**********************************************************/\r\n");
        //        }
        //#endif
        //        CAT24C512_Write(0, "12S34567980124567890123456789");
        if (WGCCON2bits.Send_FLAG) {
            WGCCON2bits.Send_FLAG = 0;
            WGCCNTbits.Send_CNT++;
            GPRS_Task();
        }
        //        Delay100ms(1);
        //        LED_Toggle();
        //        if (WGCCON2bits.Sample_FLAG) {

        //            }
        //        }
        //                Delay1ms(1);
        //        LED_Toggle(); //  
        //        printf("Hello world%d,\n",123);
        //        NUMS_SHOW(nums++, 0);
        //        RS485SendString("Now time is ", 12);
        //        PrintTime();
    }
}


