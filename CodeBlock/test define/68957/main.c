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
    uint8_t Real_len;//实际获取长度
} StrCmp;

/*************************************
Function: UARTnDataCheck
Description:
Input:
Output: 是否获取到数据
Notice：字节数不能大于256 取数据的时间可能短
 *************************************/
/*************************************
Function: UARTnDataCheck
Description:
Input: 数据结构体
Output: 是否获取到数据
Notice：字节数不能大于256 取数据的时间可能短
 *************************************/
bool UARTDataIsRight(StrCmp * strcmp) {//注意'\0'
    bool IsFind = false; //记录字节数
    uint8_t cnt = 0/*校验寻找循环地址*/, cnt1 = 0/*校验判断循环地址*/, cnt2/*赋值地址*/, /*offset,*/ byte = 0;

    if (!strcmp->Check_len || !strcmp->Source_len)//如果设置的字节数为0的话，返回错误
        return false; //为获取

    while (cnt < strcmp->Source_len) {
        if (*(strcmp->SourceData + cnt) == *(strcmp->CheckData)) {//如果数据==head的话
            for (cnt1 = 1; cnt1 < strcmp->Check_len; cnt1++) {//获取帧头的数据长度
                if (*(strcmp->SourceData + cnt + cnt1) == *(strcmp->CheckData + cnt1)) {//如果获取到数据和帧头一样，那么继续获取数据，反之退出
                    IsFind = true;
                    continue;
                } else {
                    IsFind = false;
                    break;
                }
            }
        }
        if (IsFind) break; //如果找到数据，退出寻找帧头程序
        cnt++; //校验位置加1
    }

    if (IsFind) {//如果存在接受的字节数且找到帧头
        if (strcmp->Get_len < strcmp->Check_len) {
            byte = strcmp->Get_len; //获取字节小于校验字节,比如只需要校验不需要获取数据
            for (cnt2 = 0; cnt2 < byte; cnt2++) //获取帧头数据
                *(strcmp->GetData + cnt2) = *(strcmp->CheckData + cnt2);
        } else {//如果要获取的字节数大于帧头数据，需要判断有效的剩余字节数数量
            if (strcmp->Source_len - cnt < strcmp->Get_len)//如果获取数据大于有效数据，
                for (cnt2 = 0; cnt2 < strcmp->Source_len - cnt; cnt2++) //获取剩余数据
                    *(strcmp->GetData + cnt2) = *(strcmp->SourceData + cnt + cnt2);
            else
                for (cnt2 = 0; cnt2 <= strcmp->Get_len; cnt2++) //获取剩余数据
                    *(strcmp->GetData + cnt2) = *(strcmp->SourceData + +cnt + cnt2);
        }
        strcmp->Real_len = cnt2; //实际获取到的长度
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
