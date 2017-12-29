#include "user.h"
#include "string.h"
//#include "p24FV32KA301.h"

/**********************************定义****************************************/
#define BUFFERMAX 256
//static u8 Buffer_uart1[BUFFERMAX];
u8 Buffer_uart1[BUFFERMAX];
static u8 bufferWptr_uart1 = 0;
static u8 bufferRptr_uart1 = 0;

//static u8 Buffer_uart2[BUFFERMAX];
u8 Buffer_uart2[BUFFERMAX];
/*static*/ u8 bufferWptr_uart2 = 0;
/*static*/ u8 bufferRptr_uart2 = 0;

/*************************************
Function: BufferWrite 
Description: 写数据到环形缓冲区
Input: 串口号，1和2 
Output: 无
 *************************************/
void BufferWrite_UART1(void) {
    u8 tmp;
    if (bufferWptr_uart1 == (bufferRptr_uart1 - 1)) {//如果缓冲区已满 写的速度比读的速度块
        tmp = U2RXREG; //将溢出的数据，丢弃
        return;
    }
    Buffer_uart1[bufferWptr_uart1] = U1RXREG;
    bufferWptr_uart1++;
    bufferWptr_uart1 = bufferWptr_uart1 - ((bufferWptr_uart1 >> 8) << 8);
    //bufferWptr_uart1 % BUFFERMAX; //bufferWptr_uart1 - (bufferWptr_uart1 >> 8) << 8; //// X - (X >> n) << n 取余数
    //    if (bufferWptr_uart1 >= 6)
    //        Nop();
}

/*************************************
Function: BufferWrite 
Description: 写数据到环形缓冲区
Input: 串口号，1和2 
Output: 无
 *************************************/
void BufferWrite_UART2(void) {
    u8 tmp = 0;
    if (bufferWptr_uart2 == (bufferRptr_uart2 - 1)) {//如果缓冲区已满 写的速度比读的速度块
        tmp = U2RXREG; //将溢出的数据，丢弃
        return;
    }
    Buffer_uart2[bufferWptr_uart2] = U2RXREG;
    bufferWptr_uart2++;
    bufferWptr_uart2 = bufferWptr_uart2 - ((bufferWptr_uart2 >> 8) << 8); //bufferWptr_uart2%BUFFERMAX
    //X - (X >> n) << n 取余数bufferWptr_uart2 - (bufferWptr_uart2 >> 8) << 8; 
}

/*************************************
Function:  BufferRead
Description: 读环形缓冲区
Input: 数据地址 
Output: 1：读取成功，0：读取失败
 *************************************/
bool BufferRead_UART1(u8 *data) {
    if (bufferRptr_uart1 == bufferWptr_uart1) {
        return 0;
    }
    *data = Buffer_uart1[bufferRptr_uart1];
    bufferRptr_uart1++;
    bufferRptr_uart1 = bufferRptr_uart1 - ((bufferRptr_uart1 >> 8) << 8); //bufferRptr_uart1 % BUFFERMAX; 
    //bufferRptr_uart1 - (bufferRptr_uart1 >> 8) << 8; // // X - (X >> n) << n 取余数
    return 1;
}

/*************************************
Function:  BufferRead
Description: 读环形缓冲区
Input: 数据地址 
Output: 1：读取成功，0：读取失败
 *************************************/
bool BufferRead_UART2(u8 *data) {
    if (bufferRptr_uart2 == bufferWptr_uart2) {
        if (U2STAbits.OERR)
            U2STAbits.OERR = 0; //写数据满导致FIFO溢出，而没有清除，接受数据没有
        return 0;
    }
    *data = Buffer_uart2[bufferRptr_uart2];
    bufferRptr_uart2++;
    bufferRptr_uart2 = bufferRptr_uart2 - ((bufferRptr_uart2 >> 8) << 8);
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
u8 UARTIsGet(UARTn f_uart, u8*Get_Source, const u8 get_size, const u8 *head, const u8 head_size) {//注意'\0'
    u8 first_cnt = 0; //记录字节数
    u8 cnt = 0, byte = 0;
    u8 UART_Tmp[200]; //临时变量周期有限

    while (cnt < 20)
        UART_Tmp[cnt++] = 0; //void head=08
    cnt = 0;
    while (f_uart(UART_Tmp + cnt++))
        if (cnt >= 200) break; //读取数据 +1
    byte = cnt - 1; //减去多读的一个字节  数据量过多
    for (first_cnt = 0; first_cnt < byte; first_cnt++) { //从数据中查找帧头
        if (*(UART_Tmp + first_cnt) == *head) {//寻找帧头的第一个数据
            for (cnt = 0; cnt < head_size; cnt++) {//判断一串帧头数据
                if (*(UART_Tmp + first_cnt + cnt) != *(head + cnt))
                    break; //如果数据没有正确，跳出当前循环
                else if (cnt == head_size - 1) {//正确的话，复制数据
                    if (get_size <= byte)//获取有效字节数量
                        byte = get_size;
                    for (cnt = 0; cnt < byte; cnt++)//赋值
                        *(Get_Source + cnt) = *(UART_Tmp + first_cnt + cnt);
                    return byte;
                }
            }
        }
    }
    return 0;
}


