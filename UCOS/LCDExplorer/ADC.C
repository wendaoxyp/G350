/*****************************************************************************************************************
* FileName:        ADC.c
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


// Reference voltage, mV
#define AVCC                3300

int Value;
unsigned int 	_uADCTemperature;
unsigned long Result,Result1;
unsigned char Status,ADCBUFCOUNT,_uADCState;
unsigned long VDD_RES,VDD_RES1,VDD_RES2,ADCount;
//
/*****************************************************************************
* Function: ADCInit
*
* Preconditions: None.
*
* Overview: Initialize ADC
*
* Input: None.
*
* Output: None.
*
******************************************************************************/

void ADCInit(){
//  	AD1CON1 = 0x8074;
	ADCBUFCOUNT=0;
	ADC_POT_TRIS=1;
	ADC_TEMP_TRIS=1;
	ADC_POT_CHANNEL=1; 			//Analog POT           //AN11
	ADC_TEMP_CHANNEL=1;			// temp sensor //AN20


 	AD1CSSL = 0x0800; // AN11
    AD1CSSH = 0xD010; // Include 4 channels in scan (VBG, VSS, VDD and VBAT), AN20
    AD1CON1 = 0x0070; // Internal counter triggers conversion
    AD1CON3 = 0x1F1F; // Sample time = 15Tad, Tad = Tcy

    AD1CON2 = 0x040C; // Set AD1IF after every 4 samples, enable scanning
    AD1CON5 = 0x1000; // Enable Band Gap
    AD1CON1bits.ADON = 1; // turn ADC ON
//BUF0=Voltmeter reading
//BUF1=Temperature sensor
//BUF2=Bandgap
//BUF3=VDD

        IFS0bits.AD1IF = 0; 
        AD1CON1bits.ASAM = 1; 		// auto start sampling 
        while (!IFS0bits.AD1IF){}; 	// conversion done
        AD1CON1bits.ASAM = 0; 		// yes then stop sample/convert

//VDD=(1.2/ADC_VBG)*1023
		VDD_RES=(long )ADC1BUF3;
		VDD_RES=(VDD_RES*120);//bandgap 1.2    +/-5 percent
		VDD_RES1=(long )ADC1BUF2;
		VDD_RES2=(VDD_RES/VDD_RES1)*10;
		Nop();





	_uADCState=0;
}

/*****************************************************************************
* Function: ADCEvents
*
* Preconditions: None.
*
* Overview:Scans ADC channels and update buffers
*
* Input: None.
*
* Output: None.
*
******************************************************************************/


void ADCEvents()
{
    switch(_uADCState){
        case 0: 
	        IFS0bits.AD1IF = 0; 
	        AD1CON1bits.ASAM = 1; 		// auto start sampling 
	        while (!IFS0bits.AD1IF){}; 	// conversion done
	        AD1CON1bits.ASAM = 0; 		// yes then stop sample/convert
			//VDD=(1.2/ADC_VBG)*1023
			VDD_RES=(long )ADC1BUF3;
			VDD_RES=(VDD_RES*120);//bandgap 1.2    +/-5 percent
			VDD_RES1=(long )ADC1BUF2;
			VDD_RES2=(VDD_RES/VDD_RES1)*10;
			Nop();



        case 1:  
			ADCount=0; 
     		Result = (long) ADC1BUF0;
          	Result = (Result*VDD_RES2)/1024;
		  	Value=Result;
		  	Result=Value/1000;
			DIG2=Result;
			Value=Value-(1000*Result);
		  	Result=Value/100;
			DIG1=Result;			
			Value=Value-(100*Result);
		  	Result=Value/10;
			DIG0=Result;			
          _uADCState++;
          break;

        case 2:          // Convert result for temperature  
 //    while(!AD1CON1bits.DONE);          
          Result = (long) ADC1BUF1;  
          Result = (Result*VDD_RES2)/1024;
	      Result = (Result-500)/10;		
			Result=Result*10;
	      	Value=Result;
			Result=Value/1000;
			TCDIG2=Result;
			Value=Value-(1000*Result);
		  	Result=Value/100;
			TCDIG1=Result;			
			Value=Value-(100*Result);
		  	Result=Value/10;
			TCDIG0=Result;		
          _uADCState++;
		break;
		

        case 3:          // Convert result for temperature  
//     while(!AD1CON1bits.DONE);          
	   		Result = (long) ADC1BUF1;   
	       	Result = (Result*VDD_RES2)/1024;
		   	Result = (Result-500)/10;	
	
			Result *= 9; Result /= 5; Result += 32;
				
			Result=Result*10;
		 	Value=Result;
			Result=Value/1000;
			TFDIG2=Result;
			Value=Value-(1000*Result);
			Result=Value/100;
			TFDIG1=Result;			
			Value=Value-(100*Result);
			Result=Value/10;
			TFDIG0=Result;		
			AD1CHS=ADC_VOLTAGE; 		//AD for ANALOg pot
          _uADCState++;
		break;
      case 4:          // Delay++
//	        IFS0bits.AD1IF = 0; 
//	        AD1CON1bits.ASAM = 1; 		// auto start sampling 
//	        while (!IFS0bits.AD1IF){}; 	// conversion done
//	        AD1CON1bits.ASAM = 0; 		// yes then stop sample/convert
//			//VDD=(1.2/ADC_VBG)*1023
//			VDD_RES=(long )ADC1BUF3;
//			VDD_RES=(VDD_RES*120);//bandgap 1.2    +/-5 percent
//			VDD_RES1=(long )ADC1BUF2;
//			VDD_RES2=(VDD_RES/VDD_RES1)*10;
//			Nop();
//

          _uADCState++;
		break;
      case 5:          // Delay++
			ADCount++;
			if(ADCount==1000)(  _uADCState=0);
		break;

		}
		

}

