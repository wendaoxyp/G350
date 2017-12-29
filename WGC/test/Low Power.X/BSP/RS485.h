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

#define RS485_TRIS TRISBbits.TRISB10
#define RS485_CON LATBbits.LATB10 //TRISBbits.TRISB10 
#define RS485_IN_TRIS TRISBbits.TRISB8
//#define RS485_IN LATBbits.LATB8
#define RS485_OUT_TRIS TRISBbits.TRISB9
#define RS485_OUT LATBbits.LATB9

extern void RS485_Init(void);
extern void RS485SendChar(const uint8_t dat);
extern void RS485SendString(const uint8_t* dat, const uint8_t bytes);
extern void OpenRS485(void);
extern void CloseRS485(void);

#endif	/* RS485_H */

