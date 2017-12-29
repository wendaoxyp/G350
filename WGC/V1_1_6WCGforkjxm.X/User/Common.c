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

//void Delayms(uint16_t time) {//���ܴ���1000,���
//    TMR2 = 0; //�����ʱ��2�ļ�����
//    PR2 = 625 * time / 10; //���ö�ʱʱ��
//    IFS0bits.T2IF = 0;
//    T2CONbits.TON = 1; //������ʱ����    
//    while (!IFS0bits.T2IF); //�ȴ���ʱʱ�䵽
//    T2CONbits.TON = 0; //�رն�ʱ����
//    IFS0bits.T2IF = 0; //�����־λ
//}
//8MHz-��4Mhz ʹ��������ĺ���
//0x0271 10ms

//32Mhz

void Delay1ms(char time) {
    uint16_t i;
    while (time-- > 0)
        for (i = 0; i < 2300; i++)
            Nop();
}

void Delay10ms(char time) {
    uint16_t i;
    while (time-- > 0)
        for (i = 0; i < 23000; i++)
            Nop();
}

void Delay100ms(char time) {
    uint32_t i;
    while (time-- > 0)
        for (i = 0; i < 122500; i++)
            Nop();
}

void Delay1s(char time) {
    uint32_t i; //,j;
    while (time-- > 0)
        for (i = 0; i < 1235000; i++)
            Nop();
}

//void Delays(char time) {
//    uint8_t cnt;
//    for (cnt = 0; cnt < time; cnt++)
//        Delayms(1000);
//}

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


