//#include "user.h"
//#include "string.h"
//#include "p24FV32KA301.h"
#include "SerialBuffer.h"

/**********************************定义****************************************/
#define BUFFERMAX 64
//static uint8_t Buffer_uart1[BUFFERMAX];
uint8_t Buffer_uart1[BUFFERMAX];
/*static*/ uint8_t bufferWptr_uart1 = 0;
/*static */uint8_t bufferRptr_uart1 = 0;

//static uint8_t Buffer_uart2[BUFFERMAX];
uint8_t Buffer_uart2[BUFFERMAX];
/*static*/ uint8_t bufferWptr_uart2 = 0;
/*static*/ uint8_t bufferRptr_uart2 = 0;

uint8_t Buffer_uart3[BUFFERMAX];
/*static*/ uint8_t bufferWptr_uart3 = 0;
/*static*/ uint8_t bufferRptr_uart3 = 0;

/*************************************
Function: BufferWrite 
Description: 写数据到环形缓冲区
Input: 串口号，1和2 
Output: 无
 *************************************/
void BufferWrite_UART1(void) {
    uint8_t tmp;
    if (bufferWptr_uart1 == (bufferRptr_uart1 - 1)) {//如果缓冲区已满 写的速度比读的速度块
        tmp = U1RXREG; //将溢出的数据，丢弃
        return;
    }
    Buffer_uart1[bufferWptr_uart1] = U1RXREG;
    bufferWptr_uart1++;
    bufferWptr_uart1 = bufferWptr_uart1 - ((bufferWptr_uart1 >> 6) << 6);
}

/*************************************
Function: BufferWrite 
Description: 写数据到环形缓冲区
Input: 串口号，1和2 
Output: 无
 *************************************/
void BufferWrite_UART2(void) {
    uint8_t tmp = 0;
    if (bufferWptr_uart2 == (bufferRptr_uart2 - 1)) {//如果缓冲区已满 写的速度比读的速度块
        tmp = U2RXREG; //将溢出的数据，丢弃
        return;
    }
    Buffer_uart2[bufferWptr_uart2] = U2RXREG;
    bufferWptr_uart2++;
    bufferWptr_uart2 = bufferWptr_uart2 - ((bufferWptr_uart2 >> 6) << 6); //bufferWptr_uart2%BUFFERMAX
}

/*************************************
Function: BufferWrite 
Description: 写数据到环形缓冲区
Input: 串口号，1和2 
Output: 无
 *************************************/
void BufferWrite_UART3(void) {
    uint8_t tmp = 0;
    if (bufferWptr_uart3 == (bufferRptr_uart3 - 1)) {//如果缓冲区已满 写的速度比读的速度块
        tmp = U3RXREG; //将溢出的数据，丢弃
        return;
    }
    Buffer_uart3[bufferWptr_uart3] = U3RXREG;
    bufferWptr_uart3++;
    bufferWptr_uart3 = bufferWptr_uart3 - ((bufferWptr_uart3 >> 6) << 6); //bufferWptr_uart3%BUFFERMAX
}

/*************************************
Function:  BufferRead
Description: 读环形缓冲区
Input: 数据地址 
Output: 1：读取成功，0：读取失败
 *************************************/
bool BufferRead_UART1(uint8_t *data) {
    if (bufferRptr_uart1 == bufferWptr_uart1) {
        return 0;
    }
    *data = Buffer_uart1[bufferRptr_uart1];
    bufferRptr_uart1++;
    bufferRptr_uart1 = bufferRptr_uart1 - ((bufferRptr_uart1 >> 6) << 6); //bufferRptr_uart1 % BUFFERMAX; 
    return 1;
}

/*************************************
Function:  BufferRead
Description: 读环形缓冲区
Input: 数据地址 
Output: 1：读取成功，0：读取失败
 *************************************/
bool BufferRead_UART2(uint8_t *data) {
    if (bufferRptr_uart2 == bufferWptr_uart2) {
        if (U2STAbits.OERR)
            U2STAbits.OERR = 0; //写数据满导致FIFO溢出，而没有清除，接受数据没有
        return 0;
    }
    *data = Buffer_uart2[bufferRptr_uart2];
    bufferRptr_uart2++;
    bufferRptr_uart2 = bufferRptr_uart2 - ((bufferRptr_uart2 >> 6) << 6);
    //bufferRptr_uart2 % BUFFERMAX;//bufferRptr_uart2-(bufferRptr_uart2>>8)<<8;
    return 1;
}

/*************************************
Function:  BufferRead
Description: 读环形缓冲区
Input: 数据地址 
Output: 1：读取成功，0：读取失败
 *************************************/
