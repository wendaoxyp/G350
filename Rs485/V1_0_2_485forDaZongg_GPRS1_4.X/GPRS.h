/* 
 * File:   GPRS.h
 * Author: TURONG62
 *
 * Created on 2016��6��25��, ����1:44
 */

#ifndef GPRS_H
#define	GPRS_H

void GPRS_Init(void);
//bool GPRSSendIsOK(void);
bool LKIsHigh(u16 deadline);
//bool CopTCPTask(void);
bool CopUDPTask(const u8 dat, const u8, const u8);
bool GetGMTTimeTask(void);
bool ChangeGPRSArg(const u8 *dat);
bool GPRS_IS_Close(const u8 nS);

#endif	/* GPRS_H */

