#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <stdbool.h>
bool IsLeapYear(uint16_t year);
uint8_t month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

void printtime(struct tm time1,const char* str)
{
    uint8_t  sendstr[91];
    sendstr[0] = ((time1.tm_year+1900)/1000)% 10 + 0x30;
    sendstr[1] = ((time1.tm_year+1900)/100)% 10 + 0x30;
    sendstr[2] = ((time1.tm_year+1900)/10)%10 + 0x30;
    sendstr[3] = (time1.tm_year+1900) % 10 + 0x30;
    sendstr[4] = '/';
    sendstr[5] = time1.tm_mon / 10 + 0x30;
    sendstr[6] = time1.tm_mon % 10 + 0x30;
    sendstr[7] = '/';
    sendstr[8] = time1.tm_mday / 10 + 0x30;
    sendstr[9] = time1.tm_mday % 10 + 0x30;
    sendstr[10] = '-';
    sendstr[11] = time1.tm_hour / 10 + 0x30;
    sendstr[12] = time1.tm_hour % 10 + 0x30;
    sendstr[13] = ':';
    sendstr[14] = time1.tm_min / 10 + 0x30;
    sendstr[15] = time1.tm_min % 10 + 0x30;
    sendstr[16] = ':';
    sendstr[17] = time1.tm_sec / 10 + 0x30;
    sendstr[18] = time1.tm_sec % 10 + 0x30;
    sendstr[19] = '\n';
    sendstr[20]='\0';
    //        sendstr[18] = '\n';
    //        sendstr[18] = '\0';
    printf("%s is %s",str,sendstr);
}

void SetNextAlarm(uint32_t sample_sec)
{
    struct tm time1;
//    time_t time2;
    //uint16_t dat[] = {0, 0, 0, 0, 0, 0}; //计算结果后的秒、分、时、天、月、年
//    uint8_t offset = 0;
    uint32_t tmp,tmp1;
    //uint8_t sendstr[19];

    enum
    {
        sec, min, hour, day, mon, year
    };
//  time2=time(NULL);
//  time1=*gmtime(&time2); //容错设计
    time1.tm_sec=25;
    time1.tm_min=10;
    time1.tm_hour=12;
    time1.tm_mday=28;
    time1.tm_mon=1;
    time1.tm_year=0;//1900至今
    //printtime(time1,"nowtime ");


    tmp=(time1.tm_sec + sample_sec);//计算秒数
    time1.tm_sec = tmp % 60;
    tmp1 = tmp / 60;//分钟是否溢出


    if (tmp1 >0)//如果累加的时间大于60s
    {
        tmp=(time1.tm_min + tmp1);
        time1.tm_min =tmp% 60;
        tmp1 = tmp/ 60;
        if (tmp1 > 0)
        {
            tmp=(time1.tm_hour + tmp1);
            time1.tm_hour = tmp % 24;
            tmp1 = tmp / 24;
            //offset = (time1.tm_mon == 1) ? 1 : 0; //如果是2月的话，那么...
/*            if (tmp1 > 0)  //与当前的月份总天数比较
            {
                tmp=time1.tm_mday + tmp1;
                if(IsLeapYear(time1.tm_year+1900)&&(time1.tm_mon==1))//是2月并且是闰年
                    time1.tm_mday = tmp%29;//1-29
                else
                    time1.tm_mday =tmp% month[time1.tm_mon];
                tmp1 = tmp / month[time1.tm_mon];
                if (tmp1 > 0)//month
                {
                    tmp=time1.tm_mon+tmp1;
                    time1.tm_mon=tmp%12;
                    tmp1=tmp/12;
                    if(tmp1>0)
                        time1.tm_year += 1;
                }
            }*/
        }
    }
//    time1.tm_sec=dat[sec];
//    time1.tm_min=dat[min];
//    time1.tm_hour=dat[hour];
//    time1.tm_mday=dat[day];
//    time1.tm_mon=dat[mon];
//    time1.tm_year=dat[year];
//    time1.tm_sec=dat[sec];
//     printtime(time1,"nowtime ");
    printtime(time1,"settime ");
//    //    RTC_Set_Alarm();
}

int main()
{
//    GetNextAlarm(100);
uint32_t cnt=0;
    while(cnt<86400){
            cnt+=1800;
    SetNextAlarm(cnt);
    }
    return 0;
}


//void PrintTime(void) {
//    struct tm time1;
//    uint8_t sendstr[20] = {"1234578901234567890"};
//    while (!RTC_Read_Time(&time1));
//
//    sendstr[0] = time1.tm_year / 10 + 0x30;
//    sendstr[1] = time1.tm_year % 10 + 0x30;
//    sendstr[2] = '/';
//    sendstr[3] = time1.tm_mon / 10 + 0x30;
//    sendstr[4] = time1.tm_mon % 10 + 0x30;
//    sendstr[5] = '/';
//    sendstr[6] = time1.tm_mday / 10 + 0x30;
//    sendstr[7] = time1.tm_mday % 10 + 0x30;
//    sendstr[8] = '-';
//    sendstr[9] = time1.tm_hour / 10 + 0x30;
//    sendstr[10] = time1.tm_hour % 10 + 0x30;
//    sendstr[11] = ':';
//    sendstr[12] = time1.tm_min / 10 + 0x30;
//    sendstr[13] = time1.tm_min % 10 + 0x30;
//    sendstr[14] = ':';
//    sendstr[15] = time1.tm_sec / 10 + 0x30;
//    sendstr[16] = time1.tm_sec % 10 + 0x30;
//    sendstr[17] = '\n';
//    //        sendstr[18] = '\n';
//    //        sendstr[18] = '\0';
//    RS485SendString(sendstr, 18);
//    //        OSTimeDlyHMSM();
//}

bool IsLeapYear(uint16_t year)
{
    //能被4整除但不能被100整除，或能被400整除的年份即为闰年
    bool IsTure=false;

    if(!(year %4))
        IsTure= (year%100)?true:false;
    if (!(year%400))
        IsTure= true;
    return IsTure;
}


