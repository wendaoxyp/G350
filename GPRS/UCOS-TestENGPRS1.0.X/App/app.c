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
//#include <xc.h>
//#include <Configuration Bit.h>
int FBS __attribute__((space(prog), address(0xF80000))) = 0xF;
//_FBS(
//    BWRP_OFF &           // Boot Segment Write Protect (Disabled)
//    BSS_OFF              // Boot segment Protect (No boot program flash segment)
//);
int FGS __attribute__((space(prog), address(0xF80004))) = 0x3;
//_FGS(
//    GWRP_OFF &           // General Segment Write Protect (General segment may be written)
//    GSS0_OFF             // General Segment Code Protect (No Protection)
//);
int FOSCSEL __attribute__((space(prog), address(0xF80006))) = 0xF0; //0x5E;//0xBC ;
//_FOSCSEL(
//    FNOSC_LPFRC &        // Oscillator Select (500kHz Low-Power FRC oscillator with Postscaler(LPFRCDIV))
//    SOSCSRC_DIG &        // SOSC Source Type (Digital Mode for use with external source)
//    LPRCSEL_HP &         // LPRC Oscillator Power and Accuracy (High Power, High Accuracy Mode)
//    IESO_OFF             // Internal External Switch Over bit (Internal External Switchover mode disabled (Two-speed Start-up disabled))
//);
int FOSC __attribute__((space(prog), address(0xF80008))) = 0x33; //;0x70     3B
//_FOSC(
//    POSCMOD_NONE &       // Primary Oscillator Configuration bits (Primary oscillator disabled)
//    OSCIOFNC_OFF &       // CLKO Enable Configuration bit (CLKO output disabled)
//    POSCFREQ_HS &        // Primary Oscillator Frequency Range Configuration bits (Primary oscillator/external clock input frequency greater than 8MHz)
//    SOSCSEL_SOSCHP &     // SOSC Power Selection Configuration bits (Secondary Oscillator configured for high-power operation)
//    FCKSM_CSDCME         // Clock Switching and Monitor Selection (Both Clock Switching and Fail-safe Clock Monitor are enabled)
//);
int FWDT __attribute__((space(prog), address(0xF8000A))) = 0x5F; //DF
//_FWDT(
//    WDTPS_PS32768 &      // Watchdog Timer Postscale Select bits (1:32768)
//    FWPSA_PR128 &        // WDT Prescaler bit (WDT prescaler ratio of 1:128)
//    FWDTEN_SWON &        // Watchdog Timer Enable bits (WDT controlled with the SWDTEN bit setting)
//    WINDIS_OFF           // Windowed Watchdog Timer Disable bit (Standard WDT selected(windowed WDT disabled))
//);

int FPOR __attribute__((space(prog), address(0xF8000C))) = 0xFC; //0xBB ;//0xFF//0xFC
//_FPOR(
//    BOREN_BOR3 &         // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware, SBOREN bit disabled)
//    LVRCFG_ON &          // Low Voltage Regulator Configuration bit (Low Voltage regulator is available and controlled by LVREN bit)
//    PWRTEN_ON &          // Power-up Timer Enable bit (PWRT enabled)
//    I2C1SEL_PRI &        // Alternate I2C1 Pin Mapping bit (Use Default SCL1/SDA1 Pins For I2C1)
//    BORV_V30 &           // Brown-out Reset Voltage bits (Brown-out Reset set to Highest Voltage (3.0V))
//    MCLRE_ON             // MCLR Pin Enable bit (RA5 input pin disabled,MCLR pin enabled)
//);
int FICD __attribute__((space(prog), address(0xF8000E))) = 0x82;
//_FICD(
//    ICS_PGx2             // ICD Pin Placement Select bits (EMUC/EMUD share PGC2/PGD2)
//);

int FDS __attribute__((space(prog), address(0xF80010))) = 0x1F; //0x1F ;
//_FDS(
//    DSWDTPS_DSWDTPSF &   // Deep Sleep Watchdog Timer Postscale Select bits (1:2,147,483,648 (25.7 Days))
//    DSWDTOSC_LPRC &      // DSWDT Reference Clock Select bit (DSWDT uses Low Power RC Oscillator (LPRC))
//    DSBOREN_ON &         // Deep Sleep Zero-Power BOR Enable bit (Deep Sleep BOR enabled in Deep Sleep)
//    DSWDTEN_OFF          // Deep Sleep Watchdog Timer Enable bit (DSWDT disabled)
//);    
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

OS_STK AppStartTaskStk[128];
//OS_STK  AppLCDTaskStk[128];


/*
 *********************************************************************************************************
 *                                            FUNCTION PROTOTYPES
 *********************************************************************************************************
 */

static void AppStartTask(void *p_arg);
//static  void  AppLCDTask(void *p_arg);
static void AppTaskCreate(void);

#if (uC_PROBE_OS_PLUGIN > 0) || (uC_PROBE_COM_MODULE > 0)
extern void AppProbeInit(void);
#endif

/*
 *********************************************************************************************************
 *                                                main()
 *
 * Description : This is the standard entry point for C code.
 * Arguments   : none
 *********************************************************************************************************
 */

