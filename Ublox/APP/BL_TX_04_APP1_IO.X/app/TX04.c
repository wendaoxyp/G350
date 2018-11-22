#include "TX04.h"
#include "Flash.h"
#include "config.h"
#include "ublox_g350.h"
#include "UART2.h"

/***************************************************************************
 * Defines
 ***************************************************************************/
const char USER_READY[] = {"READY\r\n"}; //开阀门指令//定义指令的数据
const char TX04_SEND_OFF[] = {"GPOFF\r\n"};
const char TX04_SEND_OFF1[] = {"GPOFF1\r\n"};
const char TX04_SEND_OFF2[] = {"GPOFF2\r\n"};
const char TX04_TXYBJT[] = {"+TXYBJT "}; //TX04在线接收帧头
const char TX04_TURONG[] = {"+TURONG "}; //TX04在线接收帧头
const char TX04_TESTW0_Rec[] = {"+RECW0"};
const char TX04_TESTW2_Rec[] = {"+RECW2"};
const char TX04_TECH_Rec[] = {"DTU Software,VERdowa_v01.07\r\n"};
const char TX04_CMD_ARRY[16][4] = {//指令数组
    "STW0", "STW2", "STR0", "STR2", "TECH",
    "GPON", "GPOF", "GPSQ", "PCH1", "PCH2",
    "GPSM", "GPSS", "GPST", "GRCH", "GROF",
    "GPID"
};
//const char TX04_ERRCODE[] = {"FAIL_"};
const char TX04_DISCONNECT[] = {"DISCONNECT\r\n"}; //TX04在线接收帧头
const char TX04_CSQ[] = {"CSQ"};
const char TX04_TX[] = {"TX:"};
const char TX04_HEARTBEAT[] = {"HEARTBEAT\r\n"};

const unsigned long STORE_ARG1_ADD = 0xA600; //定义参数在程序存储器中的位置
const unsigned long STORE_ARG2_ADD = 0xA700; //定义参数2在程序存储器中的位置
const uint16_t BaudRateArry[] = {4800, 9600, 19200, 1200, 2400}; //波特率

const uint8_t TX04DefualtArg[] = {//默认参数
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x30, 0x0B,
    0x13, 0x84, 0x44, 0x44, 0x44, 0x5F, 0x0B, 0x13, 0x82, 0x22,
    0x22, 0x22, 0x0F, 0x30, 0x31, 0x33, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x30, 0x0D, 0x77, 0x77, 0x77, 0x2E, 0x62, 0x61,
    0x69, 0x64, 0x75, 0x2E, 0x63, 0x6F, 0x6D, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x05, 0x43, 0x4D, 0x4E, 0x45,
    0x54, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x31, 0x0B, 0x13,
    0x12, 0x44, 0x54, 0x11, 0x2F, 0x0B, 0x18, 0x86, 0x21, 0x44,
    0x20, 0x4F, 0x0B, 0x13, 0x01, 0x03, 0x60, 0x50, 0x0F, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x53, 0x41
};

extern enum CMD_TP cmd_tp; //定义指令顺序
volatile Bool gRefreshArg = False; //
volatile Bool gMasteadType = False; //是否是报头
volatile Bool gReloadGPRS = False; //
volatile Bool gSMSInfo = False; //参数一
extern volatile uint16_t gT1Count_Reset;
extern volatile uint16_t gT1Count_Heart;
extern volatile uint16_t gT1Count_Listen;
extern const char BL_REMOTE_PASSWD[]; //远程升级密码TR_10_

/***************************************************************************
 * States
 ***************************************************************************/

enum argposition {
    ip = 0, port = 4, workmode = 6, tcp_udp = 7, dnsmode = 8,
    smstargetnumber1length = 9, smstargetnumber1 = 10,
    smsmonitoringcenternumber1length = 16, smsmonitoringcenternumber1 = 17,
    signalqualityenable = 23, controlmode = 24,
    baudrate = 25, restarttime = 26, hearttime = 28,
    listentime = 30, csmode = 32, dnsdomainnamelength = 33,
    dnsdomainname = 34, apnnamelength = 65, apnname = 66,
    reporten = 97, simnumberlength = 98, simnumber = 99, smstargetnumber2length = 105,
    smstargetnumber2 = 106, smsmonitoringcenternumber2length = 112,
    smsmonitoringcenternumber2 = 113, connectcnt = 119, reserve = 120, end = 128//添加结束字节数
};
enum argposition p;
/***************************************************************************
 * Statement
 ***************************************************************************/
/*volatile */TX04ARG TX04Arg_S;
/*volatile */TX04ARG TX04Arg2_S; //结构体
/*volatile */TX04ARG RunArg; //结构体
volatile Bool gExitSleep = False;
volatile uint8_t gGPRSIsONline = 0; //上线标志位
volatile uint8_t gTX04Sta; //GPRS状态 就绪状态  TCP状态 UDP状态 GSM状态
extern const char Set_SMS_NEW_TIP[12];
//确定运行的参数
const uint8_t TX04_NET_FIND_CODE[G350_F_NET_SIZE] = {2, 1, 0, 5, 0}; //找基站错误提示
const uint8_t TX04_CONNECT_CODE[G350_TCP_Client_SIZE] = {4, 0, 0, 0, 0, 0, 6, 0}; //找TCP连接错误提示


/***************************************************************************
 * Code
 ***************************************************************************/

/***************************************************************************
Function: EnsureRunArg
Description: 载入GPRS参数
Input:参数地址
Output: 
Return: 
Others: none
 ***************************************************************************/
static void EnsureRunArg(void* tx04arg) {
    uint8_t *ptr;

    ptr = (uint8_t*) tx04arg; //获取参数的地址
    CopyDat((uint8_t*) & RunArg, ptr, 130); //复制数据 必须包含CRC 用于GPCH指令
}

/***************************************************************************
Function: EnsureRunArg
Description: 载入GPRS参数
Input:参数地址
Output: 
Return: 
Others: //33H?1200bps//34H?2400bps//30H?4800bps//31H?9600bps//32H?19200bp 
 ***************************************************************************/
