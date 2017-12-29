//#include "user.h"
#include "CheckData.h"

///****************************************************************************
//名称: CRC16()
//说明: CRC16校验程序
//参数: *CRC_Buf:数据地址
//      CRC_Leni:数据长度
//返回: CRC校验值
// *****************************************************************************/
//uint16_t CRC16_Check(uint8_t *CRC_Buf, const uint8_t CRC_Leni) {
//    uint16_t i, j;
//    uint16_t CRC_Sumx;
//
//    CRC_Sumx = 0xFFFF;
//    for (i = 0; i < CRC_Leni; i++) {
//        CRC_Sumx ^= *(CRC_Buf + i); //异或
//        for (j = 0; j < 8; j++) {
//            if (CRC_Sumx & 0x01) {
//                CRC_Sumx >>= 1;
//                CRC_Sumx ^= 0xA001;
//            } else {
//                CRC_Sumx >>= 1;
//            }
//        }
//    }
//    return (CRC_Sumx);
//}

/*************************************
Function: CheckIsRight  
Description: 判断接受dat，根据fp校验，返回数据正确性
Input: fp 选择校验函数，dat:检验的数据，bytes:字节数
Output: 1：校验正确  0：校验错误
 *************************************/
bool CRCIsRight(uint8_t * CRC_Buf, const uint8_t CRC_Leni, const uint8_t* CHC_Dat) {
    uint16_t i, j;
    uint16_t CRC_Sumx;

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
    }; //CRC校验
    return (CRC_Sumx == (*CHC_Dat + (*(CHC_Dat + 1) << 8))); //校验数据+CRC
}

///*************************************
//Function: Sum_Check 
//Description: 计算和校验的数值，
//Input: frame：数据，bytes：字节数 
//Output: 和校验结果值
// *************************************/
//uint16_t Sum_Check(uint8_t *frame, const uint8_t bytes) {
//    uint16_t cksum = 0;
//    uint16_t cnt = bytes;
//    while (cnt > 0) {
//        cksum += *frame++;
//        cnt--;
//    }
//    return cksum;
//}

/*************************************
Function: Sum_Check256
Description: 计算和校验的数值，
Input: frame：数据，bytes：字节数 
Output: 和校验结果值
 *************************************/
bool SumCheckIsRight(uint8_t *frame, const uint16_t bytes, const uint8_t CheckSum) {
    uint32_t ckSum = 0; //避免数据溢出
    uint16_t cnt;

    for (cnt = 0; cnt < bytes; cnt++)
        ckSum += *frame++;

    return (CheckSum == (ckSum - ((ckSum >> 8) << 8)));
}



//bool CheckSrting(uint8_t*dat1, uint8_t*dat2, const uint8_t num) {
//    uint8_t cnt;
//    for (cnt = 0; cnt < num; cnt++) {//判断EID
//        if (*(dat1 + cnt) != *(dat2 + cnt)) {
//            return false;
//        }
//    }
//    return true;
//}

///*************************************
//Function: MD5encrypt  
//Description: 
//Input: 
//Output:
//*************************************/
//void MD5encrypt(uint8_t* input,uint8_t *output)
//{
//    
//}



