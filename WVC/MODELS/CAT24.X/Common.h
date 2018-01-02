/*************************************************
Copyright (C), 1988-1999, Tech. Co., Ltd.
File name: Common.h
Author: xx13
Version: 1.0
Date: 2017/12/29
Description: Common API函数
Others: 需要用到自定义库
History: None
1. Date:
Author:
Modification:
2. ...
 *************************************************/

#ifndef COMMON_H
#define	COMMON_H

/***************************************************************************
 * Include
 ***************************************************************************/
#include <stdint.h> 
#include <stdbool.h>
#include <xc.h>

/***************************************************************************
 * Prototype
 ***************************************************************************/
extern void FloatToChar(float *f, uint8_t *ch);
extern void CharToFloat(float *f, uint8_t *ch);
extern void DoubleToChar(long double *d, uint8_t *ch);
extern uint8_t HCD(uint8_t dat);
extern uint8_t DCH(uint8_t dat);
extern void SetVaildData(uint16_t * dat, const uint32_t max, const uint16_t min);
extern bool DataIsVaild(uint16_t dat, const uint16_t max, const uint16_t min);
extern void DataReverse(uint8_t *dat, const uint8_t byte);
extern void Delay1ms(char time);
extern void Delay10ms(char time);
extern void Delay100ms(char time);
extern void Delay1s(char time);
//extern void Delayms(uint16_t time);
//extern void Delays(char time) ;
extern void CopyDat(uint8_t* output, const uint8_t* input, const uint8_t bytes);
extern void ClearDat(uint8_t* output, const uint8_t dat, const uint8_t bytes);
extern bool ValueIsEqual(const uint8_t *v1, const uint8_t *v2, const uint8_t bytes);
extern uint8_t GetMod(uint16_t num, uint8_t mod_num);
extern uint8_t my_itoa(uint16_t i, uint8_t *str);
extern uint8_t Str_Find_Head(const uint8_t* str1, const uint8_t* str2, uint8_t, uint8_t);



#endif	/* TYPECONVERT_H */

