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
模式切换和 AUX：在低功耗应用中，用户单片机可能需要切换工作模式，从而达到休眠、无线唤醒的目的。此时，
AUX 引脚将起到关键作用。表现在如下几个方面：
a) 复位后，模块自检期间 AUX 处理低电平，AUX 上升沿后，模块才开始?入工作状态。
b) 从模式 3 切换到其他模式后，模块也会产生自检，AUX 逡辑状态等同于复位。
c) 模式切换前，如果 AUX 是高电平，可以直接改发 M1M0 切换到新模式，2ms 生效。
d) 模式切换前，如果 AUX 是低电平，可以直接改发 M1M0 切换到新模式，AUX 上升沿后 2ms 生效。
 */
static void E41_SetMode(uint8_t mode) {
    //获取当前的模式
    //    uint8_t now_mode = M0_PORT + (M1_PORT << 1);//mark
    //设置当前模式
    //    switch (mode) {
    //        case SLEEP:
    //        {
    INT0_Close(); //关闭串口，避免切换模式导致错误接受
    M0 = 0;
    M1 = 0; //避免自检程序
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
    M0_TRIS = 0; //设置引脚
    M1_TRIS = 0;
    //    uint8_t currentMode = E41_SetGetMode(10);
    E41_SetMode(SLEEP);
    Delay100ms(3); //(0, 0, 0, 300); //必须加 300ms 避开自检
    //    UART3_SendChar(0xC0);
    for (cnt = 0; cnt < 3; cnt++) {
        UART3_SendString(E41_Arg, 6);
        //    UART3_SendString(E41_Arg, 6);
        Delay10ms(1);
//        (0, 0, 0, 10);
    }
    //    E41_SetMode(LOWPOWER); //设置为低功耗模式
    //    E41_SetMode(WORK); //设置为唤醒模式   
    E41_SetMode(WAKE); //设置为唤醒模式   
}

bool E41_PressureIsGet(float* pres) {//接受到的压力值为01 03 04 3E F4 00 00 B6 29（16进制）
    //判断接受到数据类型是仪表还是压力值
    uint8_t tmp[10];
    uint8_t Head[3] = {0x1, 0x3, 0x4};
    U3Rx4Byte();
    StrCmp stcp;
    uint8_t Source_tmp[50]; //临时变量

    stcp.Source_len = UARTGetData(BufferRead_UART3, Source_tmp, 10);
    if (stcp.Source_len>sizeof (Source_tmp) / sizeof (uint8_t))//限制处理，单次采集数据大于50个字节，如果大于50个字节，那么设置为50个字节
        stcp.Source_len = 50;
    stcp.SourceData = Source_tmp;
    stcp.CheckData = Head;
    stcp.Check_len = 3;
    stcp.GetData = tmp;
    stcp.Get_len = 8;
    stcp.Real_len = 0;
    UARTDataIsRight(&stcp);
    if ((stcp.Real_len == 9) && CRCIsRight(tmp, 7, tmp + 7)) {//注意优先的结合顺序
        CharToFloat(pres, tmp + 3);
        return true;
    }
    return false;
}

void E41_Active_Send(void) {//接受到的压力值为01 03 04 3E F4 00 00 B6 29（16进制）
    //判断接受到数据类型是仪表还是压力值
    uint8_t E41_tmp[20] = {0x00, 0x01, 0x01, 0x12, 0x34, 0x20, 0x30, 0x42}, cnt;
    E41_SetMode(WAKE); //设置为唤醒模式    
    Delay100ms(1); //(0, 0, 0, 100);
    INT0_Close();
    //    for (cnt = 0; cnt < 3; cnt++) {
    UART3_SendString(E41_tmp, 8);
    Delay10ms(1); //(0, 0, 0, 10);
    //必须加
    //    }
    INT0_Open();
    Delay1s(10); //(0, 0, 10, 0);
    E41_SetMode(LOWPOWER); //设置为低功耗模式    
    //    OSTimeDlyHMSM(0, 0, 10, 0);
}


