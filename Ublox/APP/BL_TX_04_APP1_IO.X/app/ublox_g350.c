
/***************************************************************************
 * Includes
 ***************************************************************************/
//#include "ublox_g350.h"
#include "TX04.h"
#include "G350_AT_Command.h"
#include <ctype.h>
//#include <stdlib.h>
#include "DefType.h"
#include "SerialBuffer.h"
#include "Common.h"
#include "TX04_Conf.h"
#include "UART1.h"
#include "UART2.h"


/***************************************************************************
 * Definitions
 ***************************************************************************/
GPRS_Arg G350_Arg;
typedef Bool(*GetModuleArg_pf)(char *dat, uint8_t dat_bytes);

/***************************************************************************
 * Variables
 ***************************************************************************/
extern volatile Bool gSMSInfo;

/***************************************************************************
 * Prototypes
 ***************************************************************************/

/***************************************************************************
 * Code 
 ***************************************************************************/

/***************************************************************************
 * Function: Get_UDP_Rec_Data 
 * Description: 通用接口:判?是否是注册成功，本地，远程都可实现
 * Input: 判断的源数据，源数据字节数
 * Output: 是否获取到
 * Return: True:获取到期望的数据；False:获取失败
 * Others: none
 ***************************************************************************/
//static Bool Get_UDP_Rec_Data(char *dat, uint8_t dat_bytes) {
//    uint8_t check_bytes = StrLen(Rec_URC), get_pos = 0, end_pos = 0;
//    Bool sta = False;
//    //    uint8_t tmp[6], getsize, offset;
//    uint8_t headpos_real, endpos_real, readnum_real, offset;
//    char port[8] = {'"', ',', 0, 0, 0, 0, 0, 0}, port_size;
//
//    port_size = my_itoa(RunArg.Port, ((uint8_t*) port + 2));
//
//    get_pos = Str_Find_Head(dat, Rec_URC, dat_bytes, check_bytes); //获取+USORF:
//    if (get_pos) {//判断是否获取到头数据 
//        end_pos = Str_Find_Head(dat + get_pos, _r_n, dat_bytes, 2) - 1;
//        if (end_pos) {
//            headpos_real = Str_Find_Head(dat, port, dat_bytes, port_size + 2); //获取端口号的位置
//            offset = headpos_real - 1;
//            endpos_real = Str_Find_Head(dat + offset, ",\"", dat_bytes - offset, 2); //判断有效数据 
//            offset += port_size + 3;
//            readnum_real = G350_Arg.UDP_BYTES = my_atoi((uint8_t*) dat + offset, endpos_real - 8); //实际获取到的字节数
//            offset += endpos_real - 6;
//            CopyDat(dat, dat + offset, readnum_real);
//        }
//    }
//    return sta;
//}

/***************************************************************************
 * Function: Get_UDP_Rec_Byte 
 * Description: 通用接口:判?是否是注册成功，本地，远程都可实现
 * Input: 判断的源数据，源数据字节数
 * Output: 是否获取到
 * Return: True:获取成功；False:获取失败 数据看全局变量UDP_BYTES
 * Others: none
 ***************************************************************************/
static Bool Get_UDP_Rec_Byte(char *dat, uint8_t dat_bytes) {
    uint8_t check_bytes = StrLen(Rec_URC), get_pos = 0, end_pos = 0;
    Bool sta = False;
    uint8_t tmp[6], getsize;


    get_pos = Str_Find_Head(dat, Rec_URC, dat_bytes, check_bytes); //获取+USORF:
    if (get_pos) {//判断是否获取到头数据 
        end_pos = Str_Find_Head(dat + get_pos, _r_n, dat_bytes, 2); //判断是否获取到尾数据 
        if (end_pos) {
            check_bytes += 3;
            getsize = end_pos - check_bytes;
            check_bytes += get_pos - 1;
            CopyDat(tmp, dat + check_bytes, getsize); //获取20个字节
            G350_Arg.UDP_BYTES = my_atoi(tmp, getsize); //字符串转化为数字
            sta = True;
        }
    }
    return sta;
}

/***************************************************************************
 * Function: Check_CREG 
 * Description: 通用接口:判?是否是注册成功，本地，远程都可实现
 * Input: 判断的源数据，源数据字节数
 * Output: 是否获取到
 * Return: True:获取到期望的数据；False:获取失败
 * Others: none
 ***************************************************************************/
static Bool Check_CREG(char *dat, uint8_t dat_bytes) {
    uint8_t check_bytes = StrLen(Rec_CREG_1), get_pos = 0, get_bytes = sizeof (G350_Arg.LAC);
    Bool sta = False;

    get_pos = Str_Find_Head(dat, Rec_CREG_5, dat_bytes, check_bytes); //获取ICCID位置
    if (get_pos) {//判断是否是CREG:1  
        CopyDat(G350_Arg.LAC, dat + get_pos + check_bytes, get_bytes); //获取20个字节
        sta = True;
    } else {
        get_pos = Str_Find_Head(dat, Rec_CREG_1, dat_bytes, check_bytes); //判断是否是CREG:5
        if (get_pos) {
            CopyDat(G350_Arg.LAC, dat + get_pos + check_bytes, get_bytes); //获取20个字节
            sta = True;
        }
    }
    return sta;
}

/***************************************************************************
 * Function: GetModule_CCID
 * Description:获取CCID
 * Input:判断的源数据，源数据字节数
 * Output: 是否获取到
 * Return: True:获取到期望的数据；False:获取失败
 * Others: none
 ***************************************************************************/
static Bool GetModule_CCID(char *dat, uint8_t dat_bytes) {
    uint8_t get_pos = 0, check_bytes = StrLen(Rec_ICCID), get_bytes = sizeof (G350_Arg.ICCID);
    Bool sta = False;

    get_pos = Str_Find_Head(dat, Rec_ICCID, dat_bytes, check_bytes); //获取ICCID位置
    if (get_pos) {//如果获取到ICCID，进一步判断    
        CopyDat(G350_Arg.ICCID, dat + get_pos + check_bytes - 1, get_bytes); //获取20个字节
        sta = True;
    }
    return sta;
}

/***************************************************************************
 * Function: GetModule_CSQ
 * Description:获取CSQ
 * Input:判断的源数据，源数据字节数
 * Output: 是否获取到
 * Return: True:获取到期望的数据；False:获取失败
 * Others: none
 ***************************************************************************/
static Bool GetModule_CSQ(char *dat, uint8_t dat_bytes) {
    uint8_t get_pos = 0, check_bytes = StrLen(Rec_CSQ), get_bytes = sizeof (G350_Arg.CSQ);
    Bool sta = False;

    get_pos = Str_Find_Head(dat, Rec_CSQ, dat_bytes, check_bytes); //获取ICCID位置
    if (get_pos) {//如果获取到ICCID，进一步判断    
        CopyDat(G350_Arg.CSQ, dat + get_pos + check_bytes - 1, get_bytes); //获取20个字节
        sta = True;
    }
    return sta;
}

/***************************************************************************
 * Function: GetModule_ClientIP
 * Description:获取报头IP
 * Input:判断的源数据，源数据字节数
 * Output: 是否获取到
 * Return: True:获取到期望的数据；False:获取失败
 * Others: none
 ***************************************************************************/
