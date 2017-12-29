/*
 *********************************************************************************************************
 *                                                uC/OS-II
 *                                          The Real-Time Kernel
 *
 *                                 (c) Copyright 2006, Micrium, Weston, FL
 *                                           All Rights Reserved
 *
 *                                           MASTER INCLUDE FILE
 *********************************************************************************************************
 */

#ifndef     INCLUDES_H
#define     INCLUDES_H

#include    <stdio.h>
#include    <string.h>
#include    <ctype.h>
#include    <stdlib.h>
#include    <time.h>

#include    <cpu.h>
#include    <ucos_ii.h>

//#include    <lib_def.h>
//#include    <lib_str.h>
//#include    <lib_mem.h>

#include    <bsp.h>
#include    <xc.h>
#include    "UART2.h"
#include    "RS485.h"
#include    "PC.h"
#include    "UART2.h"
#include    "UART3.h"
#include    "I2C.h"
#include    "INT.h"
#include    "E41.h"
#include    "HL6528.h"
#include    "CAT24C512.h"
#include    "PCF8583.h"
#include    "DeepSleep.h"
//#include    <lcd.h>

//#if (uC_PROBE_OS_PLUGIN > 0)
//#include  <os_probe.h>
//#endif

//#if (uC_PROBE_COM_MODULE > 0)
//#include  <probe_com.h>

//#if (PROBE_COM_METHOD_RS232 > 0)
//#include  <probe_rs232.h>
//#endif
//#endif

//#define CLOSE_6528

#endif                                                                  /* End of File                                              */

