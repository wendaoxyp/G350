#include "E41_C1.h"

#define M0_TRIS TRISEbits.TRISE5
#define M1_TRIS TRISEbits.TRISE6
#define M0 LATEbits.LATE5
#define M1 LATEbits.LATE6
#define AUX PORTFbits.RF6

#define WORK 0
#define WAKE 1
#define LOWPOWER 2
#define SLEEP 3
uint8_t E41_Arg[] = {0xC0, 0x00, 0x01, 0x18, 0x01, 0x9C};
// 0xff, 0xff, 0x18, 0x1, 0x9c
//static ADDBITS E41_ADD;
//static ARG1BITS E41_ARG1;
//static ARG2BITS E41_ARG2;
extern void UART3_WriteBbuf(uint8_t* tmp, const uint8_t len);

void E41_Init(void) {
    M0_TRIS = 0; //��������
    M1_TRIS = 0;
    //    ANSFbits.
    M0 = 1; //��������ģʽ
    M1 = 1;

    E41_SetArg();
    //    M0 = 0; //���뻽��ģʽ
    //    UART3_Init(); //����3��ʼ��
    //        E41_SetArg(); //����ʡ��ģʽ 
    //    INI_Init();
}

void E41_SetMode(const uint8_t mode) {
    M0 = mode & 0x01;
    M1 = (mode >> 1) & 0x01;
}

void E41_SetArg(void) {
    //    uint8_t currentMode = E41_SetGetMode(10);
    M0 = M1 = 1;
    Delay1s(1);
    //    E41_ADD.ADDL = 0x01; //����ַ����Ϊ00 01
    //    E41_ADD.ADDH = 0x00;
    //    E41_ARG1.AIRbps = 0b00; //��������Ϊ2K
    //    E41_ARG1.TTLbps = 0b011; //������Ϊ9600
    //    E41_ARG1.checkbit = 0b00; //У����Ϊ1 ������8λ
    //    E41_ARG1.CHAN = 0x1; //Ƶ��ͨ��Ϊ1
    //    E41_ARG2.FEC = 1; //��������У��
    //    E41_ARG2.IODrive = 1; //�������
    //    E41_ARG2.MODBUS = 1; //͸��ģʽ
    //    E41_ARG2.sendPower = 0b00; //10dBm���书��
    //    E41_ARG2.waketime = 0b001; //����ʱ��
    //    uint8_t tmp = 0xC0;
    //    UART3_WriteBbuf(&tmp, 1);
    UART3_WriteBbuf(E41_Arg, 6);
    //    UART3_SendChar(E41_Arg);
    //    UART3_SendChar(E41_ADD.ADDL);
    //    UART3_SendChar(E41_ARG1.AIRbps | (E41_ARG1.TTLbps << 3) | (E41_ARG1.checkbit << 6));
    //    UART3_SendChar(E41_ARG1.CHAN);
    //    UART3_SendChar(E41_ARG2.MODBUS << 7 | (E41_ARG2.waketime << 4) | (E41_ARG2.FEC << 3) | (E41_ARG2.IODrive << 2) | (E41_ARG2.sendPower));
    //    E41_SetGetMode(currentMode);
    M0 = 0; //m1=1;
}

bool E41_PressureIsGet(float* pres, uint8_t*tmp) {//���ܵ���ѹ��ֵΪ01 03 04 3E F4 00 00 B6 29��16���ƣ�
    //�жϽ��ܵ������������Ǳ���ѹ��ֵ
    //    uint8_t tmp[20];
    uint8_t Head[3] = {0x1, 0x3, 0x4};
    //    float pres;
    //    uint8_t bytes = UART3_ReadBuffer(tmp, 20);
    //    U3Rx4Byte();
    //    if (UART_Is_Get(tmp, Head, bytes, 3) && bytes > 5) {//ע�����ȵĽ��˳��
    //        CharToFloat(pres, tmp + 3);
    //        return true;
    //    }
    return false;
}

void UART3_WriteBbuf(uint8_t* tmp, const uint8_t len) {
    uint8_t cnt;
    for (cnt = 0; cnt < len; cnt++) {
        U3TXREG = *(tmp + cnt);
        while (!U3STAbits.TRMT);
    }
}

void E41_ReadArg(void) {
    uint8_t tmp[20];
    uint8_t Head[3] = {0xC1, 0xC1, 0xC1};
    uint8_t R_byte;
    E41_SetMode(0X3);
    UART3_WriteBbuf(Head, 3);
    Delay1s(1); //wait for receive complete
    if (!UART3_ReceiveBufferIsEmpty()) {
        R_byte = UART3_ReadBuffer(tmp, 20); //��ȡѹ��ֵ
        if (/*UART_Is_Get(tmp, Head, R_byte, 3) &&*/ R_byte > 5) {//ע�����ȵĽ��˳��
            UART1_WriteBuf(tmp, R_byte);
        }
    }
    E41_SetMode(0X1);
}



