#include "HL6528.h"
#include <string.h>
//#include <math.h>
#include <stdlib.h>
#include  <libq.h>
#include "WGC.h"
#include "Common.h"
//#include "includes.h"
//#include <stdbool.h>
//#include "cJSON.h"


//extern OS_EVENT* sem1, *sem2; //上线拨号任务标志

//struct ATCommand {
const uint8_t K3[] = {"AT&K3\r\n"}; //{"AT&K3\r\n"};
const uint8_t D1[] = {"AT&D1\r\n"}; //{"AT&K3\r\n"};
const uint8_t AT[] = {"AT\r\n"};
const uint8_t CREG_2[] = {"AT+CREG=2\r\n"};
const uint8_t OK[] = {"OK"};
const uint8_t CPIN[] = {"AT+CPIN?\r\n"};
const uint8_t READY[] = {"+CPIN: READY"};
const uint8_t CIMI[] = {"AT+CIMI\r\n"};
const uint8_t CREG[] = {"AT+CREG?\r\n"};
const uint8_t CGREG[] = {"AT+CGREG?\r\n"};
const uint8_t _5[] = {",5"};
const uint8_t _1[] = {",1"};
const uint8_t CSCA[] = {"AT+CSCA\r\n"};
//const uint8_t KCNXCFG[] = {"AT+KCNXCFG"};
const uint8_t KCNXCFG[] = {"AT+KCNXCFG=1,\"GPRS\",\"CMNET\"\r\n"};
const uint8_t KTCPCFG[] = {"AT+KTCPCFG=1,0,\"};//139.196.122.159\",5080\r\n\n"};
uint8_t KTCPCFG1[] = {"AT+KTCPCFG=1,0,\"183.230.140.140\",11811\r\n\n"};
//const uint8_t KTCPCFG[] = {"AT+KTCPCFG=1,0,\"183.246.74.68\",5070\r\n"};//TR 
//const uint8_t KTCPCFG[] = {"AT+KTCPCFG=1,0,\"183.230.40.40\",1811\r\n"};//移动ONENET
const uint8_t KTCPSTART[] = {"AT+KTCPSTART=1\r\n"};
const uint8_t CONNECT[] = {"CONNECT"};
const uint8_t KTCPCLOSE[] = {"AT+KTCPCLOSE=1,1\r\n"};
const uint8_t KTCPDEL[] = {"AT+KTCPDEL=1\r\n"};


//static bool HL6528SendCmd(const uint8_t *ss, const uint8_t* cs, const uint8_t* cs1, const uint8_t csl, const uint8_t cnt);

void HL6528_Init(void) {
    //初始化端口
    PWRON_TRIS = 0; //PWN_ON 6528芯片电源控制
    PWR_TRIS = 0; //外部控制6528芯片电源
    DSR_TRIS = 0; //数据设备请求    
    DTR_TRIS = 0; //数据终端请求
    RTS_TRIS = 0; //请求发送数据
    CTS_TRIS = 0; //请求接受数据  
    PWR = 0;
    PWRON = 0;
    CTS = 0;
    RTS = 0;
    DSR = 0;
    DTR = 0;
    //    UART2_Init();
}

/*输入变量：发送字符串地址ss、接受字符串、接受字符串长度、发送字符串长度、对比字符串地址、对比字符串长度、发送间隔时间、发送次数**/
static bool HL6528SendCmd(const uint8_t *ss, const uint8_t* cs, const uint8_t* cs1, const uint8_t csl, const uint8_t cnt) {
    uint8_t cnt_tmp = 0;
    bool b_sta = false;
    StrCmp stcp;
    uint8_t tmp[50];
    do {
        cnt_tmp += 1;
        UART2_SendString(ss); //发送AT指令                               
        Delay1s(3); //(0, 0, 3, 0); //延时1s
        U2Rx4Byte();
        stcp.SourceData = tmp;
        stcp.Source_len = UARTGetData(BufferRead_UART2, stcp.SourceData, 50); //获取mark
        stcp.CheckData = (uint8_t*) cs;
        stcp.Check_len = csl;
        stcp.GetData = NULL;
        stcp.Get_len = 0;
        stcp.Real_len = 0;

        if (UARTDataIsRight(&stcp)) {
            b_sta = true;
            break;
        }

        if (cs1 != NULL) {//如果第二个校验数据不是NULL，那么进行第二个数据头的处理，判断处理。
            stcp.CheckData = (uint8_t*) cs1;
            if (UARTDataIsRight(&stcp)) {
                b_sta = true;
                break;
            }
        }

    } while (cnt > cnt_tmp);
    ClearBuffer(BufferRead_UART2);
    return b_sta;
}

