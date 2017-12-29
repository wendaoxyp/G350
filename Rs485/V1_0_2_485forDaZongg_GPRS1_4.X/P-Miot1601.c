/* 
 * File:   Miot1601.c
 * Author: TURONG62
 *
 * Created on 2016年8月17日, 下午4:48
 */
#include "user.h"
#include "P-Miot1601.h"
#include "GPRS.h"
#include "CheckData.h"
#include "TIM.h"
#include "SerialBuffer.h"
#include "Miot1601.h"
#include "math.h"
#include "Common.h"
#include "time.h"

//extern enum REG2_Add_enum enum_REG2_Add;
//extern enum REG1_Add_enum enum_REG1_Add;
//struct Alarm_Arg AlarmArgbits;
struct Status Statusbits;
//extern u8 bufferRptr_uart2;
//extern u8 bufferWptr_uart2;
//extern u8 Buffer_uart2[256];
extern const u8 ReadArg[14];
extern const u8 ArgRe[5];
extern const u8 Ver[5];
//static bool DUPDataChange(u8 *source_dat);
//static void TCP_02_Reply(u8 source);
static void TCP_03_Reply(u8 source, u8 start_ID, u8 nums);
//static void TCP_04_Reply(u16 reg_add, u8 arg_num, u8 source);
static void TCP_10_Reply(u16 reg_add, u8 arg_num, u8 source);
//static void TCP_11_Reply(u8* dat);
static void TCP_32_Reply(void);
static void TCP_33_Reply(u8* dat);
static void TCP_34_Reply(void);
static void TCP_43_Reply(void);
void TCP_Error_Relay(u8 code, u8 err, u8 source);
//u8 AlarmData[61]; //报警数据通道
//u8 TestData[61] = { 0x41,0x32,0x7F,0xF9,0x02,0x01,0x00,0x00,0x00,0x16,
//                    0x00,0x3D,0x00,0x01,0x80,0xF4,0xE6,0x58,0x08,0x03,
//                    0x25,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//                    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//                    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//                    0x00,0x00,0x00,0x00,0x40,0x66,0x66,0x66,0xE2,0x8C,0x04}; //报警数据通道

///*************************************
//Function: CopFun 
//Description: 选择通讯功能，如果通讯成功，进入TCP_XX_Reply,
//Input: 原始数据指针dat，数据类型source
//Output: 1
// *************************************/