static Bool GetModule_ClientIP(char *dat, uint8_t dat_bytes) {
    uint8_t get_pos = 0, get_pos1, check_bytes = StrLen(REC_UPSND), offset = 0; // get_bytes = sizeof (G350_Arg.Client_IP);
    Bool sta = False;

    get_pos = Str_Find_Head(dat, REC_UPSND, dat_bytes, check_bytes); //判断是否获取到
    if (get_pos) {//如果获取到ICCID，进一步判断    
        get_pos1 = Str_Find_Head(dat + get_pos, __r_n, dat_bytes - get_pos, 3); //获取ICCID位置
        if (get_pos1) {
            offset = get_pos1 - check_bytes;
            CopyDat(G350_Arg.Client_IP, dat + get_pos + check_bytes - 1, offset); //获取20个字节
            *(G350_Arg.Client_IP + offset) = '\0';
            sta = True;
        }
    }
    return sta;
}

/***************************************************************************
 * Function: GetModule_ClientIP
 * Description:获取DNS转化IP
 * Input:判断的源数据，源数据字节数
 * Output: 是否获取到
 * Return: True:获取到期望的数据；False:获取失败
 * Others: none
 ***************************************************************************/
static Bool GetModule_DNS2IP(char *dat, uint8_t dat_bytes) {
    uint8_t get_pos = 0, get_pos1, check_bytes = StrLen(Rec_SET_DNS), offset = 0;
    Bool sta = False;

    //    while (BufferRead_UART1((uint8_t*) dat + dat_bytes++)); //获取剩下的数据
    get_pos = Str_Find_Head(dat, Rec_SET_DNS, dat_bytes, check_bytes); //获取ICCID位置
    if (get_pos) {//如果获取到ICCID，进一步判断    
        get_pos1 = Str_Find_Head(dat + get_pos, __r_n, dat_bytes - get_pos, 3); //获取ICCID位置
        if (get_pos1) {
            offset = get_pos1 - check_bytes;
            CopyDat(G350_Arg.Server_IP, dat + get_pos + check_bytes - 1, offset); //获取20个字节
            *(G350_Arg.Server_IP + offset) = '\0';
            sta = True;
        }
    }
    return sta;
}

/***************************************************************************
 * Function: TX04Arg2GPRSArg
 * Description: GPRS的IP转化字符串
 * Input: 判断的源数据，源数据字节数
 * Output: 
 * Return: 获取的字节数
 * Others: 
 ***************************************************************************/
static uint8_t TX04Arg2GPRSArg(char* output_s) {
    uint8_t cnt, getbytes = 0;

    for (cnt = 0; cnt < 4; cnt++) {
        getbytes += my_itoa(RunArg.IP[cnt], (uint8_t*) (output_s + getbytes));
        if (cnt < 3) {
            output_s[getbytes++] = '.';
        }
    }
    output_s[getbytes++] = '\0';
    return getbytes;
}

/***************************************************************************
Function: UbloxSendATCmd 
Description: 发送AT命令给Ublox
Input: ss(发送数据地址);cs(对比数据地址);csl(对比数据长度);cnt(操作次数)
Output: void
Return: True:发送成功；False:发送失败
Others: source_str的长度要大于check_str，必须都是字符串
 ***************************************************************************/
static Bool UbloxSendATCmd(const char *source_str, const char* check_str, GetModuleArg_pf arg_pf, const uint16_t dly_10ms) {
    uint8_t send_cnt = 0, get_bytes = 0, head_pos = 0; //, check_bytes; //, cnt;
    Bool b_sta = False;
    uint8_t tmp[256];

    ClearDat(tmp, 0xff, 50); //清楚缓冲区
    //    check_bytes = StrLen(check_str);
    do {
        if (source_str != Null) {
            UART1SendString(source_str, StrLen(source_str)); //发送AT指令 
#ifdef DEBUG_AT_TEST 
            UART2SendString((uint8_t*) "Send:", 5); //发送AT指令  
            UART2SendString((uint8_t*) source_str, StrLen(source_str)); //发送AT指令          
#endif
        }
        Idle(); //进入休眠模式        
        get_bytes += UARTGetDat(BufferRead_UART1, tmp + get_bytes, sizeof (tmp) - get_bytes, dly_10ms);
#ifdef DEBUG_AT_TEST  
        if (get_bytes) {
            UART2SendString((uint8_t*) "Receive:", 8); //发送AT指令  
            UART2SendString((uint8_t*) tmp, get_bytes);
            UART2SendChar('\n');
        } else
            UART2SendString((uint8_t*) "No Receive!\n", 12); //发送AT指令 
#endif
        head_pos = Str_Find_Head(tmp, check_str, get_bytes, StrLen(check_str));
        if (head_pos) {//判断第一个字节 
            if (arg_pf) {
                b_sta = (*arg_pf)((char*) tmp, get_bytes) ? True : False;
            } else {
                b_sta = True;
            }
            if (b_sta)
                break;
        }
    } while (5 > send_cnt++);
    return b_sta;
}


/***************************************************************************
Function: UbloxWaitServer //形态2 发送CPOS？ OK  +CREG:1
Description: 发送AT命令给Ublox
Input: void
Output: Bool：True:上线成功 False：下线
Return: True:发送成功；False:发送失败
Others: none
 problem:1、重启的过程中串口发送很多其他的数据
 **************************************************************************
static Bool UbloxWaitServer(void) {
    uint8_t get_bytes = 0, find_cnt = 0, op = 0; //, length = 0x
    Bool b_sta = False; //, flag = True;
    uint8_t tmp[256]; //ATE exist AT Command depend on max size

    ClearDat(tmp, 0xff, 50); //清楚缓冲区
    //    CloseUblox(); //关闭ublox
    //    LP_Delay(30); //延时5s
    //    OpenUblox(); //开启ublox
    //    LP_Delay(10); //延时5s
    //    UART1SendString(Send_COPS, sizeof (Send_COPS) - 1); //必须添加，防止数据第一次返回数据错误
    //    UART1SendString(Send_COPS, sizeof (Send_COPS) - 1); //必须添加，防止数据第一次返回数据错误
    //    UART1SendString(Send_COPS, sizeof (Send_COPS) - 1); //必须添加，防止数据第一次返回数据错误

    gT2flag = 0; //   
    StartTMR2(500);
    while (!gT2flag) {
        Idle();
        //        if (gResetFlag)//等待建立服务端的时候，重启
        //            break;
        //        U1GetLast4Bytes(); //获取最后4个字节
        //        while (BufferRead_UART1(tmp + get_bytes))
        //            get_bytes++;
        //        get_bytes
        get_bytes += UARTGetDat(BufferRead_UART1, tmp + get_bytes, 0); //规定10ms时间内，获取4个字节
        if (get_bytes >= 9) {//"+UUSOAOC:"
            find_cnt = Str_Find_Head(tmp, Rec_Server_URC, get_bytes, sizeof (Rec_Server_URC) - 1);
            if (find_cnt) {//判断第一个字节 
                op = find_cnt;
                b_sta = True;
                break;
            }
        }
    }
    //    Delay100ms(1);
    gT2flag = 0;
    StopTMR2();
#ifdef DEBUG_AT_TEST
    if (get_bytes) {
        UART2SendString((uint8_t*) "Receive:", 8); //发送AT指令  
        UART2SendString((uint8_t*) tmp, get_bytes);
        UART2SendChar('\n');
    } else
        UART2SendString((uint8_t*) "No Receive!\n", 12); //发送AT指令 
#endif
    //    get_bytes = 0; //清除历史返回数据

    return b_sta;
}
 */
