//#include "p24F32KA302.h"
#include "user.h"

void ADC_Init(void) {
    ADC0_IN;
    ANSAbits.ANSA2 = 1; //AD1CHS����IO��
    AD1CON1 |= (1 << 10); //12bits
    //���ο�
    AD1CON1bits.SSRC = 7; //0b0111; //�ڲ��������Զ�ת����
    AD1CON1bits.FORM = 0b00; //���ݸ�ʽΪ�Ҷ����޷�������
    AD1CHSbits.CH0NB = 0;
    AD1CHSbits.CH0SB = 0; //Connect AN2 as positive input
    AD1CHSbits.CH0NA = 0;
    AD1CHSbits.CH0SA = 0; //��������
    AD1CON3bits.ADCS = 0; //16Tcy
    AD1CON3bits.SAMC = 0b01111;
    AD1CON2bits.ALTS = 0; //ʼ�ն�һ��ͨ���ɼ�
    AD1CON2bits.PVCFG = 0; //AVdd���òο���ѹ
    AD1CON2bits.NVCFG = 0; //AVss
    AD1CON2bits.SMPI = 0b01111; //�ɼ�16��һ���ж�
    AD1CON2bits.BUFREGEN = 0; //�����ݷŽ�
    //    AD1CON1 = 0x00E0; // Internal counter triggers conversion
    //    AD1CHS = 0x0000; // Connect AN0 as positive input
    //    AD1CSSL = 0;
    //    AD1CON3 = 0x0F00; // Sample time = 15Tad, Tad = Tcy
    //    AD1CON2 = 0x003C; // Set AD1IF after every 16 samples
    //    AD1CSSH = 0; //
    //    AD1CSSL = 0; //û��ɨ�� 

    AD1CON1bits.ADON = 0;
    //����ֵ���
    //    AD1CON2bits.CSCNA = 1; //ɨ������
    //    AD1CON5bits.ASEN = 1;
    //    AD1CON5bits.CM = 0; //SSRC!=7
    //    AD1CON5bits.LPEN = 0; //�ɼ���󷵻ص͹���ģʽ
    //    AD1CON5bits.ASINT = 2; //�Զ�ɨ�����ֵ�ն�
    //    AD1CON5bits.WM = 1; //���Զ�����
    //
    //    ADC1BUF2 = 0x99d; //3.3V-2.127
    //    AD1CON1 = 0x00E0; // Internal counter triggers conversion
    //AD1CHS = 0x0000; // Connect AN0 as positive input
    //AD1CSSL = 0;
    //AD1CON3 = 0x0F00; // Sample time = 15Tad, Tad = Tcy
    //AD1CON2 = 0x003C; // Set AD1IF after every 16 samples
    //AD1CON1bits.ADON = 1; // turn ADC ON
}

void GetVoltage(float* f) {
    u32 ADCValue = 0;
    u8 count;
    u16 *ADC16Ptr;
    //    float a = 0;

    AD1CON1bits.ADON = 1;
    ADCValue = 0; // clear value
    ADC16Ptr = (u16*) (&ADC1BUF0); // initialize ADC1BUF pointer
    IFS0bits.AD1IF = 0; // clear ADC interrupt flag
    AD1CON1bits.ASAM = 1; // auto start sampling for 31Tad
    while (!IFS0bits.AD1IF); // conversion done?
    AD1CON1bits.ASAM = 0; // yes then stop sample/convert
    for (count = 0; count < 16; count++) // average the 16 ADC value
        ADCValue += *ADC16Ptr++;
    AD1CON1bits.ADON = 0;
    *f = 3.54 * (ADCValue >> 4) / 4096;
    //    return a; //0.8642578125=3.54/2^12*1000
}

//uint16_t ADC1_ConversionResultBufferGet(uint16_t *buffer) {
//    int count;
//    uint16_t *ADC16Ptr;
//
//    ADC16Ptr = (uint16_t *)&(ADC1BUF0);
//
//    for (count = 0; count < 10; count++) {
//        buffer[count] = (uint16_t) * ADC16Ptr;
//        ADC16Ptr++;
//    }
//    return count;
//}

//��βɼ���ת����ͨ��
//int ADCValue, count;
//int *ADC16Ptr;
////ANSB = 0x0001; // Only AN0 as analog input
//AD1CON1 = 0x00E0; // Internal counter triggers conversion
//AD1CHS = 0x0000; // Connect AN0 as positive input
//AD1CSSL = 0;
//AD1CON3 = 0x0F00; // Sample time = 15Tad, Tad = Tcy
//AD1CON2 = 0x003C; // Set AD1IF after every 16 samples
//AD1CON1bits.ADON = 1; // turn ADC ON
//while (1) // repeat continuously
//{
//    ADCValue = 0; // clear value
//    ADC16Ptr = &ADC1BUF0; // initialize ADC1BUF pointer
//    IFS0bits.AD1IF = 0; // clear ADC interrupt flag
//    AD1CON1bits.ASAM = 1; // auto start sampling for 31Tad
//    // then go to conversion
//    while (!IFS0bits.AD1IF) {
//    }; // conversion done?
//    AD1CON1bits.ASAM = 0; // yes then stop sample/convert
//    for (count = 0; count < 16; count++) // average the 16 ADC value
//    {
//        ADCValue = ADCValue + *ADC16Ptr++;
//    }
//    ADCValue = ADCValue >> 4;
//}


