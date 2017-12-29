/* 
 * File:   RS485.h
 * Author: TURONG62
 *
 * Created on 2016年6月12日, 下午4:09
 */

#ifndef RS485_H
#define	RS485_H

void RS485_Init(void);
void RS485Send(const u8 dat);
void RS485SendString(const u8* dat, u8 bytes);
void OpenRS485(void);
void CloseRS485(void);
//void OpenAwake485(void);
//void CloseAwake485(void);

#endif	/* RS485_H */

