/* 
 * File:   RTCC.h
 * Author: TURONG62
 *
 * Created on 2016年6月3日, 下午4:54
 */

#ifndef RTCC_H
#define	RTCC_H

//extern u16 date[4];

void RTC_Configuration(void);
void CheckRTCC(void) ;
void RTCReadTime(u8* dat);
void StartRTCC(void);
void StopRTCC(void);
//void OutputData(u16* dat);

#endif	/* RTCC_H */

