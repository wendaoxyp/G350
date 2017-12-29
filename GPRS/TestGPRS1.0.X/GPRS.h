/* 
 * File:   GPRS.h
 * Author: TURONG62
 *
 * Created on 2016年6月25日, 下午1:44
 */

#ifndef GPRS_H
#define	GPRS_H

void GPRS_Init(void);
//bool GPRSSendIsOK(void);
bool LKIsHigh(u16 deadline);
bool CopTCPTask(void);
bool CopUDPTask(u8 dat); 
bool GetGMTTimeTask(void);
bool ChangeGPRSArg(const u8 *dat);


#endif	/* GPRS_H */

