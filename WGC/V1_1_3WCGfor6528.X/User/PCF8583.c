#include <PCF8583.h>
#include <I2C.h>
#include "Common.h"

#define PCF_ADD 0xA2//���õ�ַ
#define PCF_CON_STA 0x00//PCF8583�Ŀ���״̬�Ĵ���

//typedef enum {
//    con = 0, /* sec_100 = 1, sec = 2, min = 3, hours = 4, year = 5, months = 6, */timer = 7,
//    alarm_con = 8, alarm_reg = 9
//} PCF_Reg;

void PCF8583_Init(void) {
    TRISBbits.TRISB13 = 1; //�ⲿRTCC�����ж�����Ϊ����

}

void PCF8583_SetTime(uint32_t* timestamp) {//ʱ�����λ��1s������ʱ�䵥λ��2s
    struct tm time_tmp;
    time_tmp = *gmtime((time_t*) timestamp);
    uint8_t tmp[8] = {0x85, 00}; // 05
    tmp[2] = DCH(time_tmp.tm_sec);
    tmp[3] = DCH(time_tmp.tm_min);
    tmp[4] = DCH(time_tmp.tm_hour) & 0x3F;
    tmp[5] = (GetMod(time_tmp.tm_year + 1900, 2) << 6) + (DCH(time_tmp.tm_mday) & 0x3F);
    tmp[6] = (DCH(time_tmp.tm_wday) << 5)+(DCH(time_tmp.tm_mon + 1) & 0x1F); //ע��tm�ṹ�����ݣ�1�·ݱ�ʾ0
    tmp[7] = 0; //���ö�ʱ��
    //    tmp[8] = 0xB0; //0x90; //���ñ���������
    //    tmp[9] = 00; //�����ٷ���
    //    tmp[10] = 4; //GetMod(alarmtime, 30); //������
    //    tmp[11] = 0; //GetMod(alarmtime / 30, 60); //��������
    //    tmp[12] = 0; //GetMod(alarmtime / 1800, 60); //����Сʱ
    //    tmp[13] = tmp[14] = 0; //�������ں��·�=0
    //    uint8_t tmp1[4] = {CAT_ADD, 0x00, 0x00, 0x00};    
    i2c1_state = S_MASTER_IDLE;//123
    i2c_buf.operatcode = PCF_ADD;
    i2c_buf.address = PCF_CON_STA;
    i2c_buf.length = sizeof (tmp) / sizeof (uint8_t);
    i2c_buf.pbuffer = tmp;
    i2c_buf.flag.F_IsSelectiveMode = 1;
    i2c_buf.flag.F_WriteOrRead = 0;
    i2c_buf.flag.F_Is16bitsDevice = 0;
    IFS1bits.MI2C1IF = 1;

    while (i2c1_state != S_MASTER_Finish); //�ȴ�������ɣ������ظ���������
    //    while (IFS1bits.MI2C1IF);
    //    while (i2c1_state != S_MASTER_IDLE);
}

void PCF8583_SetAlarmTime(struct tm alarmtime) {
    uint8_t tmp[7] = {0x90, 00}; //����cat24c512 ��ַ0xA8д������ַ 05
    //    tmp[8] = 0xB0; //0x90; //���ñ���������
    //    tmp[9] = 00; //�����ٷ���
    tmp[2] = DCH(alarmtime.tm_sec); //GetMod(alarmtime, 30); //������
    tmp[3] = DCH(alarmtime.tm_min); //GetMod(alarmtime / 30, 60); //��������
    tmp[4] = DCH(alarmtime.tm_hour); //GetMod(alarmtime / 1800, 60); //����Сʱ
    tmp[5] = tmp[6] = 0; //�������ں��·�=0
    //    uint8_t tmp1[4] = {CAT_ADD, 0x00, 0x00, 0x00};
    i2c_buf.operatcode = PCF_ADD;
    i2c_buf.address = PCF_CON_STA + 8;
    i2c_buf.length = sizeof (tmp) / sizeof (uint8_t);
    i2c_buf.pbuffer = tmp;
    i2c_buf.flag.F_IsSelectiveMode = 1;
    i2c_buf.flag.F_WriteOrRead = 0;
    i2c_buf.flag.F_Is16bitsDevice = 0;
    i2c1_state = S_MASTER_IDLE;
    IFS1bits.MI2C1IF = 1;

    while (i2c1_state != S_MASTER_Finish); //�ȴ�������ɣ������ظ���������
}

