#ifndef STATUS_H
#define STATUS_H

//#include <stdint.h>
//struct Reg3_Record {
//    vu8 Buffer_ID;
//    vu16 Record;
//};

extern enum status_enum {
    GPRS_Ready_OK = 0, GPRS_Dialing = 1, /*GPRS_Online_OK = 0x22,*/GPRS_Send_Data = 2, GPRS_Initing = 3,
    GPRS_No_Ready = 4, GPRS_Dialing_Cnt_Over = 5, GPRS_Dialing_Time_Over = 6, GPRS_Unline_No_Ready = 7,
    RData_Change_OK = 8,
    RData_Change_Fail = 9, /*no use*/ RData_No_Receive = 10, RData_Error_Check_Sum = 11, RData_Error_EID = 12,
    //    Data_Timeover = 0x84,
    //    GMT_No_Ready = 0x90, GMT_No_Receive = 0x91, GMT_Error_Check_Sum = 0x92, GMT_Error_MpId = 0x93,
    //    GMT_Error_Fail = 0x94, GMT_Timeover = 0x95, GMT_Time_Error = 0x96, GMT_Unix_Time_Error = 0x97,
    //    GMT_Arg_Error = 0x98,
    //    Alarm_No_Ready = 0xA0, Alarm_No_Receive = 0xA1, Alarm_Error_Check_Sum = 0xA2, Alarm_Error_MpId = 0xA3,
    //    Alarm_Error_Fail = 0xA4, Alarm_Timeover = 0xA5,
    Change_Arg_No_Ready = 13, Change_Arg_No_Receive = 14, Change_Arg_Error_Fail = 15, /*13-15∂‡”‡*/
    All_Right = 16, GPRS_Exit = 17,
    MIOT_Low_Power = 24, MIOT_Sleep = 17, MIOT_GPRS = 18, /* MIOT_MP = 0x43,*/ MIOT_Test = 19,
    MIOT_Alarm_HP = 20, MIOT_Alarm_LP = 21, MIOT_Alarm_HT = 22, MIOT_Alarm_LT = 23,
    MP_GetData_OK = 25, MP_GetData_Fail = 26
} enum_status;

extern void GetStatus(unsigned char* sta);

#endif

