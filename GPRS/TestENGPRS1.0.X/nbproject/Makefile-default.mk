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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/TestENGPRS1.0.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/TestENGPRS1.0.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=main.c 25L64B.c DeepSleep.c ICN.c RS485.c NVIC.c RTCC.c TIM.c UART.c ADC.c INT.c Common.c CheckData.c SerialBuffer.c GPRS.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/main.o ${OBJECTDIR}/25L64B.o ${OBJECTDIR}/DeepSleep.o ${OBJECTDIR}/ICN.o ${OBJECTDIR}/RS485.o ${OBJECTDIR}/NVIC.o ${OBJECTDIR}/RTCC.o ${OBJECTDIR}/TIM.o ${OBJECTDIR}/UART.o ${OBJECTDIR}/ADC.o ${OBJECTDIR}/INT.o ${OBJECTDIR}/Common.o ${OBJECTDIR}/CheckData.o ${OBJECTDIR}/SerialBuffer.o ${OBJECTDIR}/GPRS.o
POSSIBLE_DEPFILES=${OBJECTDIR}/main.o.d ${OBJECTDIR}/25L64B.o.d ${OBJECTDIR}/DeepSleep.o.d ${OBJECTDIR}/ICN.o.d ${OBJECTDIR}/RS485.o.d ${OBJECTDIR}/NVIC.o.d ${OBJECTDIR}/RTCC.o.d ${OBJECTDIR}/TIM.o.d ${OBJECTDIR}/UART.o.d ${OBJECTDIR}/ADC.o.d ${OBJECTDIR}/INT.o.d ${OBJECTDIR}/Common.o.d ${OBJECTDIR}/CheckData.o.d ${OBJECTDIR}/SerialBuffer.o.d ${OBJECTDIR}/GPRS.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/main.o ${OBJECTDIR}/25L64B.o ${OBJECTDIR}/DeepSleep.o ${OBJECTDIR}/ICN.o ${OBJECTDIR}/RS485.o ${OBJECTDIR}/NVIC.o ${OBJECTDIR}/RTCC.o ${OBJECTDIR}/TIM.o ${OBJECTDIR}/UART.o ${OBJECTDIR}/ADC.o ${OBJECTDIR}/INT.o ${OBJECTDIR}/Common.o ${OBJECTDIR}/CheckData.o ${OBJECTDIR}/SerialBuffer.o ${OBJECTDIR}/GPRS.o

# Source Files
SOURCEFILES=main.c 25L64B.c DeepSleep.c ICN.c RS485.c NVIC.c RTCC.c TIM.c UART.c ADC.c INT.c Common.c CheckData.c SerialBuffer.c GPRS.c


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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/TestENGPRS1.0.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=24FV32KA302
MP_LINKER_FILE_OPTION=,-Tp24FV32KA302.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o.ok ${OBJECTDIR}/main.o.err 
	@${RM} ${OBJECTDIR}/main.o 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Os -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c    
	
${OBJECTDIR}/25L64B.o: 25L64B.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/25L64B.o.d 
	@${RM} ${OBJECTDIR}/25L64B.o.ok ${OBJECTDIR}/25L64B.o.err 
	@${RM} ${OBJECTDIR}/25L64B.o 
	@${FIXDEPS} "${OBJECTDIR}/25L64B.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Os -MMD -MF "${OBJECTDIR}/25L64B.o.d" -o ${OBJECTDIR}/25L64B.o 25L64B.c    
	
${OBJECTDIR}/DeepSleep.o: DeepSleep.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/DeepSleep.o.d 
	@${RM} ${OBJECTDIR}/DeepSleep.o.ok ${OBJECTDIR}/DeepSleep.o.err 
	@${RM} ${OBJECTDIR}/DeepSleep.o 
	@${FIXDEPS} "${OBJECTDIR}/DeepSleep.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Os -MMD -MF "${OBJECTDIR}/DeepSleep.o.d" -o ${OBJECTDIR}/DeepSleep.o DeepSleep.c    
	
${OBJECTDIR}/ICN.o: ICN.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ICN.o.d 
	@${RM} ${OBJECTDIR}/ICN.o.ok ${OBJECTDIR}/ICN.o.err 
	@${RM} ${OBJECTDIR}/ICN.o 
	@${FIXDEPS} "${OBJECTDIR}/ICN.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Os -MMD -MF "${OBJECTDIR}/ICN.o.d" -o ${OBJECTDIR}/ICN.o ICN.c    
	
