/* 
 * File:   UDP-TANCY RTU PROTOCOL FOR DAZHONG GAS.h
 * Author: TURONG62
 *
 * Created on 2016年9月8日, 下午12:53
 */
#ifndef UDP_TANCY_RTU_PROTOCOL_FOR_DAZHONG_GAS_H
#define	UDP_TANCY_RTU_PROTOCOL_FOR_DAZHONG_GAS_H

#ifdef	__cplusplus
extern "C" {
#endif
      
extern void UDPSendData(u8 packetType,u8 OffSet);
extern void UDPReceiveData(void);
extern void UDPAlarmTask(void);
//#define SAVE_PERIOD 0x00 
//#define	SEND_PERIOD 0x01 
//#define	ALARM_PERIOD 0x02
//#define	HIGH_PRESSURE_ALARM	0x03
//#define	LOW_PRESSURE_ALARM 0x04 
//#define	HIGH_TEMPERATURE_ALARM 0x05 
//#define	LOW_TEMPERATURE_ALARM 0x06 

//#define DATA_SAM 0x00 
#define HIGH_TEMP_ALARM 0x01 
#define LOW_TEMP_ALARM 0x02
#define HIGH_PRESSURE_ALARM 0x03
#define LOW__PRESSURE_ALARM 0x04


#ifdef	__cplusplus
}   
#endif

#endif	/* UDP_TANCY_RTU_PROTOCOL_FOR_DAZHONG_GAS_H */