/***************************************************************************
Function: UbloxWaitClient //形态2 发送CPOS？ OK  +CREG:1
Description: 发送AT命令给Ublox
Input: void
Output: Bool：True:上线成功 False：下线
Return: True:发送成功；False:发送失败
Others: none
 **************************************************************************
static Bool UbloxWaitClient(void) {
    //#define  DeBug_Break_Out     
    uint8_t get_bytes = 0, find_cnt = 0, op = 0; //, length = 0x
    Bool b_sta = False; //, flag = True;
    uint8_t tmp[256]; //ATE exist AT Command depend on max size

    ClrUARTnBuf(BufferRead_UART1);
    ClearDat(tmp, 0xff, 50); //清楚缓冲区

    while (1) {
        Idle();
        //        Delay100ms(1); //1920/10=
        //        U1GetLast4Bytes(); //获取最后4个字节        
        //        while (BufferRead_UART1(tmp + get_bytes))
        //            get_bytes++;
        get_bytes += UARTGetDat(BufferRead_UART1, tmp + get_bytes,  10); //规定100ms时间内，获取4个字节
        if (get_bytes >= 9) {//"+UUSOAOC:"
            find_cnt = Str_Find_Head(tmp, Rec_Client_URC, get_bytes, sizeof (Rec_Client_URC) - 1);
            if (find_cnt) {//判断第一个字节 
                op = find_cnt;
                b_sta = True;
#ifdef DeBug_Break_Out
                DeBug_PrintInfo("\r\nFound_Break_Out!!!\r\n");
#endif
#ifdef DEBUG_AT_TEST
                if (get_bytes) {
                    UART2SendString((uint8_t*) "Receive:", 8); //发送AT指令  
                    UART2SendString((uint8_t*) tmp, get_bytes);
                    UART2SendChar('\n');
                } else
                    UART2SendString((uint8_t*) "No Receive!\n", 12); //发送AT指令 
#endif
                break;
            }
        }
    }
    //    Delay100ms(1);
    //#ifdef DEBUG_AT_TEST
    //    if (get_bytes) {
    //        UART2SendString((uint8_t*) "Receive:", 8); //发送AT指令  
    //        UART2SendString((uint8_t*) tmp, get_bytes);
    //        UART2SendChar('\n');
    //    } else
    //        UART2SendString((uint8_t*) "No Receive!\n", 12); //发送AT指令 
    //#endif
    //    get_bytes = 0; //清除历史返回数据
    return b_sta;
}
 */




/***************************************************************************
Function: UbloxGetServerPort
Description: 发送AT命令给Ublox
Input: 输入
Output: void
Return: True:发送成功；False:发送失败
Others: none
 **************************************************************************
static uint8_t UbloxGetServerPort(uint8_t * port_str) {
    uint8_t sendportcmd[256], bytes_offset = 0;

    ClearDat(sendportcmd, 0, 256);
    bytes_offset = 11;
    CopyDat(sendportcmd, Send_SET_PORT, bytes_offset); //拷贝11bytes
    bytes_offset += GetPort(RunArg.Port, sendportcmd + bytes_offset);
    CopyDat(sendportcmd + bytes_offset, (uint8_t*) "\r\n", 3);
    bytes_offset += 3;
    CopyDat(port_str, sendportcmd, bytes_offset); //复制APN

    return bytes_offset;
}*/

/***************************************************************************
Function: UbloxGetServerIP
Description: 发送AT命令给Ublox
Input: 输入
Output: void
Return: True:发送成功；False:发送失败
Others: none
 **************************************************************************
static uint8_t UbloxGetServerIP(uint8_t * ip_str) {
    uint8_t sendipcmd[256], bytes_offset = 0;

    ClearDat(sendipcmd, 0, 256);
    bytes_offset = 12;
    CopyDat(sendipcmd, Send_SET_WHITE_LIST, bytes_offset); //拷贝11bytes
    //    CopyDat(sendipcmd, RunArg.IP, bytes_offset); //拷贝11bytes
    bytes_offset += GetIP(RunArg.IP, sendipcmd + bytes_offset);
    CopyDat(sendipcmd + bytes_offset, (uint8_t*) "\r\n", 3);
    bytes_offset += 3;
    CopyDat(ip_str, sendipcmd, bytes_offset); //复制APN

    return bytes_offset;
}*/

/***************************************************************************
Function: GetAPNCmd
Description: 获取AT发送命令ANP指令
Input: 输入 APN的参数
Output: void
Return: 返回指令长度
Others: none
 ***************************************************************************/
static uint8_t GetAPNCmd(char * apn_str) {
    uint8_t bytes_offset = StrLen(Send_SET_APN);

    CopyDat(apn_str, Send_SET_APN, bytes_offset); //"AT+UPSD=0,1,\"CMNET\"\r\n"
    CopyDat(apn_str + bytes_offset, RunArg.APNName, RunArg.APNNameLength);
    bytes_offset += RunArg.APNNameLength;
    CopyDat(apn_str + bytes_offset, __r_n, 4);
    bytes_offset += 4;

    return bytes_offset;
}

/***************************************************************************
Function: GetIPPortCmd
Description: 获取AT发送命令的IP地址和端口号指令
Input: 输入
Output: void
Return: True:发送成功；False:发送失败
Others: none
 ***************************************************************************/
static uint8_t GetIPPortCmd(char *output_s) {//note:headstr_bytes-1
    uint8_t offset = 0, getbytes = StrLen(G350_Arg.Server_IP);

    offset = StrLen(Send_SET_IP_PORT);
    CopyDat(output_s, Send_SET_IP_PORT, offset);
    *(output_s + offset++) = '\"';
    CopyDat(output_s + offset, G350_Arg.Server_IP, getbytes); //拷贝IP地址
    offset += getbytes;
    *(output_s + offset++) = '\"';
    *(output_s + offset++) = ',';
    getbytes = my_itoa(G350_Arg.PORT, (uint8_t*) (output_s + offset));
    offset += getbytes;
    CopyDat(output_s + offset, _r_n, 3);
    offset += 3;
    return offset;
}

/***************************************************************************
Function: GetDNSCmd
Description: 获取AT发送命令ANP指令
Input: 输入 APN的参数
Output: void
Return: 返回指令长度
Others: none
 ***************************************************************************/
static uint8_t GetDNSCmd(char * dns_str) {
    uint8_t bytes_offset = StrLen(Send_SET_DNS);

    CopyDat(dns_str, Send_SET_DNS, bytes_offset); //"AT+UPSD=0,1,\"CMNET\"\r\n"
    *(dns_str + bytes_offset) = '\"';
    bytes_offset++;
    CopyDat(dns_str + bytes_offset, RunArg.DNSDomainName, RunArg.DNSDomainNameLength);
    bytes_offset += RunArg.DNSDomainNameLength;
    CopyDat(dns_str + bytes_offset, __r_n, 4);
    bytes_offset += 4;

    return bytes_offset;
}

/***************************************************************************
Function: OpenUblox
Description: 通过IO口打开6310
Input: void
Output: void
Return: void
Others: none
 ***************************************************************************/
Bool OpenUblox(void) {//本例子中使用UART1的接收引脚需要
    uint8_t cnt = 0;
    OR_CTRL_PWR = 1;
    //等待电容充电完成
    UB_PWRON = 1; //开启ublox
    Delay10ms(1);
    UB_PWRON = 0;
    while (!UB_STA) {
        Delay10ms(1);
        cnt++;
        if (cnt > 10)

            return False;
    }
    return True;
}