u8 CopFun(u8*dat, u8 source) {//
    u16 CRC_Result = 0; //获取参数寄存器地址   
    u8 reg_add = 0, arg_num = 0; //BCD 参数数量  
    u8 add_base = 0;
    u8 tmp[REG2_BYTES + 10];
    //判断功能码GetMuiltSampDat = 0x02, GetSingleSampDat = 0x03, GetMIOTArg = 0x04, SetMIOTArg = 0x10, 
    //GetGPRSArg = 0x20, SetGPRSArg = 0x21, TestGPRSArg = 0x22, UnlineUpdataGPRS = 0x23, GetMIOTVer = 043
    switch (*(dat + 1)) {//读取数据包
        case GetSampDat:
        {
            reg_add = *(dat + 2); //开始序号
            arg_num = *(dat + 3); //BCD 参数数量 
            //
            if (reg_add == 0xFF) { //如果数据地址范围不在0-503(其中每隔41个有一个预留空间),发送非法数据地址
                reg_add = gOffsetAdd;
            } else {
                if (!DataIsVaild(reg_add, DataPacketNum - 1, 0)) //如果数据值不在1-5之间，发送非法数据值
                {
                    TCP_Error_Relay(GetSampDat, Dat_Add_Err, source);
                    break;
                }
            }
            if (!DataIsVaild(arg_num, DataPacketNum, 1)) //如果数据值不在1-5之间，发送非法数据值
            {
                TCP_Error_Relay(GetSampDat, Dat_Val_Err, source);
                break;
            }
            //            TCP_Error_Relay(GetSampDat, Do_Err, source);
            TCP_03_Reply(source, reg_add, arg_num);
            break;
        }
        case GetMIOTArg://读取MIOT参数
        {
            reg_add = *(dat + 2); //获取参数寄存器地址   
            arg_num = *(dat + 3); // >> 4)*10 + (*(dat + 4) & 0x0F); //BCD 参数数量                 

            if (!DataIsVaild(reg_add, REG2_Arg_Postion[REG2_ARG_NUM - 1], REG2_Arg_Postion[0])) //如果参数地址不在0x200-0x212，则发送非法数据地址
            {
                TCP_Error_Relay(GetMIOTArg, Dat_Add_Err, source);
                break;
            }

            if (!DataIsVaild(arg_num, REG2_ARG_NUM, 1)) ////如果参数数量不在1-24，则发送非法数据值????????????超出个数
            {
                TCP_Error_Relay(GetMIOTArg, Dat_Val_Err, source);
                break;
            }
            Register2Read(tmp, REG2_Arg_Postion[reg2_mi_add], 1); //赋值Miot1601地址
            tmp[1] = 0X04; //赋值功能码                   
            tmp[2] = GetSize(reg_add, arg_num); //赋值字节数
            add_base = tmp[2];
            Register2Read(tmp + 3, reg_add, add_base); //读取register2寄存器值

            CRC_Result = CRC16_Check(tmp, add_base + 3); //计算CRC结果
            tmp[add_base + 3] = (u8) (CRC_Result & 0x00ff); //赋值CRC低8位
            tmp[add_base + 4] = (u8) ((CRC_Result >> 8)&0x00ff); //赋值CRC高8位

            TCP_SendData(source, tmp, add_base + 5); //发送数据到对应串口
            break;
        }
        case SetMIOTArg://设置Miot1601参数
        {
            add_base = 0x04;
            reg_add = *(dat + 2); //获取参数寄存器地址  (*(uint16_t *)(tmp+8)<<8)+10)
            arg_num = *(dat + 3); //(*(dat + 4) >> 4)*10 + (*(dat + 4)&0x0F); //BCD 参数数量 
            //如果参数地址不在0x200-0x212，则发送数据地址错误
            if (!DataIsVaild(reg_add, REG2_Arg_Postion[REG2_ARG_NUM - 1], REG2_Arg_Postion[0])) //
            {
                TCP_Error_Relay(SetMIOTArg, Dat_Add_Err, source);
                break;
            }
            //如果参数数量不在1-18，则发送非法数据值
            if (!DataIsVaild(arg_num, REG2_ARG_NUM, 1)) //
            {
                TCP_Error_Relay(SetMIOTArg, Dat_Val_Err, source);
                break;
            }
            SetVaildData(dat + REG2_Arg_Postion[reg2_mi_tmp] + add_base, TIME_MP_MAX, TIME_MP_MIN); //获取采集时间并检查 27
            SetVaildData(dat + REG2_Arg_Postion[reg2_mi_tgprs] + add_base, TIME_GPRS_MAX, TIME_GPRS_MIN); //获取GPRS上线时间并检查
            SetVaildData(dat + REG2_Arg_Postion[reg2_mi_talarm] + add_base, TIME_ALARM_MAX, TIME_ALARM_MIN); //获取GPRS上线时间并检查 

            Register2Write(dat + add_base, reg_add, GetSize(reg_add, arg_num)); //设置的时间写入miot1601里面
            StopRTCC(); //refresh RTCC time
            CheckRTCC(); //写入RTCC中
            StartRTCC();
            //            CopyDat(tmp, dat + add_base + REG2_Arg_Postion[mi_ofst], 4);
            //            gPulseCount = tmp[3]+((u16) tmp[2] << 8)+((u32) tmp[1] << 16)+((u32) tmp[0] << 24); //反序写入
            //            FM25L64B_Write(BOR_Pulse, (u8*) (&gPulseCount), 4); //保存脉冲总量
            SaveMiotArg(); //保存MIOT参数到铁电
            TCP_10_Reply(reg_add, arg_num, source);
            OutputMiotArg();
            break;
        }
        case GetGPRSArg://获取GPRS参数//
        {//错误判断放在上位机上面 仅支持TRG1601      
            if (source == GPRS) {//GPRS上线发送数据
                TCP_Error_Relay(GetGPRSArg, Fun_Err, GPRS);
                break;
            }
            if (FLagArgbits.TestOnlieFlag || FLagArgbits.tgprsFlag || FLagArgbits.LowPoweralarmFlag) {
                TCP_Error_Relay(GetGPRSArg, Do_Err, PC);
                break;
            }
            Open_UART2();
            GPRS_ON;
            TCP_32_Reply();
            GPRS_OFF;
            Close_UART2();
            while (BufferRead_UART2(dat)); //清除缓冲区
            while (BufferRead_UART1(dat)); //清除缓冲区
            break;
        }
        case SetGPRSArg://设置GPRS参数
        {//错误判断放在上位机上面 仅支持TRG1601            
            if (source == GPRS) {//GPRS上线发送数据
                TCP_Error_Relay(SetGPRSArg, Fun_Err, GPRS);
                break;
            }
            if (FLagArgbits.TestOnlieFlag || FLagArgbits.tgprsFlag || FLagArgbits.LowPoweralarmFlag) {
                TCP_Error_Relay(SetGPRSArg, Do_Err, PC);
                break;
            }
            Open_UART2();
            GPRS_ON;
            TCP_33_Reply(dat + 2);
            GPRS_OFF;
            Close_UART2();
            while (BufferRead_UART2(dat)); //清除缓冲区
            while (BufferRead_UART1(dat)); //清除缓冲区
            //            Nop();
            break;
        }
        case TestGPRS://测试GPRS
        {//错误判断放在上位机上面 仅支持TRG1601            
            if (source == GPRS) {//GPRS上线发送数据
                TCP_Error_Relay(TestGPRS, Fun_Err, GPRS);
                break;
            }
            if (FLagArgbits.tgprsFlag) {
                TCP_Error_Relay(TestGPRS, Do_Err, PC);
                break;
            }
            FLagArgbits.TestOnlieFlag = 1;
            TCP_34_Reply();
            break;
        }
        case GetMIOTVer:
        {//获取软件版本号
            TCP_43_Reply();
            break;
        }
        case GetMIOTSta:
        {//获取MIOT状态
            u8 receiveBuffer[7] = {0, 0, 0, 0}, cnt = 0;
            u16 CRC_Result = 0; //CRC校验结果
            Register2Read(receiveBuffer, 0, 1); //赋值Miot1601地址
            receiveBuffer[1] = GetMIOTSta;
            //            for (cnt = 0; cnt < 5; cnt++)
            GetStatus(receiveBuffer + 2 + cnt);
            CRC_Result = CRC16_Check(receiveBuffer, 5); //计算CRC结果   2b开始
            receiveBuffer[5] = (u8) (CRC_Result & 0x00ff);
            receiveBuffer[6] = (u8) ((CRC_Result >> 8)&0x00ff);
            TCP_SendData(PC, receiveBuffer, 7);
            break;
        }
        default:
        {
            TCP_Error_Relay(*(dat + 1), Fun_Err, source);
            break;
        }
    }
    return 1;
}

