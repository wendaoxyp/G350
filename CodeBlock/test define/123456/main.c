#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void my_itoa(uint16_t i,uint8_t *str)
{
   uint8_t buf[6];
   uint8_t cnt=0,len;
   uint16_t tmp=i;

    while(tmp)
    {
    *(buf+cnt++)=tmp%10+0x30;
    tmp/=10;
    }
    len=cnt;
    cnt+=1;
    while(cnt--)
    {
        *(str+cnt-1)=*(buf+len-cnt);
    }
    *(str+len)='\0';
}

int main()
{
    uint8_t tmp[20];
    uint16_t a;
    while(1){
    printf("请输入数据");
    scanf("%d",&a);
    my_itoa(a,tmp);
    printf("输入数据是%s\n",tmp);
    }
    return 0;
}
