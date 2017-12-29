/* 
 * File:   CRC16.h
 * Author: TURONG62
 *
 * Created on 2016年6月22日, 上午9:06
 */

#ifndef CHECKDATA_H
#define	CHECKDATA_H
#include "user.h"

u16 CRC16_Check(u8 *CRC_Buf, const u8 CRC_Leni);
u16 Sum_Check(u8 *frame, const u8 bytes);
u8 Sum_Check256(u8 *frame, const u16 bytes);
bool CheckIsRight(FP_CRC fp, u8 * dat, const u8 bytes);
bool CheckSrting(u8*dat1, u8*dat2, const u8 num);

#endif	/* CRC16_H */