//static void TCP_02_Reply(u8 source) {
//    u8 sendBuffer1[REG3_BYTES]; //声明发送缓冲区，计数
//    u8 sendBuffer2[5], cnt; //回复返回数据
//    u16 CRC_Result = 0; //CRC校验结果
//
//    Register2Read(sendBuffer2, REG2_Arg_Postion[mi_add], 1); //赋值Miot1601地址
//    sendBuffer2[1] = GetMuiltSampDat; //赋值功能码 判断功能码GetMuiltSampDat      
//    sendBuffer2[2] = 0x90; //114组数据
//    CRC_Result = CRC16_Check(sendBuffer2, 3); //计算CRC结果
//    sendBuffer2[3] = (u8) (CRC_Result & 0x00ff);
//    sendBuffer2[4] = (u8) ((CRC_Result >> 8)&0x00ff);
//    //发送数据到对应串口
//    for (cnt = 0; cnt < 144; cnt++) {
//        FM25L64B_Read((cnt % 144) * REG3_BYTES, sendBuffer1, REG3_BYTES); //等待完成
//        TCP_SendData(source, sendBuffer1, 42); //发送采集到的数据
//    }
//}

static void TCP_03_Reply(u8 source, u8 start_ID, u8 nums) {//采集数据
    //    u16 vaildBytes = 0; //有效字节数
    u8 sendBuffer[REG1_BYTES + 2], cnt; //声明发送缓冲区，计数
    u16 CRC_Result = 0; //CRC校验结果

    if (FLagArgbits.TestOnlieFlag && (nums == 1)) //避免资源二次调用，导致设备复位
        TCP_Error_Relay(GetSampDat, Do_Err, PC);
    else {
        sendBuffer[0] = miotArgs.mi_add; //赋值Miot1601地址
        sendBuffer[1] = 0X03; //赋值功能码        
        sendBuffer[2] = nums; //获取字节数
        //CRC校验
        CRC_Result = CRC16_Check(sendBuffer, 3); //计算CRC结果
        sendBuffer[3] = (u8) (CRC_Result & 0x00ff); //赋值CRC低8位
        sendBuffer[4] = (u8) ((CRC_Result >> 8)&0x00ff); //赋值CRC高8位
        TCP_SendData(source, sendBuffer, 5);
        if (nums == 1) {
            //            IEC1bits.INT1IE = 0; //开中断保护
//            FLagArgbits.TestGetDataFlag = 1;
//            StartTime4(); //采集一次数据//中断产生过程中还未及时响应，又产生中断，导致这类陷阱中断
//            IFS1bits.T4IF = 1; //Clear the Timer3 interrupt status flag
//            while (IFS1bits.T4IF)
//                StartTime4();
            FM25L64B_Read((gOffsetAdd + 143) % 144 * REG1_BYTES, sendBuffer, REG1_BYTES); //等待完成
            //发送数据到对应串口
            TCP_SendData(source, sendBuffer, REG1_BYTES);
            //            IEC1bits.INT1IE = 1; //关中断保护
        } else {
            Delay100ms(3);
            for (cnt = 0; cnt < nums; cnt++) {
                FM25L64B_Read((start_ID + 143 + cnt) % 144 * REG1_BYTES, sendBuffer, REG1_BYTES); //等待完成
                //发送数据到对应串口
                TCP_SendData(source, sendBuffer, REG1_BYTES);
            }
        }
    }
}

