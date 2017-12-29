//#include<p24FV32KA301.h>
#include"UART.h"
#include "user.h"
#include "Common.h"

u16 gRTCCDate[4]; //���ڴ�����ڲ���

/*************************************
Function: RTC_Configuration 
Description: ʵʱʱ�Ӻ����ӳ�ʼ��
Input: ��
Output: ��
 *************************************/
void RTC_Configuration(void) {
    //    RTCPWCbits.RTCCLK=1;            //RTCC ʱ��ѡ��λ:RTCC ʱ��ѡ��λ
    //    RCFGCALbits.RTCOE=0;            //��ֹ RTCC ���
    //    RCFGCALbits.RTCSYNC=0;          //RTCC ֵ�Ĵ�����ͬ��λ  
    //    RCFGCALbits.CAL=0;              //RTC Ư��У׼λ
    u8 rtcc_tmp[7] = {0, 0, 0, 0, 0, 0, 0};
//    Register2Read(rtcc_tmp, mi_arg_add[mi_year], 7);
    asm volatile ("push w7"); //�� RTCWREN λ�� 1
    asm volatile ("push w8");
    asm volatile ("disi #5");
    asm volatile ("mov #0x55, w7");
    asm volatile ("mov w7, _NVMKEY");
    asm volatile ("mov #0xAA, w8");
    asm volatile ("mov w8, _NVMKEY");
    asm volatile ("bset _RCFGCAL, #13"); //set the RTCWREN bit
    asm volatile ("pop w8");
    asm volatile ("pop w7");

    RCFGCALbits.RTCPTR = 3; //RTCC ֵ�Ĵ�������ָ��λ
    RTCVAL = rtcc_tmp[1] & 0x00FF; //0x0016; //���  2016.6.1. 3 13:10:10
    RTCVAL = (rtcc_tmp[2] << 8) + rtcc_tmp[3]; //0x1022; //�·� ����
    RTCVAL = rtcc_tmp[4] & 0x00FF; //0x0008; //����  Сʱ
    RTCVAL = (rtcc_tmp[5] << 8) + rtcc_tmp[6]; //0x3050; //���� �� 

    ALCFGRPTbits.AMASK = 0b0011; //1s// 0010:10s//������������ 0x11ÿ���������ж�һ��
    ALCFGRPTbits.CHIME = 1; //1 = ʹ�����壻 ARPT<7:0> ����� 00h ��λ�� FFh
    ALCFGRPTbits.ALRMPTR = 3; //����ֵ�Ĵ�������ָ��λ
    ALRMVAL = 0x0000; //none       
    ALRMVAL = 0x0000; //month day 0001
    ALRMVAL = 0x0000; //week hour
    ALRMVAL = 0x0000; //minute second  0000
    //    ALCFGRPTbits.ARPT=0;
    ALCFGRPTbits.ALRMEN = 1; //������ʹ�� ��ÿ�� ARPT<7:0> = 00 �� CHIME = 0 ʱ�����������¼����Զ����㣩    

    RTCPWCbits.RTCCLK = 0; //SOSC 1; //RTCC ʱ��ѡ��λ:RTCC ʱ��ѡ��λ
    RCFGCALbits.RTCOE = 0; //��ֹ RTCC ���
    RCFGCALbits.RTCSYNC = 0; //RTCC ֵ�Ĵ�����ͬ��λ  
    RCFGCALbits.CAL = 0; //RTC Ư��У׼λ
    IPC15bits.RTCIP = 4;
    IFS3bits.RTCIF = 0; //������ص��жϱ�־״̬λ����
    IEC3bits.RTCIE = 1; //���ж� =1

    RCFGCALbits.RTCEN = 1; //ʹ�� RTCC ģ��
}

/*************************************
Function: RTC_ReadTime 
Description: ��ȡʵʱʱ�ӵ�ʱ��
Input: 4��u16�������� 
Output: ��
 *************************************/
void RTCReadTime(u8* dat) {
    u16 tmp[4];

    while (1) {
        if (RCFGCALbits.RTCSYNC)//�ȴ����밲ȫ��ȡ��
            continue;
//        __builtin_write_RTCWEN(); //����дʹ��
        RCFGCALbits.RTCPTR = 3; //RTCC ֵ�Ĵ�������ָ��λ
        tmp[0] = RTCVAL; //��ȡ��� 17 or 23   [17] 0000 0000 0001 0001
        RCFGCALbits.RTCPTR = 2;
        tmp[1] = RTCVAL; //��ȡ����[20a]
        RCFGCALbits.RTCPTR = 1;
        tmp[2] = RTCVAL; //��ȡСʱ[1]
        RCFGCALbits.RTCPTR = 0;
        tmp[3] = RTCVAL; //��ȡ���� ��[1D03]
//        RCFGCALbits.RTCWREN = 0; //�ر�дʹ��
        *(dat) = 0x20;
        *(dat + 1) = (u8) (tmp[0] & 0X00FF); //���   ���θ�8λ    2016.6.1. 3 13:10:10
        *(dat + 2) = (u8) (tmp[1] >> 8);
        *(dat + 3) = (u8) (tmp[1] & 0X00FF); //�·� ����
        *(dat + 4) = (u8) (tmp[2] & 0x00FF); //����  Сʱ   
        *(dat + 5) = (u8) (tmp[3] >> 8);
        *(dat + 6) = (u8) (tmp[3] & 0x00FF); //���� �� 
        break;
    }
}