${OBJECTDIR}/RS485.o: RS485.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/RS485.o.d 
	@${RM} ${OBJECTDIR}/RS485.o.ok ${OBJECTDIR}/RS485.o.err 
	@${RM} ${OBJECTDIR}/RS485.o 
	@${FIXDEPS} "${OBJECTDIR}/RS485.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Os -MMD -MF "${OBJECTDIR}/RS485.o.d" -o ${OBJECTDIR}/RS485.o RS485.c    
	
${OBJECTDIR}/NVIC.o: NVIC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/NVIC.o.d 
	@${RM} ${OBJECTDIR}/NVIC.o.ok ${OBJECTDIR}/NVIC.o.err 
	@${RM} ${OBJECTDIR}/NVIC.o 
	@${FIXDEPS} "${OBJECTDIR}/NVIC.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Os -MMD -MF "${OBJECTDIR}/NVIC.o.d" -o ${OBJECTDIR}/NVIC.o NVIC.c    
	
${OBJECTDIR}/RTCC.o: RTCC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/RTCC.o.d 
	@${RM} ${OBJECTDIR}/RTCC.o.ok ${OBJECTDIR}/RTCC.o.err 
	@${RM} ${OBJECTDIR}/RTCC.o 
	@${FIXDEPS} "${OBJECTDIR}/RTCC.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Os -MMD -MF "${OBJECTDIR}/RTCC.o.d" -o ${OBJECTDIR}/RTCC.o RTCC.c    
	
${OBJECTDIR}/TIM.o: TIM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/TIM.o.d 
	@${RM} ${OBJECTDIR}/TIM.o.ok ${OBJECTDIR}/TIM.o.err 
	@${RM} ${OBJECTDIR}/TIM.o 
	@${FIXDEPS} "${OBJECTDIR}/TIM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Os -MMD -MF "${OBJECTDIR}/TIM.o.d" -o ${OBJECTDIR}/TIM.o TIM.c    
	
${OBJECTDIR}/UART.o: UART.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/UART.o.d 
	@${RM} ${OBJECTDIR}/UART.o.ok ${OBJECTDIR}/UART.o.err 
	@${RM} ${OBJECTDIR}/UART.o 
	@${FIXDEPS} "${OBJECTDIR}/UART.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Os -MMD -MF "${OBJECTDIR}/UART.o.d" -o ${OBJECTDIR}/UART.o UART.c    
	
${OBJECTDIR}/ADC.o: ADC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ADC.o.d 
	@${RM} ${OBJECTDIR}/ADC.o.ok ${OBJECTDIR}/ADC.o.err 
	@${RM} ${OBJECTDIR}/ADC.o 
	@${FIXDEPS} "${OBJECTDIR}/ADC.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Os -MMD -MF "${OBJECTDIR}/ADC.o.d" -o ${OBJECTDIR}/ADC.o ADC.c    
	
${OBJECTDIR}/INT.o: INT.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/INT.o.d 
	@${RM} ${OBJECTDIR}/INT.o.ok ${OBJECTDIR}/INT.o.err 
	@${RM} ${OBJECTDIR}/INT.o 
	@${FIXDEPS} "${OBJECTDIR}/INT.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Os -MMD -MF "${OBJECTDIR}/INT.o.d" -o ${OBJECTDIR}/INT.o INT.c    
	
${OBJECTDIR}/Common.o: Common.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Common.o.d 
	@${RM} ${OBJECTDIR}/Common.o.ok ${OBJECTDIR}/Common.o.err 
	@${RM} ${OBJECTDIR}/Common.o 
	@${FIXDEPS} "${OBJECTDIR}/Common.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Os -MMD -MF "${OBJECTDIR}/Common.o.d" -o ${OBJECTDIR}/Common.o Common.c    
	
${OBJECTDIR}/CheckData.o: CheckData.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CheckData.o.d 
	@${RM} ${OBJECTDIR}/CheckData.o.ok ${OBJECTDIR}/CheckData.o.err 
	@${RM} ${OBJECTDIR}/CheckData.o 
	@${FIXDEPS} "${OBJECTDIR}/CheckData.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Os -MMD -MF "${OBJECTDIR}/CheckData.o.d" -o ${OBJECTDIR}/CheckData.o CheckData.c    
	
