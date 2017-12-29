/*****************************************************************************************************************
*
* FileName:        Switch.c
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




#include "Demo.h"
/*****************************************************************************
* Function: InitSwitches
*
* Preconditions: None.
*
* Overview: This function initiates Switches
*
* Input: None.
*
* Output: None.
*
******************************************************************************/

void InitSwtiches(void)
{
	SWITCH1_TRIS=1;
	SWITCH2_TRIS=1;
	SWITCH3_TRIS=1;
	SWITCH4_TRIS=1;
 
	SWITCH4_ANS=0; //
}

/*****************************************************************************
* Function: void SWxWaitRel(void)
*
* Preconditions: None.
*
* Overview: Wait for the Switch to be released
*
* Input: None.
*
* Output: None.
*
******************************************************************************/

void SWxWaitRel(void)
{
	while(!SW1);
	while(!SW2);
	while(!SW3);
	while(!SW4);
}



/*****************************************************************************
* Function: ScanSwitch
*
* Preconditions: None.
*
* Overview: Scan for Switch pressing
*
* Input: None.
*
* Output: None.
*
******************************************************************************/

void ScanSwitch (void)
{
	if(SW1==0)
	{
	Menu--;
//	LineComplete=1;
	while(SW1==0);
	}

	if(SW2==0)
	{
	Menu++;
//	LineComplete=1;
	while(SW2==0);
	}


	

	if(Menu==5)
	{	
	Menu=1;
	}
	if(Menu==0)
	{	
	Menu=4;

	}

}

