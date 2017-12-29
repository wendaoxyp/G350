/**
  UART3 Generated Driver File 

  @Company
    Microchip Technology Inc.

  @File Name
    uart3.c

  @Summary
    This is the generated source file for the UART3 driver using MPLAB? Code Configurator

  @Description
    This source file provides APIs for driver for UART3. 
    Generation Information : 
        Product Revision  :  MPLAB? Code Configurator - v2.25.2
        Device            :  PIC24FJ64GA306
        Driver Version    :  0.5
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.24
        MPLAB 	          :  MPLAB X v2.35 or v3.00
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

/**
  Section: Included Files
 */

#include "uart3.h"

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

static UART_OBJECT uart3_obj;

/** UART Driver Queue Length

  @Summary
    Defines the length of the Transmit and Receive Buffers

 */

#define UART3_CONFIG_TX_BYTEQ_LENGTH 8
#define UART3_CONFIG_RX_BYTEQ_LENGTH 8


/** UART Driver Queue

  @Summary
    Defines the Transmit and Receive Buffers

 */

static uint8_t uart3_txByteQ[UART3_CONFIG_TX_BYTEQ_LENGTH];
static uint8_t uart3_rxByteQ[UART3_CONFIG_RX_BYTEQ_LENGTH];

/** UART Hardware FIFO Buffer Length

  @Summary
    Defines the length of the Transmit and Receive FIFOs
 
 */

#define UART3_TX_FIFO_LENGTH 1
#define UART3_RX_FIFO_LENGTH 1 

/**
  Section: Driver Interface
 */


void UART3_Initialize(void) {
    // RTSMD disabled; BRGH enabled; STSEL 1; UARTEN enabled; PDSEL 8N; LPBACK disabled; WAKE disabled; USIDL disabled; RXINV disabled; ABAUD disabled; IREN disabled; UEN TX_RX; 
    U3MODE = 0x8008;
    // UTXEN disabled; UTXINV disabled; URXISEL RX_ONE_CHAR; ADDEN disabled; UTXISEL0 TX_ONE_CHAR; UTXBRK COMPLETED; OERR NO_ERROR_cleared; 
    U3STA = 0x0000;
    // U3TXREG 0x0000; 
    U3TXREG = 0x0000;
    // U3RXREG 0x0000; 
    U3RXREG = 0x0000;
    // Baud Rate = 9600; BRG 416; 
    U3BRG = 0x01A0;


    U3STAbits.UTXEN = 1;

    uart3_obj.txHead = uart3_txByteQ;
    uart3_obj.txTail = uart3_txByteQ;
    uart3_obj.rxHead = uart3_rxByteQ;
    uart3_obj.rxTail = uart3_rxByteQ;
    uart3_obj.rxStatus.s.empty = true;
    uart3_obj.txStatus.s.empty = true;
    uart3_obj.txStatus.s.full = false;
    uart3_obj.rxStatus.s.full = false;
}

/**
void DRV_UART3_Initialize (void)
 */
void DRV_UART3_Initialize(void) {
    UART3_Initialize();
}

/**
    Maintains the driver's transmitter state machine and implements its ISR
 */
void UART3_TasksTransmit(void) {
    if (uart3_obj.txStatus.s.empty) {
        return;
    }

    IFS5bits.U3TXIF = false;

    int count = 0;
    while ((count < UART3_TX_FIFO_LENGTH)&& !(U3STAbits.UTXBF == 1)) {
        count++;

        U3TXREG = *uart3_obj.txHead;

        uart3_obj.txHead++;

        if (uart3_obj.txHead == (uart3_txByteQ + UART3_CONFIG_TX_BYTEQ_LENGTH)) {
            uart3_obj.txHead = uart3_txByteQ;
        }

        uart3_obj.txStatus.s.full = false;

        if (uart3_obj.txHead == uart3_obj.txTail) {
            uart3_obj.txStatus.s.empty = true;
            break;
        }
    }
}

/**
   void DRV_UART3_TasksTransmit ( void )
 */
void DRV_UART3_TasksTransmit(void) {
    UART3_TasksTransmit();
}