${OBJECTDIR}/SerialBuffer.o: SerialBuffer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/SerialBuffer.o.d 
	@${RM} ${OBJECTDIR}/SerialBuffer.o.ok ${OBJECTDIR}/SerialBuffer.o.err 
	@${RM} ${OBJECTDIR}/SerialBuffer.o 
	@${FIXDEPS} "${OBJECTDIR}/SerialBuffer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Os -MMD -MF "${OBJECTDIR}/SerialBuffer.o.d" -o ${OBJECTDIR}/SerialBuffer.o SerialBuffer.c    
	
${OBJECTDIR}/GPRS.o: GPRS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/GPRS.o.d 
	@${RM} ${OBJECTDIR}/GPRS.o.ok ${OBJECTDIR}/GPRS.o.err 
	@${RM} ${OBJECTDIR}/GPRS.o 
	@${FIXDEPS} "${OBJECTDIR}/GPRS.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Os -MMD -MF "${OBJECTDIR}/GPRS.o.d" -o ${OBJECTDIR}/GPRS.o GPRS.c    
	
else
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o.ok ${OBJECTDIR}/main.o.err 
	@${RM} ${OBJECTDIR}/main.o 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Os -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c    
	
${OBJECTDIR}/25L64B.o: 25L64B.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/25L64B.o.d 
	@${RM} ${OBJECTDIR}/25L64B.o.ok ${OBJECTDIR}/25L64B.o.err 
	@${RM} ${OBJECTDIR}/25L64B.o 
	@${FIXDEPS} "${OBJECTDIR}/25L64B.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Os -MMD -MF "${OBJECTDIR}/25L64B.o.d" -o ${OBJECTDIR}/25L64B.o 25L64B.c    
	
${OBJECTDIR}/DeepSleep.o: DeepSleep.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/DeepSleep.o.d 
	@${RM} ${OBJECTDIR}/DeepSleep.o.ok ${OBJECTDIR}/DeepSleep.o.err 
	@${RM} ${OBJECTDIR}/DeepSleep.o 
	@${FIXDEPS} "${OBJECTDIR}/DeepSleep.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Os -MMD -MF "${OBJECTDIR}/DeepSleep.o.d" -o ${OBJECTDIR}/DeepSleep.o DeepSleep.c    
	
${OBJECTDIR}/ICN.o: ICN.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ICN.o.d 
	@${RM} ${OBJECTDIR}/ICN.o.ok ${OBJECTDIR}/ICN.o.err 
	@${RM} ${OBJECTDIR}/ICN.o 
	@${FIXDEPS} "${OBJECTDIR}/ICN.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Os -MMD -MF "${OBJECTDIR}/ICN.o.d" -o ${OBJECTDIR}/ICN.o ICN.c    
	
${OBJECTDIR}/RS485.o: RS485.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/RS485.o.d 
	@${RM} ${OBJECTDIR}/RS485.o.ok ${OBJECTDIR}/RS485.o.err 
	@${RM} ${OBJECTDIR}/RS485.o 
	@${FIXDEPS} "${OBJECTDIR}/RS485.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Os -MMD -MF "${OBJECTDIR}/RS485.o.d" -o ${OBJECTDIR}/RS485.o RS485.c    
	
${OBJECTDIR}/NVIC.o: NVIC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/NVIC.o.d 
	@${RM} ${OBJECTDIR}/NVIC.o.ok ${OBJECTDIR}/NVIC.o.err 
	@${RM} ${OBJECTDIR}/NVIC.o 
	@${FIXDEPS} "${OBJECTDIR}/NVIC.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Os -MMD -MF "${OBJECTDIR}/NVIC.o.d" -o ${OBJECTDIR}/NVIC.o NVIC.c    
	
${OBJECTDIR}/RTCC.o: RTCC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/RTCC.o.d 
	@${RM} ${OBJECTDIR}/RTCC.o.ok ${OBJECTDIR}/RTCC.o.err 
	@${RM} ${OBJECTDIR}/RTCC.o 
	@${FIXDEPS} "${OBJECTDIR}/RTCC.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Os -MMD -MF "${OBJECTDIR}/RTCC.o.d" -o ${OBJECTDIR}/RTCC.o RTCC.c    
	
