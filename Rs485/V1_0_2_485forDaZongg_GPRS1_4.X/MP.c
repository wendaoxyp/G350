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
#include "Status.h"
//#include "Queue.h"

#define PULSE_MAX 100000000 

vu32 gPulseTime = 0; //输入捕获数据2 单位：ms
vu32 gPulseCount = 0; //脉冲累加量
static u8 gOverFlag = 0;
u8 mi_SSP[3] = {1, 10, 100};
static u8 Read13[20] = {
    0xCC, 0x02, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0x00, 0xEE
};
static uint8_t TX13Head[3] = {0xCC, 0x02, 0x30};
//static u8 Register1[REG1_BYTES];
u8 AlarmType; //用于确定报警类型
/*************************************
Function: PulseIsOver 
Description: 脉冲数是否溢出
Input: 无
Output: 无
 *************************************/
//static bool PulseIsOver(void) {
//    bool b = false;
//    while (gPulseCount >= PULSE_MAX) {
//        gPulseCount -= PULSE_MAX; //归零
//        b = true;
//    }
//    return b;
//}

/*************************************
Function: Get_Q
Description: 获取瞬间量
Input: 无
Output: 无
 *************************************/
//static void Get_Q(const unsigned long nowPulse, float *f) {
//    u8 tmp = 0;
//    u32 pulse_time = gPulseTime; //捕获时间 避免除法的时候更新设备
//    gPulseTime = 0; //清除上次数据
//    Register2Read(&tmp, REG2_Arg_Postion[reg2_mi_arg2], 1); //ssp=
//    if (tmp > 2) tmp = 0;
//    if (!pulse_time)//如果获取到的时间为0的话，
//        *f = 0;
//    else {
//        if (nowPulse < 2) {//如果脉冲数是小于2的话
//            *f = (gOverFlag) ? (1.0 * mi_SSP[tmp] * 360000 / pulse_time) : 0; //1*0.1[ssp]/(pulse_time/(3600*1000))
//        } else {
//            *f = 1.0 * mi_SSP[tmp] * 360000 / pulse_time;
//        }
//    }
//}

/*************************************
Function: Get_V 
Description: 获取总量
Input: 无
Output: 无
 *************************************/
//static void Get_V(const unsigned long nowPulse, float*tmp) {
//    //float tmp[2];
//    if (nowPulse != 0) {
//        u8 tmp1 = 0;
//        Register2Read(&tmp1, REG2_Arg_Postion[reg2_mi_arg2], 1);
//        if (tmp1 > 2)tmp1 = 0;
//        switch (mi_SSP[tmp1]) {
//            case 1://SSP=0.1
//            {
//                *tmp = floor(nowPulse / 10 / 10000); //初始值为124889  =1
//                *(tmp + 1) = nowPulse % 100000 * 1.0 / 10; //  =2488.9
//                break;
//            }
//            case 10:
//            {
//                *tmp = floor(nowPulse / 10000);
//                *(tmp + 1) = nowPulse % 10000;
//                break;
//            }
//            case 100:
//            {
//                *tmp = floor(nowPulse * 10 / 10000);
//                *(tmp + 1) = nowPulse * 10 % 10000;
//                break;
//            }
//        }
//    } else
//        *tmp = *(tmp + 1) = 0;
//}

