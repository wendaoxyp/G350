/* 
 * File:   TX04.h
 * Author: Administrator
 *
 * Created on January 4, 2018, 10:40 AM
 */

#ifndef TX04_H
#define	TX04_H


/***************************************************************************
 * Includes
 ***************************************************************************/
#include "DefType.h"
#include "Common.h"
#include "UART2.h"
#include "UART1.h"
#include "INT.h"
#include "TIM.h"
#include "ublox_g350.h"
#include "CheckData.h"
#include "Debug.h"

/***************************************************************************
 * Defines
 ***************************************************************************/
extern const char USER_READY[]; // 开阀门指令发送
extern const char TX04_TXYBJT[]; // = {"+TXYBJT "}; //TX04在线接收帧头
extern const char TX04_TESTW0_Rec[]; // = {"+RECW0"};
extern const char TX04_TESTW2_Rec[]; // = {"+RECW2"};
extern const char TX04_TECH_Rec[]; // = {"+TXYBJT DTU Software,VERtrkj_v04.0\r\n"};
//extern const char TX04_GPSQ_Rec[]; // = {"CSQ_11"};
//extern const char TX04_GPST_Rec[]; //= {"DW: \"XXXX\",\"XXXX\",\"APN\""};
extern const char TX04_SEND_OFF[];
extern const char TX04_HEARTBEAT[];
extern const uint32_t STORE_ARG1_ADD; //= 0x00AD00; //定义参数在程序存储器中的位置
extern const uint32_t STORE_ARG2_ADD; // = 0x00AE00; //定义参数2在程序存储器中的位置
extern volatile Bool gExitSleep; //睡眠标志
extern volatile uint8_t gGPRSIsONline; //上线标志位
extern volatile uint8_t gTX04Sta; //GPRS状态 就绪状态  TCP状态 UDP状态 GSM状态

//Ublox的状态
#define TX04_Sta_Ready                     0x70    //就绪状态	
#define TX04_Sta_TCP_Server_Cop            0x76
#define TX04_Sta_TCP_Cop                   0x77    //TCP工作状态	
#define TX04_Sta_UDP_Cop                   0x78    //UDP工作状态							
#define TX04_Sta_GSM_Cop                   0x79    //GSM工作状态		

//#define TX04_ARG_CONTROL_MODE_SOFEWARE  0x30//软件控制
#define TX04_ARG_CONTROL_MODE_HARDWARE  0x31//EN控制
#define TX04_ARG_TCP_UDP_TCP            0x30//TCP协议
#define TX04_ARG_TCP_UDP_UDP            0x31//UDP协议
#define TX04_ARG_WORK_MODE_GPRS         0x30//网络协议
#define TX04_ARG_WORK_MODE_GSM          0x31//短信通讯

//#define TX04_GSM_Work_Mode              0x60    //短信工作模式
#define TX04_GSM_Work_Mode_S            0x61    //短信工作模式发送模式
#define TX04_GSM_Work_Mode_R            0x62    //短信工作模式接受模式
//#define TX04_GPRS_TCP_Work_Server_Mode  0x70    //TCP服务端模式
//#define TX04_GPRS_TCP_Work_Server_Mode_S  0x71    //TCP服务端模式
//#define TX04_GPRS_TCP_Work_Server_Mode_R  0x72    //TCP服务端模式
//#define TX04_GPRS_TCP_Work_Client_Mode  0x80    //TCP客服端模式
#define TX04_GPRS_TCP_Work_Client_Mode_S  0x81    //TCP客服端模式
#define TX04_GPRS_TCP_Work_Client_Mode_R  0x82    //TCP客服端模式
//#define TX04_GPRS_UDP_Work_Server_Mode  0x09    //UDP服务端模式
//#define TX04_GPRS_UDP_Work_Client_Mode  0x90    //UDP客服端模式
#define TX04_GPRS_UDP_Work_Mode_S  0x91    //UDP客服端模式
#define TX04_GPRS_UDP_Work_Mode_R  0x92    //UDP客服端模式


