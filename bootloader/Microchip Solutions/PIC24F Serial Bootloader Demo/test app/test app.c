/********************************************************************
* FileName:		test app.c
* Dependencies:    
* Processor:	PIC24F Family
* Hardware:		Explorer 16
* Compiler:		C30 3.00 or later
* Company:		Microchip Technology, Inc.
*
* Software License Agreement
*
* The software supplied herewith by Microchip Technology Incorporated
* (the “Company”) for its PICmicro® Microcontroller is intended and
* supplied to you, the Company’s customer, for use solely and
* exclusively on Microchip PICmicro Microcontroller products. The
* software is owned by the Company and/or its supplier, and is
* protected under applicable copyright laws. All rights are reserved.
* Any use in violation of the foregoing restrictions may subject the
* user to criminal sanctions under applicable laws, as well as to
* civil liability for the breach of the terms and conditions of this
* license.
*
* THIS SOFTWARE IS PROVIDED IN AN “AS IS” CONDITION. NO WARRANTIES,
* WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
* TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
* PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
* IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
* CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
*
* 
* File Description:
*
* This is a demo user application to test the PIC24F Seial Bootloader
* This application is for the Explorer 16 demo board
*
*
* Change History:
*
* Author      	Revision #      Date        Comment
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Brant Ivey	1.00   			1-17-2008	Initial release of AN1157
********************************************************************/
#include "p24fxxxx.h"


//Configuration **************************
_CONFIG1(JTAGEN_OFF & GWRP_OFF & ICS_PGx1 & FWDTEN_OFF )
_CONFIG2(POSCMOD_HS & FNOSC_PRIPLL & OSCIOFNC_ON)
//****************************************

//Prototypes *****************************
void _ToggleLED(void);
void _T1Interrupt();
void _T2Interrupt();
void ISRTable(); //Pseudo function to hold ISR remap jump table
//****************************************


//Defines ********************************
#ifdef __PIC24FJ64GA004__	//For compatability with 24FJ64GA004 PIM
	#define BL_ENTRY_BUTTON PORTAbits.RA9
#else
	#define BL_ENTRY_BUTTON PORTDbits.RD7
#endif


//If defined, the reset vector pointer and boot mode entry delay
// value will be stored in the device's vector space at addresses 0x100 and 0x102
#define USE_VECTOR_SPACE
//****************************************

//Bootloader Vectors *********************
#ifdef USE_VECTOR_SPACE
	/*
		Store delay timeout value & user reset vector at 0x100 
		(can't be used with bootloader's vector protect mode).
		
		Value of userReset should match reset vector as defined in linker script.
		BLreset space must be defined in linker script.
	*/
	unsigned int userReset  __attribute__ ((space(prog),section(".BLreset"))) = 0xC00 ;  
	unsigned char timeout  __attribute__ ((space(prog),section(".BLreset"))) = 0xA ;
#else
	/*
		Store delay timeout value & user reset vector at start of user space
	
		Value of userReset should be the start of actual program code since 
		these variables will be stored in the same area.
	*/
	unsigned int userReset  __attribute__ ((space(prog),section(".init"))) = 0xC04 ;
	unsigned char timeout  __attribute__ ((space(prog),section(".init"))) = 0x0A ;
#endif
//****************************************

int main(void)
{

	AD1PCFG = 0xFFFF;

	//make I/O output
	#ifdef __PIC24FJ64GA004__	//For compatability with 24FJ64GA004 PIM
		TRISAbits.TRISA10 = 0;
		TRISAbits.TRISA7 = 0;
		TRISBbits.TRISB8 = 0;
		TRISAbits.TRISA9 = 1;
  #else
		TRISAbits.TRISA0 = 0;	
		TRISAbits.TRISA1 = 0;
		TRISAbits.TRISA2 = 0;
		TRISDbits.TRISD7 = 1;
	#endif

	IEC0bits.T1IE = 1;
	IFS0bits.T1IF = 0;
	PR1 = 0xFFFF;
	T1CON = 0x8010;

	IEC0bits.T2IE = 1;
	IFS0bits.T2IF = 0;
	PR2 = 0xFFFF;
	T2CON = 0x8020;


	while(1)
	{
		_ToggleLED();		

		if(BL_ENTRY_BUTTON == 0){
			//disable interrupts so they do not affect BL operation
			T1CON = 0;
			T2CON = 0;
			IEC0bits.T1IE = 0;
			IEC0bits.T1IE = 0;

			//setup and call bootloader
			RCON = 0;
			asm("goto 0x400");
		}	
	}

}//end main()



void _ToggleLED(void)
{
	static int count = 0;
	
	if(++count == 0)
	{
		//Toggle LED D5
		#ifdef __PIC24FJ64GA004__
			LATBbits.LATB8 ^= 1;
        #else
			LATAbits.LATA2 ^= 1;
		#endif	
	}
}

//Interrupt Remap method 1:  Using direct interrupt address
void __attribute__ ((interrupt,address(0xF00),no_auto_psv)) _T1Interrupt(){

	IFS0bits.T1IF = 0;

	//Toggle LED D3
	#ifdef __PIC24FJ64GA004__
		LATAbits.LATA10 ^= 1;
    #else
		LATAbits.LATA0 ^= 1;
	#endif		
}


//Interrupt Remap method 2:  Using Goto and jump table
void __attribute__ ((interrupt,no_auto_psv)) _T2Interrupt(){

	IFS0bits.T2IF = 0;

	//Toggle LED D4
	#ifdef __PIC24FJ64GA004__
		LATAbits.LATA7 ^= 1;
    #else
		LATAbits.LATA1 ^= 1;
	#endif		
}


/*
 *	ISR JUMP TABLE
 *
 *	It is necessary to define jump table as a function because C30 will
 *	not store 24-bit wide values in program memory as variables.
 *
 *	This function should be stored at an address where the goto instructions 
 *	line up with the remapped vectors from the bootloader's linker script.
 */
void __attribute__ ((address(0x1000))) ISRTable(){

	asm("reset"); //reset instruction to prevent runaway code
	asm("goto %0"::"i"(&_T2Interrupt));  //T2Interrupt's address
}