void ChangeBaudRate(void) {
    uint16_t uart2_baud;
    if (RunArg.BaudRate > 0x34 && RunArg.BaudRate < 0x30)
        uart2_baud = 1200;
    else
        uart2_baud = BaudRateArry[RunArg.BaudRate - 0x30];
    U2BRG = OSC_Freq / uart2_baud / 4 - 1; //改变波特率
}

/***************************************************************************
Function: TX04_Init
Description: TX04产品初始化1
Input:
Output:
Return:
Othe1rs:
 ***************************************************************************/
void TX04_Init(void) {
    OSCILLATOR_Init(); //初始化时钟   
    PIN_MANAGER_Init(); //初始化IO
    INTERRUPT_Init(); //初始化中断
    TMR1_Init(); //定时器1初始化 用于快速`指令
    TMR2_Init(); //定时器2初始化 用于进入睡眠
    //    TMR3_Init(); //定时器3初始化 用于重启和心跳包
    UART1_Init(); //初始化模组通讯
    //    INT0_Init(); //初始化外部中断0 下降延触发
    INT1_Init(); //初始化外部中断1 下降延触发 分压电阻，判断电源电压，如果电压低复位设备
    TX04GetRunArg(); //确定运行参数
    UART2_Init(); //初始化用户通讯 注意必须在GetRunArg后面，避免中断读取错误 避免读取写入参数错误
    U2TXREG = '\0'; //填充一个字节，避免第一个数据乱码
    StartTMR1(); //启动定时器:用于心跳时间 重启时间、监听时间、强制短信5s
}

/***************************************************************************
Function: TX04Sleep
Description: TX04进入睡眠模式
Input:
Output:
Return:
Others:
 ***************************************************************************/
void TX04Sleep(void) {//空闲任务 配置为上处理 外设 IO口上 处理
    //关闭UART1，保存设置，进入休眠时候，设置IO口为输出0；退出休眠时候，设置串口通讯
    GLED = 0; //
    //开启深度睡眠
    //禁止保持低压稳压器； RETEN（RCON<12>） = 0， LPCFG（FPOR<2>） = 1。
    //使能保持低压稳压器； RETEN（RCON<12>） = 1， LPCFG（FPOR<2>） = 0。
    RCONbits.RETEN = 0;
    RCONbits.VREGS = 0; //快速唤醒    
    while (!U1STAbits.RIDLE); //等待接收完成
    while (!U2STAbits.RIDLE); //等待接收完成
    U1MODEbits.WAKE = 1; //中断唤醒设备
    U2MODEbits.WAKE = 1;
    gExitSleep = 0;
    while (!gExitSleep) {//等待中断唤醒设备
        Sleep(); //要屏蔽定时器1的中断
    }
    U1MODEbits.WAKE = 0;
    U2MODEbits.WAKE = 0;
    //指令唤醒设备  开启指示灯
    GLED = 1;
    Delay100ms(1); //等待电压稳定
}

/***************************************************************************
Function: TCP_Bootloader
Description: 远程升级，进入bootloader模式
Input:缓冲数据，数据长度
Output:
Return:
Others:
 ***************************************************************************/
static void TCP_Bootloader(uint8_t *Ublox_2_buf, uint8_t getsize2) {
    uint8_t cnt;
    if (Str_Find_Head(Ublox_2_buf, BL_REMOTE_PASSWD, getsize2, 6)) {
        for (cnt = 0; cnt < 10; cnt++) {//指示灯提示 100ms闪烁 5次
            GLED ^= 1;
            Delay100ms(1);
        }
        GLED = 0;
        T1CONbits.TON = 0; //关闭定时器1，避免重启设备和发送心跳包
        if (BootLoader()) {
            UbloxCloseTCPClient(); //通过AT指令关闭模块                
            USER_LK = 0; //LK置低
            GLED = 0;
            UART2SendString((uint8_t*) TX04_SEND_OFF, 7);
            gGPRSIsONline = 0;
            INTCON1bits.ADDRERR = 1; //产生数学错误中断，复位  //IFS1bits.INT1IF = 1; //触发中断，进入复位
        }
        T1CONbits.TON = 1; //开启定时器1，继续开始重启计算时间和发送心跳包时间
    }
}

/***************************************************************************
Function: TCP_IsDisconnect
Description: TCP客服端模式下，服务端是否断开(返回DISCONNECT)
Input:缓冲数据，数据长度
Output: 是否断开
Return: 是否断开
Others: none
 ***************************************************************************/
static Bool TCP_IsDisconnect(uint8_t* Ublox_2_buf, uint8_t getsize2) {
    Bool is_disconnnect = False;

    if (Str_Find_Head(Ublox_2_buf, "D", getsize2, 1) > 0) {//如果获取到+字符 hjksdfa+TXYBJT TECH
        getsize2 += UARTGetDat(BufferRead_UART1, Ublox_2_buf + getsize2, 0xff - getsize2, 8); //120
        if (Str_Find_Head(Ublox_2_buf, TX04_DISCONNECT, getsize2, sizeof (TX04_DISCONNECT) - 1)) {//如果连接监控中心失败，中心主动关闭设备
            PrintErr(15); //打印错误提示FAIL15
            is_disconnnect = True;
        }
    }
    return is_disconnnect;
}

/***************************************************************************
Function: OnlineHandleData
Description: 在线处理数据，包含TCP客服端，服务端（待添加），UDP客服端，短信
Input:模式mode
Output: 是否有通讯
Return: 是否有通讯
Others: none
 ***************************************************************************/
