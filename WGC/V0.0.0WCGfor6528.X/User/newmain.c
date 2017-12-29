/* 
 * File:   newmain.c
 * Author: Administrator
 *
 * Created on 2017年6月20日, 下午12:50
 */

#include <stdio.h>
#include <stdlib.h>
#include "../mcc_generated_files/mcc.h"

/*
 * 
 */
int main(int argc, char** argv) {
    struct tm time1;
    SYSTEM_Initialize();
    U1STAbits.UTXEN = 1;
    U1MODEbits.UARTEN = 1;
    TMR1_Start();
    TRISBbits.TRISB10 = 0;
    LATBbits.LATB10 = 1;
    while (1) {
        TMR1_Tasks_16BitOperation();
        if (TMR1_SoftwareCounterGet()) {
            TMR1_SoftwareCounterClear();
            while (!RTCC_TimeGet(&time1));
            U1TXREG = time1.tm_sec;
            while (!U1STAbits.TRMT);
            //            U1TXREG = 0x31;
            //            while (!U1STAbits.TRMT);
        }
    }
}

