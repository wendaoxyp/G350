/**
  LIN Master Driver
	
  Company:
    Microchip Technology Inc.

  File Name:
    lin_master.h

  Summary:
    LIN Master Driver

  Description:
    This header file provides the driver for LIN master nodes

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

#ifndef LIN_H
#define	LIN_H
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

typedef enum {
    LIN_IDLE,
    LIN_TX_IP,
    LIN_RX_IP,
    LIN_RX_RDY
}lin_state_t;

typedef enum {
    TRANSMIT,
    RECEIVE
}lin_packet_type_t;

typedef struct {
    uint8_t cmd;
    lin_packet_type_t type;
    uint8_t length;
    uint8_t timeout;
    uint8_t period;
    uint8_t* data;
}lin_cmd_packet_t;

typedef union {
    struct {
        uint8_t PID;
        uint8_t data[8];
        uint8_t checksum;
        uint8_t length;
    };
    uint8_t rawPacket[11];
}lin_packet_t;

typedef union {
    struct {
        uint8_t cmd;
        uint8_t rxLength;
        uint8_t data[8];
        uint8_t checksum;
        uint8_t timeout;
    };
    uint8_t rawPacket[12];
}lin_rxpacket_t;

typedef union {
    struct {
        unsigned ID0: 1;
        unsigned ID1: 1;
        unsigned ID2: 1;
        unsigned ID3: 1;
        unsigned ID4: 1;
        unsigned ID5: 1;
        unsigned P0: 1;
        unsigned P1: 1;
    };
    uint8_t rawPID;
}lin_pid_t;

//Set up schedule table timings

void LIN_init(uint8_t tableLength, const lin_cmd_packet_t* const table, void (*processData)(void));

void LIN_queuePacket(uint8_t cmd, uint8_t* data);

bool LIN_receivePacket(void);

void LIN_sendPacket(void);

uint8_t LIN_getPacket(uint8_t* data);

lin_state_t LIN_handler(void);

uint8_t LIN_getChecksum(uint8_t length, uint8_t* data);

uint8_t LIN_calcParity(uint8_t CMD);

//Timer Functions
void LIN_startTimer(uint8_t timeout);

void LIN_timerHandler(void);

void LIN_setTimerHandler(void);

void LIN_stopTimer(void);

void LIN_startPeriod(void);

void LIN_stopPeriod(void);

void LIN_enableRx(void);

void LIN_disableRx(void);

void LIN_sendBreak(void);

void LIN_sendPeriodicTx(void);


#endif	/* LIN_H */