//static void TCP_04_Reply(u16 reg_add, u8 arg_num, u8 source) {//获取miot参数
//    u16 vaildBytes = 0; //有效字节数
//    u8 sendBuffer[REG2_BYTES + 10]; //声明发送缓冲区，计数
//    u16 CRC_Result = 0; //CRC校验结果
//
//    Register2Read(sendBuffer, REG2_Arg_Postion[mi_add], 1); //赋值Miot1601地址
//    sendBuffer[1] = 0X04; //赋值功能码                   
//    sendBuffer[2] = GetSize(reg_add, arg_num); //赋值字节数
//    vaildBytes = sendBuffer[2] + 3; //Register2的数据54+地址+功能吗+字节数
//    //读取register2寄存器值
//    Register2Read(&sendBuffer[3], reg_add, sendBuffer[2]);
//
//    CRC_Result = CRC16_Check(sendBuffer, vaildBytes); //计算CRC结果
//    sendBuffer[vaildBytes] = (u8) (CRC_Result & 0x00ff); //赋值CRC低8位
//    sendBuffer[vaildBytes + 1] = (u8) ((CRC_Result >> 8)&0x00ff); //赋值CRC高8位
//    vaildBytes += 2;
//    //发送数据到对应串口
//    TCP_SendData(source, sendBuffer, vaildBytes);
//}

static void TCP_10_Reply(u16 reg_add, u8 arg_num, u8 source) {//修改miot参数
    u8 sendBuffer[7];
    u16 CRC_Result = 0; //CRC校验结果

    sendBuffer[0] = miotArgs.mi_add; //赋值Miot1601地址
    sendBuffer[1] = 0x10;
    sendBuffer[2] = (u8) ((reg_add >> 8)&0x00ff);
    sendBuffer[3] = (u8) (reg_add & 0x00ff);
    sendBuffer[4] = arg_num; //    sendBuffer[4] = arg_num / 10 * 16 + arg_num % 10;
    CRC_Result = CRC16_Check(sendBuffer, 5); //计算CRC结果    
    sendBuffer[5] = (u8) (CRC_Result & 0x00ff);
    sendBuffer[6] = (u8) ((CRC_Result >> 8)&0x00ff);

    TCP_SendData(source, sendBuffer, 7);
}

