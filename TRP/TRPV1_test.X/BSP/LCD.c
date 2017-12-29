#include <time.h>
#include "LCD.h"
extern float f_p;
union LCD_FLAGBITS W_LCDCON;

//数字符号
const uint8_t LCD_NUM[10][8] = {
    {N1A, N1B, N1C, N1D, N1E, N1F, 0xFF, N1G}, //[0]0xFF后面数据为HIDE
    {N1B, N1C, 0xFF, N1A, N1D, N1E, N1F, N1G}, //[1]
    {N1A, N1B, N1G, N1E, N1D, 0xFF, N1C, N1F}, //[2]
    {N1A, N1B, N1C, N1D, N1G, 0xFF, N1E, N1F}, //[3]
    {N1B, N1C, N1F, N1G, 0xFF, N1A, N1D, N1E}, //[4]
    {N1A, N1C, N1D, N1F, N1G, 0xFF, N1B, N1E}, //[5]
    {N1A, N1C, N1D, N1E, N1F, N1G, 0xFF, N1B}, //[6]
    {N1A, N1B, N1C, 0xFF, N1D, N1E, N1F, N1G}, //[7]
    {N1A, N1B, N1C, N1D, N1E, N1F, N1G, 0xFF}, //[8]
    {N1A, N1B, N1C, N1D, N1F, N1G, 0xFF, N1E}, //[9]
    //    {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}, //[10]
};
//数字偏移量
const uint8_t LCD_NUM_OFFSET[7] = {0, 2, 8, 10, 12, 14, 16};

static void LCD_Show(uint16_t value, bool operation);
static void NUM_SHOW(uint8_t num, uint8_t pos);

void LCD_Init(void) {
    LCDSE0 = 0xFFFF; //设置SEG0-15为段驱动引脚
    LCDSE1 = 0x0003; //设置SEG16-17为段驱动引脚
    LCDDATA0 = LCDDATA1 = LCDDATA4 = LCDDATA5 = 0;
    LCDDATA8 = LCDDATA9 = LCDDATA16 = LCDDATA17 = 0;
    LCDREG = 0x0004;
    //	LCDREF=0x07F0;  //external
    LCDREF = 0x805F; //internal regsistor ladder
    LCDPS = 0x0002;
    LCDREFbits.LCDCST = 0;
    LCDCON = 0x800B; // 4 common
}

//void LCD_ShowTest(void) {
//    LCD_Show(8, 0); //25
//    Delay1s(1);
//}

void LCD_ShowTest(uint8_t value, bool operation) {
    LCD_Show(value, operation); //25
    //    Delay1s(1);
}
//子函数

static void LCD_Show(uint16_t value, bool operation) {
    uint8_t com = (value / SegCnt)&0x00ff; //获取公共码
    uint8_t seg = value % SegCnt; //获取段码

    switch (com) {
        case COM0:
        {
            if (seg > 15)
                LCD_Set(1, seg % 16, operation);
            else
                LCD_Set(0, seg, operation);
            break;
        }
        case COM1:
        {
            if (seg > 15)
                LCD_Set(5, seg % 16, operation);
            else
                LCD_Set(4, seg, operation);
            break;
        }
        case COM2:
        {
            if (seg > 15)
                LCD_Set(9, seg % 16, operation);
            else
                LCD_Set(8, seg, operation);
            break;
        }
        case COM3:
        {
            if (seg > 15)
                LCD_Set(13, seg % 16, operation);
            else
                LCD_Set(12, seg, operation);
            break;
        }
    }
}

static void NUM_SHOW(uint8_t num, uint8_t pos) {
    uint8_t cnt; //, tmp; //, offset = pos * 2;
    bool show_or_hide = SHOW;
    //    bool IsHideflag = false;
    for (cnt = 0; cnt < 8; cnt++) {
        if ((LCD_NUM[num][cnt] == 0xff) && show_or_hide)//如果已经找到了OxFF，则接下来的数据都是隐藏,并且跳过0xff
        {
            show_or_hide = HIDE;
            continue;
        }
        //        tmp = (LCD_NUM[num][cnt] + LCD_NUM_OFFSET[pos]) % 72;
        LCD_Show((LCD_NUM[num][cnt] + LCD_NUM_OFFSET[pos]) % 72, show_or_hide);
    }
}