/***************************************************************************
Function: CloseUblox
Description: 通过IO关闭Ublox
Input: void
Output: void
Return: void
Others: none
 ***************************************************************************/
void CloseUblox(void) {//本例子中使用UART1的接收引脚需要

    UB_PWRON = 0;
    OR_CTRL_PWR = 0;
    Delay100ms(5);
}

/***************************************************************************
Function: Ublox_Find_Network
Description: 发送AT命令给Ublox
Input: 输入
Output: void
Return: True:发送成功；False:发送失败
Others: step不能大于Ublox_F_NET_ATTACHE（5）
 ***************************************************************************/
uint8_t Ublox_Find_Network(uint8_t step) {
    Bool sta = False; //设置ublox状态为网络初始化
    int8_t cnt;

    const char* send_cmd[G350_F_NET_SIZE] = {CREG_2, Send_CPIN, Send_ICCID, Null, Send_CSQ};
    const char* check_cmd[G350_F_NET_SIZE] = {Rec_OK, Rec_OK, Rec_OK, Rec_CREG, Rec_OK};
    //    const uint8_t needbytes[G350_F_NET_SIZE] = {2, 16, 38, 22, 12};
    const GetModuleArg_pf pf_th [G350_F_NET_SIZE] = {Null, Null, GetModule_CCID, Check_CREG, GetModule_CSQ};
    const uint16_t delay_10ms[G350_F_NET_SIZE] = {100, 100, 100, 800, 60}; //不能大于1691.25 10ms

    for (cnt = 0; cnt < step; cnt++) {
        sta = UbloxSendATCmd(send_cmd[cnt], check_cmd[cnt], pf_th[cnt], delay_10ms[cnt]) ? True : False;
        ClrUARTnBuf(BufferRead_UART1);
        if (!sta) break;
    }
    return cnt;
}

/***************************************************************************
Function: Ublox_UDP_Client_Dialing
Description: 发送AT命令给Ublox
Input: 输入
Output: void
Return: True:发送成功；False:发送失败
Others: none
 **************************************************************************/
uint8_t Ublox_UDP_Client_Dialing(uint8_t step) {
    char getIPcmd[256]; //, bytes = 0;
    char getAPN[256]; //, apn_bytes = 0;
    char getDNS[256]; //, apn_bytes = 0;
    Bool sta = False; //设置ublox状态为网络初始化
    int8_t cnt;
    Bool isDNS = RunArg.DNSMode == 0x31;

    ClearDat(getIPcmd, '\0', 256);
    ClearDat(getAPN, '\0', 256);
    ClearDat(getDNS, '\0', 256);

    char* send_cmd[G350_UDP_Client_SIZE] = {
        getAPN,
        (char*) Send_ACTIVE_ARG,
        getDNS,
        (char*) Send_SET_UDP, //Send_SET_TCP,
        (char*) Send_UPSND
    };
    char* check_cmd[G350_UDP_Client_SIZE] = {(char*) Rec_OK, (char*) Rec_OK, (char*) Rec_OK, (char*) Rec_OK, (char*) Rec_OK};
    //    const uint8_t needbytes[G350_UDP_Client_SIZE] = {4, 2, 28, 17, 30, 2};
    GetModuleArg_pf pf_th [G350_UDP_Client_SIZE] = {Null, Null, GetModule_DNS2IP, Null, GetModule_ClientIP,};
    uint16_t delay_10ms[G350_UDP_Client_SIZE] = {80, 150, 100, 300, 50};

    GetAPNCmd(getAPN); //获取APN
    TX04Arg2GPRSArg(G350_Arg.Server_IP); //获取IP

    G350_Arg.PORT = RunArg.Port; //获取端口号
    if (isDNS) GetDNSCmd(getDNS); //如果是域名解析的话，获取域名的AT指令

    for (cnt = 0; cnt < step; cnt++) {
        if (cnt == G350_SET_TCP_IP)//如果指令包含IP和PORT，那么重新获取指令
            GetIPPortCmd(getIPcmd);
        if ((!isDNS) &&(cnt == G350_GET_DNS))//判断是否需要域名解析
            continue;
        sta = UbloxSendATCmd(send_cmd[cnt], check_cmd[cnt], pf_th[cnt], delay_10ms[cnt]) ? True : False;
        ClrUARTnBuf(BufferRead_UART1);
        if (!sta) break;
    }
    return cnt; // == G350_UDP_Client_SIZE) ? True : False;
}

/***************************************************************************
Function: Ublox_TCP_Client_Dialing
Description: 发送AT命令给Ublox
Input: 输入 RunArg.DNSMode == 0x31) {//30H-固定IP 31H-域名解析
Output: void
Return: True:发送成功；False:发送失败
Others: none
 ***************************************************************************/
Bool Ublox_TCP_Client_Dialing(uint8_t step) {
    char getIPcmd[256]; //, bytes = 0;
    char getAPN[256]; //, apn_bytes = 0;
    char getDNS[256]; //, apn_bytes = 0;
    Bool sta = False; //设置ublox状态为网络初始化
    int8_t cnt;
    Bool isDNS = RunArg.DNSMode == 0x31;

    ClearDat(getIPcmd, '\0', 256);
    ClearDat(getAPN, '\0', 256);
    ClearDat(getDNS, '\0', 256);

    char* send_cmd[G350_TCP_Client_SIZE] = {
        getAPN,
        (char*) Send_ACTIVE_ARG,
        getDNS,
        (char*) Send_SET_TCP,
        (char*) Send_UPSND,
        (char*) Send_SET_DLINK_TIME,
        getIPcmd,
        (char*) Send_START_CONNECT
    };
    char* check_cmd[G350_TCP_Client_SIZE] = {(char*) Rec_OK, (char*) Rec_OK, (char*) Rec_SET_DNS, (char*) Rec_OK,
        (char*) Rec_OK, (char*) Rec_OK, (char*) Rec_OK, (char*) Rec_CONNECT};
    //    uint8_t needbytes[G350_TCP_Client_SIZE] = {4, 2, 28, 17, 30, 2, 2, 10};
    GetModuleArg_pf pf_th [G350_TCP_Client_SIZE] = {Null, Null, GetModule_DNS2IP, Null, GetModule_ClientIP, Null, Null, Null};
    uint16_t delay_10ms[G350_TCP_Client_SIZE] = {300, 300, 100, 100, 100, 100, 50, 300}; //提示返回04错误

    GetAPNCmd(getAPN); //获取APN
    TX04Arg2GPRSArg(G350_Arg.Server_IP); //获取IP

    G350_Arg.PORT = RunArg.Port; //获取端口号
    if (isDNS) GetDNSCmd(getDNS); //如果是域名解析的话，获取域名的AT指令

    for (cnt = 0; cnt < step; cnt++) {
        if (cnt == G350_SET_TCP_IP)//如果指令包含IP和PORT，那么重新获取指令
            GetIPPortCmd(getIPcmd);
        if ((!isDNS) &&(cnt == G350_GET_DNS))//判断是否需要域名解析
            continue;
        sta = UbloxSendATCmd(send_cmd[cnt], check_cmd[cnt], pf_th[cnt], delay_10ms[cnt]) ? True : False;
        ClrUARTnBuf(BufferRead_UART1);
        if (!sta) break;
    }
    return cnt; //) ? True : False;
}

