/* 
 * File:   PPS.c
 * Author: Administrator
 *
 * Created on 2017年6月20日, 下午1:52
 */
#include <xc.h>

void PPSInit(void) {
    __builtin_write_OSCCONL(OSCCON & 0xbf); // unlock PPS
    //    RPOR4bits.RP8R = 0x03; // B9->UART1:U1TX
    //    RPINR18bits.U1RXR = 0x09; // B8->UART1:U1RX 
    RPOR4bits.RP9R = 0x03; // RB9->UART1:U1TX
    RPINR18bits.U1RXR = 0x08; // RB8->UART1:U1RX
    RPOR11bits.RP22R = 0x05; // RD3->UART2:U2TX
    RPINR19bits.U2RXR = 0x17; // RD2->UART2:U2RX 
    RPOR13bits.RP26R = 0x1C; // RG7->UART3:U3TX
    RPINR17bits.U3RXR = 0x13; // RG8->UART3:U3RX 
    //    RPINR3bits.
    //    RPOR11bits.RP23R = 0x05; // RD2->UART2:U2TX
    //    RPINR19bits.U2RXR = 0x16; // RD3->UART2:U2RX RPG23=>17
    __builtin_write_OSCCONL(OSCCON | 0x40); // lock   PPS
}

//RPOR13bits.RP26R = 0x1C; // RG7->UART3:U3TX
//    RPINR17bits.U3RXR = 0x13; // RG8->UART3:U3RX



