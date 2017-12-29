/* 
 * File:   Json.c
 * Author: TURONG62
 *
 * Created on 2016年8月10日, 上午8:09
 */
#include "UART.h"
#include "user.h"

typedef struct Json
{
    unsigned char device[10] = "0331500002";
    unsigned char business[10] = "0331500002";
    unsigned char Version[4]="V1.0";
    unsigned long session=1465197151;
    unsigned char command[23];
    unsigned char ret[2];
}JSON;

typedef struct Content
{
    unsigned char mode;//measure、alarm、opt
    unsigned char name[4];
    unsigned char datatype[5];
    unsigned char content[];
    unsigned long time0;
    unsigned int value0;
    unsigned long time1;
    unsigned int value1;
}CONTENT;


void JsonSend(void)
{
    JSON js;
    gRSGPAddress
    UART2SendString("");
//    js.
}




