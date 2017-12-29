/*****************************************************************************************************************
*
* FileName:        LCD.h
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

#ifndef LCD_H
#define LCD_H
/*****************************************************************************
* Function: LCDBiasUpdate();
*
* Preconditions: None.
*
* Overview: This function Change the BIAS to charge PUMP if VDD < 2.8V
*
* Input: None.
*
* Output: None.
*
******************************************************************************/

extern void 	LCDBiasUpdate();

/*****************************************************************************
* Function: ADCInit
*
* Preconditions: None.
*
* Overview: This function initiates LCD
*
* Input: None.
*
* Output: None.
*
******************************************************************************/
extern void LCDInit();

/*****************************************************************************
* Function: LCDSetAll
*
* Preconditions: None.
*
* Overview: This Sets all the pixels on the glass
*
* Input: None.
*
* Output: None.
*
******************************************************************************/
extern void LCDSetAll();
extern void LCDClearAll();
extern void Microchip();

extern void Digit0(unsigned char);
extern void Digit1(unsigned char);
extern void Col1(unsigned char);
extern void Digit2(unsigned char);
extern void Digit2A(unsigned char );
extern void Digit3(unsigned char);
extern void Col2(unsigned char);
extern void Digit4(unsigned char);

extern void Banner(void);
extern void Digit5(unsigned char);

#define S1 	LCDSE0bits.SE08
#define S2 	LCDSE0bits.SE09
#define S3 	LCDSE0bits.SE10
#define S4 	LCDSE0bits.SE11
#define S5 	LCDSE0bits.SE15

#define S6 		LCDSE1bits.SE16
#define S7 		LCDSE1bits.SE17
#define S8 		LCDSE1bits.SE19
#define S9		LCDSE1bits.SE20
#define S10		LCDSE1bits.SE21
#define S11		LCDSE1bits.SE22
#define S12		LCDSE1bits.SE23
#define S13		LCDSE1bits.SE24
#define S14		LCDSE1bits.SE25
#define S15		LCDSE1bits.SE26

#define S16		LCDSE2bits.SE32
#define S17		LCDSE2bits.SE33
#define S18		LCDSE2bits.SE36
#define S19		LCDSE2bits.SE37
#define S20		LCDSE2bits.SE42
#define S21		LCDSE2bits.SE43
#define S22		LCDSE2bits.SE44
#define S23		LCDSE2bits.SE45

#define S24		LCDSE3bits.SE49
#define S25		LCDSE3bits.SE51
#define S26		LCDSE3bits.SE52
#define S27		LCDSE3bits.SE54
#define S28		LCDSE3bits.SE55
#define S29		LCDSE3bits.SE56
#define S30		LCDSE3bits.SE57
#define S31		LCDSE3bits.SE58
#define S32		LCDSE3bits.SE59
#define S33		LCDSE3bits.SE60
#define S34		LCDSE3bits.SE61
#define S35		LCDSE3bits.SE62
#define S36		LCDSE3bits.SE63



#define X1C1 		LCDDATA0bits.S08C0
#define X2C1 		LCDDATA4bits.S08C1
#define X3C1 		LCDDATA8bits.S08C2
#define X4C1 		LCDDATA12bits.S08C3
#define X5C1 		LCDDATA16bits.S08C4
#define X6C1 		LCDDATA20bits.S08C5
#define X7C1 		LCDDATA24bits.S08C6
#define Dollar		LCDDATA28bits.S08C7
//
#define X1C2		LCDDATA0bits.S09C0
#define X2C2		LCDDATA4bits.S09C1
#define X3C2		LCDDATA8bits.S09C2
#define X4C2		LCDDATA12bits.S09C3
#define X5C2		LCDDATA16bits.S09C4
#define X6C2		LCDDATA20bits.S09C5
#define X7C2		LCDDATA24bits.S09C6
#define WHEEL1	 	LCDDATA28bits.S09C7
////
#define X1C3		LCDDATA0bits.S10C0
#define X2C3		LCDDATA4bits.S10C1
#define X3C3		LCDDATA8bits.S10C2
#define X4C3		LCDDATA12bits.S10C3
#define X5C3		LCDDATA16bits.S10C4
#define X6C3		LCDDATA20bits.S10C5
#define X7C3		LCDDATA24bits.S10C6
#define WHEEL2		LCDDATA28bits.S10C7

