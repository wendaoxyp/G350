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
*                                      Communication: RS-232
*                                  Port for the Microchip dsPIC33/PIC24
*
* Filename      : probe_rs232c.c
* Version       : V1.00
* Programmer(s) : Eric Shufro
*********************************************************************************************************
*/

#include  <includes.h>
#include  <probe_rs232.h>
#include  <probe_com_cfg.h>

/*
*********************************************************************************************************
*                                              CONSTANTS
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                        FUNCTION PROTOTYPES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                       Initialize COM port for uC/Probe RS-232 Communication Module
*
* Description: Initialize UART2 for uC/Probe communication.
*
* Argument(s): baud    intended baud rate of the RS-232 channel.
*
* Returns    : None
*
* Note(s)    : 1) The UART must be enabled (U2MODE Register) before it may be configured. Otherwise,
*                 improper operation will result.
*********************************************************************************************************
*/

void  ProbeRS232_InitTarget (CPU_INT32U baud)
{
    CPU_INT32U  fcy;
    CPU_INT32U  baud_div;


    fcy              	=  BSP_CPU_ClkFrq();                                /* Get the Fcy frequency which drives the UART			*/

#if (PROBE_RS232_COMM_SEL == PROBE_RS232_UART_2)
    baud_div            = (fcy / (16 * baud)) - 1;                          /* Compute divisor for desired baud rate                */
    U2BRG	            = (CPU_INT16U)baud_div;

	U2MODE              =  UART_EN;                                         /* Enable the UART with the parameters 8N1              */

    U2STA               =  UTXEN | UTXISEL;                                 /* Enable the transmitter, configure the Tx and Rx      */
                                                                            /* interrupt modes, but do not enable interrupts        */
                                                                            /* Tx Interrupt Mode is set for Tx Shift Reg Empty      */
                                                                            /* Rx Interrupt Mode is set to Interrupt for each Rx    */

    IFS1               &= ~(U2TXIF | U2RXIF);                               /* Clear pending interrupts                             */
    IPC6               &= ~U2TXIP_MASK;                                     /* Clear the UART2 Tx priority bits                     */
    IPC6               &= ~U2RXIP_MASK;                                     /* Clear the UART2 Rx priority bits                     */
    IPC6               |= (PROBE_INT_PRIO << 0) | (PROBE_INT_PRIO << 4);    /* Configure the UART2 Rx and Tx interrupt priorities   */
#endif                                                                      /* See bsp.h                                            */
}

/*
*********************************************************************************************************
*                                 Rx and Tx Communication Handler
*
* Description: This function handles both Rx and Tx interrupts.
*
* Argument(s): None
*
* Returns    : None
*
* Note(s)    : 1) This function has been intentionally left empty since individual handlers
*                 have been configured for each SCI event.
*********************************************************************************************************
*/

void  ProbeRS232_RxTxISRHandler (void)
{
}

/*
*********************************************************************************************************
*                                 Rx Communication Handler
*
* Description: This functions handle Rx interrupts
*
* Argument(s): None
*
* Returns    : None
*
* Note(s)    : 1) The interrupt source is clearned by __U2RXInterrupt located in probe_rs232a.s
*              2) When changing the value of PROBE_RS232_COMM_SEL from within probe_com_cfg.h
*                 the file probe_rs232a.s will have to be adjusted accordingly.
*********************************************************************************************************
*/

void  ProbeRS232_RxISRHandler (void)
{
#if (PROBE_RS232_COMM_SEL == PROBE_RS232_UART_2)
    IFS1 &= ~U2RXIF;                                                    /* Clear the interrupt flag                                 */
    ProbeRS232_RxHandler(U2RXREG);                                      /* Call the generic Rx handler with the received data       */
#endif
}

/*
*********************************************************************************************************
*                                 Tx Communication Handler
*
* Description: This functions handle Tx interrupts
*
* Argument(s): None
*
* Returns    : None
*
* Note(s)    : 1) The interrupt source is clearned by __U2TXInterrupt located in probe_rs232a.s
*              2) When changing the value of PROBE_RS232_COMM_SEL from within probe_com_cfg.h
*                 the file probe_rs232a.s will have to be adjusted accordingly.
*********************************************************************************************************
*/

void  ProbeRS232_TxISRHandler (void)
{
#if (PROBE_RS232_COMM_SEL == PROBE_RS232_UART_2)
    IFS1 &= ~U2TXIF;                                                    /* Clear the interrupt flag                                 */
    ProbeRS232_TxHandler();                                             /* Call the generic Tx complete handler                     */
#endif
}

/*
*********************************************************************************************************
*                                      Transmit One Byte
*
* Description: This function transmits one byte.
*
* Argument(s): c   byte to transmit.
*
* Returns    : None
*********************************************************************************************************
*/

void  ProbeRS232_Tx1 (CPU_INT08U c)
{
#if (PROBE_RS232_COMM_SEL == PROBE_RS232_UART_2)
    U2TXREG = c;
#endif
}

/*
*********************************************************************************************************
*                                      Enable/disable Tx Interrupts
*
* Description: Enable or disable Tx interrupts.
*
* Argument(s): None
*
* Returns    : None
*********************************************************************************************************
*/

void  ProbeRS232_TxIntDis (void)
{
#if (PROBE_RS232_COMM_SEL == PROBE_RS232_UART_2)
    IEC1   &= ~U2TXIE;                                                  /* Disable Tx interrupts				                    */
#endif
}

void  ProbeRS232_TxIntEn (void)
{
#if (PROBE_RS232_COMM_SEL == PROBE_RS232_UART_2)
    IEC1   |=  U2TXIE;                                                  /* Enable Tx interrupts			                            */
#endif
}


/*
*********************************************************************************************************
*                                      Enable/disable Rx Interrupts
*
* Description: Enable or disable Rx interrupts.
*
* Argument(s): None
*
* Returns    : None
*********************************************************************************************************
*/

void  ProbeRS232_RxIntDis (void)
{
#if (PROBE_RS232_COMM_SEL == PROBE_RS232_UART_2)
    IEC1    &= ~U2RXIE;                                                 /* Disable Rx Interrupts                                    */
#endif
}

void  ProbeRS232_RxIntEn (void)
{
#if (PROBE_RS232_COMM_SEL == PROBE_RS232_UART_2)
    IEC1    |=  U2RXIE;                                                 /* Enable Rx interrupts				                        */
#endif
}
