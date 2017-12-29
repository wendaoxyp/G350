#include <DeepSleep.h>
#include <xc.h>
#include <stdint.h>

/************
 * ��ѹ/������ѹ�����ڵ�������ģʽ���������ģʽʱ
���á�����LPCFG����λ��CW1<10>�����ƣ��ڹ̼�
���� RETEN λ��RCON<12>�����ơ����뽫 LPCFG
���Ϊ 0 ���� RETEN λ�� 1������ʹ�ܸ���ѹ����
 ************************************************/
void DeepSleep(void) {
    //    uint8_t Result;
    //    if (RCONbits.WDTO) {
    //        Result = 3;
    //        RCONbits.WDTO = 0;
    //        DSCONbits.RELEASE = 0;
    //    } else if (RCONbits.EXTR) {
    //        Result = 2;
    //        RCONbits.EXTR = 0;
    //        DSCONbits.RELEASE = 0;
    //    } else if (RCONbits.DPSLP) {
    //        Result = 1;
    //        RCONbits.DPSLP = 0;
    //        DSCONbits.RELEASE = 0;
    //        if (DSWAKEbits.DSWDT) DSGPR0 = DSGPR0 + 1; /* count when wake from DSWDT */
    //        if (DSWAKEbits.DSINT0) DSGPR1 = DSGPR1 + 1; /* count when wake from INT0  */
    //    } else {
    //        Result = 0; /* assume we are a Power On reset */
    //        RCONbits.POR = 0;
    //        DSGPR0 = 0;
    //        DSGPR1 = 0;
    //    }
    //    if (Result == 0) {
    RCONbits.RETEN = 1; // CONFIG1  #pragma config LPCFG = ON    // Low power regulator control->Disabled
    //    while (!RCONbits.RETEN)
    //        RCONbits.RETEN = 1;
    //    asm("disi #4");
    //    asm("bset DSCON, #15");
    //    asm("nop");
    //    asm("nop");
    //    asm("btss INTTREG, #15");
    //    asm("pwrsav #0");
    RCONbits.DPSLP = 0; /* clear all previous deep sleep wake flags */
    DSWAKE = 0; /* clear all previous deep sleep wake flags */
    /* enter deep sleep code cut and paste from data sheet */
    asm("disi #4");
    asm("bset  DSCON, #15");
    asm("nop");
    asm("nop");
    asm("nop");    
//    asm("bset  DSCON, #15");
    asm("pwrsav #0");
    //    }
}