#define X1C4		LCDDATA0bits.S11C0
#define X2C4		LCDDATA4bits.S11C1
#define X3C4		LCDDATA8bits.S11C2
#define X4C4		LCDDATA12bits.S11C3
#define X5C4		LCDDATA16bits.S11C4
#define X6C4		LCDDATA20bits.S11C5
#define X7C4		LCDDATA24bits.S11C6
#define WHEEL3		LCDDATA28bits.S11C7

#define X1C5		LCDDATA0bits.S15C0
#define X2C5		LCDDATA4bits.S15C1
#define X3C5		LCDDATA8bits.S15C2
#define X4C5		LCDDATA12bits.S15C3
#define X5C5		LCDDATA16bits.S15C4
#define X6C5		LCDDATA20bits.S15C5
#define X7C5		LCDDATA24bits.S15C6
#define WHEEL4		LCDDATA28bits.S15C7

#define X1C6		LCDDATA1bits.S16C0
#define X2C6		LCDDATA5bits.S16C1
#define X3C6		LCDDATA9bits.S16C2
#define X4C6		LCDDATA13bits.S16C3
#define X5C6		LCDDATA17bits.S16C4
#define X6C6		LCDDATA21bits.S16C5
#define X7C6		LCDDATA25bits.S16C6
#define WHEEL5		LCDDATA29bits.S16C7

#define X1C7		LCDDATA1bits.S17C0
#define X2C7		LCDDATA5bits.S17C1
#define X3C7		LCDDATA9bits.S17C2
#define X4C7		LCDDATA13bits.S17C3
#define X5C7		LCDDATA17bits.S17C4
#define X6C7		LCDDATA21bits.S17C5
#define X7C7		LCDDATA25bits.S17C6
#define WHEEL6		LCDDATA29bits.S17C7

#define X1C8		LCDDATA1bits.S19C0
#define X2C8		LCDDATA5bits.S19C1
#define X3C8		LCDDATA9bits.S19C2
#define X4C8		LCDDATA13bits.S19C3
#define X5C8		LCDDATA17bits.S19C4
#define X6C8		LCDDATA21bits.S19C5
#define X7C8		LCDDATA25bits.S19C6
#define WHEEL7		LCDDATA29bits.S19C7

#define X1C9		LCDDATA1bits.S20C0
#define X2C9		LCDDATA5bits.S20C1
#define X3C9		LCDDATA9bits.S20C2
#define X4C9		LCDDATA13bits.S20C3
#define X5C9		LCDDATA17bits.S20C4
#define X6C9		LCDDATA21bits.S20C5
#define X7C9		LCDDATA25bits.S20C6
#define WHEEL8		LCDDATA29bits.S20C7

#define X1C10		LCDDATA1bits.S21C0
#define X2C10		LCDDATA5bits.S21C1
#define X3C10		LCDDATA9bits.S21C2
#define X4C10		LCDDATA13bits.S21C3
#define X5C10		LCDDATA17bits.S21C4
#define X6C10		LCDDATA21bits.S21C5
#define X7C10		LCDDATA25bits.S21C6
#define WHEEL9		LCDDATA29bits.S21C7

#define X1C11		LCDDATA1bits.S22C0
#define X2C11		LCDDATA5bits.S22C1
#define X3C11		LCDDATA9bits.S22C2
#define X4C11		LCDDATA13bits.S22C3
#define X5C11		LCDDATA17bits.S22C4
#define X6C11		LCDDATA21bits.S22C5
#define X7C11		LCDDATA25bits.S22C6
#define WHEEL10		LCDDATA29bits.S22C7

