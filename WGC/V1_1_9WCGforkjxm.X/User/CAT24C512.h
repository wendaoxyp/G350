#ifndef CAT24C512_H 
#define CAT24C512_H
#include <p24FJ64GA306.h>
//#include <stdint.h>
#include <stdio.h>
#include <i2c.h>
//ȡֵ��Χ0x0000-0xffff 512kb

#define CAT_ADD 0xA8
#define CAT_WP_TRIS TRISBbits.TRISB12
#define CAT_WP_LAT LATBbits.LATB12

#define CAT_NUMS 5461//65536=12*5461+4
#define CAT_NOW_ADD 0xFFFC//c d CAT_StartID; e f CAT_OperatID
//ȡֵ��Χ0x0000-0xffff 512kb
#define BufferSize 12//40//һ��ɼ����ݵ��ֽ�
//#define CAT_START 5
#define CAT_START_READ 2
#define CAT_START_WRITE 3

extern uint16_t CAT_OperatID;
extern uint16_t CAT_StartID;

extern void CAT24C512_Init(void);
extern void CAT24C512_Read(uint16_t id, uint8_t *tmp);
extern void CAT24C512_Write(uint8_t * tmp);

#endif

//���д����ȷ�ԣ�д�����ݲ���ȡ����д����������Աȣ������ͬ����д��ɹ�����֮�����²���3�Σ���ȡ����������ǲ���ͬ�Ļ�������ʾ����
//��Ӷ�ȡ��ȷ�ԣ���ȡ�������Σ��������ͬ���¶�ȡ���ظ�3�Σ�������ǲ���ͬ������ʾ����
