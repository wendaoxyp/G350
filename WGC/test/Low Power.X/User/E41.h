#ifndef E41_H
#define E41_H

/******************************************************************
 * M0       M1          模式
 * 0        0           一般模式
 * 1        1           唤醒模式
 * 0        1           省电模式
 * 1        1           休眠模式
 *******************************************************************/
#include <xc.h>
#include <stdint.h>
#include "CheckData.h"
#include "SerialBuffer.h"
#include "UART3.h"
#include "INT.h"

#define M0_TRIS TRISEbits.TRISE5
#define M1_TRIS TRISEbits.TRISE6
#define M0 LATEbits.LATE5
#define M1 LATEbits.LATE6
#define M0_PORT PORTEbits.RE5
#define M1_PORT PORTEbits.RE6
#define AUX PORTFbits.RF6

#define WORK 0
#define WAKE 1
#define LOWPOWER 2
#define SLEEP 3

extern void E41_Init(void);
//extern void E41_SetArg(void);
//extern uint8_t E41_SetGetMode(const uint8_t);
extern bool E41_PressureIsGet(float* pres);
extern void E41_Active_Send(void);
#endif

