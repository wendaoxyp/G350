/* 
 * File:   CircleReceiveBuffer.h
 * Author: TURONG62
 *
 * Created on 2016年7月22日, 下午1:01
 */

#ifndef SEIRALBUFFER_H
#define	SEIRALBUFFER_H

//#include "user.h"
#include <stdbool.h>
#include <stdint.h>
#include <xc.h>

typedef bool (*UARTn)(uint8_t*);

typedef struct STRCMP {
    uint8_t *SourceData; //源数据的地址
    uint8_t Source_len; //源数据的长度
    uint8_t *CheckData; //校验数据的地址
    uint8_t Check_len; //校验数据长度
    uint8_t* GetData; //获取数据
    uint8_t Get_len; //期望获取数据长度
    uint8_t Real_len; //实际获取长度

} StrCmp;
//extern void BufferWrite_UART1(void);
extern void BufferWrite_UART1(void);
extern void BufferWrite_UART2(void);
extern void BufferWrite_UART3(void);
//extern bool BufferRead_UART1(uint8_t *data);
extern bool BufferRead_UART1(uint8_t *data);
extern bool BufferRead_UART2(uint8_t *data);
extern bool BufferRead_UART3(uint8_t *data);
//extern bool UARTIsGet(UARTn f_uart, uint8_t*Get_Source, const uint8_t get_size, const uint8_t *head, const uint8_t head_size);
extern uint8_t UARTGetData(UARTn f_uart, uint8_t*Get_Data, uint8_t byte);
extern bool UARTDataIsRight(StrCmp * strcmp);
extern void ClearBuffer(UARTn f_uart);

#endif	/* CIRCLERECEIVEBUFFER_H */



