/* 
 * File:   Miot1601.h
 * Author: TURONG62
 *
 * Created on 2016年9月9日, 下午2:40
 */

#ifndef MIOT1601_H
#define	MIOT1601_H

//#ifdef	__cplusplus
//extern "C" {
//#endif 

/*铁电存储数据包各个参数顺序 REG1_Add_enum*/
extern enum REG1_Add_enum {
    mp_time = 0,
    mp_Qb = 7,
    mp_Vb = 11,
    mp_Qm = 19,
    mp_Vm = 23,
    mp_T = 31,
    mp_P = 35,
    mp_Vbat = 39,
    mp_alarm = 43,
    mp_status = 44,
    mp_sumcheck = 45,
} enum_REG1_add;


/*REG1用于存储数据的数组，REG2用于存储MIOT参数的数组*/
extern enum REG2_Add_enum {
    reg2_mi_add = 0,
    reg2_mi_id = 1,
    reg2_mp_add = 2,
    reg2_mp_id = 3,
    reg2_mi_year = 4,
    reg2_mi_month = 5,
    reg2_mi_day = 6,
    reg2_mi_hour = 7,
    reg2_mi_min = 8,
    reg2_mi_sec = 9,
    reg2_mi_tmp = 10,
    reg2_mi_tgprs = 11,
    reg2_mi_talarm = 12,
    reg2_mi_sp = 13,
    reg2_mi_arg1 = 14,
    reg2_mi_arg2 = 15,
    reg2_mi_mode = 16,
    reg2_mi_mp_po = 17,
    reg2_mi_hp_alarm = 18,
    reg2_mi_lp_alarm = 19,
    reg2_mi_ht_alarm = 20,
    reg2_mi_lt_alarm = 21,
    reg2_mi_lv_alarm = 22,
    reg2_mi_ofst = 23
} enum_REG2_Add;

/*发送缓冲数据各个参数顺序*/
extern enum REG3_Add_enum {
    reg3_timestamp = 0,
    reg3_Vb = 4,
    reg3_Qb = 12,
    reg3_T = 16,
    reg3_P = 20,
    reg3_sta = 24,
    reg3_Vbat = 25
} enum_send_buffer;

/*A2协议各个参数顺序*/
extern enum A2_Add_enum {
    A2_Add = 0,
    A2_ID = 1,
    A2_Bytes = 2,
    A2_Vb = 3,
    A2_Qb = 11,
    A2_Vm = 15,
    A2_Qm = 23,
    A2_T = 27,
    A2_P = 31,
    A2_Sta = 35,
    A2_Vbat = 36,
    A2_CRC16 = 40
} enum_A2_Add;

/*A2协议返回的参数顺序*/
//extern enum A2_Rec_Add_enum {
//    A2_Rec_Sample_Time = 15,
//    A2_Rec_Send_Time = 18,
//    A2_Rec_Alarm_Time = 21,
//    A2_Rec_High_Pressure = 24,
//    A2_Rec_Low_Pressure = 27,
//    A2_Rec_High_Tempurature = 32,
//    A2_Rec_Low_Tempurature = 37,
//    A2_Rec_High_Vbat = 42,
//    A2_Rec_Low_Vbat = 47,
//    A2_Rec_Time = 52
//} enum_A2_Rec_Add;

//extern enum A2_arg_add_enum enum_A2_arg_add;
extern u8 GetSize(u16 reg_add, u8 arg_num);
extern void Register2Write(u8 * dat, const u8 reg_add, const u8 bytes);
extern void Register2Read(u8* dat, const u8 reg_add, const u8 bytes);
//extern const u8 REG1_Add[REG1_ARG_NUM + 1];
extern const u8 REG2_Arg_Postion[REG2_ARG_NUM + 1];
extern void EnRegister1(u8 BufferCnt, u8 * ptr_dat);
extern void GetRegister1(u8 BufferCnt, u8 *ptr_dat, u8 reg_cnt);
extern void EmptyRegister1(void);
extern void Refresh_RTCC_Pulse(void);
extern void OutputMiotArg(void);
extern void SaveMiotArg(void);
extern bool LoadMiotArg(void);
//#ifdef	__cplusplus
//}
//#endif

#endif	/* MIOT1601_H */

