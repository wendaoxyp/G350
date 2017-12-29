/*******************************************************************************
  DMA Generated Driver API Header File

  Company:
    Microchip Technology Inc.

  File Name:
    dma.h

  Summary:
    This is the generated header file for the DMA driver using MPLAB? Code Configurator

  Description:
    This header file provides APIs for driver for DMA.
    Generation Information :
        Product Revision  :  MPLAB? Code Configurator - v2.25.2
        Device            :  PIC24FJ64GA306
        Version           :  1.0
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.24
        MPLAB             :  MPLAB X v2.35 or v3.00
 *******************************************************************************/

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

#ifndef DMA_H
#define DMA_H

#include <xc.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif

    /**
      Section: Data Types
     */

    /** DMA Channel Definition
 
     @Summary 
       Defines the channels available for DMA
 
     @Description
       This routine defines the channels that are available for the module to use.
 
     Remarks:
       None
     */
    typedef enum {
        DMA_CHANNEL0 = 0,
        DMA_NUMBER_OF_CHANNELS = 6
    } DMA_CHANNEL;
    /**
      Section: Interface Routines
     */

    /**
      @Summary
        This function initializes DMA instance : 

      @Description
        This routine initializes the DMA driver instance for : 
        index, making it ready for clients to open and use it. It also initializes any
        internal data structures.
        This routine must be called before any other DMA routine is called. 

      @Preconditions
        None.

      @Param
        None.

      @Returns
        None.

      @Comment
    
 
      @Example
        <code>
            unsigned short int srcArray[100];
            unsigned short int dstArray[100];
            int i;
            int count;
            for (i=0; i<100; i++)
            {
                srcArray[i] = i+1;
                dstArray[i] = 0;
            }
        
            DMA_Initialize();
            DMA_SoftwareTriggerEnable(CHANNEL1);
        
            count = {settings.functionPrefix?upper_case}DMA_TransferCountGet;
            while(count > 0)
            {
            while({settings.functionPrefix?upper_case}DMA_IsSoftwareRequestPending(CHANNEL1));
            DMA_SoftwareTriggerEnable(CHANNEL1);
            }
        </code>

     */
    void DMA_Initialize(void);

    /**
      @Summary
        Returns the transfer count of the DMA

      @Description
        This routine is used to determine the DMA transfer count. This routine
        returns the value of the DMACNT register. 
 
      @Preconditions
        {settings.functionPrefix?upper_case}DMA_Initializer() function should have been 
        called before calling this function.
 
      @Returns
        Returns the transfer count of the DMA

      @Param
        None
  
      @Example
        Refer to {settings.functionPrefix?upper_case}DMA_Initializer(); for an example
     */
    uint16_t DMA_TransferCountGet(DMA_CHANNEL);

    /**
      @Summary
        Enables the software trigger of the DMA

      @Description
        This routine is used to enable the software trigger of the DMA. This routine
        sets the value of the CHREQ bit to 1.
 
      @Preconditions
        {settings.functionPrefix?upper_case}DMA_Initializer() function should have been 
        called before calling this function.
 
      @Returns
        None

      @Param
        None
  
      @Example
        Refer to {settings.functionPrefix?upper_case}DMA_Initializer(); for an example
     */
    void DMA_SoftwareTriggerEnable(DMA_CHANNEL);
    /**
      @Summary
        Sets the source address for the DMA

      @Description
        This routine is used to set the source address for a DMA channel. 
 
      @Preconditions
        {settings.functionPrefix?upper_case}DMA_Initializer() function should have been 
        called before calling this function.
 
      @Returns
        None

      @Param
        None
  
      @Example
        Refer to {settings.functionPrefix?upper_case}DMA_Initializer(); for an example
     */
    void DMA_SourceAddressSet(DMA_CHANNEL, uint16_t);
    /**
      @Summary
        Sets the destination address for the DMA

      @Description
        This routine is used to set the destination address for a DMA channel. 
 
      @Preconditions
        {settings.functionPrefix?upper_case}DMA_Initializer() function should have been 
        called before calling this function.
 
      @Returns
        None

      @Param
        None
  
      @Example
        Refer to {settings.functionPrefix?upper_case}DMA_Initializer(); for an example
     */
    void DMA_DestinationAddressSet(DMA_CHANNEL, uint16_t);
    /**
      @Summary
        Returns true when the software DMA request is completed

      @Description
        This routine is used to determine if the software DMA request is completed. This routine
        returns the value of the CHREQ bit. When DMA request is complete the routine
        returns 1. It returns 0 otherwise.
 
      @Preconditions
        {settings.functionPrefix?upper_case}DMA_Initializer() function should have been 
        called before calling this function.
 
      @Returns
        Returns true if software request is completed

      @Param
        None
  
      @Example
        Refer to {settings.functionPrefix?upper_case}DMA_Initializer(); for an example
     */
    bool DMA_IsSoftwareRequestPending(DMA_CHANNEL);

    /**
      @Summary
        Returns true when the buffered DMA write is completed

      @Description
        This routine is used to determine if the buffered DMA write is completed. This routine
        returns the value of the DBUFWF bit. When buffered DMA write is complete the routine
        returns 1. It returns 0 otherwise.
 
      @Preconditions
        {settings.functionPrefix?upper_case}DMA_Initializer() function should have been 
        called before calling this function.
 
      @Returns
        Returns true if buffered DMA write is completed

      @Param
        None
  
      @Example
        Refer to {settings.functionPrefix?upper_case}DMA_Initializer(); for an example
     */
    bool DMA_IsBufferedWriteComplete(DMA_CHANNEL);

    /**
      @Summary
        Returns true when the high address limit flag is set

      @Description
        This routine is used to determine if the DMA channel has tried to access an
        address higher than the DMAH limit. This routine returns the value of the 
        HIGHIF bit. When the high address limit has been crossed the routine
        returns 1. It returns 0 otherwise.
 
      @Preconditions
        {settings.functionPrefix?upper_case}DMA_Initializer() function should have been 
        called before calling this function.
 
      @Returns
        Returns true if high address limit has been crossed.

      @Param
        None
  
      @Example
        Refer to {settings.functionPrefix?upper_case}DMA_Initializer(); for an example
     */
    bool DMA_IsHighAddressLimitFlagSet(DMA_CHANNEL);

    /**
      @Summary
        Returns true when the low address limit flag is set

      @Description
        This routine is used to determine if the DMA channel has tried to access an
        address lower than the DMAL limit. This routine returns the value of the 
        LOWIF bit. When the low address limit has been crossed the routine
        returns 1. It returns 0 otherwise.
 
      @Preconditions
        {settings.functionPrefix?upper_case}DMA_Initializer() function should have been 
        called before calling this function.
 
      @Returns
        Returns true if the low address limit has been crossed.

      @Param
        None
  
      @Example
        Refer to {settings.functionPrefix?upper_case}DMA_Initializer(); for an example
     */
    bool DMA_IsLowAddressLimitFlagSet(DMA_CHANNEL);

    /**
      @Summary
        Returns true when the operation is done.

      @Description
        This routine is used to determine if the DMA operation is done.. This routine 
        returns the value of the DONEIF bit. When the operation is done the routine 
        returns 1. It returns 0 otherwise.
 
      @Preconditions
        {settings.functionPrefix?upper_case}DMA_Initializer() function should have been 
        called before calling this function.
 
      @Returns
        Returns true if the DMA operation is done.

      @Param
        None
  
      @Example
        Refer to {settings.functionPrefix?upper_case}DMA_Initializer(); for an example
     */
    bool DMA_IsOperationDone(DMA_CHANNEL);

    /**
      @Summary
        Returns true when a DMA overrun has occured

      @Description
        This routine is used to determine if a DMA overrun has occured. This routine 
        returns the value of the OVRUNIF bit. When a DMA overrun has occurred the routine
        returns 1. It returns 0 otherwise.
 
      @Preconditions
        {settings.functionPrefix?upper_case}DMA_Initializer() function should have been 
        called before calling this function.
 
      @Returns
        Returns true if a DMA overrun has occurred. 

      @Param
        None
  
      @Example
        Refer to {settings.functionPrefix?upper_case}DMA_Initializer(); for an example
     */
    bool DMA_IsOverrunFlagSet(DMA_CHANNEL);

    /**
      @Summary
        Returns true when the operation is halfway done

      @Description
        This routine is used to determine if the DMA operation is 50% complete. This 
        routine returns the value of the HALFIF bit. When the DMA operation is halfway 
        done the routine returns 1. It returns 0 otherwise.
 
      @Preconditions
        {settings.functionPrefix?upper_case}DMA_Initializer() function should have been 
        called before calling this function.
 
      @Returns
        Returns true if the operation is halfway completed

      @Param
        None
  
      @Example
        Refer to {settings.functionPrefix?upper_case}DMA_Initializer(); for an example
     */
    bool DMA_IsOperationHalfComplete(DMA_CHANNEL);

#ifdef __cplusplus  // Provide C++ Compatibility

}

#endif

#endif  // DMA.h