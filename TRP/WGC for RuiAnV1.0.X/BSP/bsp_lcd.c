/*
*********************************************************************************************************
*                                             Microchip dsPIC33FJ
*                                            Board Support Package
*
*                                                   Micrium
*                                    (c) Copyright 2005, Micrium, Weston, FL
*                                              All Rights Reserved
*
*
* File : bsp_lcd.c
* By   : Eric Shufro
*********************************************************************************************************
*/

#include <includes.h>


/*
*********************************************************************************************************
*                                   CHARACTER LCD BIT DEFINITIONS
*********************************************************************************************************
*/

#define  LCD_BIT_E              (CPU_INT08U)(1 <<  4)           /* LCD Screen bit EN maps to PTD, bit  4                    */
#define  LCD_BIT_RW             (CPU_INT08U)(1 <<  5)           /* LCD Screen bit EN maps to PTD, bit  5                    */
#define  LCD_BIT_RS             (CPU_INT16U)(1 << 15)		    /* LCD Screen bit RS maps to PTB, bit 15                    */

#define  LCD_BIT_DATA0          (CPU_INT08U)(1 <<  0)           /* LCD Screen bit D4 maps to PDE, bit  0                    */
#define  LCD_BIT_DATA1          (CPU_INT08U)(1 <<  1)           /* LCD Screen bit D5 maps to PDE, bit  1                    */
#define  LCD_BIT_DATA2          (CPU_INT08U)(1 <<  2)			/* LCD Screen bit D6 maps to PDE, bit  2                    */
#define  LCD_BIT_DATA3          (CPU_INT08U)(1 <<  3)    	    /* LCD Screen bit D7 maps to PDE, bit  3                    */
#define  LCD_BIT_DATA4          (CPU_INT08U)(1 <<  4)    	    /* LCD Screen bit D7 maps to PDE, bit  4                    */
#define  LCD_BIT_DATA5          (CPU_INT08U)(1 <<  5)    	    /* LCD Screen bit D7 maps to PDE, bit  5                    */
#define  LCD_BIT_DATA6          (CPU_INT08U)(1 <<  6)    	    /* LCD Screen bit D7 maps to PDE, bit  6                    */
#define  LCD_BIT_DATA7          (CPU_INT08U)(1 <<  7)    	    /* LCD Screen bit D7 maps to PDE, bit  7                    */


/*
*********************************************************************************************************
*                                              VARIABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                              PROTOTYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                 DispInitPort()
*
* Description : DispInitPort() is responsible for initializing the hardware used to interface with the
*               LCD module. DispInitPort() is called by DispInit().
*
* Arguments   : None
*
* Callers     : DispInit() from lcd.c
*
* Notes       : none.
*********************************************************************************************************
*/

void  DispInitPort (void)
{
#if defined(__dsPIC33E__)
    ANSELB = 0;
    ANSELA = 0;
    ANSELC = 0;
    TRISAbits.TRISA10 = 0;    //RA10 is RS
    TRISCbits.TRISC13 = 0;    //RC13 is R/W
    TRISCbits.TRISC6 = 0;     //RC6 is E
    TRISB  &= 0x00FF;
    LATCbits.LATC13 = 0;
#elif defined(__dsPIC33F__) || defined(__PIC24F__) || defined(__PIC24E__)
    TRISB  &= ~(LCD_BIT_RS);
    TRISD  &= ~(LCD_BIT_RW | LCD_BIT_E);
    TRISE  &= ~(0xFF);
    LATD   &= ~(LCD_BIT_RW);                                    /* Pull RW low indefintely.                             */
#endif
}


/*
*********************************************************************************************************
*                                   DispSel()
*
* Description : DispSel() determines whether data written to the HD44780 goes to the control or data
*               register.
*
* Arguments   : sel determines whether data written using DispDataWr() goes to the command register
*               (when sel == DISP_SEL_CMD_REG) or the data register (when sel == DISP_SEL_DATA_REG).
*
* Callers     : Various from lcd.c
*********************************************************************************************************
*/

void  DispSel (CPU_INT08U sel)
{
    #if defined(__dsPIC33E__)
    if (sel == DISP_SEL_CMD_REG) {
        LATAbits.LATA10 = 0;

    } else {
        LATAbits.LATA10 = 1;
    }
    #elif defined(__dsPIC33F__) || defined(__PIC24F__) || defined(__PIC24E__)
        if (sel == DISP_SEL_CMD_REG) {
        LATB  &= ~(LCD_BIT_RS);                                 /* Set the RS control line LOW                          */
    } else {
        LATB  |=  (LCD_BIT_RS);                                 /* Set the RS control line HIGH                         */
    }
    #endif
}


/*
*********************************************************************************************************
*                                   DispDataWr()
*
* Description : DispDataWr() is used to write a single byte to the LCD module. Depending on the state
*               of the RS line, the byte will be either sent to the data (RS is 1) or control register
*               (RS is 0) of the LCD controller.
*
* Arguments   : data is the byte value to write to the LCD controller module. The destination ‘inside’
*               the HD44780 or compatible controller depends on whether RS is high or low.
*
* Callers     : Various from lcd.c
*
* Notes       : 1) RS is determined prior to this function call. Therefore, software must
*                  not overwrite the current state of this bit.
*********************************************************************************************************
*/

void  DispDataWr (CPU_INT08U data)
{
    #if defined(__dsPIC33E__)
    LATB &= ~(0xFF00);
    LATB |= (data << 8);
    LATCbits.LATC6 |= 1;
    DispDly_uS(100);
    LATCbits.LATC6 = 0;
    DispDly_uS(100);
    #elif defined(__dsPIC33F__) || defined(__PIC24F__) || defined(__PIC24E__)
    LATE &= ~(0xFF);                                            /* Clear data lines to 0.                               */
    LATE |=  data;                                              /* Set the data pins to the correct value.              */
    LATD |=  LCD_BIT_E;                                         /* Set the E control line HIGH                          */
    DispDly_uS(100);                                            /* Delay for about 100 uS                               */
    LATD &= ~LCD_BIT_E;                                         /* Set the E control line LOW                           */
    DispDly_uS(100);                                            /* Delay for about 100 uS                               */
    #endif
}


/*
*********************************************************************************************************
*                                 uC/LCD Delay Functionality
*
* Description : DispDly_uS() allows the code to delay for the execution for a certain amount of time to
*               allow the data to ‘stabilize’ and for the HD44780 to complete it’s operation. The delay
*               is specified in microseconds (uS). This operation is easy to perform if you have a
*               real-time kernel such as uC/OS-II.
*
* Arguments   : us determines the amount of delay (in microseconds)
*
* Callers     : lcd.c: DispInit(), DispClrScr()
*********************************************************************************************************
*/

void  DispDly_uS (CPU_INT32U us)
{
    CPU_INT32U  us_per_tick;
    CPU_INT32U  ticks;


    us_per_tick =  1000000L / OS_TICKS_PER_SEC;
    ticks       =  us / us_per_tick + 1;
    OSTimeDly(ticks);
}


