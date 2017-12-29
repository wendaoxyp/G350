/*****************************************************************************************************************
* FileName:        Banner.c
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
unsigned char Alp[6];
//char STR1[] = "Presenting PIC24FJ128GA310/";

//max nnumber of character per line should be less than 150
char* stringArray[25] = {
//"Presenting PIC24FJ128GA310",
"Presenting PIC24FJ128GA310 ",//0
"LCD with 8 Common and 480 Segments",//1
"DMA and VBAT with RTCC",//2
"Internal Resistor Bias and Charge Pump Bias",//3
"Low Power with Deep Sleep and Low Voltage Sleep",//4
"24 Channel 12-Bit ADC,24 Channel CTMU, 2-I2c Modules",//5
"5- 16 Bit Timers,4-Uart Modules,2-SPI Modules",//6
"7-Input capture ,7-Output compare , PWM",//7
"8K data RAM ,128Kb Programm Memory",//8
" to add more features ",//9
" to add more features  ",//10
" to add more features  ",//11
" to add more features  ",//12

" Ch Pump",//13
" R Bias",//14
" Temp",//15
" RTCC",//16
" Volt",//17
" Bias",//18
" Exit S3+S4",//19
" Swithcing to Resistor Bias",//20
" Switching Charge Pump Bias"//21

};

char STR1[] = "Four/";

unsigned char Length,StLength;
unsigned int X1,X2;
//char StrArray[10];

extern unsigned char CArr[37];
unsigned char Str[1000];// MAX BUFFER LENGHT FOR STRING
unsigned char *Strptr;
unsigned int Number,Counter,Rate;
unsigned char LineComplete;
unsigned int MaxLength;
unsigned char BanNum;
/*****************************************************************************
* Function: BannerInit
*
* Preconditions: None.
*
* Overview: 
*
* Input: None.
*
* Output: None.
*
******************************************************************************/
void BannerInit(void)
{
	MaxLength=0;
}
/*****************************************************************************
* Function: Banner
*
* Preconditions: None.
*
* Overview: 
*
* Input: None.
*
* Output: None.
*
******************************************************************************/
void Banner(void)
{
	Number=0;
	Counter=0;
	Rate=0;
	LineComplete=0;
}

/*****************************************************************************
* Function: BannerDisplay
*
* Preconditions: None.
*
* Overview: Initialize the Banner with the String
*
* Input: None.
*
* Output: None.
*
******************************************************************************/
void BannerDisplay(unsigned char StringNumber)
{
	unsigned char Chnum,Stnum;
	unsigned int Mlength;
    char *FillPtr;
	Stnum=StringNumber;
	FillPtr=stringArray[Stnum];
	Banner();
	Length=0;
	Chnum=1;
	X1=0;
	X2=0;
	for(Mlength=0;Mlength<=(MaxLength*6) ;Mlength++)//erase the buffer
		{
		Str[Mlength]=0;
		}
while(Chnum)
	{
//	Chnum=*stringArray[Stnum];
//	stringArray[StringNumber]++;
	Chnum=*FillPtr;
	FillPtr++;
	UpdateChar(Chnum);
	Length++;
	if(Length==44)
	{
	Nop();
	}
	Str[X1+X2]=Alp[X1];X1++;// array of 1000 bytes for the string
	Str[X1+X2]=Alp[X1];X1++;
	Str[X1+X2]=Alp[X1];X1++;
	Str[X1+X2]=Alp[X1];X1++;
	Str[X1+X2]=Alp[X1];X1++;
	Str[X1+X2]=Alp[X1];X1++;
	X2=X2+6;
	X1=0;
	if(Chnum==0)
	{
	Length--;
	Nop();
	if(MaxLength<Length)
		{
		MaxLength=Length;
		}
	}
	}

}


/*****************************************************************************
* Function: BannerUpdate
*
* Preconditions: None.
*
* Overview: Scrolls one String through the display till LineCOmplete=1
*
* Input: None.
*
* Output: None.
*
******************************************************************************/

void BannerUpdate(void)
{
	if(Rate==(6*Length)) // check for the lengh for char in Str[]
	{
	Rate=0;
	LineComplete=1; 		//one Line display complete
	}
	if(LineComplete==0)		//Skip when the one line display is complete
	{
		Strptr=&Str[Rate];
		Counter=0;
		Number=0;
		while(Counter<=36)
		{
		CArr[Number]=*Strptr;Strptr++;Number++;Counter++;
		UpdateBanner();
		}
		Rate++;
		VariableDelay();
	}
	if(Rate==255)
	{
	Nop();
	}

}



