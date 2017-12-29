/* 
 * File:   CRC16.h
 * Author: TURONG62
 *
 * Created on 2016年6月22日, 上午9:06
 */

#ifndef CRC16_H
#define	CRC16_H

#include <stdint.h>
#include <stdbool.h>
//#include 

typedef uint16_t (*FP_CRC)(uint8_t *CRC_Buf,uint8_t CRC_Leni);
uint16_t CRC16_Check(uint8_t *CRC_Buf,uint8_t CRC_Leni);
uint16_t Sum_Check(uint8_t *frame,uint8_t bytes);
bool CheckIsRight(FP_CRC fp, uint8_t * dat, const uint8_t bytes);

#endif	/* CRC16_H */