CPU_INT16S main(void) {
    CPU_INT08U err;


    BSP_IntDisAll(); /* Disable all interrupts until we are ready to accept them */

    OSInit(); /* Initialize "uC/OS-II, The Real-Time Kernel"              */

    OSTaskCreateExt(AppStartTask,
            (void *) 0,
            (OS_STK *) & AppStartTaskStk[0],
            2,
            2,
            (OS_STK *) & AppStartTaskStk[127],
            128,
            (void *) 0,
            OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);

#if OS_TASK_NAME_SIZE > 11
    OSTaskNameSet(APP_TASK_START_PRIO, (CPU_INT08U *) "Start Task", &err);
#endif

    OSStart(); /* Start multitasking (i.e. give control to uC/OS-II)       */

    return (-1); /* Return an error - This line of code is unreachable       */
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

static void AppStartTask(void *p_arg) {
//    CPU_INT08U i;
//    CPU_INT08U j;


    (void) p_arg;

    BSP_Init(); /* Initialize BSP functions                                 */

#if OS_TASK_STAT_EN > 0
    OSStatInit(); /* Determine CPU capacity                                   */
#endif

#if (uC_PROBE_OS_PLUGIN > 0) || (uC_PROBE_COM_MODULE > 0)
    AppProbeInit(); /* Initialize uC/Probe modules                              */
#endif

    //    AppTaskCreate();                                                    /* Create additional user tasks                             */

    LED_On(1); /* Turn OFF all the LEDs                                    */

    while (1) { /* Task body, always written as an infinite loop.           */
//        for (j = 1; j <= 8; j++) {/* Scroll the LEDs to the right	                            */
            LED_Toggle(1);
            OSTimeDlyHMSM(0, 0, 0, 500); /* Delay 25ms                                               */
//            LED_Off(1);
//        }
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

//static  void  AppLCDTask (void *p_arg)
//{
//       CPU_INT08S  i;
//       CPU_INT08U  buf[17];
//       CPU_INT32U  value;
//                                                                /* Power On Welcome Message. 3 msg's, 2 rows each.      */
//const  CPU_INT08U  welcome_str[12][17] = {"Welcome to the  ",
//                                          "Explorer 16 EVB.",
//                                          "This demo is    ",
//                                          "running uC/OS-II",
//                                          "and uC/Probe on ",
//                                          "the Microchip   ",
//                                          "PIC CPU.    ",
//                                          "Please visit:   ",
//                                          "www.micrium.com ",
//                                          "to download     ",
//                                          "uC/Probe for use",
//                                          "with this demo. "};
//
//
//   (void)p_arg;
//
//    DispInit(2, 16);                                            /* Initialize uC/LCD for a 2 row by 16 column display.  */
//
//
//    DispClrScr();                                               /* Clear the screen.                                    */
//
//    for (i = 0; i < 12; i+=2) {										
//        DispStr(0, 0, (CPU_INT08U *)welcome_str[i]);            /* Display row 0 of Welcome Message i.                  */
//        DispStr(1, 0, (CPU_INT08U *)welcome_str[i+1]);          /* Display row 1 of Welcome Message i.                  */
//        OSTimeDlyHMSM(0, 0, 2, 0);                              /* Delay between updating the message.                  */
//    }
//
//    Str_Copy(buf, (CPU_INT08U *)"uC/OS-II: Vx.yy ");
//    value    = (CPU_INT32U)OSVersion();
//    buf[11]  = (value / 100) + '0';
//    buf[13]  = (value % 100) / 10 + '0';
//    buf[14]  = (value %  10) + '0';
//    DispStr(0, 0, buf);
//
//    Str_Copy(buf, (CPU_INT08U *)"CPU Speed: xxMHz");
//    value    = (CPU_INT32U)BSP_CPU_ClkFrq() / 1000000L;
//    buf[11]  = (value / 10) + '0';
//    buf[12]  = (value % 10) + '0';
//    DispStr(1, 0, buf);
//
//    OSTimeDlyHMSM(0, 0, 2, 0);
//
//    while (1) {                                          /* All tasks bodies include an infinite loop.           */
//        Str_Copy(buf, (CPU_INT08U *)"CPU Usage: xxx %");
//        value    = (CPU_INT32U)OSCPUUsage;
//        buf[11]  = (value / 100)      + '0';
//        buf[12]  = (value % 100) / 10 + '0';
//        buf[13]  = (value      ) % 10 + '0';
//        DispStr(0, 0, buf);
//
//        Str_Copy(buf, (CPU_INT08U *)"OSCtxSw: ");
//        value    = (CPU_INT32U)OSCtxSwCtr;
//        sprintf((char *)&buf[9], "%ld", value);
//        DispClrLine(1);
//        DispStr(1, 0, buf);
//
//        OSTimeDlyHMSM(0, 0, 0, 100);
//     }
//}


/*
 *********************************************************************************************************
 *                              CREATE ADDITIONAL APPLICATION TASKS
 *********************************************************************************************************
 */

//static  void  AppTaskCreate (void)
//{
//    CPU_INT08U  err;
//
//
//    OSTaskCreateExt(AppLCDTask,
//                    (void *)0,
//                    (OS_STK *)&AppLCDTaskStk[0],
//                    3,
//                    3,
//                    (OS_STK *)&AppLCDTaskStk[127],
//                    128,
//                    (void *)0,
//                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);
//
//#if OS_TASK_NAME_SIZE > 11
//    OSTaskNameSet(APP_TASK_LCD_PRIO, (CPU_INT08U *)"LCD Task", &err);
//#endif
//}


