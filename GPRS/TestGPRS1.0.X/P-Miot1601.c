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

extern const u8 mi_dat_add[REG_DATA_ARG_NUM + 1];
extern const u16 mi_arg_add[REG_ARG_NUM + 1];
extern enum mi_arg_add_enum enum_mi_arg_add;
extern enum mi_dat_add_enum enum_mi_dat_add;
struct Alarm_Arg AlarmArgbits;
struct Status Statusbits;
extern u8 bufferRptr_uart2;
extern u8 bufferWptr_uart2;
extern u8 Buffer_uart2[256];
//static bool DUPDataChange(u8 *source_dat);
static void TCP_03_Reply(u8 source);
static void TCP_04_Reply(u16 reg_add, u8 arg_num, u8 source);
static void TCP_10_Reply(u16 reg_add, u8 arg_num, u8 source);
static void TCP_11_Reply(u8* dat);
static void TCP_43_Reply(void);
void TCP_Error_Relay(u8 code, u8 err, u8 source);

/*************************************
Function: CopFun 
Description: 选择通讯功能
Input: 数据 发送给
Output: 
 *************************************/
u8 CopFun(u8*dat, u8 source) {
    u16 reg_add = 0; //获取参数寄存器地址   
    u8 arg_num = 0; //BCD 参数数量  
    u8 tmp[5];
    //判断功能码
    switch (*(dat + 1)) {//读取数据包
        case 0x03:
        {
            reg_add = (*(dat + 2) << 8) + *(dat + 3); //获取数据包寄存器地址  
            arg_num = *(dat + 4); //BCD 参数数量 
            //如果数据地址范围不在0-503(其中每隔41个有一个预留空间),发送非法数据地址
            if (!DataIsVaild(reg_add, 144, 0)) //判断数据有效性
            {
                TCP_Error_Relay(0x03, Dat_Add_Err, source);
                break;
            }
            //如果数据值不在1-5之间，发送非法数据值
            if (!DataIsVaild(arg_num, 9, 1)) //
            {
                TCP_Error_Relay(0x03, Dat_Val_Err, source);
                break;
            }
            TCP_03_Reply(source);
            //            }
            break;
        }
        case 0x04://读取参数
        {
            reg_add = (* (dat + 2) << 8) + *(dat + 3); //获取参数寄存器地址   
            arg_num = *(dat + 4); // >> 4)*10 + (*(dat + 4) & 0x0F); //BCD 参数数量                 
            //如果参数地址不在0x200-0x212，则发送非法数据地址
            if (!DataIsVaild(reg_add, mi_arg_add[REG_ARG_NUM - 1], mi_arg_add[0])) //
            {
                TCP_Error_Relay(0x04, Dat_Add_Err, source);
                break;
            }
            //如果参数数量不在1-18，则发送非法数据值
            if (!DataIsVaild(arg_num, REG_ARG_NUM, 1)) //????????????超出个数
            {
                TCP_Error_Relay(0x04, Dat_Val_Err, source);
                break;
            }
            TCP_04_Reply(reg_add, arg_num, source);
            break;
        }
        case 0x10://设置Miot1601参数
        {
            reg_add = (* (dat + 2) << 8) + *(dat + 3); //获取参数寄存器地址  (*(uint16_t *)(tmp+8)<<8)+10)
            arg_num = *(dat + 4); //(*(dat + 4) >> 4)*10 + (*(dat + 4)&0x0F); //BCD 参数数量 
            //如果参数地址不在0x200-0x212，则发送数据地址错误
            if (!DataIsVaild(reg_add, mi_arg_add[REG_ARG_NUM - 1], mi_arg_add[0])) //
            {
                TCP_Error_Relay(0x10, Dat_Add_Err, source);
                break;
            }
            //如果参数数量不在1-18，则发送非法数据值
            if (!DataIsVaild(arg_num, REG_ARG_NUM, 1)) //
            {
                TCP_Error_Relay(0x10, Dat_Val_Err, source);
                break;
            }
            //如果时间大小不再规定的范围内
            SetVaildData(dat + 28, TIME_MP_MAX, 1); //获取采集时间并检查
            SetVaildData(dat + 30, TIME_GPRS_MAX, 2); //获取GPRS上线时间并检查
            SetVaildData(dat + 32, TIME_ALARM_MAX, TIME_ALARM_MIN); //获取GPRS上线时间并检查

            //写入寄存器2的地址
            Register2Write(dat + 5, reg_add, GetSize(reg_add, arg_num));
            FM25L64B_Write(RST_Time, dat + 5 + mi_arg_add[mi_year] - 0x200, 7); //写入时间
            StopRTCC(); //refresh RTCC time
            CheckRTCC(); //写入RTCC中
            StartRTCC();
            tmp[3] = *(dat + 55); // 5 + mi_arg_add[mi_ofst] - 0x200);
            tmp[2] = *(dat + 56);
            tmp[1] = *(dat + 57);
            tmp[0] = *(dat + 58);
            gPulseCount = tmp[0]+((u16) tmp[1] << 8)+((u32) tmp[2] << 16)+((u32) tmp[3] << 24); //反序写入
            FM25L64B_Write(BOR_Pulse, (u8*) (&gPulseCount), 4); //保存脉冲总量
            TCP_10_Reply(reg_add, arg_num, source);
            break;
        }
        case 0x11://设置GPRS参数
        {//错误判断放在上位机上面 仅支持TRG1601            
            if (source == GPRS) {//GPRS上线发送数据
                TCP_Error_Relay(0x11, Fun_Err, GPRS);
                break;
            }
            TCP_11_Reply(dat);
            tmp[0] = *(dat + 15) - 0x30; //获取GPRS工作模式
            break;
        }
        case 0x40:
        {//主动报当天数据
            u8 tmp[2] = {0, 0};
            tmp[0] = (u8) (U2STA >> 8);
            tmp[1] = (u8) (U2STA & 0x00FF);
            RS485SendString("AAAAAAAAAA", 10);
            RS485SendString(&bufferWptr_uart2, 1);
            RS485SendString("BBBBBBBBBB", 10);
            RS485SendString(&bufferRptr_uart2, 1);
            RS485SendString("CCCCCCCCCC", 10);
            RS485SendString(&tmp, 2);
            RS485SendString("DDDDDDDDDD", 10);
            RS485SendString(Buffer_uart2, 255);
            break;
        }

        case 0x43:
        {//获取软件版本号
            TCP_43_Reply();
            break;
        }
            //        case 0x60:
            //        {
            //            return 'b';
            //        }
        default:
        {
            TCP_Error_Relay(0, Fun_Err, source);
            break;
        }
    }
    return 1;
}

