/* 
 * File:   CircleReceiveBuffer.h
 * Author: TURONG62
 *
 * Created on 2016年7月22日, 下午1:01
 */

#ifndef SEIRALBUFFER_H
#define	SEIRALBUFFER_H

#include "user.h"

void BufferWrite_UART1(void);
void BufferWrite_UART2(void);
bool BufferRead_UART1(u8 *data);
bool BufferRead_UART2(u8 *data);
u8 UARTIsGet(UARTn f_uart, u8*Get_Source, const u8 get_size, const u8 *head, const u8 head_size);


#endif	/* CIRCLERECEIVEBUFFER_H */



