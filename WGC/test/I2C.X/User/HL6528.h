#ifndef HL6528_H
#define HL6528_H
#include <xc.h>
#include <stdint.h>
#include <stddef.h>
#include "UART2.h"
#include "SerialBuffer.h"
#include "Common.h"
#include "WCG.h"


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

//#define HL6828_SENDSTRING(x,y) UART2SendString2(x,y)

extern bool HL6528_DialingIsERR(void);
//extern void HL6528_GetIP_Port(uint8_t* dat);
extern void HL6528_Init(void);
extern void HL6528_Close(void);
//static bool HL6528SendCmd(const uint8_t *ss, const uint8_t* cs, const uint8_t csl, const uint8_t cnt);
#endif