/***************************************************************************
Function: Ublox_GSM_Dialing
Description: GSM短信模式
Input: 输入
Output: void
Return: 发送的组数下标
Others: none
 ***************************************************************************/
uint8_t Ublox_GSM_Dialing(uint8_t step) {
    Bool sta = False;
    int8_t cnt; //设置ublox状态为网络初始化

    const char* send_cmd[G350_GSM_Client_SIZE] = {
        Set_SMS_MODE,
        Set_SMS_CNMI,
        Set_SMS_CSMS
    };
    const char* check_cmd[G350_GSM_Client_SIZE] = {Rec_OK, Rec_OK, Rec_OK};
    const GetModuleArg_pf pf_th [G350_GSM_Client_SIZE] = {Null, Null, Null};
    const uint16_t delay_10ms[G350_GSM_Client_SIZE] = {20, 20, 20};

    for (cnt = 0; cnt < step; cnt++) {
        sta = UbloxSendATCmd(send_cmd[cnt], check_cmd[cnt], pf_th[cnt], delay_10ms[cnt]) ? True : False;
        ClrUARTnBuf(BufferRead_UART1);
        if (!sta) break;
    }
    return cnt; //
}

/***************************************************************************
Function: Ublox_GPRS_TCP_Server_Dialing
Description: 发送AT命令给Ublox
Input: 输入
Output: void
Return: True:发送成功；False:发送失败
Others: none
 ***************************************************************************/
//uint8_t Ublox_GPRS_TCP_Server_Dialing(void) {
//    //#define DeBug_Server
//    uint8_t sta;
//    uint8_t getip[256], ip_bytes = 0;
//    uint8_t getAPN[256], apn_bytes = 0;
//    //    uint8_t getIPcmd[256], bytes = 0;
//    uint8_t getport[256], port_bytes = 0;
//
//    ClearDat(getip, '\0', 256);
//    ClearDat(getAPN, '\0', 256);
//    ClearDat(getport, '\0', 256);
//
//    apn_bytes = UbloxGetAPN(getAPN);
//    if (UbloxSendATCmd(getAPN, apn_bytes - 1, Rec_OK, 2, 5, 2)) {
//        ClrUARTnBuf(BufferRead_UART1);
//        if (UbloxSendATCmd(Send_ACTIVE_ARG1, sizeof (Send_ACTIVE_ARG1) - 1, Rec_OK, 2, 3, 15)) {
//            ClrUARTnBuf(BufferRead_UART1);
//            if (UbloxSendATCmd(Send_SET_SERVER, sizeof (Send_SET_SERVER) - 1, Rec_OK, 2, 5, 2)) {
//                ClrUARTnBuf(BufferRead_UART1);
//                port_bytes = UbloxGetServerPort(getport);
//                if (UbloxSendATCmd(getport, port_bytes, Rec_OK, 2, 5, 1)) {
//                    ClrUARTnBuf(BufferRead_UART1);
//                    ip_bytes = UbloxGetServerIP(getip);
//                    //发送IP地址参数
//                    if (UbloxSendATCmd(getip, ip_bytes, Rec_OK, 2, 3, 5)) {
//                        ClrUARTnBuf(BufferRead_UART1);
//                        //发送连接
//                        if (UbloxSendATCmd(Send_SET_SERVER_TCP, sizeof (Send_SET_SERVER_TCP) - 1, Rec_OK, 2, 5, 1)) {
//                            ClrUARTnBuf(BufferRead_UART1);
//                            if (UbloxSendATCmd(Send_START_SAO, sizeof (Send_START_SAO) - 1, Rec_OK, 2, 5, 1)) {
//                                ClrUARTnBuf(BufferRead_UART1);
//                                if (UbloxSendATCmd(Send_SAVE_ARG, sizeof (Send_SAVE_ARG) - 1, (uint8_t*) "OK\r\n\0", 5, 5, 15)) {
//                                    ClrUARTnBuf(BufferRead_UART1);
//                                    if (UbloxSendATCmd(Send_CREG_Equ_2, sizeof (Send_CREG_Equ_2) - 1, Rec_OK, 2, 5, 15)) {//必须加
//                                        ClrUARTnBuf(BufferRead_UART1);
////                                        UART1SendString(Send_COPS, sizeof (Send_COPS) - 1);
//                                        if (UbloxWaitServer()) {
//                                            //                                            gGPRSIsONline = 1; //说明模块已经上线了
//                                            gTX04Sta = TX04_Sta_TCP_Server_Cop; //重启时间有效
//                                            if (UbloxWaitClient())
//                                                sta = Ublox_CONNECTED;
//                                            else {
//                                                User_PrintErrCode(UART2SendString, Ublox_USER_FAIL_09);
//                                                sta = Ublox_GPRS_TCP_CONNECT_NO_FAIL;
//                                            }
//                                        } else {
//                                            User_PrintErrCode(UART2SendString, Ublox_USER_FAIL_08);
//                                            sta = 102;
//                                        }
//                                    } else
//                                        sta = 103;
//                                } else
//                                    sta = 101;
//                            } else
//                                sta = 100;
//                        } else
//                            sta = 99;
//                    } else {
//                        sta = Ublox_GPRS_TCP_SET_IP_PORT_NO_REC;
//                        User_PrintErrCode(UART2SendString, Ublox_USER_FAIL_06);
//                    }
//                } else
//                    sta = Ublox_GPRS_TCP_SET_IP_PORT_NO_REC;
//            } else
//                sta = Ublox_GPRS_TCP_SET_TCP_NO_REC;
//        } else
//            sta = Ublox_GPRS_TCP_ATCTIVE_ARG_NO_FAIL;
//    } else {
//        sta = Ublox_GPRS_TCP_SET_APN_NO_REC;
//        User_PrintErrCode(UART2SendString, Ublox_USER_FAIL_17);
//    }
//#ifdef DeBug_Server
//    DeBug_PrintInfo("server end\r\n");
//    DeBug_PrintStrNum("sta", sta);
//#endif
//
//    return sta;
//}

/***************************************************************************
Function: UDPWriteStrByCmd
Description: 通过AT命令发送UDP数据给服务端
Input:数据指针地址，数据长度
Output: void
Return: 
Others: //AT+USOST=0,"122.228.138.254",5061,29
 ***************************************************************************/
