#include "I2C_S.h"



/*************************************
Function: I2C_Init 
Description: ��ʼ��I2C��IO
Input: void
Output: void
 *************************************/
void I2C_Init(void) {
    I2C_SCL_DIR = 0; //SCL����Ϊ���
    I2C_SDA_DIR = 0; //SDA����Ϊ���
    I2C_SCL = 1; //SCL�ø�
    I2C_SDA = 1; //SDA�ø�
    I2C_DELAY(1);
}



/*************************************
Function: I2C_Start 
Description: I2C��������
Input: void 
Output: void
 *************************************/
void I2C_Start(void) {
    I2C_SDA = 1; //��������
    I2C_DELAY(1);
    I2C_SCL = 1; //��������
    I2C_DELAY(1);
    I2C_SDA = 0; //�����õ�
    I2C_DELAY(1); //ȷ��IC���ܱ�ʶ�����ټ�us
    I2C_SCL = 0; //�ͷ�����
    I2C_DELAY(1);
}
/*************************************
Function: I2C_Stop 
Description: I2Cֹͣ����
Input: void
Output: void
 *************************************/
void I2C_Stop(void) {
    I2C_SDA = 0; //�����õ�
    I2C_DELAY(1);
    I2C_SCL = 1; //��������
    I2C_DELAY(1); //ȷ��IC���ܱ�ʶ�����ټ�us
    I2C_SDA = 1; //�����ø�
    I2C_DELAY(1);
}
/*************************************
Function: I2C_WriteICAdd 
Description: I2CдIC��ַ
Input: ����IC��ַadd�����ݲ���opreation
Output: �����ֵ
 *************************************/
void I2C_WriteICAdd(const uint8_t add, const uint8_t opreation) {
    uint8_t tmp = add | (opreation & 0x01); //������ʱ�������������ݸ�ֵadd+opreation
    int8_t cnt;
    for (cnt = 7; cnt >= 0; cnt--) {//ѭ����ȡ��������
        I2C_SDA = ((tmp >> cnt) & 0x01) ? 1 : 0; //SDA������Ӧ�ô���SCL��SCL�м�ɼ�
        I2C_DELAY(1);
        I2C_SCL = 1;
        I2C_DELAY(1);
        I2C_SCL = 0;
        if (!cnt && I2C_SDA)//������λ����1����SDA=0,����I2CЭ��ͨѶʧ��
            I2C_SDA = 0;
    }
}
/*************************************
Function: FloatToChar 
Description: ������ת��Ϊchar����
Input: ���븡���� ģʽ��4 �����ȸ����� 8 ˫���ȸ����� 
Output: �����ֵ
 *************************************/
void I2C_WriteOpretAdd(uint8_t add) {
    uint8_t tmp = add; // | (opreation & 0x01);
    int8_t cnt;
    for (cnt = 7; cnt >= 0; cnt--) {
        I2C_SDA = ((tmp >> cnt) & 0x01) ? 1 : 0; //SDA������Ӧ�ô���SCL��SCL�м�ɼ�
        I2C_DELAY(1);
        I2C_SCL = 1; //��������
        I2C_DELAY(1);
        I2C_SCL = 0; //�ͷ�����
        I2C_DELAY(1);
        if (!cnt && I2C_SDA)//������λ����1����SDA=0,����I2CЭ��ͨѶʧ��
            I2C_SDA = 0;
    }
}
/*************************************
Function: FloatToChar 
Description: ������ת��Ϊchar����
Input: ���븡���� ģʽ��4 �����ȸ����� 8 ˫���ȸ����� 
Output: �����ֵ
 *************************************/
void I2C_WriteData(uint8_t dat) {
    uint8_t tmp = dat; //������ʱ����
    int8_t cnt;
    for (cnt = 7; cnt >= 0; cnt--) {//ѭ����ȡ����
        I2C_SDA = ((tmp >> cnt) & 0x01) ? 1 : 0; //SDA������Ӧ�ô���SCL��SCL�м�ɼ�
        I2C_DELAY(1);
        I2C_SCL = 1; //��������
        I2C_DELAY(1);
        I2C_SCL = 0; //�ͷ�����
        I2C_DELAY(1);
        if (!cnt && I2C_SDA)//������λ����1����SDA=0,����I2CЭ��ͨѶʧ��
            I2C_SDA = 0;
    }
}
/*************************************
Function: FloatToChar 
Description: ������ת��Ϊchar����
Input: ���븡���� ģʽ��4 �����ȸ����� 8 ˫���ȸ����� 
Output: �����ֵ
 *************************************/
uint8_t I2C_ReadData(void) {
    uint8_t tmp = 0; //������ʱ����
    int8_t cnt;
    I2C_SDA_DIR = 1; //��������Ϊ����
    for (cnt = 7; cnt >= 0; cnt--) {//ѭ����ȡ���ݣ�I2CЭ����������Ϊ��ʱ���м��ȡ����
        I2C_SCL = 1; //��������
        I2C_DELAY(1);
        tmp |= I2C_R_SDA << cnt; //�м�ɼ�
        I2C_DELAY(1);
        I2C_SCL = 0; //�ͷ�����
        I2C_DELAY(1);
    }
    I2C_SDA_DIR = 0; //��������Ϊ���
    return tmp; //���ؽ��
}
/*************************************
Function: FloatToChar 
Description: ������ת��Ϊchar����
Input: ���븡���� ģʽ��4 �����ȸ����� 8 ˫���ȸ����� 
Output: �����ֵ
 *************************************/
uint8_t I2C_ACK(void) {
    uint8_t I2C_SDA_STA; //����I2C״̬����
    I2C_SDA_DIR = 1; //�л�Ϊ���루���軻����
    I2C_SCL = 1; //��������
    I2C_DELAY(1);
    I2C_SDA_STA = (I2C_R_SDA) ? I2C_ERR_NO_ACK : I2C_GET_ACK; //�ж��Ƿ��ȡ��ACK
    I2C_DELAY(1);
    I2C_SCL = 0; //�ͷ�����
    I2C_DELAY(1);
    I2C_SDA_DIR = 0; //����Ϊ���
    //    I2C_SDA = 1; //��������Ϊ��
    return I2C_SDA_STA; //����ACK״̬
}
/*************************************
Function: FloatToChar 
Description: ������ת��Ϊchar����
Input: ���븡���� ģʽ��4 �����ȸ����� 8 ˫���ȸ����� 
Output: �����ֵ
 *************************************/
void I2C_NACK(void) {
    I2C_SDA = 1; //�����ø�
    I2C_DELAY(1);

    I2C_SCL = 1; //��������
    I2C_DELAY(1);

    I2C_SCL = 0; //�����õ�
    I2C_DELAY(1);

    I2C_SDA = 0; //�ͷ�����
    I2C_DELAY(1);
}





