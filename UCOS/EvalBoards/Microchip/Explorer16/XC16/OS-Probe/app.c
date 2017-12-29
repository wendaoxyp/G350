/*
*********************************************************************************************************
*                                               uC/OS-II
*                                         The Real-Time Kernel
*
*                               (c) Copyright 2006, Micrium, Weston, FL
*                                          All Rights Reserved
*
*
*                                      Microchip Application Code
*
* File : APP.C
* By   : Eric Shufo
*********************************************************************************************************
*/

#include <includes.h>
#include <xc.h>

/*
*********************************************************************************************************
*                                                CONSTANTS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                                VARIABLES
*********************************************************************************************************
*/

OS_STK  AppStartTaskStk[APP_TASK_START_STK_SIZE];
OS_STK  AppLCDTaskStk[APP_TASK_LCD_STK_SIZE];


/*
*********************************************************************************************************
*                                            FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static  void  AppStartTask(void *p_arg);
static  void  AppLCDTask(void *p_arg);
static  void  AppTaskCreate(void);

#if (uC_PROBE_OS_PLUGIN > 0) || (uC_PROBE_COM_MODULE > 0)
extern  void  AppProbeInit(void);
#endif


/*
*********************************************************************************************************
*                                                main()
*
* Description : This is the standard entry point for C code.
* Arguments   : none
*********************************************************************************************************
*/

CPU_INT16S  main (void)
{
    CPU_INT08U  err;


    BSP_IntDisAll();                                                    /* Disable all interrupts until we are ready to accept them */

    OSInit();                                                           /* Initialize "uC/OS-II, The Real-Time Kernel"              */

    OSTaskCreateExt(AppStartTask,
                    (void *)0,
                    (OS_STK *)&AppStartTaskStk[0],
                    APP_TASK_START_PRIO,
                    APP_TASK_START_PRIO,
                    (OS_STK *)&AppStartTaskStk[APP_TASK_START_STK_SIZE-1],
                    APP_TASK_START_STK_SIZE,
                    (void *)0,
                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);

#if OS_TASK_NAME_SIZE > 11
    OSTaskNameSet(APP_TASK_START_PRIO, (CPU_INT08U *)"Start Task", &err);
#endif

    OSStart();                                                          /* Start multitasking (i.e. give control to uC/OS-II)       */

	return (-1);                                                        /* Return an error - This line of code is unreachable       */
}


/*
*********************************************************************************************************
*                                          STARTUP TASK
*
* Description : This is an example of a startup task.  As mentioned in the book's text, you MUST
*               initialize the ticker only once multitasking has started.
*
* Arguments   : p_arg   is the argument passed to 'AppStartTask()' by 'OSTaskCreate()'.
*
* Notes       : 1) The first line of code is used to prevent a compiler warning because 'p_arg' is not
*                  used.  The compiler should not generate any code for this statement.
*               2) Interrupts are enabled once the task start because the I-bit of the CCR register was
*                  set to 0 by 'OSTaskCreate()'.
*********************************************************************************************************
*/

static  void  AppStartTask (void *p_arg)
{
    CPU_INT08U  i;
    CPU_INT08U  j;


   (void)p_arg;

    BSP_Init();                                                         /* Initialize BSP functions                                 */

#if OS_TASK_STAT_EN > 0
    OSStatInit();                                                       /* Determine CPU capacity                                   */
#endif

#if (uC_PROBE_OS_PLUGIN > 0) || (uC_PROBE_COM_MODULE > 0)
    AppProbeInit();                                                     /* Initialize uC/Probe modules                              */
#endif

    AppTaskCreate();                                                    /* Create additional user tasks                             */

    LED_Off(0);                                                         /* Turn OFF all the LEDs                                    */

    while (DEF_TRUE) {                                                  /* Task body, always written as an infinite loop.           */
        for (i = 0; i < 4; i++) {                                       /* Sweep right then left 4 times                            */
    		for (j = 1; j <= 8; j++) {			                        /* Scroll the LEDs to the right	                            */
    			LED_On(j);
    			OSTimeDlyHMSM(0, 0, 0, 25);                             /* Delay 25ms                                               */
    			LED_Off(j);
    		} 	

    		for (j = 7; j >= 2; j--) {                                  /* Scroll the LEDs to the left 	                            */
    			LED_On(j);
    			OSTimeDlyHMSM(0, 0, 0, 25);
    			LED_Off(j);
    		}
        }

		for (i = 0; i < 4; i++) {                                       /* Blink all 8 LEDs 4 times                                 */
			LED_On(0);
			OSTimeDlyHMSM(0, 0, 0, 25);
			LED_Off(0);
			OSTimeDlyHMSM(0, 0, 0, 25);
		}
    }


}


