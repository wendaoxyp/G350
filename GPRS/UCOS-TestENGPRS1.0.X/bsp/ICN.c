//#include <p24FV32KA301.h>
//#include "user.h"
#include "xc.h"

void ICN_Configuration(void) {
    //    INPUT_PULSE_IN;
    TRISBbits.TRISB9 = 1;
    //    CNPU2bits.CN22PUE = 1; //S2ʹ��������
    //    CNPD2bits.CN22PDE = 1; //S2ʹ��������
    IPC4bits.CNIP = 5;
    IFS1bits.CNIF = 0;
    IEC1bits.CNIE = 1; //ʹ���ж�    
    CNEN2bits.CN21IE = 1; //S1�����ж�
    //    CNEN2bits.CN22IE = 1; //S2�����ж�
    //    CNEN1bits.CN6IE=1;//RX1����
}