static void TCP_32_Reply(void) {//获取GPRS参数
    u8 receiveBuffer[140] = {0, 0, 0, 0};
    u8 tmp;
    u16 CRC_Result = 0; //CRC校验结果
    //    Open_UART2();
    receiveBuffer[0] = miotArgs.mi_add; //赋值Miot1601地址
    receiveBuffer[1] = 0x20;
    Delay1s(1); //必须添加
    while (BufferRead_UART2(&tmp)); //清楚缓冲区数据
    TCP_SendData(GPRS, (u8*) ReadArg, 14);
    Delay1s(1);
    if (UARTIsGet(BufferRead_UART2, receiveBuffer + 2, 136, ArgRe, 5) == 136) {//修改成直接输出
        CRC_Result = CRC16_Check(receiveBuffer, 138); //计算CRC结果   2b开始
        receiveBuffer[138] = (u8) (CRC_Result & 0x00ff);
        receiveBuffer[139] = (u8) ((CRC_Result >> 8)&0x00ff);
        TCP_SendData(PC, receiveBuffer, 140);
    } else
        TCP_Error_Relay(GetGPRSArg, Do_Err, PC);
    while (BufferRead_UART2(&tmp)); //清楚缓冲区数据
    //    Close_UART2();
}

static void TCP_33_Reply(u8 * dat) {//设置GPRS参数
    u8 receiveBuffer[20], tmp;
    u16 CRC_Result = 0; //CRC校验结果

    Register2Read(receiveBuffer, REG2_Arg_Postion[0], 1); //赋值Miot1601地址
    receiveBuffer[1] = SetGPRSArg;
    Delay100ms(5);
    TCP_SendData(GPRS, dat, 144);
    //发送GPRS参数值 
    Delay100ms(8); //等待100ms 接收数据 中断
    //1s内从串口2接收数据 放在reciveBuffer+2中 反之发送没有指令的命令
    if (UARTIsGet(BufferRead_UART2, receiveBuffer + 2, 10, ArgRe, 5)) {
        Close_UART2();
        CRC_Result = CRC16_Check(receiveBuffer, 2); //计算CRC结果    
        receiveBuffer[2] = (u8) (CRC_Result & 0x00ff);
        receiveBuffer[3] = (u8) ((CRC_Result >> 8)&0x00ff);
        TCP_SendData(PC, receiveBuffer, 4);
    } else
        TCP_Error_Relay(SetGPRSArg, Do_Err, PC);
    while (BufferRead_UART2(&tmp)); //清楚缓冲区数据
}

static void TCP_34_Reply(void) {//测试GPRS工作
    u8 receiveBuffer[5], tmp;
    u16 CRC_Result = 0; //CRC校验结果

    Register2Read(receiveBuffer, REG2_Arg_Postion[reg2_mi_add], 1); //赋值Miot1601地址
    receiveBuffer[1] = TestGPRS;
    CRC_Result = CRC16_Check(receiveBuffer, 2); //计算CRC结果    
    receiveBuffer[2] = (u8) (CRC_Result & 0x00ff);
    receiveBuffer[3] = (u8) ((CRC_Result >> 8)&0x00ff);
    TCP_SendData(PC, receiveBuffer, 4);
    while (BufferRead_UART2(&tmp)); //清楚缓冲区数据
    //    GPRS_OFF;
}

//static void TCP_35_Reply(void) {//离线升级
//    u8 receiveBuffer[150];
//    u16 CRC_Result = 0; //CRC校验结果
//
//    GPRS_ON;
//    //发送GPRS参数值  
//    //    UART2SendString(dat + 2, 144);
//    //等待100ms 接收数据 中断
//    Delay100ms(1);
//    //1s内从串口2接收数据 放在reciveBuffer+2中 反之发送没有指令的命令
//    if (UARTIsGet(BufferRead_UART1, receiveBuffer + 2, 134, ArgRe,5)) {
//        Register2Read(receiveBuffer, 0x200, 1); //赋值Miot1601地址
//        receiveBuffer[1] = 0x11;
//        CRC_Result = CRC16_Check(receiveBuffer, 136); //计算CRC结果    
//        receiveBuffer[136] = (u8) (CRC_Result & 0x00ff);
//        receiveBuffer[137] = (u8) ((CRC_Result >> 8)&0x00ff);
//        TCP_SendData(PC, receiveBuffer, 138);
//    } else
//        TCP_Error_Relay(0x11, Do_Err, PC);
//    GPRS_OFF;
//}

