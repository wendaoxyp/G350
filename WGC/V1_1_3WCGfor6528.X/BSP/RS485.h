/* 
 * File:   RS485.h
 * Author: TURONG62
 *
 * Created on 2016��6��12��, ����4:09
 */

#ifndef RS485_H
#define	RS485_H

#include <xc.h>
#include <stdint.h>


extern void RS485_Init(void);
extern void RS485SendChar(const uint8_t dat);
extern void RS485SendString(const uint8_t* dat, const uint8_t bytes);
extern void OpenRS485(void);
extern void CloseRS485(void);

#endif	/* RS485_H */

