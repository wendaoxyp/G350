#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

uint8_t GetMod(uint8_t num, uint8_t mod_num) {
    return num - ((num >> mod_num) << mod_num);
}

int main()
{
    struct tm* time_tmp;
    time_t a=1499598934;
    time_t c;
    uint8_t b=183;
    time_tmp=gmtime(&a);
    printf("%d\n",time_tmp->tm_sec);
    printf("%d\n", GetMod(b,2));
    c=mktime(&time_tmp);
    printf("%ld\n", c);
    return 0;
}
