#include "CAT24C512.h"

uint16_t CAT_OperatID, CAT_StartID;
//CAT24Arg CAT24Argbits;
static void CAT24C512_ReadADD(void);
static void CAT24C512_WriteADD(uint8_t mode);

void CAT24C512_Init(void) {
    I2C_Init(); //��ʼ��i2c,���ڻ�ȡʱ�Ӻʹ洢����D
    TRISBbits.TRISB12 = 0; //WP��������Ϊ���    
    //    CAT_WP = 0; //����д����
    //    CAT24Argbits.ID = 0; //��ʼ���ṹ��
    //    CAT24Argbits.data = NULL;
    //#
    //        CAT_OperatID = 0xaaaa;
    //        CAT_StartID = 0xFFFF;
    //    CAT24C512_WriteADD(0); //ˢ���ϴβ�������
    CAT24C512_ReadADD();
}

void CAT24C512_Read(uint16_t id, uint8_t *tmp) {//��ȡһ������
    uint8_t cnt; //����cat24c512 ��ַ0xA8д������ַ     
    if (CAT_StartID == CAT_OperatID)//��ʾ����
        return;
    CAT_WP = 0; //д����
    for (cnt = 0; cnt < BufferSize; cnt++) {
        i2c_buf.operatcode = CAT_ADD;
        i2c_buf.address = id * BufferSize + cnt;
        i2c_buf.length = 1; //sizeof (tmp) / sizeof (uint8_t) - 1;
        i2c_buf.pbuffer = tmp + cnt;
        i2c_buf.flag.F_IsSelectiveMode = 1;
        i2c_buf.flag.F_WriteOrRead = 1;
        i2c_buf.flag.F_Is16bitsDevice = 1;
        i2c1_state = S_MASTER_IDLE;
        Delay10ms(1); //��ʱ�ȴ�����ͨѶ���
        IFS1bits.MI2C1IF = 1; //��ʼI2C
        //�ȴ����ݷ�����ɻ��������쳣
        //�������ݸ���λ��
        while (i2c1_state != S_MASTER_Finish) //�ȴ�������ɣ������ظ���������
            if (i2c1_state == S_MASTER_Fail) {
                CAT_WP = 1; //����
                return; //��ʾ������Ϣ
            }
        Delay1ms(1);
    }
    CAT_WP = 1; //����
    CAT_StartID += 1;
    CAT_StartID = CAT_StartID % CAT_NUMS;
}

void CAT24C512_Write(uint8_t *tmp) {//ҳд 
    CAT_WP = 0; //д����
    i2c_buf.operatcode = CAT_ADD;
    i2c_buf.address = CAT_OperatID*BufferSize;
    i2c_buf.length = BufferSize; //sizeof (tmp) / sizeof (uint8_t) - 1;
    i2c_buf.pbuffer = tmp;
    i2c_buf.flag.F_IsSelectiveMode = 1;
    i2c_buf.flag.F_WriteOrRead = 0;
    i2c_buf.flag.F_Is16bitsDevice = 1;
    i2c1_state = S_MASTER_IDLE;
    IFS1bits.MI2C1IF = 1; //��ʼI2CͨѶ
    //    I2C1CONbits.SEN =1;
    Delay10ms(1); //��ʱ�ȴ�����ͨѶ���
    while (i2c1_state != S_MASTER_Finish) //�ȴ�������ɣ������ظ���������
        if (i2c1_state == S_MASTER_Fail) {
            CAT_WP = 1; //����
            return; //��ʾ������Ϣ
        }
    //�ȴ����ݷ�����ɻ��������쳣
    Delay10ms(1);
    CAT_WP = 1; //����
    CAT_OperatID += 1;
    CAT_OperatID = CAT_OperatID % CAT_NUMS; //��Ҫ��ӷ�ֹ����Ĵ���
}

