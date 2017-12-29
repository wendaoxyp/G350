#include "user.h"
#include "UART.h"
#include "GPRS.h" 
#include "25L64B.h"
#include "TIM.h"
#include "SerialBuffer.h"
#include "Miot1601.h"
#include "CheckData.h"
#include "string.h"
#include "time.h"
#include "stdlib.h"
//#include "ctype.h"
//const u8 GPRS_Arg1[144] = {//UTC
//    0x2B, 0x54, 0x55, 0x52, 0x4F, 0x4E, 0x47, 0x20, 0x54, 0x45,
//    0x53, 0x54, 0x57, 0x30, 0x80, 0x8A, 0x8D, 0xAC, 0x0D, 0x00,
//    0x30, 0x30, 0x30, 0x0B, 0x15, 0x13, 0x87, 0x57, 0x96, 0x1F,
//    0x0B, 0x13, 0x46, 0x10, 0x79, 0x92, 0x5F, 0x30, 0x30, 0x32,
//    0x3C, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x30, 0x0D, 0x77, 0x77,
//    0x77, 0x2E, 0x62, 0x61, 0x69, 0x64, 0x75, 0x2E, 0x63, 0x6F,
//    0x6D, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
//    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x05,
//    0x43, 0x4D, 0x4E, 0x45, 0x54,   0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
//    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
//    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
//    0xFF, 0x30, 0x0B, 0x13, 0x71, 0x11, 0x11, 0x11, 0x1F, 0xFF,
//    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
//    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
//    0xFF, 0xFF, 0xCC, 0xC2
//};
/*
const u8 GPRS_Arg1[144] = {//UTC
    0x2B, 0x54, 0x55, 0x52, 0x4F, 0x4E, 0x47, 0x20, 0x54, 0x45,
    0x53, 0x54, 0x57, 0x30, 0xCA, 0x78, 0x02, 0x65, 0x7B, 0x00,
    0x30, 0x31, 0x30, 0x0B, 0x15, 0x13, 0x87, 0x57, 0x96, 0x1F,
    0x0B, 0x13, 0x46, 0x10, 0x79, 0x92, 0x5F, 0x30, 0x30, 0x31/*9600,
    0x3C, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x30, 0x0D, 0x77, 0x77,
    0x77, 0x2E, 0x62, 0x61, 0x69, 0x64, 0x75, 0x2E, 0x63, 0x6F,
    0x6D, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x05,
    0x43, 0x4D, 0x4E, 0x45, 0x54, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0x30, 0x0B, 0x13, 0x71, 0x11, 0x11, 0x11, 0x1F, 0x00,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0x68, 0x61
};
const u8 GPRS_Arg2[144] = {//miot1601
    0x2B, 0x54, 0x55, 0x52, 0x4F, 0x4E, 0x47, 0x20, 0x54, 0x45,
    0x53, 0x54, 0x57, 0x30, 0xCA, 0x94, 0xEA, 0x20, 0x7A, 0x17,
    0x30, 0x31, 0x30, 0x0B, 0x18, 0x25, 0x77, 0x00, 0x27, 0x1F,
    0x0B, 0x13, 0x80, 0x05, 0x77, 0x50, 0x0F, 0x30, 0x30, 0x31/*9600,
    0x3C, 0x00, 0xB4, 0x00, 0x58, 0x02, 0x30, 0x0D, 0x77, 0x77,
    0x77, 0x2E, 0x62, 0x61, 0x69, 0x64, 0x75, 0x2E, 0x63, 0x6F,
    0x6D, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x05,
    0x43, 0x4D, 0x4E, 0x45, 0x54, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0x30, 0x0B, 0x18, 0x35, 0x77, 0x68, 0x90, 0x7F, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0x89, 0x83
};

const u8 GPRS_Arg3[144] = {//FOR TEST
    0x2B, 0x54, 0x55, 0x52, 0x4F, 0x4E, 0x47, 0x20, 0x54, 0x45,
    0x53, 0x54, 0x57, 0x30, 0xB7, 0xF6, 0x4A, 0x44, 0xCF, 0x13,
    0x30, 0x31, 0x30, 0x0B, 0x13, 0x73, 0x69, 0x53, 0x37, 0x2F,
    0x0B, 0x13, 0x80, 0x05, 0x77, 0x50, 0x0F, 0x30, 0x30, 0x31, /*9600
    0x3C, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x30, 0x0D, 0x77, 0x77,
    0x77, 0x2E, 0x62, 0x61, 0x69, 0x64, 0x75, 0x2E, 0x63, 0x6F,
    0x6D, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x05,
    0x43, 0x4D, 0x4E, 0x45, 0x54, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0x30, 0x0B, 0x13, 0x71, 0x11, 0x11, 0x11, 0x1F, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0x3B, 0x19
};*/