/*
*********************************************************************************************************
*                                          LCD TASK
*
* Description : This example task writes messages to the Explorer16 LCD screen.
*
* Arguments   : p_arg   is the argument passed to 'AppStartTask()' by 'OSTaskCreate()'.
*
* Notes       : 1) The first line of code is used to prevent a compiler warning because 'p_arg' is not
*                  used.  The compiler should not generate any code for this statement.
*               2) Interrupts are enabled once the task start because the I-bit of the CCR register was
*                  set to 0 by 'OSTaskCreate()'.
*********************************************************************************************************
*/

static  void  AppLCDTask (void *p_arg)
{
       CPU_INT08S  i;
       CPU_INT08U  buf[17];
       CPU_INT32U  value;
                                                                /* Power On Welcome Message. 3 msg's, 2 rows each.      */
const  CPU_INT08U  welcome_str[12][17] = {"Welcome to the  ",
                                          "Explorer 16 EVB.",
                                          "This demo is    ",
                                          "running uC/OS-II",
                                          "and uC/Probe on ",
                                          "the Microchip   ",
                                          "PIC CPU.    ",
                                          "Please visit:   ",
                                          "www.micrium.com ",
                                          "to download     ",
                                          "uC/Probe for use",
                                          "with this demo. "};


   (void)p_arg;

    DispInit(2, 16);                                            /* Initialize uC/LCD for a 2 row by 16 column display.  */


    DispClrScr();                                               /* Clear the screen.                                    */

    for (i = 0; i < 12; i+=2) {										
        DispStr(0, 0, (CPU_INT08U *)welcome_str[i]);            /* Display row 0 of Welcome Message i.                  */
        DispStr(1, 0, (CPU_INT08U *)welcome_str[i+1]);          /* Display row 1 of Welcome Message i.                  */
        OSTimeDlyHMSM(0, 0, 2, 0);                              /* Delay between updating the message.                  */
    }

    Str_Copy(buf, (CPU_INT08U *)"uC/OS-II: Vx.yy ");
    value    = (CPU_INT32U)OSVersion();
    buf[11]  = (value / 100) + '0';
    buf[13]  = (value % 100) / 10 + '0';
    buf[14]  = (value %  10) + '0';
    DispStr(0, 0, buf);

    Str_Copy(buf, (CPU_INT08U *)"CPU Speed: xxMHz");
    value    = (CPU_INT32U)BSP_CPU_ClkFrq() / 1000000L;
    buf[11]  = (value / 10) + '0';
    buf[12]  = (value % 10) + '0';
    DispStr(1, 0, buf);

    OSTimeDlyHMSM(0, 0, 2, 0);

    while (DEF_TRUE) {                                          /* All tasks bodies include an infinite loop.           */
        Str_Copy(buf, (CPU_INT08U *)"CPU Usage: xxx %");
        value    = (CPU_INT32U)OSCPUUsage;
        buf[11]  = (value / 100)      + '0';
        buf[12]  = (value % 100) / 10 + '0';
        buf[13]  = (value      ) % 10 + '0';
        DispStr(0, 0, buf);

        Str_Copy(buf, (CPU_INT08U *)"OSCtxSw: ");
        value    = (CPU_INT32U)OSCtxSwCtr;
        sprintf((char *)&buf[9], "%ld", value);
        DispClrLine(1);
        DispStr(1, 0, buf);

        OSTimeDlyHMSM(0, 0, 0, 100);
     }
}


/*
*********************************************************************************************************
*                              CREATE ADDITIONAL APPLICATION TASKS
*********************************************************************************************************
*/

static  void  AppTaskCreate (void)
{
    CPU_INT08U  err;


    OSTaskCreateExt(AppLCDTask,
                    (void *)0,
                    (OS_STK *)&AppLCDTaskStk[0],
                    APP_TASK_LCD_PRIO,
                    APP_TASK_LCD_PRIO,
                    (OS_STK *)&AppLCDTaskStk[APP_TASK_LCD_STK_SIZE-1],
                    APP_TASK_LCD_STK_SIZE,
                    (void *)0,
                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);

#if OS_TASK_NAME_SIZE > 11
    OSTaskNameSet(APP_TASK_LCD_PRIO, (CPU_INT08U *)"LCD Task", &err);
#endif
}


