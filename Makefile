# MPLAB IDE generated this makefile for use with GNU make.
# Project: Lab3.mcp
# Date: Thu Oct 30 20:54:57 2014

AS = xc16-as.exe
CC = xc16-gcc.exe
LD = xc16-ld.exe
AR = xc16-ar.exe
HX = xc16-bin2hex.exe
RM = rm

Lab3.hex : Lab3.cof
	$(HX) "Lab3.cof" -omf=coff

Lab3.cof : Lab3.o lcd.o RobotMove.o
	$(CC) -omf=coff -mcpu=24FJ64GA002 "Lab3.o" "lcd.o" "RobotMove.o" -o"Lab3.cof" -Wl,-L"C:\Program Files (x86)\Microchip\xc16\v1.21\lib",-Tp24FJ64GA002.gld,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,--defsym=__ICD2RAM=1,-Map="Lab3.map",--report-mem

Lab3.o : lcd.h ../../../../../../../program\ files\ (x86)/microchip/xc16/v1.21/include/stdarg.h ../../../../../../../program\ files\ (x86)/microchip/xc16/v1.21/include/stddef.h ../../../../../../../program\ files\ (x86)/microchip/xc16/v1.21/include/stdio.h RobotMove.h ../../../../../../../program\ files\ (x86)/microchip/xc16/v1.21/support/PIC24F/h/p24fj64ga002.h Lab3.c
	$(CC) -omf=coff -mcpu=24FJ64GA002 -x c -c "Lab3.c" -o"Lab3.o" -I"C:\Program Files (x86)\Microchip\xc16\v1.21\inc" -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -g -Wall

lcd.o : ../../../../../../../program\ files\ (x86)/microchip/xc16/v1.21/support/PIC24F/h/p24fj64ga002.h lcd.c
	$(CC) -omf=coff -mcpu=24FJ64GA002 -x c -c "lcd.c" -o"lcd.o" -I"C:\Program Files (x86)\Microchip\xc16\v1.21\inc" -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -g -Wall

RobotMove.o : ../../../../../../../program\ files\ (x86)/microchip/xc16/v1.21/support/PIC24F/h/p24fj64ga002.h RobotMove.c
	$(CC) -omf=coff -mcpu=24FJ64GA002 -x c -c "RobotMove.c" -o"RobotMove.o" -I"C:\Program Files (x86)\Microchip\xc16\v1.21\inc" -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -g -Wall

clean : 
	$(RM) "Lab3.o" "lcd.o" "RobotMove.o" "Lab3.cof" "Lab3.hex"

