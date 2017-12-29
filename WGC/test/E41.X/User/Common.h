/* 
 * File:   TypeConvert.h
 * Author: TURONG62
 *
 * Created on 2016��9��9��, ����8:48
 */

#ifndef COMMON_H
#define	COMMON_H

#include <stdint.h> 
#include <stdbool.h>

//extern void FloatToChar(float *f, uint8_t *ch);
extern void CharToFloat(float *f, uint8_t *ch);
extern bool UART_Is_Get(uint8_t* sdata, uint8_t* cdata, const uint8_t sbytes, const uint8_t cbytes);
//extern void DoubleToChar(long double *d, uint8_t *ch);
//extern uint8_t HCD(uint8_t dat);
//extern uint8_t DCH(uint8_t dat);
//extern void SetVaildData(uint8_t * dat, const uint32_t max, const uint16_t min);
//extern bool DataIsVaild(uint16_t dat, const uint16_t max, const uint16_t min);
//extern void DataReverse(uint8_t *dat, const uint8_t byte);
////extern void Delay10ms(char time);
////extern void Delay100ms(char time);
extern void Delay1s(char time);
//extern void CopyDat(uint8_t* output, uint8_t* input, const uint8_t bytes);
//extern void ClearDat(uint8_t* output, const uint8_t dat, const uint8_t bytes);
//extern bool ValueIsEqual(const uint8_t *v1, const uint8_t *v2, const uint8_t bytes);

struct FLAGBITS {
    uint16_t E41 : 1;
    uint16_t TR0_Cnt : 8;
};
extern struct FLAGBITS flagbits;

#endif	/* TYPECONVERT_H */

