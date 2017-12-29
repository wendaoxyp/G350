/*****************************************************************************************************************
* LCD Explorer Demo program
******************************************************************************************************************
* FileName:        Main.c
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
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Author           Date             Comment
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Naveen Raj       11/18/2011       Demo code for PIC24F128GA310 for LCD explorer
******************************************************************************************************************/


#include "Demo.h"
_CONFIG1(FWDTEN_WDT_DIS & ICS_PGx3 & JTAGEN_OFF);       
_CONFIG2(POSCMD_NONE &OSCIOFCN_ON & FCKSM_CSDCMD & FNOSC_FRC & IESO_OFF);                                         // FRC Oscillator with PLL
_CONFIG3(SOSCSEL_ON & BOREN_ON);


void Delay(void);
int del1,del2,del3,del;
unsigned int ScrollSpeed;
unsigned char Menu,MenuLast,Set,ChangeBias,RStatus,CStatus;
int main(void)
{


	InitSwtiches();
	ScrollSpeed=6000;
	ADCInit();
	LCDInit();
	BannerInit();
	LCDClearAll();

	BanNum=0;
while(SW1&SW2)
{

	BannerDisplay(BanNum);
	while(LineComplete==0)
	{
	BannerUpdate();
	ScrollSpeedScan();
	if((SW1&SW2)!=1) break;
	}
	if((SW1&SW2)!=1) break;
	LCDClearAll();
	BanNum++;
	if(BanNum==9) BanNum=0;// max number of features in stringArray


}
	LCDClearAll();
	RTCCInit();

	Menu=1;
	MenuLast=0;
	Set=0;
	LCDClearAll();
	ADCEvents();
	SWxWaitRel();
	ScrollSpeed=2000;

	
while(1)
{
	ADCEvents();
	RTCCUpdate();
//	LCDBiasUpdate();
	VDDMonitor();

	switch(Menu)
	{
	case 1:
		LCDREFbits.LCDCST=0;
		LCDREGbits.BIAS=5;
		if(Menu!=MenuLast) 
		{
		VoltageBanner();			//display only  when entering the mode
		}
		DisplayVoltage();;
	break;
	case 2:
		LCDREGbits.BIAS=5;
		LCDREFbits.LCDCST=0;
		if(Menu!=MenuLast)
		{
  		TemperatureBanner();		//display only  when entering the mode
		}
		if(SEC0<5)
		DisplayTempC();
		else
		DisplayTempF();
		break;
	case 3:
		LCDREFbits.LCDCST=0;
		LCDREGbits.BIAS=5;

		if((SW3==0)||(SW4==0))
		{
		RTCCConfigure();;// if required to chage date time etc
		}
		if(Menu!=MenuLast) 		
		{
 		RTCCBanner();			//display only  when entering the mode
		}
		DisplayRTCC();
	break;
	case 4:
		if(Menu!=MenuLast)
		{
		BiasDisplay();		//display only  when entering the mode
		}
		ContrastUpdate();
		break;
	}
	MenuLast=Menu;
	ScanSwitch();
	if(Menu!=MenuLast)
	{
	LCDClearAll();	
	}


}


}


/*****************************************************************************
* Function:VDDMonitor()
*
* Preconditions: None.
*
* Overview: Check to monitor the VDD to Switch Between Charge Pump or resistor Ladder
*
* Input: None.
*
* Output: None.
*
******************************************************************************/

void VDDMonitor(void)
{
//	LCDBiasUpdate();
	if(VDD_RES2<2700)// enable charge pump if required
	{
		if(CStatus)
		ChangeBias=0;
		else
		ChangeBias=1;
	}
	else			//enable internal resistor ladder if required
	{
		if(RStatus)
		ChangeBias=0;
		else
		ChangeBias=1;
	}

	



	if(ChangeBias)
	{
	LCDBiasUpdate();
	ChangeBias=0;

	ScrollSpeed=3000;
	if(RStatus==1)
	{
		BanNum=20;
			BannerDisplay(BanNum);
			while(LineComplete==0)
			{
			BannerUpdate();
			}
	}
	if(CStatus==1)
	{
		BanNum=21;
			BannerDisplay(BanNum);
			while(LineComplete==0)
			{
			BannerUpdate();
			}
	}

	ScrollSpeed=2000;



	}




}










