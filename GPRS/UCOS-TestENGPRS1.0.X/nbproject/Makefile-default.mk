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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/UCOS-TestENGPRS1.0.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/UCOS-TestENGPRS1.0.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=App/app.c bsp/ADC.c bsp/IC.c bsp/ICN.c bsp/INT.c bsp/NVIC.c bsp/RS485.c bsp/RTCC.c bsp/SPI.c bsp/TIM.c bsp/bsp.c uC-CPU/cpu_bsp.c uC-CPU/cpu_core.c uCOS-II/Ports/os_cpu_c.c uCOS-II/Ports/os_cpu_a.s uCOS-II/Source/os_core.c uCOS-II/Source/os_flag.c uCOS-II/Source/os_mbox.c uCOS-II/Source/os_multi.c uCOS-II/Source/os_mutex.c uCOS-II/Source/os_q.c uCOS-II/Source/os_sem.c uCOS-II/Source/os_task.c uCOS-II/Source/os_time.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/App/app.o ${OBJECTDIR}/bsp/ADC.o ${OBJECTDIR}/bsp/IC.o ${OBJECTDIR}/bsp/ICN.o ${OBJECTDIR}/bsp/INT.o ${OBJECTDIR}/bsp/NVIC.o ${OBJECTDIR}/bsp/RS485.o ${OBJECTDIR}/bsp/RTCC.o ${OBJECTDIR}/bsp/SPI.o ${OBJECTDIR}/bsp/TIM.o ${OBJECTDIR}/bsp/bsp.o ${OBJECTDIR}/uC-CPU/cpu_bsp.o ${OBJECTDIR}/uC-CPU/cpu_core.o ${OBJECTDIR}/uCOS-II/Ports/os_cpu_c.o ${OBJECTDIR}/uCOS-II/Ports/os_cpu_a.o ${OBJECTDIR}/uCOS-II/Source/os_core.o ${OBJECTDIR}/uCOS-II/Source/os_flag.o ${OBJECTDIR}/uCOS-II/Source/os_mbox.o ${OBJECTDIR}/uCOS-II/Source/os_multi.o ${OBJECTDIR}/uCOS-II/Source/os_mutex.o ${OBJECTDIR}/uCOS-II/Source/os_q.o ${OBJECTDIR}/uCOS-II/Source/os_sem.o ${OBJECTDIR}/uCOS-II/Source/os_task.o ${OBJECTDIR}/uCOS-II/Source/os_time.o
POSSIBLE_DEPFILES=${OBJECTDIR}/App/app.o.d ${OBJECTDIR}/bsp/ADC.o.d ${OBJECTDIR}/bsp/IC.o.d ${OBJECTDIR}/bsp/ICN.o.d ${OBJECTDIR}/bsp/INT.o.d ${OBJECTDIR}/bsp/NVIC.o.d ${OBJECTDIR}/bsp/RS485.o.d ${OBJECTDIR}/bsp/RTCC.o.d ${OBJECTDIR}/bsp/SPI.o.d ${OBJECTDIR}/bsp/TIM.o.d ${OBJECTDIR}/bsp/bsp.o.d ${OBJECTDIR}/uC-CPU/cpu_bsp.o.d ${OBJECTDIR}/uC-CPU/cpu_core.o.d ${OBJECTDIR}/uCOS-II/Ports/os_cpu_c.o.d ${OBJECTDIR}/uCOS-II/Ports/os_cpu_a.o.d ${OBJECTDIR}/uCOS-II/Source/os_core.o.d ${OBJECTDIR}/uCOS-II/Source/os_flag.o.d ${OBJECTDIR}/uCOS-II/Source/os_mbox.o.d ${OBJECTDIR}/uCOS-II/Source/os_multi.o.d ${OBJECTDIR}/uCOS-II/Source/os_mutex.o.d ${OBJECTDIR}/uCOS-II/Source/os_q.o.d ${OBJECTDIR}/uCOS-II/Source/os_sem.o.d ${OBJECTDIR}/uCOS-II/Source/os_task.o.d ${OBJECTDIR}/uCOS-II/Source/os_time.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/App/app.o ${OBJECTDIR}/bsp/ADC.o ${OBJECTDIR}/bsp/IC.o ${OBJECTDIR}/bsp/ICN.o ${OBJECTDIR}/bsp/INT.o ${OBJECTDIR}/bsp/NVIC.o ${OBJECTDIR}/bsp/RS485.o ${OBJECTDIR}/bsp/RTCC.o ${OBJECTDIR}/bsp/SPI.o ${OBJECTDIR}/bsp/TIM.o ${OBJECTDIR}/bsp/bsp.o ${OBJECTDIR}/uC-CPU/cpu_bsp.o ${OBJECTDIR}/uC-CPU/cpu_core.o ${OBJECTDIR}/uCOS-II/Ports/os_cpu_c.o ${OBJECTDIR}/uCOS-II/Ports/os_cpu_a.o ${OBJECTDIR}/uCOS-II/Source/os_core.o ${OBJECTDIR}/uCOS-II/Source/os_flag.o ${OBJECTDIR}/uCOS-II/Source/os_mbox.o ${OBJECTDIR}/uCOS-II/Source/os_multi.o ${OBJECTDIR}/uCOS-II/Source/os_mutex.o ${OBJECTDIR}/uCOS-II/Source/os_q.o ${OBJECTDIR}/uCOS-II/Source/os_sem.o ${OBJECTDIR}/uCOS-II/Source/os_task.o ${OBJECTDIR}/uCOS-II/Source/os_time.o

