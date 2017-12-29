
/**
  SPI2 Generated Driver API Source File

  Company:
    Microchip Technology Inc.

  File Name:
    spi2.c

  @Summary
    This is the generated source file for the SPI2 driver using MPLAB? Code Configurator

  @Description
    This source file provides APIs for driver for SPI2.
    Generation Information :
        Product Revision  :  MPLAB? Code Configurator - v2.25.2
        Device            :  PIC24FV32KA302
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

#include <xc.h>
#include "spi2.h"


/**
 Section: File specific functions
 */

inline __attribute__((__always_inline__)) SPI2_TRANSFER_MODE SPI2_TransferModeGet(void);
void SPI2_Exchange(uint8_t *pTransmitData, uint8_t *pReceiveData);
uint16_t SPI2_ExchangeBuffer(uint8_t *pTransmitData, uint16_t byteCount, uint8_t *pReceiveData);

/**
 Section: Driver Interface Function Definitions
 */


void SPI2_Initialize(void) {
    // SPI Frequency = 1,000,000 Hz; PPRE 4:1; SMP Sample at Middle; MSTEN enabled; MODE16 disabled; DISSCK disabled; SPRE 1:1; CKE Active to Idle; DISSDO disabled; CKP Idle:Low, Active:High; 
    SPI2CON1 = 0x013E;
    // SPIFPOL disabled; SPIBEN enabled; SPIFE disabled; 
    SPI2CON2 = 0x0001;
    // SISEL SPI_INT_SPIRBF; SPIEN enabled; SPISIDL disabled; SPIROV disabled; 
    SPI2STAT = 0x800C;

}

/**
    void DRV_SPI2_Initialize (void)
 */
void DRV_SPI2_Initialize(void) {
    SPI2_Initialize();
}

void SPI2_Exchange(uint8_t *pTransmitData, uint8_t *pReceiveData) {

    while (SPI2STATbits.SPITBF == true) {

    }

    if (SPI2_TransferModeGet() == SPI2_DRIVER_TRANSFER_MODE_16BIT)
        SPI2BUF = *((uint16_t*) pTransmitData);
    else
        SPI2BUF = *((uint8_t*) pTransmitData);

    while (SPI2STATbits.SR1MPT == true);

    if (SPI2_TransferModeGet() == SPI2_DRIVER_TRANSFER_MODE_16BIT)
        *((uint16_t*) pReceiveData) = SPI2BUF;
    else
        *((uint8_t*) pReceiveData) = SPI2BUF;

}

uint16_t SPI2_ExchangeBuffer(uint8_t *pTransmitData, uint16_t byteCount, uint8_t *pReceiveData) {

    uint16_t dataSentCount = 0;
    uint16_t count = 0;
    uint16_t dummyDataReceived = 0;
    uint16_t dummyDataTransmit = SPI2_DUMMY_DATA;

    uint8_t *pSend, *pReceived;
    uint16_t addressIncrement;
    uint16_t receiveAddressIncrement, sendAddressIncrement;

    SPI2_TRANSFER_MODE spiModeStatus;

    spiModeStatus = SPI2_TransferModeGet();
    // set up the address increment variable
    if (spiModeStatus == SPI2_DRIVER_TRANSFER_MODE_16BIT) {
        addressIncrement = 2;
        byteCount >>= 1;
    }
    else {
        addressIncrement = 1;
    }

    // set the pointers and increment delta 
    // for transmit and receive operations
    if (pTransmitData == NULL) {
        sendAddressIncrement = 0;
        pSend = (uint8_t*) & dummyDataTransmit;
    } else {
        sendAddressIncrement = addressIncrement;
        pSend = (uint8_t*) pTransmitData;
    }

    if (pReceiveData == NULL) {
        receiveAddressIncrement = 0;
        pReceived = (uint8_t*) & dummyDataReceived;
    } else {
        receiveAddressIncrement = addressIncrement;
        pReceived = (uint8_t*) pReceiveData;
    }


    while (SPI2STATbits.SPITBF == true) {

    }

    while (dataSentCount < byteCount) {
        if ((count < SPI2_FIFO_FILL_LIMIT)) {
            if (spiModeStatus == SPI2_DRIVER_TRANSFER_MODE_16BIT)
                SPI2BUF = *((uint16_t*) pSend);
            else
                SPI2BUF = *pSend;
            pSend += sendAddressIncrement;
            dataSentCount++;
            count++;
        }
        if (SPI2STATbits.SR1MPT == false) {
            if (spiModeStatus == SPI2_DRIVER_TRANSFER_MODE_16BIT)
                *((uint16_t*) pReceived) = SPI2BUF;
            else
                *pReceived = SPI2BUF;
            pReceived += receiveAddressIncrement;
            count--;
        }

    }
    while (count) {
        if (SPI2STATbits.SR1MPT == false) {
            if (spiModeStatus == SPI2_DRIVER_TRANSFER_MODE_16BIT)
                *((uint16_t*) pReceived) = SPI2BUF;
            else
                *pReceived = SPI2BUF;
            pReceived += receiveAddressIncrement;
            count--;
        }
    }

    return dataSentCount;
}

