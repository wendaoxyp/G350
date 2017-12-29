#ifndef HL6528_H
#define HL6528_H
#include <xc.h>
#include <stdint.h>
#include "UART.h"
#include "SerialBuffer.h"
#include "Common.h"

#define PWRON_TRIS TRISDbits.TRISD6
#define PWRON LATDbits.LATD6
#define PWR_TRIS TRISDbits.TRISD7
#define PWR LATDbits.LATD7
#define RTS_TRIS TRISDbits.TRISD4
#define RTS LATDbits.LATD4
#define CTS_TRIS TRISDbits.TRISD5
#define CTS LATDbits.LATD5
#define DTR_TRIS TRISDbits.TRISD0
#define DTR LATDbits.LATD0
#define DSR_TRIS TRISDbits.TRISD1
#define DSR LATDbits.LATD1

extern void HL6528_Dialing(void* arg);
extern void HL6528_Init(void);


#endif



