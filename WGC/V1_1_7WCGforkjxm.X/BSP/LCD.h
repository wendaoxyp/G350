#ifndef _LCD_H
#define _LCD_H

#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <xc.h>


#define  LCD_SetLow(x,y) (LCDDATA##x &= ~(1 << y)) //某位置0 
#define  LCD_SetHigh(x,y) (LCDDATA##x |= (1 << y))  //某位清1
#define LCD_Set(x,y,z) ((LCDDATA##x)=((z)?((LCDDATA##x) | (1 << y)):((LCDDATA##x) & ~(1 << y))))
/*            
 PIN	1       2       3       4       5       6       7       8       9           10      11
COM0	--      --      --      *       1A      1B      2A      2B      5v          B_none	Sign
COM1	--      --      *       --      1F      1G      2F      2G      ERROR       B_1     Sign1
COM2	--      *       --      --      1E      1C      2E      2C      backword	B_2     Sing2
COM3	*       --      --      --      1D      P1      2D      22      forword     B_3     Sing3
 * 
PIN     12      13      14      15      16      17      18      19      20      21      22
COM0	KPa     3A      3B      4A      4B      5A      5B      6A      6B		7A      7B
COM1	m3      3F      3G      4F      4G      5F      5G      6F      6G		7F      7G
COM2	/h      3E      3C      4E      4C      5E      5C      6E      6C		7E      7C
COM3	℃      3D		P3      4D      P4      5D              6D              7D
 */
#define SegCnt 18

enum LCD_truth_table {
    N1D, P1, N2D, P2, backword, B_3, Sign3, CC, N3D, P3, N4D, P4, N5D, NUL0, N6D, NUL1, N7D, NUL5, //COM3 DATA0
    N1E, N1C, N2E, N2C, forword, B_2, Sign2, __h, N3E, N3C, N4E, N4C, N5E, N5C, N6E, N6C, N7E, N7C, //Com2 DATA4
    N1F, N1G, N2F, N2G, error, B_1, Sign1, m3, N3F, N3G, N4F, N4G, N5F, N5G, N6F, N6G, N7F, N7G, //COM1 DATA8
    N1A, N1B, N2A, N2B, power, B_0, Sign0, KPa, N3A, N3B, N4A, N4B, N5A, N5B, N6A, N6B, N7A, N7B //COM0 DATA12           
};

enum LCD_COM {
    COM0, COM1, COM2, COM3
};



#define SHOW 1
#define HIDE 0

#define POW_SHOW(x) ((x)?(LCD_SetHigh(12,4)):(LCD_SetLow(12,4)))
#define ERR_SHOW(x) ((x)?(LCD_SetHigh(8,4)):(LCD_SetLow(8,4)))
#define FOR_SHOW(x) ((x)?(LCD_SetHigh(4,4)):(LCD_SetLow(4,4)))
#define BACK_SHOW(x) ((x)?(LCD_SetHigh(0,4)):(LCD_SetLow(0,4)))
#define kPa_SHOW(x) ((x)?(LCD_SetHigh(12,7)):(LCD_SetLow(12,7)))
#define m3_SHOW(x) ((x)?(LCD_SetHigh(8,7)):(LCD_SetLow(8,7)))
#define _h_SHOW(x) ((x)?(LCD_SetHigh(4,7)):(LCD_SetLow(4,7)))
#define CC_SHOW(x) ((x)?(LCD_SetHigh(0,7)):(LCD_SetLow(0,7)))

struct LCD_FlagBits {
    uint32_t F_Charge : 1; //充电标志位
    uint32_t F_Error : 1; //错误标志位
    uint32_t F_Qm : 1; //瞬间流量标志位
    uint32_t F_Vm : 1; //总流量标志位
    uint32_t F_Bat1 : 1;
    uint32_t F_Bat2 : 1;
    uint32_t F_Bat3 : 1;
    uint32_t F_Sign1 : 1;
    uint32_t F_Sign2 : 1;
    uint32_t F_Sign3 : 1;
    uint32_t F_Sign4 : 1;
    uint32_t F_KPa : 1;
    uint32_t F_M3 : 1;
    uint32_t F_h : 1;
    uint32_t F_C : 1;
    uint32_t F_DP : 3;
    uint32_t F_Num : 1;
    uint32_t F_Time : 1;
    uint32_t None : 12;
};

union LCD_FLAGBITS {
    struct LCD_FlagBits LCD_Flagbits;
    uint32_t LCD_Flag;
};
extern union LCD_FLAGBITS W_LCDCON;

extern void LCD_Init(void);
extern void LCD_ShowTest(uint8_t, bool);
extern void BAT_SHOW(uint8_t bat);
extern void SIGN_SHOW(uint8_t sign);
extern void DP_SHOW(uint8_t dp_pos);
extern void NUMS_SHOW(uint32_t num, uint8_t all_show);
extern void ClrNum(void);
extern void TIME_SHOW(void);
extern void LCD_Task(uint32_t dat);
#endif


