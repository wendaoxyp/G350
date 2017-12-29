//#include "pc.h"
#include "includes.h"

void PCCopTask(void*arg) {

    while (1) {
        RS485Send(0x31);
//        RS485SendString("ErrCode:\r\n", 10);
        OSTimeDlyHMSM(0, 0, 1, 0);
    }
}

