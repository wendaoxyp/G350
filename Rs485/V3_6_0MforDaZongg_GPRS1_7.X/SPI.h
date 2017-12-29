/* 
 * File:   SPI.h
 * Author: TURONG62
 *
 * Created on 2016年6月1日, 下午3:52
 */
#include "user.h"
#ifndef SPI_H
#define	SPI_H

extern void SPI2_Start(void);
extern void SPI2_Stop(void);
extern void SPI2_Configuration(void);
extern uint8_t SPI2_Exchange(const uint8_t TransmitData);

#endif	/* SPI_H */

