/* 
 * File:   TypeConvert.h
 * Author: TURONG62
 *
 * Created on 2016年9月9日, 上午8:48
 */

#ifndef COMMON_H
#define	COMMON_H

#include <stdint.h>
#include <stdbool.h>

#ifdef	__cplusplus
extern "C" {
#endif

    extern void FloatToChar(float *f, uint8_t *ch);
    extern void CharToFloat(float *f, uint8_t *ch);
    extern void DoubleToChar(long double *d, uint8_t *ch);
    uint8_t HCD(uint8_t dat);
    uint8_t DCH(uint8_t dat);
    extern void SetVaildData(uint8_t * dat, const uint32_t max, const uint16_t min);
    bool DataIsVaild(uint16_t dat, const uint16_t max, const uint16_t min);
    extern void DataReverse(uint8_t *dat, const uint8_t byte);
    extern void Delay10ms(char time);
    extern void Delay100ms(char time);
    extern void Delay1s(char time);
    extern void CopyDat(uint8_t* output, uint8_t* input, const uint8_t bytes);
    extern void ClearDat(uint8_t* output, const uint8_t dat, const uint8_t bytes);
#ifdef	__cplusplus
}
#endif

#endif	/* TYPECONVERT_H */

