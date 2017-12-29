#include "StringDeal.h"

struct StringCmpResult ATString;

bool RecIsRight(struct StringCmpResult*scr) {
    //    bool b = false;
    scr->cmpPzt = 0;
    while (FindStringHead(scr)) {
        if (CmpString(scr))
            return true;
    }
    return false;
}

void GetBuffer(uint8_t* str1, uint8_t bytes,pFun uart_rec) {
    uint8_t cnt;
    for (cnt = 0; cnt < bytes; cnt++) {
        *(str1 + cnt) = uart_rec();
        if (!(*(str1 + cnt)))
            break;
    }
}

void StringCmpInit(struct StringCmpResult* scr_input) {
    scr_input->cmpstring = NULL;
    scr_input->inputlgt = 0;
    scr_input->cmpstring = NULL;
    scr_input->cmplgt = 0;
    scr_input->cmpPzt = 0;
    //    scr_input->cmpSrt = 0;
}

bool FindStringHead(struct StringCmpResult* scr_input) {
    uint8_t postion;
    for (postion = scr_input->cmpPzt; postion < scr_input->inputlgt; postion++) {
        if (*(scr_input->inputstring + postion) == *scr_input->cmpstring) {
            scr_input->cmpPzt = postion;
            return true;
        }
    }
    return false;
}

bool CmpString(struct StringCmpResult* scr_input) {
    uint8_t cnt;
    for (cnt = 0; cnt < scr_input->cmplgt; cnt++) {
        if (*(scr_input->cmpstring + cnt) != *(scr_input->inputstring + cnt + scr_input->cmpPzt))
            break;
        else if (cnt == scr_input->cmplgt - 1)
            return true;
    }
    scr_input->cmpPzt += 1;//根据地址在继续搜索字符
    return false;
}




//bool FindStringHead(struct StringCmpResult scr_uart) {
//    uint8_t postion, cnt;
//    for (postion = 0; postion < scr_uart.inputlgt; postion++) {
//        if (*(scr_uart.input + postion) == *scr_uart.cmpstring) {
//            for (cnt = 1; cnt < scr_uart.cmplgt; cnt++)
//                if (*(scr_uart.input + postion + cnt) != *(scr_uart.cmpstring + postion + cnt)) {
//                    return false;
//                } else if (cnt == (scr_uart.cmplgt - 1)) {
//                    *(scr_uart.cmpPzt) = postion;
//                    return true;
//                }
//        }
//    }
//    return false;
//}
