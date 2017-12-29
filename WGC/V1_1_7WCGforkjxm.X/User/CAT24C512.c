#include "CAT24C512.h"

uint16_t CAT_OperatID, CAT_StartID;
//CAT24Arg CAT24Argbits;
static void CAT24C512_ReadADD(void);
static void CAT24C512_WriteADD(uint8_t mode);

void CAT24C512_Init(void) {
    I2C_Init(); //初始化i2c,用于获取时钟和存储数据D
    TRISBbits.TRISB12 = 0; //WP引脚设置为输出    
    //    CAT_WP = 0; //开启写保护
    //    CAT24Argbits.ID = 0; //初始化结构体
    //    CAT24Argbits.data = NULL;
    //#
    //        CAT_OperatID = 0xaaaa;
    //        CAT_StartID = 0xFFFF;
    //    CAT24C512_WriteADD(0); //刷新上次操作数据
    CAT24C512_ReadADD();
}

void CAT24C512_Read(uint16_t id, uint8_t *tmp) {//读取一组数据
    uint8_t cnt; //调试cat24c512 地址0xA8写操作地址     
    if (CAT_StartID == CAT_OperatID)//提示错误
        return;
    CAT_WP = 0; //写保护
    for (cnt = 0; cnt < BufferSize; cnt++) {
        i2c_buf.operatcode = CAT_ADD;
        i2c_buf.address = id * BufferSize + cnt;
        i2c_buf.length = 1; //sizeof (tmp) / sizeof (uint8_t) - 1;
        i2c_buf.pbuffer = tmp + cnt;
        i2c_buf.flag.F_IsSelectiveMode = 1;
        i2c_buf.flag.F_WriteOrRead = 1;
        i2c_buf.flag.F_Is16bitsDevice = 1;
        i2c1_state = S_MASTER_IDLE;
        Delay10ms(1); //延时等待数据通讯完成
        IFS1bits.MI2C1IF = 1; //开始I2C
        //等待数据发送完成或是数据异常
        //发送数据给上位机
        while (i2c1_state != S_MASTER_Finish) //等待发送完成，避免重复发送数据
            if (i2c1_state == S_MASTER_Fail) {
                CAT_WP = 1; //保护
                return; //提示错误信息
            }
        Delay1ms(1);
    }
    CAT_WP = 1; //保护
    CAT_StartID += 1;
    CAT_StartID = CAT_StartID % CAT_NUMS;
}

void CAT24C512_Write(uint8_t *tmp) {//页写 
    CAT_WP = 0; //写保护
    i2c_buf.operatcode = CAT_ADD;
    i2c_buf.address = CAT_OperatID*BufferSize;
    i2c_buf.length = BufferSize; //sizeof (tmp) / sizeof (uint8_t) - 1;
    i2c_buf.pbuffer = tmp;
    i2c_buf.flag.F_IsSelectiveMode = 1;
    i2c_buf.flag.F_WriteOrRead = 0;
    i2c_buf.flag.F_Is16bitsDevice = 1;
    i2c1_state = S_MASTER_IDLE;
    IFS1bits.MI2C1IF = 1; //开始I2C通讯
    //    I2C1CONbits.SEN =1;
    Delay10ms(1); //延时等待数据通讯完成
    while (i2c1_state != S_MASTER_Finish) //等待发送完成，避免重复发送数据
        if (i2c1_state == S_MASTER_Fail) {
            CAT_WP = 1; //保护
            return; //提示错误信息
        }
    //等待数据发送完成或是数据异常
    Delay10ms(1);
    CAT_WP = 1; //保护
    CAT_OperatID += 1;
    CAT_OperatID = CAT_OperatID % CAT_NUMS; //需要添加防止溢出的处理
}

static void CAT24C512_ReadADD(void) {
    uint8_t tmp[4] = {0, 0};
    uint8_t cnt = 0, cnt1 = 0;

    CAT_WP = 0; //写保护
    for (cnt = 0; cnt < 4; cnt++) {//选择读取        

        i2c_buf.operatcode = CAT_ADD;
        i2c_buf.address = CAT_NOW_ADD + cnt;
        i2c_buf.length = 1; //sizeof (tmp) / sizeof (uint8_t) - 1;
        i2c_buf.pbuffer = tmp + cnt;
        i2c_buf.flag.F_IsSelectiveMode = 1;
        i2c_buf.flag.F_WriteOrRead = 1;
        i2c_buf.flag.F_Is16bitsDevice = 1;
        i2c1_state = S_MASTER_IDLE;
        Delay10ms(1); //延时等待数据通讯完成
        IFS1bits.MI2C1IF = 1; //开始I2C通讯
        while (i2c1_state != S_MASTER_Finish) {//等待发送完成，避免重复发送数据
            if (i2c1_state == S_MASTER_Fail) {
                CAT_WP = 1; //保护
                return; //提示错误信息
            }
            Delay10ms(1); //延时等待数据通讯完成
            CAT_WP = 1; //保护
            return;
        }
        //        i2c1_state = S_MASTER_IDLE;
        //等待数据发送完成或是数据异常        
        Delay1ms(1);
    }
    CAT_WP = 1; //保护
    CAT_StartID = ((uint16_t) tmp[0] << 8) + tmp[1]; //刷新ID地址  
    CAT_OperatID = ((uint16_t) tmp[2] << 8) + tmp[3]; //刷新ID地址  
}

static void CAT24C512_WriteADD(uint8_t mode) {
    uint8_t tmp[4] = {0, 0};
    //    CAT_StartID = ((uint16_t) tmp[2] << 8) + tmp[3]; //刷新ID地址 
    tmp[0] = (CAT_StartID >> 8)& 0x00ff; //刷新ID地址  
    tmp[1] = CAT_StartID & 0x00ff;
    tmp[2] = (CAT_OperatID >> 8)& 0x00ff; //刷新ID地址  
    tmp[3] = CAT_OperatID & 0x00ff;

    CAT_WP = 0; //写保护
    i2c_buf.operatcode = CAT_ADD;
    if (mode == CAT_START_READ) {//表示开始读取地址写到EEROM中
        i2c_buf.address = CAT_NOW_ADD;
        i2c_buf.length = 2; //
        i2c_buf.pbuffer = tmp;
    } else if (mode == CAT_START_WRITE) {//表示数据写入地址写到EEROM中
        i2c_buf.address = CAT_NOW_ADD + 2;
        i2c_buf.length = 2; //        
        i2c_buf.pbuffer = tmp + 2;
    } else {
        i2c_buf.address = CAT_NOW_ADD; //更新全部
        i2c_buf.length = 4; //        
        i2c_buf.pbuffer = tmp;
    }
    i2c_buf.flag.F_IsSelectiveMode = 1;
    i2c_buf.flag.F_WriteOrRead = 0;
    i2c_buf.flag.F_Is16bitsDevice = 1;
    i2c1_state = S_MASTER_IDLE;
    //    while (IFS1bits.MI2C1IF);
    IFS1bits.MI2C1IF = 1; //开始I2C通讯
    while (i2c1_state != S_MASTER_SEND_STOP) //等待发送完成，避免重复发送数据
        if (i2c1_state == S_MASTER_Fail) {
            CAT_WP = 1; //保护
            return; //提示错误信息
        }
    //等待数据发送完成或是数据异常
    Delay1ms(1);
    CAT_WP = 1; //保护
}

//void Get
