/* 
 * File:   CRC16.h
 * Author: TURONG62
 *
 * Created on 2016年6月22日, 上午9:06
 */

#ifndef CHECKDATA_H
#define	CHECKDATA_H

#include <stdint.h>
#include <stdbool.h>

//typedef uint16_t(*FP_CRC)(uint8_t*, const uint8_t);


//uint16_t CRC16_Check(uint8_t *CRC_Buf, const uint8_t CRC_Leni);
//uint16_t Sum_Check(uint8_t *frame, const uint8_t bytes);
//uint8_t Sum_Check256(uint8_t *frame, const uint16_t bytes);
bool SumCheckIsRight(uint8_t *frame, const uint16_t bytes, const uint8_t CheckSum);
bool CRCIsRight(uint8_t * CRC_Buf, const uint8_t CRC_Leni, const uint8_t* CHC_Dat);
//bool CheckSrting(uint8_t*dat1, uint8_t*dat2, const uint8_t num);

#endif	/* CRC16_H */

