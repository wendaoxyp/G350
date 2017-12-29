#ifndef I2C_H
#define I2C_H

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

typedef enum {
    S_MASTER_IDLE, //0
    S_MASTER_RESTART, //1
    S_MASTER_SEND_ADDR, //2
    S_MASTER_SEND_DATA, //3
    S_MASTER_SEND_ADDR_16BIT, //���ͼĴ�����ַ16λ��ַ�������Ǵ��豸�ĵ�ַ
    S_MASTER_SEND_ADDR_16BIT_LSB, //5
    S_MASTER_SEND_STOP, //6
    S_MASTER_ACK_ADDR, //7
    S_MASTER_RCV_DATA,
    S_MASTER_RCV_STOP, //9
    S_MASTER_ACK_RCV_DATA,//10
    S_MASTER_NOACK_STOP,//11
    S_MASTER_16BIT_RESTART,//12
    S_MASTER_Finish,//13
    S_MASTER_Fail
} I2C_MASTER_STATES;

//typedef enum {
//    I2C1_MESSAGE_FAIL,
//    I2C1_MESSAGE_PENDING,
//    I2C1_MESSAGE_COMPLETE,
//    I2C1_STUCK_START,
//    I2C1_MESSAGE_ADDRESS_NO_ACK,
//    I2C1_DATA_NO_ACK,
//    I2C1_LOST_STATE
//} I2C1_MESSAGE_STATUS;

typedef struct {
    uint8_t F_IsSelectiveMode : 1; //�Ƿ���ѡ��ģʽ������Ǹ���ѡ��ĵ�ַ�������ݶ�ȡ
    uint8_t F_Is16bitsDevice : 1; //ͨѶ�Ƿ���16λ������ַ
    uint8_t F_WriteOrRead : 1; //��������1������д������0��
    //    uint8_t F_IsFinish : 1;//���ݲ����Ƿ����
} I2C_Flag;

typedef struct {
    uint8_t operatcode; //������
    uint16_t address; // ���ݵ�ַ EEROM�ĵ�ַ��1010100X��ʱ��оƬ��ַ��1010001X X��ζ0��1д
    uint8_t length; //���ݳ���
    uint8_t *pbuffer; // ����ָ��
    I2C_Flag flag;
    //    bool IsSelectMode; //�Ƿ�˳���ȡ
    //    uint8_t device; //�豸ѡ�� CAT24C512 PCF8583
} I2C1_Buffer;
extern I2C1_Buffer i2c_buf;
extern volatile uint8_t i2c1_state;

void I2C_Init(void);
void Start_I2C(void);
void Clear_I2C_Sta(void);

#endif



