//#include "pc.h"
#include "includes.h"

void PCCop_Init(void)
{
    RS485_Init();
}


void PCCopTask(void*arg) {

    while (1) {
        RS485SendChar(0x31);
        //        RS485SendString("ErrCode:\r\n", 10);
//        OSTimeDlyHMSM(0, 0, 1, 0);
//        Delay_1S(1);
    }
}

