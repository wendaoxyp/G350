/* 
 * File:   RTCC.h
 * Author: TURONG62
 *
 * Created on 2016年6月3日, 下午4:54
 */

#ifndef RTCC_H
#define	RTCC_H


#include <stdint.h>
#include <time.h>
#include <stdint.h>
#include <stdbool.h>
#include "RS485.h"
#include "Debug.h"

extern void RTC_Init(void);
extern void RTC_Set_Time(struct tm);
extern bool RTC_Read_Time(struct tm*currentTime);
extern void RTC_Set_Alarm(struct tm);
extern void RTC_Refresh_Time(void);
#ifdef DEBUG_RTCC_TIME
void printrtccArg(void);
#endif
void printnums(uint32_t settingtime); //extern void PrintTime(void);


#endif	/* RTCC_H */