void SaveSampleData(u8*dat) {
    u16 OffsetAdd1 = gOffsetAdd * REG1_BYTES; //统一使用偏移量

    *(dat + mp_sumcheck) = Sum_Check256(dat, REG1_BYTES - 1); //计算校验和
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
bool GetValueTask(u8 InputSource) {
    u8 tmp_reg1[REG1_BYTES]; //用于存放采集的数据        
    u8 tmp_reg3[REG3_BYTES]; //用于存放发送数据
    u8 tmp[50]; //用于接受仪表端的数据
    u8 cnt, cnt1 = 0; //循环次数
    bool Is_Get = true; //判断是否获取到数据
    u16 check_sum = 0; //校验和
    float f_tmp = 0; //临时变量
    double d_tmp = 0; //

    ClearDat(tmp_reg1, 0, REG1_BYTES); //清空数据
    TX13Head[1] = miotArgs.mp_add; //获取帧头中的地址数据
    check_sum = Sum_Check(Read13, 17); //前17个数字的校验码
    Read13[17] = (u8) (check_sum & 0x00ff);
    Read13[18] = (u8) (check_sum >> 8); //赋值校验吗
    LATAbits.LATA2 = 1; //使能485通讯电源
    do {
        RS485SendString(Read13, 20); //发送1.3协议数据获取采集数据 20个字节
        Delay100ms(2);
        if (cnt++ > 9) {
            Is_Get = false;
            break;
        }//CC 08 30 1C 00 20 06 06 05 16 16 44 05 7B 86 80 00 00 0E 45 98 01 05 50 00 00 07 65 03 00 AA 5E 80 79 06 EE
        for (cnt1 = 0; cnt1 < 4; cnt1++)//串口最后四个字节没有接受到，中断原因
            if (U1STAbits.URXDA == 1) //没有接收到
                BufferWrite_UART1();
    } while (!UARTIsGet(BufferRead_UART1, tmp, REG1_BYTES, TX13Head, 3)); //将接收到的数据存在REG1大小的数组中
    LATAbits.LATA2 = 0; //失能485通讯电源
    if (Is_Get) {
        //计算采集时间
        GetUnixTime_Char(tmp + 5, tmp_reg3 + reg3_timestamp);
        //        CopyDat(tmp + 5, tmp_reg3 + reg3_timestamp, 7); //将采集到的时间赋值数据到保存数据的reg1中
        //标况累积总量V1_acc //将13协议的数据转化为IEEE745浮点数 
        TX2Float(&f_tmp, tmp + 18);
        d_tmp = 2000000 * ((*(tmp + 16) << 8)+ *(tmp + 17)) + (double) f_tmp;
        if (d_tmp >= 1000000) //test
        {
            f_tmp = d_tmp / 1000000;
            FloatToChar(&f_tmp, tmp_reg3 + reg3_Vb);
            d_tmp -= f_tmp * 1000000;
        } else
            ClearDat(tmp_reg3 + reg3_Vb, 0, 4);
        f_tmp = d_tmp;
        FloatToChar(&f_tmp, tmp_reg3 + reg3_Vb + 4);

        //标况瞬时流量V1_ins 
        TX2Float(&f_tmp, tmp + 12);
        FloatToChar(&f_tmp, tmp_reg3 + reg3_Qb);

        //温度
        TX2Float(&f_tmp, tmp + 22);
        FloatToChar(&f_tmp, tmp_reg3 + reg3_T);
        if (InputSource == AlarmData) {
            if (f_tmp < miotArgs.AlarmLT)//添加报警功能
                AlarmType = 2;
            else if (f_tmp > miotArgs.AlarmHT)
                AlarmType = 1;
        }
        //压力
        TX2Float(&f_tmp, tmp + 26);
        FloatToChar(&f_tmp, tmp_reg3 + reg3_P);
        if (InputSource == AlarmData) {
            if (f_tmp < miotArgs.AlarmLP)
                AlarmType = 4;
            else if (f_tmp > miotArgs.AlarmHP)
                AlarmType = 3;
        }
        //状态字
        tmp_reg3[reg3_sta] = tmp[32];
        //电池电压
        GetMuilVoltage(&gGetVoltage); //采集电压值
        FloatToChar(&gGetVoltage, tmp_reg3 + reg3_Vbat);

        //将待发送值服务器的数据保存至铁电
        CopyDat(tmp_reg1 + mp_time, tmp + 5, 7); //时间        
        ClearDat(tmp_reg1 + mp_Qb, 0, 4); //标况瞬间量
        ClearDat(tmp_reg1 + mp_Vb, 0, 8); //标况总量
        CopyDat(tmp_reg1 + mp_Qb, tmp_reg3 + reg3_Qb, 4); //工况瞬间量
        CopyDat(tmp_reg1 + mp_Vb, tmp_reg3 + reg3_Vb, 8); //工况总量
        CopyDat(tmp_reg1 + mp_T, tmp_reg3 + reg3_T, 4); //温度
        CopyDat(tmp_reg1 + mp_P, tmp_reg3 + reg3_P, 4); //压力
        CopyDat(tmp_reg1 + mp_Vbat, tmp_reg3 + reg3_Vbat, 4); //电压值
        CopyDat(tmp_reg1 + mp_status, tmp_reg3 + reg3_sta, 1); //状态字
        CopyDat(tmp_reg1 + mp_alarm, tmp + 30, 1); //报警字
        EnRegister1(InputSource, tmp_reg3); //将采集的数据写入发送通道中
        SaveSampleData(tmp_reg1); //见数据写入FROM中
    } //else {//发送错误代码
    Statusbits.staGPRS = (Is_Get) ? MP_GetData_OK : MP_GetData_Fail; //与修正仪通讯失败
    //}
    return Is_Get;
}

/*************************************
Function: PacketData2A2
Description: 选择指定的通道打包成A2
Input: 指定铁电通道（0-12） dat 输出A2协议包，REG3Buf 采集到的数据
Output:无
02 03 18 41 10 00 00 40 F0 FC 46 00 00 00 00 00 00 00 00 41 A0 00 00 42 CA A6 00 BA A2
 **************************************/
void PacketData2A2(u8 *A2Dat, u8*REG3Buf) {
    u16 CRCtmp;
    *(A2Dat + A2_Add) = miotArgs.mi_add; //设备地址  
    *(A2Dat + A2_ID) = 0x03; //功能码    
    *(A2Dat + A2_Bytes) = UDP_A2_LENGTH - 5; //字节数 减去功能码 地址 CRC校验2位- 自身1位    
    ClearDat(A2Dat + A2_Vm, 0, 8); //标况总量
    ClearDat(A2Dat + A2_Qm, 0, 4); //标况瞬间量
    CopyDat(A2Dat + A2_Vb, REG3Buf + reg3_Vb, 8); //工况总量
    CopyDat(A2Dat + A2_Qb, REG3Buf + reg3_Qb, 4); //工况瞬间量
    CopyDat(A2Dat + A2_T, REG3Buf + reg3_T, 4); //温度
    CopyDat(A2Dat + A2_P, REG3Buf + reg3_P, 4); //压力
    *(A2Dat + A2_Sta) = *(REG3Buf + reg3_sta); //清楚报警值
    //    if (FLagArgbits.LowPoweralarmFlag) //设备状态//A2里面没有报警值
    //        *(A2Dat + A2_Ala) |= (1 << 4); //置一
    //    else
    //        *(A2Dat + A2_Ala) &= ~(1 << 4); //清零
    //    if (FLagArgbits.TestOnlieFlag) //设备状态
    //        *(A2Dat + A2_Sta) |= (1 << 5); //置一
    //    else
    //        *(A2Dat + A2_Sta) &= ~(1 << 5); //清零
    CopyDat(A2Dat + A2_Vbat, REG3Buf + reg3_Vbat, 4); //电压值

    CRCtmp = CRC16_Check(A2Dat, UDP_A2_LENGTH - 2); //CRC校验
    *(A2Dat + A2_CRC16) = (u8) (CRCtmp & 0x00FF);
    *(A2Dat + A2_CRC16 + 1) = (u8) (CRCtmp >> 8);
}
//将获取到的数据转化为13协议

//void PacketData213(u8 *dat, u8*REG3Buf) {
//    *dat = 0xcc;
//    Register2Read(dat + 1, REG2_Arg_Postion[mi_add], 1); //设备地址  
//    *(dat + 2) = 0x03; //功能码    
//    *(dat + 3) = UDP_13_LENGTH - 6; //字节数 减去功能码 地址 CRC校验2位- 自身1位    
//    *(dat + 4) = 0;
//    CopyDat(dat + 5, REG3Buf, UDP_13_LENGTH - 6);
//    *(dat + 35) = 0xee;
//}



