#include "Status.h"
#include "user.h"
#include "25L64B.h"
//#include 

typedef void(*SaveFun)(u16 add, u8* dat, u8 bytes); //函数指针
#define SAVE_STATUS 0x1F80//状态保存地址
//#define Sta_Cnt_MAX 7
//uint8_t Sta_Cnt; //状态通道
//uint8_t Sta_Dat[Sta_Cnt_MAX][7];

uint8_t GetMIOTStatus(void) {
    return Statusbits.staMiot;
}

uint8_t GetGPRSStatus(void) {
    return Statusbits.staGPRS;
}

uint8_t GetMPStatus(void) {
    return Statusbits.staMp;
}

void GetStatus(uint8_t* sta) {
    uint8_t* tmp_sta;
    tmp_sta = sta;

    *tmp_sta = Statusbits.staMiot;
    *(tmp_sta + 1) = Statusbits.staGPRS;
    *(tmp_sta + 2) = Statusbits.staMp;
}

//void SaveStatus(SaveFun sf, uint8_t *sta, uint8_t *time) {
//    uint8_t cnt;
//    //    tmp
//    for (cnt = 0; cnt < 4; cnt++)//赋值时间
//        *(sta + cnt) = *(time + cnt);
//    *(sta + 4) = Statusbits.staMiot;
//    *(sta + 5) = Statusbits.staGPRS;
//    *(sta + 6) = Statusbits.staMp;
//    //            RTCReadTime();
//    sf(SAVE_STATUS, sta, 7);
//}

//void ReadStatus(SaveFun sf, uint8_t *sta) {
//    sf(SAVE_STATUS, sta, 7);
//}
