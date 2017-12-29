/*****************************************************************************************************************
*
* FileName:        ADC.h
* Company:         Microchip Technology Incorporated
*
* Copyright 2011 Microchip Technology Inc.  All rights reserved.
*
* Microchip licenses to you the right use, modify, copy, and distribute the accompanying 
* Microchip demo code only when used with or embedded on a Microchip microcontroller or Microchip 
* digital signal controller that is integrated into your product or a third party product.  
* Any redistributions of Microchip’s demo code in compliance with the foregoing must include a copy 
* of this entire notice. 
* 
* 
* THE MICROCHIP DEMO CODE AND DOCUMENTATION ARE PROVIDED “AS IS” WITHOUT WARRANTY OF ANY KIND, EITHER 
* EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY, TITLE, NON-INFRINGEMENT, 
* AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED 
* UNDER CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR OTHER LEGAL EQUITABLE 
* THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, 
* INDIRECT, OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF SUBSTITUTE GOODS, 
* TECHNOLOGY, SERVICES, ANY CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), 
* OR OTHER SIMILAR COSTS.
* 
******************************************************************************************************************/

#ifndef ADC_H
#define ADC_H

#define ADC_TEMP_CHANNEL 		ANSGbits.ANSG9
#define ADC_POT_CHANNEL 		ANSBbits.ANSB11
#define ADC_TEMP_TRIS		TRISGbits.TRISG9
#define ADC_POT_TRIS 		TRISAbits.TRISA1

extern void ADCInit();
extern void ADCEvents();
#define  ADC_TEMPERATURE 0x14;
#define  ADC_VOLTAGE 0x0B;
#define  ADC_BANDGAP 0x1C;

extern unsigned int 	_uADCTemperature;
extern unsigned long Result,Result1;
extern unsigned char Status,ADCBUFCOUNT,_uADCState;
extern unsigned long VDD_RES,VDD_RES1,VDD_RES2,ADCount;

#endif//EOF