/*****************************************************************************
* Function:VoltageBanner
*
* Preconditions: None.
*
* Overview: Displays Volt banner
*
* Input: None.
*
* Output: None.
*
******************************************************************************/

void VoltageBanner(void)
{
			BanNum=17;
			BannerDisplay(BanNum);
		while(LineComplete==0)
			{
			BannerUpdate();
			if((SW1&SW2)!=1) break;
			}	
	SWxWaitRel();
	LCDClearAll();
}
/*****************************************************************************
* Function:RTCCBanner
*
* Preconditions: None.
*
* Overview: Displays RTCC banner
*
* Input: None.
*
* Output: None.
*
******************************************************************************/
void RTCCBanner(void)
{
			BanNum=16;
			BannerDisplay(BanNum);
		while(LineComplete==0)
			{
			BannerUpdate();
			if((SW1&SW2)!=1) break;
			}	
	SWxWaitRel();
	LCDClearAll();
}
/*****************************************************************************
* Function:TemperatureBanner
*
* Preconditions: None.
*
* Overview: Displays Temp banner
*
* Input: None.
*
* Output: None.
*
******************************************************************************/
void TemperatureBanner(void)
{
			BanNum=15;
			BannerDisplay(BanNum);
		while(LineComplete==0)
			{
			BannerUpdate();
			if((SW1&SW2)!=1) break;
			}	
	SWxWaitRel();
	LCDClearAll();
}
/*****************************************************************************
* Function:BiasDisplay
*
* Preconditions: None.
*
* Overview: Displays Bias banner
*
* Input: None.
*
* Output: None.
*
******************************************************************************/

void BiasDisplay(void)
{

		LCDClearAll();	
		if(VDD_RES2<2700)				//enable charge pump and keep monitoring VDD		
		{
			_uADCState=0;
			ADCEvents();
			BanNum=13;
			BannerDisplay(BanNum);
			while(LineComplete==0)
			{
			BannerUpdate();
			if((SW1&SW2)!=1) break;
			}
		}
		else
		{
			_uADCState=0;
			ADCEvents();
			BanNum=14;
			BannerDisplay(BanNum);
			while(LineComplete==0)
			{
			BannerUpdate();
			if((SW1&SW2)!=1) break;
			}

		}
	
	SWxWaitRel();
	LCDClearAll();
}






/*****************************************************************************
* Function: Delay
*
* Preconditions: None.
*
* Overview: Delay
*
* Input: None.
*
* Output: None.
*
******************************************************************************/

void Delay(void)
{
for(del=0;del<100;del++)
	{
	for(del1=0;del1<10;del1++);
	}
}
/*****************************************************************************
* Function: VariableDelay
*
* Preconditions: None.
*
* Overview: Delay
*
* Input: None.
*
* Output: None.
*
******************************************************************************/

void VariableDelay(void)
{
for(del2=0;del2<ScrollSpeed;del2++)
	{
	for(del3=0;del3<10;del3++);
	}
}

/*****************************************************************************
* Function: ScrollSpeedScan
*
* Preconditions: None.
*
* Overview: This scan swtich to increase decrease banner speed
*
* Input: None.
*
* Output: None.
*
******************************************************************************/
void ScrollSpeedScan(void)
{
	if(SW4==0)
	{ ScrollSpeed=ScrollSpeed-500;
	 Delay();
	}
	if(SW3==0) 
	{ScrollSpeed=ScrollSpeed+500; 
	Delay();
	}
	if(ScrollSpeed<=500) ScrollSpeed=500;

}
