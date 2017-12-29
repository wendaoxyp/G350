#ifndef CAT24C512_H 
#define CAT24C512_H
#include <p24FJ64GA306.h>
//#include <stdint.h>
#include <stdio.h>
#include <i2c.h>
//È¡Öµ·¶Î§0x0000-0xffff 512kb

//#define CAT24C512 0x03
#define CAT_ADD 0xA8
#define CAT_WP LATBbits.LATB12


//typedef struct {
//    uint8_t* data;
//} CAT24Arg;

//extern  CAT24Arg cat24argbits;
extern void CAT24C512_Init(void);
extern void CAT24C512_Read(uint16_t id, uint8_t *tmp);
extern void CAT24C512_Write(uint16_t id, uint8_t * tmp);

#endif

