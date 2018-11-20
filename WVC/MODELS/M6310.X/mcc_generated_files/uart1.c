/**
  UART1 Generated Driver File 

  @Company
    Microchip Technology Inc.

  @File Name
    uart1.c

  @Summary
    This is the generated source file for the UART1 driver using Foundation Services Library

  @Description
    This source file provides APIs for driver for UART1. 
    Generation Information : 
        Product Revision  :  Foundation Services Library - pic24-dspic-pic32mm : v1.26
        Device            :  PIC24FJ64GA702
    The generated drivers are tested against the following:
        Compiler          :  XC16 1.30
        MPLAB 	          :  MPLAB X 3.45
 */

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
 */

/**
  Section: Included Files
 */

#include "uart1.h"
#include "../SerialBuffer.h"
/**
  Section: Data Type Definitions
 */

/** UART Driver Queue Status

  @Summary
    Defines the object required for the status of the queue.
 */

typedef union {

    struct {
        uint8_t full : 1;
        uint8_t empty : 1;
        uint8_t reserved : 6;
    } s;
    uint8_t status;
}

UART_BYTEQ_STATUS;

/** UART Driver Hardware Instance Object

  @Summary
    Defines the object required for the maintenance of the hardware instance.

 */
typedef struct {
    /* RX Byte Q */
    uint8_t *rxTail;

    uint8_t *rxHead;

    /* TX Byte Q */
    uint8_t *txTail;

    uint8_t *txHead;

    UART_BYTEQ_STATUS rxStatus;

    UART_BYTEQ_STATUS txStatus;

} UART_OBJECT;

static UART_OBJECT uart1_obj;

/** UART Driver Queue Length

  @Summary
    Defines the length of the Transmit and Receive Buffers

 */

#define UART1_CONFIG_TX_BYTEQ_LENGTH 64
#define UART1_CONFIG_RX_BYTEQ_LENGTH 64


/** UART Driver Queue

  @Summary
    Defines the Transmit and Receive Buffers

 */

static uint8_t uart1_txByteQ[UART1_CONFIG_TX_BYTEQ_LENGTH];
static uint8_t uart1_rxByteQ[UART1_CONFIG_RX_BYTEQ_LENGTH];

void (*UART1_TxDefaultInterruptHandler)(void);
void (*UART1_RxDefaultInterruptHandler)(void);

/**
  Section: Driver Interface
 */


void UART1_Initialize(void) {
    // STSEL 1; IREN disabled; PDSEL 8N; UARTEN enabled; RTSMD disabled; USIDL disabled; WAKE disabled; ABAUD disabled; LPBACK disabled; BRGH enabled; URXINV disabled; UEN TX_RX; 
    U1MODE = (0x8008 & ~(1 << 15)); // disabling UARTEN bit   
    // UTXISEL0 TX_ONE_CHAR; UTXINV disabled; URXEN disabled; OERR NO_ERROR_cleared; URXISEL RX_3_4_BUF_FULL; UTXBRK COMPLETED; UTXEN disabled; ADDEN disabled; 
    U1STA = 0x0080;
    // BaudRate = 19200; Frequency = 4000000 Hz; U1BRG 51; 
    U1BRG = 0x0033;
    // ADMADDR 0; ADMMASK 0; 
    U1ADMD = 0x0000;

    IEC0bits.U1RXIE = 1;
    UART1_SetRxInterruptHandler(UART1_Receive_ISR);
    UART1_SetTxInterruptHandler(UART1_Transmit_ISR);

    //Make sure to set LAT bit corresponding to TxPin as high before UART initialization
    U1MODEbits.UARTEN = 1; // enabling UART ON bit
    U1STAbits.UTXEN = 1;



    uart1_obj.txHead = uart1_txByteQ;
    uart1_obj.txTail = uart1_txByteQ;
    uart1_obj.rxHead = uart1_rxByteQ;
    uart1_obj.rxTail = uart1_rxByteQ;
    uart1_obj.rxStatus.s.empty = true;
    uart1_obj.txStatus.s.empty = true;
    uart1_obj.txStatus.s.full = false;
    uart1_obj.rxStatus.s.full = false;
}

/**
    Maintains the driver's transmitter state machine and implements its ISR
 */
void UART1_SetTxInterruptHandler(void* handler) {
    UART1_TxDefaultInterruptHandler = handler;
}

void __attribute__((interrupt, no_auto_psv)) _U1TXInterrupt(void) {
    (*UART1_TxDefaultInterruptHandler)();
}

void UART1_Transmit_ISR(void) {
    if (uart1_obj.txStatus.s.empty) {
        IEC0bits.U1TXIE = false;
        return;
    }

    IFS0bits.U1TXIF = false;

    while (!(U1STAbits.UTXBF == 1)) {

        U1TXREG = *uart1_obj.txHead;

        uart1_obj.txHead++;

        if (uart1_obj.txHead == (uart1_txByteQ + UART1_CONFIG_TX_BYTEQ_LENGTH)) {
            uart1_obj.txHead = uart1_txByteQ;
        }

        uart1_obj.txStatus.s.full = false;

        if (uart1_obj.txHead == uart1_obj.txTail) {
            uart1_obj.txStatus.s.empty = true;
            break;
        }
    }
}

void UART1_SetRxInterruptHandler(void* handler) {
    UART1_RxDefaultInterruptHandler = handler;
}

void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt(void) {
    // (*UART1_RxDefaultInterruptHandler)();
    uint8_t cnt;
    for (cnt = 0; cnt < 4; cnt++) {//read UART1 buffer
        if (U1STAbits.URXDA)
            BufferWrite_UART1();
    }
    IFS0bits.U1RXIF = false;
}

