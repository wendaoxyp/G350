#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint8_t my_itoa(uint16_t i, uint8_t *str) {
    uint8_t buf[6];
    uint8_t cnt = 0, len;
    uint16_t tmp = i;
    do {
        *(buf + cnt++) = tmp % 10 + 0x30;
        tmp /= 10;
    } while (tmp);
    len = cnt;
    cnt += 1;
    while (cnt--) {
        *(str + cnt - 1) = *(buf + len - cnt);
    }
    *(str + len) = '\0';
    return len;
}
int main()
{
    char tmp[10]={1,2,3,4,5,6};
    my_itoa(192,tmp);
    printf("Hello world!\n%s",tmp);
    return 0;
}
