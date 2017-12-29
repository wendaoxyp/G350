#ifndef HL6528_H
#define HL6528_H
#include <xc.h>
#include <stdint.h>
#include <stddef.h>
#include "UART2.h"
#include "SerialBuffer.h"
#include "Common.h"
#include "WGC.h"


#define PWRON_TRIS TRISDbits.TRISD6
#define PWRON LATDbits.LATD6
#define PWR_TRIS TRISDbits.TRISD7
#define PWR LATDbits.LATD7
#define RTS_TRIS TRISDbits.TRISD4
#define RTS LATDbits.LATD4
#define CTS_TRIS TRISDbits.TRISD5
#define CTS LATDbits.LATD5
#define DTR_TRIS TRISDbits.TRISD1
#define DTR LATDbits.LATD1
#define DSR_TRIS TRISFbits.TRISF1
#define DSR LATFbits.LATF1



extern uint8_t HL6528_DialingIsERR(void);
extern void HL6528_Init(void);
extern void HL6528_Close(uint8_t);
extern void HL6528_GetIP_Port(void);
//extern void GPRS_Task(void);


#endif




