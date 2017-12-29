/*
 *********************************************************************************************************
 *                                               Microchip PIC33
 *                                            Board Support Package
 *
 *                                                    Micrium
 *                                    (c) Copyright 2005, Micrium, Weston, FL
 *                                              All Rights Reserved
 *
 *
 * File : BSP.H
 * By   : Eric Shufro
 *********************************************************************************************************
 */

/*
 *********************************************************************************************************
 *                                      OSCILLATOR FREQUENCIES
 *********************************************************************************************************
 */
#ifndef _BSP_H_
#define _BSP_H_


typedef void (*PFNCT)(void);

extern void LED_Init(void);
extern void LED_On(void);
extern void LED_Off(void);
extern void LED_Toggle(void);
extern void LED_Toggle1(unsigned char time, unsigned char count);
//extern void Close6528Cop(void);
//extern void Open6528Cop(void);
extern void OSCILLATOR_Initialize(void);

#endif