const u16 GPRS_ON_TIME = 7000; //50s 5000*0.01
const u16 GPRS_ON_CHECK = 9000; //100s
//const u8 NTP_Message[48] = {
//    0x23, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
//};

//u8 SendUTC[12] = "+TURONG GPOT";
const u8 Ready[5] = "READY";
const u8 SendON[12] = "+TURONG GPON";
const u8 SendOFF[13] = "+TURONG GPOFF";
const u8 SendGPOT[12] = "+TURONG GPOT";
//const u8 ReceiveOK[6] = "+RECW0";
const u8 ReadArg[14] = "+TURONG TESTR0";
const u8 ArgRe[5] = {0x2B, 0x52, 0x45, 0x43, 0x57};
const u8 UDPHead[2] = {0x41, 0x32};
//const u8 GMTHead[3] = {'T', 'R', ':'};
//const u8 GMTHead[4] = {0x24, 0x03, 0x03, 0xE9};

//const u8 SendCH[12] = "+TURONG GPCH";
//u8 Head2[4] = "FAIL";
//u8 gUARTtmp[2]; //用于存放临时变量
u8 gAlarmZeroLock = 0;
//extern u8 gCurrentSampleCount;

/*************************************
Function: GPRS_Init 
Description: GPRS模块初始化
Input: 无
Output: 无
 *************************************/
void GPRS_Init(void) {
    //    u8 dat;
    GP_CON_OUT;
    GPRS_OFF;
    ANSAbits.ANSA3 = 0; //数字输入
    LK_OUT;
    ANSBbits.ANSB13 = 0; //数字输入
    //    dat = LK;
}

//static bool RTCCDataIsOK(u8* input, u8 *output) {//UTC时间
//    bool b = false;
//    if ((*(input + 2) == 0x2D)&&(*(input + 5) == 0x2D)) {
//        *output = ((*input - 0x30) << 4) + (*(input + 1) - 0x30);
//        *(output + 1) = ((*(input + 3) - 0x30) << 4) + (*(input + 4) - 0x30);
//        *(output + 2) = ((*(input + 6) - 0x30) << 4) + (*(input + 7) - 0x30);
//        if ((*(input + 11) == 0x3A)&&(*(input + 14) == 0x3A)) {
//            *(output + 3) = ((*(input + 9) - 0x30) << 4) + (*(input + 10) - 0x30);
//            *(output + 4) = ((*(input + 12) - 0x30) << 4) + (*(input + 13) - 0x30);
//            *(output + 5) = ((*(input + 15) - 0x30) << 4) + (*(input + 16) - 0x30);
//            b = true;
//        }
//    }
//    return b;
//}

bool GPRS_IS_Ready(void) {//如果返回READY，EN为高；反之，EN为低
    u8 fail_Cnt = 0; // loop_Cnt = 0;
    u8 tmp[5] = {0, 0};

    do {
        GPRS_OFF;
        Delay1s(6); //6s
        GPRS_ON;
        Delay1s(1); //6s
        if (fail_Cnt++ > 3) {//上线6次
            GPRS_OFF;
            return false;
        }
    } while (!UARTIsGet(BufferRead_UART2, tmp, 2, Ready, 5)); //{//是不是接收到READY
    return true;
}

bool GPRS_IS_Close(const u8 nS) {
    u8 tmp[5] = {0, 0};

    GPRS_OFF;
    Delay1s(nS); //延时delay秒
    return UARTIsGet(BufferRead_UART2, tmp, 2, SendOFF + 9, 4); //{//是不是接收到READY
}

void GPRS_Send(const u8*dat, u8 bytes) {
    u8 cnt = 0;
    while (cnt++ < 3) {
        UART2SendString(dat, bytes);
        Delay1s(1); //延时1s 
    }
}