#define X1C12		LCDDATA1bits.S23C0
#define X2C12		LCDDATA5bits.S23C1
#define X3C12		LCDDATA9bits.S23C2
#define X4C12		LCDDATA13bits.S23C3
#define X5C12		LCDDATA17bits.S23C4
#define X6C12		LCDDATA21bits.S23C5
#define X7C12		LCDDATA25bits.S23C6
#define SUN 		LCDDATA29bits.S23C7

#define X1C12		LCDDATA1bits.S23C0
#define X2C12		LCDDATA5bits.S23C1
#define X3C12		LCDDATA9bits.S23C2
#define X4C12		LCDDATA13bits.S23C3
#define X5C12		LCDDATA17bits.S23C4
#define X6C12		LCDDATA21bits.S23C5
#define X7C12		LCDDATA25bits.S23C6
#define SUN 		LCDDATA29bits.S23C7

#define X1C13		LCDDATA1bits.S24C0
#define X2C13		LCDDATA5bits.S24C1
#define X3C13		LCDDATA9bits.S24C2
#define X4C13		LCDDATA13bits.S24C3
#define X5C13		LCDDATA17bits.S24C4
#define X6C13		LCDDATA21bits.S24C5
#define X7C13		LCDDATA25bits.S24C6
#define PAN 		LCDDATA29bits.S24C7

#define X1C14		LCDDATA1bits.S25C0
#define X2C14		LCDDATA5bits.S25C1
#define X3C14		LCDDATA9bits.S25C2
#define X4C14		LCDDATA13bits.S25C3
#define X5C14		LCDDATA17bits.S25C4
#define X6C14		LCDDATA21bits.S25C5
#define X7C14		LCDDATA25bits.S25C6
#define WIFI 		LCDDATA29bits.S25C7

#define X1C15		LCDDATA1bits.S26C0
#define X2C15		LCDDATA5bits.S26C1
#define X3C15		LCDDATA9bits.S26C2
#define X4C15		LCDDATA13bits.S26C3
#define X5C15		LCDDATA17bits.S26C4
#define X6C15		LCDDATA21bits.S26C5
#define X7C15		LCDDATA25bits.S26C6
#define ZIG 		LCDDATA29bits.S26C7

#define X1C16		LCDDATA2bits.S32C0
#define X2C16		LCDDATA6bits.S32C1
#define X3C16		LCDDATA10bits.S32C2
#define X4C16		LCDDATA14bits.S32C3
#define X5C16		LCDDATA18bits.S32C4
#define X6C16		LCDDATA22bits.S32C5
#define X7C16		LCDDATA26bits.S32C6
#define CLOUD 		LCDDATA30bits.S32C7

#define X1C17		LCDDATA2bits.S33C0
#define X2C17		LCDDATA6bits.S33C1
#define X3C17		LCDDATA10bits.S33C2
#define X4C17		LCDDATA14bits.S33C3
#define X5C17		LCDDATA18bits.S33C4
#define X6C17		LCDDATA22bits.S33C5
#define X7C17		LCDDATA26bits.S33C6
#define HEART 		LCDDATA30bits.S33C7


#define X1C18		LCDDATA2bits.S36C0
#define X2C18		LCDDATA6bits.S36C1
#define X3C18		LCDDATA10bits.S36C2
#define X4C18		LCDDATA14bits.S36C3
#define X5C18		LCDDATA18bits.S36C4
#define X6C18		LCDDATA22bits.S36C5
#define X7C18		LCDDATA26bits.S36C6
#define STRIP 		LCDDATA30bits.S36C7

#define X1C19		LCDDATA2bits.S37C0
#define X2C19		LCDDATA6bits.S37C1
#define X3C19		LCDDATA10bits.S37C2
#define X4C19		LCDDATA14bits.S37C3
#define X5C19		LCDDATA18bits.S37C4
#define X6C19		LCDDATA22bits.S37C5
#define X7C19		LCDDATA26bits.S37C6
#define BAT1 		LCDDATA30bits.S37C7