#define CMDIsGetVer(x)   ((x == CMD_TECH) ? True : False)
#define TX04IsWorkSta(x)    ((x == TX04_Sta_TCP_Cop) ||\
                            (x == TX04_Sta_GSM_Cop) ||\
                            (x == TX04_Sta_UDP_Cop) ||\
                            (x == TX04_Sta_TCP_Server_Cop))            //判断是否工作转台

/***************************************************************************
 * Typedef
 ***************************************************************************/
typedef struct TX04arg {
    uint8_t IP[4]; //IP地址
    uint16_t Port; //端口  低尾端（小端存储方式 little Endian）
    uint8_t WorkMode; //工作模式 0x31GSM
    uint8_t TCP_UDP; //TCP_UDP
    uint8_t DNSMode; //DNS工作方式
    uint8_t SMSTargetNumber1Length; //短信目标号码1长度
    uint8_t SMSTargetNumber1[6]; //短信目标号码1
    uint8_t SMSMonitoringCenterNumber1Length; //短消息监控中心号码1长度
    uint8_t SMSMonitoringCenterNumber1[6]; //短消息监控中心号码1
    uint8_t SignalQualityEnable; //信号强度检测使能
    uint8_t ControlMode; //30H:软件控制   31H:EN控制
    uint8_t BaudRate; //通信波特率
    uint16_t RestartTime; //重启时间 Low First 低尾端（小端存储方式 little Endian）
    uint16_t HeartTime; //心跳包时间 低尾端（小端存储方式 little Endian）
    uint16_t ListenTime; //监听时间 低尾端（小端存储方式 little Endian）
    uint8_t CSMode; //客户服务模式
    uint8_t DNSDomainNameLength; //DNS域名长度
    uint8_t DNSDomainName[31]; //DNS域名
    uint8_t APNNameLength; //APN名称长度
    uint8_t APNName[31]; //APN名称
    uint8_t ReportEN; //报头使能
    uint8_t SimNumberLength; //本机号码长度
    uint8_t SimNumber[6]; //本机号码
    uint8_t SMSTargetNumber2Length; //短信目标号码2长度
    uint8_t SMSTargetNumber2[6]; //短信目标号码2
    uint8_t SMSMonitoringCenterNumber2Length; //短消息监控中心号码2长度
    uint8_t SMSMonitoringCenterNumber2[6]; //短消息监控中心号码2
    uint8_t Reserve[9]; //备用 
    uint16_t CRC16; //CRC校验值
} TX04ARG;
extern/* volatile*/ TX04ARG TX04Arg_S;
extern/* volatile*/ TX04ARG TX04Arg2_S;
extern TX04ARG RunArg; //结构体

enum CMD_TP { //指令类型定义 注意必须要从零开始，和偏移数组有关  //必须和上面的TX04_CMD_ARRY类型对应
    CMD_TESTW0 = 0x0 /*写参数0*/, CMD_TESTW2 = 0x1 /*写参数1*/, CMD_TESTR0 = 0x2 /*读参数0*/, CMD_TESTR2 = 0x3 /*读参数1*/, CMD_TECH = 0x4 /*读取版本号*/,
    CMD_GPON = 0x5 /*上线*/, CMD_GPOF = 0x6 /*下线*/, CMD_GPSQ = 0x7 /*检索强度*/, CMD_GPCH1 = 0x8 /*切换中心*/, CMD_GPCH2 = 0x9, /*切换中心*/
    CMD_GPSM = 0xA /*强制短信一*/, CMD_GPSS = 0xB /*强制短信二*/, CMD_GPST = 0xC /*获取地理信息*/, CMD_GRCH = 0xD/*SMS切换中心*/, CMD_GROF = 0xE /*SMS下线*/,
    CMD_GPID = 0xF /*获取ICCID*/, CMD_NO_CMD = 0x10 /*没有有效的指令*/
};
extern enum CMD_TP cmd_tp;

