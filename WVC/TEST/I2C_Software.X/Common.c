/*************************************************
Copyright (C), 1988-1999, Tech. Co., Ltd.
File name: Common.c
Author: xx13
Version: 1.0
Date: 2017/12/29
Description: Common API����
Others: ��Ҫ�õ��Զ����
History: None
1. Date:
Author:
Modification:
2. ...
 *************************************************/
#include "Common.h"

/*************************************
Function: FloatToChar 
Description: ������ת��Ϊchar����
Input: ���븡���� ģʽ��4 �����ȸ����� 8 ˫���ȸ����� 
Output: �����ֵ
 *************************************/
void FloatToChar(float *f, uint8_t *ch) {
    uint8_t count;
    void * pf;
    pf = f;

    for (count = 0; count < 4; count++) {
        *(ch + count) = *((uint8_t *) pf + 3 - count);
    }
}

/*************************************
Function: CharToFloat 
Description: char����ת��Ϊ������ 
Input: �����ֵ    ģʽ��4 �����ȸ����� 8 ˫���ȸ����� 
Output: ���븡����
 *************************************/
void CharToFloat(float *f, uint8_t *ch) {
    uint8_t count;
    void *pf;
    pf = f;

    for (count = 0; count < 4; count++) {
        *((uint8_t *) pf + count) = *(ch + 3 - count);
    }
}

/*************************************
Function: FloatToChar 
Description: ������ת��Ϊchar����
Input: ���븡���� ģʽ��4 �����ȸ����� 8 ˫���ȸ����� 
Output: �����ֵ
 *************************************/
void DoubleToChar(long double *d, uint8_t *ch) {
    uint8_t count;
    void * pf;
    pf = d;

    for (count = 0; count < 8; count++) {
        *(ch + count) = *((uint8_t *) pf + 7 - count);
    }
}

/*************************************
Function: HCD 
Description: 16����ת��Ϊ10����
Input: ���ݣ��ֽ���
Output: �����ֵ
 *************************************/
uint8_t HCD(uint8_t dat) {
    return (dat >> 4)*10 + GetMod(dat, 4);
}

/*************************************
Function: DCH 
Description: 10����ת��Ϊ16����
Input: ���ݣ��ֽ���
Output: �����ֵ
 *************************************/
uint8_t DCH(uint8_t dat) { //0x11 17
    return ((dat / 10 << 4)&0xF0) | ((dat % 10)&0x0F);
}

//uint8_t D2Hex(uint8_t dat)//0x11��17��-> 0x17  
//{
//    if(dat>)
//}

/*************************************
Function: DataIsVaild 
Description: �ж������Ƿ���Ч
Input: �Ƿ�
Output: �����ֵ
 *************************************/
bool DataIsVaild(uint16_t dat, const uint16_t max, const uint16_t min) {
    if (dat > max) return false;
    else if (dat < min) return false;
    return true;
}

/*************************************
Function: SetVaildData 
Description: ���ݷ�ֵ���ò���
Input: �Ƿ�
Output: �����ֵ
 *************************************/
void SetVaildData(uint16_t * dat, const uint32_t max, const uint16_t min) {
    uint16_t tmp = ((*dat) << 8) + *(dat + 1);

    if (tmp > max) {
        *dat = max;
    } else if (tmp < min) {
        *dat = min;
    }
}
//�����ݷ�ת

void DataReverse(uint8_t *dat, const uint8_t byte) {
    uint8_t tmp, cnt;

    for (cnt = 0; cnt < byte / 2; cnt++) {
        tmp = dat[cnt];
        dat[cnt] = dat[byte - 1 - cnt];
        dat[byte - 1 - cnt] = tmp;
    }
}

void Delay1ms(char time) {
    uint16_t i;
    while (time-- > 0)
        for (i = 0; i < 144; i++)
            Nop();
}

void Delay10ms(char time) {
    uint16_t i;
    while (time-- > 0)
        for (i = 0; i < 1440; i++)
            Nop();
}

void Delay100ms(char time) {
    uint32_t i;
    while (time-- > 0)
        for (i = 0; i < 14400; i++)
            Nop();
}

void Delay1s(char time) {
    uint32_t i; //,j;
    while (time-- > 0)
        for (i = 0; i < 144000; i++)
            Nop();
}

void CopyDat(uint8_t* output, const uint8_t *input, const uint8_t bytes) {
    uint8_t num;
    for (num = 0; num < bytes; num++)
        *(output + num) = *(input + num);
}

void ClearDat(uint8_t *output, const uint8_t dat, const uint8_t bytes) {
    uint8_t num;
    for (num = 0; num < bytes; num++)
        *(output + num) = dat;
}

bool ValueIsEqual(const uint8_t *str1, const uint8_t *str2, const uint8_t bytes) {
    uint8_t cnt;
    for (cnt = 0; cnt < bytes; cnt++)
        if (*(str1 + cnt) != *(str2 + cnt))
            return false;
    return true;
}