void InitChar(void)
{
unsigned char Chnum;
Length=0;
Chnum=0;
X1=0;
X2=0;
while(Chnum!='/')
{
Chnum=STR1[Length];
Length++;
UpdateChar(Chnum);
Str[X1+X2]=Alp[X1];X1++;
Str[X1+X2]=Alp[X1];X1++;
Str[X1+X2]=Alp[X1];X1++;
Str[X1+X2]=Alp[X1];X1++;
Str[X1+X2]=Alp[X1];X1++;
Str[X1+X2]=Alp[X1];X1++;
X2=X2+6;
X1=0;

}

}
/*****************************************************************************
* Function: UpdateChar
*
* Preconditions: None.
*
* Overview: Update the character set-Not all characters are updated , user 
* can modify each case depending on what format they need for the font or character
*
* Input: None.
*
* Output: None.
*
*Note each case statement has 6 values , each reptesenting one column.
*There are seven row 
*
*000000--->1
*000000--->2
*000000--->3
*000000--->4
*000000--->5
*000000--->6
*000000--->7
*||||||
*......
*123456
*
*So Alp[0]=  Column[1] Row[1-7] 
*Example of representing A
*
*00x000--->1
*0x0x00--->2
*x000x0--->3
*x000x0--->4
*xxxxx0--->5
*x000x0--->6
*x000x0--->7
*||||||
*123456
*Alp[0]=  Column[1] Row[1-7] =0x7C
*Alp[1]=  Column[2] Row[1-7] =0x12
*Alp[2]=  Column[3] Row[1-7] =0x22
*Alp[3]=  Column[4] Row[1-7] =0x23
*Alp[4]=  Column[5] Row[1-7] =0x7C
*Alp[5]=  Column[6] Row[1-7] =0x00 always maintain this zero for the spacing between character
*Note that in each row , row 1 is the lsb and row 7 is the msb, the 8th bit should always be 
*maintained zero
*******************************************************************************/

