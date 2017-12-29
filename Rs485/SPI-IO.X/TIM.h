/* 
 * File:   TIM.h
 * Author: TURONG62
 *
 * Created on 2016年6月6日, 下午3:04
 */

#ifndef TIM_H
#define	TIM_H


void TIM1_Configuration(void);
//void TIM2_Configuration(void);
void TIM3_Configuration(void);
void TIM4_Configuration(void);
bool T2IsOver(const u16 deadline);
bool T3IsOver(const u16 deadline);
//void T2Delay10ms(u16 time);
//void T3Delay10ms(u16 time); 
//void StartTime2(void);
//void CloseTime2(void);
void StartTime3(void);
void CloseTime3(void);
void StartTim4(void);
void CloseTime4(void);
void GetUnixTime_Char(u8* timeptr, u8* output);
void Delay_Nop(int count);

#endif	/* TIM_H */

