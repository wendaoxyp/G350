#ifndef UART_H
#define UART_H
#include"user.h"


void UART2_Configuration(void); //GPRS
void UART2Send(const u8 dat);
void UART2SendString(const u8* ch, u8 bytes);
void UART2SendString2(const u8* ch);
//void Close_UART2(void);
//void Open_UART2(void);
void SetGPRSBaudRate(u8 baudID);
#endif