void BAT_SHOW(uint8_t bat) {
    switch (bat) {
        case 0:
        {
            LCD_Show(B_0, SHOW);
            LCD_Show(B_1, HIDE);
            LCD_Show(B_2, HIDE);
            LCD_Show(B_3, HIDE);
            break;
        }
        case 1:
        {
            LCD_Show(B_0, SHOW);
            LCD_Show(B_1, SHOW);
            LCD_Show(B_2, HIDE);
            LCD_Show(B_3, HIDE);
            break;
        }
        case 2:
        {
            LCD_Show(B_0, SHOW);
            LCD_Show(B_1, SHOW);
            LCD_Show(B_2, SHOW);
            LCD_Show(B_3, HIDE);
            break;
        }
        case 3:
        {
            LCD_Show(B_0, SHOW);
            LCD_Show(B_1, SHOW);
            LCD_Show(B_2, SHOW);
            LCD_Show(B_3, SHOW);
            break;
        }
        default:
        {
            LCD_Show(B_0, HIDE);
            LCD_Show(B_1, HIDE);
            LCD_Show(B_2, HIDE);
            LCD_Show(B_3, HIDE);
            break;
        }
    }
}

void SIGN_SHOW(uint8_t sign) {
    switch (sign) {
        case 1:
        {
            LCD_Show(Sign0, SHOW);
            LCD_Show(Sign1, HIDE);
            LCD_Show(Sign2, HIDE);
            LCD_Show(Sign3, HIDE);
            break;
        }
        case 2:
        {
            LCD_Show(Sign0, SHOW);
            LCD_Show(Sign1, SHOW);
            LCD_Show(Sign2, HIDE);
            LCD_Show(Sign3, HIDE);
            break;
        }
        case 3:
        {
            LCD_Show(Sign0, SHOW);
            LCD_Show(Sign1, SHOW);
            LCD_Show(Sign2, SHOW);
            LCD_Show(Sign3, HIDE);
            break;
        }
        case 4:
        {
            LCD_Show(Sign0, SHOW);
            LCD_Show(Sign1, SHOW);
            LCD_Show(Sign2, SHOW);
            LCD_Show(Sign3, SHOW);
            break;
        }
        default:
        {
            LCD_Show(Sign0, HIDE);
            LCD_Show(Sign1, HIDE);
            LCD_Show(Sign2, HIDE);
            LCD_Show(Sign3, HIDE);
            break;
        }
    }
}

void NUMS_SHOW(uint32_t num, uint8_t all_show) {
    char cnt; //
    uint8_t num_tmp;
    uint8_t IsFindHead = 0;
    //    uint8_t nums[7] = {0, 0, 0, 0, 0, 0, 0};

    //    ClrNum();
    if (!num)
        NUM_SHOW(0, 0);
    else
        //获取数字位数
        for (cnt = 6; cnt >= 0; cnt--) {
            num_tmp = (uint32_t) (num / pow(10, cnt)) % 10;
            if (num_tmp) {//如果字节为0的话，那么就pass
                IsFindHead = 1;
                NUM_SHOW(num_tmp, cnt);
            } else {
                if (IsFindHead)
                    NUM_SHOW(num_tmp, cnt);
                //            else
                //                NUM_SHOW(11, cnt);
            }
        }
}

void TIME_SHOW(void) {
    struct tm tmptr;
    uint8_t cnt;
    ClrNum();

    while (!RTC_Read_Time(&tmptr))
        if (cnt++ > 3)
            return; //添加错误提示
    //    time->tm_year;//显示小时
    NUM_SHOW(tmptr.tm_hour >> 4, 5);
    NUM_SHOW(GetMod(tmptr.tm_hour, 4), 4);
    //    DP_SHOW(4);
    NUM_SHOW(tmptr.tm_min >> 4, 3);
    NUM_SHOW(GetMod(tmptr.tm_min, 4), 2);
    //    DP_SHOW(2);
    NUM_SHOW(tmptr.tm_sec >> 4, 1);
    NUM_SHOW(GetMod(tmptr.tm_sec, 4), 0);
}

void DP_SHOW(uint8_t dp_pos) {
    //显示小数点
    switch (dp_pos) {
        case 1:
        {
            LCD_Show(P1, SHOW);
            LCD_Show(P2, HIDE);
            LCD_Show(P3, HIDE);
            LCD_Show(P4, HIDE);
            break;
        }
        case 2:
        {
            LCD_Show(P1, HIDE);
            LCD_Show(P2, SHOW);
            LCD_Show(P3, HIDE);
            LCD_Show(P4, HIDE);
            break;
        }
        case 3:
        {
            LCD_Show(P1, HIDE);
            LCD_Show(P2, HIDE);
            LCD_Show(P3, SHOW);
            LCD_Show(P4, HIDE);
            break;
        }
        case 4:
        {
            LCD_Show(P1, HIDE);
            LCD_Show(P2, HIDE);
            LCD_Show(P3, HIDE);
            LCD_Show(P4, SHOW);
            break;
        }
        default:
        {
            LCD_Show(P1, HIDE);
            LCD_Show(P2, HIDE);
            LCD_Show(P3, HIDE);
            LCD_Show(P4, HIDE);
            break;
        }
    }
}

