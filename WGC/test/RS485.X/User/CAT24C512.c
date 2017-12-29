#include "CAT24C512.h"

//取值范围0x0000-0xffff 512kb
#define BufferSize 40//一组采集数据的字节


uint16_t CAT_OperatID;
//CAT24Arg CAT24Argbits;

void CAT24C512_Init(void) {
    TRISBbits.TRISB12 = 0; //WP引脚设置为输出    
    LATBbits.LATB12 = 1;//开启写保护
    //    CAT24Argbits.ID = 0; //初始化结构体
    //    CAT24Argbits.data = NULL;
}

void CAT24C512_Read(uint16_t id, uint8_t *tmp) {
    //    uint8_t tmp[BufferSize] = {1, 2, 3, 4}; //调试cat24c512 地址0xA8写操作地址 
    i2c_buf.operatcode = CAT_ADD;
    i2c_buf.address = id*BufferSize;
    i2c_buf.length = BufferSize; //sizeof (tmp) / sizeof (uint8_t) - 1;
    i2c_buf.pbuffer = tmp;
    i2c_buf.flag.F_IsSelectiveMode = 1;
    i2c_buf.flag.F_WriteOrRead = 1;
    i2c_buf.flag.F_Is16bitsDevice = 1;
    i2c1_state = S_MASTER_IDLE;
    IFS1bits.MI2C1IF = 1; //开始I2C
    //等待数据发送完成或是数据异常
    //发送数据给上位机
    while (i2c1_state != S_MASTER_SEND_STOP); //等待发送完成，避免重复发送数据
}

void CAT24C512_Write(uint16_t id, uint8_t *tmp) {
    //    uint8_t tmp[BufferSize] = {1, 2, 3, 4}; //调试cat24c512 地址0xA8写操作地址 
    //    uint8_t tmp1[4] = {CAT_ADD, 0x00, 0x00, 0x00};
    i2c_buf.operatcode = CAT_ADD;
    i2c_buf.address = id*BufferSize;
    i2c_buf.length = BufferSize; //sizeof (tmp) / sizeof (uint8_t) - 1;
    i2c_buf.pbuffer = tmp;
    i2c_buf.flag.F_IsSelectiveMode = 1;
    i2c_buf.flag.F_WriteOrRead = 0;
    i2c_buf.flag.F_Is16bitsDevice = 1;
    i2c1_state = S_MASTER_IDLE;
    IFS1bits.MI2C1IF = 1;
    while (i2c1_state != S_MASTER_SEND_STOP); //等待发送完成，避免重复发送数据
    //等待数据发送完成或是数据异常
}