static Bool OnlineHandleData(uint8_t mode) {
    CMDTYPE cmdtype = 0; //定义返回指令类型
    uint16_t getsize = 0, headsize = 0; //, opcnt = 1; //, cnt;
    uint8_t Ublox_buf[1024]; //用于用户的交互
    uartsendstring senddat_f, reccmd_f;
    BufferRead_UARTn readbuf_f;
    Bool has_Cop = False, isneedget = True;

    switch (mode) {
        case TX04_GSM_Work_Mode_S:
        {
            reccmd_f = UART2SendString;
            senddat_f = GSMSendMessage; //GSM
            readbuf_f = BufferRead_UART2;
            break;
        }
        case TX04_GSM_Work_Mode_R:
        {
            reccmd_f = SMSWriteStrByCmd; //发送CMD
            senddat_f = SMSWriteRecUser; //修改
            readbuf_f = BufferRead_UART1;
            getsize = UbloxSMSGetURC(Ublox_buf, sizeof (Ublox_buf)); //获取有效数据
            isneedget = False;
            break;
        }
        case TX04_GPRS_UDP_Work_Mode_S:
        {
            reccmd_f = UART2SendString;
            senddat_f = UDPSendDat2Sever;
            readbuf_f = BufferRead_UART2;
            break;
        }
        case TX04_GPRS_UDP_Work_Mode_R:
        {
            reccmd_f = UDPWriteStrByCmd;
            senddat_f = UART2SendString;
            readbuf_f = BufferRead_UART1;
            getsize = UbloxUDPGetURC(Ublox_buf, sizeof (Ublox_buf)); //获取有效数据
            isneedget = False;
            break;
        }
        case TX04_GPRS_TCP_Work_Client_Mode_S:
        {
            reccmd_f = UART2SendString;
            senddat_f = UART1SendString;
            readbuf_f = BufferRead_UART2;
            break;
        }
        case TX04_GPRS_TCP_Work_Client_Mode_R:
        {
            reccmd_f = UART1SendString;
            senddat_f = UART2SendString;
            readbuf_f = BufferRead_UART1;
            break;
        }
    }
    //    建议60ms刷新，时间太长，大数据发送和接收的时候，容易导致TCP接收数据丢失，缓冲区域数据溢出
    if (isneedget)//是否需要通过串口直接获取数据，
        getsize = UARTGetDat(readbuf_f, Ublox_buf, sizeof (Ublox_buf), 6); //获取数据 

    //    if (Str_Find_Head(Ublox_buf, "+", getsize, 1) > 0) {//如果获取到+字符 +TXYBJT TECH12           
    //        getsize += UARTGetDat(readbuf_f, Ublox_buf + getsize, sizeof (Ublox_buf) - getsize, 12); //120
    //    }
    if (getsize) {//添加字节判断，提高刷新效率，其他模式下可能存在问题
        if (mode == TX04_GPRS_TCP_Work_Client_Mode_R) {
            if (TCP_IsDisconnect(Ublox_buf, getsize)) { //附加程序 判断服务端是否关闭
                gGPRSIsONline = 0;
                return True; //TCP服务端是否关闭连接点，隐性关闭模块,有通讯，不需要进入休眠模式
            } else
                TCP_Bootloader(Ublox_buf, getsize); //判断远程远程设计
        }
        //判断是否是指令 以检索指令为例
        headsize = IsGetMasthead(Ublox_buf, getsize);
        if (headsize) {//寻找+TXYBJT
            cmdtype = TX04GetCMDType(Ublox_buf, getsize); //判断指令后面的数据;  
            if (CMDRec_HandleCmd(reccmd_f, cmdtype, Ublox_buf + headsize - 1)) {
                ClearT1ArgCnt();
                gGPRSIsONline = 0;
            }
            has_Cop = True; //存在数据交互
        } else {
            if (getsize) {//如果接受到字节数据,发送数据给监听中心
                senddat_f(Ublox_buf, getsize);
                has_Cop = True;
            }
        }
    }
    return has_Cop;
}

/*************************************
 * Function: GSMCop5s
 * Description: 写数据到Flash中
 * Input:参数地址，串口发送函数，接收到的数据
 * Output: 
 * Note:参数1和参数2在同一块区域内，所以擦除的话，先要读取另外一个参数，然后擦除
 *************************************/
static Bool GSMCop5s(const uint8_t smsinfo) {//Bool=True:表示通讯任务结束
    uint8_t getsize = 0, smsinfo_tmp = gSMSInfo;
    uint8_t Ublox_buf[256]; //用于用户的交互
    uint16_t delay_time = gT1Count2 + 6;

    //将运行的参数1参数设置身边number，和number_size
    gSMSInfo = smsinfo; //隐式表达
    while (gT1Count2 <= delay_time) {//TCP发送数据   轮寻查找  
        // ********************(0)********************用户端的发送数据值服务器
        GSMSendMessage(Ublox_buf, getsize);
        // ********************(1)********************服务端的接收数据从服务器
        getsize = UbloxSMSGetURC(Ublox_buf, getsize); //获取有效数据
        if (getsize)
            SMSWriteStrByCmd(Ublox_buf, getsize);
    }
    //运行完毕后，还原参数1的短信参数
    gSMSInfo = smsinfo_tmp;
    return True;
}

/*************************************
 * Function: TX04WriteArgByCMD
 * Description: 写数据到Flash中
 * Input:参数地址，串口发送函数，接收到的数据
 * Output: 
 * Note:参数1和参数2在同一块区域内，所以擦除的话，先要读取另外一个参数，然后擦除
 *************************************/
