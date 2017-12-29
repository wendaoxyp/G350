/* 
 * File:   newmain.c
 * Author: Administrator
 *
 * Created on 2017年6月20日, 下午12:50
 */

#include <stdio.h>
#include <stdlib.h>
#include "../mcc_generated_files/mcc.h"
#include "Common.h"
#include "E41_C1.h"


// Flagbits;

#define MY_BUFFER_SIZE 64
//#define E41_SEND ""
struct FLAGBITS flagbits;
void DelayTR0(uint8_t cnt);
void UART1_WriteBuf(uint8_t* tmp, const uint8_t len);
void UART3_WriteBbuf(uint8_t* tmp, const uint8_t len);

/*
 * 
 */
int main(int argc, char** argv) {
    //    struct tm time1;
    //    uint8_t numBytes;
    uint8_t E41_SEND[] = {0x01, 0x03, 0x00, 0x64, 0x00, 0x02, 0x85, 0xD4};
    uint8_t E41_RECEIVE[20] = {0x01, 0x03, 0x04, 0x43, 0x3C, 0xF2, 0x00, 0x6A, 0xDB};
    uint8_t Head[3] = {0x1, 0x3, 0x4};
    uint8_t Head1[15] = {0xFF, 0xFF, 0x01}; //目标通道是01 目标地址是FF FF
    float pressure;
    uint8_t R_byte = 0;
    SYSTEM_Initialize();
    E41_Init();
    U1STAbits.UTXEN = 1;
    U1MODEbits.UARTEN = 1;
    TRISBbits.TRISB10 = 0;
    LATBbits.LATB10 = 0; //RS485 In Receive Mode
    TRISFbits.TRISF0 = 0;
    E41_SetMode(0x02); //转化为唤醒模式
    while (1) {
        //                E41_ReadArg();
        //                LATFbits.LATF0 = 1;
        //                Delay1s(5);
        //                LATFbits.LATF0 = 0;
        //                Delay1s(5);
        //        FF FF 01 01 03 04 43 3C F2 00 6A DB 
        if (flagbits.E41) {
            UART1_WriteBuf(E41_SEND, 8);
            Delay1s(1); //wait for receive complete
            if (!UART1_ReceiveBufferIsEmpty()) {
                R_byte = UART1_ReadBuffer(E41_RECEIVE, 20); //获取压力值
                if (UART_Is_Get(E41_RECEIVE, Head, R_byte, 3) && R_byte > 5) {//注意优先的结合顺序
                    CharToFloat(&pressure, E41_RECEIVE + 3);
                    LATFbits.LATF0 = 1;
                    Delay1s(1);
                    E41_SetMode(0x00); //转化为唤醒模式
                    UART3_WriteBbuf(Head1, 3);
//                    for (R_byte = 0; R_byte < 8; R_byte++)
//                        *(Head1 + 3 + R_byte) = *(E41_RECEIVE + R_byte);
                    UART3_WriteBbuf(E41_RECEIVE, R_byte);
                    R_byte = 0;
                    //        LATFbits.LATF0 = 0;
                    Delay1s(10);
                    E41_SetMode(0x02); //转化为省电模式
                }
            }
            flagbits.E41 = 0;
        }
        LATFbits.LATF0 = 0;
    }
}

void DelayTR0(uint8_t cnt) {
    TMR1_Start();
    while (flagbits.TR0_Cnt < cnt);
    TMR1_Stop();
    flagbits.TR0_Cnt = 0;
}

void UART1_WriteBuf(uint8_t* tmp, const uint8_t len) {
    uint8_t cnt;
    LATBbits.LATB10 = 1; //RS485 In Receive Mode    
    for (cnt = 0; cnt < len; cnt++) {
        U1TXREG = *(tmp + cnt);
        while (!U1STAbits.TRMT);
    }
    //    DelayTR0(1);
    LATBbits.LATB10 = 0; //RS485 In Receive Mode    
}




//void UART3

