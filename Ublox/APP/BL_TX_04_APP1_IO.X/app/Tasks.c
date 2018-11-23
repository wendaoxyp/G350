//#include "Tasks.h"
#include "TX04.h"
#include "DefType.h"
#include <xc.h>

//static volatile uint8_t gCmdType = CMD_NO_CMD;
extern volatile uint8_t gGPRSIsONline; //上线标志位;
//extern volatile uint8_t gTX04WorkMode;
extern volatile Bool gRefreshArg;
extern volatile Bool gMasteadType;
extern volatile Bool gReloadGPRS;
extern volatile Bool gSMSInfo; //参数一
extern GPRS_Arg G350_Arg;
extern const uint8_t TX04_NET_FIND_CODE[];
extern const uint8_t TX04_CONNECT_CODE[];
extern uint16_t GetT1Count(void);
extern void PrintErr(uint8_t);

/***************************************************************************
Function: Task1Upload 
Description: 上线指令
Input: 参数指针
Output: void
Return: none
Others: none
 ***************************************************************************/
Bool Task1Upload(void *arg) {//TX04FCON upload_TX04f) {
    TX04ARG tx04arg = *((TX04ARG*) arg); //获取TX04参数
    uint8_t Ub_online_code = 0, finish_code = 0; //Ublox状态
    Bool sta = False;

    //    if (gTX04Sta == TX04_Sta_TCP_Server_Cop) {//如果是服务端的话，跳过检索网络的指令开始找网络;反之，开始找网络
    //        Ub_online_code = G350_F_NET_SIZE;
    //    } else
    Ub_online_code = Ublox_Find_Network(G350_F_NET_SIZE); //查找网络
    if (Ub_online_code == G350_F_NET_SIZE) {//根据参数的需求，查找数据
        if (tx04arg.SignalQualityEnable == 0x31) {//是否开始信号前侧
            TX04ReadCSQByCMD(UART2SendString); //用户串口返回信号强度
        }
        do {//切换中心参数，不需要重新找基站
            gReloadGPRS = False; //避免一直循环
            gTX04Sta = TX04GetWorkMode(RunArg); //获取工作状态
            if (!TX04SMSArgIsRight(gTX04Sta)) {//短信号码长度判断
                break;
            }
            Ub_online_code = TX04Connect(gTX04Sta, &finish_code); //根据工作模式，开始连接网络
            if (Ub_online_code == finish_code) {//如果上线成功的话，处理数据            
                gGPRSIsONline = 1;
                GLED = 1; //开启上线指示灯
                USER_LK = 1; //LK置高
                TX04ReportMasthead(gTX04Sta); //发送报头
                UART2SendString((uint8_t*) "OK\r\n", 4); //发送提示信息
                Delay100ms(1); //延时一段时间等待灯亮
                TX04DataInterchange(gTX04Sta); //发送数据  
                sta = True;
            } else
                PrintErr(TX04_CONNECT_CODE[Ub_online_code]);
        } while (gReloadGPRS);
    } else {
        PrintErr(TX04_NET_FIND_CODE[Ub_online_code]);
    }
    if (gRefreshArg) {//GPRS下线，如果模块需要重新载入参数的话，标志位清除，并重载参数
        gRefreshArg = 0;
        gSMSInfo = 0;
        CopyDat((uint8_t*) & RunArg, (uint8_t*) & TX04Arg_S, 130); //刷新参数，避免重复进入敦信模式
    }
    gGPRSIsONline = 0; //下线标志清除
    CloseUART1(); //关闭串口 注意顺序，不然会导致UARTERR中断
    CloseUblox(); //关闭Ublox
    //    Delay100ms(20);
    return sta;
}

/***************************************************************************
Function: Task3InitWriteArg
Description: 发送AT命令给Ublox
Input: ss(发送数据地址);cs(对比数据地址);csl(对比数据长度);cnt(操作次数)
Output: void
Return: True:发送成功；False:发送失败
Others: none
 ***************************************************************************/
void Task3InitWriteArg(void) {
    ////    #define Debug_10s
    Bool TECH_is_get = False; //判断是否一直是等待参数写入的状态 与10s的时间做区别
    uint8_t getsize = 0, headsize = 0; //获取到的字节数，数据帧开始识别的位置
    uint8_t Ublox_buf[256]; //接收服务器的数据
    uint8_t gCmdType = CMD_NO_CMD; //清除指令
    uint16_t NowT1Cnt = 0, StartT1Cut = 0;
#ifdef Debug_10s
    DeBug_PrintInfo("start of 10s!!!\r\n");
#endif
    StartT1Cut = GetT1Count(); //获取当前时间
    NowT1Cnt = StartT1Cut;
    do {//如果设定时间没到，已经在循环中
        Idle(); //进入休眠模式            
        getsize = UARTGetDat(BufferRead_UART2, Ublox_buf, sizeof (Ublox_buf), 6); //期望获取到的最小字节数是12->“+TURONG TECH”,期望获取到的时间100ms->12/120
        if (getsize >= 12) {
            headsize = IsGetMasthead(Ublox_buf, getsize); //判断第一个字节 
            if (headsize) {//判断是否获取到+TXYBJT，根据IsGetMasthead返回的位置，如果是0的话，表示没有接收到                                    
                gCmdType = TX04GetCMDType(Ublox_buf, getsize); //判断指令后面的数据
                getsize = 0; //清楚获取数据 
                if (CMDRec_HandleCmd(UART2SendString, gCmdType, Ublox_buf + headsize - 1)) //根据指令返回数据 t通过指令判断是否要退出
                    break;
                if (CMDIsGetVer(gCmdType))//是否是检索指令，那么定时器停止定时，客户可以在一直操作
                    TECH_is_get = True;
            }
        }
        if ((RunArg.ControlMode == TX04_ARG_CONTROL_MODE_HARDWARE) && !TECH_is_get) {//如果是EN控制模式，而且tech指令没有接受到
            NowT1Cnt = GetT1Count();
            if (NowT1Cnt - StartT1Cut > 10)//如果时间大于10s，那么退出
                break;
        }
        gCmdType = CMD_NO_CMD;
    } while (1); //跳出循环，进行拨号上线  上线时间小于0，EN控制模式，跳出循环
#ifdef Debug_10s
    DeBug_PrintInfo("End of 10s!!!\r\n");
#endif
    OpenUblox(); //开启Ublox 
    OpenUART1(); //在打开Ublox避免进入中断 注意顺序，不然会导致UARTERR中断
    LP_Delay(150); //低功耗延时500ms，等待ublox正常开启
}





