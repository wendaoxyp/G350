/* 
 * File:   main.c
 * Author: Administrator
 *
 * Created on 2017年12月21日, 下午12:54
 */

#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "SerialBuffer.h"
#include "mcc_generated_files/mcc.h"
#include "M6310.h"

//#define LED_G LATBbits.LATB12
void LED_Twinkle(void);
void OpenM6310(void);
void UART1_SendString(uint8_t* tmp);
void U1Rx4Byte(void);
//uint8_t FLAG_T1;
//uint8_t AT[] = "AT\n";

/*
 * 
 */
int main(void) {
    bool need_online_f = true;
    uint8_t m6310_online_err = 1, getsize = 0;
    //    M6310_STA sta;
    uint8_t M6310_buf[50];
    RCONbits.SBOREN = 0;
    RCONbits.BOR = 0;
    SYSTEM_Initialize();
    //    TRISBbits.TRISB12 = 0;
    //    return (EXIT_SUCCESS);
    //    UART1_SetRxInterruptHandler(LED_Twinkle);
    //    IEC0bits.U1TXIE = false;
    //    UART1_SetTxInterruptHandler(UART1_Transmit_ISR);
    //    //    TMR1_Stop();

    //    TMR1_Start();

    while (1) {
        //if need_online_f =1,
        if (need_online_f) {
            OpenM6310();
            Delay1s(10);
            m6310_online_err = M6310_DialingIsERR();
            if (m6310_online_err == M6310_Daling_OK) {
                ClearDat(Buffer_uart1, 0xff, BUFFERMAX);
                while (1) {
                    Delay1s(3); //配合M6310_Receive
                    U1Rx4Byte();
                    //                    sta = M6310_Receive(M6310_buf, 20);
                    if (!getsize)
                        getsize = UARTGetData(BufferRead_UART1, M6310_buf, 20);
                    else
                        getsize += UARTGetData(BufferRead_UART1, M6310_buf, 20);
                    if (Str_Find_Head((const uint8_t*) M6310_buf, (const uint8_t*) "12345", 20, 5)) {
                        M6310_Send((uint8_t*) "Hello World!!");
                        M6310_AT_Close();
                        break;
                    }
                }
                need_online_f = false;
            }
            CloseM6310();
            Delay1s(5);
        }
        //        while (!FLAG_T1);
        //        while(FLAG)
        //        FLAG_T1 = 0;
        //        TMR1 = 0;
        //        LED_G ^= 1;
    }
}

/*
void Timer0_Init(void)
{
    T1CONbits.TON=0;//关闭定时器1
    T1CONbits.TECS=0b10;//使用LPRC 晶振
    TMR1=0;
    PR1=0x7918;//1s定时
    IFS0bits.T1IF=0;
//    IECbits.
//    IPCbits.
}
 */
void LED_Twinkle(void) {
    //    uint8_t tmp[20], bytes;
    //    LED_G = 1;
    //    UART1_Receive_ISR();
    BufferWrite_UART1();
    //    bytes = UART1_ReadBuffer(tmp, 10);
    //    UART1_Read();
    //    IFS0bits.U1RXIF = 0;
}

void UART1_SendString(uint8_t * tmp) {
    //    uint8_t byte = 0;
    while (*tmp != '\0') {
        U1TXREG = *tmp;
        while (!U1STAbits.TRMT); //等待发送完毕
        tmp += 1;
    }
}

void U1Rx4Byte(void) {//获取终端里面的最后几个数据，每4个字节中断
    uint8_t cnt;
    for (cnt = 0; cnt < 4; cnt++)//串口最后四个字节没有接受到，中断原因
        if (U1STAbits.URXDA) //没有接收到
            BufferWrite_UART1();
}
