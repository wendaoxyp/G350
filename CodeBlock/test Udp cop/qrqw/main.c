#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

void CharToFloat(float *f, uint8_t *ch)
{
    uint8_t count;
    void *pf;
    pf = f;

    for (count = 0; count < 4; count++)
    {
        *((uint8_t *) pf + count) = *(ch + 3 - count);
    }
}

bool DUPDataChange(uint8_t * source_dat)
{
    uint8_t Data_Type = *(source_dat + 14); //��ȡ��һ�����ݵ����
    //    char bytes = *(source_dat + 13); //��ȡ���ݵĳ���
    uint8_t bytes = 14; //��ֵ��һ�����ݵ������ַ00 00 16
    uint8_t tmprtcc[7] = {0, 0, 0, 0, 0, 0, 0};
    float setvoltage = 0, getvoltage = 0;

    // u16 time_tmp;//��ȡʱ��
    //41 32 7F F9 02 01 00 00 00 09
    //00 1F 00 1D 00 00 3C 01 00 3C
    //02 00 00 05 41 20 00 00 06 41
    //20 00 00 03 41 20 00 00 04 41
    //20 00 00 44
//    if (!DataIsVaild((u16) Data_Type, 8, 0)) //�ж����������Ƿ񳬳���Χ
//        return false;

    //    if (!DataIsVaild((u16) bytes, 39, 3)) //�ж��ֽ����Ƿ񳬳���Χ
    //        return false;

    if (!(*(source_dat + 12)))  //�������������ACK
    {
        while (bytes < *(source_dat + 13) + 14)
        {
            Data_Type = *(source_dat + bytes);
            switch (Data_Type)
            {
            case 0x00:
            {
                printf("�趨����ʱ��Ϊ%d\t\n",(*(source_dat + bytes + 1)<<8)+*(source_dat + bytes + 2));
                bytes += 3;
                break;
            }
            case 0x01:
            {
                printf("�趨�ϴ�ʱ��Ϊ%d\t\n",(*(source_dat + bytes + 1)<<8)+*(source_dat + bytes + 2));
                bytes += 3;
                break;
            }
            case 0x02:
            {
                printf("�趨����ʱ��Ϊ%d\t\n",(*(source_dat + bytes + 1)<<8)+*(source_dat + bytes + 2));
                bytes += 3;
                break;
            }
            case 0x03:
            {
                CharToFloat(&setvoltage,source_dat + bytes + 1);
                printf("�趨��ѹΪ%.2f\t\n",setvoltage);
                bytes += 5;
                break;
            }
            case 0x04:
            {
                CharToFloat(&setvoltage,source_dat + bytes + 1);
                printf("�趨��ѹΪ%.2f\t\n",setvoltage);
                bytes += 5;
                break;
            }
            case 0x05:
            {
                CharToFloat(&setvoltage,source_dat + bytes + 1);
                printf("�趨����Ϊ%.2f\t\n",setvoltage);
                bytes += 5;
                break;
            }
            case 0x06:
            {
                CharToFloat(&setvoltage,source_dat + bytes + 1);
                printf("�趨����Ϊ%.2f\t\n",setvoltage);
                bytes += 5;
                break;
            }
            case 0x07:
            {
                printf("�趨ʱ��Ϊ%d\t\n",*(source_dat + bytes + 1));
                bytes += 5;
                break;
            }
            case 0x08:
            {
                CharToFloat(&setvoltage,source_dat + bytes + 1);
                printf("�趨��ѹ1Ϊ%.2f\t\n",setvoltage);
                bytes += 5;
                break;
            }
            default:
            {
                bytes = 100;

                break;
            }
            }
        }
//        RefreshMiotArg(); //ˢ������
        return true;
    }
    return false;
}
int main()
{
    uint8_t tmp[]=
    {
        0x41,0x32,0x7F,0xF9,0x02,0x01,0x00,0x00,0x00,0x09,
        0x00,0x1F,0x00,0x1D,0x00,0x00,0x3C,0x01,0x00,0x3C,
        0x02,0x00,0x00,0x05,0x41,0x20,0x00,0x00,0x06,0x41,
        0x20,0x00,0x00,0x03,0x41,0x20,0x00,0x00,0x04,0x41,
        0x20,0x00,0x00,0x44
    };
    if(DUPDataChange(tmp))
        printf("DataGetIsSuccessful\n");
    else
        printf("DataGetIsFail\n");
    return 0;
}