uint8_t HL6528_DialingIsERR(void) {
    uint8_t sta;
    //    uint8_t ip_port[25] = {'\0'};

    //    HL6528_GetIP_Port();
    PWR = 1;
    PWRON = 1;
    CTS = 0;
    RTS = 0;
    DSR = 0;
    DTR = 0;
    Delay1s(2);
    if (HL6528SendCmd(D1, OK, NULL, 2, 2)) {
        if (HL6528SendCmd(CPIN, READY, NULL, 8, 2)) {
            if (HL6528SendCmd(CREG, _5, _1, 2, 10)) {//设置网络模式
                if (HL6528SendCmd(KCNXCFG, OK, NULL, 2, 3)) {
                    //HL6528_GetIP_Port(); //刷新IP地址和端口号
                    if (HL6528SendCmd(KTCPCFG1, OK, NULL, 2, 3)) {
                        if (HL6528SendCmd(KTCPSTART, CONNECT, NULL, 5, 5)) {
                            sta = 0;
                        } else
                            sta = 6; //未开启TCP，
                    } else
                        sta = 5; //设置TCP失败
                } else
                    sta = 4; //设置APN的问题
            } else
                sta = 3; //手机信号未找到 电压不足可能导致
        } else
            sta = 2; //手机卡未插入
    } else
        sta = 1; //模块损坏
    return sta;
}

void HL6528_Close(void) {
    uint8_t tmp[20];
    StrCmp stcp;
    ClearBuffer(BufferRead_UART2);
    do {
        DSR = 1; //切换数据至AT命令 mark
        DTR = 1;
        Delay1s(1); //(0, 0, 1, 0); //延时1s
        DSR = 0; //请求发送数据
        DTR = 0;
        Delay1s(1); //(0, 0, 1, 0); //延时1s
        stcp.SourceData = tmp;
        stcp.Source_len = UARTGetData(BufferRead_UART2, stcp.SourceData, 20); //获取mark
        stcp.CheckData = (uint8_t*) OK;
        stcp.Check_len = 2;
        stcp.GetData = NULL;
        stcp.Get_len = 0;
        stcp.Real_len = 0;
    } while (UARTDataIsRight(&stcp)); //等待接受成功下线返回OK
    if (HL6528SendCmd(KTCPCLOSE, OK, NULL, 2, 2))//关闭并删除TCP的ID通道
        HL6528SendCmd(KTCPDEL, OK, NULL, 2, 2);
    Delay1s(1); // (0, 0, 1, 0); //延时1s    
    PWR = 0; //电源控制
    PWRON = 0; //电源关闭
    CTS = 0; //请求接受
    RTS = 0; //请求发送
    DSR = 0; //设备
    DTR = 0; //终端
    UART2_Close();
}



//static void HL6528_IOStart(void) {
//    PWR = 1;
//    PWRON = 1;
//    CTS = 0;
//    RTS = 0;
//    DSR = 0;
//    DTR = 0;
//}
//
//static void HL6528_IOClose(void) {
//    PWRON = 0;
//    PWR = 0;
//    CTS = 1;
//    RTS = 1;
//    DSR = 1;
//    DTR = 1;
//}

void HL6528_GetIP_Port(void) {
    uint8_t net_addr[25] = {'\0'};
    uint8_t str_tmp[4] = {1, 2, 3, 4};
    uint8_t cnt;
    uint8_t all_bytes = 0;

    //获取网络地址
    all_bytes = my_itoa(WGCIPbits.IP3, net_addr);
    net_addr[all_bytes] = '.';
    net_addr[all_bytes + 1] = '\0';
    all_bytes = all_bytes + 1;

    all_bytes += my_itoa(WGCIPbits.IP2, str_tmp);
    strcat(net_addr, str_tmp);
    net_addr[all_bytes ] = '.';
    net_addr[ all_bytes + 1] = '\0';
    all_bytes = all_bytes + 1;

    all_bytes += my_itoa(WGCIPbits.IP1, str_tmp);
    strcat(net_addr, str_tmp);
    net_addr[all_bytes ] = '.';
    net_addr[ all_bytes + 1] = '\0';
    all_bytes = all_bytes + 1;

    all_bytes += my_itoa(WGCIPbits.IP0, str_tmp);
    strcat(net_addr, str_tmp);
    net_addr[ all_bytes ] = '"';
    net_addr[all_bytes + 1 ] = ',';
    net_addr[ all_bytes + 2] = '\0';
    all_bytes = all_bytes + 2;

    all_bytes += my_itoa(WGCPORT, str_tmp);
    strcat(net_addr, str_tmp);
    net_addr[ all_bytes ] = '\r';
    net_addr[ all_bytes + 1] = '\n';
    net_addr[ all_bytes + 2] = '\0';
    all_bytes = all_bytes + 2;
    //   uint8_t KTCPCFG1[] = {"AT+KTCPCFG=1,0,\"183.230.40.40\",1811\r\n\n"};
    for (cnt = 0; cnt < all_bytes; cnt++)
        *(KTCPCFG1 + 16 + cnt) = *(net_addr + cnt);
    //    return all_bytes;
}





