#ifndef STRINGDEAL_H
#define STRINGDEAL_H
#include <stdbool.h>

typedef uint8_t (*pFun)(void);
 
extern bool FindStringHead( pFun ,unsigned char *,const unsigned char , unsigned char*); 
extern void CopyString(unsigned char *,unsigned char *,const unsigned char );
extern bool CmpString(unsigned char*,unsigned char*,unsigned char );
 
#endif

