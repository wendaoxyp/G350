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
    S_MASTER_SEND_ADDR_16BIT, //发送寄存器地址16位地址，而不是从设备的地址
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
    uint8_t F_IsSelectiveMode : 1; //是否是选择模式，如果是根据选择的地址进行数据读取
    uint8_t F_Is16bitsDevice : 1; //通讯是否有16位操作地址
    uint8_t F_WriteOrRead : 1; //读操作（1）还是写操作（0）
    //    uint8_t F_IsFinish : 1;//数据操作是否完成
} I2C_Flag;

typedef struct {
    uint8_t operatcode; //操作码
    uint16_t address; // 数据地址 EEROM的地址是1010100X，时钟芯片地址是1010001X X意味0读1写
    uint8_t length; //数据长度
    uint8_t *pbuffer; // 数据指针
    I2C_Flag flag;
    //    bool IsSelectMode; //是否顺序读取
    //    uint8_t device; //设备选择 CAT24C512 PCF8583
} I2C1_Buffer;
extern I2C1_Buffer i2c_buf;
extern volatile uint8_t i2c1_state;

void I2C_Init(void);
void Start_I2C(void);
void Clear_I2C_Sta(void);

#endif