void ClrNum(void) {
    uint8_t x, y, z, m;
    for (y = 0; y < 4; y++)//清楚字母部分1
        for (x = 0; x < 4; x++)
            LCD_Show(x + y * SegCnt, HIDE);

    for (z = 0; z < 4; z++)//清楚字母部分2
        for (m = 8; m < SegCnt; m++)
            LCD_Show(m + z * SegCnt, HIDE);
}

void ClrScreen(void) {
    uint16_t lcd_x = 0, lcd_y = 0;
    for (lcd_y = 0; lcd_y < 4; lcd_y++)
        for (lcd_x = 0; lcd_x < SegCnt; lcd_x++)
            LCD_Show(lcd_x + lcd_y * SegCnt, HIDE);
}

void LCD_Task(uint32_t dat) {
    ClrScreen();
    (W_LCDCON.LCD_Flagbits.F_Bat1) ? BAT_SHOW(1) : BAT_SHOW(4);
    (W_LCDCON.LCD_Flagbits.F_Bat2) ? BAT_SHOW(2) : BAT_SHOW(4);
    (W_LCDCON.LCD_Flagbits.F_Bat3) ? BAT_SHOW(3) : BAT_SHOW(4);
    (W_LCDCON.LCD_Flagbits.F_C) ? CC_SHOW(SHOW) : CC_SHOW(HIDE);
    (W_LCDCON.LCD_Flagbits.F_M3) ? m3_SHOW(SHOW) : m3_SHOW(HIDE);
    (W_LCDCON.LCD_Flagbits.F_KPa) ? kPa_SHOW(SHOW) : kPa_SHOW(HIDE);
    (W_LCDCON.LCD_Flagbits.F_h) ? _h_SHOW(SHOW) : _h_SHOW(HIDE);
    (W_LCDCON.LCD_Flagbits.F_Charge) ? POW_SHOW(SHOW) : POW_SHOW(HIDE);
    (W_LCDCON.LCD_Flagbits.F_Error) ? ERR_SHOW(SHOW) : ERR_SHOW(HIDE);
    (W_LCDCON.LCD_Flagbits.F_Qm) ? FOR_SHOW(SHOW) : FOR_SHOW(HIDE);
    (W_LCDCON.LCD_Flagbits.F_Vm) ? BACK_SHOW(SHOW) : BACK_SHOW(HIDE);
    (W_LCDCON.LCD_Flagbits.F_Sign1) ? SIGN_SHOW(1) : SIGN_SHOW(0);
    (W_LCDCON.LCD_Flagbits.F_Sign2) ? SIGN_SHOW(2) : SIGN_SHOW(0);
    (W_LCDCON.LCD_Flagbits.F_Sign3) ? SIGN_SHOW(3) : SIGN_SHOW(0);
    (W_LCDCON.LCD_Flagbits.F_Sign4) ? SIGN_SHOW(4) : SIGN_SHOW(0);
    DP_SHOW(W_LCDCON.LCD_Flagbits.F_DP);

    if (W_LCDCON.LCD_Flagbits.F_Num)
        NUMS_SHOW(dat, 0);
    else if (W_LCDCON.LCD_Flagbits.F_Time)
        TIME_SHOW();
    else
        Nop();
    W_LCDCON.LCD_Flag = 0; //清楚所有标志
}


void ShowPressure(void) {//显示压力值
    uint32_t pressure10 = 0;

    pressure10 = f_p * 1000;
    if (pressure10) {//如果压力值为0
        //                NUMS_SHOW((uint32_t) pressure10, 0);
        W_LCDCON.LCD_Flagbits.F_DP = 3;
    } else {
        W_LCDCON.LCD_Flagbits.F_DP = 0;
        //                NUMS_SHOW(0, 0);
    }
    W_LCDCON.LCD_Flagbits.F_KPa = 1;
    W_LCDCON.LCD_Flagbits.F_Num = 1;
    LCD_Task(pressure10); //执行LCD刷新任务
}