static void TCP_43_Reply(void) {
    u8 receiveBuffer[10] = {0, 0, 0, 0}, cnt = 0;
    u16 CRC_Result = 0; //CRC校验结果
    Register2Read(receiveBuffer, 0, 1); //赋值Miot1601地址
    receiveBuffer[1] = 0x43;
    for (cnt = 0; cnt < 5; cnt++)
        receiveBuffer[2 + cnt] = Ver[cnt];
    CRC_Result = CRC16_Check(receiveBuffer, 7); //计算CRC结果   2b开始
    receiveBuffer[7] = (u8) (CRC_Result & 0x00ff);
    receiveBuffer[8] = (u8) ((CRC_Result >> 8)&0x00ff);
    TCP_SendData(PC, receiveBuffer, 9);
}

void TCP_Error_Relay(u8 code, u8 err, u8 source) {
    u8 sendBuffer[5]; //声明发送缓冲区
    u16 CRC_Result; //声明CRC结果

    Register2Read(sendBuffer, REG2_Arg_Postion[0], 1); //赋值Miot1601地址
    sendBuffer[1] = 0x80 + code;
    sendBuffer[2] = err;

    CRC_Result = CRC16_Check(sendBuffer, 3); //计算CRC结果
    sendBuffer[3] = (u8) (CRC_Result & 0x00ff);

    sendBuffer[4] = (u8) ((CRC_Result >> 8)&0x00ff);
    TCP_SendData(source, sendBuffer, 5); //发送数据
}

//input arg,01,7

void TCP_SendData(u8 source, u8 *dat, u8 bytes) {
    if (source)
        UART2SendString(dat, bytes); //向GPRS发送数据
    else
        RS485SendString(dat, bytes); //向电脑发送数据
}
//for DAZONG

void UDPSendData(u8 packetType) {//, u8 OffSet, const u8 SampleCnt) {
    u8 reg3Buffer[UDP_13_LENGTH + 4]; //采集数据Register 47=UDP_A2_LENGTH + 4+1(sumcheck))
    u8 A2Dat[61]; //
    u8 cnt, sumCheck = 0; // start_cnt = 0;
    u16 length = 0;
    u16 sampCnt = Reg3_Buf1_Recordbits.Record; //获取采集的数据次数
    u8 startCnt = Reg3_Buf1_Recordbits.Buffer_ID; //获取当前开始的数据头
    //    Record = 23 Buffer_ID=23 [0-22] start_cnt = 0
    //    Record = 24 Buffer_ID=0  [0-23] start_cnt = 0
    //    Record = 25 Buffer_ID=1  [1--23-0] start_cnt = 1
    //    Record = 28 Buffer_ID=4  [4--23-3] start_cnt = 4
    //    Record = 47 Buffer_ID=23  [23--22] start_cnt = 23
    //    Record = 48 Buffer_ID=0   [0--23] start_cnt = 0

    A2Dat[0] = 'A'; //设置13开头
    A2Dat[1] = '2';
    CopyDat(A2Dat + 2, miotArgs.mi_ID, 8); //获取EID号
    if (sampCnt > REG3_BUF1_CNT)//如果获取到25组数据的话,将发送的数据组设置成24
        sampCnt = REG3_BUF1_CNT; //else
    else
        startCnt = 0; //小于等于24组      
    length = 15 + (UDP_A2_LENGTH + 4) * sampCnt; //2+8+2+1+1+(UDP_A2_LENGTH+4)*number+1; //数据总长


    switch (packetType) {
        case SampleData:
        {
            A2Dat[10] = (u8) (length >> 8);
            A2Dat[11] = (u8) (length & 0x00FF);
            A2Dat[12] = packetType; //数据类型 
            A2Dat[13] = sampCnt; //赋值数据包个数 
            sumCheck = Sum_Check256(A2Dat, 14); //获取校验和
            TCP_SendData(GPRS, A2Dat, 14); //发送前14个字节数据
            for (cnt = 0; cnt < sampCnt; cnt++) {//组合数据包 //赋值数据包的数据      
                GetRegister1(REG3_BUF1, reg3Buffer, (cnt + startCnt) % REG3_BUF1_CNT); //获取数据  
                CopyDat(A2Dat, reg3Buffer, 4); //赋值时间戳
                PacketData2A2(A2Dat + 4, reg3Buffer); //获取协议 赋值给数据包  A2参数+时间戳18=数据头(14)+地址位在A2中的位置(4)
                sumCheck += Sum_Check256(A2Dat, UDP_A2_LENGTH + 4); //获取和校验46个字节
                if (sampCnt - 1 == cnt) {
                    A2Dat[UDP_A2_LENGTH + 4] = sumCheck;
                    TCP_SendData(GPRS, A2Dat, UDP_A2_LENGTH + 5);
                } else {
                    TCP_SendData(GPRS, A2Dat, UDP_A2_LENGTH + 4); //使用中断发送给数据，避免数据丢失
                    Delay100ms(5);//延时500ms避免数据发送过快导致下线
                }
            }
            break;
        }
        case LowPowerData:
        {
            A2Dat[10] = 0; //数据总长
            A2Dat[11] = 61;
            A2Dat[12] = 5; //数据类型 低压报警数据
            A2Dat[13] = 1; //赋值数据包个数 
            //            sumCheck = Sum_Check256(A2Dat, 14); //获取校验和                       
            GetRegister1(REG3_BUF2, reg3Buffer, 1); //获取数据
            CopyDat(A2Dat + 14, reg3Buffer, 4); //赋值时间戳
            PacketData2A2(A2Dat + 18, reg3Buffer); //获取协议 赋值给数据包  A2参数+时间戳18=数据头(14)+地址位在A2中的位置(4)
            A2Dat[60] = Sum_Check256(A2Dat, 60); //获取和校验            
            TCP_SendData(GPRS, A2Dat, 61);
            break;
        }
        case TestData:
        {
            A2Dat[10] = 0; //数据总长
            A2Dat[11] = 61;
            A2Dat[12] = 0; //数据类型 
            A2Dat[13] = 1; //赋值数据包个数 
            GetRegister1(REG3_BUF2, reg3Buffer, 1); //获取数据 different
            CopyDat(A2Dat + 14, reg3Buffer, 4); //赋值时间戳
            PacketData2A2(A2Dat + 18, reg3Buffer); //获取协议 赋值给数据包  A2参数+时间戳18=数据头(14)+地址位在A2中的位置(4)
            A2Dat[60] = Sum_Check256(A2Dat, 60); //获取和校验
            TCP_SendData(GPRS, A2Dat, 61);
            break;
        }
        default:
            break;
    }
}
//}