Bool TX04WriteArgByCMD(const uint32_t argadd, uartsendstring uart, uint8_t * Ublox_buf) {
    uint8_t Send_Buf[300];
    uint16_t offset = 0; // 128;
    uint8_t save_arg1_Buf[520];
    uint8_t save_arg2_Buf[520];
    uint8_t cnt, cnt1;
    uint32_t other_arg = argadd;
    Bool isArg1 = STORE_ARG1_ADD == argadd;
    char *send_ptr;
    TX04ARG *arg_ptr;

    if (CRCIsRight(Ublox_buf, 128, Ublox_buf + 128)) {//判断CRC校验是否正确        
        other_arg = (isArg1) ? STORE_ARG2_ADD : STORE_ARG1_ADD; //判断接下来要写参数的位置 
        send_ptr = (isArg1) ? (char *) TX04_TESTW0_Rec : (char *) TX04_TESTW2_Rec;
        arg_ptr = (isArg1) ? &TX04Arg_S : &TX04Arg2_S; //设置参数 写入Flash
        CopyDat(arg_ptr, Ublox_buf, 130); //设置参数 写入Flash
        offset = StrLen(TX04_TESTW0_Rec);
        CopyDat(Send_Buf, send_ptr, offset); //赋值返回的开头数据

        ClearDat(save_arg1_Buf, 0xFF, 512); //
        ClearDat(save_arg2_Buf, 0xFF, 512); //

        ReadArgFromFlash(other_arg, save_arg2_Buf, 176); //在同一区域内，擦除导致数据丢失，故先读取另外一个参数
        Erase(0, STORE_ARG1_ADD); //擦除
        for (cnt = 0, cnt1 = 0; cnt < 173; cnt += 4, cnt1 += 3) {
            CopyDat(save_arg1_Buf + cnt, Ublox_buf + cnt1, 3); //拷贝参数一
            *(save_arg1_Buf + cnt + 3) = 0x00;
        }
        save_arg1_Buf[cnt++] = *(Ublox_buf + cnt1++); //最后4个字节
        save_arg1_Buf[cnt++] = *(Ublox_buf + cnt1);
        save_arg1_Buf[cnt++] = 0x00;
        save_arg1_Buf[cnt] = 0x00;
        WriteFlashByRow(argadd, save_arg1_Buf, 1); //要保存的参数写入FLash
        WriteFlashByRow(other_arg, save_arg2_Buf, 1); //备份的另外一个参数写入FLash        

        if ((gTX04Sta == TX04_Sta_GSM_Cop)&&(uart != UART2SendString))//短信返回参数内容的话，需要拆分为字符串    
            offset += Hex2Char(Ublox_buf, 130, Send_Buf + offset);
        else {
            CopyDat(Send_Buf + offset, Ublox_buf, 130); //赋值参数 行CRC
            offset += 130;
        }
        CopyDat(Send_Buf + offset, "\r\n", 2);
        offset += 2;
        uart(Send_Buf, offset); //发送数据
        Delay100ms(5); //兼容UDP模式
        return True;
    }
    return False;
}

/*************************************
 * Function: TX04ReadArgByCMD
 * Description: 读取参数通过指令
 * Input:串口发送函数、指令、发送的数据
 * Output: 
 * Note:
 *************************************/
void TX04ReadArgByCMD(uartsendstring uart, CMDTYPE cmd, TX04ARG * tx04arg) {
    uint8_t Send_Buf[300]; //, Dat_Buf[150];
    uint16_t offset = StrLen(TX04_TESTW2_Rec);

    if (cmd == CMD_TESTR2)
        CopyDat(Send_Buf, TX04_TESTW2_Rec, offset); //生成发送数据
    else
        CopyDat(Send_Buf, TX04_TESTW0_Rec, offset); //生成发送数据
    //如果短信下载，而且是短信平台发（手机）发送读取参数指令的话
    if ((gTX04Sta == TX04_Sta_GSM_Cop)&&(uart != UART2SendString))
        offset += Hex2Char((uint8_t*) tx04arg, 130, Send_Buf + offset);
    else {//客户端获取
        CopyDat(Send_Buf + offset, tx04arg, 130); //设置参数
        offset += 130;
    }
    CopyDat(Send_Buf + offset, "\r\n", 2);
    offset += 2;
    uart(Send_Buf, offset); //发送数据
    //    Delay10ms(1);
}
//通过指令读取软件版本号

/***************************************************************************
Function: TX04ReadSofewareVersionByCMD
Description: 发送AT命令给Ublox
Input: v
Output: void
Return: True:发送成功；False:发送失败
Others: step不能大于Ublox_F_NET_ATTACHE（5）
 ***************************************************************************/
void TX04ReadSofewareVersionByCMD(uartsendstring uart, Bool sta) {
    uint8_t tmp[40], bytes = sizeof (TX04_TXYBJT) - 1;

    if (sta)
        CopyDat(tmp, (uint8_t*) TX04_TXYBJT, bytes); //发送数据
    else
        CopyDat(tmp, (uint8_t*) TX04_TURONG, bytes); //发送数据  
    CopyDat(tmp + bytes, (uint8_t*) TX04_TECH_Rec, sizeof (TX04_TECH_Rec) - 1); //发送数据
    bytes += sizeof (TX04_TECH_Rec) - 1;
    uart(tmp, bytes);
}

/***************************************************************************
Function: TX04ReadCSQByCMD
Description: 发送AT命令给Ublox
Input: 输入
Output: void
Return: True:发送成功；False:发送失败
Others: step不能大于Ublox_F_NET_ATTACHE（5）
 ***************************************************************************/
void TX04ReadCSQByCMD(uartsendstring uart) {

    uint8_t tmp[15], bytes = sizeof (TX04_CSQ) - 1;

    CopyDat(tmp, TX04_CSQ, bytes); //复制CSQ
    tmp[bytes++] = '_';
    tmp[bytes++] = ((((uint8_t) G350_Arg.CSQ[0]) - 0x30) << 4)+(((uint8_t) G350_Arg.CSQ[1]) - 0x30);
    tmp[bytes++] = '\r'; //(TX04Cmd.CSQ & 0x0f) + 0x31;
    tmp[bytes++] = '\n'; //(TX04Cmd.CSQ & 0x0f) + 0x31;
    uart(tmp, bytes);
}

/***************************************************************************
Function: TX04ReadLocInfoByCMD
Description: 发送AT命令给Ublox
Input: 输入
Output: void
Return: True:发送成功；False:发送失败
Others: step不能大于Ublox_F_NET_ATTACHE（5）
 ***************************************************************************/
void TX04ReadLocInfoByCMD(uartsendstring uart) {

    uint8_t tmp[30], bytes = sizeof (TX04_TX) - 1, copy_size = sizeof (G350_Arg.LAC);

    CopyDat(tmp, TX04_TX, bytes);
    CopyDat(tmp + bytes, G350_Arg.LAC, copy_size);
    bytes += copy_size;
    tmp[bytes++] = ',';
    tmp[bytes++] = '\"';
    CopyDat(tmp + bytes, RunArg.APNName, RunArg.APNNameLength);
    bytes += RunArg.APNNameLength;
    tmp[bytes++] = '\"';
    tmp[bytes++] = '\r';
    tmp[bytes++] = '\n';
    uart(tmp, bytes);
}

