#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/TRPV1.0.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/TRPV1.0.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=BSP/bsp.c BSP/NVIC.c BSP/RS485.c BSP/PPS.c BSP/UART2.c BSP/UART3.c BSP/INT.c BSP/I2C.c BSP/Sleep.c BSP/DeepSleep.c BSP/RTCC.c BSP/LCD.c BSP/TIM.c BSP/CRC16.c User/HL6528.c User/SerialBuffer.c User/Common.c User/main.c User/E41.c User/CheckData.c User/CAT24C512.c User/WGC.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/BSP/bsp.o ${OBJECTDIR}/BSP/NVIC.o ${OBJECTDIR}/BSP/RS485.o ${OBJECTDIR}/BSP/PPS.o ${OBJECTDIR}/BSP/UART2.o ${OBJECTDIR}/BSP/UART3.o ${OBJECTDIR}/BSP/INT.o ${OBJECTDIR}/BSP/I2C.o ${OBJECTDIR}/BSP/Sleep.o ${OBJECTDIR}/BSP/DeepSleep.o ${OBJECTDIR}/BSP/RTCC.o ${OBJECTDIR}/BSP/LCD.o ${OBJECTDIR}/BSP/TIM.o ${OBJECTDIR}/BSP/CRC16.o ${OBJECTDIR}/User/HL6528.o ${OBJECTDIR}/User/SerialBuffer.o ${OBJECTDIR}/User/Common.o ${OBJECTDIR}/User/main.o ${OBJECTDIR}/User/E41.o ${OBJECTDIR}/User/CheckData.o ${OBJECTDIR}/User/CAT24C512.o ${OBJECTDIR}/User/WGC.o
POSSIBLE_DEPFILES=${OBJECTDIR}/BSP/bsp.o.d ${OBJECTDIR}/BSP/NVIC.o.d ${OBJECTDIR}/BSP/RS485.o.d ${OBJECTDIR}/BSP/PPS.o.d ${OBJECTDIR}/BSP/UART2.o.d ${OBJECTDIR}/BSP/UART3.o.d ${OBJECTDIR}/BSP/INT.o.d ${OBJECTDIR}/BSP/I2C.o.d ${OBJECTDIR}/BSP/Sleep.o.d ${OBJECTDIR}/BSP/DeepSleep.o.d ${OBJECTDIR}/BSP/RTCC.o.d ${OBJECTDIR}/BSP/LCD.o.d ${OBJECTDIR}/BSP/TIM.o.d ${OBJECTDIR}/BSP/CRC16.o.d ${OBJECTDIR}/User/HL6528.o.d ${OBJECTDIR}/User/SerialBuffer.o.d ${OBJECTDIR}/User/Common.o.d ${OBJECTDIR}/User/main.o.d ${OBJECTDIR}/User/E41.o.d ${OBJECTDIR}/User/CheckData.o.d ${OBJECTDIR}/User/CAT24C512.o.d ${OBJECTDIR}/User/WGC.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/BSP/bsp.o ${OBJECTDIR}/BSP/NVIC.o ${OBJECTDIR}/BSP/RS485.o ${OBJECTDIR}/BSP/PPS.o ${OBJECTDIR}/BSP/UART2.o ${OBJECTDIR}/BSP/UART3.o ${OBJECTDIR}/BSP/INT.o ${OBJECTDIR}/BSP/I2C.o ${OBJECTDIR}/BSP/Sleep.o ${OBJECTDIR}/BSP/DeepSleep.o ${OBJECTDIR}/BSP/RTCC.o ${OBJECTDIR}/BSP/LCD.o ${OBJECTDIR}/BSP/TIM.o ${OBJECTDIR}/BSP/CRC16.o ${OBJECTDIR}/User/HL6528.o ${OBJECTDIR}/User/SerialBuffer.o ${OBJECTDIR}/User/Common.o ${OBJECTDIR}/User/main.o ${OBJECTDIR}/User/E41.o ${OBJECTDIR}/User/CheckData.o ${OBJECTDIR}/User/CAT24C512.o ${OBJECTDIR}/User/WGC.o

