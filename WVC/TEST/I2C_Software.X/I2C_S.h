/* 
 * File:   I2C_S.h
 * Author: Administrator
 *
 * Created on December 29, 2017, 3:35 PM
 */

#ifndef I2C_S_H
#define	I2C_S_H

/***************************************************************************
 * Includes
 ***************************************************************************/
#include <xc.h>
//#include <libpic30.h>
#include <stdint.h>
#include "Common.h"
#include <stdbool.h>
/***************************************************************************
 * Definitions
 ***************************************************************************/

#define I2C_DELAY(x) Delay1ms(x)
#define I2C_SCL LATBbits.LATB5
#define I2C_SDA LATBbits.LATB6
#define I2C_R_SDA PORTBbits.RB6
#define I2C_ERR_NO_ACK                  1
#define I2C_GET_ACK                     2
//需要设置成数字输入

/***************************************************************************
 * Prototypes
 ***************************************************************************/



#endif	/* I2C_S_H */

