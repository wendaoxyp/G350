#include "user.h"
#include "RS485.h"
#include "UART.h"
#include "Protocal.h"
#include "CheckData.h"
#include "TIM.h"
#include "Mp.h"
#include "P-Miot1601.h"
#include "SerialBuffer.h"
#include "math.h"
#include "Miot1601.h"
#include "Common.h"
//#include "Queue.h"

#define PULSE_MAX 100000000 
//extern QUEUE line; //创建队列
/*********************************模块与PC通讯的参数**********************************/
//vu32 gNowCapture = 0; //输入捕获数据2 单位：ms
//vu32 gPulseTOffset = 0; //脉冲时间偏移量
//vu32 gPulseCount = 0; //脉冲累加量
u8 gAlarmVoltageAdd;
u8 gOverFlag = 0;
static u8 mi_SSP[3] = {1, 10, 100};
/**********************************模块和设备通讯的参数****************************/

/*********************************函数声明**********************************/

/*************************************
Function: ClrData 
Description: 清除数据
Input: dat：数据地址 bytes：字节数
Output: 无
 *************************************/
void ClrData(u8 *dat, u8 bytes) {
    u8 count = 0;

    while (count < bytes) {
        *(dat + count) = 0;
        count++;
    }
}

/*************************************
Function: PulseIsOver 
Description: 脉冲数是否溢出
Input: 无
Output: 无
 *************************************/
static bool PulseIsOver(void) {
    bool b = false;
    while (gPulseCount >= PULSE_MAX) {
        gPulseCount -= PULSE_MAX; //归零
        b = true;
    }
    return b;
}

/*************************************
Function: Get_Q
Description: 获取瞬间量
Input: 无
Output: 无
 *************************************/
static float Get_Q(const unsigned long nowPulse) {
    u8 tmp = 0;
    u32 pulse_time = gNowCapture; //捕获时间 避免除法的时候更新设备
    gNowCapture = 0; //清除上次数据
    Register2Read(&tmp, mi_arg_add[mi_arg2], 1); //ssp=
    if (tmp > 2) tmp = 0;
    if (!pulse_time)
        return 0;
    if (nowPulse < 2) {
        return (gOverFlag) ? (1.0 * mi_SSP[tmp] * 360000 / pulse_time) : 0; //1*0.1[ssp]/(pulse_time/(3600*1000))
    } else {
        return 1.0 * mi_SSP[tmp] * 360000 / pulse_time;
    }
}

/*************************************
Function: Get_V 
Description: 获取总量
Input: 无
Output: 无
 *************************************/
static void Get_V(const unsigned long nowPulse, float*tmp) {
    //float tmp[2];
    if (nowPulse != 0) {
        u8 tmp1 = 0;
        Register2Read(&tmp1, mi_arg_add[mi_arg2], 1);
        if (tmp1 > 2)tmp1 = 0;
        switch (mi_SSP[tmp1]) {
            case 1://SSP=0.1
            {
                *tmp = floor(nowPulse / 10 / 10000); //初始值为124889  =1
                *(tmp + 1) = nowPulse % 100000 * 1.0 / 10; //  =2488.9
                break;
            }
            case 10:
            {
                *tmp = floor(nowPulse / 10000);
                *(tmp + 1) = nowPulse % 10000;
                break;
            }
            case 100:
            {
                *tmp = floor(nowPulse * 10 / 10000);
                *(tmp + 1) = nowPulse * 10 % 10000;
                break;
            }
        }
    } else
        *tmp = *(tmp + 1) = 0;
}

/*************************************
Function: GetValueTask
Description: 获取MP中工况瞬间量和工况总量
Input: 无
Output: 无
 *************************************/
