#ifndef CAT24C512_H 
#define CAT24C512_H
#include <p24FJ64GA306.h>
//#include <stdint.h>
#include <stdio.h>
#include <i2c.h>
//取值范围0x0000-0xffff 512kb

#define CAT_ADD 0xA8
#define CAT_WP_TRIS TRISBbits.TRISB12
#define CAT_WP_LAT LATBbits.LATB12

#define CAT_NUMS 5461//65536=12*5461+4
#define CAT_NOW_ADD 0xFFFC//c d CAT_StartID; e f CAT_OperatID
//取值范围0x0000-0xffff 512kb
#define BufferSize 12//40//一组采集数据的字节
//#define CAT_START 5
#define CAT_START_READ 2
#define CAT_START_WRITE 3

extern uint16_t CAT_OperatID;
extern uint16_t CAT_StartID;

extern void CAT24C512_Init(void);
extern void CAT24C512_Read(uint16_t id, uint8_t *tmp);
extern void CAT24C512_Write(uint8_t * tmp);

#endif

//添加写入正确性：写入数据并读取，和写入的数据做对比，如果相同，则写入成功，反之，重新操作3次（读取）。如果还是不相同的话，这提示错误
//添加读取正确性：读取数据两次，如果不相同重新读取，重复3次，如果还是不相同，则提示错误
