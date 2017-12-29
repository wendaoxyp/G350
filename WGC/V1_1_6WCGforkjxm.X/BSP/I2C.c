#include "I2C.h"

volatile uint8_t i2c1_state;
I2C1_Buffer i2c_buf;

void I2C_Init(void) {
    TRISGbits.TRISG2 = 0; //��SCL1����Ϊ�����
    TRISGbits.TRISG3 = 0; //��SCK1����Ϊ�����
    I2C1BRG = 0x9D; //100kHz Fcy=16000000
    I2C1CONbits.I2CEN = 1; //ʹ��I2C1
    I2C1CONbits.I2CSIDL = 0; //ģ���ڿ���ģʽ�¼�������
    I2C1CONbits.IPMIEN = 0; //��ֹIPMIģʽ
    I2C1CONbits.A10M = 0; //7λ�ӵ�ַ
    IFS1bits.MI2C1IF = 0; //���Master��־λ
    IEC1bits.MI2C1IE = 1; //ʹ��Master�ж�
    //    IEC1bits.SI2C1IE = 1;//ʹ��Slave�ж�
    //    IFS1bits.SI2C1IF = 0;//���Slave��־λ
    //    I2C1CONbits.I2CEN = 0; //�ر�I2C1
}

//void Start_I2C(void) {
//    //    IEC4bits.
//    //    I2C1CONbits.I2CEN = 1;
//    IFS1bits.MI2C1IF = 1;
//}

//void Stop_I2C(void) {
//    IFS1bits.MI2C1IF = 0;
//    I2C1CONbits.I2CEN = 0;
//}

//void Check_I2C(void) {
//    if (I2C1STATbits.IWCOL) {//���д��ͻ���λΪ1����ô�������λ������״̬����Ϊ����
//        I2C1STATbits.IWCOL = 0;
//    }
//}

//void Clear_I2C_Sta(void) {
//    i2c1_state = S_MASTER_IDLE;
//}

//void Send_I2C_Data(I2C1_Buffer* buf)
//{
//    buf
//}