/*************************************
Function: Check_RTCC 
Description: ���Ǳ��ȡʱ�� ��ֵ��RTCC
Input: 6��u8��������
Output: ��
 *************************************/
void CheckRTCC(void) {
    //    IEC3bits.RTCIE = 0; //�ر��ж� 
    //    RCFGCALbits.RTCEN = 0; //�ر� RTCC ģ��

    u8 rtcc_tmp[7] = {0, 0, 0, 0, 0, 0, 0};
//    Register2Read(rtcc_tmp, mi_arg_add[mi_year], 7); //0x14 0x11
    //    rtcc_tmp[0] = DCH(rtcc_tmp[0]); //20->0x20
    //    rtcc_tmp[1] = DCH(rtcc_tmp[1]);
    //    rtcc_tmp[2] = DCH(rtcc_tmp[2]);
    //    rtcc_tmp[3] = DCH(rtcc_tmp[3]);
    //    rtcc_tmp[4] = DCH(rtcc_tmp[4]);
    //    rtcc_tmp[5] = DCH(rtcc_tmp[5]);
    //    rtcc_tmp[6] = DCH(rtcc_tmp[6]);
    //    Nop();
    asm volatile ("push w7"); //�� RTCWREN λ�� 1
    asm volatile ("push w8");
    asm volatile ("disi #5");
    asm volatile ("mov #0x55, w7");
    asm volatile ("mov w7, _NVMKEY");
    asm volatile ("mov #0xAA, w8");
    asm volatile ("mov w8, _NVMKEY");
    asm volatile ("bset _RCFGCAL, #13"); //set the RTCWREN bit
    asm volatile ("pop w8");
    asm volatile ("pop w7");

    RCFGCALbits.RTCPTR = 3; //RTCC ֵ�Ĵ�������ָ��λ
    RTCVAL = rtcc_tmp[1] & 0x00FF; //0x0016; //���  2016.6.1. 3 13:10:10
    RTCVAL = (rtcc_tmp[2] << 8) + rtcc_tmp[3]; //0x1022; //�·� ����
    RTCVAL = rtcc_tmp[4] & 0x00FF; //0x0008; //����  Сʱ
    RTCVAL = (rtcc_tmp[5] << 8) + rtcc_tmp[6]; //0x3050; //���� �� 
//    RCFGCALbits.RTCWREN = 0;//�رն�дʹ��
    //    Nop();
    //    IEC3bits.RTCIE = 1; //�����ж�
    //    RCFGCALbits.RTCEN = 1; //����RTCC
    //    Nop();
}

/*************************************
Function: StartRTCC 
Description: 
Input: 
Output: 
 *************************************/
void StartRTCC(void) {

    IEC3bits.RTCIE = 1; //�����ж�
    ALCFGRPTbits.ALRMEN = 1;
    RCFGCALbits.RTCEN = 1; //����RTCC
}

/*************************************
Function: StopRTCC 
Description: 
Input: 
Output: 
 *************************************/
void StopRTCC(void) {
    IEC3bits.RTCIE = 0; //�ر��ж� 
    ALCFGRPTbits.ALRMEN = 0;
    RCFGCALbits.RTCEN = 0; //�ر� RTCC ģ��
}

/*************************************
Function: OutputData 
Description: ͨ������2��ӡ4*u16���͵�����
Input: 4��u16�������� 
Output: ��
 *************************************/
//void OutputData(u16* dat)
//{
//    u8 count=0;
//    *dat|=0x2000;        
//    while(count<4)
//    {
//        UART2Send(RTC_NumProcess(dat+count,12));
//        UART2Send(RTC_NumProcess(dat+count,8));
//        UART2Send(RTC_NumProcess(dat+count,4));
//        UART2Send(RTC_NumProcess(dat+count,0));
//        UART2Send(' ');
//        count++;
//    }
//    UART2Send('\n');
//}
/*************************************
Function: RTC_NumProcess 
Description: �������ݺ�����������ö�ӦASC��ֵ
Input: 4��u16�������� ��λ����
Output: ���ASCII
 *************************************/
//static u8 RTCNumProcess(u16*d,u8 s)
//{
//    return (u8)(((*d>>s)&0x000f)+0x30);
//}