${OBJECTDIR}/TIM.o: TIM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/TIM.o.d 
	@${RM} ${OBJECTDIR}/TIM.o.ok ${OBJECTDIR}/TIM.o.err 
	@${RM} ${OBJECTDIR}/TIM.o 
	@${FIXDEPS} "${OBJECTDIR}/TIM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Os -MMD -MF "${OBJECTDIR}/TIM.o.d" -o ${OBJECTDIR}/TIM.o TIM.c    
	
${OBJECTDIR}/UART.o: UART.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/UART.o.d 
	@${RM} ${OBJECTDIR}/UART.o.ok ${OBJECTDIR}/UART.o.err 
	@${RM} ${OBJECTDIR}/UART.o 
	@${FIXDEPS} "${OBJECTDIR}/UART.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Os -MMD -MF "${OBJECTDIR}/UART.o.d" -o ${OBJECTDIR}/UART.o UART.c    
	
${OBJECTDIR}/ADC.o: ADC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ADC.o.d 
	@${RM} ${OBJECTDIR}/ADC.o.ok ${OBJECTDIR}/ADC.o.err 
	@${RM} ${OBJECTDIR}/ADC.o 
	@${FIXDEPS} "${OBJECTDIR}/ADC.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Os -MMD -MF "${OBJECTDIR}/ADC.o.d" -o ${OBJECTDIR}/ADC.o ADC.c    
	
${OBJECTDIR}/INT.o: INT.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/INT.o.d 
	@${RM} ${OBJECTDIR}/INT.o.ok ${OBJECTDIR}/INT.o.err 
	@${RM} ${OBJECTDIR}/INT.o 
	@${FIXDEPS} "${OBJECTDIR}/INT.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Os -MMD -MF "${OBJECTDIR}/INT.o.d" -o ${OBJECTDIR}/INT.o INT.c    
	
${OBJECTDIR}/Common.o: Common.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Common.o.d 
	@${RM} ${OBJECTDIR}/Common.o.ok ${OBJECTDIR}/Common.o.err 
	@${RM} ${OBJECTDIR}/Common.o 
	@${FIXDEPS} "${OBJECTDIR}/Common.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Os -MMD -MF "${OBJECTDIR}/Common.o.d" -o ${OBJECTDIR}/Common.o Common.c    
	
${OBJECTDIR}/CheckData.o: CheckData.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CheckData.o.d 
	@${RM} ${OBJECTDIR}/CheckData.o.ok ${OBJECTDIR}/CheckData.o.err 
	@${RM} ${OBJECTDIR}/CheckData.o 
	@${FIXDEPS} "${OBJECTDIR}/CheckData.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Os -MMD -MF "${OBJECTDIR}/CheckData.o.d" -o ${OBJECTDIR}/CheckData.o CheckData.c    
	
${OBJECTDIR}/SerialBuffer.o: SerialBuffer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/SerialBuffer.o.d 
	@${RM} ${OBJECTDIR}/SerialBuffer.o.ok ${OBJECTDIR}/SerialBuffer.o.err 
	@${RM} ${OBJECTDIR}/SerialBuffer.o 
	@${FIXDEPS} "${OBJECTDIR}/SerialBuffer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Os -MMD -MF "${OBJECTDIR}/SerialBuffer.o.d" -o ${OBJECTDIR}/SerialBuffer.o SerialBuffer.c    
	
${OBJECTDIR}/GPRS.o: GPRS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/GPRS.o.d 
	@${RM} ${OBJECTDIR}/GPRS.o.ok ${OBJECTDIR}/GPRS.o.err 
	@${RM} ${OBJECTDIR}/GPRS.o 
	@${FIXDEPS} "${OBJECTDIR}/GPRS.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Os -MMD -MF "${OBJECTDIR}/GPRS.o.d" -o ${OBJECTDIR}/GPRS.o GPRS.c    
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/TestENGPRS1.0.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -omf=elf -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -o dist/${CND_CONF}/${IMAGE_TYPE}/TestENGPRS1.0.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}         -Wl,--defsym=__MPLAB_BUILD=1,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1
else
dist/${CND_CONF}/${IMAGE_TYPE}/TestENGPRS1.0.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -omf=elf -mcpu=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/TestENGPRS1.0.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}         -Wl,--defsym=__MPLAB_BUILD=1,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION)
	${MP_CC_DIR}\\pic30-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/TestENGPRS1.0.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -omf=elf
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
