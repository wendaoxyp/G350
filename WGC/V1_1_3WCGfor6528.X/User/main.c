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

//#include "HL6528.h"
//#include "UART.h"
//#include <xc.h>
//#include "mcc_generated_files/mcc.h"
//volatile uint8_t TMR1_CNT;


uint8_t WGC_sta;
OS_STK LEDStk[128];
OS_STK HL6528Stk[256]; //mark
OS_STK E41Stk[256];
OS_STK Tsk7[256]; //��������
//OS_STK I2CStk[128];
//OS_STK U485Stk[128];
//OS_STK SLPStk[32];
//OS_STK PCCopStk[32];
OS_EVENT *sem_set_alarm, *sem_get_pressure, *sem_send_pressure, *sem_receive_pressure, *sem_mutex;
//OS_EVENT* E41_Dat; //, *sem2;
//OS_FLAG_GRP *sem_F;

static void Task1Led(void* p_arg);
//static void Task2CopGPRS(void* p_arg);
static void Task2UseHL6528(void *p_arg);
static void Task3UseE41(void *parg);
static void Task4Use485(void *parg);
static void Task5TestI2C(void* parg);
static void Task6Sleep(void* p_arg);
static void Task7SetAlarm(void *p_arg);
extern I2C1_Buffer i2c_buf;
extern volatile uint8_t i2c1_state;

/*
                         Main application
 */
CPU_INT16S main(void) {
    // initialize the device
    //    SYSTEM_Initialize();
    //    TMR1_Stop();
    //    TMR1_Stop();
    INT8U err;
    BSP_Init(); //�ײ�������ʼ��

    OSInit();
    sem_send_pressure = OSSemCreate(0);
    sem_get_pressure = OSSemCreate(0);
    sem_receive_pressure = OSSemCreate(0);
    sem_set_alarm = OSSemCreate(0);
    //    sem_mutex = OSMutexCreate(0);
    //    sem_F = OSFlagCreate(0, &err);
    //    sem2 = OSSemCreate(0);
    //    E41_Dat = OSMboxCreate((void*) 0);
    //    sem2 = OSSemCreate(1);

    OSTaskCreate(Task1Led, (void*) 0, (OS_STK *) & LEDStk[0], 3);
    OSTaskCreate(Task7SetAlarm, (void*) 0, (OS_STK*) & Tsk7[0], 4);
    OSTaskCreate(Task3UseE41, (void*) 0, (OS_STK*) & E41Stk[0], 5);
    OSTaskCreate(Task2UseHL6528, (void*) 0, (OS_STK *) & HL6528Stk[0], 6); //mark
    //    OSTaskCreate(Task4Use485, (void*) 0, (OS_STK *) & U485Stk[0], 4);
    //    OSTaskCreate(Task5TestI2C, (void*) 0, (OS_STK*) & I2CStk[0], 6);
    //    OSTaskCreate(Task6Sleep, (void*) 0, (OS_STK*) & SLPStk[0], 8);
    OSStart();
    return -1;

}

/**
 End of File
 */

void Task1Led(void* p_arg) {
    INT8U err;
    //    uint8_t cnt = 0;
    //    OS_EVENT sem1;
    while (1) {
        //        PrintTime();
        switch (WGC_sta) {
            case 1://����˯��ģʽ
            {
                LED_Toggle();
                OSTimeDlyHMSM(0, 0, 1, 0); //��ʱ1s 
                break;
            }
            case 2://���߹���
            {
                LED_Toggle();
                OSTimeDlyHMSM(0, 0, 0, 500); //��ʱ1s  
                break;
            }
            case 3://��������
            {
                LED_On();
                OSTimeDlyHMSM(0, 0, 3, 0); //������������  
                break;
            }
            case 4://�ɼ�����
            {
                LED_Toggle();
                OSTimeDlyHMSM(0, 0, 0, 200); //��ʱ1s  
                break;
            }
            default://����ģʽ
            {
                LED_Toggle();
                err = OSTimeDlyHMSM(0, 0, 2, 0); //��ʱ1s  
                break;
            }

        }
    }
}

void Task2UseHL6528(void *p_arg) {
    INT8U err;
    //    uint8_t tmp[55];//���ڷ���IP��ַ�Ͷ˿ں�
    //    float press = 0;
    //    struct tm time2;
    //    time_t time3;
    //    uint8_t press[] = {0, 1, 2, 3};
    HL6528_Init(); /*Initialize the HL6528*/
    //    OSTimeDlyHMSM(0, 0, 5, 0);
    while (1) {
        OSSemPend(sem_send_pressure, 0, &err);
        UART2_Open();
        WGC_sta = 2; //GPRS����
        //        HL6528_GetIP_Port(tmp);
        if (!HL6528_DialingIsERR()) {
            WGC_sta = 3; //GPRS��������
            OSTimeDlyHMSM(0, 0, 1, 0); //��ʱ1s
            UART2_SendString("103.1");
            OSTimeDlyHMSM(0, 0, 1, 0); //��ʱ1s
        }
        HL6528_Close();
        WGC_sta = 0; //GPRS����
    }
}