static void TCP_03_Reply(u8 source) {
    //    u16 vaildBytes = 0; //有效字节数
    u8 sendBuffer[REG_DATA_SZIE + 10]; //声明发送缓冲区，计数
    u16 CRC_Result = 0; //CRC校验结果

    Register2Read(sendBuffer, mi_arg_add[mi_add], 1); //赋值Miot1601地址
    sendBuffer[1] = 0X03; //赋值功能码        
    sendBuffer[2] = 0x29; //获取字节数

    FM25L64B_Read((gOffsetAdd + 143) % 144 * REG_DATA_SECTION, sendBuffer + 3, REG_DATA_SECTION); //等待完成

    //CRC校验
    CRC_Result = CRC16_Check(sendBuffer, 44); //计算CRC结果
    sendBuffer[44] = (u8) (CRC_Result & 0x00ff); //赋值CRC低8位
    sendBuffer[45] = (u8) ((CRC_Result >> 8)&0x00ff); //赋值CRC高8位
    //    vaildBytes += 2;
    //发送数据到对应串口
    TCP_SendData(source, sendBuffer, 46);
}

static void TCP_04_Reply(u16 reg_add, u8 arg_num, u8 source) {
    u16 vaildBytes = 0; //有效字节数
    u8 sendBuffer[REG_ARG_SIZE + 10]; //声明发送缓冲区，计数
    u16 CRC_Result = 0; //CRC校验结果

    Register2Read(sendBuffer, mi_arg_add[mi_add], 1); //赋值Miot1601地址
    sendBuffer[1] = 0X04; //赋值功能码                   
    sendBuffer[2] = GetSize(reg_add, arg_num); //赋值字节数
    vaildBytes = sendBuffer[2] + 3; //Register2的数据54+地址+功能吗+字节数
    //读取register2寄存器值
    Register2Read(&sendBuffer[3], reg_add, sendBuffer[2]);

    CRC_Result = CRC16_Check(sendBuffer, vaildBytes); //计算CRC结果
    sendBuffer[vaildBytes] = (u8) (CRC_Result & 0x00ff); //赋值CRC低8位
    sendBuffer[vaildBytes + 1] = (u8) ((CRC_Result >> 8)&0x00ff); //赋值CRC高8位
    vaildBytes += 2;
    //发送数据到对应串口
    TCP_SendData(source, sendBuffer, vaildBytes);
}
//修改miot参数

