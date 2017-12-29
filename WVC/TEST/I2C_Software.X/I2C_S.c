#include "I2C_S.h"

void I2C_Init(void) {
    I2C_SCL = 1; //初始化保持I2C总线置高，通过上拉电阻
    I2C_SDA = 1;
    I2C_DELAY(1);
}

void I2C_Start(void) {
    I2C_SDA = 0;
    I2C_DELAY(1); //确保IC端能被识别，至少几us
    I2C_SCL = 0;
    I2C_DELAY(1);
}

void I2C_Stop() {
    I2C_SCL = 1;
    I2C_DELAY(1); //确保IC端能被识别，至少几us
    I2C_SDA = 0;
    I2C_DELAY(1);
}

void I2C_WriteICAdd(const uint8_t add, const uint8_t opreation) {
    uint8_t cnt, tmp = (add << 7) + (opreation & 0x01);
    for (cnt = 7; cnt > 0; cnt--) {
        I2C_SCL = 1;
        I2C_DELAY(1);
        I2C_SDA = (tmp >> cnt) ? 1 : 0;
        I2C_DELAY(1);
        I2C_SCL = 0;
        I2C_DELAY(1);
    }
}

void I2C_WriteOpretAdd(uint8_t add) {
    uint8_t cnt;
    for (cnt = 7; cnt > 0; cnt--) {
        I2C_SCL = 1;
        I2C_DELAY(1);
        I2C_SDA = (add >> cnt) ? 1 : 0;
        I2C_DELAY(1);
        I2C_SCL = 0;
        I2C_DELAY(1);
    }
}

void I2C_WriteOpretAdd16(uint16_t add) {

}

void I2C_WriteData(uint8_t dat) {

}

void I2C_ReadData(uint8_t dat) {

}

uint8_t I2C_ACK(void) {
    I2C_SCL = 1;
    I2C_DELAY(1);

    if (!I2C_R_SDA) {//如果接受到ACK，那么跳过；反之，如果没有接受ACK，提示错误
        //        I2C_DELAY(1);
        return I2C_ERR_NO_ACK;
    }
    I2C_SCL = 0;
    I2C_DELAY(1);
    return I2C_GET_ACK;
}

void I2C_NACK(void) {
    I2C_SDA = 1;
    I2C_DELAY(1);

    I2C_SCL = 1;
    I2C_DELAY(1);

    I2C_SCL = 0;
    I2C_DELAY(1);
    //    return I2C_GET_ACK;
}