void GetValueTask(void) {
    u8 tmp_ch[19]; //临时4为浮点数IEE745的字符
    float Qm_f; //瞬间量
    float Vm_f[2]; //总量的高8位和低8位
    u16 OffsetAdd1 = gOffsetAdd * REG_DATA_SECTION; //同意使用偏移量
    //计算工况数据
    if (PulseIsOver() && !gOverFlag)
        gOverFlag = 1;
    //    if (gNowCapture)
    Qm_f = Get_Q(gPulseCount);
    //    else
    //        Qm_f = 0;
    if (Qm_f > 50) Qm_f = 50;
    Get_V(gPulseCount, Vm_f);
    //    gNowCapture = 0; //清除定时器数值，避免没有脉冲是显示脉冲工况瞬间量
    //将数据写入队列中
    FloatToChar(&Qm_f, tmp_ch); //工况瞬间量
    FloatToChar(Vm_f, tmp_ch + 4); //工况总量1
    FloatToChar(Vm_f + 1, tmp_ch + 8); //工况总量2
    RTCReadTime(tmp_ch + 12); //7字节时间
    //    EnQueue(tmp_ch, &line);
    EnRegister1(tmp_ch);

    //写标况瞬间量  change
    FM25L64B_Write((mi_dat_add[mp_Qm] + OffsetAdd1), tmp_ch, 4);
    //获取工况总量转换字符串，并写入FRAM  
    FM25L64B_Write((mi_dat_add[mp_Vm] + OffsetAdd1), tmp_ch + 4, 4);
    FM25L64B_Write((mi_dat_add[mp_Vm] + OffsetAdd1 + 4), tmp_ch + 8, 4);
    //获取时间，并写入FRAM
    FM25L64B_Write((mi_dat_add[mp_time] + OffsetAdd1), tmp_ch + 12, 7);
    //赋值其他值
    tmp_ch[0] = tmp_ch[1] = tmp_ch[2] = tmp_ch[3] = 0;
    FM25L64B_Write(mi_dat_add[mp_T] + OffsetAdd1, tmp_ch, 4);
    FM25L64B_Write((mi_dat_add[mp_P] + OffsetAdd1), tmp_ch, 4);
    FM25L64B_Write((mi_dat_add[mp_Qb] + OffsetAdd1), tmp_ch, 4);
    FM25L64B_Write((mi_dat_add[mp_Vb] + OffsetAdd1), tmp_ch, 4);
    FM25L64B_Write((mi_dat_add[mp_Vb] + OffsetAdd1 + 4), tmp_ch, 4);

    FM25L64B_Write((mi_dat_add[mp_status] + OffsetAdd1), tmp_ch, 1);
    //    更新数据包数据
    FROM_WriteDPNum(); //更新数据包数据
}

/*************************************
Function: GetAlarmValue
Description: 获取MP中工况瞬间量和工况总量
Input: 无
Output: 无
 *************************************/
void GetAlarmValue(void) {
    u8 tmp_ch[19]; //临时4为浮点数IEE745的字符
    float Vm_f[2]; //总量的高8位和低8位
    u16 OffsetAdd1 = gOffsetAdd * REG_DATA_SECTION; //同意使用偏移量
    u16 length = 19 + UDP_A2_LENGTH, CRCtmp;
    u8 rtcc_tmp[7] = {0, 0, 0, 0, 0, 0, 0};
    u8 cnt; //用于循环
    for (cnt = 0; cnt < length; cnt++)//清除AlarmData数组数据
        *(AlarmData + cnt) = 0;
    //计算工况数据
    if (PulseIsOver() && !gOverFlag)
        gOverFlag = 1;
    Get_V(gPulseCount, Vm_f);
    //将数据写入队列中
    AlarmData[0] = 'A'; //A2帧头
    AlarmData[1] = '2';
    Register2Read(AlarmData + 2, mi_arg_add[mi_id], 8); //EID
    AlarmData[10] = (u8) (length >> 8); //数据总长15+A2+4
    AlarmData[11] = (u8) (length & 0x00FF);
    AlarmData[12] = 0; //数据类型 使用正常数据代替
    AlarmData[13] = 1; //赋值数据包个数
    RTCReadTime(rtcc_tmp); //7字节时间
    GetUnixTime_Char(rtcc_tmp, AlarmData + 14); //获取时间戳
    Register2Read(AlarmData + 18, mi_arg_add[mi_add], 1); //获取地址
    *(AlarmData + 19) = 0x03; //功能码
    //字节数 减去功能码 地址 CRC校验2位- 自身1位
    *(AlarmData + 20) = UDP_A2_LENGTH - 5;
    //标况总量+8 21-28
    //标况瞬间量+4 29-32
    //工况总量+8 33-40
    FloatToChar(Vm_f, AlarmData + 33); //工况总量1 +4
    FloatToChar(Vm_f + 1, AlarmData + 37); //工况总量2 +4
    //工况瞬间量+4 41-44
    //温度+4 45-48
    //压力+4 49-52
    //设备状态
    *(AlarmData + 53) = 0x10; //状态位 如果获取到的电压为
    *(AlarmData + 54) = 0x40; //状态位=1的话输出3.0V  
    *(AlarmData + 55) = 0x40;
    *(AlarmData + 56) = 0x00;
    *(AlarmData + 57) = 0x00;
    CRCtmp = CRC16_Check(AlarmData + 18, UDP_A2_LENGTH - 2); //CRC校验
    *(AlarmData + 58) = (u8) (CRCtmp & 0x00FF);
    *(AlarmData + 59) = (u8) (CRCtmp >> 8);
    *(AlarmData + 60) = Sum_Check(AlarmData, length);
    //写工况瞬间量  change
    //获取工况总量转换字符串，并写入FRAM  
    FM25L64B_Write((mi_dat_add[mp_Vm] + OffsetAdd1), AlarmData + 33, 4);
    FM25L64B_Write((mi_dat_add[mp_Vm] + OffsetAdd1 + 4), AlarmData + 37, 4);
    //获取时间，并写入FRAM
    FM25L64B_Write((mi_dat_add[mp_time] + OffsetAdd1), rtcc_tmp, 7);
    //赋值其他值
    tmp_ch[0] = tmp_ch[1] = tmp_ch[2] = tmp_ch[3] = 0;
    FM25L64B_Write(mi_dat_add[mp_T] + OffsetAdd1, tmp_ch, 4);
    FM25L64B_Write((mi_dat_add[mp_P] + OffsetAdd1), tmp_ch, 4);
    FM25L64B_Write((mi_dat_add[mp_Qb] + OffsetAdd1), tmp_ch, 4);
    FM25L64B_Write((mi_dat_add[mp_Vb] + OffsetAdd1), tmp_ch, 4);
    FM25L64B_Write((mi_dat_add[mp_Vb] + OffsetAdd1 + 4), tmp_ch, 4);
    FM25L64B_Write((mi_dat_add[mp_Qm] + OffsetAdd1), tmp_ch, 4);

    FM25L64B_Write((mi_dat_add[mp_status] + OffsetAdd1), tmp_ch, 1);
    //    更新数据包数据
    FROM_WriteDPNum(); //更新数据包数据
}