void UART1_Receive_ISR(void) {


    while ((U1STAbits.URXDA == 1)) {

        *uart1_obj.rxTail = U1RXREG;

        uart1_obj.rxTail++;

        if (uart1_obj.rxTail == (uart1_rxByteQ + UART1_CONFIG_RX_BYTEQ_LENGTH)) {
            uart1_obj.rxTail = uart1_rxByteQ;
        }

        uart1_obj.rxStatus.s.empty = false;

        if (uart1_obj.rxTail == uart1_obj.rxHead) {
            //Sets the flag RX full
            uart1_obj.rxStatus.s.full = true;
            break;
        }

    }

    IFS0bits.U1RXIF = false;

}

void __attribute__((interrupt, no_auto_psv)) _U1ErrInterrupt(void) {
    if ((U1STAbits.OERR == 1)) {
        U1STAbits.OERR = 0;
    }

    IFS4bits.U1ERIF = false;
}

/**
  Section: UART Driver Client Routines
 */

uint8_t UART1_Read(void) {
    uint8_t data = 0;

    data = *uart1_obj.rxHead;

    uart1_obj.rxHead++;

    if (uart1_obj.rxHead == (uart1_rxByteQ + UART1_CONFIG_RX_BYTEQ_LENGTH)) {
        uart1_obj.rxHead = uart1_rxByteQ;
    }

    if (uart1_obj.rxHead == uart1_obj.rxTail) {
        uart1_obj.rxStatus.s.empty = true;
    }

    uart1_obj.rxStatus.s.full = false;

    return data;
}

unsigned int UART1_ReadBuffer(uint8_t *buffer, unsigned int bufLen) {
    unsigned int numBytesRead = 0;
    while (numBytesRead < (bufLen)) {
        if (uart1_obj.rxStatus.s.empty) {
            break;
        } else {
            buffer[numBytesRead++] = UART1_Read();
        }
    }

    return numBytesRead;
}

void UART1_Write(uint8_t byte) {
    IEC0bits.U1TXIE = false;

    *uart1_obj.txTail = byte;

    uart1_obj.txTail++;

    if (uart1_obj.txTail == (uart1_txByteQ + UART1_CONFIG_TX_BYTEQ_LENGTH)) {
        uart1_obj.txTail = uart1_txByteQ;
    }

    uart1_obj.txStatus.s.empty = false;

    if (uart1_obj.txHead == uart1_obj.txTail) {
        uart1_obj.txStatus.s.full = true;
    }

    IEC0bits.U1TXIE = true;

}

unsigned int UART1_WriteBuffer(uint8_t *buffer, unsigned int bufLen) {
    unsigned int numBytesWritten = 0;

    while (numBytesWritten < (bufLen)) {
        if ((uart1_obj.txStatus.s.full)) {
            break;
        } else {
            UART1_Write(buffer[numBytesWritten++]);
        }
    }

    return numBytesWritten;

}

UART1_TRANSFER_STATUS UART1_TransferStatusGet(void) {
    UART1_TRANSFER_STATUS status = 0;

    if (uart1_obj.txStatus.s.full) {
        status |= UART1_TRANSFER_STATUS_TX_FULL;
    }

    if (uart1_obj.txStatus.s.empty) {
        status |= UART1_TRANSFER_STATUS_TX_EMPTY;
    }

    if (uart1_obj.rxStatus.s.full) {
        status |= UART1_TRANSFER_STATUS_RX_FULL;
    }

    if (uart1_obj.rxStatus.s.empty) {
        status |= UART1_TRANSFER_STATUS_RX_EMPTY;
    } else {
        status |= UART1_TRANSFER_STATUS_RX_DATA_PRESENT;
    }
    return status;
}

uint8_t UART1_Peek(uint16_t offset) {
    if ((uart1_obj.rxHead + offset) > (uart1_rxByteQ + UART1_CONFIG_RX_BYTEQ_LENGTH)) {
        return uart1_rxByteQ[offset - (uart1_rxByteQ + UART1_CONFIG_RX_BYTEQ_LENGTH - uart1_obj.rxHead)];
    } else {
        return *(uart1_obj.rxHead + offset);
    }
}

uint8_t UART1_is_rx_ready(void) {
    if (!uart1_obj.rxStatus.s.full) {
        if (uart1_obj.rxHead > uart1_obj.rxTail) {
            return (uart1_obj.rxHead - uart1_obj.rxTail);
        } else {
            return (UART1_CONFIG_RX_BYTEQ_LENGTH - (uart1_obj.rxTail - uart1_obj.rxHead));
        }
    }
    return 0;
}

uint8_t UART1_is_tx_ready(void) {
    if (!uart1_obj.txStatus.s.full) {
        if (uart1_obj.txHead > uart1_obj.txTail) {
            return (uart1_obj.txHead - uart1_obj.txTail);
        } else {
            return (UART1_CONFIG_TX_BYTEQ_LENGTH - (uart1_obj.txTail - uart1_obj.txHead));
        }
    }
    return 0;
}

bool UART1_ReceiveBufferIsEmpty(void) {
    return (uart1_obj.rxStatus.s.empty);
}

bool UART1_TransmitBufferIsFull(void) {
    return (uart1_obj.txStatus.s.full);
}

UART1_STATUS UART1_StatusGet(void) {
    return U1STA;
}

bool UART1_is_tx_done(void) {
    return U1STAbits.TRMT;
}


/**
  End of File
 */