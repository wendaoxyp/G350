/*****************************************************************************************************************
*
* FileName:        Demo.h
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
#ifndef DEMO_H
#define DEMO_H
#include <p24FJ128GA310.h>
#include "LCD.h"
#include "ADC.h"
#include "Display.h"
#include "Switch.h"
#include "RTCC.h"
#include "Contrast.h"
#include "Banner.h"
extern unsigned char Menu,Set,ChangeBias,RStatus,CStatus;
extern unsigned int ScrollSpeed;
extern void Delay(void);
extern void VariableDelay(void);
extern void BiasDisplay(void);
extern void ScrollSpeedScan(void);
extern void VoltageBanner(void);
extern void RTCCBanner(void);
extern void TemperatureBanner(void);
extern int del1,del2,del3,del;
extern void VDDMonitor(void);

#endif //eof

