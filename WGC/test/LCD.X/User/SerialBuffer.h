/* 
 * File:   CircleReceiveBuffer.h
 * Author: TURONG62
 *
 * Created on 2016年7月22日, 下午1:01
 */

#ifndef SEIRALBUFFER_H
#define	SEIRALBUFFER_H

//#include "user.h"
#include <stdbool.h>
#include <stdint.h>
#include <xc.h>

typedef bool (*UARTn)(uint8_t*);

//extern void BufferWrite_UART1(void);
extern void BufferWrite_UART2(void);
//extern bool BufferRead_UART1(uint8_t *data);
extern bool BufferRead_UART2(uint8_t *data);
extern uint8_t UARTIsGet(UARTn f_uart, uint8_t*Get_Source, const uint8_t get_size,const uint8_t *head, const uint8_t head_size);
extern void ClearBuffer2(void);

#endif	/* CIRCLERECEIVEBUFFER_H */