# Source Files
SOURCEFILES=BSP/bsp.c BSP/NVIC.c BSP/RS485.c BSP/PPS.c BSP/UART2.c BSP/UART3.c BSP/INT.c BSP/I2C.c BSP/Sleep.c BSP/DeepSleep.c BSP/RTCC.c BSP/LCD.c BSP/TIM.c BSP/CRC16.c User/HL6528.c User/SerialBuffer.c User/Common.c User/main.c User/E41.c User/CheckData.c User/CAT24C512.c User/WGC.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/TRPV1.0.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=24FJ64GA306
MP_LINKER_FILE_OPTION=,--script=p24FJ64GA306.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/BSP/bsp.o: BSP/bsp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/BSP" 
	@${RM} ${OBJECTDIR}/BSP/bsp.o.d 
	@${RM} ${OBJECTDIR}/BSP/bsp.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  BSP/bsp.c  -o ${OBJECTDIR}/BSP/bsp.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/BSP/bsp.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -D__PIC24F__ -legacy-libc -I"BSP" -I"User" -O0 -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/BSP/bsp.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/BSP/NVIC.o: BSP/NVIC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/BSP" 
	@${RM} ${OBJECTDIR}/BSP/NVIC.o.d 
	@${RM} ${OBJECTDIR}/BSP/NVIC.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  BSP/NVIC.c  -o ${OBJECTDIR}/BSP/NVIC.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/BSP/NVIC.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -D__PIC24F__ -legacy-libc -I"BSP" -I"User" -O0 -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/BSP/NVIC.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/BSP/RS485.o: BSP/RS485.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/BSP" 
	@${RM} ${OBJECTDIR}/BSP/RS485.o.d 
	@${RM} ${OBJECTDIR}/BSP/RS485.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  BSP/RS485.c  -o ${OBJECTDIR}/BSP/RS485.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/BSP/RS485.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -D__PIC24F__ -legacy-libc -I"BSP" -I"User" -O0 -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/BSP/RS485.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/BSP/PPS.o: BSP/PPS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/BSP" 
	@${RM} ${OBJECTDIR}/BSP/PPS.o.d 
	@${RM} ${OBJECTDIR}/BSP/PPS.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  BSP/PPS.c  -o ${OBJECTDIR}/BSP/PPS.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/BSP/PPS.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -D__PIC24F__ -legacy-libc -I"BSP" -I"User" -O0 -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/BSP/PPS.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/BSP/UART2.o: BSP/UART2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/BSP" 
	@${RM} ${OBJECTDIR}/BSP/UART2.o.d 
	@${RM} ${OBJECTDIR}/BSP/UART2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  BSP/UART2.c  -o ${OBJECTDIR}/BSP/UART2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/BSP/UART2.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -D__PIC24F__ -legacy-libc -I"BSP" -I"User" -O0 -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/BSP/UART2.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/BSP/UART3.o: BSP/UART3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/BSP" 
	@${RM} ${OBJECTDIR}/BSP/UART3.o.d 
	@${RM} ${OBJECTDIR}/BSP/UART3.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  BSP/UART3.c  -o ${OBJECTDIR}/BSP/UART3.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/BSP/UART3.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -D__PIC24F__ -legacy-libc -I"BSP" -I"User" -O0 -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/BSP/UART3.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/BSP/INT.o: BSP/INT.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/BSP" 
	@${RM} ${OBJECTDIR}/BSP/INT.o.d 
	@${RM} ${OBJECTDIR}/BSP/INT.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  BSP/INT.c  -o ${OBJECTDIR}/BSP/INT.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/BSP/INT.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -D__PIC24F__ -legacy-libc -I"BSP" -I"User" -O0 -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/BSP/INT.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/BSP/I2C.o: BSP/I2C.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/BSP" 
	@${RM} ${OBJECTDIR}/BSP/I2C.o.d 
	@${RM} ${OBJECTDIR}/BSP/I2C.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  BSP/I2C.c  -o ${OBJECTDIR}/BSP/I2C.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/BSP/I2C.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -D__PIC24F__ -legacy-libc -I"BSP" -I"User" -O0 -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/BSP/I2C.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/BSP/Sleep.o: BSP/Sleep.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/BSP" 
	@${RM} ${OBJECTDIR}/BSP/Sleep.o.d 
	@${RM} ${OBJECTDIR}/BSP/Sleep.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  BSP/Sleep.c  -o ${OBJECTDIR}/BSP/Sleep.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/BSP/Sleep.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -D__PIC24F__ -legacy-libc -I"BSP" -I"User" -O0 -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/BSP/Sleep.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/BSP/DeepSleep.o: BSP/DeepSleep.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/BSP" 
	@${RM} ${OBJECTDIR}/BSP/DeepSleep.o.d 
	@${RM} ${OBJECTDIR}/BSP/DeepSleep.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  BSP/DeepSleep.c  -o ${OBJECTDIR}/BSP/DeepSleep.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/BSP/DeepSleep.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -D__PIC24F__ -legacy-libc -I"BSP" -I"User" -O0 -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/BSP/DeepSleep.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/BSP/RTCC.o: BSP/RTCC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/BSP" 
	@${RM} ${OBJECTDIR}/BSP/RTCC.o.d 
	@${RM} ${OBJECTDIR}/BSP/RTCC.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  BSP/RTCC.c  -o ${OBJECTDIR}/BSP/RTCC.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/BSP/RTCC.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -D__PIC24F__ -legacy-libc -I"BSP" -I"User" -O0 -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/BSP/RTCC.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/BSP/LCD.o: BSP/LCD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/BSP" 
	@${RM} ${OBJECTDIR}/BSP/LCD.o.d 
	@${RM} ${OBJECTDIR}/BSP/LCD.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  BSP/LCD.c  -o ${OBJECTDIR}/BSP/LCD.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/BSP/LCD.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -D__PIC24F__ -legacy-libc -I"BSP" -I"User" -O0 -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/BSP/LCD.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/BSP/TIM.o: BSP/TIM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/BSP" 
	@${RM} ${OBJECTDIR}/BSP/TIM.o.d 
	@${RM} ${OBJECTDIR}/BSP/TIM.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  BSP/TIM.c  -o ${OBJECTDIR}/BSP/TIM.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/BSP/TIM.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -D__PIC24F__ -legacy-libc -I"BSP" -I"User" -O0 -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/BSP/TIM.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/BSP/CRC16.o: BSP/CRC16.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/BSP" 
	@${RM} ${OBJECTDIR}/BSP/CRC16.o.d 
	@${RM} ${OBJECTDIR}/BSP/CRC16.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  BSP/CRC16.c  -o ${OBJECTDIR}/BSP/CRC16.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/BSP/CRC16.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -D__PIC24F__ -legacy-libc -I"BSP" -I"User" -O0 -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/BSP/CRC16.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/User/HL6528.o: User/HL6528.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/User" 
	@${RM} ${OBJECTDIR}/User/HL6528.o.d 
	@${RM} ${OBJECTDIR}/User/HL6528.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  User/HL6528.c  -o ${OBJECTDIR}/User/HL6528.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/User/HL6528.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -D__PIC24F__ -legacy-libc -I"BSP" -I"User" -O0 -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/User/HL6528.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/User/SerialBuffer.o: User/SerialBuffer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/User" 
	@${RM} ${OBJECTDIR}/User/SerialBuffer.o.d 
	@${RM} ${OBJECTDIR}/User/SerialBuffer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  User/SerialBuffer.c  -o ${OBJECTDIR}/User/SerialBuffer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/User/SerialBuffer.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -D__PIC24F__ -legacy-libc -I"BSP" -I"User" -O0 -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/User/SerialBuffer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/User/Common.o: User/Common.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/User" 
	@${RM} ${OBJECTDIR}/User/Common.o.d 
	@${RM} ${OBJECTDIR}/User/Common.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  User/Common.c  -o ${OBJECTDIR}/User/Common.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/User/Common.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -D__PIC24F__ -legacy-libc -I"BSP" -I"User" -O0 -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/User/Common.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/User/main.o: User/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/User" 
	@${RM} ${OBJECTDIR}/User/main.o.d 
	@${RM} ${OBJECTDIR}/User/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  User/main.c  -o ${OBJECTDIR}/User/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/User/main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -D__PIC24F__ -legacy-libc -I"BSP" -I"User" -O0 -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/User/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/User/E41.o: User/E41.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/User" 
	@${RM} ${OBJECTDIR}/User/E41.o.d 
	@${RM} ${OBJECTDIR}/User/E41.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  User/E41.c  -o ${OBJECTDIR}/User/E41.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/User/E41.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -D__PIC24F__ -legacy-libc -I"BSP" -I"User" -O0 -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/User/E41.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/User/CheckData.o: User/CheckData.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/User" 
	@${RM} ${OBJECTDIR}/User/CheckData.o.d 
	@${RM} ${OBJECTDIR}/User/CheckData.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  User/CheckData.c  -o ${OBJECTDIR}/User/CheckData.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/User/CheckData.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -D__PIC24F__ -legacy-libc -I"BSP" -I"User" -O0 -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/User/CheckData.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/User/CAT24C512.o: User/CAT24C512.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/User" 
	@${RM} ${OBJECTDIR}/User/CAT24C512.o.d 
	@${RM} ${OBJECTDIR}/User/CAT24C512.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  User/CAT24C512.c  -o ${OBJECTDIR}/User/CAT24C512.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/User/CAT24C512.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -D__PIC24F__ -legacy-libc -I"BSP" -I"User" -O0 -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/User/CAT24C512.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/User/WGC.o: User/WGC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/User" 
	@${RM} ${OBJECTDIR}/User/WGC.o.d 
	@${RM} ${OBJECTDIR}/User/WGC.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  User/WGC.c  -o ${OBJECTDIR}/User/WGC.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/User/WGC.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -D__PIC24F__ -legacy-libc -I"BSP" -I"User" -O0 -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/User/WGC.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/BSP/bsp.o: BSP/bsp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/BSP" 
	@${RM} ${OBJECTDIR}/BSP/bsp.o.d 
	@${RM} ${OBJECTDIR}/BSP/bsp.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  BSP/bsp.c  -o ${OBJECTDIR}/BSP/bsp.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/BSP/bsp.o.d"      -mno-eds-warn  -g -omf=elf -D__PIC24F__ -legacy-libc -I"BSP" -I"User" -O0 -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/BSP/bsp.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/BSP/NVIC.o: BSP/NVIC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/BSP" 
	@${RM} ${OBJECTDIR}/BSP/NVIC.o.d 
	@${RM} ${OBJECTDIR}/BSP/NVIC.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  BSP/NVIC.c  -o ${OBJECTDIR}/BSP/NVIC.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/BSP/NVIC.o.d"      -mno-eds-warn  -g -omf=elf -D__PIC24F__ -legacy-libc -I"BSP" -I"User" -O0 -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/BSP/NVIC.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/BSP/RS485.o: BSP/RS485.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/BSP" 
	@${RM} ${OBJECTDIR}/BSP/RS485.o.d 
	@${RM} ${OBJECTDIR}/BSP/RS485.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  BSP/RS485.c  -o ${OBJECTDIR}/BSP/RS485.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/BSP/RS485.o.d"      -mno-eds-warn  -g -omf=elf -D__PIC24F__ -legacy-libc -I"BSP" -I"User" -O0 -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/BSP/RS485.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/BSP/PPS.o: BSP/PPS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/BSP" 
	@${RM} ${OBJECTDIR}/BSP/PPS.o.d 
	@${RM} ${OBJECTDIR}/BSP/PPS.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  BSP/PPS.c  -o ${OBJECTDIR}/BSP/PPS.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/BSP/PPS.o.d"      -mno-eds-warn  -g -omf=elf -D__PIC24F__ -legacy-libc -I"BSP" -I"User" -O0 -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/BSP/PPS.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/BSP/UART2.o: BSP/UART2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/BSP" 
	@${RM} ${OBJECTDIR}/BSP/UART2.o.d 
	@${RM} ${OBJECTDIR}/BSP/UART2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  BSP/UART2.c  -o ${OBJECTDIR}/BSP/UART2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/BSP/UART2.o.d"      -mno-eds-warn  -g -omf=elf -D__PIC24F__ -legacy-libc -I"BSP" -I"User" -O0 -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/BSP/UART2.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/BSP/UART3.o: BSP/UART3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/BSP" 
	@${RM} ${OBJECTDIR}/BSP/UART3.o.d 
	@${RM} ${OBJECTDIR}/BSP/UART3.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  BSP/UART3.c  -o ${OBJECTDIR}/BSP/UART3.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/BSP/UART3.o.d"      -mno-eds-warn  -g -omf=elf -D__PIC24F__ -legacy-libc -I"BSP" -I"User" -O0 -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/BSP/UART3.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/BSP/INT.o: BSP/INT.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/BSP" 
	@${RM} ${OBJECTDIR}/BSP/INT.o.d 
	@${RM} ${OBJECTDIR}/BSP/INT.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  BSP/INT.c  -o ${OBJECTDIR}/BSP/INT.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/BSP/INT.o.d"      -mno-eds-warn  -g -omf=elf -D__PIC24F__ -legacy-libc -I"BSP" -I"User" -O0 -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/BSP/INT.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/BSP/I2C.o: BSP/I2C.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/BSP" 
	@${RM} ${OBJECTDIR}/BSP/I2C.o.d 
	@${RM} ${OBJECTDIR}/BSP/I2C.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  BSP/I2C.c  -o ${OBJECTDIR}/BSP/I2C.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/BSP/I2C.o.d"      -mno-eds-warn  -g -omf=elf -D__PIC24F__ -legacy-libc -I"BSP" -I"User" -O0 -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/BSP/I2C.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/BSP/Sleep.o: BSP/Sleep.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/BSP" 
	@${RM} ${OBJECTDIR}/BSP/Sleep.o.d 
	@${RM} ${OBJECTDIR}/BSP/Sleep.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  BSP/Sleep.c  -o ${OBJECTDIR}/BSP/Sleep.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/BSP/Sleep.o.d"      -mno-eds-warn  -g -omf=elf -D__PIC24F__ -legacy-libc -I"BSP" -I"User" -O0 -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/BSP/Sleep.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/BSP/DeepSleep.o: BSP/DeepSleep.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/BSP" 
	@${RM} ${OBJECTDIR}/BSP/DeepSleep.o.d 
	@${RM} ${OBJECTDIR}/BSP/DeepSleep.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  BSP/DeepSleep.c  -o ${OBJECTDIR}/BSP/DeepSleep.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/BSP/DeepSleep.o.d"      -mno-eds-warn  -g -omf=elf -D__PIC24F__ -legacy-libc -I"BSP" -I"User" -O0 -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/BSP/DeepSleep.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/BSP/RTCC.o: BSP/RTCC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/BSP" 
	@${RM} ${OBJECTDIR}/BSP/RTCC.o.d 
	@${RM} ${OBJECTDIR}/BSP/RTCC.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  BSP/RTCC.c  -o ${OBJECTDIR}/BSP/RTCC.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/BSP/RTCC.o.d"      -mno-eds-warn  -g -omf=elf -D__PIC24F__ -legacy-libc -I"BSP" -I"User" -O0 -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/BSP/RTCC.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/BSP/LCD.o: BSP/LCD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/BSP" 
	@${RM} ${OBJECTDIR}/BSP/LCD.o.d 
	@${RM} ${OBJECTDIR}/BSP/LCD.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  BSP/LCD.c  -o ${OBJECTDIR}/BSP/LCD.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/BSP/LCD.o.d"      -mno-eds-warn  -g -omf=elf -D__PIC24F__ -legacy-libc -I"BSP" -I"User" -O0 -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/BSP/LCD.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/BSP/TIM.o: BSP/TIM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/BSP" 
	@${RM} ${OBJECTDIR}/BSP/TIM.o.d 
	@${RM} ${OBJECTDIR}/BSP/TIM.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  BSP/TIM.c  -o ${OBJECTDIR}/BSP/TIM.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/BSP/TIM.o.d"      -mno-eds-warn  -g -omf=elf -D__PIC24F__ -legacy-libc -I"BSP" -I"User" -O0 -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/BSP/TIM.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/BSP/CRC16.o: BSP/CRC16.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/BSP" 
	@${RM} ${OBJECTDIR}/BSP/CRC16.o.d 
	@${RM} ${OBJECTDIR}/BSP/CRC16.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  BSP/CRC16.c  -o ${OBJECTDIR}/BSP/CRC16.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/BSP/CRC16.o.d"      -mno-eds-warn  -g -omf=elf -D__PIC24F__ -legacy-libc -I"BSP" -I"User" -O0 -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/BSP/CRC16.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/User/HL6528.o: User/HL6528.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/User" 
	@${RM} ${OBJECTDIR}/User/HL6528.o.d 
	@${RM} ${OBJECTDIR}/User/HL6528.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  User/HL6528.c  -o ${OBJECTDIR}/User/HL6528.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/User/HL6528.o.d"      -mno-eds-warn  -g -omf=elf -D__PIC24F__ -legacy-libc -I"BSP" -I"User" -O0 -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/User/HL6528.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/User/SerialBuffer.o: User/SerialBuffer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/User" 
	@${RM} ${OBJECTDIR}/User/SerialBuffer.o.d 
	@${RM} ${OBJECTDIR}/User/SerialBuffer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  User/SerialBuffer.c  -o ${OBJECTDIR}/User/SerialBuffer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/User/SerialBuffer.o.d"      -mno-eds-warn  -g -omf=elf -D__PIC24F__ -legacy-libc -I"BSP" -I"User" -O0 -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/User/SerialBuffer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/User/Common.o: User/Common.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/User" 
	@${RM} ${OBJECTDIR}/User/Common.o.d 
	@${RM} ${OBJECTDIR}/User/Common.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  User/Common.c  -o ${OBJECTDIR}/User/Common.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/User/Common.o.d"      -mno-eds-warn  -g -omf=elf -D__PIC24F__ -legacy-libc -I"BSP" -I"User" -O0 -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/User/Common.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/User/main.o: User/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/User" 
	@${RM} ${OBJECTDIR}/User/main.o.d 
	@${RM} ${OBJECTDIR}/User/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  User/main.c  -o ${OBJECTDIR}/User/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/User/main.o.d"      -mno-eds-warn  -g -omf=elf -D__PIC24F__ -legacy-libc -I"BSP" -I"User" -O0 -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/User/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/User/E41.o: User/E41.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/User" 
	@${RM} ${OBJECTDIR}/User/E41.o.d 
	@${RM} ${OBJECTDIR}/User/E41.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  User/E41.c  -o ${OBJECTDIR}/User/E41.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/User/E41.o.d"      -mno-eds-warn  -g -omf=elf -D__PIC24F__ -legacy-libc -I"BSP" -I"User" -O0 -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/User/E41.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/User/CheckData.o: User/CheckData.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/User" 
	@${RM} ${OBJECTDIR}/User/CheckData.o.d 
	@${RM} ${OBJECTDIR}/User/CheckData.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  User/CheckData.c  -o ${OBJECTDIR}/User/CheckData.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/User/CheckData.o.d"      -mno-eds-warn  -g -omf=elf -D__PIC24F__ -legacy-libc -I"BSP" -I"User" -O0 -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/User/CheckData.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/User/CAT24C512.o: User/CAT24C512.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/User" 
	@${RM} ${OBJECTDIR}/User/CAT24C512.o.d 
	@${RM} ${OBJECTDIR}/User/CAT24C512.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  User/CAT24C512.c  -o ${OBJECTDIR}/User/CAT24C512.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/User/CAT24C512.o.d"      -mno-eds-warn  -g -omf=elf -D__PIC24F__ -legacy-libc -I"BSP" -I"User" -O0 -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/User/CAT24C512.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/User/WGC.o: User/WGC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/User" 
	@${RM} ${OBJECTDIR}/User/WGC.o.d 
	@${RM} ${OBJECTDIR}/User/WGC.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  User/WGC.c  -o ${OBJECTDIR}/User/WGC.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/User/WGC.o.d"      -mno-eds-warn  -g -omf=elf -D__PIC24F__ -legacy-libc -I"BSP" -I"User" -O0 -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/User/WGC.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/TRPV1.0.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    p24FJ64GA306.gld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/TRPV1.0.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -D__PIC24F__ -legacy-libc -I"BSP" -I"User"  -mreserve=data@0x800:0x81B -mreserve=data@0x81C:0x81D -mreserve=data@0x81E:0x81F -mreserve=data@0x820:0x821 -mreserve=data@0x822:0x823 -mreserve=data@0x824:0x827 -mreserve=data@0x82A:0x84F   -Wl,--local-stack,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,$(MP_LINKER_FILE_OPTION),--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST) 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/TRPV1.0.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   p24FJ64GA306.gld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/TRPV1.0.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -D__PIC24F__ -legacy-libc -I"BSP" -I"User" -Wl,--local-stack,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST) 
	${MP_CC_DIR}\\xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/TRPV1.0.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf  
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