/*************************************
Function: LKIsHigh 
Description: 判断是否上线
Input: 无
Output: 1：发送成功
 *************************************/
bool LKIsHigh(u16 deadline) {
    LK_IN;
    StartTime3();

    while (gT3Count < deadline) {//50s内上线  
        ClrWdt();
        if (LK) {
            Delay100ms(1);
            if (LK) {
                LK_OUT;
                return true;
            }
        }
    }
    CloseTime3();
    LK_OUT;
    return false;
}

/*************************************
Function: CopUDPTask 
Description: UDP发送采集数据任务通讯任务
Input: 无
Output: 无
 *************************************/
bool CopUDPTask(const u8 sendDat, const u8 goLineCount, const u8 sendCount) {
    u8 receiveBuffer[48] = {0, 0, 0, 0}; //29+15=44
    u8 FailCount = 0, sendCnt = 0, cnt = 0;
    u8 mi_id_Tmp[8] = {0, 0, 0, 0, 0, 0, 0, 0};

    Register2Read(mi_id_Tmp, REG2_Arg_Postion[mi_id], 8); //获取EID
    Statusbits.staGPRS = 1;
    Open_UART2(); //打开串口2

    while (FailCount++ < goLineCount) {//2次上线
        if (!GPRS_IS_Ready())//等待GPRS在状态
        {
            Statusbits.staGPRS = Data_No_Ready;
            Close_UART2(); //关闭串口2
            return false;
        }
        GPRS_Send(SendON, 12); //发送GPRS_ON
        if (LKIsHigh(GPRS_ON_TIME))//判断LK在60s内是否上线
        {
            Delay1s(1); //延时
            sendCnt = 0; //清除发送次数
            while (sendCnt++ < sendCount) {
                UDPSendData(sendDat); //, offsetAdd);
                Delay1s(6); //延时4s 必须要等待3s后数据返回
                //41 32 7F F9 02 01 00 00 00 08 00 1F 00 1D 00 0E 10 01 0E 10 02 00 00 05 41 20 00 00 06 41 20 00 00 03 41 20 00 00 04 41 20 00 00 07  [44bytes]
                for (cnt = 0; cnt < 4; cnt++)//最后四个字节没有接受到，中断原因
                    if (U2STAbits.URXDA == 1) //没有接收到
                        BufferWrite_UART2();
                if (UARTIsGet(BufferRead_UART2, receiveBuffer, 44, UDPHead, 2)) { //获取数据并校验数据     //如果有接收到数据 
                    if (receiveBuffer[43] == Sum_Check256(receiveBuffer, 43)) { //判断校验和是否正确                        
                        if (CheckSrting(receiveBuffer + 2, mi_id_Tmp, 8)) {
                            DUPDataChange(receiveBuffer);
                            Statusbits.staGPRS = All_Right;
                            if (!GPRS_IS_Close(3))
                                Statusbits.staGPRS = GPRS_Unline_No_Ready;
                            Close_UART2(); //关闭串口2
                            gTimeCount.timeGprs = gTimeCount.timeMp; //确保每次发送的数据正常
                            if (sendDat == SampleData)//如果是采集数据的话，采集数据通道不清除
                                EmptyRegister1(); //清除缓冲数据
                            if (((u16) receiveBuffer[21] << 8) + receiveBuffer[22])
                                gAlarmZeroLock = 0; //如果报警值不为零的话，清除锁存位
                            return true;
                        } else
                            Statusbits.staGPRS = Data_Error_MpId;
                    } else
                        Statusbits.staGPRS = Data_Error_Check_Sum;
                }
            }
        }
        Statusbits.staGPRS = Data_Timeover;
    }
    Statusbits.staGPRS = Data_Error_Fail;
    if (!GPRS_IS_Close(3))
        Statusbits.staGPRS = GPRS_Unline_No_Ready;
    Close_UART2(); //关闭串口2
    return false;
}

/*************************************
Function: GetGMTTimeTask 
Description: 获取UTC任务
Input: 无
Output: 无
 *************************************/
