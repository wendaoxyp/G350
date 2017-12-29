#ifndef PCF8583_H
#define PCF8583_H

#include <p24FJ64GA306.h> 
#include <stdint.h>
#include <time.h>


#define PCF_INT PORTBbits.RB13

extern void PCF8583_Init(void);
extern void PCF8583_SetTime(uint32_t* timestamp); //, uint16_t alarmtime);
extern uint32_t PCF8583_ReadTime(void);
extern void PCF8583_SetAlarmTime(struct tm alarmtime);
extern void PCF8583_SetStatusReg(uint8_t reg);
extern void PCF8583_ReadStatus(uint8_t *tmp);


#endif

