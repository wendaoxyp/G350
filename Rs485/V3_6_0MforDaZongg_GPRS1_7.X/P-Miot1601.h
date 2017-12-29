/* 
 * File:   Miot1601.h
 * Author: TURONG62
 *
 * Created on 2016年8月17日, 下午4:47
 */

#ifndef TCP_MIOT1601_H
#define	TCP_MIOT1601_H

#ifdef	__cplusplus
extern "C" {
#endif

    //#ifndef errcode
#define errcode u8
#define Fun_Err 01          //功能不支持
#define Dat_Add_Err 02      //非法数据地址
#define Dat_Val_Err 03      //非法数据值
#define Do_Err 04           //执行失败
#define GPRS_UnLine 05      //GPRS下线


    //#endif
    extern void UDPSendData(u8 packetType); //,u8 OffSet,const u8 );
    //extern bool UDPReceiveData(u8 *dat, u8 *head, u8 num);
    extern bool DUPDataChange(u8 * source_dat);



    extern u8 CopFun(u8*dat, u8 source);
    extern void PC_Cop(void);
//    extern void RefreshMiotArg(void);
    //extern void Miot1601_03_Reply(u8 start,u8 bytes,u8 source);
    //extern void Register_Refresh(u8 * dat,u16 start,u8 bytes);
    extern void TCP_43_Send(/*u8 datacont,*/u8 source);
    extern void TCP_SendData(u8 source, u8 *dat, u8 bytes);
    //extern bool DataIsVaild(u16 dat, u16 max, u16 min); 

#ifdef	__cplusplus
}
#endif

#endif	/* MIOT1601_H */

