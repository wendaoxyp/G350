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
#include "stdbool.h"
#include "stdio.h"
//#include "ctype.h"
const u8 TX_GPRS_Arg1[144] = {//UTC
    0x2B, 0x54, 0x55, 0x52, 0x4F, 0x4E, 0x47, 0x20, 0x54, 0x45, 0x53, 0x54, 0x57, 0x30, 0xB7,
    0xF6, 0x4A, 0x44, 0xCE, 0x13, 0x30, 0x30, 0x30, 0x0B, 0x18, 0x25, 0x77, 0x00, 0x27, 0x1F,
    0x0B, 0x13, 0x80, 0x05, 0x77, 0x50, 0x0F, 0x30, 0x31, 0x31, 0x3C, 0x00, 0xB4, 0x00, 0x00,
    0x00, 0x30, 0x0D, 0x77, 0x77, 0x77, 0x2E, 0x62, 0x61, 0x69, 0x64, 0x75, 0x2E, 0x63, 0x6F,
    0x6D, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0x05, 0x43, 0x4D, 0x4E, 0x45, 0x54, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x31, 0x0B, 0x18, 0x35, 0x77, 0x68, 0x90, 0x7F, 0x0B,
    0x18, 0x65, 0x71, 0x58, 0x14, 0x9F, 0x0B, 0x13, 0x01, 0x03, 0x60, 0x50, 0x0F, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x9E, 0x47
};
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
const u8 ReceiveOK[6] = "+RECW0";
const u8 UDPHead[2] = {0x41, 0x32};
//const u8 GMTHead[3] = {'T', 'R', ':'};
const u8 GMTHead[4] = {0x24, 0x03, 0x03, 0xE9};
//const u8 SendCH[12] = "+TURONG GPCH";
//u8 Head2[4] = "FAIL";
//u8 gUARTtmp[2]; //用于存放临时变量
extern u8 gAlarmVoltageAdd;
u8 gAlarmZeroLock = 0;
//extern u8 gCurrentSampleCount;

/*************************************
Function: GPRS_Init 
Description: GPRS模块初始化
Input: 无
Output: 无
 *************************************/
void GPRS_Init(void) {
    u8 dat;

    GP_CON_OUT;
    GPRS_OFF;
    ANSAbits.ANSA3 = 0; //数字输入
    LK_IN;
    ANSBbits.ANSB13 = 0; //数字输入
    //    CNPD2bits.CN22PDE = 1; //设置下拉
    dat = LK;
}

static bool RTCCDataIsOK(u8* input, u8 *output) {//UTC时间
    bool b = false;
    if ((*(input + 2) == 0x2D)&&(*(input + 5) == 0x2D)) {
        *output = ((*input - 0x30) << 4) + (*(input + 1) - 0x30);
        *(output + 1) = ((*(input + 3) - 0x30) << 4) + (*(input + 4) - 0x30);
        *(output + 2) = ((*(input + 6) - 0x30) << 4) + (*(input + 7) - 0x30);
        if ((*(input + 11) == 0x3A)&&(*(input + 14) == 0x3A)) {
            *(output + 3) = ((*(input + 9) - 0x30) << 4) + (*(input + 10) - 0x30);
            *(output + 4) = ((*(input + 12) - 0x30) << 4) + (*(input + 13) - 0x30);
            *(output + 5) = ((*(input + 15) - 0x30) << 4) + (*(input + 16) - 0x30);
            b = true;
        }
    }
    return b;
}

bool GPRS_IS_Ready(void) {
    u8 fail_Cnt = 0; // loop_Cnt = 0;
    u8 tmp[5] = {0, 0};
    //    Open_UART2();
    do {
        GPRS_OFF;
        Delay1s(5); //6s
        GPRS_ON;
        Delay1s(1); //6s
        if (fail_Cnt++ > 3) {//上线6次
            GPRS_OFF;
            //            Close_UART2();
            return false;
        }
    } while (!UARTIsGet(BufferRead_UART2, tmp, 2, Ready, 5)); //{//是不是接收到READY
    return true;
}

char GetGPRSBaudRate(void) {
    u8 i;
    RS485_CON = 1;
    printf("\nNow Test:GPRS Baud Rate!!!\n");
    Delay10ms(1);
    RS485_CON = 0;
    //    u8 buf[50];
    for (i = 0; i < 5; i++) {
        RS485_CON = 1; //发送
        printf("BaudRate Test:Try %d!!!\n", i);
        Delay10ms(1);
        RS485_CON = 0; //发送
        //        RS485SendString(, 11);
        SetGPRSBaudRate(i);
        if (GPRS_IS_Ready())
            return i;
    }
    return -1;
}

//void GPRS_Send(const u8*dat, u8 bytes) {
//    u8 cnt = 0;
//    while (cnt++ < 3) {
//        UART2SendString(dat, bytes);
//        Delay1s(1); //延时1s 
//    }
//}

/*************************************
Function: LKIsHigh 
Description: 判断是否上线
Input: 无
Output: 1：发送成功
 *************************************/
bool LKIsHigh(u16 deadline) {
    StartTime3();

    while (gT3Count < deadline) {//50s内上线  
        ClrWdt();
        if (LK) {
            Delay100ms(1);
            if (LK) {
                return true;
            }
        }
    }
    CloseTime3();
    return false;
}

