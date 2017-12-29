//#include <ctype.h>
#include <xc.h>

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

// CONFIG1
//#pragma config FOSC = INTOSC    // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
//#pragma config WDTE = OFF    // Watchdog Timer Enable (WDT enabled while running and disabled in Sleep)
//#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
//#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
//#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
//#pragma config BOREN = OFF      // Brown-out Reset Enable (Brown-out Reset disabled)
//#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
//#pragma config IESO = OFF       // Internal/External Switchover (Internal/External Switchover mode is disabled)
//#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is disabled)
//
//// CONFIG2
//#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
//#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
//#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
//#pragma config LPBOR = OFF      // Low-Power Brown Out Reset (Low-Power BOR is disabled)
//#pragma config LVP = OFF        // Low-Voltage Programming Enable (High-voltage on MCLR/VPP must be used for programming)
//__CONFIG(FOSC_INTOSC & WDTE_OFF & PWRTE_OFF & MCLRE_ON & CP_OFF & BOREN_OFF & CLKOUTEN_OFF & IESO_OFF & FCMEN_OFF);
//__CONFIG(WRT_OFF & STVREN_ON & BORV_LO & LPBOR_OFF & LVP_OFF);
//#pragma config ICESEL = ICS_PGx1//ICE pins are shared with PGC1, PGD1

// CONFIG1
#pragma config FOSC = ECH       // Oscillator Selection (ECH, External Clock, High Power Mode (4-20 MHz): device clock supplied to CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable (Brown-out Reset disabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = OFF       // Internal/External Switchover (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is disabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LPBOR = OFF      // Low-Power Brown Out Reset (Low-Power BOR is disabled)
#pragma config LVP = ON         // Low-Voltage Programming Enable (Low-voltage programming enabled)

//#define  LED PORTDbits.RD7
#define  LED LATDbits.LATD7
#define  LED_DIR TRISDbits.TRISD7
#define  TURE 1	
#define  FALSE 0
//#define  CLRWDT()  asm("clr wdt")//CLRWDT;
//#define  debug 1
typedef  unsigned char  u8;

unsigned long ms_count=0;
//u8 temp1;
//char b='b';
//char dat[]="Hello world\r\n";//temp variable

void OSC_Init(void);
//void WatchDog_Init(void);
//void USART2_Init(void);
//char USART2_Rx(u8*);
//void USART2_Tx(char );
//void USART2_SendString(char * );
void Timer0_Init(void);
void NVIC_Configuration(void);
void Delay_ms(unsigned long time);
//void Delay_ms(unsigned int time);
//void USART2_RxTest(void);
void USART2_SendString(const char * temp);
void USART2_Init(void);

void main(void)
{	
	OSC_Init();
//	USART2_Init();
    Timer0_Init();
    NVIC_Configuration();
    USART2_Init();
	LED_DIR=0;
    
	LED=1;
//	#ifdef debug //test tx2
//	for(i=0;i<10;i++)
//		USART2_SendString(dat);
//	#endif
	while(1)
	{
		Delay_ms(1000);
        LED = ~LED;
        USART2_SendString("AT\n");
    }
}

void USART2_Init(void)
{
	SP2BRG=416;//baudrate=9600

	BAUD2CONbits.BRG16=1;
	TX2STAbits.BRGH=1;//fosc/(64(n+1))
	
	ANSELGbits.ANSG1=0;
	ANSELGbits.ANSG2=0;
	TRISGbits.TRISG1=0;//tx2
	TRISGbits.TRISG2=1;//rx2

	TX2STAbits.SYNC=0;

	RC2STAbits.SPEN=1;
	
	RC2STAbits.CREN=1;

 	TX2STAbits.TXEN=1;
}

char USART2_Rx(u8* temp)
{
	//RC2STAbits.SPEN=0;
	//RC2STAbits.SPEN=1;
	if(PIR4bits.RC2IF)
	{
		PIR4bits.RC2IF=0;
		*temp = RC2REG;
		return TURE;
	}
	else
		return FALSE;
}
/*
void USART2_RxTest(void)
{
	u8 dat1;
	if(USART2_Rx(&dat1))
	{
		switch(toupper(dat1))
		{
			case 'O':
			{
				LED=1;
				break;
			}
			case 'C':
			{
				LED=0;
				break;
			}
			default:
			{
				break;
			}
		}
	}
}*/

void USART2_Tx(char dat)
{
	TX2REG = dat;	
	while(!TX2STAbits.TRMT);
}

void USART2_SendString(const char * temp)
{
	while(*temp!='\0')
	{
		USART2_Tx(*temp);
		temp++;	
	}
}

void OSC_Init(void)
{
	OSCSTATbits.SOSCR=0;
	OSCSTATbits.OSTS=0;
	OSCSTATbits.HFIOFR=1;	
	OSCSTATbits.LFIOFR=0;
	OSCSTATbits.HFIOFS=1;
	
	OSCCONbits.IRCF0=1;//OSCCON
	OSCCONbits.IRCF1=1;
	OSCCONbits.IRCF2=1;
	OSCCONbits.IRCF3=1;//set 16MHz
	OSCCONbits.SCS1=1;//set IN_OSC	 	
}

void WatchDog_Init(void)
{
	//CONFIG1bits.WDTE0=1;
	//CONFIG1bits.WDTE1=1;
	WDTCONbits.WDTPS0=0;//1s   01010
	WDTCONbits.WDTPS1=1;
	WDTCONbits.WDTPS2=0;
	WDTCONbits.WDTPS3=1;
	WDTCONbits.WDTPS4=0;
	//SWDTEN
}

void Timer0_Init(void)
{
    OPTION_REGbits.TMR0CS=0;// Internal instruction cycle clock (FOSC/4) =4Mhz
    asm("NOP");
    asm("NOP");
    TMR0=132;//8us*(256-132))=1ms
    OPTION_REGbits.PS0=0;
    OPTION_REGbits.PS1=0;
    OPTION_REGbits.PS2=1;//Prescaler 32  32/4=8us
    OPTION_REGbits.PSA=0; 
    //watch TMR0IF;
}


void NVIC_Configuration(void)
{
    INTCONbits.GIE=1;
    INTCONbits.PEIE=1;
    INTCONbits.TMR0IE=1;
}


void interrupt tc_int(void)
{
    if (TMR0IE && TMR0IF) {
        TMR0IF=0;
    //    ++tick_count;
        ms_count++;
        return;
    }
// process other interrupt sources here, if required
}


void Delay_ms(unsigned long time)
{
    ms_count=0;
    while(time > ms_count);
}


