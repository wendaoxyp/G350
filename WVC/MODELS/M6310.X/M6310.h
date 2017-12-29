/*************************************************
Copyright (C), 1988-1999, Tech. Co., Ltd.
File name: M6310.h
Author: xx13
Version: 1.0
Date: 2017/12/29
Description: M6310 API函数的头文件
Others: None
History: None
1. Date:
Author:
Modification:
2. ...
 *************************************************/
#ifndef M6310_H
#define M6310_H

/***************************************************************************
 * Includes
 ***************************************************************************/
#include <xc.h>
#include <stdint.h>
#include <stddef.h>
#include "SerialBuffer.h"
#include "Common.h"


/***************************************************************************
 * Definitions
 ***************************************************************************/
#define M6310_Daling_OK                     0
#define M6310_Daling_Ser_Socket_Fail        1
#define M6310_Daling_Socket_Fail            2
#define M6310_Daling_APN_Fail               3
#define M6310_Daling_Find_Net_Fail          4
#define M6310_Daling_SIM_Fail               5
#define M6310_Daling_URC_Fail               6
#define M6310_Daling_Serial_Control_Fail    7
#define M6310_Daling_Broken_Fail            8
#define M6310_SEND_OK                       9
#define M6310_SEND_FAIL                     10
#define M6310_SEND_NO_BACK                  11
#define M6310_SEND_ERR_NO_RECEIVE           12
//#define M6310_SEND_NO_BACK           3
typedef uint8_t M6310_STA;


/***************************************************************************
 * Prototypes 
 ***************************************************************************/
extern M6310_STA M6310_DialingIsERR(void);
extern void M6310_Init(void);
extern void OpenM6310(void);
extern void CloseM6310(void);
extern bool M6310_AT_Close(void);
//extern void M6310_GetIP_Port(void);
extern M6310_STA M6310_Send(uint8_t * arg);


#endif