/***************************************************************************
Function: TX04ReadSIMIDByCMD
Description: 发送AT命令给Ublox
Input: 输入
Output: void
Return: True:发送成功；False:发送失败
Others: step不能大于Ublox_F_NET_ATTACHE（5）
 ***************************************************************************/
void TX04ReadSIMIDByCMD(uartsendstring uart) {//打印获取ICCID

    uint8_t tmp[30], bytes = sizeof (TX04_TX) - 1, copy_size = sizeof (G350_Arg.ICCID);

    CopyDat(tmp, TX04_TX, bytes);
    tmp[bytes++] = '\"';
    CopyDat(tmp + bytes, G350_Arg.ICCID, copy_size);
    bytes += copy_size;
    tmp[bytes++] = '\"';
    tmp[bytes++] = '\r';
    tmp[bytes++] = '\n';
    uart(tmp, bytes);
}

/***************************************************************************
Function: TX04GetArgByDialing
Description: 下线 通过AT指令获取网络参数
Input:参数
Output: 是否获取成功
Return: 
Others: none
 ***************************************************************************/
Bool TX04GetArgByDialing(uint8_t arg) {//通过拨号获取ICCID，下线状态发送+TXYBJT GPID
    Bool b_sta = False; //申明状态变量
    uint8_t step = 0;

    OpenUblox(); //开启Ublox 
    OpenUART1(); //在打开Ublox避免进入中断
    Delay100ms(15); //等待设备完全开启
    step = Ublox_Find_Network(arg); //拨号获取
    if (step == arg) {
        b_sta = True;
        switch (arg) {
            case G350_GET_CCID:
                TX04ReadSIMIDByCMD(UART2SendString);
                break;
            case G350_GET_CSQ:
                TX04ReadCSQByCMD(UART2SendString);
                break;
            case G350_GET_LOC:
                TX04ReadLocInfoByCMD(UART2SendString);
                break;
        }
    }
    CloseUART1(); //关闭串口1
    CloseUblox(); //关闭Ublox 
    Delay100ms(15); //等待设备完全关闭
    UART2SendString((uint8_t*) USER_READY, 7); //发送就绪状态

    return b_sta;
}

/***************************************************************************
Function: IntoGSM5S 
Description: GPRS进入短信模式
Input:模式mode 中心参数smsinfo
Output:进入成功
Return:
Others:
 ***************************************************************************/
static Bool IntoGSM5S(const uint8_t mode, const uint8_t smsinfo) {//uint8_t sta) {
    Bool sta = False, ready_enter = False;
    uint8_t sms_info[20] = {"ENTER_SMS1\r\n"};

    if (smsinfo)//如果是短信2的话 smsinfo=1
        sms_info[9] = smsinfo + 0x31;
    switch (mode) {
        case TX04_Sta_TCP_Cop:
        {
            if (UbloxSwitchFlow(DATA2CMD))
                ready_enter = True;
            break;
        }
        case TX04_Sta_UDP_Cop:
        {
            ready_enter = True;
            break;
        }
        case TX04_Sta_GSM_Cop:
        {
            UART2SendString((uint8_t*) sms_info + 6, 6); //提示切换成功
            gSMSInfo = smsinfo;
            sta = True;
            break;
        }
    }
    //是否是命令模式，并且切换到短信模式成功
    if (ready_enter && (Ublox_GSM_Dialing(G350_GSM_Client_SIZE) == G350_GSM_Client_SIZE)) { //切换到短信模式
        UART2SendString(sms_info, 12); //提示切换成功
        USER_LK = 0; //LK置低
        GLED = 1; //绿灯亮
        if (GSMCop5s(smsinfo)) {
            //如果是UDP模式，返回通讯成功；如果是TCP模式，切换到数据模式，返回通讯成功        
            if ((mode == TX04_Sta_UDP_Cop) ||
                    ((mode == TX04_Sta_TCP_Cop)&& (UbloxSwitchFlow(CMD2DATA))))//切换中心，切换到透传模式  ~+++
                sta = True;
        }
        USER_LK = 1; //LK置高
        GLED = 0; //绿灯灭
    }
    return sta;
}

/***************************************************************************
Function: LED_Blink 
Description: 控制LED闪烁
Input: 次数，间隔时间
Output:
Return:
Others:间隔时间单位100ms
 ***************************************************************************/
void LED_Blink(uint8_t Cnt, uint8_t Dly100ms) {
    uint8_t cnt;

    GLED = 1;
    for (cnt = 0; cnt < Cnt; cnt++) {
        Delay100ms(Dly100ms); //避免硬件上的重复进入该中断
        GLED ^= 1; //消耗电容C22电量，EN下线
    }
    GLED = 0; //最后一定要加，避免奇数情况下，灯常亮
}

/***************************************************************************
Function: IsGetMasthead 
Description: 判断是是否是报头//判断帧头是否是TXYBJT,
Input: 参数指针，数据字节数
Output:返回所在的字节位置+1
Return: 字节数
Others: none
 ***************************************************************************/
uint8_t IsGetMasthead(const uint8_t * Ublox_buf, const uint8_t bytes) {
    uint8_t getsize;

    gMasteadType = 1; //是TXYBJT
    getsize = Str_Find_Head(Ublox_buf, TX04_TXYBJT, bytes, sizeof (TX04_TXYBJT) - 1);
    if (!getsize) {
        getsize = Str_Find_Head(Ublox_buf, TX04_TURONG, bytes, sizeof (TX04_TURONG) - 1);
        gMasteadType = 0; //是TURONG
    }
    return getsize;
}

/*************************************
Function: TX04GetCMDType 
Description: 获取数据总的指令类型
Input: 字符串指针Ublox_buf 字符串长度bytes 
Output: 数据类型代号
 *************************************/
CMDTYPE TX04GetCMDType(const uint8_t* Ublox_buf, const uint8_t bytes) {
    int8_t cnt;
    for (cnt = sizeof (TX04_CMD_ARRY); cnt >= 0; cnt--) {//debug查看是否是15个数组
        if (Str_Find_Head(Ublox_buf, TX04_CMD_ARRY[cnt], bytes, 4)) {
            return cnt;
        }
    }
    return CMD_NO_CMD;
}

