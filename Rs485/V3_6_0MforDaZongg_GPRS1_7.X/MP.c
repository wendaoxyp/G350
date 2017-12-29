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

vu32 gPulseTime = 0; //输入捕获数据2 单位：ms
vu32 gPulseCount = 0; //脉冲累加量
static u8 gOverFlag = 0;
u8 mi_SSP[3] = {1, 10, 100};
static u8 Read13[] = {
    0xCC, 0x02, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0x00, 0xEE
};
static uint8_t TX13Head[3] = {0xCC, 0x02, 0x30};
//static u8 Register1[REG1_BYTES];

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
static void Get_Q(const unsigned long nowPulse, float *f) {
    u8 tmp = 0;
    u32 pulse_time = gPulseTime; //捕获时间 避免除法的时候更新设备
    gPulseTime = 0; //清除上次数据
    Register2Read(&tmp, REG2_Arg_Postion[mi_arg2], 1); //ssp=
    if (tmp > 2) tmp = 0;
    if (!pulse_time)//如果获取到的时间为0的话，
        *f = 0;
    else {
        if (nowPulse < 2) {//如果脉冲数是小于2的话
            *f = (gOverFlag) ? (1.0 * mi_SSP[tmp] * 360000 / pulse_time) : 0; //1*0.1[ssp]/(pulse_time/(3600*1000))
        } else {
            *f = 1.0 * mi_SSP[tmp] * 360000 / pulse_time;
        }
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
        Register2Read(&tmp1, REG2_Arg_Postion[mi_arg2], 1);
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

void SaveSampleData(u8*dat) {
    u16 OffsetAdd1 = gOffsetAdd * REG1_BYTES; //统一使用偏移量

    *(dat + mp_sumcheck) = Sum_Check(dat, REG1_BYTES - 1); //计算校验和
    FM25L64B_Write(OffsetAdd1, dat, REG1_BYTES); //获取时间1 注意主要是使用SPI中断写参数，避免数据错误

    FM25L64B_Write(DataPacket_ID, &gOffsetAdd, 1); //写入数据包序号
    gOffsetAdd += 1; //数据包序号+1  
    gOffsetAdd = gOffsetAdd % DataPacketNum; //一个环数据为252 12*21; 
}

/*************************************
Function: GetValueTask
Description: 获取MP中工况瞬间量和工况总量
Input: 无
Output: 无
 *************************************/
void GetValueTask(u8 InputSource) {
    u8 tmp_reg1[REG1_BYTES]; //用于存放采集的数据
    u8 tmp_reg3[REG3_BYTES]; //用于存放发送数据
    float Qm_f = 0, Vbat_f = 0; //定义瞬间量、电压量
    float Vm_f[2] = {0, 0}; //总量的高8位和低8位

    ClearDat(tmp_reg1, 0, REG1_BYTES); //清空数据
    if (PulseIsOver() && !gOverFlag) gOverFlag = 1; //判断脉冲数量是否有溢出归零的情况    
    Get_Q(gPulseCount, &Qm_f); //计算秒冲瞬间量，保存到Qm_f变量中
    if (Qm_f > 50) Qm_f = 0; //如果脉冲的数量大于50的话，说明数据有误
    Get_V(gPulseCount, Vm_f); //清除定时器数值，避免没有脉冲是显示脉冲工况瞬间量
    GetMuilVoltage(&Vbat_f); //采集电压值
    
    RTCReadTime(tmp_reg3 + sb_time); //获取时间至发送缓冲区reg3buffer1中
    CopyDat(tmp_reg1 + mp_time, tmp_reg3 + sb_time, 7); //赋值数据到保存数据的reg1中

    FloatToChar(&Qm_f, tmp_reg3 + sb_Qm); //获取工况瞬间量至发送缓冲区reg3buffer1中
    CopyDat(tmp_reg1 + mp_Qm, tmp_reg3 + sb_Qm, 4); //复制数据到保存数据的reg1中

    FloatToChar(Vm_f, tmp_reg3 + sb_Vm); //获取工况总量至发送缓冲区reg3buffer1中
    FloatToChar(Vm_f + 1, tmp_reg3 + sb_Vm + 4);
    CopyDat(tmp_reg1 + mp_Vm, tmp_reg3 + sb_Vm, 8);

    FloatToChar(&Vbat_f, tmp_reg3 + sb_Vbat); //获取电池电压至发送缓冲区reg3buffer1中
    CopyDat(tmp_reg1 + mp_Vbat, tmp_reg3 + sb_Vbat, 4);
    switch (InputSource) {
        case SampleData:
        {
            tmp_reg1[mp_status] = SampleData; //添加数据值报警位，表示该数据为正常数据
            EnRegister1(REG3_BUF1, tmp_reg3);
            break;
        }
        case LowPowerData:
        {
            tmp_reg1[mp_status] = LowPowerData; //添加数据值报警位，表示该数据为现场采集一次的数据        
            EnRegister1(REG3_BUF2, tmp_reg3);
            break;
        }
        case TestData:
        {
            tmp_reg1[mp_status] = TestData; //添加数据值报警位，表示该数据为测试的数据
            EnRegister1(REG3_BUF2, tmp_reg3);
            break;
        }
        default:break;
    }
    SaveSampleData(tmp_reg1); //见数据写入FROM中
}

/*************************************
Function: PacketData2A2
Description: 选择指定的通道打包成A2
Input: 指定铁电通道（0-12） dat 输出A2协议包，REG3Buf 采集到的数据
Output:无
02 03 18 41 10 00 00 40 F0 FC 46 00 00 00 00 00 00 00 00 41 A0 00 00 42 CA A6 00 BA A2
 **************************************/
void PacketData2A2(u8 *dat, u8*REG3Buf) {
    u16 CRCtmp;

    Register2Read(dat, REG2_Arg_Postion[mi_add], 1); //设备地址  
    *(dat + A2_ID) = 0x03; //功能码    
    *(dat + A2_Bytes) = UDP_A2_LENGTH - 5; //字节数 减去功能码 地址 CRC校验2位- 自身1位    
    ClearDat(dat + A2_Vb, 0, 8); //标况总量
    ClearDat(dat + A2_Qb, 0, 4); //标况瞬间量
    CopyDat(dat + A2_Vm, REG3Buf + sb_Vm, 8); //工况总量
    CopyDat(dat + A2_Qm, REG3Buf + sb_Qm, 4); //工况瞬间量
    ClearDat(dat + A2_T, 0, 4); //温度
    ClearDat(dat + A2_P, 0, 4); //压力
    *(dat + A2_Sta) = 0; //清楚报警值
    if (FLagArgbits.LowPoweralarmFlag) //设备状态
        *(dat + A2_Sta) |= (1 << 4); //置一
    else
        *(dat + A2_Sta) &= ~(1 << 4); //清零
//    if (FLagArgbits.TestOnlieFlag) //设备状态
//        *(dat + A2_Sta) |= (1 << 5); //置一
//    else
//        *(dat + A2_Sta) &= ~(1 << 5); //清零
    CopyDat(dat + A2_Vbat, REG3Buf + sb_Vbat, 4); //电压值

    CRCtmp = CRC16_Check(dat, UDP_A2_LENGTH - 2); //CRC校验
    *(dat + A2_CRC16) = (u8) (CRCtmp & 0x00FF);
    *(dat + A2_CRC16 + 1) = (u8) (CRCtmp >> 8);
}

/************************************连接修正仪*********************************/
bool TX13IsOK(u8 *output) {
    uint8_t cnt = 0;
    uint8_t tmp[50] = {0, 0, 0};
    do {
        RS485SendString(Read13, 20); //发送1.3协议数据获取采集数据
        Delay100ms(1);
        if (cnt++ > 3)
            return false;
    } while (!UARTIsGet(BufferRead_UART1, tmp, 46, TX13Head, 3));
    CopyDat(output, tmp, 46);

    return true;
}


