#include "I2C.h"

volatile uint8_t i2c1_state;
I2C1_Buffer i2c_buf;

void I2C_Init(void) {
    TRISGbits.TRISG2 = 0; //将SCL1设置为输出口
    TRISGbits.TRISG3 = 0; //将SCK1设置为输出口
    I2C1BRG = 0x9D; //100kHz Fcy=16000000
    I2C1CONbits.I2CEN = 1; //使能I2C1
    I2C1CONbits.I2CSIDL = 0; //模块在空闲模式下继续工作
    I2C1CONbits.IPMIEN = 0; //禁止IPMI模式
    I2C1CONbits.A10M = 0; //7位从地址
    IFS1bits.MI2C1IF = 0; //清楚Master标志位
    IEC1bits.MI2C1IE = 1; //使能Master中断
    //    IEC1bits.SI2C1IE = 1;//使能Slave中断
    //    IFS1bits.SI2C1IF = 0;//清楚Slave标志位
    //    I2C1CONbits.I2CEN = 0; //关闭I2C1
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
//    if (I2C1STATbits.IWCOL) {//如果写冲突检测位为1，那么清楚错误位，并将状态设置为空闲
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

