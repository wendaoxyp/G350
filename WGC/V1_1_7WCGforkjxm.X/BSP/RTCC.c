#include "RTCC.h"
#include "WGC.h"
#include "RS485.h"
#include <xc.h>

/*************************************
Function: RTC_Configuration 
Description: ʵʱʱ�Ӻ����ӳ�ʼ��
Input: ��
Output: ��
 *************************************/
void RTC_Init(void) {
    uint8_t rtcc_tmp[7] = {0x20, 0x17, 0x10, 0x30, 0x12, 0x59, 0x00};
    // Set the RTCWREN bit
    __builtin_write_RTCWEN(); //unlock sequence

    RCFGCALbits.RTCPTR = 3; //RTCC ֵ�Ĵ�������ָ��λ
    RTCVAL = rtcc_tmp[1] & 0x00FF; //0x0016; //���  2016.6.1. 3 13:10:10
    RTCVAL = (rtcc_tmp[2] << 8) + rtcc_tmp[3]; //0x1022; //�·� ����
    RTCVAL = rtcc_tmp[4] & 0x00FF; //0x0008; //����  Сʱ
    RTCVAL = (rtcc_tmp[5] << 8) + rtcc_tmp[6]; //0x3050; //���� �� 

    // PWCPOL disabled; PWCEN disabled; RTCLK SOSC; PWCPRE disabled; RTCOUT Alarm Pulse; PWSPRE disabled; 
    //    RTCPWC = 0x0000;

    //    ALCFGRPTbits.AMASK = 0b0110; //ÿ���ж�//0b0011; -1s ������������ 0x11ÿ���������ж�һ��
    //    ALCFGRPTbits.CHIME = 1; //1 = ʹ�����壻 ARPT<7:0> ����� 00h ��λ�� FFh
    ALCFGRPTbits.ALRMEN = 0; //�رձ���
    ALCFGRPTbits.ALRMPTR = 2; //����ֵ�Ĵ�������ָ��λ
    //        ALRMVAL = 0x0000; //none       
    ALRMVAL = 0x0000; //month day 0001
    ALRMVAL = 0x0000; //week hour
    ALRMVAL = 0x0000; //minute second  0000
    //    ALRMVAL = rtcc_tmp[1] & 0x00FF; //0x0016; //���  2016.6.1. 3 13:10:10
    //    ALRMVAL = (rtcc_tmp[2] << 8) + rtcc_tmp[3]; //0x1022; //�·� ����
    //    ALRMVAL = rtcc_tmp[4] & 0x00FF; //0x0008; //����  Сʱ
    //    ALRMVAL = (rtcc_tmp[5] << 8) + 0x25; //rtcc_tmp[6] ; //0x3050; //���� �� 
    //    ALCFGRPTbits.ARPT=0;
    //    ALCFGRPTbits.ALRMEN = 1; //������ʹ�� ��ÿ�� ARPT<7:0> = 00 �� CHIME = 0 ʱ�����������¼����Զ����㣩    

    // ALRMEN enabled; ARPT 0; AMASK Every Second; CHIME enabled; ALRMPTR MIN_SEC; 
    ALCFGRPT = 0xD800; //    every day once 
    //    ALCFGRPT = 0xC800;
    // PWCPOL disabled; PWCEN disabled; RTCLK SOSC; PWCPRE disabled; RTCOUT Alarm Pulse; PWSPRE disabled; 
    RTCPWC = 0x0000;
    IPC15bits.RTCIP = 6;
    IFS3bits.RTCIF = 0; //������ص��жϱ�־״̬λ����
    IEC3bits.RTCIE = 1; //���ж� =1

    RCFGCALbits.RTCEN = 1; //ʹ�� RTCC ģ��
    RCFGCALbits.RTCWREN = 0; //�ر�RTCCдʹ��
}

void RTC_Set_Alarm(struct tm initialTime) {//, uint8_t mask) {
    //ֻ���ڽ�ֹ���� ��ALRMEN = 0��ʱ���Ķ�ʱ��������ֵ��������RTCSYNC = 0 ʱ���� ALCFGRPT �Ĵ����� CHIME λ��
    __builtin_write_RTCWEN(); //unlock sequence

    ALCFGRPTbits.ALRMEN = 0; //�ر�����
    while (RCFGCALbits.RTCSYNC); //�ȴ�ͬ��λ

    ALCFGRPTbits.ALRMPTR = 2; //����ֵ�Ĵ�������ָ��λ
    ALRMVAL = ((initialTime.tm_mon) << 8) + (initialTime.tm_mday);
    ALRMVAL = ((initialTime.tm_wday) << 8) + (initialTime.tm_hour);
    ALRMVAL = ((initialTime.tm_min) << 8) + (initialTime.tm_sec);
    RCFGCALbits.RTCWREN = 0; //�ر�RTCCдʹ��
    ALCFGRPTbits.ALRMEN = 1; //��������
}