extern volatile uint8_t gTX04Sta;
/***************************************************************************
 * Prototype
 ***************************************************************************/
extern void TX04_Init(void);
extern Bool TX04WriteArgByCMD(const uint32_t argadd, uartsendstring uart, uint8_t *Ublox_buf);
extern void TX04ReadArgByCMD(uartsendstring uart, CMDTYPE cmd, TX04ARG* tx04arg);
extern void TX04ReadSofewareVersionByCMD(uartsendstring uart, Bool);
extern void TX04ReadCSQByCMD(uartsendstring uart);
extern void TX04ReadLocInfoByCMD(uartsendstring uart);
extern void TX04ReadSIMIDByCMD(uartsendstring uart);
extern uint8_t IsGetMasthead(const uint8_t * Ublox_buf, const uint8_t bytes);
extern Bool IsDisconnect(const uint8_t * Ublox_buf, const uint8_t bytes);
extern CMDTYPE TX04GetCMDType(const uint8_t* Ublox_buf, const uint8_t bytes);
extern uint8_t TX04GetWorkMode(TX04ARG tx04arg);
extern uint8_t TX04Connect(uint8_t workmode, uint8_t *);
extern Bool TX04DataInterchange(uint8_t workmode);
//extern void User_PrintErrCode(uartsendstring uart, uint8_t errcode);
extern Bool ControlModeIsEN(void);
extern void TX04Sleep(void);
extern uint8_t TX04GetMasthead(uint8_t*);
extern void TX04GetRunArg(void);
extern void ChangeBaudRate(void);
extern Bool CMDRec_HandleCmd(uartsendstring uart, CMDTYPE cmdtype, uint8_t * Ublox_buf);
extern void TX04ReportMasthead(uint8_t workmode);
extern Bool BootLoader(void);
extern Bool TX04SMSArgIsRight(uint8_t workmode);
extern void LED_Blink(uint8_t Cnt, uint8_t Dly100ms);

#endif	/* WVC_H */
//定义用户的错误提示
//#define Ublox_USER_FAIL_01                1    //GPRS模块上电初始化失败：未插卡、GPRS芯片异常、电源电压异常
//#define Ublox_USER_FAIL_02                2    //堆栈打开错误：可能GPRS模块坏或未正常复位
//#define Ublox_USER_FAIL_03                3    //打开GPRS失败：无信号或网络故障
//#define Ublox_USER_FAIL_04                4    //设置APN失败：APN设置错误或网络故障
//#define Ublox_USER_FAIL_05                5    //开始GPRS失败：无信号或网络故障
//#define Ublox_USER_FAIL_06                6    //TCP CLIENT模式连接失败：服务端未上线监听
//#define Ublox_USER_FAIL_07                7    //连接后数据通信失败：无信号或网络故障
//#define Ublox_USER_FAIL_08                8    //TCP SERVER模式，建立连接失败：APN设置错误或网络故障或端口有误
//#define Ublox_USER_FAIL_09                9    //服务端模式未监听到客户端上线：客户端未上线超时或无信号
//#define Ublox_USER_FAIL_10                10    //上线过程复位：电源电压低引起复位
//#define Ublox_USER_FAIL_11                11    //短信号码设置存在问题
//#define Ublox_USER_FAIL_14                14    //发送短信目标错误：电源电压低或网络差引起复位
//#define Ublox_USER_FAIL_15                15    //数据中心停止监听, 关GPRS：因数据中心停止监听而退出并关GPRS
//#define Ublox_USER_FAIL_16                16    //连接链路故障，关GPRS：因连接链路故障而退出并关GPRS
//#define Ublox_USER_FAIL_17                17    //打开GPRS失败：手机卡欠费或停机
//#define Ublox_USER_FAIL_18                18    //上线达到次数：达到参数中的规定上线次数
