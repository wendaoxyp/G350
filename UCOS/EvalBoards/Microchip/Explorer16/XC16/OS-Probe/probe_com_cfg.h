/*
*********************************************************************************************************
*                                      uC/Probe Communication
*
*                           (c) Copyright 2007; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*               Knowledge of the source code may NOT be used to develop a similar product.
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                              uC/Probe
*
*                                     Communication: Configuration
*
* Filename      : probe_com_cfg.h
* Version       : V1.00
* Programmer(s) : Brian Nagel
* Note(s)       : (1) This file contains configuration constants for uC/Probe Communication Modules.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                    CHOOSE COMMUNICATION METHOD
*********************************************************************************************************
*/

#define  PROBE_COM_METHOD_RS232           DEF_TRUE

/*
*********************************************************************************************************
*                            CONFIGURE GENERAL COMMUNICATION PARAMETERS
*********************************************************************************************************
*/

#define  PROBE_COM_RX_MAX_SIZE               64
#define  PROBE_COM_TX_MAX_SIZE               64

#define  PROBE_COM_SUPPORT_WR              DEF_TRUE
#define  PROBE_COM_SUPPORT_STR             DEF_TRUE

#if     (PROBE_COM_SUPPORT_STR  == DEF_TRUE)                            /* If strings are supported                                 */
#define  PROBE_COM_STR_BUF_SIZE             128                         /*   (a) Set size of string buffer                          */
#endif

/*
*********************************************************************************************************
*                               CONFIGURE STATISTICS AND COUNTERS
*********************************************************************************************************
*/

#define  PROBE_COM_STAT_EN                 DEF_ENABLED

/*
*********************************************************************************************************
*                              CONFIGURE RS-232 SPECIFIC PARAMETERS
*********************************************************************************************************
*/

#if     (PROBE_COM_METHOD_RS232 == DEF_TRUE)                            /* For the RS-232 communication method                      */

#define  PROBE_RS232_PARSE_TASK            DEF_TRUE                     /*  (a) Set whether a task will handle parsing              */

#if     (PROBE_RS232_PARSE_TASK == DEF_TRUE)                            /*  (b) If a task will handle parsing                       */
#define  PROBE_RS232_TASK_PRIO                9                         /*       (i) Set task priority                              */
#define  PROBE_RS232_TASK_STK_SIZE          160                        /*      (ii) Set task stack size                            */
#endif


#define  PROBE_RS232_RX_BUF_SIZE       PROBE_COM_RX_MAX_SIZE            /*  (c) Set Rx buffer size                                  */
#define  PROBE_RS232_TX_BUF_SIZE       PROBE_COM_TX_MAX_SIZE            /*  (d) Set Tx buffer size                                  */

#define  PROBE_RS232_UART_0                   1
#define  PROBE_RS232_UART_1                   2
#define  PROBE_RS232_UART_2                   3
#define  PROBE_RS232_UART_3                   4
#define  PROBE_RS232_UART_4                   5
#define  PROBE_RS232_UART_5                   6
#define  PROBE_RS232_UART_6                   7
#define  PROBE_RS232_UART_7                   8
#define  PROBE_RS232_UART_8                   9
#define  PROBE_RS232_UART_9                  10
#define  PROBE_RS232_UART_DBG                63
#define  PROBE_RS232_COMM_SEL           PROBE_RS232_UART_2              /*  (e) Configure UART selection                            */

#endif
