#include <stdbool.h>
#include <stdint.h>
#include "StringDeal.h"

bool FindStringHead(pFun readBuffer,uint8_t *rightDat,const uint8_t stringlen, uint8_t* postion1)
{
	uint8_t postion;
	for (postion=0;postion<stringlen;postion++)
        if (readBuffer() == *rightDat) {
			*postion1=postion;
            return true;
		}
    return false;
}

void CopyString(uint8_t *inputDat,uint8_t *outputDat,const uint8_t len)
{
	uint8_t cnt;
	for(cnt=0;cnt<len;cnt++)
		*(outputDat+cnt)=*(inputDat+cnt);
}

bool CmpString(uint8_t*inputDat,uint8_t*rightDat,uint8_t cmplen)
{
	uint8_t cnt;
	for (cnt = 0; cnt < cmplen; cnt++) {
    	if ((*inputDat + cnt + cnt) != ((*inputDat + cnt + cnt)))
     		break;
        else if (cnt == cmplen - 1) 
        	return true;                
	}
	return false;
}





