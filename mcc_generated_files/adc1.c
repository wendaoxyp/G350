
/**
  ADC1 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    adc1.c

  @Summary
    This is the generated header file for the ADC1 driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This header file provides APIs for driver for ADC1.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - pic24-dspic-pic32mm : 1.75.1
        Device            :  PIC24FJ64GA702
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.35
        MPLAB 	          :  MPLAB X v5.05
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

#include <xc.h>
#include "adc1.h"

/**
  Section: Data Type Definitions
*/

/* ADC Driver Hardware Instance Object

  @Summary
    Defines the object required for the maintenance of the hardware instance.

  @Description
    This defines the object required for the maintenance of the hardware
    instance. This object exists once per hardware instance of the peripheral.

 */
typedef struct
{
	uint8_t intSample;
}

ADC_OBJECT;

static ADC_OBJECT adc1_obj;

/**
  Section: Driver Interface
*/


void ADC1_Initialize (void)
{
    // ASAM disabled; DMABM disabled; ADSIDL disabled; DONE disabled; DMAEN disabled; FORM Absolute decimal result, unsigned, right-justified; SAMP disabled; SSRC Clearing sample bit ends sampling and starts conversion; MODE12 10-bit; ADON enabled; 

   AD1CON1 = 0x8000;

    // CSCNA disabled; NVCFG0 AVSS; PVCFG AVDD; ALTS disabled; BUFM disabled; SMPI Generates interrupt after completion of every sample/conversion operation; BUFREGEN disabled; 

   AD1CON2 = 0x0000;

    // SAMC 0; EXTSAM disabled; PUMPEN disabled; ADRC FOSC/2; ADCS 0; 

   AD1CON3 = 0x0000;

    // CH0SA AN0; CH0SB AN0; CH0NB AVSS; CH0NA AVSS; 

   AD1CHS = 0x0000;

    // CSS30 disabled; CSS29 disabled; CSS28 disabled; 

   AD1CSSH = 0x0000;

    // CSS9 disabled; CSS8 disabled; CSS7 disabled; CSS6 disabled; CSS5 disabled; CSS4 disabled; CSS3 disabled; CSS2 disabled; CSS15 disabled; CSS1 disabled; CSS14 disabled; CSS0 disabled; CSS13 disabled; CSS12 disabled; CSS11 disabled; CSS10 disabled; 

   AD1CSSL = 0x0000;

    // DMABL Allocates 1 word of buffer to each analog input; 

   AD1CON4 = 0x0000;

    // ASEN disabled; WM Legacy operation; ASINT No interrupt; CM Less Than mode; BGREQ disabled; CTMREQ disabled; LPEN disabled; 

   AD1CON5 = 0x0000;

    // CHH2 disabled; CHH1 disabled; CHH0 disabled; CHH9 disabled; CHH8 disabled; CHH7 disabled; CHH6 disabled; CHH5 disabled; CHH4 disabled; CHH3 disabled; 

   AD1CHITL = 0x0000;

    // CTMEN30 disabled; CTMEN29 disabled; CTMEN28 disabled; 

   AD1CTMENH = 0x0000;

    // CTMEN5 disabled; CTMEN6 disabled; CTMEN7 disabled; CTMEN8 disabled; CTMEN9 disabled; CTMEN12 disabled; CTMEN13 disabled; CTMEN10 disabled; CTMEN0 disabled; CTMEN11 disabled; CTMEN1 disabled; CTMEN2 disabled; CTMEN3 disabled; CTMEN4 disabled; CTMEN14 disabled; CTMEN15 disabled; 

   AD1CTMENL = 0x0000;

    // AD1RESDMA 0; 

   AD1RESDMA = 0x0000;

    // 

   ANCFG = 0x0000;


   adc1_obj.intSample = AD1CON2bits.SMPI;
   
}

void ADC1_Start(void)
{
   AD1CON1bits.SAMP = 1;
}
void ADC1_Stop(void)
{
   AD1CON1bits.SAMP = 0;
}
uint16_t ADC1_ConversionResultBufferGet(uint16_t *buffer)
{
    int count;
    uint16_t *ADC16Ptr;

    ADC16Ptr = (uint16_t *)&(ADC1BUF0);

    for(count=0;count<=adc1_obj.intSample;count++)
    {
        buffer[count] = (uint16_t)*ADC16Ptr;
        ADC16Ptr++;
    }
    return count;
}
uint16_t ADC1_ConversionResultGet(void)
{
    return ADC1BUF0;
}
bool ADC1_IsConversionComplete( void )
{
    return AD1CON1bits.DONE; //Wait for conversion to complete   
}
void ADC1_ChannelSelect( ADC1_CHANNEL channel )
{
    AD1CHS = channel;
}


void ADC1_Tasks ( void )
{
    // clear the ADC interrupt flag
    IFS0bits.AD1IF = false;
}


/**
  End of File
*/
