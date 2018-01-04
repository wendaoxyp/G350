/* 
 * File:   RS485.h
 * Author: TURONG62
 *
 * Created on 2016��6��12��, ����4:09
 */

#ifndef RS485_H
#define	RS485_H


/***************************************************************************
 * Includes
 ***************************************************************************/
#include <xc.h>
#include <stdint.h>
#include "WCV_Conf.h"
#include "Common.h"
#include "SerialBuffer.h"

/***************************************************************************
 * Defines
 ***************************************************************************/
#define RS485_RDE_TRIS  TRISAbits.TRISA0    //���ƿ�����λ���
#define RS485_RDE       LATAbits.LATA0      //���ý���ʹ�ܶ�
//#define RS485_IN_TRIS   TRISBbits.TRISB2    //����Ϊ����/
//#define RS485_OUT_TRIS  TRISBbits.TRISB3    //����Ϊ���
//#define ANSBbits.ANSB8      //������������Ϊ��������

/***************************************************************************
 * Prototypes
 ***************************************************************************/
extern void RS485_Init(void);
extern void RS485Send(const uint8_t dat);
extern void RS485SendString(const uint8_t* dat, const uint8_t bytes);
extern void OpenRS485(void);
extern void CloseRS485(void);
extern void GetLast4Bytes(void);

#endif	/* RS485_H */