static void TCP_10_Reply(u16 reg_add, u8 arg_num, u8 source) {
    u8 sendBuffer[7];
    u16 CRC_Result = 0; //CRC校验结果

    Register2Read(sendBuffer, mi_arg_add[mi_add], 1); //赋值Miot1601地址
    sendBuffer[1] = 0x10;
    sendBuffer[2] = (u8) ((reg_add >> 8)&0x00ff);
    sendBuffer[3] = (u8) (reg_add & 0x00ff);
    sendBuffer[4] = arg_num; //    sendBuffer[4] = arg_num / 10 * 16 + arg_num % 10;
    CRC_Result = CRC16_Check(sendBuffer, 5); //计算CRC结果    
    sendBuffer[5] = (u8) (CRC_Result & 0x00ff);
    sendBuffer[6] = (u8) ((CRC_Result >> 8)&0x00ff);

    TCP_SendData(source, sendBuffer, 7);
}
//修改GPRS参数

static void TCP_11_Reply(u8* dat) {
    u8 receiveBuffer[150];
    u16 CRC_Result = 0; //CRC校验结果
    //    u8 tmp = 0x2B;

    GPRS_ON;
    //发送GPRS参数值  
    UART2SendString(dat + 2, 144);
    //等待100ms 接收数据 中断
    Delay100ms(1);
    //1s内从串口2接收数据 放在reciveBuffer+2中 反之发送没有指令的命令
    if (UARTIsGet(BufferRead_UART1, receiveBuffer + 2, 134, ReceiveOK, 6)) {
        Register2Read(receiveBuffer, 0x200, 1); //赋值Miot1601地址
        receiveBuffer[1] = 0x11;
        CRC_Result = CRC16_Check(receiveBuffer, 136); //计算CRC结果    
        receiveBuffer[136] = (u8) (CRC_Result & 0x00ff);
        receiveBuffer[137] = (u8) ((CRC_Result >> 8)&0x00ff);
        TCP_SendData(PC, receiveBuffer, 138);
    } else
        TCP_Error_Relay(0x11, Do_Err, PC);
    GPRS_OFF;
}

static void TCP_43_Reply(void) {
    u8 receiveBuffer[10] = {0, 0, 0, 0}, cnt = 0;
    u16 CRC_Result = 0; //CRC校验结果
    Register2Read(receiveBuffer, 0x200, 1); //赋值Miot1601地址
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

    Register2Read(sendBuffer, 0x200, 1); //赋值Miot1601地址
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
    u8 sendBuffer1[14]; //开始数据 15+46*REG1_MAX_CNT=1119 REG1_MAX_CNT=24
    u8 sendBuffer2[19]; //采集数据变量Register
    u8 sendBuffer3[47]; //采集数据Register 47=UDP_A2_LENGTH + 4+1(sumcheck))
    u8 cnt, sumCheck = 0; // start_cnt = 0;
    u16 length = 0;
    u16 sampCnt = 1;//Reg1Argbits.Record; //获取采集的数据次数
    u8 startCnt = Reg1Argbits.Buffer_ID; //获取当前开始的数据头
    //    Record = 23 Buffer_ID=23 [0-22] start_cnt = 0
    //    Record = 24 Buffer_ID=0  [0-23] start_cnt = 0
    //    Record = 25 Buffer_ID=1  [1--23-0] start_cnt = 1
    //    Record = 28 Buffer_ID=4  [4--23-3] start_cnt = 4
    //    Record = 47 Buffer_ID=23  [23--22] start_cnt = 23
    //    Record = 48 Buffer_ID=0   [0--23] start_cnt = 0
    if (packetType == LowPowerAlarm) {//如果数据包类型是报警数据的话
        TCP_SendData(GPRS, AlarmData, UDP_A2_LENGTH + 19); //发送一组采集数据包
    } else {
        if (sampCnt > REG1_MAX_CNT)//如果获取到25组数据的话,将发送的数据组设置成24
            sampCnt = REG1_MAX_CNT; //else
        else
            startCnt = 0; //小于等于24组
        sendBuffer1[0] = 'A'; //A2帧头
        sendBuffer1[1] = '2';

        Register2Read(sendBuffer1 + 2, mi_arg_add[mi_id], 8); //EID

        length = 15 + (UDP_A2_LENGTH + 4) * sampCnt; //2+8+2+1+1+(UDP_A2_LENGTH+4)*number+1; //数据总长
        sendBuffer1[10] = (u8) (length >> 8);
        sendBuffer1[11] = (u8) (length & 0x00FF);
        sendBuffer1[12] = packetType; //数据类型 
        sendBuffer1[13] = sampCnt; //赋值数据包个数 
        sumCheck = Sum_Check256(sendBuffer1, 14); //获取校验和
        TCP_SendData(GPRS, sendBuffer1, 14);
        for (cnt = 0; cnt < sampCnt; cnt++) {//组合数据包 //赋值数据包的数据            
            GetRegister1(sendBuffer2, (cnt + startCnt) % REG1_MAX_CNT); //获取数据
            GetUnixTime_Char(sendBuffer2 + 12, sendBuffer3); //46=A2(42)+时间戳(4)//获取时间戳 08 16 1 1 0 0 0 时间容易溢出
            PacketData2A2(sendBuffer3 + 4, sendBuffer2); //获取协议 赋值给数据包  A2参数+时间戳18=数据头(14)+地址位在A2中的位置(4)
            sumCheck += Sum_Check256(sendBuffer3, 46); //获取和校验

            if (sampCnt - 1 == cnt) {
                sendBuffer3[46] = sumCheck;
                TCP_SendData(GPRS, sendBuffer3, 47);
            } else {
                TCP_SendData(GPRS, sendBuffer3, 46);
                Delay100ms(5);
            }
        }
    }
}

