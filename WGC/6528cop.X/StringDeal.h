#ifndef STRINGDEAL_H
#define STRINGDEAL_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

typedef uint8_t(*pFun)(void);

struct StringCmpResult {
    uint8_t* inputstring;
    uint8_t inputlgt;
    uint8_t* cmpstring;
    uint8_t cmplgt;
    uint8_t cmpPzt;
//    uint8_t cmpSrt;
};
extern struct StringCmpResult ATString;

 bool FindStringHead(struct StringCmpResult* scr_input);
//extern void CopyString(unsigned char *, unsigned char *, const unsigned char);
 bool CmpString(struct StringCmpResult* scr_input);
 void StringCmpInit(struct StringCmpResult* scr_input);
 bool RecIsRight(struct StringCmpResult*scr) ;
 void GetBuffer(uint8_t* str1, uint8_t bytes,pFun uart_rec) ;
 void StringCmpInit(struct StringCmpResult* scr_input);
#endif

