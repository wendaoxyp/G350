/*
*********************************************************************************************************
*                                               Microchip PIC33
*                                            Board Support Package
*
*                                                    Micrium
*                                    (c) Copyright 2005, Micrium, Weston, FL
*                                              All Rights Reserved
*
*
* File : BSP.H
* By   : Eric Shufro
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                      OSCILLATOR FREQUENCIES
*********************************************************************************************************
*/

#define  CPU_PRIMARY_OSC_FRQ         8000000L                               /* Primary External Oscillator Frequency                */
#define  CPU_FRC_OSC_FRQ             7370000L                               /* Internal Fast Oscillator Frequency                   */
#define  CPU_SECONDARY_OSC_FRQ         32768L                               /* Secondary External Oscillator Frequency              */
#define  CPU_LOW_POWER_OSC_FRQ         31000L                           /* Low Power Oscillator (LPOSC) 31Khz Nominal               */

/*
*********************************************************************************************************
*                                      OS TICK TIMER SELECTION
*********************************************************************************************************
*/

#define  BSP_OS_TMR_SEL                    2                                /* Select a timer for the OS Tick Interrupt (2 or 4)    */
#define  TIMER_INT_PRIO                    4                                /* Configure the timer to use interrupt priority 4      */
#define  PROBE_INT_PRIO                    4                                /* Configure UART2 Interrupts to use priority 4         */

/*
*********************************************************************************************************
*                                             DATATYPES
*********************************************************************************************************
*/

typedef  void (*PFNCT)(void);

/*
*********************************************************************************************************
*                                             MACROS
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                       CHIP SPECIFIC MACROS
*********************************************************************************************************
*/
                                                                        /* OSCCON register bits                                     */
#define  XT_HS_EC_PLL_SEL           (CPU_INT16U)(3 <<  0)
#define  COSC_MASK                  (CPU_INT16U)(7 << 12)
#define  LOCK                       (CPU_INT16U)(1 <<  5)
#define  OSWEN                      (CPU_INT16U)(1 <<  0)
                                                                        /* CLKDIV register bits                                     */
#define  FRCDIV_MASK                (CPU_INT16U)(7 <<  8)
#define  PLLPOST_MASK               (CPU_INT16U)(3 <<  6)
#define  PLLPRE_MASK                (CPU_INT16U)(0x1F <<  0)
#define  PLLDIV_MASK                (CPU_INT16U)(0xFF <<  0)
                                                                        /* Timer Control register bits                              */
#define  TON                        (CPU_INT16U)(1 << 15)
                                                                        /* IPC1 Interrupt Priority register bits                    */
#define  T2IP_MASK                  (CPU_INT16U)(7 << 12)
                                                                        /* IPC5 Interrupt Priority register bits                    */
#define  T4IP_MASK                  (CPU_INT16U)(7 << 12)
                                                                        /* IPC7 Interrupt Priority register bits                    */
#define  U2TXIP_MASK                (CPU_INT16U)(7 << 12)
#define  U2RXIP_MASK                (CPU_INT16U)(7 <<  8)
                                                                        /* IEC0 Interrupt Enable register bits                      */
#define  T2IE                       (CPU_INT16U)(1 <<  7)
                                                                        /* IEC1 Interrupt Enable register bits                      */
#define  T4IE                       (CPU_INT16U)(1 << 11)
#define  U2TXIE                     (CPU_INT16U)(1 << 15)
#define  U2RXIE                     (CPU_INT16U)(1 << 14)
                                                                        /* IFS0 Interrupt Flag register bits                        */
#define  T2IF                       (CPU_INT16U)(1 <<  7)
                                                                        /* IFS1 Interrupt Flag register bits                        */
#define  T4IF                       (CPU_INT16U)(1 << 11)
#define  U2TXIF                     (CPU_INT16U)(1 << 15)
#define  U2RXIF                     (CPU_INT16U)(1 << 14)
                                                                        /* UxMODE register bits                                     */
#define  UART_EN                    (CPU_INT16U)(1 << 15)
                                                                        /* UxSTA register  bits                                     */
#define  UTXISEL                    (CPU_INT16U)(1 << 15)
#define  UTXEN                      (CPU_INT16U)(1 << 10)
#define  TRMT                       (CPU_INT16U)(1 <<  8)
#define  URXDA                      (CPU_INT16U)(1 <<  0)

                                                                        /* System Control register bits                             */
#define  SWDTEN                     (CPU_INT16U)(1 <<  5)

                                                                        /* Interrupt Configuration register 1 bits                  */
#define  NSTDIS                     (CPU_INT16U)(1 << 15)

/*
*********************************************************************************************************
*                                       FUNCTION PROTOTYPES
*********************************************************************************************************
*/

void        BSP_Init(void);
void        BSP_IntEn(CPU_INT08U IntCont, CPU_INT08U IntNum, CPU_INT08U IntPol, CPU_INT08U IntAct, PFNCT pfnct);
void        BSP_IntDis(CPU_INT08U IntCont, CPU_INT08U IntNum);
void        BSP_IntDisAll(void);

CPU_INT32U  BSP_CPU_ClkFrq(void);

/*
*********************************************************************************************************
*                                          LED SERVICES
*********************************************************************************************************
*/

void     LED_Init(void);
void     LED_On(CPU_INT08U led);
void     LED_Off(CPU_INT08U led);
void     LED_Toggle(CPU_INT08U led);

/*
*********************************************************************************************************
*                                          TICK SERVICES
*********************************************************************************************************
*/

void     Tmr_TickISR_Handler(void);

/*
*********************************************************************************************************
*                                      CONFIGURATION CHECKING
*********************************************************************************************************
*/

#if ((BSP_OS_TMR_SEL != 2) && (BSP_OS_TMR_SEL != 4))
#error "BSP_OS_TMR_SEL is illegally defined in bsp.h. Allowed values: 2 or 4"
#endif