void UART3_TasksReceive(void) {
    int count = 0;

    while ((count < UART3_RX_FIFO_LENGTH) && (U3STAbits.URXDA == 1)) {
        count++;

        *uart3_obj.rxTail = U3RXREG;

        uart3_obj.rxTail++;

        if (uart3_obj.rxTail == (uart3_rxByteQ + UART3_CONFIG_RX_BYTEQ_LENGTH)) {
            uart3_obj.rxTail = uart3_rxByteQ;
        }

        uart3_obj.rxStatus.s.empty = false;

        if (uart3_obj.rxTail == uart3_obj.rxHead) {
            //Sets the flag RX full
            uart3_obj.rxStatus.s.full = true;
            break;
        }

    }

    IFS5bits.U3RXIF = false;

}

/**
   void DRV_UART3_TasksReceive ( void )
 */
void DRV_UART3_TasksReceive(void) {
    UART3_TasksReceive();
}

void UART3_TasksError(void) {
    if ((U3STAbits.OERR == 1)) {
        U3STAbits.OERR = 0;
    }

    IFS5bits.U3ERIF = false;
}

/**
   void DRV_UART3_TasksError ( void )
 */
void DRV_UART3_TasksError(void) {
    UART3_TasksError();
}

/**
  Section: UART Driver Client Routines
 */

uint8_t UART3_Read(void) {
    uint8_t data = 0;

    data = *uart3_obj.rxHead;

    uart3_obj.rxHead++;

    if (uart3_obj.rxHead == (uart3_rxByteQ + UART3_CONFIG_RX_BYTEQ_LENGTH)) {
        uart3_obj.rxHead = uart3_rxByteQ;
    }

    if (uart3_obj.rxHead == uart3_obj.rxTail) {
        uart3_obj.rxStatus.s.empty = true;
    }

    uart3_obj.rxStatus.s.full = false;

    return data;
}

/**
   uint8_t DRV_UART3_Read ( void )
 */
uint8_t DRV_UART3_Read(void) {
    return (UART3_Read());
}

unsigned int UART3_ReadBuffer(uint8_t *buffer, const unsigned int bufLen) {
    unsigned int numBytesRead = 0;
    while (numBytesRead < (bufLen)) {
        if (uart3_obj.rxStatus.s.empty) {
            break;
        } else {
            buffer[numBytesRead++] = UART3_Read();
        }
    }

    return numBytesRead;
}

/**
   unsigned int DRV_UART3_ReadBuffer( uint8_t *buffer, const unsigned int bufLen)
 */
unsigned int DRV_UART3_ReadBuffer(uint8_t *buffer, const unsigned int bufLen) {
    return (UART3_ReadBuffer(buffer, bufLen));
}

void UART3_Write(const uint8_t byte) {
    *uart3_obj.txTail = byte;

    uart3_obj.txTail++;

    if (uart3_obj.txTail == (uart3_txByteQ + UART3_CONFIG_TX_BYTEQ_LENGTH)) {
        uart3_obj.txTail = uart3_txByteQ;
    }

    uart3_obj.txStatus.s.empty = false;

    if (uart3_obj.txHead == uart3_obj.txTail) {
        uart3_obj.txStatus.s.full = true;
    }


}

/**
   void DRV_UART3_Write( const uint8_t byte)
 */
void DRV_UART3_Write(const uint8_t byte) {
    UART3_Write(byte);
}

unsigned int UART3_WriteBuffer(const uint8_t *buffer, const unsigned int bufLen) {
    unsigned int numBytesWritten = 0;

    while (numBytesWritten < (bufLen)) {
        if ((uart3_obj.txStatus.s.full)) {
            break;
        } else {
            UART3_Write(buffer[numBytesWritten++]);
        }
    }

    return numBytesWritten;

}

/**
   unsigned int DRV_UART3_WriteBuffer( const uint8_t *buffer , const unsigned int bufLen )
 */
unsigned int DRV_UART3_WriteBuffer(const uint8_t *buffer, const unsigned int bufLen) {
    return (UART3_WriteBuffer(buffer, bufLen));
}

