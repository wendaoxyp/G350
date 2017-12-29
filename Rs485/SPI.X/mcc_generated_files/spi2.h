/**
  SPI2 Generated Driver API Header File

  Company:
    Microchip Technology Inc.

  File Name:
    spi2.h

  @Summary
    This is the generated header file for the SPI2 driver using MPLAB? Code Configurator

  @Description
    This header file provides APIs for driver for SPI2.
    Generation Information :
        Product Revision  :  MPLAB? Code Configurator - v2.25.2
        Device            :  PIC24F32KA302
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

#ifndef _SPI2_H
#define _SPI2_H

/**
 Section: Included Files
 */

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif

    /**
     Section: Data Type Definitions
     */

    /**
      SPI2_DUMMY_DATA 

      @Summary
        Dummy data to be sent. 

      @Description
        Dummy data to be sent, when no input buffer is specified in the buffer APIs.
     */
#define SPI2_DUMMY_DATA 0x0

    /**
    Deprecated Data Type
     */
#define DRV_SPI2_DUMMY_DATA 0x0

    /**
      SPI2_FIFO_FILL_LIMIT

      @Summary
        FIFO fill limit for data transmission. 

      @Description
        The amount of data to be filled in the FIFO during transmission. The maximum limit allowed is 8.
     */
#define SPI2_FIFO_FILL_LIMIT 0x8

    //Check to make sure that the FIFO limit does not exceed the maximum allowed limit of 8
#if (SPI2_FIFO_FILL_LIMIT > 8)

#define SPI2_FIFO_FILL_LIMIT 8

#endif

    /**
    Deprecated FIFO FILL LIMIT
     */
#define DRV_SPI2_FIFO_FILL_LIMIT 0x8	

#if (DRV_SPI2_FIFO_FILL_LIMIT > 8)

#define DRV_SPI2_FIFO_FILL_LIMIT 8

