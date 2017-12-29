/* 
 * File:   Miot1601.h
 * Author: TURONG62
 *
 * Created on 2016年9月9日, 下午2:40
 */

#ifndef MIOT1601_H
#define	MIOT1601_H

#ifdef	__cplusplus
extern "C" {
#endif 

#define REG1_MAX_CNT 24
#define SEND_OK {RS485Send('\n');RS485Send('O');RS485Send('K');RS485Send('\n');RS485Send('\n');} 

    extern u8 GetSize(u16 reg_add, u8 arg_num);
    extern void Register2Write(u8 * dat, u16 reg_add, u8 bytes);
    extern void Register2Read(u8* dat, u16 reg_add, u8 bytes);
    //extern void RegisterToFrom(void);
//    extern const u8 mi_dat_add[REG_DATA_ARG_NUM + 1];
//    extern const u16 mi_arg_add[REG_ARG_NUM + 1];

    //void RefreshDaZong(void);
    //void RefreshTime(void);
    //void RefreshAllArg(void);
    //void Get_Mi_Ofst(void);
//    void GetArgForTest(void);
    extern bool EnRegister1(u8 * ptr_dat);
    extern void EmptyRegister1(void);
    extern void GetRegister1(u8 *ptr_dat, u8 reg_cnt);
    extern void Refresh_RTCC_Pulse(void);

#ifdef	__cplusplus
}
#endif

#endif	/* MIOT1601_H */