bool DUPDataChange(u8 * source_dat) {
    u8 Data_Type = *(source_dat + 14); //获取第一个数据的序号
    //    char bytes = *(source_dat + 13); //获取数据的长度
    uint8_t bytes = 14; //赋值第一个数据的数组地址00 00 16
    uint8_t tmprtcc[7] = {0, 0, 0, 0, 0, 0, 0};

    float setvoltage = 0; //, getvoltage = 0;
    // u16 time_tmp;//获取时间 
    //41 32 7F F9 02 01 00 00 00 01
    //00 06 00 1D 00 00 78 01 02 58 
    //02 00 3C 03 42 C8 00 00 04 42 
    //C8 00 00 05 41 20 00 00 06 41 
    //20 00 00 0B 
    if (!DataIsVaild((u16) Data_Type, 8, 0)) //判断数据类型是否超出范围
        return false;

    //    if (!DataIsVaild((u16) bytes, 39, 3)) //判断字节数是否超出范围
    //        return false;

    if (!(*(source_dat + 12))) {//如果数据类型是ACK
        while (bytes < *(source_dat + 13) + 14) {
            Data_Type = *(source_dat + bytes);
            switch (Data_Type) {
                case 0x00:
                {// Save Period (seconds) 时间的表示方式不对                    
                    SetVaildData((source_dat + bytes + 1), TIME_MP_MAX, TIME_MP_MIN); //检查数据
                    Register2Write((source_dat + bytes + 1), REG2_Arg_Postion[reg2_mi_tmp], 2);
                    bytes += 3;
                    break;
                }
                case 0x01:
                {// Send Period (seconds)                   
                    SetVaildData((source_dat + bytes + 1), TIME_GPRS_MAX, TIME_GPRS_MIN); //获取GPRS上线时间并检查
                    Register2Write((source_dat + bytes + 1), REG2_Arg_Postion[reg2_mi_tgprs], 2);
                    bytes += 3;
                    break;
                }
                case 0x02:
                {// Alarm Period (seconds)
                    SetVaildData((source_dat + bytes + 1), TIME_ALARM_MAX, TIME_ALARM_MIN); //获取GPRS上线时间并检查
                    Register2Write((source_dat + bytes + 1), REG2_Arg_Postion[reg2_mi_talarm], 2);
                    bytes += 3;
                    break;
                }
                case 0x03:
                {// High Pressure Alarm 需要加判断
                    Register2Write((source_dat + bytes + 1), REG2_Arg_Postion[reg2_mi_hp_alarm], 4);
                    bytes += 5;
                    break;
                }
                case 0x04:
                {// Low Pressure Alarm 需要加判断
                    Register2Write((source_dat + bytes + 1), REG2_Arg_Postion[reg2_mi_lp_alarm], 4);
                    bytes += 5;
                    break;
                }
                case 0x05:
                {// High Temperature Alarm 需要加判断
                    Register2Write((source_dat + bytes + 1), REG2_Arg_Postion[reg2_mi_ht_alarm], 4);
                    bytes += 5;
                    break;
                }
                case 0x06:
                {// Low Temperature Alarm 需要加判断
                    Register2Write((source_dat + bytes + 1), REG2_Arg_Postion[reg2_mi_lt_alarm], 4);
                    bytes += 5;
                    break;
                }
                case 0x07:
                {// 时间 需要加判断
                    GetUnixTime_YYYYMMDD((const u8*) (source_dat + bytes + 1), tmprtcc);
                    Register2Write(tmprtcc, REG2_Arg_Postion[reg2_mi_year], 7);
                    bytes += 5;
                    break;
                }
                case 0x08:
                {// 低压报警 需要加判断
                    Register2Write((source_dat + bytes + 1), REG2_Arg_Postion[reg2_mi_lv_alarm], 4); //将服务器发送的数据写入MIOT的参数表中
                    CharToFloat(&setvoltage, source_dat + bytes + 1); //将4个字节char类型数据转化为浮点数
                    //                    GetMuilVoltage(&getvoltage); //获取现在电池电压
                    //                    FLagArgbits.LowPoweralarmFlag = (getvoltage < setvoltage) ? true : false; //设定标志位
                    bytes += 5;
                    break;
                }
                default:
                {
                    bytes = 100;
                    break;
                }
            }
        }
        OutputMiotArg(); //刷新数据       
        return true;
    }
    return false;
}