UART3_TRANSFER_STATUS UART3_TransferStatusGet(void) {
    UART3_TRANSFER_STATUS status = 0;

    if (uart3_obj.txStatus.s.full) {
        status |= UART3_TRANSFER_STATUS_TX_FULL;
    }

    if (uart3_obj.txStatus.s.empty) {
        status |= UART3_TRANSFER_STATUS_TX_EMPTY;
    }

    if (uart3_obj.rxStatus.s.full) {
        status |= UART3_TRANSFER_STATUS_RX_FULL;
    }

    if (uart3_obj.rxStatus.s.empty) {
        status |= UART3_TRANSFER_STATUS_RX_EMPTY;
    } else {
        status |= UART3_TRANSFER_STATUS_RX_DATA_PRESENT;
    }
    return status;
}

/**
   DRV_UART3_TRANSFER_STATUS UART3_TransferStatusGet (void )
 */
DRV_UART3_TRANSFER_STATUS DRV_UART3_TransferStatusGet(void) {
    return (UART3_TransferStatusGet());
}

uint8_t UART3_Peek(uint16_t offset) {
    if ((uart3_obj.rxHead + offset) > (uart3_rxByteQ + UART3_CONFIG_RX_BYTEQ_LENGTH)) {
        return uart3_rxByteQ[offset - (uart3_rxByteQ + UART3_CONFIG_RX_BYTEQ_LENGTH - uart3_obj.rxHead)];
    } else {
        return *(uart3_obj.rxHead + offset);
    }
}

/**
  uint8_t DRV_UART3_Peek(uint16_t offset)
 */
uint8_t DRV_UART3_Peek(uint16_t offset) {
    return (UART3_Peek(offset));
}

unsigned int UART3_ReceiveBufferSizeGet(void) {
    if (!uart3_obj.rxStatus.s.full) {
        if (uart3_obj.rxHead > uart3_obj.rxTail) {
            return (uart3_obj.rxHead - uart3_obj.rxTail);
        } else {
            return (UART3_CONFIG_RX_BYTEQ_LENGTH - (uart3_obj.rxTail - uart3_obj.rxHead));
        }
    }
    return 0;
}

/**
  unsigned int DRV_UART3_ReceiveBufferSizeGet(void)
 */
unsigned int DRV_UART3_ReceiveBufferSizeGet(void) {
    return (UART3_ReceiveBufferSizeGet());
}

unsigned int UART3_TransmitBufferSizeGet(void) {
    if (!uart3_obj.txStatus.s.full) {
        if (uart3_obj.txHead > uart3_obj.txTail) {
            return (uart3_obj.txHead - uart3_obj.txTail);
        } else {
            return (UART3_CONFIG_TX_BYTEQ_LENGTH - (uart3_obj.txTail - uart3_obj.txHead));
        }
    }
    return 0;
}

/**
  unsigned int DRV_UART3_TransmitBufferSizeGet(void)
 */
unsigned int DRV_UART3_TransmitBufferSizeGet(void) {
    return (UART3_TransmitBufferSizeGet());
}

bool UART3_ReceiveBufferIsEmpty(void) {
    return (uart3_obj.rxStatus.s.empty);
}

/**
  bool DRV_UART3_ReceiveBufferIsEmpty(void)
 */
bool DRV_UART3_ReceiveBufferIsEmpty(void) {
    return (UART3_ReceiveBufferIsEmpty());
}

bool UART3_TransmitBufferIsFull(void) {
    return (uart3_obj.txStatus.s.full);
}

/**
  bool DRV_UART3_TransmitBufferIsFull(void)
 */
bool DRV_UART3_TransmitBufferIsFull(void) {
    return (UART3_TransmitBufferIsFull());
}

UART3_STATUS UART3_StatusGet(void) {
    return U3STA;
}

/**
  DRV_UART3_STATUS DRV_UART3_StatusGet (void)
 */
DRV_UART3_STATUS DRV_UART3_StatusGet(void) {
    return (UART3_StatusGet());
}


/**
  End of File
 */
