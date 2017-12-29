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
//#include "E41_C1.h"
#include "LCD.h"


// Flagbits;

//#define MY_BUFFER_SIZE 64
////#define E41_SEND ""
//struct FLAGBITS flagbits;
//void DelayTR0(uint8_t cnt);
//void UART1_WriteBuf(uint8_t* tmp, const uint8_t len);
//void UART3_WriteBbuf(uint8_t* tmp, const uint8_t len);

/*
 * 
 */
int main(int argc, char** argv) {
    //    struct tm time1;
    uint8_t cnt = 0;
    //    uint8_t E41_SEND[] = {0x01, 0x03, 0x00, 0x64, 0x00, 0x02, 0x85, 0xD4};
    //    uint8_t E41_RECEIVE[20] = {0x01, 0x03, 0x04, 0x43, 0x3C, 0xF2, 0x00, 0x6A, 0xDB};
    //    uint8_t Head[3] = {0x1, 0x3, 0x4};
    //    uint8_t Head1[15] = {0xFF, 0xFF, 0x01}; //目标通道是01 目标地址是FF FF
    //    float pressure;
    //    uint8_t R_byte = 0;
    SYSTEM_Initialize();
    LCD_Init();
    //    E41_Init();
    //    U1STAbits.UTXEN = 1;
    //    U1MODEbits.UARTEN = 1;
    //    TRISBbits.TRISB10 = 0;
    //    LATBbits.LATB10 = 0; //RS485 In Receive Mode
    //    TRISFbits.TRISF0 = 0;
    //    E41_SetMode(0x02); //转化为唤醒模式
    LCDSE0 = 0xFFFF;
    TRISBbits.TRISB13 = 0;
    TRISDbits.TRISD6 = 0;
    TRISDbits.TRISD7 = 0;
    while (1) {
        //        //        LATBbits.LATB13=1;
        //        LCD_ShowTest();
        POW_SHOW(HIDE);
        ERR_SHOW(SHOW);
        FOR_SHOW(SHOW);
        BACK_SHOW(HIDE);
        CC_SHOW(SHOW);
        _h_SHOW(SHOW);
        m3_SHOW(SHOW);
        kPa_SHOW(SHOW);
        BAT_SHOW(cnt % 4);
        SIGN_SHOW(cnt % 5);
        DP_SHOW(cnt % 5);
        //        NUM_SHOW(1,0);
        //        NUM_SHOW(1,1);
        //      d  NUM_SHOW(3,2);
        //        NUM_SHOW(4,3);
        //        NUM_SHOW(5,4);
        //        NUM_SHOW(6,5);
        NUMS_SHOW((000000 + 111111 * cnt) % 999999);
        LCD_ShowTest(7, SHOW);
        //                LCD_Set(0, 6, SHOW);
        //                LCD_Set(0, 7, SHOW);
        //                LCD_Set(0, 8, SHOW);
        //                LCD_Set(1, 1, SHOW);
        LATBbits.LATB13 = 1;
        Delay1s(2); //wait for receive complete
        //        //        LATFbits.LATF0 = 0;
        //        //        LCD_ShowTest(cnt, HIDE);
        LATBbits.LATB13 = 0;
        PORTDbits.RD7 = 1;
        POW_SHOW(SHOW);
        ERR_SHOW(HIDE);
        FOR_SHOW(HIDE);
        BACK_SHOW(SHOW);
        CC_SHOW(HIDE);
        _h_SHOW(HIDE);
        m3_SHOW(HIDE);
        kPa_SHOW(HIDE);
        //        NUMS_SHOW(976543);
        //        NUM_SHOW(0,1);
        //        LCDDATA0 = 0xFFFF;
        //        LCDDATA4 = 0xFFFF;
        //        LCDDATA8 = 0xFFFF;
        //        LCDDATA12 = 0xFFFF;
        //        LCDDATA16 = 0xFFFF;
        Delay1s(2); //wait for receive complete   
        //        cnt += 1;
        cnt = (cnt+1) % 72;
        //                PORTDbits.RD6 = 0;
        //        PORTDbits.RD7=0;
        //        Sleep();
    }
}

//void DelayTR0(uint8_t cnt) {
//    TMR1_Start();
//    while (flagbits.TR0_Cnt < cnt);
//    TMR1_Stop();
//    flagbits.TR0_Cnt = 0;
//}

//void UART1_WriteBuf(uint8_t* tmp, const uint8_t len) {
//    uint8_t cnt;
//    LATBbits.LATB10 = 1; //RS485 In Receive Mode    
//    for (cnt = 0; cnt < len; cnt++) {
//        U1TXREG = *(tmp + cnt);
//        while (!U1STAbits.TRMT);
//    }
//    //    DelayTR0(1);
//    LATBbits.LATB10 = 0; //RS485 In Receive Mode    
//}




//void UART3

