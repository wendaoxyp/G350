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
#include "../mcc_generated_files/mcc.h"
#include <stdint.h>
//#include "CheckData.h"
//#include "SerialBuffer.h"
#include "Common.h"
//#include "UART3.h"
//#include <stdbool.h>

//typedef struct tagADD {
//    unsigned ADDL : 8;
//    unsigned ADDH : 8;
//} ADDBITS;
////extern volatile ADDBITS ADDbits;
//
//typedef struct tagARG1 {//含SPED CHAN参数
//    unsigned CHAN : 8;
//    unsigned AIRbps : 2;
//    unsigned : 1;
//    unsigned TTLbps : 3;
//    unsigned checkbit : 2;
//} ARG1BITS;
////extern volatile ARG1BITS ARG1bits;
//
//typedef struct tagARG2 {//含SPED CHAN参数
//    unsigned : 8;
//    unsigned sendPower : 2;
//    unsigned IODrive : 1;
//    unsigned FEC : 1;
//    unsigned waketime : 3;
//    unsigned MODBUS : 1;
//} ARG2BITS;
//extern volatile ARG2BITS ARG2bits;

extern void E41_Init(void);
extern void E41_SetArg(void);
extern void E41_SetMode(const uint8_t mode);
extern void E41_ReadArg(void);
extern void UART3_WriteBbuf(uint8_t* tmp, const uint8_t len) ;
//extern uint8_t E41_SetGetMode(const uint8_t);
//extern bool E41_PressureIsGet(float* pres);

#endif