bool BufferRead_UART3(uint8_t *data) {
    if (bufferRptr_uart3 == bufferWptr_uart3) {
        if (U3STAbits.OERR)
            U3STAbits.OERR = 0; //写数据满导致FIFO溢出，而没有清除，接受数据没有
        return 0;
    }
    *data = Buffer_uart3[bufferRptr_uart3];
    bufferRptr_uart3++;
    bufferRptr_uart3 = bufferRptr_uart3 - ((bufferRptr_uart3 >> 6) << 6);
    //bufferRptr_uart3 % BUFFERMAX;//bufferRptr_uart3-(bufferRptr_uart3>>8)<<8;
    return 1;
}

/*************************************
Function: UARTDataIsRight
Description: 根据结构体的内容获取有效数据和有效长度
Input: 数据结构体
Output: 是否获取到数据
Notice：字节数不能大于256 取数据的时间可能短   
 *************************************/
bool UARTDataIsRight(StrCmp * strcmp) {//注意
    bool IsFind = false; //记录字节数
    uint8_t cnt = 0/*校验寻找循环地址*/, cnt1 = 0/*校验判断循环地址*/, cnt2/*赋值地址*/, /*offset,*/ byte = 0;

    if (!(strcmp->Check_len) || !(strcmp->Source_len))//如果设置的字节数为0的话，返回错误
        return false; //为获取

    while (cnt < strcmp->Source_len) {
        if (*(strcmp->SourceData + cnt) == *(strcmp->CheckData)) {//如果数据==head的话           
            for (cnt1 = 1; cnt1 < strcmp->Check_len; cnt1++) {//获取帧头的数据长度               
                if (*(strcmp->SourceData + cnt + cnt1) == *(strcmp->CheckData + cnt1)) {//如果获取到数据和帧头一样，那么继续获取数据，反之退出
                    IsFind = true;
                    continue;
                } else {
                    IsFind = false;
                    break;
                }
            }
        }
        if (IsFind) break; //如果找到数据，退出寻找帧头程序
        cnt++; //校验位置加1
    }

    if (IsFind) {//如果存在接受的字节数且找到帧头
        if (strcmp->Get_len < strcmp->Check_len) {
            byte = strcmp->Get_len; //获取字节小于校验字节,比如只需要校验不需要获取数据
            for (cnt2 = 0; cnt2 < byte; cnt2++) //获取帧头数据
                *(strcmp->GetData + cnt2) = *(strcmp->CheckData + cnt2);
        } else {//如果要获取的字节数大于帧头数据，需要判断有效的剩余字节数数量
            if (strcmp->Source_len - cnt < strcmp->Get_len)//如果获取数据大于有效数据，
                for (cnt2 = 0; cnt2 < strcmp->Source_len - cnt; cnt2++) //获取剩余数据
                    *(strcmp->GetData + cnt2) = *(strcmp->SourceData + cnt + cnt2);
            else
                for (cnt2 = 0; cnt2 <= strcmp->Get_len; cnt2++) //获取剩余数据
                    *(strcmp->GetData + cnt2) = *(strcmp->SourceData + +cnt + cnt2);
        }
        strcmp->Real_len = cnt2; //实际获取到的长度
        return true;
    }
    strcmp->Real_len = 0;
    return false;
}

/*************************************
Function: UARTGetData  
Description: 通过指定串口获取函数，获取数据保存至数据地址
Input: UARTn获取函数，获取数据的地址
Output: 字节数
Notice：字节数不能大于256    
 *************************************/
uint8_t UARTGetData(UARTn f_uart, uint8_t*Get_Data, uint8_t bytes) {//, const uint8_t get_size) {//注意'\0'
    uint8_t byte = 0;
    while (bytes > byte) {
        if (f_uart(Get_Data + byte))
            byte++;
        else
            break;
    }
    return byte;
}

/*************************************
Function: ClearBuffer
Description: 清楚缓冲区数据
Input: 指定清楚的串口
Output: 无
Notice：清楚串口缓冲区
 *************************************/
void ClearBuffer(UARTn f_uart) {
    uint8_t tmp;
    while (f_uart(&tmp));
}
//将UARTGetData和

//bool UARTIsGet(UARTn f_uart, uint8_t*Get_Source, const uint8_t get_size, const uint8_t *head, const uint8_t head_size) {
//    StrCmp stcp;
//    uint8_t Source_tmp[50]; //临时变量
//    //    bool b = false;
//
//    stcp->Source_len = UARTGetData(f_uart, Source_tmp);
//    if (stcp->Source_len>sizeof (Source_tmp) / sizeof (uint8_t))//限制处理，单次采集数据大于50个字节，如果大于50个字节，那么设置为50个字节
//        stcp->Source_len = 50;
//    stcp->SourceData = Source_tmp;
//    stcp->CheckData = head;
//    stcp->Check_len = head_size;
//    stcp->GetData = Get_Source;
//    stcp->Get_len = get_size;
//
//    return UARTDataIsRight(stcp);
//}



