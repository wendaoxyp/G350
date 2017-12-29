/* 
 * File:   AllInclude.h
 * Author: TURONG62
 *
 * Created on 2016年8月11日, 下午1:14
 */

#ifndef ALLINCLUDE_H
#define	ALLINCLUDE_H

#ifdef	__cplusplus
extern "C" {
#endif

    /*************************头文件*****************************/
#include "user.h"
#include "UART.h"
#include "RTCC.h"
#include "TIM.h"
    //#include "25L64B.h"
#include "SPI.h"
#include "ICN.h"
#include "RS485.h"
#include "CheckData.h"
#include "Mp.h"
#include "GPRS.h"
#include "SerialBuffer.h"
#include "PC.h"
#include "Miot1601.h"
#include "DeepSleep.h"
#include "stdio.h"
#include "task.h"
    //#include "IC.h"
    //#include "Print.h"
#include "Queue.h"
#include "SPI.h"
#include "ADC.h"
#include "Status.h"

//    QUEUE line;
    //V2 
    int FBS __attribute__((space(prog), address(0xF80000))) = 0xF;
    //_FBS(
    //    BWRP_OFF &           // Boot Segment Write Protect (Disabled)
    //    BSS_OFF              // Boot segment Protect (No boot program flash segment)
    //);
    int FGS __attribute__((space(prog), address(0xF80004))) = 0x3;
    //_FGS(
    //    GWRP_OFF &           // General Segment Write Protect (General segment may be written)
    //    GSS0_OFF             // General Segment Code Protect (No Protection)
    //);
    int FOSCSEL __attribute__((space(prog), address(0xF80006))) = 0x60;//0xF0; //0x5E;//0xBC ;
    //_FOSCSEL(
    //    FNOSC_LPFRC &        // Oscillator Select (500kHz Low-Power FRC oscillator with Postscaler(LPFRCDIV))
    //    SOSCSRC_DIG &        // SOSC Source Type (Digital Mode for use with external source)
    //    LPRCSEL_HP &         // LPRC Oscillator Power and Accuracy (High Power, High Accuracy Mode)
    //    IESO_OFF             // Internal External Switch Over bit (Internal External Switchover mode disabled (Two-speed Start-up disabled))
    //);
    int FOSC __attribute__((space(prog), address(0xF80008))) = 0x33; //0x33; //;0x70     3B
    //_FOSC(
    //    POSCMOD_NONE &       // Primary Oscillator Configuration bits (Primary oscillator disabled)
    //    OSCIOFNC_OFF &       // CLKO Enable Configuration bit (CLKO output disabled)
    //    POSCFREQ_HS &        // Primary Oscillator Frequency Range Configuration bits (Primary oscillator/external clock input frequency greater than 8MHz)
    //    SOSCSEL_SOSCHP &     // SOSC Power Selection Configuration bits (Secondary Oscillator configured for high-power operation)
    //    FCKSM_CSDCME         // Clock Switching and Monitor Selection (Both Clock Switching and Fail-safe Clock Monitor are enabled)
    //);
    int FWDT __attribute__((space(prog), address(0xF8000A))) = 0xFF; //DF
    //_FWDT(
    //    WDTPS_PS32768 &      // Watchdog Timer Postscale Select bits (1:32768)
    //    FWPSA_PR128 &        // WDT Prescaler bit (WDT prescaler ratio of 1:128)
    //    FWDTEN_SWON &        // Watchdog Timer Enable bits (WDT controlled with the SWDTEN bit setting)
    //    WINDIS_OFF           // Windowed Watchdog Timer Disable bit (Standard WDT selected(windowed WDT disabled))
    //);

    int FPOR __attribute__((space(prog), address(0xF8000C))) = 0xFC; //0xBB ;//0xFF//0xFC
    //_FPOR(
    //    BOREN_BOR3 &         // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware, SBOREN bit disabled)
    //    LVRCFG_ON &          // Low Voltage Regulator Configuration bit (Low Voltage regulator is available and controlled by LVREN bit)
    //    PWRTEN_ON &          // Power-up Timer Enable bit (PWRT enabled)
    //    I2C1SEL_PRI &        // Alternate I2C1 Pin Mapping bit (Use Default SCL1/SDA1 Pins For I2C1)
    //    BORV_V30 &           // Brown-out Reset Voltage bits (Brown-out Reset set to Highest Voltage (3.0V))
    //    MCLRE_ON             // MCLR Pin Enable bit (RA5 input pin disabled,MCLR pin enabled)
    //);
    int FICD __attribute__((space(prog), address(0xF8000E))) = 0x82;
    //_FICD(
    //    ICS_PGx2             // ICD Pin Placement Select bits (EMUC/EMUD share PGC2/PGD2)
    //);

    int FDS __attribute__((space(prog), address(0xF80010))) = 0x1F; //0x1F ;
    //_FDS(
    //    DSWDTPS_DSWDTPSF &   // Deep Sleep Watchdog Timer Postscale Select bits (1:2,147,483,648 (25.7 Days))
    //    DSWDTOSC_LPRC &      // DSWDT Reference Clock Select bit (DSWDT uses Low Power RC Oscillator (LPRC))
    //    DSBOREN_ON &         // Deep Sleep Zero-Power BOR Enable bit (Deep Sleep BOR enabled in Deep Sleep)
    //    DSWDTEN_OFF          // Deep Sleep Watchdog Timer Enable bit (DSWDT disabled)
    //);    

#ifdef	__cplusplus
}
#endif

#endif	/* ALLINCLUDE_H */

