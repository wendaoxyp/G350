/*******************************************************************************
  DMA Generated Driver File

  Company:
    Microchip Technology Inc.

  File Name:
    dma.c

  Summary:
    This is the generated driver implementation file for the DMA driver using MPLAB? Code Configurator

  Description:
    This source file provides implementations for driver APIs for DMA.
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

#include <xc.h>
#include "dma.h"

/**
  Prototype:        void DMA_Initialize(void)
  Input:            none
  Output:           none
  Description:      DMA_Initialize is an
                    initialization routine that takes inputs from the GUI.
  Comment:          
  Usage:            DMA_Initialize();
 */
void DMA_Initialize(void) {
    // PRSSEL Fixed priority; DMAEN enabled; 
    DMACON = (0x8000 | 0x01) & 0x7FFF; //Enable DMA later
    // HADDR 0xFFFF; 
    DMAH = 0xFFFF;
    // LADDR 0x0800; 
    DMAL = 0x0800;
    // CHEN enabled; BYTE Word (16 bit); SAMODE Unchanged; RELOAD disabled; TRMODE One-Shot; DAMODE Unchanged; CHREQ disabled; NULLW disabled; 
    DMACH0 = 0x0001 & 0xFFFE; //Enable DMA Channel later;
    // CHSEL None; OVRUNIF disabled; DONEIF disabled; HALFEN disabled; HIGHIF disabled; HALFIF disabled; LOWIF disabled; 
    DMAINT0 = 0x0000;
    // SADDR 0x0000; 
    DMASRC0 = 0x0000;
    // DADDR 0x0000; 
    DMADST0 = 0x0000;
    // CNT 0; 
    DMACNT0 = 0x0000;
    // Clearing Channel 0 Interrupt Flag;
    IFS0bits.DMA0IF = false;

    //Enable DMA
    DMACONbits.DMAEN = 0;

    //Enable DMA Channel 0
    DMACH0bits.CHEN = 0;
}

void __attribute__((interrupt, no_auto_psv)) _DMA0Interrupt(void) {
    IFS0bits.DMA0IF = 0;
}

uint16_t DMA_TransferCountGet(DMA_CHANNEL channel) {
    switch (channel) {
        case DMA_CHANNEL0:
            return (DMACNT0);
        default: return 0;
    }
}

void DMA_SoftwareTriggerEnable(DMA_CHANNEL channel) {
    switch (channel) {
        case DMA_CHANNEL0:
            DMACH0bits.CHREQ = 1;
            break;
        default: break;
    }
}

void DMA_SourceAddressSet(DMA_CHANNEL channel, uint16_t address) {
    switch (channel) {
        case DMA_CHANNEL0:
            DMASRC0 = address;
            break;
        default: break;
    }
}

void DMA_DestinationAddressSet(DMA_CHANNEL channel, uint16_t address) {
    switch (channel) {
        case DMA_CHANNEL0:
            DMADST0 = address;
            break;
        default: break;
    }
}

bool DMA_IsSoftwareRequestPending(DMA_CHANNEL channel) {
    switch (channel) {
        case DMA_CHANNEL0:
            return (DMACH0bits.CHREQ);
        default: return 0;
    }
}

bool DMA_IsBufferedWriteComplete(DMA_CHANNEL channel) {
    switch (channel) {
        case DMA_CHANNEL0:
            return (DMAINT0bits.DBUFWF);
        default: return 0;
    }
}

bool DMA_IsHighAddressLimitFlagSet(DMA_CHANNEL channel) {
    switch (channel) {
        case DMA_CHANNEL0:
            return (DMAINT0bits.HIGHIF);
        default: return 0;
    }
}

bool DMA_IsLowAddressLimitFlagSet(DMA_CHANNEL channel) {
    switch (channel) {
        case DMA_CHANNEL0:
            return (DMAINT0bits.LOWIF);
        default: return 0;
    }
}

bool DMA_IsOperationDone(DMA_CHANNEL channel) {
    switch (channel) {
        case DMA_CHANNEL0:
            return (DMAINT0bits.DONEIF);
        default: return 0;
    }
}

bool DMA_IsOverrunFlagSet(DMA_CHANNEL channel) {
    switch (channel) {
        case DMA_CHANNEL0:
            return (DMAINT0bits.OVRUNIF);
        default: return 0;
    }
}

bool DMA_IsOperationHalfComplete(DMA_CHANNEL channel) {
    switch (channel) {
        case DMA_CHANNEL0:
            return (DMAINT0bits.HALFIF);
        default: return 0;
    }
}
