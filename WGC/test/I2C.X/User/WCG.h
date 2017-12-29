#ifndef WCG_H
#define WCG_H

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <string.h>

/*
 * 3	0x02	�������	       82	���������������ʽ
            IP��ַ	      [20]	20�ֽ�ASCII��������0(˳��)
            �˿�           [2]  2�ֽ�С�˸�ʽ
            APN	          [20]	20�ֽ�ASCII��������0(˳��)
            APN�����û���  [20]	20�ֽ�ASCII��������0(˳��)
            APN��������	  [20]	20�ֽ�ASCII��������0(˳��)
 */
struct NET_ARG {
    uint8_t IP_Addr[20];
    uint16_t Port;
    uint8_t APN[20];
    uint8_t APN_User[20];
    uint8_t APN_Password[20];
};

/*
6	0x05	ѹ����������ز���	20
            �Ǳ�87������ѹ��ֵ	[4]
            �Ǳ�88������ѹ��ֵ	[4]
            ѹ����������ֵ       [4]
            ѹ����������ֵ       [4]
            ѹ��ͻ�����ı�ֵ	[4]
note:1��С�˸�ʽ
2��ѹ����λΪ������������ֵΪʵ��ֵ*1000��
�磺40060000 =1.6MPa��
3��ȫ���ʾ��Ч

 */
struct PRESSURE_TRANSMITTER_ARG {
    float P_87_full_scale;
    float P_88_full_scale;
    float P_upper_limit;
    float P_lower_limit;
    float P_Max_of_Mutations;
};

/*
 7	0x06	�ϱ����ʱ�����ʼʱ��	4	�������ϱ����ʱ�����ʼʱ���ʽ
            �ϱ����ʱ��            [2]	С�˸�ʽ����λСʱ
            �ϱ���ʼʱ��-Сʱ       [1]	
            �ϱ���ʼʱ��-��         [1]	
 */
struct SEND_TIME_AND_START_TIME {
    uint16_t Send_time;
    uint8_t Start_time_hour;
    uint8_t Start_time_minutes;
};

/*8	0x07	��׶�	6	�����õ׶ȸ�ʽ
            ͨ����	[1]	
            �׶�    [5]	 �׶����ݵ�1�ֽ�ΪС������(��Χ0-9)����4�ֽ�Ϊ��������(���ֽ���ǰ)
 */
struct SET_MINUENT {
    uint8_t Channel_number;
    uint8_t Minuent[5];
};

/*
 9	0x08	������һ����������	7	�������������͸�ʽ
        ��ʼ����	[1]	
        ��ʼСʱ	[1]	
        ��ʼ����	[1]	
        �������	[1]	0��ʾ�������λ���£�
                    1��ʾ�գ�
                    2��ʾʱ��
                    3��ʾ��
        �����	[1]	
        �Ƿ񰴱��ַλ��������	[1]	00 - ��01 - ��
        ���ַβ�����ߵ�ʱ����	[1]	��λ������
 */
struct OTHER_ONLINE_ARG {
    uint8_t Start_day;
    uint8_t Start_hour;
    uint8_t Start_minutes;
    uint8_t Serial_interval_Type;
    uint8_t Serial_interval_Num;
    uint8_t Is_send_by_addr;
    uint8_t Send_serial_interval_by_addr;
};

/*
10	0xFF	�豸ID��	5	
            ID��	[2]	0000-0xFFFF
            �ͺ�	[2]	�̶�����W������G��
            �ͻ�ID��	[1]	 
 */
struct WGC_ID {
    uint16_t Producer_id;
    uint16_t Producer_name;
    uint8_t client_id;
};

struct WGC_ARG {
    uint8_t Sample_Time;
    uint8_t Send_Time[24];
    struct NET_ARG Net_arg;
    uint8_t Channel_arg[8];
    uint8_t Pulse_arg[6];
    struct PRESSURE_TRANSMITTER_ARG PT_arg;
    struct SEND_TIME_AND_START_TIME SST_arg;
    struct SET_MINUENT Set_minute;
    struct OTHER_ONLINE_ARG Other_onlie_arg;
    struct WGC_ID WCG_id;
};

extern void WGC_Get_Arg(struct WGC_ARG *tmp_arg);
#endif