void UpdateChar(unsigned char ch)
{
	switch(ch)
	{
	case '+':
	Alp[0]=0x08;
	Alp[1]=0x08;
	Alp[2]=0x3E;
	Alp[3]=0x08;
	Alp[4]=0x08;
	Alp[5]=0;
	break;

	case 0:
	Alp[0]=0;
	Alp[1]=0;
	Alp[2]=0;
	Alp[3]=0;
	Alp[4]=0;
	Alp[5]=0;
	break;

	case 'A':
	Alp[0]=0x7C;
	Alp[1]=0x12;
	Alp[2]=0x11;
	Alp[3]=0x12;
	Alp[4]=0x7C;
	Alp[5]=0x0;	
	break;

	case 'a':
	Alp[0]=0x20;
	Alp[1]=0x54;
	Alp[2]=0x54;
	Alp[3]=0x54;
	Alp[4]=0x78;
	Alp[5]=0x0;	
	break;

    case 'B':
	Alp[0]=0x7F;
	Alp[1]=0x49;
	Alp[2]=0x49;
	Alp[3]=0x49;
	Alp[4]=0x36;
	Alp[5]=0x0;	
	break;

    case 'b':
	Alp[0]=0x7F;
	Alp[1]=0x48;
	Alp[2]=0x44;
	Alp[3]=0x44;
	Alp[4]=0x38;
	Alp[5]=0x0;	
	break;
       
    case 'C':
	Alp[0]=0x3E;
	Alp[1]=0x41;
	Alp[2]=0x41;
	Alp[3]=0x41;
	Alp[4]=0x22;
	Alp[5]=0x0;	
	break;

    case 'c':
	Alp[0]=0x38;
	Alp[1]=0x44;
	Alp[2]=0x44;
	Alp[3]=0x44;
	Alp[4]=0x20;
	Alp[5]=0x0;	
	break;

    case 'D':
	Alp[0]=0x7F;
	Alp[1]=0x41;
	Alp[2]=0x41;
	Alp[3]=0x22;
	Alp[4]=0x1C;
	Alp[5]=0x0;	
	break;

    case 'd':
	Alp[0]=0x38;
	Alp[1]=0x44;
	Alp[2]=0x44;
	Alp[3]=0x48;
	Alp[4]=0x7F;
	Alp[5]=0x0;	
	break;

    case 'E':
	Alp[0]=0x7F;
	Alp[1]=0x49;
	Alp[2]=0x49;
	Alp[3]=0x49;
	Alp[4]=0x41;
	Alp[5]=0x0;	
	break;

    case 'e':
	Alp[0]=0x38;
	Alp[1]=0x54;
	Alp[2]=0x54;
	Alp[3]=0x54;
	Alp[4]=0x18;
	Alp[5]=0x0;	
	break;

    case 'F':
	Alp[0]=0x7F;
	Alp[1]=0x09;
	Alp[2]=0x09;
	Alp[3]=0x09;
	Alp[4]=0x01;
	Alp[5]=0x0;	
	break;

    case 'f':
	Alp[0]=0x08;
	Alp[1]=0x7E;
	Alp[2]=0x09;
	Alp[3]=0x01;
	Alp[4]=0x02;
	Alp[5]=0x0;	
	break;

    case 'G':
	Alp[0]=0x3E;
	Alp[1]=0x41;
	Alp[2]=0x49;
	Alp[3]=0x49;
	Alp[4]=0x7A;
	Alp[5]=0x0;	
	break;

    case 'g':
	Alp[0]=0x08;
	Alp[1]=0x54;
	Alp[2]=0x54;
	Alp[3]=0x54;
	Alp[4]=0x3C;
	Alp[5]=0x0;	
	break;

    case 'H':
	Alp[0]=0x7F;
	Alp[1]=0x08;
	Alp[2]=0x08;
	Alp[3]=0x08;
	Alp[4]=0x7F;
	Alp[5]=0x0;	
	break;
    
    case 'h':
	Alp[0]=0x7F;
	Alp[1]=0x08;
	Alp[2]=0x04;
	Alp[3]=0x04;
	Alp[4]=0x78;
	Alp[5]=0x0;	
	break;

    case 'I':
	Alp[0]=0x00;
	Alp[1]=0x41;
	Alp[2]=0x7F;
	Alp[3]=0x41;
	Alp[4]=0x00;
	Alp[5]=0x0;	
	break;
  
    case 'i':
	Alp[0]=0x00;
	Alp[1]=0x48;
	Alp[2]=0x7D;
	Alp[3]=0x40;
	Alp[4]=0x00;
	Alp[5]=0x0;	
	break;

    case 'J':
	Alp[0]=0x20;
	Alp[1]=0x40;
	Alp[2]=0x41;
	Alp[3]=0x3F;
	Alp[4]=0x01;
	Alp[5]=0x0;	
	break;
    
    case 'j':
	Alp[0]=0x20;
	Alp[1]=0x40;
	Alp[2]=0x44;
	Alp[3]=0x3D;
	Alp[4]=0x00;
	Alp[5]=0x0;	
	break;

    case 'K':
	Alp[0]=0x7F;
	Alp[1]=0x08;
	Alp[2]=0x14;
	Alp[3]=0x22;
	Alp[4]=0x41;
	Alp[5]=0x0;	
	break;

    case 'k':
	Alp[0]=0x7F;
	Alp[1]=0x10;
	Alp[2]=0x28;
	Alp[3]=0x44;
	Alp[4]=0x00;
	Alp[5]=0x0;	
	break;

    case 'L':
	Alp[0]=0x7F;
	Alp[1]=0x40;
	Alp[2]=0x40;
	Alp[3]=0x40;
	Alp[4]=0x40;
	Alp[5]=0x0;	
	break;

    case 'l':
	Alp[0]=0x00;
	Alp[1]=0x41;
	Alp[2]=0x7F;
	Alp[3]=0x40;
	Alp[4]=0x00;
	Alp[5]=0x0;	
	break;

	case 'M':
	Alp[0]=0x7F;
	Alp[1]=0x02;
	Alp[2]=0x0C;
	Alp[3]=0x02;
	Alp[4]=0x7F;
	Alp[5]=0x0;	
	break;

	case 'm':
	Alp[0]=0x7C;
	Alp[1]=0x04;
	Alp[2]=0x78;
	Alp[3]=0x04;
	Alp[4]=0x78;
	Alp[5]=0x0;	
	break;
    
    case 'N':
	Alp[0]=0x7F;
	Alp[1]=0x04;
	Alp[2]=0x08;
	Alp[3]=0x10;
	Alp[4]=0x7F;
	Alp[5]=0x0;	
	break;

    case 'n':
	Alp[0]=0x7C;
	Alp[1]=0x08;
	Alp[2]=0x04;
	Alp[3]=0x04;
	Alp[4]=0x78;
	Alp[5]=0x0;	
	break;

    case 'O':
	Alp[0]=0x3E;
	Alp[1]=0x41;
	Alp[2]=0x41;
	Alp[3]=0x41;
	Alp[4]=0x3E;
	Alp[5]=0x0;	
	break;
 
    case 'o':
	Alp[0]=0x38;
	Alp[1]=0x44;
	Alp[2]=0x44;
	Alp[3]=0x44;
	Alp[4]=0x38;
	Alp[5]=0x0;	
	break;

    case 'P':
	Alp[0]=0x7F;
	Alp[1]=0x09;
	Alp[2]=0x09;
	Alp[3]=0x09;
	Alp[4]=0x06;
	Alp[5]=0x0;	
	break;

    case 'p':
	Alp[0]=0x7C;
	Alp[1]=0x14;
	Alp[2]=0x14;
	Alp[3]=0x14;
	Alp[4]=0x08;
	Alp[5]=0x0;	
	break;

    case 'Q':
	Alp[0]=0x3E;
	Alp[1]=0x41;
	Alp[2]=0x51;
	Alp[3]=0x21;
	Alp[4]=0x5E;
	Alp[5]=0x0;	
	break;

    case 'q':
	Alp[0]=0x08;
	Alp[1]=0x14;
	Alp[2]=0x14;
	Alp[3]=0x18;
	Alp[4]=0x7C;
	Alp[5]=0x0;	
	break;

    case 'R':
	Alp[0]=0x7F;
	Alp[1]=0x09;
	Alp[2]=0x19;
	Alp[3]=0x29;
	Alp[4]=0x46;
	Alp[5]=0x0;	
	break;

    case 'r':
	Alp[0]=0x7C;
	Alp[1]=0x08;
	Alp[2]=0x04;
	Alp[3]=0x04;
	Alp[4]=0x08;
	Alp[5]=0x0;	
	break;

    case 'S':
	Alp[0]=0x46;
	Alp[1]=0x49;
	Alp[2]=0x49;
	Alp[3]=0x49;
	Alp[4]=0x31;
	Alp[5]=0x0;	
	break;

    case 's':
	Alp[0]=0x48;
	Alp[1]=0x54;
	Alp[2]=0x54;
	Alp[3]=0x54;
	Alp[4]=0x20;
	Alp[5]=0x0;	
	break;

    case 'T':
	Alp[0]=0x01;
	Alp[1]=0x01;
	Alp[2]=0x7F;
	Alp[3]=0x01;
	Alp[4]=0x01;
	Alp[5]=0x0;	
	break;
    
    case 't':
	Alp[0]=0x04;
	Alp[1]=0x3F;
	Alp[2]=0x44;
	Alp[3]=0x40;
	Alp[4]=0x20;
	Alp[5]=0x0;	
	break;

    case 'U':
	Alp[0]=0x3F;
	Alp[1]=0x40;
	Alp[2]=0x40;
	Alp[3]=0x40;
	Alp[4]=0x3F;
	Alp[5]=0x0;	
	break;

    case 'u':
	Alp[0]=0x3C;
	Alp[1]=0x40;
	Alp[2]=0x40;
	Alp[3]=0x20;
	Alp[4]=0x7C;
	Alp[5]=0x0;	
	break;

    case 'V':
	Alp[0]=0x1F;
	Alp[1]=0x20;
	Alp[2]=0x40;
	Alp[3]=0x20;
	Alp[4]=0x1F;
	Alp[5]=0x0;	
	break;
    
    case 'v':
	Alp[0]=0x1C;
	Alp[1]=0x20;
	Alp[2]=0x40;
	Alp[3]=0x20;
	Alp[4]=0x1C;
	Alp[5]=0x0;	
	break;

    case 'W':
	Alp[0]=0x3F;
	Alp[1]=0x40;
	Alp[2]=0x38;
	Alp[3]=0x40;
	Alp[4]=0x3F;
	Alp[5]=0x0;	
	break;

    case 'w':
	Alp[0]=0x3C;
	Alp[1]=0x40;
	Alp[2]=0x38;
	Alp[3]=0x40;
	Alp[4]=0x3C;
	Alp[5]=0x0;	
	break;
    
    case 'X':
	Alp[0]=0x63;
	Alp[1]=0x14;
	Alp[2]=0x08;
	Alp[3]=0x14;
	Alp[4]=0x63;
	Alp[5]=0x0;	
	break;
  
    case 'x':
	Alp[0]=0x44;
	Alp[1]=0x28;
	Alp[2]=0x10;
	Alp[3]=0x28;
	Alp[4]=0x44;
	Alp[5]=0x0;	
	break;

    case 'Y':
	Alp[0]=0x07;
	Alp[1]=0x08;
	Alp[2]=0x70;
	Alp[3]=0x08;
	Alp[4]=0x07;
	Alp[5]=0x0;	
	break;
   
    case 'y':
	Alp[0]=0x0C;
	Alp[1]=0x50;
	Alp[2]=0x50;
	Alp[3]=0x50;
	Alp[4]=0x3C;
	Alp[5]=0x0;	
	break;

    case 'Z':
	Alp[0]=0x61;
	Alp[1]=0x51;
	Alp[2]=0x49;
	Alp[3]=0x45;
	Alp[4]=0x43;
	Alp[5]=0x0;	
	break;

    case 'z':
	Alp[0]=0x44;
	Alp[1]=0x64;
	Alp[2]=0x54;
	Alp[3]=0x4C;
	Alp[4]=0x44;
	Alp[5]=0x0;	
	break;

    case ';':
	Alp[0]=0x00;
	Alp[1]=0x56;
	Alp[2]=0x36;
	Alp[3]=0x00;
	Alp[4]=0x00;
	Alp[5]=0x0;	
	break;
    case ',':
	Alp[0]=0x00;
	Alp[1]=0x50;
	Alp[2]=0x30;
	Alp[3]=0x00;
	Alp[4]=0x00;
	Alp[5]=0x0;	
	break;
    case ':':
	Alp[0]=0x00;
	Alp[1]=0x36;
	Alp[2]=0x36;
	Alp[3]=0x00;
	Alp[4]=0x00;
	Alp[5]=0x0;	
	break;

    case '-':
	Alp[0]=0x00;
	Alp[1]=0x08;
	Alp[2]=0x08;
	Alp[3]=0x08;
	Alp[4]=0x00;
	Alp[5]=0x0;	
	break;

    case '1':
	Alp[0]=0x00;
	Alp[1]=0x42;
	Alp[2]=0x7F;
	Alp[3]=0x40;
	Alp[4]=0x00;
	Alp[5]=0x0;	
	break;

    case '2':
	Alp[0]=0x42;
	Alp[1]=0x61;
	Alp[2]=0x51;
	Alp[3]=0x49;
	Alp[4]=0x46;
	Alp[5]=0x0;	
	break;	

    case '3':
	Alp[0]=0x21;
	Alp[1]=0x41;
	Alp[2]=0x45;
	Alp[3]=0x4B;
	Alp[4]=0x31;
	Alp[5]=0x0;	
	break;

    case '4':
	Alp[0]=0x18;
	Alp[1]=0x14;
	Alp[2]=0x12;
	Alp[3]=0x7F;
	Alp[4]=0x10;
	Alp[5]=0x0;	
	break;

    case '5':
	Alp[0]=0x27;
	Alp[1]=0x45;
	Alp[2]=0x45;
	Alp[3]=0x45;
	Alp[4]=0x39;
	Alp[5]=0x0;	
	break;

    case '6':
	Alp[0]=0x3C;
	Alp[1]=0x4A;
	Alp[2]=0x49;
	Alp[3]=0x49;
	Alp[4]=0x30;
	Alp[5]=0x0;	
	break;

    case '7':
	Alp[0]=0x03;
	Alp[1]=0x01;
	Alp[2]=0x71;
	Alp[3]=0x09;
	Alp[4]=0x07;
	Alp[5]=0x0;	
	break;

    case '8':
	Alp[0]=0x36;
	Alp[1]=0x49;
	Alp[2]=0x49;
	Alp[3]=0x49;
	Alp[4]=0x36;
	Alp[5]=0x0;	
	break;

    case '9':
	Alp[0]=0x06;
	Alp[1]=0x49;
	Alp[2]=0x49;
	Alp[3]=0x29;
	Alp[4]=0x1E;
	Alp[5]=0x0;	
	break;

    case '0':
	Alp[0]=0x3E;
	Alp[1]=0x51;
	Alp[2]=0x49;
	Alp[3]=0x45;
	Alp[4]=0x3E;
	Alp[5]=0x0;	
	break;

    case '/':
	Alp[0]=0;
	Alp[1]=0;
	Alp[2]=0;
	Alp[3]=0;
	Alp[4]=0;
	Alp[5]=0;	
	break;

    case ' ':
	Alp[0]=0;
	Alp[1]=0;
	Alp[2]=0;
	Alp[3]=0;
	Alp[4]=0;
	Alp[5]=0;	
	break;



}



	

}
