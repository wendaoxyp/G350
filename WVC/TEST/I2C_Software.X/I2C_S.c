#include "I2C_S.h"

void I2C_Init(void) {
    I2C_SCL = 1; //��ʼ������I2C�����øߣ�ͨ����������
    I2C_SDA = 1;
    I2C_DELAY(1);
}

void I2C_Start(void) {
    I2C_SDA = 0;
    I2C_DELAY(1); //ȷ��IC���ܱ�ʶ�����ټ�us
    I2C_SCL = 0;
    I2C_DELAY(1);
}

void I2C_Stop() {
    I2C_SCL = 1;
    I2C_DELAY(1); //ȷ��IC���ܱ�ʶ�����ټ�us
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

    if (!I2C_R_SDA) {//������ܵ�ACK����ô��������֮�����û�н���ACK����ʾ����
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