bool DUPDataChange(u8 * source_dat) {
    u8 Data_Type = *(source_dat + 14); //获取第一个数据的序号
    char bytes = *(source_dat + 13); //获取数据的长度
    // u16 time_tmp;//获取时间 
    //41 32 7F F9 02 01 00 00 00 01
    //00 06 00 1D 00 00 78 01 02 58 
    //02 00 3C 03 42 C8 00 00 04 42 
    //C8 00 00 05 41 20 00 00 06 41 
    //20 00 00 0B 
    if (!DataIsVaild((u16) Data_Type, 6, 0)) //判断数据类型是否超出范围
        return false;

    if (!DataIsVaild((u16) bytes, 29, 3)) //判断字节数是否超出范围
        return false;

    if (!(*(source_dat + 12))) {//如果数据类型是ACK
        while (bytes > 0) {
            switch (Data_Type) {
                case 0x00:
                {// Save Period (seconds) 时间的表示方式不对                    
                    SetVaildData((source_dat + 15), TIME_MP_MAX, TIME_MP_MIN); //检查数据

                    Register2Write((source_dat + 15), mi_arg_add[mi_tmp], 2);
                    bytes -= 3;
                    Data_Type = *(source_dat + 17);
                    break;
                }
                case 0x01:
                {// Send Period (seconds)                   
                    SetVaildData((source_dat + 18), TIME_GPRS_MAX, TIME_GPRS_MIN); //获取GPRS上线时间并检查

                    Register2Write((source_dat + 18), mi_arg_add[mi_tgprs], 2);
                    bytes -= 3;
                    Data_Type = *(source_dat + 20);
                    break;
                }
                case 0x02:
                {// Alarm Period (seconds)
                    if (!(*(source_dat + 22)+ (*(source_dat + 21) << 8))) {//(*((uint16_t *)(tmp+8))<<8)+10)
                        SetVaildData((source_dat + 21), TIME_ALARM_MAX, TIME_ALARM_MIN); //获取GPRS上线时间并检查
                    } else {
                        *(source_dat + 21) = 0;
                        *(source_dat + 22) = 0;
                    }
                    Register2Write((source_dat + 21), mi_arg_add[mi_talarm], 2);
                    bytes -= 3;
                    Data_Type = *(source_dat + 23);
                    break;
                }
                    //                case 0x03:
                    //                {// High Pressure Alarm 需要加判断
                    //                    Register2Write((source_dat + 24), mi_arg_add[mi_hp_alarm], 4);
                    //                    bytes -= 5;
                    //                    Data_Type = *(source_dat + 28);
                    //                    break;
                    //                }
                    //                case 0x04:
                    //                {// Low Pressure Alarm 需要加判断
                    //                    Register2Write((source_dat + 29), mi_arg_add[mi_lp_alarm], 4);
                    //                    bytes -= 5;
                    //                    Data_Type = *(source_dat + 33);
                    //                    break;
                    //                }
                    //                case 0x05:
                    //                {// High Temperature Alarm 需要加判断
                    //                    Register2Write((source_dat + 34), mi_arg_add[mi_ht_alarm], 4);
                    //                    bytes -= 5;
                    //                    Data_Type = *(source_dat + 38);
                    //                    break;
                    //                }
                    //                case 0x06:
                    //                {// Low Temperature Alarm 需要加判断
                    //                    Register2Write((source_dat + 39), mi_arg_add[mi_lt_alarm], 4);
                    //                    bytes -= 5;
                    //                    //                    Data_Type = *(source_dat + 24);
                    //                    break;
                    //                }
                default:
                {
                    bytes = 0;
                    break;
                }
            }
        }
        //        RefreshDaZong(); //刷新数据
        return true;
    }
    return false;
}

void PC_Cop(void) {
    u8 byte = 0;
    u8 Receive[65] = {0, 0};
    u8 Mp_id = 0;

    Register2Read(&Mp_id, mi_arg_add[mi_add], 1);
    byte = UARTIsGet(BufferRead_UART1, Receive, 61, &Mp_id, 1);
    if (byte && CheckIsRight(CRC16_Check, Receive, (const u8) (byte - 2))) {
        CopFun(Receive, PC);
    }
    Nop();
}

