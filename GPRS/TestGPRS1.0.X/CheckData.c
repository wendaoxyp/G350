#include "user.h"
#include "UART.h"

/****************************************************************************
名称: CRC16()
说明: CRC16校验程序
参数: *CRC_Buf:数据地址
      CRC_Leni:数据长度
返回: CRC校验值
 *****************************************************************************/
u16 CRC16_Check(u8 *CRC_Buf, const u8 CRC_Leni) {
    u16 i, j;
    u16 CRC_Sumx;

    CRC_Sumx = 0xFFFF;
    for (i = 0; i < CRC_Leni; i++) {
        CRC_Sumx ^= *(CRC_Buf + i); //异或
        for (j = 0; j < 8; j++) {
            if (CRC_Sumx & 0x01) {
                CRC_Sumx >>= 1;
                CRC_Sumx ^= 0xA001;
            } else {
                CRC_Sumx >>= 1;
            }
        }
    }
    return (CRC_Sumx);
}

/*************************************
Function: Sum_Check 
Description: 计算和校验的数值，
Input: frame：数据，bytes：字节数 
Output: 和校验结果值
 *************************************/
u16 Sum_Check(u8 *frame, const u8 bytes) {
    u16 cksum = 0;
    u16 cnt = bytes;
    while (cnt > 0) {
        cksum += *frame++;
        cnt--;
    }
    return cksum;
}

/*************************************
Function: Sum_Check256
Description: 计算和校验的数值，
Input: frame：数据，bytes：字节数 
Output: 和校验结果值
 *************************************/
u8 Sum_Check256(u8 *frame, const u16 bytes) {
    u32 ckSum = 0; //避免数据溢出
    u16 cnt;

    for (cnt = 0; cnt < bytes; cnt++)
        ckSum += *frame++;

    return (u8) (ckSum - ((ckSum >> 8) << 8));
}

/*************************************
Function: CheckIsRight  
Description: 判断接受dat，根据fp校验，返回数据正确性
Input: fp 选择校验函数，dat:检验的数据，bytes:字节数
Output: 1：校验正确  0：校验错误
 *************************************/
bool CheckIsRight(FP_CRC fp, u8 * dat, const u8 bytes) {
    u16 CRCtep = fp(dat, bytes); //CRC校验
    return (CRCtep == (*(dat + bytes)+ (*(dat + bytes + 1) << 8))); //校验数据+CRC
}

bool CheckSrting(u8*dat1, u8*dat2, const u8 num) {
    u8 cnt;
    for (cnt = 0; cnt < num; cnt++) {//判断EID
        if (*(dat1 + cnt) != *(dat2 + cnt)) {
            return false;
        }
    }
    return true;
}

///*************************************
//Function: MD5encrypt  
//Description: 
//Input: 
//Output:
//*************************************/
//void MD5encrypt(u8* input,u8 *output)
//{
//    
//}