//����ȥ����

uint8_t GetMod(uint16_t num, uint8_t mod_num) {
    return num - ((num >> mod_num) << mod_num);
}

//16λ����ת��Ϊ�ַ���

uint8_t my_itoa(uint16_t i, uint8_t *str) {
    uint8_t buf[6];
    uint8_t cnt = 0, len;
    uint16_t tmp = i;
    if (!tmp) {
        *str = '0';
        *(str + 1) = '\0';
        len = 1;
    } else {
        while (tmp) {
            *(buf + cnt++) = tmp % 10 + 0x30;
            tmp /= 10;
        }
        len = cnt;
        cnt += 1;
        while (cnt--) {
            *(str + cnt - 1) = *(buf + len - cnt);
        }
        *(str + len) = '\0';
    }
    return len;
}

void CmpStr(const uint8_t* str1, const uint8_t* str2, uint8_t bytes) {

}

/*************************************
Function: UARTDataIsRight
Description: ���ݽṹ������ݻ�ȡ��Ч���ݺ���Ч����
Input: ���ݽṹ��
Output: �Ƿ��ȡ������
Notice���ֽ������ܴ���256 ȡ���ݵ�ʱ����ܶ�   
 *************************************/
//bool UARTDataIsRight(StrCmp * strcmp) {//ע��
//    bool IsFind = false; //��¼�ֽ���
//    uint8_t cnt = 0/*У��Ѱ��ѭ����ַ*/, cnt1 = 0/*У���ж�ѭ����ַ*/, cnt2/*��ֵ��ַ*/, /*offset,*/ byte = 0;

//    if (!(strcmp->Check_len) || !(strcmp->Source_len))//������õ��ֽ���Ϊ0�Ļ������ش���
//        return false; //Ϊ��ȡ

//���Աȵ�str1���Աȵ�str2��str1�ֽ���

uint8_t Str_Find_Head(const uint8_t* str1, const uint8_t *str2, uint8_t str1_bytes, uint8_t str2_bytes) {
    uint8_t cnt = 0, cnt1 = 0;
    uint8_t position = 0;
    bool is_find = false;
    uint8_t *ptr = (uint8_t *) str1;
    if (str2_bytes > str1_bytes)//�涨�ж��ַ��ֽ������ܴ���Դ���ݵ��ֽ���
        return 0;

    if (str1_bytes == 1) {//���һ���ֽڵ������
        if (*ptr == *str2)
            return true;
        else
            return false;
    }
    while (cnt < str1_bytes) {
        ptr = (uint8_t *) str1 + cnt;
        if (*ptr == *str2) {//�������==head�Ļ� 
            for (cnt1 = 1; cnt1 < str2_bytes; cnt1++) {
                if (*(str1 + cnt1 + cnt) != *(str2 + cnt1)) {
                    is_find = false;
                    break;
                } else
                    is_find = true;
            }
            if (is_find) {
                position = cnt + 1;
                break;
            }
        }
        cnt += 1;
    }
    return position;
}

//uint8_t Str_Cut(uint8_t* str1, uint8_t * str2, uint8_t str1_bytes, uint8_t str2_bytes) {
//    if(str2_bytes<str1_bytes)
//        return 1;//STRING_HANDLE_ERR_NO_SIZE
//    CopyDat
//}

//if (IsFind) break; //����ҵ����ݣ��˳�Ѱ��֡ͷ����
//cnt++; //У��λ�ü�1
//}
//}
//if (IsFind) {//������ڽ��ܵ��ֽ������ҵ�֡ͷ
//    if (strcmp->Get_len < strcmp->Check_len) {
//        byte = strcmp->Get_len; //��ȡ�ֽ�С��У���ֽ�,����ֻ��ҪУ�鲻��Ҫ��ȡ����
//        for (cnt2 = 0; cnt2 < byte; cnt2++) //��ȡ֡ͷ����
//            *(strcmp->GetData + cnt2) = *(strcmp->CheckData + cnt2);
//    } else {//���Ҫ��ȡ���ֽ�������֡ͷ���ݣ���Ҫ�ж���Ч��ʣ���ֽ�������
//        if (strcmp->Source_len - cnt < strcmp->Get_len)//�����ȡ���ݴ�����Ч���ݣ�
//            for (cnt2 = 0; cnt2 < strcmp->Source_len - cnt; cnt2++) //��ȡʣ������
//                *(strcmp->GetData + cnt2) = *(strcmp->SourceData + cnt + cnt2);
//        else
//            for (cnt2 = 0; cnt2 <= strcmp->Get_len; cnt2++) //��ȡʣ������
//                *(strcmp->GetData + cnt2) = *(strcmp->SourceData + +cnt + cnt2);
//    }
//    strcmp->Real_len = cnt2; //ʵ�ʻ�ȡ���ĳ���
//    return true;
//}
//strcmp->Real_len = 0;
//return false;
//}


