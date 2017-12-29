//#include "user.h"
//#include "string.h"
//#include "p24FV32KA301.h"
#include "SerialBuffer.h"

/**********************************定义****************************************/
#define BUFFERMAX 64
//static uint8_t Buffer_uart1[BUFFERMAX];
uint8_t Buffer_uart1[BUFFERMAX];
static uint8_t bufferWptr_uart1 = 0;
static uint8_t bufferRptr_uart1 = 0;

//static uint8_t Buffer_uart2[BUFFERMAX];
uint8_t Buffer_uart2[BUFFERMAX];
/*static*/ uint8_t bufferWptr_uart2 = 0;
/*static*/ uint8_t bufferRptr_uart2 = 0;

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
Function: UARTnDataIsGet  
Description: deadline时间内，从串口缓冲区取bytes个字节数据，判断帧头head 
 * 校验方式 帧头+CRC16
Input: 
Output: 是否获取到数据
Notice：字节数不能大于256 取数据的时间可能短   
 *************************************/
uint8_t UARTIsGet(UARTn f_uart, uint8_t*Get_Source, const uint8_t get_size, const uint8_t *head, const uint8_t head_size) {//注意'\0'
    bool IsFind = false; //记录字节数
    uint8_t cnt = 0, byte = 0;
    uint8_t UART_Tmp = 0; //临时变量周期限制
    //    uint8_t UART_Tm[10];

    while (f_uart(&UART_Tmp)) {//获取一个数据
        if (UART_Tmp == *head) {//如果数据==head的话
            //            UART_Tm[0] = UART_Tmp;
            for (cnt = 1; cnt < head_size; cnt++) {//获取帧头的数据长度
                f_uart(&UART_Tmp);
                if (UART_Tmp == *(head + cnt)) {//如果获取到数据和帧头一样，那么继续获取数据，反之退出
                    IsFind = true;
                    continue;
                } else {
                    IsFind = false;
                    break;
                }
            }
        }
        if (IsFind) break; //如果找到数据，退出寻找帧头程序
    }
    if (!get_size && IsFind)
        return 0xFF; //表示找到
    else if (IsFind) {//如果存在接受的字节数且找到帧头
        byte = (get_size < head_size) ? get_size : head_size; //获取字节小于校验字节
        for (cnt = 0; cnt < byte; cnt++) //获取帧头数据
            *(Get_Source + cnt) = *(head + cnt);
        for (cnt = head_size; cnt < get_size; cnt++) //获取剩余数据
            if (!f_uart(Get_Source + byte++))
                break;
    }
    return byte;
}

void ClearBuffer2(void) {
    uint8_t tmp;
    while (BufferRead_UART2(&tmp));
}
