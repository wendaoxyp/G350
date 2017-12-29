#include "user.h"
#include "UART.h"

/****************************************************************************
����: CRC16()
˵��: CRC16У�����
����: *CRC_Buf:���ݵ�ַ
      CRC_Leni:���ݳ���
����: CRCУ��ֵ
 *****************************************************************************/
u16 CRC16_Check(u8 *CRC_Buf, const u8 CRC_Leni) {
    u16 i, j;
    u16 CRC_Sumx;

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
    }
    return (CRC_Sumx);
}

/*************************************
Function: Sum_Check 
Description: �����У�����ֵ��
Input: frame�����ݣ�bytes���ֽ��� 
Output: ��У����ֵ
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
Description: �����У�����ֵ��
Input: frame�����ݣ�bytes���ֽ��� 
Output: ��У����ֵ
 *************************************/
u8 Sum_Check256(u8 *frame, const u16 bytes) {
    u32 ckSum = 0; //�����������
    u16 cnt;

    for (cnt = 0; cnt < bytes; cnt++)
        ckSum += *frame++;

    return (u8) (ckSum - ((ckSum >> 8) << 8));
}

/*************************************
Function: CheckIsRight  
Description: �жϽ���dat������fpУ�飬����������ȷ��
Input: fp ѡ��У�麯����dat:��������ݣ�bytes:�ֽ���
Output: 1��У����ȷ  0��У�����
 *************************************/
bool CheckIsRight(FP_CRC fp, u8 * dat, const u8 bytes) {
    u16 CRCtep = fp(dat, bytes); //CRCУ��
    return (CRCtep == (*(dat + bytes)+ (*(dat + bytes + 1) << 8))); //У������+CRC
}

bool CheckSrting(u8*dat1, u8*dat2, const u8 num) {
    u8 cnt;
    for (cnt = 0; cnt < num; cnt++) {//�ж�EID
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