#define X1C20		LCDDATA2bits.S42C0
#define X2C20		LCDDATA6bits.S42C1
#define X3C20		LCDDATA10bits.S42C2
#define X4C20		LCDDATA14bits.S42C3
#define X5C20		LCDDATA18bits.S42C4
#define X6C20		LCDDATA22bits.S42C5
#define X7C20		LCDDATA26bits.S42C6
#define BAT2 		LCDDATA30bits.S42C7

#define X1C21		LCDDATA2bits.S43C0
#define X2C21		LCDDATA6bits.S43C1
#define X3C21		LCDDATA10bits.S43C2
#define X4C21		LCDDATA14bits.S43C3
#define X5C21		LCDDATA18bits.S43C4
#define X6C21		LCDDATA22bits.S43C5
#define X7C21		LCDDATA26bits.S43C6
#define BAT3 		LCDDATA30bits.S43C7

#define X1C22		LCDDATA2bits.S44C0
#define X2C22		LCDDATA6bits.S44C1
#define X3C22		LCDDATA10bits.S44C2
#define X4C22		LCDDATA14bits.S44C3
#define X5C22		LCDDATA18bits.S44C4
#define X6C22		LCDDATA22bits.S44C5
#define X7C22		LCDDATA26bits.S44C6
#define BAT4 		LCDDATA30bits.S44C7

#define X1C23		LCDDATA2bits.S45C0
#define X2C23		LCDDATA6bits.S45C1
#define X3C23		LCDDATA10bits.S45C2
#define X4C23		LCDDATA14bits.S45C3
#define X5C23		LCDDATA18bits.S45C4
#define X6C23		LCDDATA22bits.S45C5
#define X7C23		LCDDATA26bits.S45C6
#define DROP 		LCDDATA30bits.S45C7

#define X1C24		LCDDATA3bits.S49C0
#define X2C24		LCDDATA7bits.S49C1
#define X3C24		LCDDATA11bits.S49C2
#define X4C24		LCDDATA15bits.S49C3
#define X5C24		LCDDATA19bits.S49C4
#define X6C24		LCDDATA23bits.S49C5
#define X7C24		LCDDATA27bits.S49C6
#define THERMO 		LCDDATA31bits.S49C7

#define X1C25		LCDDATA3bits.S51C0
#define X2C25		LCDDATA7bits.S51C1
#define X3C25		LCDDATA11bits.S51C2
#define X4C25		LCDDATA15bits.S51C3
#define X5C25		LCDDATA19bits.S51C4
#define X6C25		LCDDATA23bits.S51C5
#define X7C25		LCDDATA27bits.S51C6
#define CEL 		LCDDATA31bits.S51C7

#define X1C26		LCDDATA3bits.S52C0
#define X2C26		LCDDATA7bits.S52C1
#define X3C26		LCDDATA11bits.S52C2
#define X4C26		LCDDATA15bits.S52C3
#define X5C26		LCDDATA19bits.S52C4
#define X6C26		LCDDATA23bits.S52C5
#define X7C26		LCDDATA27bits.S52C6
#define FAR 		LCDDATA31bits.S52C7

#define X1C27		LCDDATA3bits.S54C0
#define X2C27		LCDDATA7bits.S54C1
#define X3C27		LCDDATA11bits.S54C2
#define X4C27		LCDDATA15bits.S54C3
#define X5C27		LCDDATA19bits.S54C4
#define X6C27		LCDDATA23bits.S54C5
#define X7C27		LCDDATA27bits.S54C6
#define MICROCHIP 	LCDDATA31bits.S54C7