void UDPWriteStrByCmd(const void * dat, const uint16_t bytes) {
    //#define UDP_IP_TEST //测试生成的数据
    char getIPcmd[256];
    uint16_t offset, getbytes = 0; //获取IP的变量以及字节数
    //    uint8_t bytesstr[6]; //端口号的字符串以及字节数

    offset = StrLen(Send_UDP_SEND_DAT);
    CopyDat(getIPcmd, Send_UDP_SEND_DAT, offset); //复制AT+USOST=0,
    *(getIPcmd + offset++) = '"';
    offset += TX04Arg2GPRSArg(getIPcmd + offset) - 1; //复制IP地址
    CopyDat(getIPcmd + offset, "\",", 2);
    offset += 2;
    //    getbytes = my_itoa(RunArg.Port, bytesstr); //复制PORT
    //    CopyDat(getIPcmd + offset, bytesstr, getbytes);
    getbytes = my_itoa(RunArg.Port, (uint8_t*) getIPcmd + offset);
    offset += getbytes;
#ifdef UDP_IP_TEST //断点1
    DeBug_PrintInfo("\r\nThis is UDP Send String 1 bk:\t");
    DeBug_PrintString(getIPcmd, all_bytes);
    DeBug_Print_rn();
#endif
    getIPcmd [offset++] = ',';
    //    getbytes = my_itoa(bytes, bytesstr);
    //    CopyDat(getIPcmd + offset, bytesstr, getbytes); ////复制发送的数据长度
    getbytes = my_itoa(bytes, (uint8_t*) getIPcmd + offset);
    offset += getbytes; //计算字节数
    CopyDat(getIPcmd + offset, _r_n, 3);
    offset += 3;
#ifdef UDP_IP_TEST //断点2
    DeBug_PrintInfo("\r\nThis is UDP Send String 2 bk:\t");
    DeBug_PrintString(getIPcmd, all_bytes);
    DeBug_Print_rn();
#endif
    if (UbloxSendATCmd(getIPcmd, _a, Null, 10)) {//发送udp发送字节的AT指令
        //        CopyDat(getIPcmd, dat, bytes);
        //        *(getIPcmd + bytes) = '\0'; //D
        //        UbloxSendATCmd(getIPcmd, Rec_OK, Null, 50); //发送数据 发送测试参数的时候包含\0
        UART1SendString(dat, bytes); //可以发送数据不含\0的数据           
    }
}

/***************************************************************************
Function: UDPMakeReadATCmd
Description: 通过UDP发送AT命令
Input:数据，数据指针
Output: 发送的字节数
Return: 
Others: //AT+USOST=0,"122.228.138.254",5061,29
 ***************************************************************************/
static uint8_t UDPMakeReadATCmd(uint16_t readnum, uint8_t*atcmd) {
    char readcmd[50];
    uint8_t readbytes = 0, cmdbytes = 0; //readdat[6],

    cmdbytes = sizeof (Send_UDP_Read) - 1;
    CopyDat(readcmd, Send_UDP_Read, cmdbytes); //复制指令数据
    //    readbytes = my_itoa(readnum, readdat); //将123=>"123"
    //    CopyDat(readcmd + cmdbytes, readdat, readbytes); //复制数据
    readbytes = my_itoa(readnum, (uint8_t*) readcmd + cmdbytes);
    cmdbytes += readbytes; //计算总体字节数
    CopyDat(readcmd + cmdbytes, _r_n, 3); //复制数据
    cmdbytes += 3;
    CopyDat(atcmd, readcmd, cmdbytes);
    return cmdbytes;
}

/***************************************************************************
Function: UDPReadStrByCmd
Description: 通过AT命令读取UDP协议服务器发送过来数据，比如该函数是发送数据的长度AT+USORF=0,10
Input: 数据的字节数，数据缓冲区域
Output: 实际返回字节数
Return: 
Others: none =0表示可以获取的字节数
 ***************************************************************************/
uint16_t UDPReadStrByCmd(uint8_t * Ublox_buf) {
    uint8_t readcmd[50];
    uint16_t readbytes = 0, cmdbytes = 0, getbytes = 0; //readdat[6], 
    uint16_t headpos_real, endpos_real, readnum_real = 0, offset;
    char port[8] = {'"', ',', 0, 0, 0, 0, 0, 0}, port_size = 0;


    cmdbytes = UDPMakeReadATCmd(0, readcmd); // AT+USORF=0,0 make
    if (UbloxSendATCmd((char*) readcmd, Rec_OK, Get_UDP_Rec_Byte, 200)) {// AT+USORF=0,0send
        readbytes = G350_Arg.UDP_BYTES; //全局变量（UDP变量）在Get_UDP_Rec_Byte函数
        if (readbytes) {//0
            if (readbytes > 200) {//如果数据溢出
                readbytes = 200;
            }
            cmdbytes = UDPMakeReadATCmd(readbytes, readcmd); // AT+USORF=0,n make
            if (cmdbytes) {
                UART1SendString(readcmd, cmdbytes);
                getbytes = UARTGetDat(BufferRead_UART1, Ublox_buf, 0xFF, 100);
                if (getbytes) {
                    port_size = my_itoa(RunArg.Port, ((uint8_t*) port + 2));
                    headpos_real = Str_Find_Head(Ublox_buf, port, getbytes, port_size + 2); //获取端口号的位置
                    offset = headpos_real - 1;
                    endpos_real = Str_Find_Head(Ublox_buf + offset, ",\"", getbytes - offset, 2); //判断有效数据 
                    offset += port_size + 3;
                    readnum_real = G350_Arg.UDP_BYTES = my_atoi((uint8_t*) Ublox_buf + offset, endpos_real - 8); //实际获取到的字节数
                    offset += endpos_real - 6;
                    CopyDat(Ublox_buf, Ublox_buf + offset, readnum_real);
                }
            }
        }
    }
    return readnum_real;
}

/***************************************************************************
Function: SMSWriteStrByCmd
Description: 发送短信 指令返回的数据
Input: 输入
Output: void
Return: True:发送成功；False:发送失败
Others: 
 ***************************************************************************/
void SMSWriteStrByCmd(const void *sms, const uint16_t smssize) {
    //#define DEBUG_SMS_Write_Test
    char tmp_send[256];
    uint16_t offset = 0, cnt = 0;
    Bool sta = False;
    uint8_t tmp_number[15] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    uint8_t cnt1 = 0, tmp = 0, size = 0;
    uint8_t sms_bytes;
    uint8_t sms_num[6];

    if (gSMSInfo) {
        CopyDat(sms_num, RunArg.SMSTargetNumber2, 6);
        size = HCD(RunArg.SMSTargetNumber2Length) / 2 + HCD(RunArg.SMSTargetNumber2Length) % 2;
        sms_bytes = RunArg.SMSTargetNumber2Length;
    } else {//默认，参数一
        CopyDat(sms_num, RunArg.SMSTargetNumber1, 6);
        size = HCD(RunArg.SMSTargetNumber1Length) / 2 + HCD(RunArg.SMSTargetNumber1Length) % 2;
        sms_bytes = RunArg.SMSTargetNumber1Length;
    }

    for (cnt = 0; cnt < size; cnt++) {//获取短信号码字符串
        tmp = *(sms_num + cnt);
        tmp_number[cnt1++] = (tmp >> 4) + 0x30;
        if (toupper(tmp_number[cnt1 - 1]) == 'F')
            break;
        tmp_number[cnt1++] = (tmp & 0x0f) + 0x30;
        if (toupper(tmp_number[cnt1 - 1]) == 'F')
            break;
    }
    offset = sizeof (Set_SMS_SEND) - 1; //获取偏移量
    CopyDat(tmp_send, (uint8_t*) Set_SMS_SEND, offset); //复制字符串 AT+CMGS=
    CopyDat((tmp_send + offset), (uint8_t*) "\"+86", 4); //复制字符串 "+86
    offset += 4; //偏移量+4
    CopyDat((tmp_send + offset), (uint8_t*) tmp_number, sms_bytes); //复制手机号码
    offset += sms_bytes; //偏移量+手机号码
    CopyDat((tmp_send + offset), (uint8_t*) "\"\r\0", 3); //复制字符串 “<CR>    
    offset = smssize;
    cnt = 0;
    do {
        Delay100ms(10); //看情况是否需要添加延时
        if (UbloxSendATCmd((char*) tmp_send, Rec_Allow_Write, Null, 50)) { //发送AT指令，等待返回‘>’            
            if (offset > 160) {//字节数大于200 数据溢出处理   
                UART1SendString(sms + cnt, 160); //发送短信消息，不能使用UbloxSendATCmd，数据中包换\0FFF
                offset -= 160;
                cnt += 160;
            } else {
                UART1SendString(sms + cnt, offset); //发送短信消息，不能使用UbloxSendATCmd，数据中包换\0FFF
                sta = True;
            }
            UART1SendChar(0x1a); //发送短信结束
            UART1SendChar('\0');
            Delay100ms(50); //看情况是否需要添加延时
            if (sta)
                break;
        }
    } while (1);
}
//#ifdef DEBUG_AT_TEST
//UART2SendString(sms, smssize);
//UART2SendChar((const uint8_t) 0x1a); //ctrl+z
//#endif
//}