/*************************************
Function: PacketData2A2
Description: 选择指定的通道打包成A2
Input: 指定铁电通道（0-12） dat 输出A2协议包，dat1 采集到的数据
Output: A2的字符长度
 *************************************/
// 02 03 18 41 10 00 00 40 F0 FC 46 00 00 00 00 00 00 00 00 41 A0 00 00 42 CA A6 00 BA A2

void PacketData2A2(u8 *dat, u8*dat1) {
    u8 cnt;
    u16 CRCtmp;
    //设备地址
    Register2Read(dat, mi_arg_add[mi_add], 1);
    //功能码
    *(dat + 1) = 0x03;
    //字节数 减去功能码 地址 CRC校验2位- 自身1位
    *(dat + 2) = UDP_A2_LENGTH - 5;
    //标况总量
    for (cnt = 0; cnt < 8; cnt++)
        *(dat + 3 + cnt) = 0;
    //标况瞬间量
    for (cnt = 0; cnt < 4; cnt++)
        *(dat + 11 + cnt) = 0;
    //工况总量
    for (cnt = 0; cnt < 8; cnt++)
        *(dat + 15 + cnt) = *(dat1 + cnt + 4);
    //工况瞬间量
    for (cnt = 0; cnt < 4; cnt++)
        *(dat + 23 + cnt) = *(dat1 + cnt);
    //温度
    for (cnt = 0; cnt < 4; cnt++)
        *(dat + 27 + cnt) = 0;
    //压力
    for (cnt = 0; cnt < 4; cnt++)
        *(dat + 31 + cnt) = 0;
    //设备状态
    *(dat + 35) = (FLagArgbits.LowPowerFlag) << 4; //状态位 如果获取到的电压为
    if (*(dat + 35)) {//状态位=1的话输出3.0V  
        *(dat + 36) = 0x40;
        *(dat + 37) = 0x40;
        *(dat + 38) = 0x00;
        *(dat + 39) = 0x00;
    } else {//状态位=0的话输出3.6V  
        *(dat + 36) = 0x40;
        *(dat + 37) = 0x66;
        *(dat + 38) = 0x66;
        *(dat + 39) = 0x66;
    }
    CRCtmp = CRC16_Check(dat, UDP_A2_LENGTH - 2); //CRC校验
    *(dat + 40) = (u8) (CRCtmp & 0x00FF);
    *(dat + 41) = (u8) (CRCtmp >> 8);
}

