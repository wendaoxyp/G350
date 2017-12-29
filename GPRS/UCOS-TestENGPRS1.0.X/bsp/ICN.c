//#include <p24FV32KA301.h>
//#include "user.h"
#include "xc.h"

void ICN_Configuration(void) {
    //    INPUT_PULSE_IN;
    TRISBbits.TRISB9 = 1;
    //    CNPU2bits.CN22PUE = 1; //S2使能弱上拉
    //    CNPD2bits.CN22PDE = 1; //S2使能弱下拉
    IPC4bits.CNIP = 5;
    IFS1bits.CNIF = 0;
    IEC1bits.CNIE = 1; //使能中断    
    CNEN2bits.CN21IE = 1; //S1输入中断
    //    CNEN2bits.CN22IE = 1; //S2输入中断
    //    CNEN1bits.CN6IE=1;//RX1接受
}