void PC_Cop(void) {
    u8 byte = 0;
    u8 Receive[150] = {0, 0};

    byte = UARTIsGet(BufferRead_UART1, Receive, 148, &miotArgs.mi_add, 1);
    if (byte && CheckIsRight(CRC16_Check, Receive, (const u8) (byte - 2))) {
        CopFun(Receive, PC);
    }
}


/*//地址
                gprs_output[19] = rs485_receive[1]; //获取设备编号 20个字节地址最后2个字节有效
//                gprs_output[18] = rs485_receive[1];
                //获取时间
                for(count=0;count<7;count++)
                    gprs_output[P_Location[Gprs][time1] + count] = 
                            rs485_receive[P_Location[V1_3][time1] + count];
                //标况瞬时流量V1_ins 
                V1_ins = ToFloat1(rs485_receive+P_Location[V1_3][v1i]);
                Float_To_Char(&V1_ins,gprs_output + P_Location[Gprs][v1i]);
                //标况累积总量V1_acc
                V1_acc = (*(rs485_receive+P_Location[V1_3][v1a])*100)+
 *(rs485_receive+P_Location[V1_3][v1a]+1)+
                        ToFloat1(rs485_receive+P_Location[V1_3][v1a]+2);
                Double_To_Char(&V1_acc,gprs_output + P_Location[Gprs][v1a]);
                //温度
                temperature = ToFloat1(rs485_receive+P_Location[V1_3][t1]);
                Float_To_Char(&temperature,gprs_output + P_Location[Gprs][t1]);
                //压力
                stress = ToFloat1(rs485_receive+P_Location[V1_3][s1]);
                Float_To_Char(&stress,gprs_output + P_Location[Gprs][s1]);
                //报警字
                Alarm_w = *(rs485_receive+P_Location[V1_3][alarm1]);
 *(gprs_output + P_Location[Gprs][alarm1]) = Alarm_w;
                //状态字
                Status_w = *(rs485_receive+P_Location[V1_3][status1]);
 *(gprs_output + P_Location[Gprs][status1]) = Status_w;
                //crc
                crctemp = CRC16_Check(gprs_output,61);
                gprs_output[61] = (u8)crctemp;
                gprs_output[62] = (u8)(crctemp>>8);
                
 */

