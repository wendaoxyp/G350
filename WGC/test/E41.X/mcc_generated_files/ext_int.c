/**
  EXT_INT Generated Driver File 

  @Company:
    Microchip Technology Inc.

  @File Name:
    ext_int.c

  @Summary
    This is the generated driver implementation file for the EXT_INT 
    driver using MPLAB? Code Configurator

  @Description:
    This source file provides implementations for driver APIs for EXT_INT. 
    Generation Information : 
        Product Revision  :  MPLAB? Code Configurator - v2.25.2
        Device            :  PIC24FJ64GA306
        Driver Version    :  1.0.0
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.24
        MPLAB             :  MPLAB X v2.35 or v3.00
 */

/**
   Section: Includes
 */
#include <xc.h>
#include "ext_int.h"
#include "Common.h"
//***User Area Begin->code: Add External Interrupt handler specific headers 
//struct FLAGBITS {
//    uint16_t E41 : 1;
//};
//struct FLAGBITS Flagbits;
////extern uint8_t Flag_E41;
//***User Area End->code: Add External Interrupt handler specific headers

/**
   Section: External Interrupt Handlers
 */

/**
  Interrupt Handler for EX_INT0 - INT0
 */
void __attribute__((interrupt, no_auto_psv)) _INT0Interrupt(void) {
    //***User Area Begin->code: INT0 - External Interrupt 0***
    flagbits.E41 = 1;
    //***User Area End->code: INT0 - External Interrupt 0***
    EX_INT0_InterruptFlagClear();
}
/**
    Section: External Interrupt Initializers
 */

/**
    void EXT_INT_Initialize(void)

    Initializer for the following external interrupts
    INT0
 */
void EXT_INT_Initialize(void) {
    /*******
     * INT0
     * Clear the interrupt flag
     * Set the external interrupt edge detect
     * Enable the interrupt
     ********/
    EX_INT0_InterruptFlagClear();
    EX_INT0_NegativeEdgeSet();
    EX_INT0_InterruptEnable();
}

/**
    void DRV_EXT_INT_Initialize(void)
 */
void DRV_EXT_INT_Initialize(void) {
    EXT_INT_Initialize();
}
