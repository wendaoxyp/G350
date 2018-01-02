#include "I2C_S.h"



/*************************************
Function: I2C_Init 
Description: 初始化I2C的IO
Input: void
Output: void
 *************************************/
void I2C_Init(void) {
    I2C_SCL_DIR = 0; //SCL设置为输出
    I2C_SDA_DIR = 0; //SDA设置为输出
    I2C_SCL = 1; //SCL置高
    I2C_SDA = 1; //SDA置高
    I2C_DELAY(1);
}



/*************************************
Function: I2C_Start 
Description: I2C启动函数
Input: void 
Output: void
 *************************************/
void I2C_Start(void) {
    I2C_SDA = 1; //数据拉高
    I2C_DELAY(1);
    I2C_SCL = 1; //握手总线
    I2C_DELAY(1);
    I2C_SDA = 0; //数据置低
    I2C_DELAY(1); //确保IC端能被识别，至少几us
    I2C_SCL = 0; //释放总线
    I2C_DELAY(1);
}
/*************************************
Function: I2C_Stop 
Description: I2C停止函数
Input: void
Output: void
 *************************************/
void I2C_Stop(void) {
    I2C_SDA = 0; //数据置低
    I2C_DELAY(1);
    I2C_SCL = 1; //握手总线
    I2C_DELAY(1); //确保IC端能被识别，至少几us
    I2C_SDA = 1; //数据置高
    I2C_DELAY(1);
}
/*************************************
Function: I2C_WriteICAdd 
Description: I2C写IC地址
Input: 输入IC地址add，数据操作opreation
Output: 输出数值
 *************************************/
void I2C_WriteICAdd(const uint8_t add, const uint8_t opreation) {
    uint8_t tmp = add | (opreation & 0x01); //申请临时变量，并将数据赋值add+opreation
    int8_t cnt;
    for (cnt = 7; cnt >= 0; cnt--) {//循环获取发送数据
        I2C_SDA = ((tmp >> cnt) & 0x01) ? 1 : 0; //SDA的周期应该大于SCL，SCL中间采集
        I2C_DELAY(1);
        I2C_SCL = 1;
        I2C_DELAY(1);
        I2C_SCL = 0;
        if (!cnt && I2C_SDA)//如果最后位发送1，将SDA=0,避免I2C协议通讯失败
            I2C_SDA = 0;
    }
}
/*************************************
Function: FloatToChar 
Description: 浮点数转化为char数组
Input: 输入浮点数 模式：4 单精度浮点数 8 双精度浮点数 
Output: 输出数值
 *************************************/
void I2C_WriteOpretAdd(uint8_t add) {
    uint8_t tmp = add; // | (opreation & 0x01);
    int8_t cnt;
    for (cnt = 7; cnt >= 0; cnt--) {
        I2C_SDA = ((tmp >> cnt) & 0x01) ? 1 : 0; //SDA的周期应该大于SCL，SCL中间采集
        I2C_DELAY(1);
        I2C_SCL = 1; //握手总线
        I2C_DELAY(1);
        I2C_SCL = 0; //释放总线
        I2C_DELAY(1);
        if (!cnt && I2C_SDA)//如果最后位发送1，将SDA=0,避免I2C协议通讯失败
            I2C_SDA = 0;
    }
}
/*************************************
Function: FloatToChar 
Description: 浮点数转化为char数组
Input: 输入浮点数 模式：4 单精度浮点数 8 双精度浮点数 
Output: 输出数值
 *************************************/
void I2C_WriteData(uint8_t dat) {
    uint8_t tmp = dat; //申明临时变量
    int8_t cnt;
    for (cnt = 7; cnt >= 0; cnt--) {//循环获取数据
        I2C_SDA = ((tmp >> cnt) & 0x01) ? 1 : 0; //SDA的周期应该大于SCL，SCL中间采集
        I2C_DELAY(1);
        I2C_SCL = 1; //握手总线
        I2C_DELAY(1);
        I2C_SCL = 0; //释放总线
        I2C_DELAY(1);
        if (!cnt && I2C_SDA)//如果最后位发送1，将SDA=0,避免I2C协议通讯失败
            I2C_SDA = 0;
    }
}
/*************************************
Function: FloatToChar 
Description: 浮点数转化为char数组
Input: 输入浮点数 模式：4 单精度浮点数 8 双精度浮点数 
Output: 输出数值
 *************************************/
uint8_t I2C_ReadData(void) {
    uint8_t tmp = 0; //声明临时变量
    int8_t cnt;
    I2C_SDA_DIR = 1; //数据设置为输入
    for (cnt = 7; cnt >= 0; cnt--) {//循环获取数据，I2C协议中是总线为高时，中间获取数据
        I2C_SCL = 1; //握手总线
        I2C_DELAY(1);
        tmp |= I2C_R_SDA << cnt; //中间采集
        I2C_DELAY(1);
        I2C_SCL = 0; //释放总线
        I2C_DELAY(1);
    }
    I2C_SDA_DIR = 0; //数据设置为输出
    return tmp; //返回结果
}
/*************************************
Function: FloatToChar 
Description: 浮点数转化为char数组
Input: 输入浮点数 模式：4 单精度浮点数 8 双精度浮点数 
Output: 输出数值
 *************************************/
uint8_t I2C_ACK(void) {
    uint8_t I2C_SDA_STA; //声明I2C状态变量
    I2C_SDA_DIR = 1; //切换为输入（必需换方向）
    I2C_SCL = 1; //握手总线
    I2C_DELAY(1);
    I2C_SDA_STA = (I2C_R_SDA) ? I2C_ERR_NO_ACK : I2C_GET_ACK; //判断是否获取到ACK
    I2C_DELAY(1);
    I2C_SCL = 0; //释放总线
    I2C_DELAY(1);
    I2C_SDA_DIR = 0; //设置为输出
    //    I2C_SDA = 1; //数据设置为高
    return I2C_SDA_STA; //返回ACK状态
}
/*************************************
Function: FloatToChar 
Description: 浮点数转化为char数组
Input: 输入浮点数 模式：4 单精度浮点数 8 双精度浮点数 
Output: 输出数值
 *************************************/
void I2C_NACK(void) {
    I2C_SDA = 1; //数据置高
    I2C_DELAY(1);

    I2C_SCL = 1; //握手总线
    I2C_DELAY(1);

    I2C_SCL = 0; //数据置低
    I2C_DELAY(1);

    I2C_SDA = 0; //释放总线
    I2C_DELAY(1);
}