/***************************************************************************
Function: SMSWriteRecUser
Description: 发送接收的到的数据提示
Input: 输入
Output: void
Return: True:发送成功；False:发送失败
Others: 
+CMGR: "REC UNREAD","+8618657158149",,"18/10/11,09:10:26+50"
00680065006C006C006F00200077006F0072006C0064FF01
OK 
SM:123454678989165;+8618653214721;16/10/21,08:59:38;"
SM:123454678989165;+8618657158149;18/10/11,13:16:49;"
 ***************************************************************************/
void SMSWriteRecUser(const void *sms, const uint16_t smssize) {
    uint8_t buffer[256], sendbyte = 0, offset;
    uint8_t get_data_start_op, get_data_end_op, get_phone_op, get_time_op;

    CopyDat(buffer, Send_User_SMS, 3);
    sendbyte = 3;
    get_data_start_op = Str_Find_Head(sms, "\"\r\n", smssize, 3); //获取内容 
    if (get_data_start_op) {
        get_data_end_op = Str_Find_Head(sms + get_data_start_op, _r_n2_OK, smssize, 6); //获取内容 
        if (get_data_end_op) {
            offset = get_data_end_op - 4;
            CopyDat(buffer + sendbyte, sms + get_data_start_op + 2, offset);
            sendbyte += offset;
            *(buffer + sendbyte++) = ';';
            get_phone_op = Str_Find_Head(sms, "\"+", smssize, 2); //获取手机号 
            get_time_op = Str_Find_Head(sms, "\",,\"", smssize, 4); //获取时间 
            if (get_phone_op && get_time_op && get_phone_op < get_time_op) {
                offset = get_time_op - get_phone_op - 1;
                CopyDat(buffer + sendbyte, get_phone_op + sms, offset); //获取手机号 
                sendbyte += offset;
                *(buffer + sendbyte++) = ';';
                offset = get_data_start_op - get_time_op - 7;
                CopyDat(buffer + sendbyte, sms + get_time_op + 3, offset); //获取时间
                sendbyte += offset;
                CopyDat(buffer + sendbyte, ";\"\r\n", 4); //获取手机号 
                sendbyte += 4;
                UART2SendString(buffer, sendbyte); //发送短接收到的数据给用户界面
            }
        }
    }
}

/***************************************************************************
Function: SMSReadStrByCmd
Description: 生成读取短信的AT命令并发送给模组
Input: 短信的ID号
Output: void
Return: 获取到的数据字节
Others: none
 ***************************************************************************/
static uint16_t SMSReadStrByCmd(const uint16_t id, uint8_t* Ublox_buf) {
    uint8_t send_getSMS[50], id_str[6], id_str_size = 0, offset = 0;
    uint8_t databuf[240]; //短信最大的长度是160内容+提示URC62+8字节\r\n\r\nOK\r\n
    uint16_t get_offset = 0, getbytes = 0, end_op = 0, URC_op = 0, buf_getbytes = 0;

    CopyDat(send_getSMS, '\0', 50); //清除数据
    offset = sizeof (Set_SMS_READ) - 1; //计算发送字节
    CopyDat(send_getSMS, Set_SMS_READ, offset); //复制AT指令
    id_str_size = my_itoa(id, id_str); //计算发送字节
    CopyDat(send_getSMS + offset, id_str, id_str_size); //复制ID号
    offset += id_str_size; //计算发送字节
    CopyDat(send_getSMS + offset, (const uint8_t*) "\r\n", 2); //追加回车换行
    offset += 2; //计算发送字节
    UART1SendString(send_getSMS, offset); //发送获取短信AT指令

    buf_getbytes = UARTGetDat(BufferRead_UART1, databuf, 240, 300); //规定300ms时间内获取短信内容
    if (buf_getbytes) {
        offset = StrLen(SMS_CKC_CMGR);
        URC_op = Str_Find_Head(databuf, SMS_CKC_CMGR, buf_getbytes, offset);
        end_op = Str_Find_Head(databuf, _r_n2_OK, buf_getbytes, 6);
        if (URC_op && end_op) {
            offset += URC_op; //数组的偏移量，开始截取的位置
            get_offset = end_op - offset + 5; //计算获取的字节数
            CopyDat(Ublox_buf, databuf + offset, get_offset);
            getbytes += get_offset; // += getbytes;
        }
    }
    return getbytes;
}

/***************************************************************************
Function: UDPSendDat2Sever
Description: UDP客服端模式下，数据发送服务端，批量发送数据
Input:Ublox_buf，getsize
Output: none
Return: none
Others: 大于200字节分段发送，存在数据分还几次发送
 ***************************************************************************/
void UDPSendDat2Sever(const void *buffer, uint16_t getsize) {
    uint16_t getbytes = getsize, cnt = 0;

    do {//发送数据
        if (getbytes > 200) {//字节数大于200 数据溢出处理   
            UDPWriteStrByCmd(buffer + cnt, 200);
            getbytes -= 200;
        } else {
            UDPWriteStrByCmd(buffer + cnt, getbytes);
            break;
        }
        cnt += 200;
    } while (1);
}

/***************************************************************************
Function: GSMSendMessage
Description: GMS模式下，数据发送短信
Input:Ublox_buf，getsize
Output: none
Return: none
Others: 发送成功要返回OK
 ***************************************************************************/
void GSMSendMessage(const void *Ublox_buf, uint16_t getsize) {
    Bool sta = True;
    //获取完整的数据
    do {
        if (U2STAbits.URXDA) {//如果有一个字节，那么将字节数获取，不经过中断函数,不需要延时
            BufferWrite_UART2();
        } else {
            Delay10ms(1); //1200bit/s
            if (U2STAbits.URXDA) {//如果有一个字节，那么将字节数获取，不经过中断函数,不需要延时
                BufferWrite_UART2();
            } else
                sta = False;
        }
        while (BufferRead_UART2((uint8_t*) Ublox_buf + getsize)) {
            getsize++;
            if (getsize >= 160) {//字节数大于200 数据溢出处理   
                SMSWriteStrByCmd(Ublox_buf, 160); //汉字数70,英文140。
                getsize = 0;
                break;
            }
        }
    } while (sta);
    if (getsize) {
        SMSWriteStrByCmd(Ublox_buf, getsize);
        UART2SendString((const uint8_t*) "SMS_OK\r\n", 8);
    }
}

/***************************************************************************
Function: UbloxUDPGetURC
Description: 发送AT命令给Ublox
Input: 输入
Output: void
Return: True:发送成功；False:发送失败
Others: none
 ***************************************************************************/
