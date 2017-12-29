/*****************************************************************************************************************
*
* FileName:        RTCC.c
* Dependencies:    Demo.h
* Processor:       PIC24
* Compiler:        MPLAB C30 v3.30C or later
* Linker:          MPLAB LINK30
* Company:         Microchip Technology Incorporated
*
* Copyright 2011 Microchip Technology Inc.  All rights reserved.
*
* Microchip licenses to you the right use, modify, copy, and distribute the accompanying 
* Microchip demo code only when used with or embedded on a Microchip microcontroller or Microchip 
* digital signal controller that is integrated into your product or a third party product.  
* Any redistributions of Microchip’s demo code in compliance with the foregoing must include a copy 
* of this entire notice.  *\
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

#include "Demo.h"
/*****************************************************************************
* Function: RTCCInit
*
* Preconditions: None.
*
* Overview: initialize RTCC
*
* Input: None.
*
* Output: None.
*
******************************************************************************/
void RTCCInit()
	{	
	asm("MOV #NVMKEY, W1");//move the address of NVMKEY into W1
	asm("MOV #0x55, W2");//
	asm("MOV W2, [W1]");// ;start 55/AA sequence
	asm("MOV #0xAA, W3");//
	asm("MOV W3, [W1]");//
	asm("BSET RCFGCAL, #13 ");
	
//
//	RCFGCALbits.RTCPTR=3;
//	RTCVAL=0x0011;
//	RTCVAL=0x0501;
//	RTCVAL=0x0101;
//	RTCVAL=0x0000;
//	RTCPWCbits.RTCLK=1;   //clock is 01=LPRC      ;00= sosc
//	RCFGCALbits.RTCEN=1;

	RCFGCALbits.RTCPTR=3;
	RTCVAL=0x0000;
	RTCVAL=0x0000;
	RTCVAL=0x0000;
	RTCVAL=0x0000;
	RTCPWCbits.RTCLK=0;   //clock is 01=LPRC      ;00= sosc
	RCFGCALbits.RTCEN=1;

	
	
}



/*****************************************************************************
* Function: RTCCUpdate
*
* Preconditions: None.
*
* Overview: collect RTCC values
*
* Input: None.
*
* Output: None.
*
******************************************************************************/
void RTCCUpdate()
	{

			RCFGCALbits.RTCPTR=1;
			WKHRS=RTCVAL;
			HRS0=WKHRS&0x0F;
			HRS1=(WKHRS>>4)&0X0f;
			WK=(WKHRS>>8)&0X0f;

			MINSEC0=RTCVAL;
			SEC0=MINSEC0&0x0F;
			SEC1=(MINSEC0>>4)&0X0f;
			MIN0=(MINSEC0>>8)&0X0f;
			MIN1=(MINSEC0>>12)&0X0f;

	}




/*****************************************************************************
* Function: RTCCConfigure
*
* Preconditions: None.
*
* Overview: Confiigure RTCC to desired value
*
* Input: None.
*
* Output: None.
*
******************************************************************************/

void	RTCCConfigure(void)
{
	long int Mtime;
	Set=10;// to Indicate RTCC is being CONFIGUred
	LCDClearAll();
	SWxWaitRel();

	ScrollSpeed=3000;
		BanNum=19;
			BannerDisplay(BanNum);
		while(LineComplete==0)
			{
			BannerUpdate();
			}
	ScrollSpeed=2000;
	LCDClearAll();
	SEC1=0;
	SEC0=0;
	MIN1=0;
	MIN0=0;
	MICROCHIP=1;

	Col1(2);
while((SW4)||(SW3))
{
	MICROCHIP=1;
	if(SW1==0) SEC1++;
	if(SW2==0) SEC0++;
	if(SW3==0) MIN1++;
	if(SW4==0) MIN0++;


	if(SEC0==10)SEC0=0;
	if(MIN0==10)MIN0=0;

	if(SEC1==6)
	{
	SEC0=0;
	SEC1=0;
	}
	if(MIN1==6)
	{
	MIN0=0;
	MIN1=0;
	}


	Digit3(MIN1);
	Digit2(MIN0);
	Digit1(SEC1);
	Digit0(SEC0);

	SWxWaitRel();
	for(Mtime=0;Mtime<100000;Mtime++);
}
	SWxWaitRel();
	WK=1;
	HRS1=2;
	HRS0=3;
UpdateHrsWeek();
while((SW4)||(SW3))
{
	if(SW1==0) HRS1++;
	if(SW2==0) HRS0++;
	if(SW3==0) WK++;

	if(HRS1==3) HRS1=0;
	if(HRS1!=2)
	{
	if(HRS0==10)HRS0=0;
	}
	if(HRS1==2)
	{
	if(HRS0>=4)HRS0=3;
	}

	if(WK==7)WK=0;
	UpdateHrsWeek();
	Digit1(MIN1);
	Digit0(MIN0);

	for(Mtime=0;Mtime<100000;Mtime++);


}

	SWxWaitRel();



	WKHRS=WK<<8;
	WKHRS=(WKHRS)|(HRS1<<4);
	WKHRS=WKHRS|HRS0;
	MINSEC0=MIN1;
	MINSEC0=MINSEC0<<12;
	MINSEC0=(MINSEC0)|(MIN0<<8);
	MINSEC0=(MINSEC0)|(SEC1<<4);
	MINSEC0=(MINSEC0)|(SEC0);

	asm("MOV #NVMKEY, W1");//move the address of NVMKEY into W1
	asm("MOV #0x55, W2");//
	asm("MOV W2, [W1]");// ;start 55/AA sequence
	asm("MOV #0xAA, W3");//
	asm("MOV W3, [W1]");//
	asm("BSET RCFGCAL, #13 ");
	






	RCFGCALbits.RTCPTR=3;
	RTCVAL=0x0000;
	RTCVAL=0x0000;
	RTCVAL=WKHRS;
	RTCVAL=MINSEC0;


	RTCPWCbits.RTCLK=0;   //clock is 01=LPRC      ;00= sosc
	RCFGCALbits.RTCEN=1;

	


	Set=DONE;// configuration complete


}
