#ifndef WCG_H
#define WCG_H

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <string.h>

/*
 * 3	0x02	网络参数	       82	见设置网络参数格式
            IP地址	      [20]	20字节ASCII，不足填0(顺序)
            端口           [2]  2字节小端格式
            APN	          [20]	20字节ASCII，不足填0(顺序)
            APN访问用户名  [20]	20字节ASCII，不足填0(顺序)
            APN访问密码	  [20]	20字节ASCII，不足填0(顺序)
 */
struct NET_ARG {
    uint8_t IP_Addr[20];
    uint16_t Port;
    uint8_t APN[20];
    uint8_t APN_User[20];
    uint8_t APN_Password[20];
};

/*
6	0x05	压力变送器相关参数	20
            仪表87满量程压力值	[4]
            仪表88满量程压力值	[4]
            压力上限数据值       [4]
            压力下限数据值       [4]
            压力突变最大改变值	[4]
note:1、小端格式
2、压力单位为兆帕，该数据值为实际值*1000，
如：40060000 =1.6MPa。
3、全零表示无效

 */
struct PRESSURE_TRANSMITTER_ARG {
    float P_87_full_scale;
    float P_88_full_scale;
    float P_upper_limit;
    float P_lower_limit;
    float P_Max_of_Mutations;
};

/*
 7	0x06	上报间隔时间和起始时间	4	见设置上报间隔时间和起始时间格式
            上报间隔时间            [2]	小端格式，单位小时
            上报起始时间-小时       [1]	
            上报起始时间-分         [1]	
 */
struct SEND_TIME_AND_START_TIME {
    uint16_t Send_time;
    uint8_t Start_time_hour;
    uint8_t Start_time_minutes;
};

/*8	0x07	设底度	6	见设置底度格式
            通道号	[1]	
            底度    [5]	 底度数据第1字节为小数部分(范围0-9)，后4字节为整数部分(低字节在前)
 */
struct SET_MINUENT {
    uint8_t Channel_number;
    uint8_t Minuent[5];
};

/*
 9	0x08	设置另一种上线类型	7	见设置上线类型格式
        起始日期	[1]	
        起始小时	[1]	
        起始分钟	[1]	
        间隔类型	[1]	0表示间隔数单位是月，
                    1表示日，
                    2表示时，
                    3表示分
        间隔数	[1]	
        是否按表地址位数错开上线	[1]	00 - 否，01 - 是
        表地址尾数上线的时间间隔	[1]	单位：分钟
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
10	0xFF	设备ID号	5	
            ID号	[2]	0000-0xFFFF
            型号	[2]	固定：’W’、’G’
            客户ID号	[1]	 
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