/*************************************
Function: CMDRec_HandleCmd 
Description:根据对应的指令，返回提示信息，并根据指令，判断GPRS是否要重启 或是重新拨号
Input: 串口n接收函数uart，指令类型cmdtype，字符串指针Ublox_buf 
Output: 是否需要重启
 *************************************/
Bool CMDRec_HandleCmd(uartsendstring uart, CMDTYPE cmdtype, uint8_t * Ublox_buf) {//指令回复
    uint8_t sta = gTX04Sta;
    Bool is_need_restart = False; // isArg1 = False;
    TX04ARG RunArg1;
    TX04ARG* runarg = &RunArg1;

    switch (cmdtype) {
        case CMD_TESTW0:
        {
            if (TX04WriteArgByCMD(STORE_ARG1_ADD, uart, Ublox_buf + 14)) //发送写参数1指令
            {
                EnsureRunArg(&TX04Arg_S); //设置运行参数
                switch (sta) {
                    case TX04_Sta_Ready:
                    {//如果是就绪状态下写入参数一
                        UART2SendString((uint8_t*) USER_READY, 7); //返回提示
                        break;
                    }
                    case TX04_Sta_TCP_Cop://注意 不能添加break
                    {
                        UbloxCloseTCPClient(); //通过AT指令关闭模块
                    }
                    default:
                    {
                        is_need_restart = True;
                        USER_LK = 0; //LK置低
                        GLED = 0;
                        UART2SendString((uint8_t*) TX04_SEND_OFF, 7);
                        break;
                    }
                }
                ChangeBaudRate(); //改变波特率
            }
            break;
        }
        case CMD_TESTW2:
        {
            if (TX04WriteArgByCMD(STORE_ARG2_ADD, uart, Ublox_buf + 14)) //发送写参数2指令
            {
                switch (sta) {
                    case TX04_Sta_Ready:
                    {//如果是就绪状态下写入参数一
                        UART2SendString((uint8_t*) USER_READY, 7); //返回提示
                        break;
                    }
                    case TX04_Sta_TCP_Cop://注意 不能添加break
                    {
                        UbloxCloseTCPClient(); //通过AT指令关闭模块
                    }
                    default:
                    {
                        is_need_restart = True;
                        USER_LK = 0; //LK置低
                        GLED = 0;
                        UART2SendString((uint8_t*) TX04_SEND_OFF, 7);
                        break;
                    }
                }
            }
            break;
        }
        case CMD_TESTR0:
        {
            TX04ReadArgByCMD(uart, CMD_TESTR0, &TX04Arg_S);
            break;
        }
        case CMD_TESTR2:
        {
            TX04ReadArgByCMD(uart, CMD_TESTR2, &TX04Arg2_S);
            break;
        }
        case CMD_TECH:
        {
            TX04ReadSofewareVersionByCMD(uart, gMasteadType);
            break;
        }
        case CMD_GPON:
        {
            if (sta == TX04_Sta_Ready) {//跳出初始化循环  ramark 修改才函数参数 以及应用该函数GPOFF指令有问题
                is_need_restart = True;
            }
            break; //外部程序跳出，进入拨号模式
        }
        case CMD_GPOF:
        {
            if (TX04IsWorkSta(sta)) {
                if ((sta == TX04_Sta_TCP_Cop)) {//如果是TCP模式
                    UbloxCloseTCPClient(); //通过AT指令关闭模块                    
                }
                USER_LK = 0; //LK置低
                UART2SendString(TX04_SEND_OFF, 7);
                LED_Blink(6, 5);
                is_need_restart = True;
            }
            break;
        }
        case CMD_GPSQ:
        {
            if (TX04IsWorkSta(sta)) //如果是拨号状态或是GPRS工作模式
                TX04ReadCSQByCMD(uart); //发送信号强度
            else if (sta == TX04_Sta_Ready) //如果是就绪状态的话，就需要拨号上线
                TX04GetArgByDialing(G350_GET_CSQ);
            break;
        }
        case CMD_GPCH1:
        {
            if (sta == TX04_Sta_Ready) {//如果是就绪状态
                UART2SendString(TX04_SEND_OFF1, sizeof (TX04_SEND_OFF1) - 1); //发送GPOFF1
                EnsureRunArg(&TX04Arg_S);
                ChangeBaudRate();
                UART2SendString(USER_READY, sizeof (USER_READY) - 1); //8字节，方便客户判断READY\r\n
                is_need_restart = True; //需要重启模块
            }
            if (TX04IsWorkSta(sta)) {//如果是工作模式                          
                UbloxCloseTCPClient(); //如果是TCP模式，先关闭连接点
                UbloxDisablePSD(); //切换到命令模式
                UART2SendString(TX04_SEND_OFF1, sizeof (TX04_SEND_OFF1)); //发送GPOFF1
                EnsureRunArg(&TX04Arg_S);
                ChangeBaudRate(); //改变波特率
                gReloadGPRS = True;
                is_need_restart = True;
            }
            break;
        }
        case CMD_GPCH2:
        {
            if ((TX04Arg2_S.Port != 0)&&(TX04Arg2_S.IP[0] + TX04Arg2_S.IP[1] + TX04Arg2_S.IP[2] + TX04Arg2_S.IP[3] != 0)) {//如果参数二是无效参数（IP：0,0,0,0 Port:0）
                if (sta == TX04_Sta_Ready) {//如果是就绪状态
                    UART2SendString(TX04_SEND_OFF2, sizeof (TX04_SEND_OFF2) - 1); //发送GPOFF2
                    EnsureRunArg(&TX04Arg2_S);
                    ChangeBaudRate();
                    UART2SendString(USER_READY, sizeof (USER_READY) - 1); //8字节，方便客户判断READY\r\n
                    is_need_restart = True; //需要重启模块
                }
                if (TX04IsWorkSta(sta)) {//如果是工作模式                              
                    UbloxCloseTCPClient(); //如果是TCP模式，先关闭连接点
                    UbloxDisablePSD(); //切换到命令模式
                    UART2SendString(TX04_SEND_OFF2, sizeof (TX04_SEND_OFF2) - 1); //发送GPOFF2
                    EnsureRunArg(&TX04Arg2_S);
                    ChangeBaudRate(); //改变波特率
                    gReloadGPRS = True;
                    is_need_restart = True;
                }
            }
            break;
        }
        case CMD_GPSM:
        {
            if (sta == TX04_Sta_Ready) {
                CopyDat((uint8_t*) runarg, (uint8_t*) & TX04Arg_S, 130); //复制数据
                gSMSInfo = 0; //发送参数一
                runarg->WorkMode = TX04_ARG_WORK_MODE_GSM; //工作模式设置为短信模式
                EnsureRunArg(runarg); //确认运行参数
                gRefreshArg = 1; //就绪，发送强制短信，模块下线，需要重新载入参数
                is_need_restart = True; //需要重启模块
            } else {
                IntoGSM5S(sta, 0); //进入强制短信模式
            }
            break;
        }
        case CMD_GPSS:
        {
            if (sta == TX04_Sta_Ready) {
                CopyDat((uint8_t*) runarg, (uint8_t*) & TX04Arg_S, 130); //复制数据
                gSMSInfo = 1; //发送参数二
                runarg->WorkMode = TX04_ARG_WORK_MODE_GSM; //工作模式设置为短信模式
                EnsureRunArg(runarg); //确认运行参数
                gRefreshArg = 1; //就绪，发送强制短信，模块下线，需要重新载入参数
                is_need_restart = True;
            } else {
                IntoGSM5S(sta, 1); //进入强制短信模式
            }
            break;
        }
        case CMD_GPST:
        {
            if (TX04IsWorkSta(sta))//如果是拨号转台或是GPRS工作模式
                TX04ReadLocInfoByCMD(uart);
            else if (sta == TX04_Sta_Ready) //如果是就绪状态的话，就需要拨号上线
                TX04GetArgByDialing(G350_GET_LOC);
            break;
        }
        case CMD_GPID://获取ID
        {
            if (TX04IsWorkSta(sta))//如果是拨号转台或是GPRS工作模式
                TX04ReadSIMIDByCMD(uart);
            else if (sta == TX04_Sta_Ready) //如果是就绪状态的话，拨号获取
                TX04GetArgByDialing(G350_GET_CCID);

            break;
        }
    }
    return is_need_restart;
}

