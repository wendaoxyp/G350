/* 
 * File:   Modbus.h
 * Author: TURONG62
 *
 * Created on 2016年6月23日, 下午1:54
 */

#ifndef MP_H
#define	MP_H

#include "type.h"


#define TONUM(x) (x-0x30)
#define TOASC(x) (x+0x30)


extern bool CopMPTaskIsFinish(u8 protocals);
//extern void PCCop10s(u8 GPRSStatus);
//void GetProtocal(void);
extern void PacketData2A2(u8 *dat, u8*dat1);
extern void GetValueTask(u8);
//extern void GetAlarmValue(void);

#endif	/* MODBUS_H */