/*************************************
Function: CopUDPTask 
Description: UDP发送采集数据任务通讯任务
Input: 无
Output: 无
 *************************************/
bool CopUDPTask(void) {
    u8 receiveBuffer[48] = {0, 0, 0, 0}; //29+15=44
    u8 FailCount = 0, cnt = 0; // sendCnt = 0;
    //    u8 mi_id_Tmp[8] = {0, 0, 0, 0, 0, 0, 0, 0};

    //    Register2Read(mi_id_Tmp, mi_arg_add[mi_id], 8);

    //    Statusbits.staGPRS = 1;
    RS485_CON = 1;
    printf("\nGPRS Online Test:GPRS CopTest Starting...\n");
    Delay10ms(1);
    RS485_CON = 0;
    while (FailCount++ < 3) {//2次上线
        RS485_CON = 1;
        printf("\nGPRS Online Test:%d\n", FailCount);
        Delay10ms(1);
        RS485_CON = 0;
        GPRS_ON; //T3Delay10ms(100);打开GPRS模块  
        if (!GPRS_IS_Ready())//等待GPRS在状态
        {
            RS485_CON = 1;
            printf("GPRS Online Test:Can't Get Ready!!!\n");
            Delay10ms(1);
            RS485_CON = 0;
            return false;
        }
        //        GPRS_Send(SendON, 12); //发送GPRS_ON
        if (LKIsHigh(GPRS_ON_TIME))//判断LK在60s内是否上线
        {
            RS485_CON = 1;
            printf("GPRS Online Test: Conneted ALi Server\n");
            Delay10ms(1);
            RS485_CON = 0;
            Delay100ms(5); //延时
            UART2SendString2((const u8*) "This is GPRS test context:11223344556677889900");
            RS485_CON = 1;
            printf("GPRS Online Test: Send Data ALi Server\n");
            Delay10ms(1);
            RS485_CON = 0;
            Delay1s(3); //延时4s 必须要等待3s后数据返回
            //最后四个字节没有接受到，中断原因
            for (cnt = 0; cnt < 4; cnt++)
                if (U2STAbits.URXDA == 1) //没有接收到
                    BufferWrite_UART2();
            if (UARTIsGet(BufferRead_UART2, receiveBuffer, 44, UDPHead, 2)) { //获取数据并校验数据     //如果有接收到数据 
                RS485_CON = 1;
                printf("GPRS Online Test:  Receive Data From ALi Server!!!\n");
                Delay10ms(1);
                RS485_CON = 0;
                return true;
            } else {
                RS485_CON = 1;
                printf("GPRS Online Test: Receive None From ALi Server\n");
                Delay10ms(1);
                RS485_CON = 0;
            }
        } else {
            RS485_CON = 1;
            printf("GPRS Online Test:overtime\n");
            Delay10ms(1);
            RS485_CON = 0;
        }
        //        GPRS_Send(SendOFF, 13);
        GPRS_OFF; //关闭GPRS模块  
    }
    //    Statusbits.staGPRS = Data_Error_Fail;
    GPRS_OFF; //重要
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
//                Register2Write(RTCCtime, mi_arg_add[mi_year], 7);
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

bool ChangeGPRSArg(const u8 * dat) {
    u8 receiveBuffer[10] = {0, 0, 0};
    u8 cnt = 0;
    while (LK)//等待GPRS下线
        GPRS_OFF;
    //    GPRS_ON; //打开GPRS模块 
    RS485_CON = 1; //发送
    printf("\nNow Test:Set Arg Test!!!\n");
    Delay10ms(1);
    RS485_CON = 0; //发送
    if (!GPRS_IS_Ready()) {//等待设备准备好
        RS485_CON = 1; //发送
        printf("Set Arg Test:GPRS Is No Ready!!!\n");
        Delay10ms(1);
        RS485_CON = 0; //发送
        return false;
    }
    do {
        UART2SendString(dat, 144); //发送修改参数值指令
        if (cnt++ > 3) {
            RS485_CON = 1; //发送
            printf("Set Arg Test:Arg Send count > 3!!!\n");
            Delay10ms(1);
            RS485_CON = 0; //发送
            //            Statusbits.staGPRS = Change_Arg_Error_Fail;
            break;
        }
        Delay1s(1); //延时1s
        if (UARTIsGet(BufferRead_UART2, receiveBuffer, 5, ReceiveOK, 6)) {
            RS485_CON = 1; //发送
            printf("Set Arg Test:GPRS Arg is Setted !!!\n");
            Delay10ms(1);
            RS485_CON = 0; //发送
            break;
        }
    } while (1); //如果修改成功
    //    printf("Set Arg Test:GPRS Arg is Setted !!!");
    //    while (BufferRead_UART2(receiveBuffer)); //串口2的清除缓冲数据
    //    Statusbits.staGPRS = All_Right;
    GPRS_OFF;
    return true;
}

//bool GetGPRSBaudRate(uint8_t count, uint8_t time) {
//    uint8_t cnt = 0;
//    do {
//        GPRS_OFF;
//        Delay1s(time); //延时一秒
//        GPRS_ON;
//        if ()
//        } while (cnt++ < count);
//}