/*************************************
Function: RTC_ReadTime 
Description: ��ȡʵʱʱ�ӵ�ʱ��
Input: 4��u16�������� 
Output: ��
 *************************************/
bool RTC_Read_Time(struct tm*currentTime) {
    uint16_t time_tmp;
    if (RCFGCALbits.RTCSYNC)//�ȴ����밲ȫ��ȡ��
        return false;

    __builtin_write_RTCWEN(); // Set the RTCWREN bit

    RCFGCALbits.RTCPTR = 3; //RTCC ֵ�Ĵ�������ָ��λ
    time_tmp = RTCVAL; //��ȡ��� 
    currentTime->tm_year = time_tmp;
    RCFGCALbits.RTCPTR = 2;
    time_tmp = RTCVAL; //��ȡ����
    currentTime->tm_mon = (time_tmp & 0xFF00) >> 8;
    currentTime->tm_mday = time_tmp & 0x00FF;
    RCFGCALbits.RTCPTR = 1;
    time_tmp = RTCVAL; //��ȡСʱ
    currentTime->tm_wday = (time_tmp & 0xFF00) >> 8;
    currentTime->tm_hour = time_tmp & 0x00FF;
    RCFGCALbits.RTCPTR = 0;
    time_tmp = RTCVAL; //��ȡ������
    currentTime->tm_min = (time_tmp & 0xFF00) >> 8;
    currentTime->tm_sec = time_tmp & 0x00FF;
    //    RCFGCALbits.RTCPTR = 3; //RTCC ֵ�Ĵ�������ָ��λ
    //    time_tmp = RTCVAL; //��ȡ��� 
    //    currentTime->tm_year = ((((time_tmp & 0x00FF) & 0xF0) >> 4)* 10 + ((time_tmp & 0x00FF) & 0x0F));
    //    RCFGCALbits.RTCPTR = 2;
    //    time_tmp = RTCVAL; //��ȡ����
    //    currentTime->tm_mon = (((((time_tmp & 0xFF00) >> 8) & 0xF0) >> 4)* 10 + (((time_tmp & 0xFF00) >> 8) & 0x0F));
    //    currentTime->tm_mday = ((((time_tmp & 0x00FF) & 0xF0) >> 4)* 10 + ((time_tmp & 0x00FF) & 0x0F));
    //    RCFGCALbits.RTCPTR = 1;
    //    time_tmp = RTCVAL; //��ȡСʱ
    //    currentTime->tm_wday = (((((time_tmp & 0xFF00) >> 8) & 0xF0) >> 4)* 10 + (((time_tmp & 0xFF00) >> 8) & 0x0F));
    //    currentTime->tm_hour = ((((time_tmp & 0x00FF) & 0xF0) >> 4)* 10 + ((time_tmp & 0x00FF) & 0x0F));
    //    RCFGCALbits.RTCPTR = 0;
    //    time_tmp = RTCVAL; //��ȡ������
    //    currentTime->tm_min = (((((time_tmp & 0xFF00) >> 8) & 0xF0) >> 4)* 10 + (((time_tmp & 0xFF00) >> 8) & 0x0F));
    //    currentTime->tm_sec = ((((time_tmp & 0x00FF) & 0xF0) >> 4)* 10 + ((time_tmp & 0x00FF) & 0x0F));
    //    currentTime->tm_isdst
    RCFGCALbits.RTCWREN = 0;

    return true;
}

/*************************************
Function: Check_RTCC 
Description: ���Ǳ��ȡʱ�� ��ֵ��RTCC
Input: 6��u8��������
Output: ��
 *************************************/
void RTC_Set_Time(struct tm initialTime) {
    __builtin_write_RTCWEN(); // Set the RTCWREN bit
    RCFGCALbits.RTCEN = 0; //Close RTCC

    IFS3bits.RTCIF = false;
    IEC3bits.RTCIE = 0;

    // set RTCC initial time
    RCFGCALbits.RTCPTR = 3; // start the sequence
    RTCVAL = (initialTime.tm_year); // YEAR
    RTCVAL = (initialTime.tm_mon) << 8 + (initialTime.tm_mday); // MONTH-1/DAY-1
    RTCVAL = (initialTime.tm_wday) << 8 + (initialTime.tm_hour); // WEEKDAY/HOURS
    RTCVAL = (initialTime.tm_min) << 8 + (initialTime.tm_sec); // MINUTES/SECONDS   

    // Enable RTCC, clear RTCWREN         
    RCFGCALbits.RTCEN = 1;
    RCFGCALbits.RTCWREN = 0;

    IEC3bits.RTCIE = 1;
}