//bool GetGMTTimeTask(void) {
//    u8 RTCCtime[7] = {0x20, 0, 0, 0, 0, 0, 0}; //16-10-28 00:31:37
//    u8 receiveBuffer[50] = {0, 0, 0, 0, 0, 0, 0, 0};
//    time_t nowtime_C = 0;
//    struct tm *nowtime_P = NULL;
//
//    while (LK)//保护机制 GPRS 没有插上 添加提示
//        GPRS_OFF;
//
//    GPRS_ON; //打开GPRS模块  
//    Delay1s(1); //延时100ms
//    if (!ChangeGPRSArg(GPRS_Arg1)) { //修改GPRS参数1
//        Statusbits.staGPRS = GMT_Arg_Error;
//        return false;
//    }
//    GPRS_ON;
//    GPRS_Send(SendON, 12);
//    if (LKIsHigh(GPRS_ON_TIME)) {
//        Delay1s(1); //延时200ms  
//        GPRS_Send(NTP_Message, 48);
//        GPRS_Send(NTP_Message, 48);
//        Delay1s(4); //延时100ms 
//        if (UARTIsGet(BufferRead_UART2, receiveBuffer, 48, GMTHead, 4)) {//最后八位数，整数4位 小数4位
//            //24 03 03 E9 00, 00 13 78 00 00 ,19 F4 0F B3 9C ,F8 DC 15 6A B5, 2C 81 B8 5E 00, 00 00 00 00 00 ,00 00 DC 15 71, 98 B3 0C 4D 19 ,DC 15 71 98 B3 ,0D B9 22 
//            //TR:16-10-28 00:31:37 10 0 0 721.7 UTC(NIST) * ??      
//            nowtime_C = ((u32) receiveBuffer[40] << 24) + ((u32) receiveBuffer[41] << 16)
//                    + ((u16) receiveBuffer[42] << 8) + receiveBuffer[43] - 0x83AA7E80; //获取时间戳
//            nowtime_P = gmtime(&nowtime_C);
//            if (nowtime_P != NULL) {
//                RTCCtime[0] = (u8) DCH((u8) (((nowtime_P->tm_year + 1900) / 100) & 0x00FF)); //20 
//                RTCCtime[1] = (u8) DCH((u8) (nowtime_P->tm_year % 100 & 0x00FF)); //16 
//                RTCCtime[2] = (u8) DCH((u8) (nowtime_P->tm_mon + 1 & 0x00FF)); //月
//                RTCCtime[3] = (u8) DCH((u8) (nowtime_P->tm_mday & 0x00FF)); //日
//                RTCCtime[4] = (u8) DCH((u8) (nowtime_P->tm_hour & 0x00FF)); //小时
//                RTCCtime[5] = (u8) DCH((u8) (nowtime_P->tm_min & 0x00FF)); //分钟
//                RTCCtime[6] = (u8) DCH((u8) (nowtime_P->tm_sec & 0x00FF)); //秒
//                Register2Write(RTCCtime, REG2_Arg_Postion[mi_year], 7);
//                StopRTCC();
//                CheckRTCC();
//                StartRTCC();
//                Statusbits.staGPRS = All_Right;
//                GPRS_Send(SendOFF, 13);
//                GPRS_OFF; //关闭GPRS模块  避免绿灯亮过久 
//                return true;
//            } else
//                Statusbits.staGPRS = GMT_Time_Error;
//        } else
//            Statusbits.staGPRS = GMT_No_Receive;
//    } else
//        Statusbits.staGPRS = GMT_Timeover;
//    GPRS_Send(SendOFF, 13);
//    GPRS_OFF;
//    return false;
//}

//bool ChangeGPRSArg(const u8 * dat) {
//    u8 receiveBuffer[10] = {0, 0, 0};
//    u8 cnt = 0;
//    while (LK)
//        GPRS_OFF;
//    //    GPRS_ON; //打开GPRS模块 
//    if (!GPRS_IS_Ready()) {//等待设备准备好
//        Statusbits.staGPRS = Change_Arg_No_Ready;
//        return false;
//    }
//    do {
//        UART2SendString(dat, 144); //发送修改参数值指令
//        if (cnt++ > 3) {
//            Statusbits.staGPRS = Change_Arg_Error_Fail;
//            break;
//        }
//        Delay1s(1); //延时1s
//    } while (!UARTIsGet(BufferRead_UART2, receiveBuffer, 5, ArgRe, 5)); //如果修改成功
//    //    while (BufferRead_UART2(receiveBuffer)); //串口2的清除缓冲数据
//    Statusbits.staGPRS = All_Right;
//    GPRS_OFF;
//    return true;
//}