uint16_t UbloxUDPGetURC(uint8_t *Ublox_buf, uint16_t bytes) {
    return UDPReadStrByCmd(Ublox_buf); //主动获取接收到的字节数
}

/***************************************************************************
Function: SMSGetURC
Description: 发送AT命令给Ublox,获取URC，发送AT指令读取短信，返回读取到的内容
Input: 短信消息缓冲区
Output: 缓冲区数据、数据大小、短信ID号
Return: 短信ID号
Others: 
 ***************************************************************************/
static uint16_t SMSGetURC(uint8_t* Ublox_buf, uint16_t* buf_bytes) {
    uint8_t databuf[240], sms_id[6]; //, cmdtype; //短信最大的长度是160内容+提示URC62+8字节\r\n\r\nOK\r\n
    uint16_t offset = 0, getbytes = 0, end_op = 0, URC_op = 0, buf_getbytes = 0, sms_ID = 0;

    buf_getbytes = UARTGetDat(BufferRead_UART1, databuf, 240, 100); //1s刷新字节
    if (buf_getbytes) {
        offset = StrLen(Rec_SMS_NEW_TIP);
        URC_op = Str_Find_Head(databuf, Rec_SMS_NEW_TIP, buf_getbytes, offset); //获取URC提示+CMTI: "ME",90
        Delay100ms(20); //等待接收另外一个URC
        if (URC_op) {
            offset += URC_op - 1; //数据长度减一
            end_op = Str_Find_Head(databuf + offset, _r_n, buf_getbytes, 2) - 1; //获取数据的结尾
            if (end_op) {//短信ID
                CopyDat(sms_id, databuf + offset, end_op); //获取短信的ID字符串
                sms_ID = my_atoi(sms_id, end_op); //ID字符串转化为数字
                getbytes = SMSReadStrByCmd(sms_ID, Ublox_buf); //发送获取短信指令
            }
        }
    }
    *buf_bytes = getbytes;
    return sms_ID;
}

/***************************************************************************
Function: UbloxSMSGetURC
Description: 发送AT命令给Ublox,获取URC，发送AT指令读取短信，返回读取到的内容
Input: 输入
Output: void
Return: True:发送成功；False:发送失败
Others: //指令全部换乘str  str->hex的需要处理
 ***************************************************************************/
uint16_t UbloxSMSGetURC(uint8_t* Ublox_buf, uint16_t bytes) {
    uint8_t cmdtype; //短信最大的长度是160内容+提示URC62+8字节\r\n\r\nOK\r\n
    uint16_t offset = 0, getbytes = 0, end_op = 0, URC_op = 0, buf_getbytes = 0, sms_ID = 0, get_offset, cmd_op = 0;

    sms_ID = SMSGetURC(Ublox_buf, &buf_getbytes); //获取短信内容
    //判断是否是写指令，如果是写指令的话，那么就继续读取一条指令
    cmd_op = IsGetMasthead(Ublox_buf, buf_getbytes); //寻找+TXYBJT
    if (cmd_op) {
        cmdtype = TX04GetCMDType(Ublox_buf, buf_getbytes); //判断指令类型
        if ((cmdtype == CMD_TESTW0) || (cmdtype == CMD_TESTW2)) {//如果是写指令的话
            buf_getbytes += SMSReadStrByCmd(sms_ID + 1, Ublox_buf + buf_getbytes); //发送获取短信指令
            if (buf_getbytes > 370) {//如果获取到的数据字节数大于370个字节的话，即获取到第二个短信
                //将数据连接，开始判断第一个短信的位置
                offset = cmd_op - 1;
                end_op = Str_Find_Head(Ublox_buf, _r_n2_OK, buf_getbytes, 6);
                if (end_op) {
                    get_offset = end_op - offset - 3; //计算获取的字节数
                    CopyDat(Ublox_buf, Ublox_buf + offset, get_offset); //拷贝有效的字节数
                    getbytes = get_offset; //重新开始计算获取的字节数
                    //判断后面一个数据的开始地址
                    offset = end_op + 5; //设置偏移量，确保获取到正确的数据
                    URC_op = Str_Find_Head(Ublox_buf + offset, __r_n, buf_getbytes, 3); //获取到数据的开始
                    end_op = Str_Find_Head(Ublox_buf + offset, _r_n2_OK, buf_getbytes, 6); //获取数据的结尾
                    if (URC_op && end_op) {//判断是否都获取到
                        offset += URC_op + 2; //数组的偏移量，开始截取的位置
                        get_offset = end_op - URC_op - 5; //计算获取的字节数
                        CopyDat(Ublox_buf + getbytes, Ublox_buf + offset, get_offset);
                        getbytes += get_offset; // += getbytes;  
                        //转化数据                        
                        offset = 14;
                        get_offset = Char2Hex(Ublox_buf + offset, getbytes - offset, Ublox_buf + offset);
                        getbytes = get_offset + offset; //返回字节数                                                
                    }
                }
            }
        } else//如果是其他指令
            getbytes = buf_getbytes;
    } else {//如果是短信消息
        getbytes = buf_getbytes;
    }
    return getbytes;
}

/***************************************************************************
Function: UbloxCloseTCPClient
Description: 关闭Ublox的TCP连接，
Input: 发送前延时，发送后延时
Output: 是否关闭成功
Return: True:发送成功；False:发送失败
Others: 单位10ms
 ***************************************************************************/
Bool UbloxCloseTCPClient(void) {
    Bool sta = True;
    //清楚缓冲区
    if (gTX04Sta == TX04_Sta_TCP_Cop) {
        ClrUARTnBuf(BufferRead_UART1);
        LP_Delay(100); //避免上线后，立刻EN置低 导致+++数据发送给远程 800ms
        if (UbloxSendATCmd(Send_ToAT, Rec_DISCONNECT, Null, 200)
                && UbloxSendATCmd(Send_CLOSE_CONNET, Rec_OK, Null, 200)) {
            LP_Delay(50); //避免下线后，没有关闭连接点 500ms
        } else
            sta = False;
    }
    return sta;
}

/***************************************************************************
Function: UbloxSwitchFlow
Description: 发送AT命令,切换模式
Input: 延时时间，模式
Output: 切换是否成功
Return: True:切换成功；False:切换失败
Others: none
 ***************************************************************************/
Bool UbloxSwitchFlow(const uint8_t mode) {
    Bool sta = False;

    LP_Delay(1); //避免上线后，立刻EN置低 导致+++数据发送给远程
    if (mode != DATA2CMD)
        sta = UbloxSendATCmd(Send_START_CONNECT, Rec_CONNECT, Null, 100);
    else
        sta = UbloxSendATCmd(Send_ToAT, Rec_DISCONNECT, Null, 200);
    LP_Delay(1); //避免上线后，立刻EN置低 导致+++数据发送给远程

    return sta;
}

/***************************************************************************
Function: UbloxDisablePSD
Description:通过AT指令关闭PSD=0的参数
Input: void
Output: void
Return: ture:close success ;False:close：fail
Others: none
 ***************************************************************************/
Bool UbloxDisablePSD(void) {
    uint8_t sta = False;

    if (UbloxSendATCmd(Send_DISABLE_ARG, Rec_OK, Null, 40)) {//close tcp and return result
        sta = True;
    }
    //    if (after_delay_ms)
    //        LP_Delay(after_delay_ms);
    return sta;
}

