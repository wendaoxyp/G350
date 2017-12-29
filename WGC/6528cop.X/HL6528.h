/* 
 * File:   HL6528.h
 * Author: Administrator
 *
 * Created on 2017年5月16日, 上午10:19
 */

#ifndef HL6528_H
#define	HL6528_H
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "StringDeal.h"
#ifdef	__cplusplus
extern "C" {
#endif
//    typedef void (*pfunuartw)(uint8_t);
//    typedef uint8_t(*pfunuartr)(void);
//#define ClSGPRS CloseGPRS
    
     void SendDat2GPRS(const uint8_t*, uint8_t);
//    extern bool RecIsRight(struct StringCmpResult*scr);
//    extern void GetBuffer( uint8_t* str1, uint8_t bytes);
     void GPRSDialing(struct StringCmpResult*scr, uint8_t Dialing);
     bool CloseGPRS(struct StringCmpResult*scr) ;
#ifdef	__cplusplus
}
#endif

#endif	/* HL6528_H */