uint8_t SPI2_Exchange8bit(uint8_t data) {
    uint8_t receiveData;

    SPI2_Exchange(&data, &receiveData);

    return (receiveData);
}

/**
    uint8_t DRV_SPI2_Exchange16bit (uint8_t data)
 */
uint8_t DRV_SPI2_Exchange8bit(uint8_t data) {
    return (SPI2_Exchange8bit(data));
}

uint16_t SPI2_Exchange8bitBuffer(uint8_t *dataTransmitted, uint16_t byteCount, uint8_t *dataReceived) {
    return (SPI2_ExchangeBuffer(dataTransmitted, byteCount, dataReceived));
}

/**
    uint8_t DRV_SPI2_Exchange8bitBuffer (uint8_t *dataTransmitted, uint8_t byteCount, uint8_t *dataReceived)
 */
uint8_t DRV_SPI2_Exchange8bitBuffer(uint8_t *dataTransmitted, uint16_t byteCount, uint8_t *dataReceived) {
    return (SPI2_Exchange8bitBuffer((uint8_t *) dataTransmitted, byteCount, (uint8_t *) dataReceived));
}

/**

    The module's transfer mode affects the operation
    of the exchange functions. The table below shows
    the effect on data sent or received:
    |=======================================================================|
    | Transfer Mode  |     Exchange Function      |        Comments         |
    |=======================================================================|
    |                | SPIx_Exchange8bitBuffer()  |                         |
    |                |----------------------------|  OK                     |
    |                | SPIx_Exchange8bit()        |                         |
    |     8 bits     |----------------------------|-------------------------|
    |                | SPIx_Exchange16bitBuffer() | Do not use. Only the    |
    |                |----------------------------| lower byte of the 16-bit|
    |                | SPIx_Exchange16bit()       | data will be sent or    |
    |                |                            | received.               |
    |----------------|----------------------------|-------------------------|
    |                | SPIx_Exchange8bitBuffer()  | Do not use. Additional  |
    |                |----------------------------| data byte will be       |
    |                | SPIx_Exchange8bit()        | inserted for each       |
    |                |                            | 8-bit data.             |
    |     16 bits    |----------------------------|-------------------------|
    |                | SPIx_Exchange16bitBuffer() |                         |
    |                |----------------------------|  OK                     |
    |                | SPIx_Exchange16bit()       |                         |
    |----------------|----------------------------|-------------------------|
 */
inline __attribute__((__always_inline__)) SPI2_TRANSFER_MODE SPI2_TransferModeGet(void) {
    if (SPI2CON1bits.MODE16 == 0)
        return SPI2_DRIVER_TRANSFER_MODE_8BIT;
    else
        return SPI2_DRIVER_TRANSFER_MODE_16BIT;
}

SPI2_STATUS SPI2_StatusGet() {
    return (SPI2STAT);
}

/**
    DRV_SPI2_STATUS DRV_SPI2_StatusGet ()
 */
DRV_SPI2_STATUS DRV_SPI2_StatusGet() {
    return (SPI2_StatusGet());
}
/**
 End of File
 */
