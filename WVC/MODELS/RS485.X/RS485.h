/* 
 * File:   RS485.h
 * Author: TURONG62
 *
 * Created on 2016年6月12日, 下午4:09
 */

#ifndef RS485_H
#define	RS485_H


/***************************************************************************
 * Includes
 ***************************************************************************/
#include <xc.h>
#include <stdint.h>
#include "WCV_Conf.h"
#include "Common.h"
#include "SerialBuffer.h"

/***************************************************************************
 * Defines
 ***************************************************************************/
#define RS485_RDE_TRIS  TRISAbits.TRISA0    //控制口设置位输出
#define RS485_RDE       LATAbits.LATA0      //设置接收使能端
//#define RS485_IN_TRIS   TRISBbits.TRISB2    //设置为输入/
//#define RS485_OUT_TRIS  TRISBbits.TRISB3    //设置为输出
//#define ANSBbits.ANSB8      //接收引脚设置为数字输入

/***************************************************************************
 * Prototypes
 ***************************************************************************/
extern void RS485_Init(void);
extern void RS485Send(const uint8_t dat);
extern void RS485SendString(const uint8_t* dat, const uint8_t bytes);
extern void OpenRS485(void);
extern void CloseRS485(void);
extern void GetLast4Bytes(void);

#endif	/* RS485_H */

