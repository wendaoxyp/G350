/**
  LIN Master Application
	
  Company:
    Microchip Technology Inc.

  File Name:
    lin_app.h

  Summary:
    LIN Master Application

  Description:
    This header file provides the interface between the user and 
    the LIN drivers.

 */

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

#include "lin_master.h"

#ifndef LIN_APP_H
#define	LIN_APP_H


typedef enum {
    UNLOCK = 0x00,
    RSSI = 0x01,
    LFRX = 0x02
}lin_cmd_t;

uint8_t UNLOCK_Data[1];
uint8_t RSSI_Data[1];
uint8_t LFRX_Data[8];

const lin_cmd_packet_t scheduleTable[] = {
    //Command, Type, TX/RX Length, Timeout, Period, Data Address
    {UNLOCK, TRANSMIT, 1, 0, 100, UNLOCK_Data },
    {RSSI, TRANSMIT, 1, 0, 20, RSSI_Data },
    {LFRX, RECEIVE, 8, 100, 0, LFRX_Data }
};
#define TABLE_SIZE  (sizeof(scheduleTable)/sizeof(lin_cmd_packet_t))

void LIN_Master_Initialize(void);

void processLIN(void);

#endif	/* LIN_APP_H */

