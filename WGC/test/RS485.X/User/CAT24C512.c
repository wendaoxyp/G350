#include "CAT24C512.h"

//ȡֵ��Χ0x0000-0xffff 512kb
#define BufferSize 40//һ��ɼ����ݵ��ֽ�


uint16_t CAT_OperatID;
//CAT24Arg CAT24Argbits;

void CAT24C512_Init(void) {
    TRISBbits.TRISB12 = 0; //WP��������Ϊ���    
    LATBbits.LATB12 = 1;//����д����
    //    CAT24Argbits.ID = 0; //��ʼ���ṹ��
    //    CAT24Argbits.data = NULL;
}

void CAT24C512_Read(uint16_t id, uint8_t *tmp) {
    //    uint8_t tmp[BufferSize] = {1, 2, 3, 4}; //����cat24c512 ��ַ0xA8д������ַ 
    i2c_buf.operatcode = CAT_ADD;
    i2c_buf.address = id*BufferSize;
    i2c_buf.length = BufferSize; //sizeof (tmp) / sizeof (uint8_t) - 1;
    i2c_buf.pbuffer = tmp;
    i2c_buf.flag.F_IsSelectiveMode = 1;
    i2c_buf.flag.F_WriteOrRead = 1;
    i2c_buf.flag.F_Is16bitsDevice = 1;
    i2c1_state = S_MASTER_IDLE;
    IFS1bits.MI2C1IF = 1; //��ʼI2C
    //�ȴ����ݷ�����ɻ��������쳣
    //�������ݸ���λ��
    while (i2c1_state != S_MASTER_SEND_STOP); //�ȴ�������ɣ������ظ���������
}

void CAT24C512_Write(uint16_t id, uint8_t *tmp) {
    //    uint8_t tmp[BufferSize] = {1, 2, 3, 4}; //����cat24c512 ��ַ0xA8д������ַ 
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
    while (i2c1_state != S_MASTER_SEND_STOP); //�ȴ�������ɣ������ظ���������
    //�ȴ����ݷ�����ɻ��������쳣
}


