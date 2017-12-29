#include "E41.h"

#define M0_TRIS TRISEbits.TRISE5
#define M1_TRIS TRISEbits.TRISE6
#define M0 LATEbits.LATE5
#define M1 LATEbits.LATE6
#define M0_PORT PORTEbits.RE5
#define M1_PORT PORTEbits.RE6
#define AUX PORTFbits.RF6

#define WORK 0
#define WAKE 1
#define LOWPOWER 2
#define SLEEP 3
uint8_t E41_Arg[] = {0xC0, 0xff, 0xff, 0x18, 0x1, 0xfc};
// FF FF 18 01 9C
//static ADDBITS E41_ADD;
//static ARG1BITS E41_ARG1;
//static ARG2BITS E41_ARG2;

/*
ģʽ�л��� AUX���ڵ͹���Ӧ���У��û���Ƭ��������Ҫ�л�����ģʽ���Ӷ��ﵽ���ߡ����߻��ѵ�Ŀ�ġ���ʱ��
AUX ���Ž��𵽹ؼ����á����������¼������棺
a) ��λ��ģ���Լ��ڼ� AUX ����͵�ƽ��AUX �����غ�ģ��ſ�ʼ?�빤��״̬��
b) ��ģʽ 3 �л�������ģʽ��ģ��Ҳ������Լ죬AUX �Ҽ�״̬��ͬ�ڸ�λ��
c) ģʽ�л�ǰ����� AUX �Ǹߵ�ƽ������ֱ�Ӹķ� M1M0 �л�����ģʽ��2ms ��Ч��
d) ģʽ�л�ǰ����� AUX �ǵ͵�ƽ������ֱ�Ӹķ� M1M0 �л�����ģʽ��AUX �����غ� 2ms ��Ч��
 */
static void E41_SetMode(uint8_t mode) {
    //��ȡ��ǰ��ģʽ
    //    uint8_t now_mode = M0_PORT + (M1_PORT << 1);//mark
    //���õ�ǰģʽ
    //    switch (mode) {
    //        case SLEEP:
    //        {
    INT0_Close(); //�رմ��ڣ������л�ģʽ���´������
    M0 = 0;
    M1 = 0; //�����Լ����
    Delay100ms(3); //(0, 0, 0, 250);
    M0 = mode & 0x01;
    M1 = (mode >> 1) & 0x01;
    Delay10ms(1); //(0, 0, 0, 10);
    INT0_Open();
    //            break;
    //        }
    //        case LOWPOWER:
    //        {
    //            break;
    //        }
    //        case WAKE:
    //        {
    //            break;
    //        }
    //        case WORK:
    //        {
    //            break;
}
//            M0 = mode & 0x01;
//            M1 = (mode >> 1) & 0x01;
//}
//}

void E41_Init(void) {
    uint8_t cnt;
    M0_TRIS = 0; //��������
    M1_TRIS = 0;
    //    uint8_t currentMode = E41_SetGetMode(10);
    E41_SetMode(SLEEP);
    Delay100ms(3); //(0, 0, 0, 300); //����� 300ms �ܿ��Լ�
    //    UART3_SendChar(0xC0);
    for (cnt = 0; cnt < 3; cnt++) {
        UART3_SendString(E41_Arg, 6);
        //    UART3_SendString(E41_Arg, 6);
        Delay10ms(1);
//        (0, 0, 0, 10);
    }
    //    E41_SetMode(LOWPOWER); //����Ϊ�͹���ģʽ
    //    E41_SetMode(WORK); //����Ϊ����ģʽ   
    E41_SetMode(WAKE); //����Ϊ����ģʽ   
}

bool E41_PressureIsGet(float* pres) {//���ܵ���ѹ��ֵΪ01 03 04 3E F4 00 00 B6 29��16���ƣ�
    //�жϽ��ܵ������������Ǳ���ѹ��ֵ
    uint8_t tmp[10];
    uint8_t Head[3] = {0x1, 0x3, 0x4};
    U3Rx4Byte();
    StrCmp stcp;
    uint8_t Source_tmp[50]; //��ʱ����

    stcp.Source_len = UARTGetData(BufferRead_UART3, Source_tmp, 10);
    if (stcp.Source_len>sizeof (Source_tmp) / sizeof (uint8_t))//���ƴ������βɼ����ݴ���50���ֽڣ��������50���ֽڣ���ô����Ϊ50���ֽ�
        stcp.Source_len = 50;
    stcp.SourceData = Source_tmp;
    stcp.CheckData = Head;
    stcp.Check_len = 3;
    stcp.GetData = tmp;
    stcp.Get_len = 8;
    stcp.Real_len = 0;
    UARTDataIsRight(&stcp);
    if ((stcp.Real_len == 9) && CRCIsRight(tmp, 7, tmp + 7)) {//ע�����ȵĽ��˳��
        CharToFloat(pres, tmp + 3);
        return true;
    }
    return false;
}

void E41_Active_Send(void) {//���ܵ���ѹ��ֵΪ01 03 04 3E F4 00 00 B6 29��16���ƣ�
    //�жϽ��ܵ������������Ǳ���ѹ��ֵ
    uint8_t E41_tmp[20] = {0x00, 0x01, 0x01, 0x12, 0x34, 0x20, 0x30, 0x42}, cnt;
    E41_SetMode(WAKE); //����Ϊ����ģʽ    
    Delay100ms(1); //(0, 0, 0, 100);
    INT0_Close();
    //    for (cnt = 0; cnt < 3; cnt++) {
    UART3_SendString(E41_tmp, 8);
    Delay10ms(1); //(0, 0, 0, 10);
    //�����
    //    }
    INT0_Open();
    Delay1s(10); //(0, 0, 10, 0);
    E41_SetMode(LOWPOWER); //����Ϊ�͹���ģʽ    
    //    OSTimeDlyHMSM(0, 0, 10, 0);
}