#define X1C28		LCDDATA3bits.S55C0
#define X2C28		LCDDATA7bits.S55C1
#define X3C28		LCDDATA11bits.S55C2
#define X4C28		LCDDATA15bits.S55C3
#define X5C28		LCDDATA19bits.S55C4
#define X6C28		LCDDATA23bits.S55C5
#define X7C28		LCDDATA27bits.S55C6
#define CENT     	LCDDATA31bits.S55C7

#define X1C29		LCDDATA3bits.S56C0
#define X2C29		LCDDATA7bits.S56C1
#define X3C29		LCDDATA11bits.S56C2
#define X4C29		LCDDATA15bits.S56C3
#define X5C29		LCDDATA19bits.S56C4
#define X6C29		LCDDATA23bits.S56C5
#define X7C29		LCDDATA27bits.S56C6
#define RMB     	LCDDATA31bits.S56C7

#define X1C30		LCDDATA3bits.S57C0
#define X2C30		LCDDATA7bits.S57C1
#define X3C30		LCDDATA11bits.S57C2
#define X4C30		LCDDATA15bits.S57C3
#define X5C30		LCDDATA19bits.S57C4
#define X6C30		LCDDATA23bits.S57C5
#define X7C30		LCDDATA27bits.S57C6
#define X1C37     	LCDDATA31bits.S57C7


#define X1C31		LCDDATA3bits.S58C0
#define X2C31		LCDDATA7bits.S58C1
#define X3C31		LCDDATA11bits.S58C2
#define X4C31		LCDDATA15bits.S58C3
#define X5C31		LCDDATA19bits.S58C4
#define X6C31		LCDDATA23bits.S58C5
#define X7C31		LCDDATA27bits.S58C6
#define X2C37     	LCDDATA31bits.S58C7



#define X1C32		LCDDATA3bits.S59C0
#define X2C32		LCDDATA7bits.S59C1
#define X3C32		LCDDATA11bits.S59C2
#define X4C32		LCDDATA15bits.S59C3
#define X5C32		LCDDATA19bits.S59C4
#define X6C32		LCDDATA23bits.S59C5
#define X7C32		LCDDATA27bits.S59C6
#define X3C37    	LCDDATA31bits.S59C7

#define X1C33		LCDDATA3bits.S60C0
#define X2C33		LCDDATA7bits.S60C1
#define X3C33		LCDDATA11bits.S60C2
#define X4C33		LCDDATA15bits.S60C3
#define X5C33		LCDDATA19bits.S60C4
#define X6C33		LCDDATA23bits.S60C5
#define X7C33		LCDDATA27bits.S60C6
#define X4C37    	LCDDATA31bits.S60C7


#define X1C34		LCDDATA3bits.S61C0
#define X2C34		LCDDATA7bits.S61C1
#define X3C34		LCDDATA11bits.S61C2
#define X4C34		LCDDATA15bits.S61C3
#define X5C34		LCDDATA19bits.S61C4
#define X6C34		LCDDATA23bits.S61C5
#define X7C34		LCDDATA27bits.S61C6
#define X5C37    	LCDDATA31bits.S61C7

#define X1C35		LCDDATA3bits.S62C0
#define X2C35		LCDDATA7bits.S62C1
#define X3C35		LCDDATA11bits.S62C2
#define X4C35		LCDDATA15bits.S62C3
#define X5C35		LCDDATA19bits.S62C4
#define X6C35		LCDDATA23bits.S62C5
#define X7C35		LCDDATA27bits.S62C6
#define X6C37    	LCDDATA31bits.S62C7

#define X1C36		LCDDATA3bits.S63C0
#define X2C36		LCDDATA7bits.S63C1
#define X3C36		LCDDATA11bits.S63C2
#define X4C36		LCDDATA15bits.S63C3
#define X5C36		LCDDATA19bits.S63C4
#define X6C36		LCDDATA23bits.S63C5
#define X7C36		LCDDATA27bits.S63C6
#define X7C37    	LCDDATA31bits.S63C7






#endif //EOF
