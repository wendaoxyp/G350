/* 
 * File:   RS485.h
 * Author: TURONG62
 *
 * Created on 2016年6月12日, 下午4:09
 */

#ifndef RS485_H
#define	RS485_H


#include <xc.h>
#include <stdint.h>
#include "Debug.h"

extern void RS485_Init(void);
extern void RS485SendChar(const uint8_t dat);
extern void RS485SendString(const uint8_t* dat, const uint8_t bytes);
//#ifdef DEBUG_485_SEND_STR
extern void RS485SendString1(const uint8_t* dat);
extern void U1Rx4Byte(void);
//#endif
//extern void OpenRS485(void);
//extern void CloseRS485(void);

#endif	/* RS485_H */