/*************************************
Function: RTC_Refresh_Time 
Description: ���Ǳ��ȡʱ�� ��ֵ��RTCC
Input: 6��u8��������
Output: ��
 *************************************/

void RTC_Refresh_Time(void) {
    __builtin_write_RTCWEN(); // Set the RTCWREN bit
    RCFGCALbits.RTCEN = 0; //Close RTCC

    IFS3bits.RTCIF = false;
    IEC3bits.RTCIE = 0;

    // set RTCC initial time
    RCFGCALbits.RTCPTR = 3; // start the sequence
    RTCVAL = WGCTIME0bits.year; // YEAR
    RTCVAL = (WGCTIME0bits.month << 8) + WGCTIME1bits.day; // MONTH-1/DAY-1
    RTCVAL = WGCTIME1bits.hour; // WEEKDAY/HOURS
    RTCVAL = (WGCTIME2bits.min << 8) + WGCTIME2bits.sec; // MINUTES/SECONDS   
    // Enable RTCC, clear RTCWREN         
    RCFGCALbits.RTCEN = 1;
    RCFGCALbits.RTCWREN = 0;

    IEC3bits.RTCIE = 1;
}

/*************************************
Function: StartRTCC 
Description: 
Input: 
Output: 
 *************************************/
//void StartRTCC(void) {
//
//    IEC3bits.RTCIE = 1; //�����ж�
//    ALCFGRPTbits.ALRMEN = 1;
//    RCFGCALbits.RTCEN = 1; //����RTCC
//}

/*************************************
Function: StopRTCC 
Description: 
Input: 
Output: 
 *************************************/
//void StopRTCC(void) {
//    IEC3bits.RTCIE = 0; //�ر��ж� 
//    ALCFGRPTbits.ALRMEN = 0;
//    RCFGCALbits.RTCEN = 0; //�ر� RTCC ģ��
//}

void PrintTime(void) {
    struct tm time1;
    uint8_t sendstr[20] = {"1234578901234567890"};
    while (!RTC_Read_Time(&time1));

    sendstr[0] = (time1.tm_year / 16) + 0x30;
    sendstr[1] = (time1.tm_year % 16) + 0x30;
    sendstr[2] = '/';
    sendstr[3] = ((time1.tm_mon + 1) / 16) + 0x30;
    sendstr[4] = ((time1.tm_mon + 1) % 16) + 0x30;
    sendstr[5] = '/';
    sendstr[6] = (time1.tm_mday / 16) + 0x30;
    sendstr[7] = (time1.tm_mday % 16) + 0x30;
    sendstr[8] = '-';
    sendstr[9] = (time1.tm_hour / 16) + 0x30;
    sendstr[10] = (time1.tm_hour % 16) + 0x30;
    sendstr[11] = ':';
    sendstr[12] = (time1.tm_min / 16) + 0x30;
    sendstr[13] = (time1.tm_min % 16) + 0x30;
    sendstr[14] = ':';
    sendstr[15] = (time1.tm_sec / 16) + 0x30;
    sendstr[16] = (time1.tm_sec % 16) + 0x30;
    sendstr[17] = '\n';
    //        sendstr[18] = '\n';
    //        sendstr[18] = '\0';
    RS485SendString(sendstr, 18);
    //        OSTimeDlyHMSM();
}
#ifdef DEBUG_RTCC_TIME

void printrtccArg(void) {
    uint8_t tmp[10];
    uint8_t strings[200] = {'\0'}; //clear history data

    strcat(strings, "S1_t:");
    my_itoa(WGCCON3bits.delay, tmp);
    strcat(strings, tmp);

    strcat(strings, ";\tS1_c:");
    my_itoa(WGCCON3bits.count, tmp);
    strcat(strings, tmp);


    strcat(strings, ";\r\nS2_t:");
    my_itoa(WGCCON4bits.delay, tmp);
    strcat(strings, tmp);

    strcat(strings, ";\tS2_c:");
    my_itoa(WGCCON4bits.count, tmp);
    strcat(strings, tmp);
    RS485SendString1(strings); //�޷���ȷ���
}

#endif

void printnums(uint32_t settingtime) {
    uint8_t strings[50] = {'\0'}; //clear history data
    uint8_t tmp[10];
    //    strcat(strings, ch);
    my_itoa(settingtime, tmp); //���16������
    strcat(strings, tmp);
    RS485SendString1(strings); //�޷���ȷ���
    //    my_itoa(WGCCON3bits.count,tmp);
    //    strcat(strings,tmp);

    //    WGCCON3bits.delay;
    //    WGCCON4bits.count;
    //    WGCCON4bits.delay;

    //     my_itoa(); 
}