#endif

    /**
      SPI2 Status Enumeration

      @Summary
        Defines the status enumeration for SPI2.

      @Description
        This defines the status enumeration for SPI2.
     */
    typedef enum {
        SPI2_SHIFT_REGISTER_EMPTY = 1 << 7,
        SPI2_RECEIVE_OVERFLOW = 1 << 6,
        SPI2_RECEIVE_FIFO_EMPTY = 1 < 5,
        SPI2_TRANSMIT_BUFFER_FULL = 1 << 1,
        SPI2_RECEIVE_BUFFER_FULL = 1 << 0
    } SPI2_STATUS;

    /**
    Deprecated Status Enumeration
     */
    typedef enum {
        DRV_SPI2_SHIFT_REGISTER_EMPTY = 1 << 7,
        DRV_SPI2_RECEIVE_OVERFLOW = 1 << 6,
        DRV_SPI2_RECEIVE_FIFO_EMPTY = 1 < 5,
        DRV_SPI2_TRANSMIT_BUFFER_FULL = 1 << 1,
        DRV_SPI2_RECEIVE_BUFFER_FULL = 1 << 0
    } DRV_SPI2_STATUS;

    /**
      SPI2 Mode Enumeration

      @Summary
        Defines the mode of operation for SPI2.

      @Description
        This defines the mode of operation for SPI2.
     */
    typedef enum {
        SPI2_DRIVER_TRANSFER_MODE_8BIT = 0,
        SPI2_DRIVER_TRANSFER_MODE_16BIT = 1,
        SPI2_DRIVER_TRANSFER_MODE_32BIT = 2,
    } SPI2_TRANSFER_MODE;

    /**
     Section: Interface Routines
     */

    /**
      @Summary
        Initializes the SPI instance : 2

      @Description
        This routine initializes the spi2 driver instance for : 2
        index, making it ready for clients to open and use it.

        This routine must be called before any other SPI2 routine is called.
        This routine should only be called once during system initialization.
 
      @Preconditions
        None.

      @Returns
        None.

      @Param
        None.

      @Example
        <code>
        uint16_t   myWriteBuffer[MY_BUFFER_SIZE];
        uint16_t   myReadBuffer[MY_BUFFER_SIZE];
        uint16_t writeData;
        uint16_t readData;
        SPI2_STATUS status;
        unsigned int    total;
        SPI2_Initialize;
        total = 0;
        do
        {
            total  = SPI2_Exchange16bitBuffer( &myWriteBuffer[total], MY_BUFFER_SIZE - total, &myWriteBuffer[total]);

            // Do something else...

        } while( total < MY_BUFFER_SIZE );

        readData = SPI2_Exchange16bit( writeData);

        status = SPI2_StatusGet();

        </code>

     */

    void SPI2_Initialize(void);

    /**
        void DRV_SPI2_Initialize(void)
     */
    void DRV_SPI2_Initialize(void) __attribute__((deprecated("\nThis will be removed in future MCC releases. \nUse SPI2_Initialize instead. ")));




    /**
      @Summary
        Exchanges one byte of data from SPI2

      @Description
        This routine exchanges one byte of data from the SPI2.
        This is a blocking routine.

      @Preconditions
        The SPI2_Initialize routine must have been called for the specified
        SPI2 driver instance.
        The SPI transfer mode should be selected as 8bit mode in the initialization. 
        Do not select 16 bit mode, as additional data byte will be inserted for each 8 bit data if selected.

      @Returns
        Data read from SPI2

      @Param
        data         - Data to be written onto SPI2.

      @Example 
        Refer to SPI2_Initialize() for an example	
     */

    uint8_t SPI2_Exchange8bit(uint8_t data);

    /**
        uint8_t DRV_SPI2_Exchange8bit(uint8_t data)
     */
    uint8_t DRV_SPI2_Exchange8bit(uint8_t data) __attribute__((deprecated("\nThis will be removed in future MCC releases. \nUse SPI2_Exchange8bit instead. ")));

    /**
      @Summary
        Exchanges data from a buffer of size one byte from SPI2

      @Description
        This routine exchanges data from a buffer of size one byte from the SPI2.
        This is a blocking routine.

      @Preconditions
        The SPI2_Initialize routine must have been called for the specified
        SPI2 driver instance.
        The SPI transfer mode should be selected as 8bit mode in the initialization. 
        Do not select 16 bit mode, as additional data byte will be inserted for each 8 bit data if selected.

      @Returns
        Number of words written/read.

      @Param
        dataTransmitted         - Buffer of data to be written onto SPI2.
 
      @Param
        byteCount         - Number of bytes to be exchanged.
 
      @Param
        dataReceived         - Buffer of data to be read from SPI2.

      @Example 
        Refer to SPI2_Initialize() for an example	
 
     */

    uint16_t SPI2_Exchange8bitBuffer(uint8_t *dataTransmitted, uint16_t byteCount, uint8_t *dataReceived);

    /**
        uint8_t DRV_SPI2_Exchange8bitBuffer(uint8_t *dataTransmitted, uint8_t byteCount, uint8_t *dataReceived)
     */
    uint8_t DRV_SPI2_Exchange8bitBuffer(uint8_t *dataTransmitted, uint16_t byteCount, uint8_t *dataReceived) __attribute__((deprecated("\nThis will be removed in future MCC releases. \nUse SPI2_Exchange8bitBuffer instead. ")));

    /**
      @Summary
        Returns the value of the status register of SPI instance : 2

      @Description
        This routine returns the value of the status register of SPI2 driver instance : 2

      @Preconditions
        None.

      @Returns
        Returns the value of the status register.

      @Param
        None.

      @Example 
        Refer to SPI2_Initialize() for an example	
 
     */

    SPI2_STATUS SPI2_StatusGet(void);

    /**
        DRV_SPI2_STATUS DRV_SPI2_StatusGet(void)
     */
    DRV_SPI2_STATUS DRV_SPI2_StatusGet(void) __attribute__((deprecated("\nThis will be removed in future MCC releases. \nUse SPI2_StatusGet instead. ")));

#ifdef __cplusplus  // Provide C++ Compatibility

}

#endif

#endif //_SPI2_H

/*******************************************************************************
 End of File
 */