void Task3UseE41(void *parg) {
    INT8U err;
    float f_dat;
    E41_Init();
    OSTimeDlyHMSM(0, 0, 1, 0); //��ʱ1s
    //    uint8_t E41_tmp[20] = {0x00, 0x01, 0x01, 0x12, 0x34};
    //    E41_SetArg(); //E41���ò���
    while (1) {
        OSSemPend(sem_get_pressure, 0, &err); //�ȴ������ɼ�ָ��
        E41_Active_Send();
        OSSemPend(sem_receive_pressure, 1000, &err);
        WGC_sta = 4;
        OSTimeDlyHMSM(0, 0, 3, 0); //��ʱ1s
        //        LED_Toggle();
        //        OSTimeDlyHMSM(0, 0, 0, 200);
        if (E41_PressureIsGet(&f_dat)) {
            OSSemPost(sem_send_pressure);
            //            OSMboxPost(E41_Dat, &f_dat); //ͨ�����䷢�����ݸ�������
        }
        WGC_sta = 0;
        //        UART3_SendString(E41_tmp, 5);
        //        OSTimeDlyHMSM(0, 0, 10, 0); //��ʱ1s
    }
}

//void Task4Use485(void *parg) {
//    parg = parg;
//    while (1) {
//        RS485SendChar(0x30);
//        //        RS485SendString("123", 3);
//        OSTimeDlyHMSM(0, 0, 1, 0);
//        //        OSSemPost(sem1);
//    }
//}

//void Task5UseCAT24C512(void* parg) {
//    INT8U err;
//    parg = parg; //��ֹ����������
//    CAT24C512_Init(); //Ӧ�ó����ʼ��
//
//    while (1) {
//        //�ȴ�ʹ�û������ź�
//        //ͨ�������жϴ洢���Ƕ�ȡ
//        //
////        OSMutexPost();
////        OSMutexPend();
////        OSMBoxPost
////        OSSemPend(sem2, 0, &err); //, 0, &err);
////        -(0, tmp2);
//    }
//}

//void Task6Sleep(void* p_arg) {
//    p_arg = p_arg;
//    LED_Off();
//    //    TRIS
//    while (1) {
//        DeepSleep();
//        OSSemPost(sem2); //, 0, &err);
//        //        Sleep();
//
//    }
//}
//

void Task7SetAlarm(void *p_arg) {
    INT8U err;
    //    static uint8_t tag_Time; //ʱ���ֵ
    //    uint8_t quotients, remainders; //�̺�����
    //    static uint8_t repeat_cnt = 0; //ѭ������
    time_t now_time;
    struct tm now_time1;
    //    struct WGC_ARG tmp_arg;
    WGC_sta = 0;
    //    uint8_t sta = 0; //״̬

    //    WGC_Get_Arg(&tmp_arg); //��ȡWGC����

    //    if (tmp_arg.Sample_Time >= tmp_arg.Send_Time[0]) {//����ѭ������
    //        quotients = remainders = 1;
    //    } else {
    //        quotients = tmp_arg.Send_Time[0] / tmp_arg.Sample_Time;
    //        remainders = tmp_arg.Send_Time[0] % tmp_arg.Sample_Time;
    //    }
    IFS3bits.RTCIF = 1; //��������һ�Σ������´�����ʱ��

    while (1) {
        OSSemPend(sem_set_alarm, 0, &err);
        PrintTime();
        while (!RTC_Read_Time(&now_time1)); //��ȡ��ǰʱ�� 
        now_time = mktime(&now_time1); //ת��Ϊ����ʱ��
        //        if (repeat_cnt >= quotients) {
        //            if (remainders)
        //                now_time += remainders; //���������������ϴ�ʱ��
        //            else
        //                now_time += 20;
        //            repeat_cnt = 0;
        //            //���¼���ɼ��ͷ���ʱ��
        //            if (tmp_arg.Sample_Time >= tmp_arg.Send_Time[0]) {//����ѭ������
        //                quotients = remainders = 1;
        //            } else {
        //                quotients = tmp_arg.Send_Time[0] / tmp_arg.Sample_Time;
        //                remainders = tmp_arg.Send_Time[0] % tmp_arg.Sample_Time;
        //            }
        //        } else {
        //            now_time += 15; //(unsigned int) (tmp_arg.Sample_Time) * 60; //�����´β��õ�ʱ��
        //            repeat_cnt += 1;
        //        }
        now_time += 300; //һ�����ж�һ��
        now_time1 = *gmtime(&now_time); //ת��Ϊ�ṹ��
        RTC_Set_Alarm(now_time1);
        OSSemPost(sem_get_pressure); //�����ɼ�
    }
}