/***************************************************************************
Function: TX04Connect
Description: 根据工作模式，开始拨号连接
Input: 工作模式（workmode）
Output: Ublox的状态[uint8_t]
Return: Ublox的状态[uint8_t]
Others: uint8_t的低级中添加了（Ublox_User_ERR0），便于统一管理错宏定义
 ***************************************************************************/
uint8_t TX04Connect(uint8_t workmode, uint8_t * finish_code) {//开始拨号连接
    uint8_t sta = 0;
    switch (workmode) {
        case TX04_Sta_GSM_Cop:
        {
            sta = Ublox_GSM_Dialing(G350_GSM_Client_SIZE);
            *finish_code = G350_GSM_Client_SIZE;
            break;
        }
            //        case TX04_GPRS_TCP_Work_Server_Mode:
            //        {
            //            sta = Ublox_GPRS_TCP_Server_Dialing();
            //            break;
            //        }
        case TX04_Sta_TCP_Cop:
        {
            sta = Ublox_TCP_Client_Dialing(G350_TCP_Client_SIZE);
            *finish_code = G350_TCP_Client_SIZE;
            break;
        }
        case TX04_Sta_UDP_Cop:
        {
            sta = Ublox_UDP_Client_Dialing(G350_UDP_Client_SIZE);
            *finish_code = G350_UDP_Client_SIZE;

            break;
        }
    }
    return sta;
}

/***************************************************************************
Function: TX04GetWorkMode
Description: 将参数转化为内部定义工作模式
Input: TX04参数（tx04arg）
Output: 工作状态[uint8_t]
Return: 工作状态[uint8_t]
Others: 如果参数错误，没有设置的话，就会提示错误处理（TX04_Sta_Ready）
 ***************************************************************************/
uint8_t TX04GetWorkMode(TX04ARG tx04arg) {
    uint8_t sta = TX04_Sta_Ready;

    switch (tx04arg.WorkMode) {
        case TX04_ARG_WORK_MODE_GSM:
        {
            sta = TX04_Sta_GSM_Cop;
            break;
        }
        case TX04_ARG_WORK_MODE_GPRS:
        {
            switch (tx04arg.TCP_UDP) {
                case TX04_ARG_TCP_UDP_TCP:
                {
                    switch (tx04arg.CSMode) {
                        case 0x31:
                        {
                            sta = TX04_Sta_TCP_Server_Cop;
                            break;
                        }
                        case 0x30:
                        {
                            sta = TX04_Sta_TCP_Cop;
                            break;
                        }
                    }
                    break;
                }
                case TX04_ARG_TCP_UDP_UDP:
                {
                    sta = TX04_Sta_UDP_Cop;

                    break;
                }
            }
            break;
        }
    }
    return sta;
}

/***************************************************************************
Function: TX04DataInterchange
Description: 根据工作模式，开始拨号连接
Input: 工作模式（workmode）
Output: Ublox的状态[uint8_t]
Return: Ublox的状态[uint8_t]
Others: uint8_t的低级中添加了（Ublox_User_ERR0），便于统一管理错宏定义
 ***************************************************************************/
Bool TX04DataInterchange(uint8_t workmode) {//开始拨号连接
    Bool has_send_cop = False;
    Bool has_rec_cop = False;
    uint8_t mode1, mode2;

    switch (workmode) {
        case TX04_Sta_GSM_Cop:
        {
            mode1 = TX04_GSM_Work_Mode_S;
            mode2 = TX04_GSM_Work_Mode_R;
            break;
        }
        case TX04_Sta_TCP_Cop:
        {
            mode1 = TX04_GPRS_TCP_Work_Client_Mode_S;
            mode2 = TX04_GPRS_TCP_Work_Client_Mode_R;
            break;
        }
        case TX04_Sta_TCP_Server_Cop:
        {
            //             TCP_Server_Link_Cop();
            break;
        }
        case TX04_Sta_UDP_Cop:
        {
            mode1 = TX04_GPRS_UDP_Work_Mode_S;
            mode2 = TX04_GPRS_UDP_Work_Mode_R;
            break;
        }
    }

    do {//TCP发送数据   轮寻查找 
        has_send_cop = OnlineHandleData(mode1); //发送
        if (!gGPRSIsONline)
            break;
        has_rec_cop = OnlineHandleData(mode2); //接收
        if (!has_send_cop && !has_rec_cop) {//如果发送函数、接收没有操作，且定时器处于关闭状态
            TX04Sleep(); //函数中T2清楚标志
        }
    } while (gGPRSIsONline); //通讯异常结束
    GLED = 0; //关闭电流  
    return True;
}

