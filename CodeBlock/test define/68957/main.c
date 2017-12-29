#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
typedef struct STRCMP {
    uint8_t *SourceData;
    uint8_t Source_len;
    uint8_t *CheckData;
    uint8_t Check_len;
    uint8_t* GetData;
    uint8_t Get_len;
    uint8_t Real_len;//ʵ�ʻ�ȡ����
} StrCmp;

/*************************************
Function: UARTnDataCheck
Description:
Input:
Output: �Ƿ��ȡ������
Notice���ֽ������ܴ���256 ȡ���ݵ�ʱ����ܶ�
 *************************************/
/*************************************
Function: UARTnDataCheck
Description:
Input: ���ݽṹ��
Output: �Ƿ��ȡ������
Notice���ֽ������ܴ���256 ȡ���ݵ�ʱ����ܶ�
 *************************************/
bool UARTDataIsRight(StrCmp * strcmp) {//ע��'\0'
    bool IsFind = false; //��¼�ֽ���
    uint8_t cnt = 0/*У��Ѱ��ѭ����ַ*/, cnt1 = 0/*У���ж�ѭ����ַ*/, cnt2/*��ֵ��ַ*/, /*offset,*/ byte = 0;

    if (!strcmp->Check_len || !strcmp->Source_len)//������õ��ֽ���Ϊ0�Ļ������ش���
        return false; //Ϊ��ȡ

    while (cnt < strcmp->Source_len) {
        if (*(strcmp->SourceData + cnt) == *(strcmp->CheckData)) {//�������==head�Ļ�
            for (cnt1 = 1; cnt1 < strcmp->Check_len; cnt1++) {//��ȡ֡ͷ�����ݳ���
                if (*(strcmp->SourceData + cnt + cnt1) == *(strcmp->CheckData + cnt1)) {//�����ȡ�����ݺ�֡ͷһ������ô������ȡ���ݣ���֮�˳�
                    IsFind = true;
                    continue;
                } else {
                    IsFind = false;
                    break;
                }
            }
        }
        if (IsFind) break; //����ҵ����ݣ��˳�Ѱ��֡ͷ����
        cnt++; //У��λ�ü�1
    }

    if (IsFind) {//������ڽ��ܵ��ֽ������ҵ�֡ͷ
        if (strcmp->Get_len < strcmp->Check_len) {
            byte = strcmp->Get_len; //��ȡ�ֽ�С��У���ֽ�,����ֻ��ҪУ�鲻��Ҫ��ȡ����
            for (cnt2 = 0; cnt2 < byte; cnt2++) //��ȡ֡ͷ����
                *(strcmp->GetData + cnt2) = *(strcmp->CheckData + cnt2);
        } else {//���Ҫ��ȡ���ֽ�������֡ͷ���ݣ���Ҫ�ж���Ч��ʣ���ֽ�������
            if (strcmp->Source_len - cnt < strcmp->Get_len)//�����ȡ���ݴ�����Ч���ݣ�
                for (cnt2 = 0; cnt2 < strcmp->Source_len - cnt; cnt2++) //��ȡʣ������
                    *(strcmp->GetData + cnt2) = *(strcmp->SourceData + cnt + cnt2);
            else
                for (cnt2 = 0; cnt2 <= strcmp->Get_len; cnt2++) //��ȡʣ������
                    *(strcmp->GetData + cnt2) = *(strcmp->SourceData + +cnt + cnt2);
        }
        strcmp->Real_len = cnt2; //ʵ�ʻ�ȡ���ĳ���
        return true;
    }
    strcmp->Real_len = 0;
    return false;
}

int main()
{
    uint8_t GetData1[1],cnt;
    uint8_t SourceData1[15]="012348101234567";
    uint8_t CheckData1[5]="12345";
    StrCmp tmp;
    tmp.CheckData=CheckData1;
    tmp.Check_len=sizeof(CheckData1)/sizeof(uint8_t);
    tmp.GetData=GetData1;
    tmp.Get_len=sizeof(GetData1)/sizeof(uint8_t);
    tmp.SourceData=SourceData1;
    tmp.Source_len=sizeof(SourceData1)/sizeof(uint8_t);
    if(UARTDataIsRight(&tmp)){
        printf("The length of Get data is %d\n",tmp.Real_len);
        for(cnt=0;cnt<tmp.Real_len;cnt++)
            printf("Get_Data[%d]=%c\n",cnt,*(tmp.GetData+cnt));
    }else
        printf("Error \n");
    return 0;
}
