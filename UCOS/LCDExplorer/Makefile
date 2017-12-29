# MPLAB IDE generated this makefile for use with GNU make.
# Project: LCDDemo.mcp
# Date: Tue Sep 13 15:08:33 2011

AS = pic30-as.exe
CC = pic30-gcc.exe
LD = pic30-ld.exe
AR = pic30-ar.exe
HX = pic30-bin2hex.exe
RM = rm

LCDDemo.hex : LCDDemo.cof
	$(HX) "LCDDemo.cof"

LCDDemo.cof : Main.o LCD.o ADC.o Display.o Switch.o RTCC.o Contrast.o Banner.o
	$(CC) -mcpu=24FJ128GA310 "Main.o" "LCD.o" "ADC.o" "Display.o" "Switch.o" "RTCC.o" "Contrast.o" "Banner.o" -o"LCDDemo.cof" -Wl,-Tp24FJ128GA310.gld,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__MPLAB_DEBUGGER_REAL_ICE=1,--defsym=__ICD2RAM=1,-Map="LCDDemo.map",--report-mem

Main.o : Banner.h Contrast.h RTCC.h Switch.h Display.h ADC.h LCD.h ../../../../../program\ files/microchip/mplabc30/v3.30b/support/PIC24F/h/p24FJ128GA310.h Demo.h Main.c
	$(CC) -mcpu=24FJ128GA310 -x c -c "Main.c" -o"Main.o" -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -g -Wall

LCD.o : Banner.h Contrast.h RTCC.h Switch.h Display.h ADC.h LCD.h ../../../../../program\ files/microchip/mplabc30/v3.30b/support/PIC24F/h/p24FJ128GA310.h Demo.h LCD.c
	$(CC) -mcpu=24FJ128GA310 -x c -c "LCD.c" -o"LCD.o" -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -g -Wall

ADC.o : Banner.h Contrast.h RTCC.h Switch.h Display.h ADC.h LCD.h ../../../../../program\ files/microchip/mplabc30/v3.30b/support/PIC24F/h/p24FJ128GA310.h Demo.h ADC.C
	$(CC) -mcpu=24FJ128GA310 -x c -c "ADC.C" -o"ADC.o" -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -g -Wall

Display.o : Banner.h Contrast.h RTCC.h Switch.h Display.h ADC.h LCD.h ../../../../../program\ files/microchip/mplabc30/v3.30b/support/PIC24F/h/p24FJ128GA310.h Demo.h Display.C
	$(CC) -mcpu=24FJ128GA310 -x c -c "Display.C" -o"Display.o" -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -g -Wall

Switch.o : Banner.h Contrast.h RTCC.h Switch.h Display.h ADC.h LCD.h ../../../../../program\ files/microchip/mplabc30/v3.30b/support/PIC24F/h/p24FJ128GA310.h Demo.h Switch.c
	$(CC) -mcpu=24FJ128GA310 -x c -c "Switch.c" -o"Switch.o" -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -g -Wall

RTCC.o : Banner.h Contrast.h RTCC.h Switch.h Display.h ADC.h LCD.h ../../../../../program\ files/microchip/mplabc30/v3.30b/support/PIC24F/h/p24FJ128GA310.h Demo.h RTCC.c
	$(CC) -mcpu=24FJ128GA310 -x c -c "RTCC.c" -o"RTCC.o" -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -g -Wall

Contrast.o : Banner.h Contrast.h RTCC.h Switch.h Display.h ADC.h LCD.h ../../../../../program\ files/microchip/mplabc30/v3.30b/support/PIC24F/h/p24FJ128GA310.h Demo.h Contrast.c
	$(CC) -mcpu=24FJ128GA310 -x c -c "Contrast.c" -o"Contrast.o" -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -g -Wall

Banner.o : Banner.h Contrast.h RTCC.h Switch.h Display.h ADC.h LCD.h ../../../../../program\ files/microchip/mplabc30/v3.30b/support/PIC24F/h/p24FJ128GA310.h Demo.h Banner.c
	$(CC) -mcpu=24FJ128GA310 -x c -c "Banner.c" -o"Banner.o" -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -g -Wall

clean : 
	$(RM) "Main.o" "LCD.o" "ADC.o" "Display.o" "Switch.o" "RTCC.o" "Contrast.o" "Banner.o" "LCDDemo.cof" "LCDDemo.hex"

