#include "user.h"

/*************************************
Function: FloatToChar 
Description: ������ת��Ϊchar����
Input: ���븡���� ģʽ��4 �����ȸ����� 8 ˫���ȸ����� 
Output: �����ֵ
 *************************************/
void FloatToChar(float *f, u8 *ch) {
    u8 count;
    void * pf;
    pf = f;

    for (count = 0; count < 4; count++) {
        *(ch + count) = *((u8 *) pf + 3 - count);
    }
}

/*************************************
Function: CharToFloat 
Description: char����ת��Ϊ������ 
Input: �����ֵ    ģʽ��4 �����ȸ����� 8 ˫���ȸ����� 
Output: ���븡����
 *************************************/
void CharToFloat(float *f, u8 *ch) {
    u8 count;
    void *pf;
    pf = f;

    for (count = 0; count < 4; count++) {
        *((u8 *) pf + count) = *(ch + 3 - count);
    }
}

/*************************************
Function: FloatToChar 
Description: ������ת��Ϊchar����
Input: ���븡���� ģʽ��4 �����ȸ����� 8 ˫���ȸ����� 
Output: �����ֵ
 *************************************/
void DoubleToChar(long double *d, u8 *ch) {
    u8 count;
    void * pf;
    pf = d;

    for (count = 0; count < 8; count++) {
        *(ch + count) = *((u8 *) pf + 7 - count);
    }
}

/*************************************
Function: HCD 
Description: 16����ת��Ϊ10����
Input: ���ݣ��ֽ���
Output: �����ֵ
 *************************************/
u8 HCD(u8 dat) {
    return ((dat >> 4)&0x0f)*10 + (dat & 0x0f);
}

/*************************************
Function: DCH 
Description: 10����ת��Ϊ16����
Input: ���ݣ��ֽ���
Output: �����ֵ
 *************************************/
u8 DCH(u8 dat) { //0x11 17
    return ((dat / 10 << 4)&0xF0) | ((dat % 10)&0x0F);
}

//u8 D2Hex(u8 dat)//0x11��17��-> 0x17  
//{
//    if(dat>)
//}

/*************************************
Function: DataIsVaild 
Description: �ж������Ƿ���Ч
Input: �Ƿ�
Output: �����ֵ
 *************************************/
bool DataIsVaild(u16 dat, const u16 max, const u16 min) {
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
void SetVaildData(u8 * dat, const u32 max, const u16 min) {
    u16 tmp = (* dat << 8) + *(dat + 1);

    if (tmp > max) {
        *dat = max >> 8;
        *(dat + 1) = max & 0x00ff;
    } else if (tmp < min) {
        *dat = min >> 8;
        *(dat + 1) = min & 0x00ff;
    }
}
//�����ݷ�ת

void DataReverse(u8 *dat, const u8 byte) {
    u8 tmp, cnt;

    for (cnt = 0; cnt < byte / 2; cnt++) {
        tmp = dat[cnt];
        dat[cnt] = dat[byte - 1 - cnt];
        dat[byte - 1 - cnt] = tmp;
    }
}

//8MHz-��4Mhz

void Delay10ms(char time) {
    u16 i;
    while (time-- > 0)
        for (i = 0; i < 6700; i++)
            Nop();
}

void Delay100ms(char time) {
    u16 i;
    while (time-- > 0)
        for (i = 0; i < 65500; i++)
            Nop();
}

void Delay1s(char time) {
    u32 i; //,j;
    while (time-- > 0)
        for (i = 0; i < 365000; i++)
            Nop();
}

void CopyDat(u8* output, u8 *input, const u8 bytes) {
    u8 num;
    for (num = 0; num < bytes; num++)
        *(output + num) = *(input + num);
}

void ClearDat(u8 *output, const u8 dat, const u8 bytes) {
    u8 num;
    for (num = 0; num < bytes; num++)
        *(output + num) = dat;
}

bool ValueIsEqual(u8 *v1, u8 *v2, const u8 bytes) {
    u8 cnt;
    for (cnt = 0; cnt < bytes; cnt++)
        if (*(v1 + cnt) != *(v2 + cnt))
            return false;
    return true;
}

/*************************************
Function: ToFloat 
Description: ����V1.2���ݴ���
Input: 4��u16�������� 
Output: ������
 *************************************/
void TX2Float(float *f, u8 *dat) {
    char temp = *dat; //����
    long temp0 = (long) (((unsigned long) (*(dat + 1)) << 16) + ((unsigned int) (*(dat + 2)) << 8) + *dat);

    *f = 1.0 * pow(2, temp) * temp0 / 8388608;
}