static void CAT24C512_ReadADD(void) {
    uint8_t tmp[4] = {0, 0};
    uint8_t cnt = 0, cnt1 = 0;

    CAT_WP = 0; //д����
    for (cnt = 0; cnt < 4; cnt++) {//ѡ���ȡ        

        i2c_buf.operatcode = CAT_ADD;
        i2c_buf.address = CAT_NOW_ADD + cnt;
        i2c_buf.length = 1; //sizeof (tmp) / sizeof (uint8_t) - 1;
        i2c_buf.pbuffer = tmp + cnt;
        i2c_buf.flag.F_IsSelectiveMode = 1;
        i2c_buf.flag.F_WriteOrRead = 1;
        i2c_buf.flag.F_Is16bitsDevice = 1;
        i2c1_state = S_MASTER_IDLE;
        Delay10ms(1); //��ʱ�ȴ�����ͨѶ���
        IFS1bits.MI2C1IF = 1; //��ʼI2CͨѶ
        while (i2c1_state != S_MASTER_Finish) {//�ȴ�������ɣ������ظ���������
            if (i2c1_state == S_MASTER_Fail) {
                CAT_WP = 1; //����
                return; //��ʾ������Ϣ
            }
            Delay10ms(1); //��ʱ�ȴ�����ͨѶ���
            CAT_WP = 1; //����
            return;
        }
        //        i2c1_state = S_MASTER_IDLE;
        //�ȴ����ݷ�����ɻ��������쳣        
        Delay1ms(1);
    }
    CAT_WP = 1; //����
    CAT_StartID = ((uint16_t) tmp[0] << 8) + tmp[1]; //ˢ��ID��ַ  
    CAT_OperatID = ((uint16_t) tmp[2] << 8) + tmp[3]; //ˢ��ID��ַ  
}

static void CAT24C512_WriteADD(uint8_t mode) {
    uint8_t tmp[4] = {0, 0};
    //    CAT_StartID = ((uint16_t) tmp[2] << 8) + tmp[3]; //ˢ��ID��ַ 
    tmp[0] = (CAT_StartID >> 8)& 0x00ff; //ˢ��ID��ַ  
    tmp[1] = CAT_StartID & 0x00ff;
    tmp[2] = (CAT_OperatID >> 8)& 0x00ff; //ˢ��ID��ַ  
    tmp[3] = CAT_OperatID & 0x00ff;

    CAT_WP = 0; //д����
    i2c_buf.operatcode = CAT_ADD;
    if (mode == CAT_START_READ) {//��ʾ��ʼ��ȡ��ַд��EEROM��
        i2c_buf.address = CAT_NOW_ADD;
        i2c_buf.length = 2; //
        i2c_buf.pbuffer = tmp;
    } else if (mode == CAT_START_WRITE) {//��ʾ����д���ַд��EEROM��
        i2c_buf.address = CAT_NOW_ADD + 2;
        i2c_buf.length = 2; //        
        i2c_buf.pbuffer = tmp + 2;
    } else {
        i2c_buf.address = CAT_NOW_ADD; //����ȫ��
        i2c_buf.length = 4; //        
        i2c_buf.pbuffer = tmp;
    }
    i2c_buf.flag.F_IsSelectiveMode = 1;
    i2c_buf.flag.F_WriteOrRead = 0;
    i2c_buf.flag.F_Is16bitsDevice = 1;
    i2c1_state = S_MASTER_IDLE;
    //    while (IFS1bits.MI2C1IF);
    IFS1bits.MI2C1IF = 1; //��ʼI2CͨѶ
    while (i2c1_state != S_MASTER_SEND_STOP) //�ȴ�������ɣ������ظ���������
        if (i2c1_state == S_MASTER_Fail) {
            CAT_WP = 1; //����
            return; //��ʾ������Ϣ
        }
    //�ȴ����ݷ�����ɻ��������쳣
    Delay1ms(1);
    CAT_WP = 1; //����
}

//void Get