/***************************************************************************
Function: GetGPRSArgFromFlash
Description: 通过读取Flash读取GPRS参数
Input: 地址
Output: 无
Return: 无
Others: 支持参数一和参数二
 ***************************************************************************/
static void GetGPRSArgFromFlash(const uint32_t add) {
    uint8_t arg1[200], cnt = 0, cnt1 = 0;
    uint8_t argtmp[200];
    uint8_t * source_ptr;
    TX04ARG* arg_ptr;
    Bool isArg1 = (add == STORE_ARG1_ADD); //是否是参数一

    ReadArgFromFlash(add, arg1, 176); //根据地址add，读取参数
    for (cnt = 0, cnt1 = 0; cnt < 176; cnt += 4, cnt1 += 3) {//拷贝有效数据
        CopyDat(argtmp + cnt1, arg1 + cnt, 3);
    }
    source_ptr = (CRCIsRight(argtmp, 128, argtmp + 128)) ? argtmp : (uint8_t *) TX04DefualtArg; //读取出来的数据进行CRC16校验,
    arg_ptr = (isArg1) ? &TX04Arg_S : &TX04Arg2_S;
    CopyDat(arg_ptr, source_ptr, 130);
}

/***************************************************************************
Function: TX04GetRunArg
Description: 获取运行参数
Input: 无
Output: 无
Return: 无
Others: 
 ***************************************************************************/
void TX04GetRunArg(void) {
    GetGPRSArgFromFlash(STORE_ARG1_ADD);
    GetGPRSArgFromFlash(STORE_ARG2_ADD);
    EnsureRunArg(&TX04Arg_S); //确定运行的程序
    ChangeBaudRate(); //修改波特率
}

/***************************************************************************
Function: TX04ReportMasthead
Description: 模块上线，发送报头数据
Input: 工作模式（workmode）
Output: 无
Return: 无
Others: 支持UDP和短信
 ***************************************************************************/
void TX04ReportMasthead(uint8_t workmode) {
    uint8_t masthead_dat[50], masthead_bytes = 9; //报头的数据和字节数变量
    if (RunArg.ReportEN == 0x31) {//是否开启报头
        masthead_bytes = TX04GetMasthead(masthead_dat); //发送报头参数
        switch (workmode) {
            case TX04_Sta_TCP_Cop:
            {
                UART1SendString(masthead_dat, masthead_bytes); //发送报头数据
                break;
            }
            case TX04_Sta_UDP_Cop:
            {
                UDPWriteStrByCmd(masthead_dat, masthead_bytes); //发送报头数据                
                break;
            }
            case TX04_Sta_GSM_Cop:
            {
                SMSWriteStrByCmd(masthead_dat, masthead_bytes); //发送报头数据

                break;
            }
        }
    }
}

/*************************************
 * Function: TX04GetMasthead
 * Description: 获取报头数据
 * Input: 获取抱头数据
 * Output: 获取抱头数据的长度
 * Notice：字节数不能大于256
 * 示例：@@13588888888IP:－.－.－.－##36\r\n
 *************************************/
uint8_t TX04GetMasthead(uint8_t * masthead_dat) {
    uint8_t simtmp[40];
    uint8_t cnt = 0, cnt1 = 0;
    uint8_t length = RunArg.SimNumberLength;
    uint8_t copybytes = StrLen((char*) G350_Arg.Client_IP);

    CopyDat(simtmp, (uint8_t*) "@@", 2);
    if (length < 12) {//排除号码是0的情况 数据长度为0xff的情况
        for (cnt = 2; cnt <= length; cnt += 2) {
            simtmp[cnt] = ((RunArg.SimNumber[cnt1 ]) >> 4) + 0x30;
            simtmp[cnt + 1] = ((RunArg.SimNumber[cnt1 ]) &0x0f) + 0x30;
            cnt1 += 1;
        }
    } else
        length = 0;
    if (length % 2) {
        simtmp[cnt] = ((RunArg.SimNumber[cnt1]) >> 4) + 0x30;
        cnt += 1;
    }
    length += 2; //添加@@
    CopyDat(simtmp + length, "IP:", 3);
    length += 3;
    CopyDat(simtmp + length, G350_Arg.Client_IP, copybytes); //拷贝字节数
    length += copybytes;
    CopyDat(simtmp + length, "##36\r\n", 6);
    length += 6;
    CopyDat(masthead_dat, simtmp, length);

    return length;
}

/***************************************************************************
Function: TX04SMSArgIsRight 
Description: 验证发送短信，并提供错误提示
Input: GPRS工作模式
Output: 是否错误
Return: True:短信长度正确；False:短信长度正确
Others: none
 ***************************************************************************/
Bool TX04SMSArgIsRight(uint8_t workmode) {
    Bool b_sta = True;
    if (workmode == TX04_Sta_GSM_Cop) {//如果是短信模式
        if (!DataIsVaild(RunArg.SMSTargetNumber1Length, 13, 1) ||
                !DataIsVaild(RunArg.SMSTargetNumber2Length, 13, 1)) {//检查手机号码长度            
            PrintErr(11);
            //            if (gRefreshArg) {//GPRS下线，如果模块需要重新载入参数的话，标志位清除，并重载参数
            //                gRefreshArg = 0;
            //                CopyDat((uint8_t*) & RunArg, (uint8_t*) & TX04Arg_S, 130); //刷新参数，避免重复进入短信模式
            //            }
            b_sta = False;
        }
    }
    return b_sta;
}