# Source Files
SOURCEFILES=App/app.c bsp/ADC.c bsp/IC.c bsp/ICN.c bsp/INT.c bsp/NVIC.c bsp/RS485.c bsp/RTCC.c bsp/SPI.c bsp/TIM.c bsp/bsp.c uC-CPU/cpu_bsp.c uC-CPU/cpu_core.c uCOS-II/Ports/os_cpu_c.c uCOS-II/Ports/os_cpu_a.s uCOS-II/Source/os_core.c uCOS-II/Source/os_flag.c uCOS-II/Source/os_mbox.c uCOS-II/Source/os_multi.c uCOS-II/Source/os_mutex.c uCOS-II/Source/os_q.c uCOS-II/Source/os_sem.c uCOS-II/Source/os_task.c uCOS-II/Source/os_time.c


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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/UCOS-TestENGPRS1.0.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=24FV32KA302
MP_LINKER_FILE_OPTION=,--script=p24FV32KA302.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/App/app.o: App/app.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/App" 
	@${RM} ${OBJECTDIR}/App/app.o.d 
	@${RM} ${OBJECTDIR}/App/app.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  App/app.c  -o ${OBJECTDIR}/App/app.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/App/app.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -I"App" -I"bsp" -I"uC-CPU" -I"uC-LIB" -I"uCOS-II/Source" -I"uCOS-II/Ports" -mlarge-code -Os -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/App/app.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/bsp/ADC.o: bsp/ADC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/bsp" 
	@${RM} ${OBJECTDIR}/bsp/ADC.o.d 
	@${RM} ${OBJECTDIR}/bsp/ADC.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  bsp/ADC.c  -o ${OBJECTDIR}/bsp/ADC.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/bsp/ADC.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -I"App" -I"bsp" -I"uC-CPU" -I"uC-LIB" -I"uCOS-II/Source" -I"uCOS-II/Ports" -mlarge-code -Os -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/bsp/ADC.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/bsp/IC.o: bsp/IC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/bsp" 
	@${RM} ${OBJECTDIR}/bsp/IC.o.d 
	@${RM} ${OBJECTDIR}/bsp/IC.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  bsp/IC.c  -o ${OBJECTDIR}/bsp/IC.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/bsp/IC.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -I"App" -I"bsp" -I"uC-CPU" -I"uC-LIB" -I"uCOS-II/Source" -I"uCOS-II/Ports" -mlarge-code -Os -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/bsp/IC.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/bsp/ICN.o: bsp/ICN.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/bsp" 
	@${RM} ${OBJECTDIR}/bsp/ICN.o.d 
	@${RM} ${OBJECTDIR}/bsp/ICN.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  bsp/ICN.c  -o ${OBJECTDIR}/bsp/ICN.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/bsp/ICN.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -I"App" -I"bsp" -I"uC-CPU" -I"uC-LIB" -I"uCOS-II/Source" -I"uCOS-II/Ports" -mlarge-code -Os -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/bsp/ICN.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/bsp/INT.o: bsp/INT.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/bsp" 
	@${RM} ${OBJECTDIR}/bsp/INT.o.d 
	@${RM} ${OBJECTDIR}/bsp/INT.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  bsp/INT.c  -o ${OBJECTDIR}/bsp/INT.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/bsp/INT.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -I"App" -I"bsp" -I"uC-CPU" -I"uC-LIB" -I"uCOS-II/Source" -I"uCOS-II/Ports" -mlarge-code -Os -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/bsp/INT.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/bsp/NVIC.o: bsp/NVIC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/bsp" 
	@${RM} ${OBJECTDIR}/bsp/NVIC.o.d 
	@${RM} ${OBJECTDIR}/bsp/NVIC.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  bsp/NVIC.c  -o ${OBJECTDIR}/bsp/NVIC.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/bsp/NVIC.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -I"App" -I"bsp" -I"uC-CPU" -I"uC-LIB" -I"uCOS-II/Source" -I"uCOS-II/Ports" -mlarge-code -Os -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/bsp/NVIC.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/bsp/RS485.o: bsp/RS485.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/bsp" 
	@${RM} ${OBJECTDIR}/bsp/RS485.o.d 
	@${RM} ${OBJECTDIR}/bsp/RS485.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  bsp/RS485.c  -o ${OBJECTDIR}/bsp/RS485.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/bsp/RS485.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -I"App" -I"bsp" -I"uC-CPU" -I"uC-LIB" -I"uCOS-II/Source" -I"uCOS-II/Ports" -mlarge-code -Os -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/bsp/RS485.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/bsp/RTCC.o: bsp/RTCC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/bsp" 
	@${RM} ${OBJECTDIR}/bsp/RTCC.o.d 
	@${RM} ${OBJECTDIR}/bsp/RTCC.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  bsp/RTCC.c  -o ${OBJECTDIR}/bsp/RTCC.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/bsp/RTCC.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -I"App" -I"bsp" -I"uC-CPU" -I"uC-LIB" -I"uCOS-II/Source" -I"uCOS-II/Ports" -mlarge-code -Os -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/bsp/RTCC.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/bsp/SPI.o: bsp/SPI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/bsp" 
	@${RM} ${OBJECTDIR}/bsp/SPI.o.d 
	@${RM} ${OBJECTDIR}/bsp/SPI.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  bsp/SPI.c  -o ${OBJECTDIR}/bsp/SPI.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/bsp/SPI.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -I"App" -I"bsp" -I"uC-CPU" -I"uC-LIB" -I"uCOS-II/Source" -I"uCOS-II/Ports" -mlarge-code -Os -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/bsp/SPI.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/bsp/TIM.o: bsp/TIM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/bsp" 
	@${RM} ${OBJECTDIR}/bsp/TIM.o.d 
	@${RM} ${OBJECTDIR}/bsp/TIM.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  bsp/TIM.c  -o ${OBJECTDIR}/bsp/TIM.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/bsp/TIM.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -I"App" -I"bsp" -I"uC-CPU" -I"uC-LIB" -I"uCOS-II/Source" -I"uCOS-II/Ports" -mlarge-code -Os -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/bsp/TIM.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/bsp/bsp.o: bsp/bsp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/bsp" 
	@${RM} ${OBJECTDIR}/bsp/bsp.o.d 
	@${RM} ${OBJECTDIR}/bsp/bsp.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  bsp/bsp.c  -o ${OBJECTDIR}/bsp/bsp.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/bsp/bsp.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -I"App" -I"bsp" -I"uC-CPU" -I"uC-LIB" -I"uCOS-II/Source" -I"uCOS-II/Ports" -mlarge-code -Os -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/bsp/bsp.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/uC-CPU/cpu_bsp.o: uC-CPU/cpu_bsp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/uC-CPU" 
	@${RM} ${OBJECTDIR}/uC-CPU/cpu_bsp.o.d 
	@${RM} ${OBJECTDIR}/uC-CPU/cpu_bsp.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  uC-CPU/cpu_bsp.c  -o ${OBJECTDIR}/uC-CPU/cpu_bsp.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/uC-CPU/cpu_bsp.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -I"App" -I"bsp" -I"uC-CPU" -I"uC-LIB" -I"uCOS-II/Source" -I"uCOS-II/Ports" -mlarge-code -Os -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/uC-CPU/cpu_bsp.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/uC-CPU/cpu_core.o: uC-CPU/cpu_core.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/uC-CPU" 
	@${RM} ${OBJECTDIR}/uC-CPU/cpu_core.o.d 
	@${RM} ${OBJECTDIR}/uC-CPU/cpu_core.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  uC-CPU/cpu_core.c  -o ${OBJECTDIR}/uC-CPU/cpu_core.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/uC-CPU/cpu_core.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -I"App" -I"bsp" -I"uC-CPU" -I"uC-LIB" -I"uCOS-II/Source" -I"uCOS-II/Ports" -mlarge-code -Os -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/uC-CPU/cpu_core.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/uCOS-II/Ports/os_cpu_c.o: uCOS-II/Ports/os_cpu_c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/uCOS-II/Ports" 
	@${RM} ${OBJECTDIR}/uCOS-II/Ports/os_cpu_c.o.d 
	@${RM} ${OBJECTDIR}/uCOS-II/Ports/os_cpu_c.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  uCOS-II/Ports/os_cpu_c.c  -o ${OBJECTDIR}/uCOS-II/Ports/os_cpu_c.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/uCOS-II/Ports/os_cpu_c.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -I"App" -I"bsp" -I"uC-CPU" -I"uC-LIB" -I"uCOS-II/Source" -I"uCOS-II/Ports" -mlarge-code -Os -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/uCOS-II/Ports/os_cpu_c.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/uCOS-II/Source/os_core.o: uCOS-II/Source/os_core.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/uCOS-II/Source" 
	@${RM} ${OBJECTDIR}/uCOS-II/Source/os_core.o.d 
	@${RM} ${OBJECTDIR}/uCOS-II/Source/os_core.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  uCOS-II/Source/os_core.c  -o ${OBJECTDIR}/uCOS-II/Source/os_core.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/uCOS-II/Source/os_core.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -I"App" -I"bsp" -I"uC-CPU" -I"uC-LIB" -I"uCOS-II/Source" -I"uCOS-II/Ports" -mlarge-code -Os -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/uCOS-II/Source/os_core.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/uCOS-II/Source/os_flag.o: uCOS-II/Source/os_flag.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/uCOS-II/Source" 
	@${RM} ${OBJECTDIR}/uCOS-II/Source/os_flag.o.d 
	@${RM} ${OBJECTDIR}/uCOS-II/Source/os_flag.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  uCOS-II/Source/os_flag.c  -o ${OBJECTDIR}/uCOS-II/Source/os_flag.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/uCOS-II/Source/os_flag.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -I"App" -I"bsp" -I"uC-CPU" -I"uC-LIB" -I"uCOS-II/Source" -I"uCOS-II/Ports" -mlarge-code -Os -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/uCOS-II/Source/os_flag.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/uCOS-II/Source/os_mbox.o: uCOS-II/Source/os_mbox.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/uCOS-II/Source" 
	@${RM} ${OBJECTDIR}/uCOS-II/Source/os_mbox.o.d 
	@${RM} ${OBJECTDIR}/uCOS-II/Source/os_mbox.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  uCOS-II/Source/os_mbox.c  -o ${OBJECTDIR}/uCOS-II/Source/os_mbox.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/uCOS-II/Source/os_mbox.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -I"App" -I"bsp" -I"uC-CPU" -I"uC-LIB" -I"uCOS-II/Source" -I"uCOS-II/Ports" -mlarge-code -Os -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/uCOS-II/Source/os_mbox.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/uCOS-II/Source/os_multi.o: uCOS-II/Source/os_multi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/uCOS-II/Source" 
	@${RM} ${OBJECTDIR}/uCOS-II/Source/os_multi.o.d 
	@${RM} ${OBJECTDIR}/uCOS-II/Source/os_multi.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  uCOS-II/Source/os_multi.c  -o ${OBJECTDIR}/uCOS-II/Source/os_multi.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/uCOS-II/Source/os_multi.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -I"App" -I"bsp" -I"uC-CPU" -I"uC-LIB" -I"uCOS-II/Source" -I"uCOS-II/Ports" -mlarge-code -Os -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/uCOS-II/Source/os_multi.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/uCOS-II/Source/os_mutex.o: uCOS-II/Source/os_mutex.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/uCOS-II/Source" 
	@${RM} ${OBJECTDIR}/uCOS-II/Source/os_mutex.o.d 
	@${RM} ${OBJECTDIR}/uCOS-II/Source/os_mutex.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  uCOS-II/Source/os_mutex.c  -o ${OBJECTDIR}/uCOS-II/Source/os_mutex.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/uCOS-II/Source/os_mutex.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -I"App" -I"bsp" -I"uC-CPU" -I"uC-LIB" -I"uCOS-II/Source" -I"uCOS-II/Ports" -mlarge-code -Os -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/uCOS-II/Source/os_mutex.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/uCOS-II/Source/os_q.o: uCOS-II/Source/os_q.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/uCOS-II/Source" 
	@${RM} ${OBJECTDIR}/uCOS-II/Source/os_q.o.d 
	@${RM} ${OBJECTDIR}/uCOS-II/Source/os_q.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  uCOS-II/Source/os_q.c  -o ${OBJECTDIR}/uCOS-II/Source/os_q.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/uCOS-II/Source/os_q.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -I"App" -I"bsp" -I"uC-CPU" -I"uC-LIB" -I"uCOS-II/Source" -I"uCOS-II/Ports" -mlarge-code -Os -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/uCOS-II/Source/os_q.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/uCOS-II/Source/os_sem.o: uCOS-II/Source/os_sem.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/uCOS-II/Source" 
	@${RM} ${OBJECTDIR}/uCOS-II/Source/os_sem.o.d 
	@${RM} ${OBJECTDIR}/uCOS-II/Source/os_sem.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  uCOS-II/Source/os_sem.c  -o ${OBJECTDIR}/uCOS-II/Source/os_sem.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/uCOS-II/Source/os_sem.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -I"App" -I"bsp" -I"uC-CPU" -I"uC-LIB" -I"uCOS-II/Source" -I"uCOS-II/Ports" -mlarge-code -Os -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/uCOS-II/Source/os_sem.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/uCOS-II/Source/os_task.o: uCOS-II/Source/os_task.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/uCOS-II/Source" 
	@${RM} ${OBJECTDIR}/uCOS-II/Source/os_task.o.d 
	@${RM} ${OBJECTDIR}/uCOS-II/Source/os_task.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  uCOS-II/Source/os_task.c  -o ${OBJECTDIR}/uCOS-II/Source/os_task.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/uCOS-II/Source/os_task.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -I"App" -I"bsp" -I"uC-CPU" -I"uC-LIB" -I"uCOS-II/Source" -I"uCOS-II/Ports" -mlarge-code -Os -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/uCOS-II/Source/os_task.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/uCOS-II/Source/os_time.o: uCOS-II/Source/os_time.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/uCOS-II/Source" 
	@${RM} ${OBJECTDIR}/uCOS-II/Source/os_time.o.d 
	@${RM} ${OBJECTDIR}/uCOS-II/Source/os_time.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  uCOS-II/Source/os_time.c  -o ${OBJECTDIR}/uCOS-II/Source/os_time.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/uCOS-II/Source/os_time.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -I"App" -I"bsp" -I"uC-CPU" -I"uC-LIB" -I"uCOS-II/Source" -I"uCOS-II/Ports" -mlarge-code -Os -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/uCOS-II/Source/os_time.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/App/app.o: App/app.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/App" 
	@${RM} ${OBJECTDIR}/App/app.o.d 
	@${RM} ${OBJECTDIR}/App/app.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  App/app.c  -o ${OBJECTDIR}/App/app.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/App/app.o.d"        -g -omf=elf -I"App" -I"bsp" -I"uC-CPU" -I"uC-LIB" -I"uCOS-II/Source" -I"uCOS-II/Ports" -mlarge-code -Os -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/App/app.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/bsp/ADC.o: bsp/ADC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/bsp" 
	@${RM} ${OBJECTDIR}/bsp/ADC.o.d 
	@${RM} ${OBJECTDIR}/bsp/ADC.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  bsp/ADC.c  -o ${OBJECTDIR}/bsp/ADC.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/bsp/ADC.o.d"        -g -omf=elf -I"App" -I"bsp" -I"uC-CPU" -I"uC-LIB" -I"uCOS-II/Source" -I"uCOS-II/Ports" -mlarge-code -Os -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/bsp/ADC.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/bsp/IC.o: bsp/IC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/bsp" 
	@${RM} ${OBJECTDIR}/bsp/IC.o.d 
	@${RM} ${OBJECTDIR}/bsp/IC.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  bsp/IC.c  -o ${OBJECTDIR}/bsp/IC.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/bsp/IC.o.d"        -g -omf=elf -I"App" -I"bsp" -I"uC-CPU" -I"uC-LIB" -I"uCOS-II/Source" -I"uCOS-II/Ports" -mlarge-code -Os -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/bsp/IC.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/bsp/ICN.o: bsp/ICN.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/bsp" 
	@${RM} ${OBJECTDIR}/bsp/ICN.o.d 
	@${RM} ${OBJECTDIR}/bsp/ICN.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  bsp/ICN.c  -o ${OBJECTDIR}/bsp/ICN.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/bsp/ICN.o.d"        -g -omf=elf -I"App" -I"bsp" -I"uC-CPU" -I"uC-LIB" -I"uCOS-II/Source" -I"uCOS-II/Ports" -mlarge-code -Os -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/bsp/ICN.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/bsp/INT.o: bsp/INT.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/bsp" 
	@${RM} ${OBJECTDIR}/bsp/INT.o.d 
	@${RM} ${OBJECTDIR}/bsp/INT.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  bsp/INT.c  -o ${OBJECTDIR}/bsp/INT.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/bsp/INT.o.d"        -g -omf=elf -I"App" -I"bsp" -I"uC-CPU" -I"uC-LIB" -I"uCOS-II/Source" -I"uCOS-II/Ports" -mlarge-code -Os -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/bsp/INT.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/bsp/NVIC.o: bsp/NVIC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/bsp" 
	@${RM} ${OBJECTDIR}/bsp/NVIC.o.d 
	@${RM} ${OBJECTDIR}/bsp/NVIC.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  bsp/NVIC.c  -o ${OBJECTDIR}/bsp/NVIC.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/bsp/NVIC.o.d"        -g -omf=elf -I"App" -I"bsp" -I"uC-CPU" -I"uC-LIB" -I"uCOS-II/Source" -I"uCOS-II/Ports" -mlarge-code -Os -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/bsp/NVIC.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/bsp/RS485.o: bsp/RS485.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/bsp" 
	@${RM} ${OBJECTDIR}/bsp/RS485.o.d 
	@${RM} ${OBJECTDIR}/bsp/RS485.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  bsp/RS485.c  -o ${OBJECTDIR}/bsp/RS485.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/bsp/RS485.o.d"        -g -omf=elf -I"App" -I"bsp" -I"uC-CPU" -I"uC-LIB" -I"uCOS-II/Source" -I"uCOS-II/Ports" -mlarge-code -Os -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/bsp/RS485.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/bsp/RTCC.o: bsp/RTCC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/bsp" 
	@${RM} ${OBJECTDIR}/bsp/RTCC.o.d 
	@${RM} ${OBJECTDIR}/bsp/RTCC.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  bsp/RTCC.c  -o ${OBJECTDIR}/bsp/RTCC.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/bsp/RTCC.o.d"        -g -omf=elf -I"App" -I"bsp" -I"uC-CPU" -I"uC-LIB" -I"uCOS-II/Source" -I"uCOS-II/Ports" -mlarge-code -Os -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/bsp/RTCC.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/bsp/SPI.o: bsp/SPI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/bsp" 
	@${RM} ${OBJECTDIR}/bsp/SPI.o.d 
	@${RM} ${OBJECTDIR}/bsp/SPI.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  bsp/SPI.c  -o ${OBJECTDIR}/bsp/SPI.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/bsp/SPI.o.d"        -g -omf=elf -I"App" -I"bsp" -I"uC-CPU" -I"uC-LIB" -I"uCOS-II/Source" -I"uCOS-II/Ports" -mlarge-code -Os -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/bsp/SPI.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/bsp/TIM.o: bsp/TIM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/bsp" 
	@${RM} ${OBJECTDIR}/bsp/TIM.o.d 
	@${RM} ${OBJECTDIR}/bsp/TIM.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  bsp/TIM.c  -o ${OBJECTDIR}/bsp/TIM.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/bsp/TIM.o.d"        -g -omf=elf -I"App" -I"bsp" -I"uC-CPU" -I"uC-LIB" -I"uCOS-II/Source" -I"uCOS-II/Ports" -mlarge-code -Os -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/bsp/TIM.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/bsp/bsp.o: bsp/bsp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/bsp" 
	@${RM} ${OBJECTDIR}/bsp/bsp.o.d 
	@${RM} ${OBJECTDIR}/bsp/bsp.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  bsp/bsp.c  -o ${OBJECTDIR}/bsp/bsp.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/bsp/bsp.o.d"        -g -omf=elf -I"App" -I"bsp" -I"uC-CPU" -I"uC-LIB" -I"uCOS-II/Source" -I"uCOS-II/Ports" -mlarge-code -Os -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/bsp/bsp.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/uC-CPU/cpu_bsp.o: uC-CPU/cpu_bsp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/uC-CPU" 
	@${RM} ${OBJECTDIR}/uC-CPU/cpu_bsp.o.d 
	@${RM} ${OBJECTDIR}/uC-CPU/cpu_bsp.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  uC-CPU/cpu_bsp.c  -o ${OBJECTDIR}/uC-CPU/cpu_bsp.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/uC-CPU/cpu_bsp.o.d"        -g -omf=elf -I"App" -I"bsp" -I"uC-CPU" -I"uC-LIB" -I"uCOS-II/Source" -I"uCOS-II/Ports" -mlarge-code -Os -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/uC-CPU/cpu_bsp.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/uC-CPU/cpu_core.o: uC-CPU/cpu_core.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/uC-CPU" 
	@${RM} ${OBJECTDIR}/uC-CPU/cpu_core.o.d 
	@${RM} ${OBJECTDIR}/uC-CPU/cpu_core.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  uC-CPU/cpu_core.c  -o ${OBJECTDIR}/uC-CPU/cpu_core.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/uC-CPU/cpu_core.o.d"        -g -omf=elf -I"App" -I"bsp" -I"uC-CPU" -I"uC-LIB" -I"uCOS-II/Source" -I"uCOS-II/Ports" -mlarge-code -Os -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/uC-CPU/cpu_core.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/uCOS-II/Ports/os_cpu_c.o: uCOS-II/Ports/os_cpu_c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/uCOS-II/Ports" 
	@${RM} ${OBJECTDIR}/uCOS-II/Ports/os_cpu_c.o.d 
	@${RM} ${OBJECTDIR}/uCOS-II/Ports/os_cpu_c.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  uCOS-II/Ports/os_cpu_c.c  -o ${OBJECTDIR}/uCOS-II/Ports/os_cpu_c.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/uCOS-II/Ports/os_cpu_c.o.d"        -g -omf=elf -I"App" -I"bsp" -I"uC-CPU" -I"uC-LIB" -I"uCOS-II/Source" -I"uCOS-II/Ports" -mlarge-code -Os -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/uCOS-II/Ports/os_cpu_c.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/uCOS-II/Source/os_core.o: uCOS-II/Source/os_core.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/uCOS-II/Source" 
	@${RM} ${OBJECTDIR}/uCOS-II/Source/os_core.o.d 
	@${RM} ${OBJECTDIR}/uCOS-II/Source/os_core.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  uCOS-II/Source/os_core.c  -o ${OBJECTDIR}/uCOS-II/Source/os_core.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/uCOS-II/Source/os_core.o.d"        -g -omf=elf -I"App" -I"bsp" -I"uC-CPU" -I"uC-LIB" -I"uCOS-II/Source" -I"uCOS-II/Ports" -mlarge-code -Os -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/uCOS-II/Source/os_core.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/uCOS-II/Source/os_flag.o: uCOS-II/Source/os_flag.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/uCOS-II/Source" 
	@${RM} ${OBJECTDIR}/uCOS-II/Source/os_flag.o.d 
	@${RM} ${OBJECTDIR}/uCOS-II/Source/os_flag.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  uCOS-II/Source/os_flag.c  -o ${OBJECTDIR}/uCOS-II/Source/os_flag.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/uCOS-II/Source/os_flag.o.d"        -g -omf=elf -I"App" -I"bsp" -I"uC-CPU" -I"uC-LIB" -I"uCOS-II/Source" -I"uCOS-II/Ports" -mlarge-code -Os -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/uCOS-II/Source/os_flag.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/uCOS-II/Source/os_mbox.o: uCOS-II/Source/os_mbox.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/uCOS-II/Source" 
	@${RM} ${OBJECTDIR}/uCOS-II/Source/os_mbox.o.d 
	@${RM} ${OBJECTDIR}/uCOS-II/Source/os_mbox.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  uCOS-II/Source/os_mbox.c  -o ${OBJECTDIR}/uCOS-II/Source/os_mbox.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/uCOS-II/Source/os_mbox.o.d"        -g -omf=elf -I"App" -I"bsp" -I"uC-CPU" -I"uC-LIB" -I"uCOS-II/Source" -I"uCOS-II/Ports" -mlarge-code -Os -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/uCOS-II/Source/os_mbox.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/uCOS-II/Source/os_multi.o: uCOS-II/Source/os_multi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/uCOS-II/Source" 
	@${RM} ${OBJECTDIR}/uCOS-II/Source/os_multi.o.d 
	@${RM} ${OBJECTDIR}/uCOS-II/Source/os_multi.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  uCOS-II/Source/os_multi.c  -o ${OBJECTDIR}/uCOS-II/Source/os_multi.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/uCOS-II/Source/os_multi.o.d"        -g -omf=elf -I"App" -I"bsp" -I"uC-CPU" -I"uC-LIB" -I"uCOS-II/Source" -I"uCOS-II/Ports" -mlarge-code -Os -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/uCOS-II/Source/os_multi.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/uCOS-II/Source/os_mutex.o: uCOS-II/Source/os_mutex.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/uCOS-II/Source" 
	@${RM} ${OBJECTDIR}/uCOS-II/Source/os_mutex.o.d 
	@${RM} ${OBJECTDIR}/uCOS-II/Source/os_mutex.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  uCOS-II/Source/os_mutex.c  -o ${OBJECTDIR}/uCOS-II/Source/os_mutex.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/uCOS-II/Source/os_mutex.o.d"        -g -omf=elf -I"App" -I"bsp" -I"uC-CPU" -I"uC-LIB" -I"uCOS-II/Source" -I"uCOS-II/Ports" -mlarge-code -Os -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/uCOS-II/Source/os_mutex.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/uCOS-II/Source/os_q.o: uCOS-II/Source/os_q.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/uCOS-II/Source" 
	@${RM} ${OBJECTDIR}/uCOS-II/Source/os_q.o.d 
	@${RM} ${OBJECTDIR}/uCOS-II/Source/os_q.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  uCOS-II/Source/os_q.c  -o ${OBJECTDIR}/uCOS-II/Source/os_q.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/uCOS-II/Source/os_q.o.d"        -g -omf=elf -I"App" -I"bsp" -I"uC-CPU" -I"uC-LIB" -I"uCOS-II/Source" -I"uCOS-II/Ports" -mlarge-code -Os -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/uCOS-II/Source/os_q.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/uCOS-II/Source/os_sem.o: uCOS-II/Source/os_sem.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/uCOS-II/Source" 
	@${RM} ${OBJECTDIR}/uCOS-II/Source/os_sem.o.d 
	@${RM} ${OBJECTDIR}/uCOS-II/Source/os_sem.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  uCOS-II/Source/os_sem.c  -o ${OBJECTDIR}/uCOS-II/Source/os_sem.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/uCOS-II/Source/os_sem.o.d"        -g -omf=elf -I"App" -I"bsp" -I"uC-CPU" -I"uC-LIB" -I"uCOS-II/Source" -I"uCOS-II/Ports" -mlarge-code -Os -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/uCOS-II/Source/os_sem.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/uCOS-II/Source/os_task.o: uCOS-II/Source/os_task.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/uCOS-II/Source" 
	@${RM} ${OBJECTDIR}/uCOS-II/Source/os_task.o.d 
	@${RM} ${OBJECTDIR}/uCOS-II/Source/os_task.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  uCOS-II/Source/os_task.c  -o ${OBJECTDIR}/uCOS-II/Source/os_task.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/uCOS-II/Source/os_task.o.d"        -g -omf=elf -I"App" -I"bsp" -I"uC-CPU" -I"uC-LIB" -I"uCOS-II/Source" -I"uCOS-II/Ports" -mlarge-code -Os -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/uCOS-II/Source/os_task.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/uCOS-II/Source/os_time.o: uCOS-II/Source/os_time.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/uCOS-II/Source" 
	@${RM} ${OBJECTDIR}/uCOS-II/Source/os_time.o.d 
	@${RM} ${OBJECTDIR}/uCOS-II/Source/os_time.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  uCOS-II/Source/os_time.c  -o ${OBJECTDIR}/uCOS-II/Source/os_time.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/uCOS-II/Source/os_time.o.d"        -g -omf=elf -I"App" -I"bsp" -I"uC-CPU" -I"uC-LIB" -I"uCOS-II/Source" -I"uCOS-II/Ports" -mlarge-code -Os -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/uCOS-II/Source/os_time.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/uCOS-II/Ports/os_cpu_a.o: uCOS-II/Ports/os_cpu_a.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/uCOS-II/Ports" 
	@${RM} ${OBJECTDIR}/uCOS-II/Ports/os_cpu_a.o.d 
	@${RM} ${OBJECTDIR}/uCOS-II/Ports/os_cpu_a.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  uCOS-II/Ports/os_cpu_a.s  -o ${OBJECTDIR}/uCOS-II/Ports/os_cpu_a.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -I"App" -I"bsp" -I"uC-CPU" -I"uC-LIB" -I"uCOS-II/Source" -I"uCOS-II/Ports" -Wa,-MD,"${OBJECTDIR}/uCOS-II/Ports/os_cpu_a.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/uCOS-II/Ports/os_cpu_a.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/uCOS-II/Ports/os_cpu_a.o: uCOS-II/Ports/os_cpu_a.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/uCOS-II/Ports" 
	@${RM} ${OBJECTDIR}/uCOS-II/Ports/os_cpu_a.o.d 
	@${RM} ${OBJECTDIR}/uCOS-II/Ports/os_cpu_a.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  uCOS-II/Ports/os_cpu_a.s  -o ${OBJECTDIR}/uCOS-II/Ports/os_cpu_a.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -I"App" -I"bsp" -I"uC-CPU" -I"uC-LIB" -I"uCOS-II/Source" -I"uCOS-II/Ports" -Wa,-MD,"${OBJECTDIR}/uCOS-II/Ports/os_cpu_a.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/uCOS-II/Ports/os_cpu_a.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/UCOS-TestENGPRS1.0.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/UCOS-TestENGPRS1.0.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -I"App" -I"bsp" -I"uC-CPU" -I"uC-LIB" -I"uCOS-II/Source" -I"uCOS-II/Ports"  -mreserve=data@0x800:0x81F -mreserve=data@0x820:0x821 -mreserve=data@0x822:0x823 -mreserve=data@0x824:0x825 -mreserve=data@0x826:0x84F   -Wl,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,$(MP_LINKER_FILE_OPTION),--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST) 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/UCOS-TestENGPRS1.0.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/UCOS-TestENGPRS1.0.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -I"App" -I"bsp" -I"uC-CPU" -I"uC-LIB" -I"uCOS-II/Source" -I"uCOS-II/Ports" -Wl,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST) 
	${MP_CC_DIR}\\xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/UCOS-TestENGPRS1.0.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf  
	
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
