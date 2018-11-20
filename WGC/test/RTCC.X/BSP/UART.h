#ifndef UART_H
#define UART_H

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>


extern void UART2_Init(void);
extern void UART2_Open(void);
extern void UART2_Close(void);
extern void UART2_SendChar(const uint8_t);
extern uint8_t UART2_SendString(const uint8_t *str);
extern void U2Rx4Byte(void);

#endif
