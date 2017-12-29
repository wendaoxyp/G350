//#include "user.h"
#include "CheckData.h"

///****************************************************************************
//����: CRC16()
//˵��: CRC16У�����
//����: *CRC_Buf:���ݵ�ַ
//      CRC_Leni:���ݳ���
//����: CRCУ��ֵ
// *****************************************************************************/
//uint16_t CRC16_Check(uint8_t *CRC_Buf, const uint8_t CRC_Leni) {
//    uint16_t i, j;
//    uint16_t CRC_Sumx;
//
//    CRC_Sumx = 0xFFFF;
//    for (i = 0; i < CRC_Leni; i++) {
//        CRC_Sumx ^= *(CRC_Buf + i); //���
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
Description: �жϽ���dat������fpУ�飬����������ȷ��
Input: fp ѡ��У�麯����dat:��������ݣ�bytes:�ֽ���
Output: 1��У����ȷ  0��У�����
 *************************************/
bool CRCIsRight(uint8_t * CRC_Buf, const uint8_t CRC_Leni, const uint8_t* CHC_Dat) {
    uint16_t i, j;
    uint16_t CRC_Sumx;

    CRC_Sumx = 0xFFFF;
    for (i = 0; i < CRC_Leni; i++) {
        CRC_Sumx ^= *(CRC_Buf + i); //���
        for (j = 0; j < 8; j++) {
            if (CRC_Sumx & 0x01) {
                CRC_Sumx >>= 1;
                CRC_Sumx ^= 0xA001;
            } else {
                CRC_Sumx >>= 1;
            }
        }
    }; //CRCУ��
    return (CRC_Sumx == (*CHC_Dat + (*(CHC_Dat + 1) << 8))); //У������+CRC
}

///*************************************
//Function: Sum_Check 
//Description: �����У�����ֵ��
//Input: frame�����ݣ�bytes���ֽ��� 
//Output: ��У����ֵ
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
Description: �����У�����ֵ��
Input: frame�����ݣ�bytes���ֽ��� 
Output: ��У����ֵ
 *************************************/
bool SumCheckIsRight(uint8_t *frame, const uint16_t bytes, const uint8_t CheckSum) {
    uint32_t ckSum = 0; //�����������
    uint16_t cnt;

    for (cnt = 0; cnt < bytes; cnt++)
        ckSum += *frame++;

    return (CheckSum == (ckSum - ((ckSum >> 8) << 8)));
}



//bool CheckSrting(uint8_t*dat1, uint8_t*dat2, const uint8_t num) {
//    uint8_t cnt;
//    for (cnt = 0; cnt < num; cnt++) {//�ж�EID
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



