#ifndef UART3_H
#define UART3_H

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>


extern void UART3_Init(void);
extern void UART3_Open(void);
extern void UART3_Close(void);
extern void UART3_SendChar(const uint8_t);
extern uint8_t UART3_SendString(const uint8_t *str, const uint8_t);
extern void U3Rx4Byte(void);

#endif