uint32_t PCF8583_ReadTime(void) {
    struct tm time_tmp; //timestamp

    uint8_t tmp[5] = {0x03, 00}; //����cat24c512 ��ַ0xA8д������ַ 
    i2c_buf.operatcode = PCF_ADD;
    i2c_buf.address = PCF_CON_STA + 2; //���뿪ʼ��ȡ
    i2c_buf.length = sizeof (tmp) / sizeof (uint8_t);
    i2c_buf.pbuffer = tmp;
    i2c_buf.flag.F_IsSelectiveMode = 1;
    i2c_buf.flag.F_WriteOrRead = 1;
    i2c_buf.flag.F_Is16bitsDevice = 0;
    i2c1_state = S_MASTER_IDLE;
    IFS1bits.MI2C1IF = 1;
    while (i2c1_state != S_MASTER_Finish); //�ȴ�������ɣ������ظ���������

    time_tmp.tm_sec = HCD(tmp[0]); //��
    time_tmp.tm_min = HCD(tmp[1]); //��
    time_tmp.tm_hour = HCD(tmp[2]&0x3F); //Сʱ
    time_tmp.tm_mday = HCD(tmp[3]&0x3F); //��
    time_tmp.tm_mon = HCD(tmp[4]&0x1F) - 1; //��
    time_tmp.tm_year = (uint16_t) (tmp[3] >> 6) + 2016 - 1900; //ע���Ƿ���Ҫ������ݼ�2016�����������E2ROM

    return mktime(&time_tmp);
}

void PCF8583_SetStatusReg(uint8_t reg) {//����
    //    uint8_t tmp = 0x05; //��ʼ��ʱ 05
    i2c_buf.operatcode = PCF_ADD;
    i2c_buf.address = PCF_CON_STA;
    i2c_buf.length = 1;
    i2c_buf.pbuffer = &reg;
    i2c_buf.flag.F_IsSelectiveMode = 1;
    i2c_buf.flag.F_WriteOrRead = 0;
    i2c_buf.flag.F_Is16bitsDevice = 0;
    i2c1_state = S_MASTER_IDLE;
    IFS1bits.MI2C1IF = 1;
    while (i2c1_state != S_MASTER_Finish); //�ȴ�������ɣ������ظ���������
}

void PCF8583_ReadStatus(uint8_t *tmp) {
    //    struct tm time_tmp; //timestamp

    //    uint8_t tmp[16] = {0x03, 00}; //����cat24c512 ��ַ0xA8д������ַ 
    i2c_buf.operatcode = PCF_ADD;
    i2c_buf.address = PCF_CON_STA; //���뿪ʼ��ȡ
    i2c_buf.length = 16;
    i2c_buf.pbuffer = tmp;
    i2c_buf.flag.F_IsSelectiveMode = 1;
    i2c_buf.flag.F_WriteOrRead = 1;
    i2c_buf.flag.F_Is16bitsDevice = 0;
    i2c1_state = S_MASTER_IDLE;
    IFS1bits.MI2C1IF = 1;
    while (i2c1_state != S_MASTER_Finish); //�ȴ�������ɣ������ظ���������

    //    time_tmp.tm_sec = HCD(tmp[0]); //��
    //    time_tmp.tm_min = HCD(tmp[1]); //��
    //    time_tmp.tm_hour = HCD(tmp[2]&0x3F); //Сʱ
    //    time_tmp.tm_mday = HCD(tmp[3]&0x3F); //��
    //    time_tmp.tm_mon = HCD(tmp[4]&0x1F) - 1; //��
    //    time_tmp.tm_year = (uint16_t) (tmp[3] >> 6) + 2016 - 1900; //ע���Ƿ���Ҫ������ݼ�2016�����������E2ROM

    //    return mktime(&time_tmp);
}

//void PCF8583_CelarFlag(void) {
//    uint8_t tmp = 0x05; //��ʼ��ʱ 05
//    i2c_buf.operatcode = PCF_ADD;
//    i2c_buf.address = PCF_CON_STA;
//    i2c_buf.length = 1;
//    i2c_buf.pbuffer = &tmp;
//    i2c_buf.flag.F_IsSelectiveMode = 1;
//    i2c_buf.flag.F_WriteOrRead = 0;
//    i2c_buf.flag.F_Is16bitsDevice = 0;
//    i2c1_state = S_MASTER_IDLE;
//    IFS1bits.MI2C1IF = 1;
//    while (i2c1_state != S_MASTER_Finish); //�ȴ�������ɣ������ظ���������
//}


