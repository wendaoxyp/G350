/*****************************************************************************************************************
*
* FileName:        Switch.h
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
#ifndef SWITCH_H
#define SWITCH_H

extern void InitSwtiches();
extern void ScanSwitch (void);
extern void SWxWaitRel(void);

#define SWITCH1_TRIS 	TRISAbits.TRISA1
#define SWITCH2_TRIS 	TRISAbits.TRISA5
#define SWITCH3_TRIS 	TRISAbits.TRISA4
#define SWITCH4_TRIS 	TRISBbits.TRISB7


#define SWITCH4_ANS 	ANSBbits.ANSB7

#define SW1 	PORTAbits.RA1
#define SW2 	PORTAbits.RA5
#define SW3 	PORTAbits.RA4
#define SW4 	PORTBbits.RB7

#endif //eof

