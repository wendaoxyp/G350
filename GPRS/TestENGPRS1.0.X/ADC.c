//#include "p24F32KA302.h"
#include "user.h"

void ADC_Init(void) {    
    ADC0_IN;
    ANSAbits.ANSA2 = 0;
    //���ο�
    AD1CON2bits.PVCFG=0;//AVdd
    AD1CON2bits.NVCFG=0;//AVss
    AD1CON3bits.ADCS=0b00001111;//16Tcy
    AD1CON1bits.SSRC=0;
    AD1CON3bits.SAMC=0b01111;//15Tcy
    AD1CON1bits.FORM=0;//����������
}

float Get_Voltage(void) {

}


