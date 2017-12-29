/* 
 * File:   TypeConvert.h
 * Author: TURONG62
 *
 * Created on 2016年9月9日, 上午8:48
 */

#ifndef COMMON_H
#define	COMMON_H

#ifdef	__cplusplus
extern "C" {
#endif

    void FloatToChar(float *f, u8 *ch);
    void CharToFloat(float *f, u8 *ch);
    void DoubleToChar(long double *d, u8 *ch);
    u8 HCD(u8 dat);
    u8 DCH(u8 dat);
    void SetVaildData(u8 * dat, const u32 max, const u16 min);
    bool DataIsVaild(u16 dat, const u16 max, const u16 min);
    void DataReverse(u8 *dat, const u8 byte);
    void Delay10ms(char time);
    void Delay100ms(char time);
    void Delay1s(char time);
#ifdef	__cplusplus
}
#endif

#endif	/* TYPECONVERT_H */

