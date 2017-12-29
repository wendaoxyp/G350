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
ifeq "$(wildcard nbproject/Makefile-local-pic24EP512GU810.mk)" "nbproject/Makefile-local-pic24EP512GU810.mk"
include nbproject/Makefile-local-pic24EP512GU810.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=pic24EP512GU810
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/OS-Probe.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/OS-Probe.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../app.c ../app_hooks.c ../app_probe.c ../../BSP/bsp_a.s ../../BSP/bsp_lcd.c ../../BSP/bsp.c ../../../../../../uC-CPU/cpu_core.c ../../../../../../uC-LCD/Source/lcd.c ../../../../../../uC-LCD/OS/uCOS-II/lcd_os.c ../../../../../../uC-LIB/lib_ascii.c ../../../../../../uC-LIB/lib_math.c ../../../../../../uC-LIB/lib_mem.c ../../../../../../uC-LIB/lib_str.c ../../../../../../uCOS-II/Source/os_core.c ../../../../../../uCOS-II/Ports/Microchip/XC16/os_cpu_a.s ../../../../../../uCOS-II/Ports/Microchip/XC16/os_cpu_c.c ../../../../../../uCOS-II/Ports/Microchip/XC16/os_cpu_util_a.s ../../../../../../uCOS-II/Ports/Microchip/XC16/os_dbg.c ../../../../../../uCOS-II/Source/os_mem.c ../../../../../../uCOS-II/Source/os_flag.c ../../../../../../uCOS-II/Source/os_mbox.c ../../../../../../uCOS-II/Source/os_mutex.c ../../../../../../uCOS-II/Source/os_q.c ../../../../../../uCOS-II/Source/os_sem.c ../../../../../../uCOS-II/Source/os_task.c ../../../../../../uCOS-II/Source/os_time.c ../../../../../../uC-Probe/Target/Plugins/uCOS-II/os_probe.c ../../../../../../uC-Probe/Target/Communication/Generic/Source/probe_com.c ../../../../../../uC-Probe/Target/Communication/Generic/OS/uCOS-II/probe_com_os.c ../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Source/probe_rs232.c ../../../../../../uC-Probe/Target/Communication/Generic/RS-232/OS/uCOS-II/probe_rs232_os.c ../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16/probe_rs232a.s ../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16/probe_rs232c.c ../../../../../../uCOS-II/Source/os_tmr.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1472/app.o ${OBJECTDIR}/_ext/1472/app_hooks.o ${OBJECTDIR}/_ext/1472/app_probe.o ${OBJECTDIR}/_ext/1445226623/bsp_a.o ${OBJECTDIR}/_ext/1445226623/bsp_lcd.o ${OBJECTDIR}/_ext/1445226623/bsp.o ${OBJECTDIR}/_ext/2124156279/cpu_core.o ${OBJECTDIR}/_ext/1601543492/lcd.o ${OBJECTDIR}/_ext/1313440559/lcd_os.o ${OBJECTDIR}/_ext/2124147866/lib_ascii.o ${OBJECTDIR}/_ext/2124147866/lib_math.o ${OBJECTDIR}/_ext/2124147866/lib_mem.o ${OBJECTDIR}/_ext/2124147866/lib_str.o ${OBJECTDIR}/_ext/1543819695/os_core.o ${OBJECTDIR}/_ext/1247949376/os_cpu_a.o ${OBJECTDIR}/_ext/1247949376/os_cpu_c.o ${OBJECTDIR}/_ext/1247949376/os_cpu_util_a.o ${OBJECTDIR}/_ext/1247949376/os_dbg.o ${OBJECTDIR}/_ext/1543819695/os_mem.o ${OBJECTDIR}/_ext/1543819695/os_flag.o ${OBJECTDIR}/_ext/1543819695/os_mbox.o ${OBJECTDIR}/_ext/1543819695/os_mutex.o ${OBJECTDIR}/_ext/1543819695/os_q.o ${OBJECTDIR}/_ext/1543819695/os_sem.o ${OBJECTDIR}/_ext/1543819695/os_task.o ${OBJECTDIR}/_ext/1543819695/os_time.o ${OBJECTDIR}/_ext/105359244/os_probe.o ${OBJECTDIR}/_ext/406459372/probe_com.o ${OBJECTDIR}/_ext/2060064257/probe_com_os.o ${OBJECTDIR}/_ext/1621511116/probe_rs232.o ${OBJECTDIR}/_ext/756044361/probe_rs232_os.o ${OBJECTDIR}/_ext/1920874491/probe_rs232a.o ${OBJECTDIR}/_ext/1920874491/probe_rs232c.o ${OBJECTDIR}/_ext/1543819695/os_tmr.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1472/app.o.d ${OBJECTDIR}/_ext/1472/app_hooks.o.d ${OBJECTDIR}/_ext/1472/app_probe.o.d ${OBJECTDIR}/_ext/1445226623/bsp_a.o.d ${OBJECTDIR}/_ext/1445226623/bsp_lcd.o.d ${OBJECTDIR}/_ext/1445226623/bsp.o.d ${OBJECTDIR}/_ext/2124156279/cpu_core.o.d ${OBJECTDIR}/_ext/1601543492/lcd.o.d ${OBJECTDIR}/_ext/1313440559/lcd_os.o.d ${OBJECTDIR}/_ext/2124147866/lib_ascii.o.d ${OBJECTDIR}/_ext/2124147866/lib_math.o.d ${OBJECTDIR}/_ext/2124147866/lib_mem.o.d ${OBJECTDIR}/_ext/2124147866/lib_str.o.d ${OBJECTDIR}/_ext/1543819695/os_core.o.d ${OBJECTDIR}/_ext/1247949376/os_cpu_a.o.d ${OBJECTDIR}/_ext/1247949376/os_cpu_c.o.d ${OBJECTDIR}/_ext/1247949376/os_cpu_util_a.o.d ${OBJECTDIR}/_ext/1247949376/os_dbg.o.d ${OBJECTDIR}/_ext/1543819695/os_mem.o.d ${OBJECTDIR}/_ext/1543819695/os_flag.o.d ${OBJECTDIR}/_ext/1543819695/os_mbox.o.d ${OBJECTDIR}/_ext/1543819695/os_mutex.o.d ${OBJECTDIR}/_ext/1543819695/os_q.o.d ${OBJECTDIR}/_ext/1543819695/os_sem.o.d ${OBJECTDIR}/_ext/1543819695/os_task.o.d ${OBJECTDIR}/_ext/1543819695/os_time.o.d ${OBJECTDIR}/_ext/105359244/os_probe.o.d ${OBJECTDIR}/_ext/406459372/probe_com.o.d ${OBJECTDIR}/_ext/2060064257/probe_com_os.o.d ${OBJECTDIR}/_ext/1621511116/probe_rs232.o.d ${OBJECTDIR}/_ext/756044361/probe_rs232_os.o.d ${OBJECTDIR}/_ext/1920874491/probe_rs232a.o.d ${OBJECTDIR}/_ext/1920874491/probe_rs232c.o.d ${OBJECTDIR}/_ext/1543819695/os_tmr.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1472/app.o ${OBJECTDIR}/_ext/1472/app_hooks.o ${OBJECTDIR}/_ext/1472/app_probe.o ${OBJECTDIR}/_ext/1445226623/bsp_a.o ${OBJECTDIR}/_ext/1445226623/bsp_lcd.o ${OBJECTDIR}/_ext/1445226623/bsp.o ${OBJECTDIR}/_ext/2124156279/cpu_core.o ${OBJECTDIR}/_ext/1601543492/lcd.o ${OBJECTDIR}/_ext/1313440559/lcd_os.o ${OBJECTDIR}/_ext/2124147866/lib_ascii.o ${OBJECTDIR}/_ext/2124147866/lib_math.o ${OBJECTDIR}/_ext/2124147866/lib_mem.o ${OBJECTDIR}/_ext/2124147866/lib_str.o ${OBJECTDIR}/_ext/1543819695/os_core.o ${OBJECTDIR}/_ext/1247949376/os_cpu_a.o ${OBJECTDIR}/_ext/1247949376/os_cpu_c.o ${OBJECTDIR}/_ext/1247949376/os_cpu_util_a.o ${OBJECTDIR}/_ext/1247949376/os_dbg.o ${OBJECTDIR}/_ext/1543819695/os_mem.o ${OBJECTDIR}/_ext/1543819695/os_flag.o ${OBJECTDIR}/_ext/1543819695/os_mbox.o ${OBJECTDIR}/_ext/1543819695/os_mutex.o ${OBJECTDIR}/_ext/1543819695/os_q.o ${OBJECTDIR}/_ext/1543819695/os_sem.o ${OBJECTDIR}/_ext/1543819695/os_task.o ${OBJECTDIR}/_ext/1543819695/os_time.o ${OBJECTDIR}/_ext/105359244/os_probe.o ${OBJECTDIR}/_ext/406459372/probe_com.o ${OBJECTDIR}/_ext/2060064257/probe_com_os.o ${OBJECTDIR}/_ext/1621511116/probe_rs232.o ${OBJECTDIR}/_ext/756044361/probe_rs232_os.o ${OBJECTDIR}/_ext/1920874491/probe_rs232a.o ${OBJECTDIR}/_ext/1920874491/probe_rs232c.o ${OBJECTDIR}/_ext/1543819695/os_tmr.o

# Source Files
SOURCEFILES=../app.c ../app_hooks.c ../app_probe.c ../../BSP/bsp_a.s ../../BSP/bsp_lcd.c ../../BSP/bsp.c ../../../../../../uC-CPU/cpu_core.c ../../../../../../uC-LCD/Source/lcd.c ../../../../../../uC-LCD/OS/uCOS-II/lcd_os.c ../../../../../../uC-LIB/lib_ascii.c ../../../../../../uC-LIB/lib_math.c ../../../../../../uC-LIB/lib_mem.c ../../../../../../uC-LIB/lib_str.c ../../../../../../uCOS-II/Source/os_core.c ../../../../../../uCOS-II/Ports/Microchip/XC16/os_cpu_a.s ../../../../../../uCOS-II/Ports/Microchip/XC16/os_cpu_c.c ../../../../../../uCOS-II/Ports/Microchip/XC16/os_cpu_util_a.s ../../../../../../uCOS-II/Ports/Microchip/XC16/os_dbg.c ../../../../../../uCOS-II/Source/os_mem.c ../../../../../../uCOS-II/Source/os_flag.c ../../../../../../uCOS-II/Source/os_mbox.c ../../../../../../uCOS-II/Source/os_mutex.c ../../../../../../uCOS-II/Source/os_q.c ../../../../../../uCOS-II/Source/os_sem.c ../../../../../../uCOS-II/Source/os_task.c ../../../../../../uCOS-II/Source/os_time.c ../../../../../../uC-Probe/Target/Plugins/uCOS-II/os_probe.c ../../../../../../uC-Probe/Target/Communication/Generic/Source/probe_com.c ../../../../../../uC-Probe/Target/Communication/Generic/OS/uCOS-II/probe_com_os.c ../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Source/probe_rs232.c ../../../../../../uC-Probe/Target/Communication/Generic/RS-232/OS/uCOS-II/probe_rs232_os.c ../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16/probe_rs232a.s ../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16/probe_rs232c.c ../../../../../../uCOS-II/Source/os_tmr.c


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
	${MAKE}  -f nbproject/Makefile-pic24EP512GU810.mk dist/${CND_CONF}/${IMAGE_TYPE}/OS-Probe.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=24EP512GU810
MP_LINKER_FILE_OPTION=,--script=p24EP512GU810.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1472/app.o: ../app.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/app.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/app.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../app.c  -o ${OBJECTDIR}/_ext/1472/app.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/app.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -O0 -I"../" -I"../../" -I"../../BSP" -I"." -I"../../../../../../uC-CPU" -I"../../../../../../uC-CPU/Microchip/XC16" -I"../../../../../../uC-LCD/Source" -I"../../../../../../uC-LCD/OS/uCOS-II" -I"../../../../../../uC-LIB" -I"../../../../../../uCOS-II/Source" -I"../../../../../../uCOS-II/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Source" -I"../../../../../../uC-Probe/Target/Communication/Generic/Source" -I"../../../../../../uC-Probe/Target/Plugins/uCOS-II" -I"../../../../../../uC-CPU/Cfg/Template" -I"../../../../../../uCOS-II/Cfg/Template" -I"../../../../../../uC-LIB/Cfg/Template" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/app.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/app_hooks.o: ../app_hooks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/app_hooks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/app_hooks.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../app_hooks.c  -o ${OBJECTDIR}/_ext/1472/app_hooks.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/app_hooks.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -O0 -I"../" -I"../../" -I"../../BSP" -I"." -I"../../../../../../uC-CPU" -I"../../../../../../uC-CPU/Microchip/XC16" -I"../../../../../../uC-LCD/Source" -I"../../../../../../uC-LCD/OS/uCOS-II" -I"../../../../../../uC-LIB" -I"../../../../../../uCOS-II/Source" -I"../../../../../../uCOS-II/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Source" -I"../../../../../../uC-Probe/Target/Communication/Generic/Source" -I"../../../../../../uC-Probe/Target/Plugins/uCOS-II" -I"../../../../../../uC-CPU/Cfg/Template" -I"../../../../../../uCOS-II/Cfg/Template" -I"../../../../../../uC-LIB/Cfg/Template" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/app_hooks.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/app_probe.o: ../app_probe.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/app_probe.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/app_probe.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../app_probe.c  -o ${OBJECTDIR}/_ext/1472/app_probe.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/app_probe.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -O0 -I"../" -I"../../" -I"../../BSP" -I"." -I"../../../../../../uC-CPU" -I"../../../../../../uC-CPU/Microchip/XC16" -I"../../../../../../uC-LCD/Source" -I"../../../../../../uC-LCD/OS/uCOS-II" -I"../../../../../../uC-LIB" -I"../../../../../../uCOS-II/Source" -I"../../../../../../uCOS-II/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Source" -I"../../../../../../uC-Probe/Target/Communication/Generic/Source" -I"../../../../../../uC-Probe/Target/Plugins/uCOS-II" -I"../../../../../../uC-CPU/Cfg/Template" -I"../../../../../../uCOS-II/Cfg/Template" -I"../../../../../../uC-LIB/Cfg/Template" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/app_probe.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1445226623/bsp_lcd.o: ../../BSP/bsp_lcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1445226623 
	@${RM} ${OBJECTDIR}/_ext/1445226623/bsp_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1445226623/bsp_lcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../BSP/bsp_lcd.c  -o ${OBJECTDIR}/_ext/1445226623/bsp_lcd.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1445226623/bsp_lcd.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -O0 -I"../" -I"../../" -I"../../BSP" -I"." -I"../../../../../../uC-CPU" -I"../../../../../../uC-CPU/Microchip/XC16" -I"../../../../../../uC-LCD/Source" -I"../../../../../../uC-LCD/OS/uCOS-II" -I"../../../../../../uC-LIB" -I"../../../../../../uCOS-II/Source" -I"../../../../../../uCOS-II/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Source" -I"../../../../../../uC-Probe/Target/Communication/Generic/Source" -I"../../../../../../uC-Probe/Target/Plugins/uCOS-II" -I"../../../../../../uC-CPU/Cfg/Template" -I"../../../../../../uCOS-II/Cfg/Template" -I"../../../../../../uC-LIB/Cfg/Template" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1445226623/bsp_lcd.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1445226623/bsp.o: ../../BSP/bsp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1445226623 
	@${RM} ${OBJECTDIR}/_ext/1445226623/bsp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1445226623/bsp.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../BSP/bsp.c  -o ${OBJECTDIR}/_ext/1445226623/bsp.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1445226623/bsp.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -O0 -I"../" -I"../../" -I"../../BSP" -I"." -I"../../../../../../uC-CPU" -I"../../../../../../uC-CPU/Microchip/XC16" -I"../../../../../../uC-LCD/Source" -I"../../../../../../uC-LCD/OS/uCOS-II" -I"../../../../../../uC-LIB" -I"../../../../../../uCOS-II/Source" -I"../../../../../../uCOS-II/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Source" -I"../../../../../../uC-Probe/Target/Communication/Generic/Source" -I"../../../../../../uC-Probe/Target/Plugins/uCOS-II" -I"../../../../../../uC-CPU/Cfg/Template" -I"../../../../../../uCOS-II/Cfg/Template" -I"../../../../../../uC-LIB/Cfg/Template" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1445226623/bsp.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/2124156279/cpu_core.o: ../../../../../../uC-CPU/cpu_core.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2124156279 
	@${RM} ${OBJECTDIR}/_ext/2124156279/cpu_core.o.d 
	@${RM} ${OBJECTDIR}/_ext/2124156279/cpu_core.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../../uC-CPU/cpu_core.c  -o ${OBJECTDIR}/_ext/2124156279/cpu_core.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2124156279/cpu_core.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -O0 -I"../" -I"../../" -I"../../BSP" -I"." -I"../../../../../../uC-CPU" -I"../../../../../../uC-CPU/Microchip/XC16" -I"../../../../../../uC-LCD/Source" -I"../../../../../../uC-LCD/OS/uCOS-II" -I"../../../../../../uC-LIB" -I"../../../../../../uCOS-II/Source" -I"../../../../../../uCOS-II/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Source" -I"../../../../../../uC-Probe/Target/Communication/Generic/Source" -I"../../../../../../uC-Probe/Target/Plugins/uCOS-II" -I"../../../../../../uC-CPU/Cfg/Template" -I"../../../../../../uCOS-II/Cfg/Template" -I"../../../../../../uC-LIB/Cfg/Template" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/2124156279/cpu_core.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1601543492/lcd.o: ../../../../../../uC-LCD/Source/lcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1601543492 
	@${RM} ${OBJECTDIR}/_ext/1601543492/lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1601543492/lcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../../uC-LCD/Source/lcd.c  -o ${OBJECTDIR}/_ext/1601543492/lcd.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1601543492/lcd.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -O0 -I"../" -I"../../" -I"../../BSP" -I"." -I"../../../../../../uC-CPU" -I"../../../../../../uC-CPU/Microchip/XC16" -I"../../../../../../uC-LCD/Source" -I"../../../../../../uC-LCD/OS/uCOS-II" -I"../../../../../../uC-LIB" -I"../../../../../../uCOS-II/Source" -I"../../../../../../uCOS-II/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Source" -I"../../../../../../uC-Probe/Target/Communication/Generic/Source" -I"../../../../../../uC-Probe/Target/Plugins/uCOS-II" -I"../../../../../../uC-CPU/Cfg/Template" -I"../../../../../../uCOS-II/Cfg/Template" -I"../../../../../../uC-LIB/Cfg/Template" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1601543492/lcd.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1313440559/lcd_os.o: ../../../../../../uC-LCD/OS/uCOS-II/lcd_os.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1313440559 
	@${RM} ${OBJECTDIR}/_ext/1313440559/lcd_os.o.d 
	@${RM} ${OBJECTDIR}/_ext/1313440559/lcd_os.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../../uC-LCD/OS/uCOS-II/lcd_os.c  -o ${OBJECTDIR}/_ext/1313440559/lcd_os.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1313440559/lcd_os.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -O0 -I"../" -I"../../" -I"../../BSP" -I"." -I"../../../../../../uC-CPU" -I"../../../../../../uC-CPU/Microchip/XC16" -I"../../../../../../uC-LCD/Source" -I"../../../../../../uC-LCD/OS/uCOS-II" -I"../../../../../../uC-LIB" -I"../../../../../../uCOS-II/Source" -I"../../../../../../uCOS-II/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Source" -I"../../../../../../uC-Probe/Target/Communication/Generic/Source" -I"../../../../../../uC-Probe/Target/Plugins/uCOS-II" -I"../../../../../../uC-CPU/Cfg/Template" -I"../../../../../../uCOS-II/Cfg/Template" -I"../../../../../../uC-LIB/Cfg/Template" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1313440559/lcd_os.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/2124147866/lib_ascii.o: ../../../../../../uC-LIB/lib_ascii.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2124147866 
	@${RM} ${OBJECTDIR}/_ext/2124147866/lib_ascii.o.d 
	@${RM} ${OBJECTDIR}/_ext/2124147866/lib_ascii.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../../uC-LIB/lib_ascii.c  -o ${OBJECTDIR}/_ext/2124147866/lib_ascii.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2124147866/lib_ascii.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -O0 -I"../" -I"../../" -I"../../BSP" -I"." -I"../../../../../../uC-CPU" -I"../../../../../../uC-CPU/Microchip/XC16" -I"../../../../../../uC-LCD/Source" -I"../../../../../../uC-LCD/OS/uCOS-II" -I"../../../../../../uC-LIB" -I"../../../../../../uCOS-II/Source" -I"../../../../../../uCOS-II/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Source" -I"../../../../../../uC-Probe/Target/Communication/Generic/Source" -I"../../../../../../uC-Probe/Target/Plugins/uCOS-II" -I"../../../../../../uC-CPU/Cfg/Template" -I"../../../../../../uCOS-II/Cfg/Template" -I"../../../../../../uC-LIB/Cfg/Template" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/2124147866/lib_ascii.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/2124147866/lib_math.o: ../../../../../../uC-LIB/lib_math.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2124147866 
	@${RM} ${OBJECTDIR}/_ext/2124147866/lib_math.o.d 
	@${RM} ${OBJECTDIR}/_ext/2124147866/lib_math.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../../uC-LIB/lib_math.c  -o ${OBJECTDIR}/_ext/2124147866/lib_math.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2124147866/lib_math.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -O0 -I"../" -I"../../" -I"../../BSP" -I"." -I"../../../../../../uC-CPU" -I"../../../../../../uC-CPU/Microchip/XC16" -I"../../../../../../uC-LCD/Source" -I"../../../../../../uC-LCD/OS/uCOS-II" -I"../../../../../../uC-LIB" -I"../../../../../../uCOS-II/Source" -I"../../../../../../uCOS-II/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Source" -I"../../../../../../uC-Probe/Target/Communication/Generic/Source" -I"../../../../../../uC-Probe/Target/Plugins/uCOS-II" -I"../../../../../../uC-CPU/Cfg/Template" -I"../../../../../../uCOS-II/Cfg/Template" -I"../../../../../../uC-LIB/Cfg/Template" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/2124147866/lib_math.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/2124147866/lib_mem.o: ../../../../../../uC-LIB/lib_mem.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2124147866 
	@${RM} ${OBJECTDIR}/_ext/2124147866/lib_mem.o.d 
	@${RM} ${OBJECTDIR}/_ext/2124147866/lib_mem.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../../uC-LIB/lib_mem.c  -o ${OBJECTDIR}/_ext/2124147866/lib_mem.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2124147866/lib_mem.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -O0 -I"../" -I"../../" -I"../../BSP" -I"." -I"../../../../../../uC-CPU" -I"../../../../../../uC-CPU/Microchip/XC16" -I"../../../../../../uC-LCD/Source" -I"../../../../../../uC-LCD/OS/uCOS-II" -I"../../../../../../uC-LIB" -I"../../../../../../uCOS-II/Source" -I"../../../../../../uCOS-II/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Source" -I"../../../../../../uC-Probe/Target/Communication/Generic/Source" -I"../../../../../../uC-Probe/Target/Plugins/uCOS-II" -I"../../../../../../uC-CPU/Cfg/Template" -I"../../../../../../uCOS-II/Cfg/Template" -I"../../../../../../uC-LIB/Cfg/Template" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/2124147866/lib_mem.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/2124147866/lib_str.o: ../../../../../../uC-LIB/lib_str.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2124147866 
	@${RM} ${OBJECTDIR}/_ext/2124147866/lib_str.o.d 
	@${RM} ${OBJECTDIR}/_ext/2124147866/lib_str.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../../uC-LIB/lib_str.c  -o ${OBJECTDIR}/_ext/2124147866/lib_str.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2124147866/lib_str.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -O0 -I"../" -I"../../" -I"../../BSP" -I"." -I"../../../../../../uC-CPU" -I"../../../../../../uC-CPU/Microchip/XC16" -I"../../../../../../uC-LCD/Source" -I"../../../../../../uC-LCD/OS/uCOS-II" -I"../../../../../../uC-LIB" -I"../../../../../../uCOS-II/Source" -I"../../../../../../uCOS-II/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Source" -I"../../../../../../uC-Probe/Target/Communication/Generic/Source" -I"../../../../../../uC-Probe/Target/Plugins/uCOS-II" -I"../../../../../../uC-CPU/Cfg/Template" -I"../../../../../../uCOS-II/Cfg/Template" -I"../../../../../../uC-LIB/Cfg/Template" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/2124147866/lib_str.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1543819695/os_core.o: ../../../../../../uCOS-II/Source/os_core.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1543819695 
	@${RM} ${OBJECTDIR}/_ext/1543819695/os_core.o.d 
	@${RM} ${OBJECTDIR}/_ext/1543819695/os_core.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../../uCOS-II/Source/os_core.c  -o ${OBJECTDIR}/_ext/1543819695/os_core.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1543819695/os_core.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -O0 -I"../" -I"../../" -I"../../BSP" -I"." -I"../../../../../../uC-CPU" -I"../../../../../../uC-CPU/Microchip/XC16" -I"../../../../../../uC-LCD/Source" -I"../../../../../../uC-LCD/OS/uCOS-II" -I"../../../../../../uC-LIB" -I"../../../../../../uCOS-II/Source" -I"../../../../../../uCOS-II/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Source" -I"../../../../../../uC-Probe/Target/Communication/Generic/Source" -I"../../../../../../uC-Probe/Target/Plugins/uCOS-II" -I"../../../../../../uC-CPU/Cfg/Template" -I"../../../../../../uCOS-II/Cfg/Template" -I"../../../../../../uC-LIB/Cfg/Template" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1543819695/os_core.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1247949376/os_cpu_c.o: ../../../../../../uCOS-II/Ports/Microchip/XC16/os_cpu_c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1247949376 
	@${RM} ${OBJECTDIR}/_ext/1247949376/os_cpu_c.o.d 
	@${RM} ${OBJECTDIR}/_ext/1247949376/os_cpu_c.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../../uCOS-II/Ports/Microchip/XC16/os_cpu_c.c  -o ${OBJECTDIR}/_ext/1247949376/os_cpu_c.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1247949376/os_cpu_c.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -O0 -I"../" -I"../../" -I"../../BSP" -I"." -I"../../../../../../uC-CPU" -I"../../../../../../uC-CPU/Microchip/XC16" -I"../../../../../../uC-LCD/Source" -I"../../../../../../uC-LCD/OS/uCOS-II" -I"../../../../../../uC-LIB" -I"../../../../../../uCOS-II/Source" -I"../../../../../../uCOS-II/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Source" -I"../../../../../../uC-Probe/Target/Communication/Generic/Source" -I"../../../../../../uC-Probe/Target/Plugins/uCOS-II" -I"../../../../../../uC-CPU/Cfg/Template" -I"../../../../../../uCOS-II/Cfg/Template" -I"../../../../../../uC-LIB/Cfg/Template" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1247949376/os_cpu_c.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1247949376/os_dbg.o: ../../../../../../uCOS-II/Ports/Microchip/XC16/os_dbg.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1247949376 
	@${RM} ${OBJECTDIR}/_ext/1247949376/os_dbg.o.d 
	@${RM} ${OBJECTDIR}/_ext/1247949376/os_dbg.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../../uCOS-II/Ports/Microchip/XC16/os_dbg.c  -o ${OBJECTDIR}/_ext/1247949376/os_dbg.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1247949376/os_dbg.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -O0 -I"../" -I"../../" -I"../../BSP" -I"." -I"../../../../../../uC-CPU" -I"../../../../../../uC-CPU/Microchip/XC16" -I"../../../../../../uC-LCD/Source" -I"../../../../../../uC-LCD/OS/uCOS-II" -I"../../../../../../uC-LIB" -I"../../../../../../uCOS-II/Source" -I"../../../../../../uCOS-II/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Source" -I"../../../../../../uC-Probe/Target/Communication/Generic/Source" -I"../../../../../../uC-Probe/Target/Plugins/uCOS-II" -I"../../../../../../uC-CPU/Cfg/Template" -I"../../../../../../uCOS-II/Cfg/Template" -I"../../../../../../uC-LIB/Cfg/Template" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1247949376/os_dbg.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1543819695/os_mem.o: ../../../../../../uCOS-II/Source/os_mem.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1543819695 
	@${RM} ${OBJECTDIR}/_ext/1543819695/os_mem.o.d 
	@${RM} ${OBJECTDIR}/_ext/1543819695/os_mem.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../../uCOS-II/Source/os_mem.c  -o ${OBJECTDIR}/_ext/1543819695/os_mem.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1543819695/os_mem.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -O0 -I"../" -I"../../" -I"../../BSP" -I"." -I"../../../../../../uC-CPU" -I"../../../../../../uC-CPU/Microchip/XC16" -I"../../../../../../uC-LCD/Source" -I"../../../../../../uC-LCD/OS/uCOS-II" -I"../../../../../../uC-LIB" -I"../../../../../../uCOS-II/Source" -I"../../../../../../uCOS-II/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Source" -I"../../../../../../uC-Probe/Target/Communication/Generic/Source" -I"../../../../../../uC-Probe/Target/Plugins/uCOS-II" -I"../../../../../../uC-CPU/Cfg/Template" -I"../../../../../../uCOS-II/Cfg/Template" -I"../../../../../../uC-LIB/Cfg/Template" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1543819695/os_mem.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1543819695/os_flag.o: ../../../../../../uCOS-II/Source/os_flag.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1543819695 
	@${RM} ${OBJECTDIR}/_ext/1543819695/os_flag.o.d 
	@${RM} ${OBJECTDIR}/_ext/1543819695/os_flag.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../../uCOS-II/Source/os_flag.c  -o ${OBJECTDIR}/_ext/1543819695/os_flag.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1543819695/os_flag.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -O0 -I"../" -I"../../" -I"../../BSP" -I"." -I"../../../../../../uC-CPU" -I"../../../../../../uC-CPU/Microchip/XC16" -I"../../../../../../uC-LCD/Source" -I"../../../../../../uC-LCD/OS/uCOS-II" -I"../../../../../../uC-LIB" -I"../../../../../../uCOS-II/Source" -I"../../../../../../uCOS-II/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Source" -I"../../../../../../uC-Probe/Target/Communication/Generic/Source" -I"../../../../../../uC-Probe/Target/Plugins/uCOS-II" -I"../../../../../../uC-CPU/Cfg/Template" -I"../../../../../../uCOS-II/Cfg/Template" -I"../../../../../../uC-LIB/Cfg/Template" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1543819695/os_flag.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1543819695/os_mbox.o: ../../../../../../uCOS-II/Source/os_mbox.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1543819695 
	@${RM} ${OBJECTDIR}/_ext/1543819695/os_mbox.o.d 
	@${RM} ${OBJECTDIR}/_ext/1543819695/os_mbox.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../../uCOS-II/Source/os_mbox.c  -o ${OBJECTDIR}/_ext/1543819695/os_mbox.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1543819695/os_mbox.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -O0 -I"../" -I"../../" -I"../../BSP" -I"." -I"../../../../../../uC-CPU" -I"../../../../../../uC-CPU/Microchip/XC16" -I"../../../../../../uC-LCD/Source" -I"../../../../../../uC-LCD/OS/uCOS-II" -I"../../../../../../uC-LIB" -I"../../../../../../uCOS-II/Source" -I"../../../../../../uCOS-II/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Source" -I"../../../../../../uC-Probe/Target/Communication/Generic/Source" -I"../../../../../../uC-Probe/Target/Plugins/uCOS-II" -I"../../../../../../uC-CPU/Cfg/Template" -I"../../../../../../uCOS-II/Cfg/Template" -I"../../../../../../uC-LIB/Cfg/Template" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1543819695/os_mbox.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1543819695/os_mutex.o: ../../../../../../uCOS-II/Source/os_mutex.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1543819695 
	@${RM} ${OBJECTDIR}/_ext/1543819695/os_mutex.o.d 
	@${RM} ${OBJECTDIR}/_ext/1543819695/os_mutex.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../../uCOS-II/Source/os_mutex.c  -o ${OBJECTDIR}/_ext/1543819695/os_mutex.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1543819695/os_mutex.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -O0 -I"../" -I"../../" -I"../../BSP" -I"." -I"../../../../../../uC-CPU" -I"../../../../../../uC-CPU/Microchip/XC16" -I"../../../../../../uC-LCD/Source" -I"../../../../../../uC-LCD/OS/uCOS-II" -I"../../../../../../uC-LIB" -I"../../../../../../uCOS-II/Source" -I"../../../../../../uCOS-II/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Source" -I"../../../../../../uC-Probe/Target/Communication/Generic/Source" -I"../../../../../../uC-Probe/Target/Plugins/uCOS-II" -I"../../../../../../uC-CPU/Cfg/Template" -I"../../../../../../uCOS-II/Cfg/Template" -I"../../../../../../uC-LIB/Cfg/Template" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1543819695/os_mutex.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1543819695/os_q.o: ../../../../../../uCOS-II/Source/os_q.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1543819695 
	@${RM} ${OBJECTDIR}/_ext/1543819695/os_q.o.d 
	@${RM} ${OBJECTDIR}/_ext/1543819695/os_q.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../../uCOS-II/Source/os_q.c  -o ${OBJECTDIR}/_ext/1543819695/os_q.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1543819695/os_q.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -O0 -I"../" -I"../../" -I"../../BSP" -I"." -I"../../../../../../uC-CPU" -I"../../../../../../uC-CPU/Microchip/XC16" -I"../../../../../../uC-LCD/Source" -I"../../../../../../uC-LCD/OS/uCOS-II" -I"../../../../../../uC-LIB" -I"../../../../../../uCOS-II/Source" -I"../../../../../../uCOS-II/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Source" -I"../../../../../../uC-Probe/Target/Communication/Generic/Source" -I"../../../../../../uC-Probe/Target/Plugins/uCOS-II" -I"../../../../../../uC-CPU/Cfg/Template" -I"../../../../../../uCOS-II/Cfg/Template" -I"../../../../../../uC-LIB/Cfg/Template" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1543819695/os_q.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1543819695/os_sem.o: ../../../../../../uCOS-II/Source/os_sem.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1543819695 
	@${RM} ${OBJECTDIR}/_ext/1543819695/os_sem.o.d 
	@${RM} ${OBJECTDIR}/_ext/1543819695/os_sem.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../../uCOS-II/Source/os_sem.c  -o ${OBJECTDIR}/_ext/1543819695/os_sem.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1543819695/os_sem.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -O0 -I"../" -I"../../" -I"../../BSP" -I"." -I"../../../../../../uC-CPU" -I"../../../../../../uC-CPU/Microchip/XC16" -I"../../../../../../uC-LCD/Source" -I"../../../../../../uC-LCD/OS/uCOS-II" -I"../../../../../../uC-LIB" -I"../../../../../../uCOS-II/Source" -I"../../../../../../uCOS-II/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Source" -I"../../../../../../uC-Probe/Target/Communication/Generic/Source" -I"../../../../../../uC-Probe/Target/Plugins/uCOS-II" -I"../../../../../../uC-CPU/Cfg/Template" -I"../../../../../../uCOS-II/Cfg/Template" -I"../../../../../../uC-LIB/Cfg/Template" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1543819695/os_sem.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1543819695/os_task.o: ../../../../../../uCOS-II/Source/os_task.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1543819695 
	@${RM} ${OBJECTDIR}/_ext/1543819695/os_task.o.d 
	@${RM} ${OBJECTDIR}/_ext/1543819695/os_task.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../../uCOS-II/Source/os_task.c  -o ${OBJECTDIR}/_ext/1543819695/os_task.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1543819695/os_task.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -O0 -I"../" -I"../../" -I"../../BSP" -I"." -I"../../../../../../uC-CPU" -I"../../../../../../uC-CPU/Microchip/XC16" -I"../../../../../../uC-LCD/Source" -I"../../../../../../uC-LCD/OS/uCOS-II" -I"../../../../../../uC-LIB" -I"../../../../../../uCOS-II/Source" -I"../../../../../../uCOS-II/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Source" -I"../../../../../../uC-Probe/Target/Communication/Generic/Source" -I"../../../../../../uC-Probe/Target/Plugins/uCOS-II" -I"../../../../../../uC-CPU/Cfg/Template" -I"../../../../../../uCOS-II/Cfg/Template" -I"../../../../../../uC-LIB/Cfg/Template" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1543819695/os_task.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1543819695/os_time.o: ../../../../../../uCOS-II/Source/os_time.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1543819695 
	@${RM} ${OBJECTDIR}/_ext/1543819695/os_time.o.d 
	@${RM} ${OBJECTDIR}/_ext/1543819695/os_time.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../../uCOS-II/Source/os_time.c  -o ${OBJECTDIR}/_ext/1543819695/os_time.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1543819695/os_time.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -O0 -I"../" -I"../../" -I"../../BSP" -I"." -I"../../../../../../uC-CPU" -I"../../../../../../uC-CPU/Microchip/XC16" -I"../../../../../../uC-LCD/Source" -I"../../../../../../uC-LCD/OS/uCOS-II" -I"../../../../../../uC-LIB" -I"../../../../../../uCOS-II/Source" -I"../../../../../../uCOS-II/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Source" -I"../../../../../../uC-Probe/Target/Communication/Generic/Source" -I"../../../../../../uC-Probe/Target/Plugins/uCOS-II" -I"../../../../../../uC-CPU/Cfg/Template" -I"../../../../../../uCOS-II/Cfg/Template" -I"../../../../../../uC-LIB/Cfg/Template" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1543819695/os_time.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/105359244/os_probe.o: ../../../../../../uC-Probe/Target/Plugins/uCOS-II/os_probe.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/105359244 
	@${RM} ${OBJECTDIR}/_ext/105359244/os_probe.o.d 
	@${RM} ${OBJECTDIR}/_ext/105359244/os_probe.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../../uC-Probe/Target/Plugins/uCOS-II/os_probe.c  -o ${OBJECTDIR}/_ext/105359244/os_probe.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/105359244/os_probe.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -O0 -I"../" -I"../../" -I"../../BSP" -I"." -I"../../../../../../uC-CPU" -I"../../../../../../uC-CPU/Microchip/XC16" -I"../../../../../../uC-LCD/Source" -I"../../../../../../uC-LCD/OS/uCOS-II" -I"../../../../../../uC-LIB" -I"../../../../../../uCOS-II/Source" -I"../../../../../../uCOS-II/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Source" -I"../../../../../../uC-Probe/Target/Communication/Generic/Source" -I"../../../../../../uC-Probe/Target/Plugins/uCOS-II" -I"../../../../../../uC-CPU/Cfg/Template" -I"../../../../../../uCOS-II/Cfg/Template" -I"../../../../../../uC-LIB/Cfg/Template" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/105359244/os_probe.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/406459372/probe_com.o: ../../../../../../uC-Probe/Target/Communication/Generic/Source/probe_com.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/406459372 
	@${RM} ${OBJECTDIR}/_ext/406459372/probe_com.o.d 
	@${RM} ${OBJECTDIR}/_ext/406459372/probe_com.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../../uC-Probe/Target/Communication/Generic/Source/probe_com.c  -o ${OBJECTDIR}/_ext/406459372/probe_com.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/406459372/probe_com.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -O0 -I"../" -I"../../" -I"../../BSP" -I"." -I"../../../../../../uC-CPU" -I"../../../../../../uC-CPU/Microchip/XC16" -I"../../../../../../uC-LCD/Source" -I"../../../../../../uC-LCD/OS/uCOS-II" -I"../../../../../../uC-LIB" -I"../../../../../../uCOS-II/Source" -I"../../../../../../uCOS-II/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Source" -I"../../../../../../uC-Probe/Target/Communication/Generic/Source" -I"../../../../../../uC-Probe/Target/Plugins/uCOS-II" -I"../../../../../../uC-CPU/Cfg/Template" -I"../../../../../../uCOS-II/Cfg/Template" -I"../../../../../../uC-LIB/Cfg/Template" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/406459372/probe_com.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/2060064257/probe_com_os.o: ../../../../../../uC-Probe/Target/Communication/Generic/OS/uCOS-II/probe_com_os.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2060064257 
	@${RM} ${OBJECTDIR}/_ext/2060064257/probe_com_os.o.d 
	@${RM} ${OBJECTDIR}/_ext/2060064257/probe_com_os.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../../uC-Probe/Target/Communication/Generic/OS/uCOS-II/probe_com_os.c  -o ${OBJECTDIR}/_ext/2060064257/probe_com_os.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2060064257/probe_com_os.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -O0 -I"../" -I"../../" -I"../../BSP" -I"." -I"../../../../../../uC-CPU" -I"../../../../../../uC-CPU/Microchip/XC16" -I"../../../../../../uC-LCD/Source" -I"../../../../../../uC-LCD/OS/uCOS-II" -I"../../../../../../uC-LIB" -I"../../../../../../uCOS-II/Source" -I"../../../../../../uCOS-II/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Source" -I"../../../../../../uC-Probe/Target/Communication/Generic/Source" -I"../../../../../../uC-Probe/Target/Plugins/uCOS-II" -I"../../../../../../uC-CPU/Cfg/Template" -I"../../../../../../uCOS-II/Cfg/Template" -I"../../../../../../uC-LIB/Cfg/Template" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/2060064257/probe_com_os.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1621511116/probe_rs232.o: ../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Source/probe_rs232.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1621511116 
	@${RM} ${OBJECTDIR}/_ext/1621511116/probe_rs232.o.d 
	@${RM} ${OBJECTDIR}/_ext/1621511116/probe_rs232.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Source/probe_rs232.c  -o ${OBJECTDIR}/_ext/1621511116/probe_rs232.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1621511116/probe_rs232.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -O0 -I"../" -I"../../" -I"../../BSP" -I"." -I"../../../../../../uC-CPU" -I"../../../../../../uC-CPU/Microchip/XC16" -I"../../../../../../uC-LCD/Source" -I"../../../../../../uC-LCD/OS/uCOS-II" -I"../../../../../../uC-LIB" -I"../../../../../../uCOS-II/Source" -I"../../../../../../uCOS-II/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Source" -I"../../../../../../uC-Probe/Target/Communication/Generic/Source" -I"../../../../../../uC-Probe/Target/Plugins/uCOS-II" -I"../../../../../../uC-CPU/Cfg/Template" -I"../../../../../../uCOS-II/Cfg/Template" -I"../../../../../../uC-LIB/Cfg/Template" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1621511116/probe_rs232.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/756044361/probe_rs232_os.o: ../../../../../../uC-Probe/Target/Communication/Generic/RS-232/OS/uCOS-II/probe_rs232_os.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/756044361 
	@${RM} ${OBJECTDIR}/_ext/756044361/probe_rs232_os.o.d 
	@${RM} ${OBJECTDIR}/_ext/756044361/probe_rs232_os.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../../uC-Probe/Target/Communication/Generic/RS-232/OS/uCOS-II/probe_rs232_os.c  -o ${OBJECTDIR}/_ext/756044361/probe_rs232_os.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/756044361/probe_rs232_os.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -O0 -I"../" -I"../../" -I"../../BSP" -I"." -I"../../../../../../uC-CPU" -I"../../../../../../uC-CPU/Microchip/XC16" -I"../../../../../../uC-LCD/Source" -I"../../../../../../uC-LCD/OS/uCOS-II" -I"../../../../../../uC-LIB" -I"../../../../../../uCOS-II/Source" -I"../../../../../../uCOS-II/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Source" -I"../../../../../../uC-Probe/Target/Communication/Generic/Source" -I"../../../../../../uC-Probe/Target/Plugins/uCOS-II" -I"../../../../../../uC-CPU/Cfg/Template" -I"../../../../../../uCOS-II/Cfg/Template" -I"../../../../../../uC-LIB/Cfg/Template" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/756044361/probe_rs232_os.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1920874491/probe_rs232c.o: ../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16/probe_rs232c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1920874491 
	@${RM} ${OBJECTDIR}/_ext/1920874491/probe_rs232c.o.d 
	@${RM} ${OBJECTDIR}/_ext/1920874491/probe_rs232c.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16/probe_rs232c.c  -o ${OBJECTDIR}/_ext/1920874491/probe_rs232c.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1920874491/probe_rs232c.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -O0 -I"../" -I"../../" -I"../../BSP" -I"." -I"../../../../../../uC-CPU" -I"../../../../../../uC-CPU/Microchip/XC16" -I"../../../../../../uC-LCD/Source" -I"../../../../../../uC-LCD/OS/uCOS-II" -I"../../../../../../uC-LIB" -I"../../../../../../uCOS-II/Source" -I"../../../../../../uCOS-II/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Source" -I"../../../../../../uC-Probe/Target/Communication/Generic/Source" -I"../../../../../../uC-Probe/Target/Plugins/uCOS-II" -I"../../../../../../uC-CPU/Cfg/Template" -I"../../../../../../uCOS-II/Cfg/Template" -I"../../../../../../uC-LIB/Cfg/Template" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1920874491/probe_rs232c.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1543819695/os_tmr.o: ../../../../../../uCOS-II/Source/os_tmr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1543819695 
	@${RM} ${OBJECTDIR}/_ext/1543819695/os_tmr.o.d 
	@${RM} ${OBJECTDIR}/_ext/1543819695/os_tmr.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../../uCOS-II/Source/os_tmr.c  -o ${OBJECTDIR}/_ext/1543819695/os_tmr.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1543819695/os_tmr.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -O0 -I"../" -I"../../" -I"../../BSP" -I"." -I"../../../../../../uC-CPU" -I"../../../../../../uC-CPU/Microchip/XC16" -I"../../../../../../uC-LCD/Source" -I"../../../../../../uC-LCD/OS/uCOS-II" -I"../../../../../../uC-LIB" -I"../../../../../../uCOS-II/Source" -I"../../../../../../uCOS-II/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Source" -I"../../../../../../uC-Probe/Target/Communication/Generic/Source" -I"../../../../../../uC-Probe/Target/Plugins/uCOS-II" -I"../../../../../../uC-CPU/Cfg/Template" -I"../../../../../../uCOS-II/Cfg/Template" -I"../../../../../../uC-LIB/Cfg/Template" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1543819695/os_tmr.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/_ext/1472/app.o: ../app.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/app.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/app.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../app.c  -o ${OBJECTDIR}/_ext/1472/app.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/app.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -O0 -I"../" -I"../../" -I"../../BSP" -I"." -I"../../../../../../uC-CPU" -I"../../../../../../uC-CPU/Microchip/XC16" -I"../../../../../../uC-LCD/Source" -I"../../../../../../uC-LCD/OS/uCOS-II" -I"../../../../../../uC-LIB" -I"../../../../../../uCOS-II/Source" -I"../../../../../../uCOS-II/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Source" -I"../../../../../../uC-Probe/Target/Communication/Generic/Source" -I"../../../../../../uC-Probe/Target/Plugins/uCOS-II" -I"../../../../../../uC-CPU/Cfg/Template" -I"../../../../../../uCOS-II/Cfg/Template" -I"../../../../../../uC-LIB/Cfg/Template" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/app.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/app_hooks.o: ../app_hooks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/app_hooks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/app_hooks.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../app_hooks.c  -o ${OBJECTDIR}/_ext/1472/app_hooks.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/app_hooks.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -O0 -I"../" -I"../../" -I"../../BSP" -I"." -I"../../../../../../uC-CPU" -I"../../../../../../uC-CPU/Microchip/XC16" -I"../../../../../../uC-LCD/Source" -I"../../../../../../uC-LCD/OS/uCOS-II" -I"../../../../../../uC-LIB" -I"../../../../../../uCOS-II/Source" -I"../../../../../../uCOS-II/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Source" -I"../../../../../../uC-Probe/Target/Communication/Generic/Source" -I"../../../../../../uC-Probe/Target/Plugins/uCOS-II" -I"../../../../../../uC-CPU/Cfg/Template" -I"../../../../../../uCOS-II/Cfg/Template" -I"../../../../../../uC-LIB/Cfg/Template" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/app_hooks.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/app_probe.o: ../app_probe.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/app_probe.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/app_probe.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../app_probe.c  -o ${OBJECTDIR}/_ext/1472/app_probe.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/app_probe.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -O0 -I"../" -I"../../" -I"../../BSP" -I"." -I"../../../../../../uC-CPU" -I"../../../../../../uC-CPU/Microchip/XC16" -I"../../../../../../uC-LCD/Source" -I"../../../../../../uC-LCD/OS/uCOS-II" -I"../../../../../../uC-LIB" -I"../../../../../../uCOS-II/Source" -I"../../../../../../uCOS-II/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Source" -I"../../../../../../uC-Probe/Target/Communication/Generic/Source" -I"../../../../../../uC-Probe/Target/Plugins/uCOS-II" -I"../../../../../../uC-CPU/Cfg/Template" -I"../../../../../../uCOS-II/Cfg/Template" -I"../../../../../../uC-LIB/Cfg/Template" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/app_probe.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1445226623/bsp_lcd.o: ../../BSP/bsp_lcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1445226623 
	@${RM} ${OBJECTDIR}/_ext/1445226623/bsp_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1445226623/bsp_lcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../BSP/bsp_lcd.c  -o ${OBJECTDIR}/_ext/1445226623/bsp_lcd.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1445226623/bsp_lcd.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -O0 -I"../" -I"../../" -I"../../BSP" -I"." -I"../../../../../../uC-CPU" -I"../../../../../../uC-CPU/Microchip/XC16" -I"../../../../../../uC-LCD/Source" -I"../../../../../../uC-LCD/OS/uCOS-II" -I"../../../../../../uC-LIB" -I"../../../../../../uCOS-II/Source" -I"../../../../../../uCOS-II/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Source" -I"../../../../../../uC-Probe/Target/Communication/Generic/Source" -I"../../../../../../uC-Probe/Target/Plugins/uCOS-II" -I"../../../../../../uC-CPU/Cfg/Template" -I"../../../../../../uCOS-II/Cfg/Template" -I"../../../../../../uC-LIB/Cfg/Template" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1445226623/bsp_lcd.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1445226623/bsp.o: ../../BSP/bsp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1445226623 
	@${RM} ${OBJECTDIR}/_ext/1445226623/bsp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1445226623/bsp.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../BSP/bsp.c  -o ${OBJECTDIR}/_ext/1445226623/bsp.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1445226623/bsp.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -O0 -I"../" -I"../../" -I"../../BSP" -I"." -I"../../../../../../uC-CPU" -I"../../../../../../uC-CPU/Microchip/XC16" -I"../../../../../../uC-LCD/Source" -I"../../../../../../uC-LCD/OS/uCOS-II" -I"../../../../../../uC-LIB" -I"../../../../../../uCOS-II/Source" -I"../../../../../../uCOS-II/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Source" -I"../../../../../../uC-Probe/Target/Communication/Generic/Source" -I"../../../../../../uC-Probe/Target/Plugins/uCOS-II" -I"../../../../../../uC-CPU/Cfg/Template" -I"../../../../../../uCOS-II/Cfg/Template" -I"../../../../../../uC-LIB/Cfg/Template" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1445226623/bsp.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/2124156279/cpu_core.o: ../../../../../../uC-CPU/cpu_core.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2124156279 
	@${RM} ${OBJECTDIR}/_ext/2124156279/cpu_core.o.d 
	@${RM} ${OBJECTDIR}/_ext/2124156279/cpu_core.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../../uC-CPU/cpu_core.c  -o ${OBJECTDIR}/_ext/2124156279/cpu_core.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2124156279/cpu_core.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -O0 -I"../" -I"../../" -I"../../BSP" -I"." -I"../../../../../../uC-CPU" -I"../../../../../../uC-CPU/Microchip/XC16" -I"../../../../../../uC-LCD/Source" -I"../../../../../../uC-LCD/OS/uCOS-II" -I"../../../../../../uC-LIB" -I"../../../../../../uCOS-II/Source" -I"../../../../../../uCOS-II/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Source" -I"../../../../../../uC-Probe/Target/Communication/Generic/Source" -I"../../../../../../uC-Probe/Target/Plugins/uCOS-II" -I"../../../../../../uC-CPU/Cfg/Template" -I"../../../../../../uCOS-II/Cfg/Template" -I"../../../../../../uC-LIB/Cfg/Template" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/2124156279/cpu_core.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1601543492/lcd.o: ../../../../../../uC-LCD/Source/lcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1601543492 
	@${RM} ${OBJECTDIR}/_ext/1601543492/lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1601543492/lcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../../uC-LCD/Source/lcd.c  -o ${OBJECTDIR}/_ext/1601543492/lcd.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1601543492/lcd.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -O0 -I"../" -I"../../" -I"../../BSP" -I"." -I"../../../../../../uC-CPU" -I"../../../../../../uC-CPU/Microchip/XC16" -I"../../../../../../uC-LCD/Source" -I"../../../../../../uC-LCD/OS/uCOS-II" -I"../../../../../../uC-LIB" -I"../../../../../../uCOS-II/Source" -I"../../../../../../uCOS-II/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Source" -I"../../../../../../uC-Probe/Target/Communication/Generic/Source" -I"../../../../../../uC-Probe/Target/Plugins/uCOS-II" -I"../../../../../../uC-CPU/Cfg/Template" -I"../../../../../../uCOS-II/Cfg/Template" -I"../../../../../../uC-LIB/Cfg/Template" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1601543492/lcd.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1313440559/lcd_os.o: ../../../../../../uC-LCD/OS/uCOS-II/lcd_os.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1313440559 
	@${RM} ${OBJECTDIR}/_ext/1313440559/lcd_os.o.d 
	@${RM} ${OBJECTDIR}/_ext/1313440559/lcd_os.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../../uC-LCD/OS/uCOS-II/lcd_os.c  -o ${OBJECTDIR}/_ext/1313440559/lcd_os.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1313440559/lcd_os.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -O0 -I"../" -I"../../" -I"../../BSP" -I"." -I"../../../../../../uC-CPU" -I"../../../../../../uC-CPU/Microchip/XC16" -I"../../../../../../uC-LCD/Source" -I"../../../../../../uC-LCD/OS/uCOS-II" -I"../../../../../../uC-LIB" -I"../../../../../../uCOS-II/Source" -I"../../../../../../uCOS-II/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Source" -I"../../../../../../uC-Probe/Target/Communication/Generic/Source" -I"../../../../../../uC-Probe/Target/Plugins/uCOS-II" -I"../../../../../../uC-CPU/Cfg/Template" -I"../../../../../../uCOS-II/Cfg/Template" -I"../../../../../../uC-LIB/Cfg/Template" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1313440559/lcd_os.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/2124147866/lib_ascii.o: ../../../../../../uC-LIB/lib_ascii.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2124147866 
	@${RM} ${OBJECTDIR}/_ext/2124147866/lib_ascii.o.d 
	@${RM} ${OBJECTDIR}/_ext/2124147866/lib_ascii.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../../uC-LIB/lib_ascii.c  -o ${OBJECTDIR}/_ext/2124147866/lib_ascii.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2124147866/lib_ascii.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -O0 -I"../" -I"../../" -I"../../BSP" -I"." -I"../../../../../../uC-CPU" -I"../../../../../../uC-CPU/Microchip/XC16" -I"../../../../../../uC-LCD/Source" -I"../../../../../../uC-LCD/OS/uCOS-II" -I"../../../../../../uC-LIB" -I"../../../../../../uCOS-II/Source" -I"../../../../../../uCOS-II/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Source" -I"../../../../../../uC-Probe/Target/Communication/Generic/Source" -I"../../../../../../uC-Probe/Target/Plugins/uCOS-II" -I"../../../../../../uC-CPU/Cfg/Template" -I"../../../../../../uCOS-II/Cfg/Template" -I"../../../../../../uC-LIB/Cfg/Template" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/2124147866/lib_ascii.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/2124147866/lib_math.o: ../../../../../../uC-LIB/lib_math.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2124147866 
	@${RM} ${OBJECTDIR}/_ext/2124147866/lib_math.o.d 
	@${RM} ${OBJECTDIR}/_ext/2124147866/lib_math.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../../uC-LIB/lib_math.c  -o ${OBJECTDIR}/_ext/2124147866/lib_math.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2124147866/lib_math.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -O0 -I"../" -I"../../" -I"../../BSP" -I"." -I"../../../../../../uC-CPU" -I"../../../../../../uC-CPU/Microchip/XC16" -I"../../../../../../uC-LCD/Source" -I"../../../../../../uC-LCD/OS/uCOS-II" -I"../../../../../../uC-LIB" -I"../../../../../../uCOS-II/Source" -I"../../../../../../uCOS-II/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Source" -I"../../../../../../uC-Probe/Target/Communication/Generic/Source" -I"../../../../../../uC-Probe/Target/Plugins/uCOS-II" -I"../../../../../../uC-CPU/Cfg/Template" -I"../../../../../../uCOS-II/Cfg/Template" -I"../../../../../../uC-LIB/Cfg/Template" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/2124147866/lib_math.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/2124147866/lib_mem.o: ../../../../../../uC-LIB/lib_mem.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2124147866 
	@${RM} ${OBJECTDIR}/_ext/2124147866/lib_mem.o.d 
	@${RM} ${OBJECTDIR}/_ext/2124147866/lib_mem.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../../uC-LIB/lib_mem.c  -o ${OBJECTDIR}/_ext/2124147866/lib_mem.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2124147866/lib_mem.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -O0 -I"../" -I"../../" -I"../../BSP" -I"." -I"../../../../../../uC-CPU" -I"../../../../../../uC-CPU/Microchip/XC16" -I"../../../../../../uC-LCD/Source" -I"../../../../../../uC-LCD/OS/uCOS-II" -I"../../../../../../uC-LIB" -I"../../../../../../uCOS-II/Source" -I"../../../../../../uCOS-II/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Source" -I"../../../../../../uC-Probe/Target/Communication/Generic/Source" -I"../../../../../../uC-Probe/Target/Plugins/uCOS-II" -I"../../../../../../uC-CPU/Cfg/Template" -I"../../../../../../uCOS-II/Cfg/Template" -I"../../../../../../uC-LIB/Cfg/Template" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/2124147866/lib_mem.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/2124147866/lib_str.o: ../../../../../../uC-LIB/lib_str.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2124147866 
	@${RM} ${OBJECTDIR}/_ext/2124147866/lib_str.o.d 
	@${RM} ${OBJECTDIR}/_ext/2124147866/lib_str.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../../uC-LIB/lib_str.c  -o ${OBJECTDIR}/_ext/2124147866/lib_str.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2124147866/lib_str.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -O0 -I"../" -I"../../" -I"../../BSP" -I"." -I"../../../../../../uC-CPU" -I"../../../../../../uC-CPU/Microchip/XC16" -I"../../../../../../uC-LCD/Source" -I"../../../../../../uC-LCD/OS/uCOS-II" -I"../../../../../../uC-LIB" -I"../../../../../../uCOS-II/Source" -I"../../../../../../uCOS-II/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Source" -I"../../../../../../uC-Probe/Target/Communication/Generic/Source" -I"../../../../../../uC-Probe/Target/Plugins/uCOS-II" -I"../../../../../../uC-CPU/Cfg/Template" -I"../../../../../../uCOS-II/Cfg/Template" -I"../../../../../../uC-LIB/Cfg/Template" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/2124147866/lib_str.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1543819695/os_core.o: ../../../../../../uCOS-II/Source/os_core.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1543819695 
	@${RM} ${OBJECTDIR}/_ext/1543819695/os_core.o.d 
	@${RM} ${OBJECTDIR}/_ext/1543819695/os_core.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../../uCOS-II/Source/os_core.c  -o ${OBJECTDIR}/_ext/1543819695/os_core.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1543819695/os_core.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -O0 -I"../" -I"../../" -I"../../BSP" -I"." -I"../../../../../../uC-CPU" -I"../../../../../../uC-CPU/Microchip/XC16" -I"../../../../../../uC-LCD/Source" -I"../../../../../../uC-LCD/OS/uCOS-II" -I"../../../../../../uC-LIB" -I"../../../../../../uCOS-II/Source" -I"../../../../../../uCOS-II/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Source" -I"../../../../../../uC-Probe/Target/Communication/Generic/Source" -I"../../../../../../uC-Probe/Target/Plugins/uCOS-II" -I"../../../../../../uC-CPU/Cfg/Template" -I"../../../../../../uCOS-II/Cfg/Template" -I"../../../../../../uC-LIB/Cfg/Template" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1543819695/os_core.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1247949376/os_cpu_c.o: ../../../../../../uCOS-II/Ports/Microchip/XC16/os_cpu_c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1247949376 
	@${RM} ${OBJECTDIR}/_ext/1247949376/os_cpu_c.o.d 
	@${RM} ${OBJECTDIR}/_ext/1247949376/os_cpu_c.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../../uCOS-II/Ports/Microchip/XC16/os_cpu_c.c  -o ${OBJECTDIR}/_ext/1247949376/os_cpu_c.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1247949376/os_cpu_c.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -O0 -I"../" -I"../../" -I"../../BSP" -I"." -I"../../../../../../uC-CPU" -I"../../../../../../uC-CPU/Microchip/XC16" -I"../../../../../../uC-LCD/Source" -I"../../../../../../uC-LCD/OS/uCOS-II" -I"../../../../../../uC-LIB" -I"../../../../../../uCOS-II/Source" -I"../../../../../../uCOS-II/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Source" -I"../../../../../../uC-Probe/Target/Communication/Generic/Source" -I"../../../../../../uC-Probe/Target/Plugins/uCOS-II" -I"../../../../../../uC-CPU/Cfg/Template" -I"../../../../../../uCOS-II/Cfg/Template" -I"../../../../../../uC-LIB/Cfg/Template" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1247949376/os_cpu_c.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1247949376/os_dbg.o: ../../../../../../uCOS-II/Ports/Microchip/XC16/os_dbg.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1247949376 
	@${RM} ${OBJECTDIR}/_ext/1247949376/os_dbg.o.d 
	@${RM} ${OBJECTDIR}/_ext/1247949376/os_dbg.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../../uCOS-II/Ports/Microchip/XC16/os_dbg.c  -o ${OBJECTDIR}/_ext/1247949376/os_dbg.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1247949376/os_dbg.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -O0 -I"../" -I"../../" -I"../../BSP" -I"." -I"../../../../../../uC-CPU" -I"../../../../../../uC-CPU/Microchip/XC16" -I"../../../../../../uC-LCD/Source" -I"../../../../../../uC-LCD/OS/uCOS-II" -I"../../../../../../uC-LIB" -I"../../../../../../uCOS-II/Source" -I"../../../../../../uCOS-II/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Source" -I"../../../../../../uC-Probe/Target/Communication/Generic/Source" -I"../../../../../../uC-Probe/Target/Plugins/uCOS-II" -I"../../../../../../uC-CPU/Cfg/Template" -I"../../../../../../uCOS-II/Cfg/Template" -I"../../../../../../uC-LIB/Cfg/Template" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1247949376/os_dbg.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1543819695/os_mem.o: ../../../../../../uCOS-II/Source/os_mem.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1543819695 
	@${RM} ${OBJECTDIR}/_ext/1543819695/os_mem.o.d 
	@${RM} ${OBJECTDIR}/_ext/1543819695/os_mem.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../../uCOS-II/Source/os_mem.c  -o ${OBJECTDIR}/_ext/1543819695/os_mem.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1543819695/os_mem.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -O0 -I"../" -I"../../" -I"../../BSP" -I"." -I"../../../../../../uC-CPU" -I"../../../../../../uC-CPU/Microchip/XC16" -I"../../../../../../uC-LCD/Source" -I"../../../../../../uC-LCD/OS/uCOS-II" -I"../../../../../../uC-LIB" -I"../../../../../../uCOS-II/Source" -I"../../../../../../uCOS-II/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Source" -I"../../../../../../uC-Probe/Target/Communication/Generic/Source" -I"../../../../../../uC-Probe/Target/Plugins/uCOS-II" -I"../../../../../../uC-CPU/Cfg/Template" -I"../../../../../../uCOS-II/Cfg/Template" -I"../../../../../../uC-LIB/Cfg/Template" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1543819695/os_mem.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1543819695/os_flag.o: ../../../../../../uCOS-II/Source/os_flag.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1543819695 
	@${RM} ${OBJECTDIR}/_ext/1543819695/os_flag.o.d 
	@${RM} ${OBJECTDIR}/_ext/1543819695/os_flag.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../../uCOS-II/Source/os_flag.c  -o ${OBJECTDIR}/_ext/1543819695/os_flag.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1543819695/os_flag.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -O0 -I"../" -I"../../" -I"../../BSP" -I"." -I"../../../../../../uC-CPU" -I"../../../../../../uC-CPU/Microchip/XC16" -I"../../../../../../uC-LCD/Source" -I"../../../../../../uC-LCD/OS/uCOS-II" -I"../../../../../../uC-LIB" -I"../../../../../../uCOS-II/Source" -I"../../../../../../uCOS-II/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Source" -I"../../../../../../uC-Probe/Target/Communication/Generic/Source" -I"../../../../../../uC-Probe/Target/Plugins/uCOS-II" -I"../../../../../../uC-CPU/Cfg/Template" -I"../../../../../../uCOS-II/Cfg/Template" -I"../../../../../../uC-LIB/Cfg/Template" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1543819695/os_flag.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1543819695/os_mbox.o: ../../../../../../uCOS-II/Source/os_mbox.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1543819695 
	@${RM} ${OBJECTDIR}/_ext/1543819695/os_mbox.o.d 
	@${RM} ${OBJECTDIR}/_ext/1543819695/os_mbox.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../../uCOS-II/Source/os_mbox.c  -o ${OBJECTDIR}/_ext/1543819695/os_mbox.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1543819695/os_mbox.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -O0 -I"../" -I"../../" -I"../../BSP" -I"." -I"../../../../../../uC-CPU" -I"../../../../../../uC-CPU/Microchip/XC16" -I"../../../../../../uC-LCD/Source" -I"../../../../../../uC-LCD/OS/uCOS-II" -I"../../../../../../uC-LIB" -I"../../../../../../uCOS-II/Source" -I"../../../../../../uCOS-II/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Source" -I"../../../../../../uC-Probe/Target/Communication/Generic/Source" -I"../../../../../../uC-Probe/Target/Plugins/uCOS-II" -I"../../../../../../uC-CPU/Cfg/Template" -I"../../../../../../uCOS-II/Cfg/Template" -I"../../../../../../uC-LIB/Cfg/Template" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1543819695/os_mbox.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1543819695/os_mutex.o: ../../../../../../uCOS-II/Source/os_mutex.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1543819695 
	@${RM} ${OBJECTDIR}/_ext/1543819695/os_mutex.o.d 
	@${RM} ${OBJECTDIR}/_ext/1543819695/os_mutex.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../../uCOS-II/Source/os_mutex.c  -o ${OBJECTDIR}/_ext/1543819695/os_mutex.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1543819695/os_mutex.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -O0 -I"../" -I"../../" -I"../../BSP" -I"." -I"../../../../../../uC-CPU" -I"../../../../../../uC-CPU/Microchip/XC16" -I"../../../../../../uC-LCD/Source" -I"../../../../../../uC-LCD/OS/uCOS-II" -I"../../../../../../uC-LIB" -I"../../../../../../uCOS-II/Source" -I"../../../../../../uCOS-II/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Source" -I"../../../../../../uC-Probe/Target/Communication/Generic/Source" -I"../../../../../../uC-Probe/Target/Plugins/uCOS-II" -I"../../../../../../uC-CPU/Cfg/Template" -I"../../../../../../uCOS-II/Cfg/Template" -I"../../../../../../uC-LIB/Cfg/Template" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1543819695/os_mutex.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1543819695/os_q.o: ../../../../../../uCOS-II/Source/os_q.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1543819695 
	@${RM} ${OBJECTDIR}/_ext/1543819695/os_q.o.d 
	@${RM} ${OBJECTDIR}/_ext/1543819695/os_q.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../../uCOS-II/Source/os_q.c  -o ${OBJECTDIR}/_ext/1543819695/os_q.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1543819695/os_q.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -O0 -I"../" -I"../../" -I"../../BSP" -I"." -I"../../../../../../uC-CPU" -I"../../../../../../uC-CPU/Microchip/XC16" -I"../../../../../../uC-LCD/Source" -I"../../../../../../uC-LCD/OS/uCOS-II" -I"../../../../../../uC-LIB" -I"../../../../../../uCOS-II/Source" -I"../../../../../../uCOS-II/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Source" -I"../../../../../../uC-Probe/Target/Communication/Generic/Source" -I"../../../../../../uC-Probe/Target/Plugins/uCOS-II" -I"../../../../../../uC-CPU/Cfg/Template" -I"../../../../../../uCOS-II/Cfg/Template" -I"../../../../../../uC-LIB/Cfg/Template" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1543819695/os_q.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1543819695/os_sem.o: ../../../../../../uCOS-II/Source/os_sem.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1543819695 
	@${RM} ${OBJECTDIR}/_ext/1543819695/os_sem.o.d 
	@${RM} ${OBJECTDIR}/_ext/1543819695/os_sem.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../../uCOS-II/Source/os_sem.c  -o ${OBJECTDIR}/_ext/1543819695/os_sem.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1543819695/os_sem.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -O0 -I"../" -I"../../" -I"../../BSP" -I"." -I"../../../../../../uC-CPU" -I"../../../../../../uC-CPU/Microchip/XC16" -I"../../../../../../uC-LCD/Source" -I"../../../../../../uC-LCD/OS/uCOS-II" -I"../../../../../../uC-LIB" -I"../../../../../../uCOS-II/Source" -I"../../../../../../uCOS-II/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Source" -I"../../../../../../uC-Probe/Target/Communication/Generic/Source" -I"../../../../../../uC-Probe/Target/Plugins/uCOS-II" -I"../../../../../../uC-CPU/Cfg/Template" -I"../../../../../../uCOS-II/Cfg/Template" -I"../../../../../../uC-LIB/Cfg/Template" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1543819695/os_sem.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1543819695/os_task.o: ../../../../../../uCOS-II/Source/os_task.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1543819695 
	@${RM} ${OBJECTDIR}/_ext/1543819695/os_task.o.d 
	@${RM} ${OBJECTDIR}/_ext/1543819695/os_task.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../../uCOS-II/Source/os_task.c  -o ${OBJECTDIR}/_ext/1543819695/os_task.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1543819695/os_task.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -O0 -I"../" -I"../../" -I"../../BSP" -I"." -I"../../../../../../uC-CPU" -I"../../../../../../uC-CPU/Microchip/XC16" -I"../../../../../../uC-LCD/Source" -I"../../../../../../uC-LCD/OS/uCOS-II" -I"../../../../../../uC-LIB" -I"../../../../../../uCOS-II/Source" -I"../../../../../../uCOS-II/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Source" -I"../../../../../../uC-Probe/Target/Communication/Generic/Source" -I"../../../../../../uC-Probe/Target/Plugins/uCOS-II" -I"../../../../../../uC-CPU/Cfg/Template" -I"../../../../../../uCOS-II/Cfg/Template" -I"../../../../../../uC-LIB/Cfg/Template" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1543819695/os_task.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1543819695/os_time.o: ../../../../../../uCOS-II/Source/os_time.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1543819695 
	@${RM} ${OBJECTDIR}/_ext/1543819695/os_time.o.d 
	@${RM} ${OBJECTDIR}/_ext/1543819695/os_time.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../../uCOS-II/Source/os_time.c  -o ${OBJECTDIR}/_ext/1543819695/os_time.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1543819695/os_time.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -O0 -I"../" -I"../../" -I"../../BSP" -I"." -I"../../../../../../uC-CPU" -I"../../../../../../uC-CPU/Microchip/XC16" -I"../../../../../../uC-LCD/Source" -I"../../../../../../uC-LCD/OS/uCOS-II" -I"../../../../../../uC-LIB" -I"../../../../../../uCOS-II/Source" -I"../../../../../../uCOS-II/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Source" -I"../../../../../../uC-Probe/Target/Communication/Generic/Source" -I"../../../../../../uC-Probe/Target/Plugins/uCOS-II" -I"../../../../../../uC-CPU/Cfg/Template" -I"../../../../../../uCOS-II/Cfg/Template" -I"../../../../../../uC-LIB/Cfg/Template" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1543819695/os_time.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/105359244/os_probe.o: ../../../../../../uC-Probe/Target/Plugins/uCOS-II/os_probe.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/105359244 
	@${RM} ${OBJECTDIR}/_ext/105359244/os_probe.o.d 
	@${RM} ${OBJECTDIR}/_ext/105359244/os_probe.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../../uC-Probe/Target/Plugins/uCOS-II/os_probe.c  -o ${OBJECTDIR}/_ext/105359244/os_probe.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/105359244/os_probe.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -O0 -I"../" -I"../../" -I"../../BSP" -I"." -I"../../../../../../uC-CPU" -I"../../../../../../uC-CPU/Microchip/XC16" -I"../../../../../../uC-LCD/Source" -I"../../../../../../uC-LCD/OS/uCOS-II" -I"../../../../../../uC-LIB" -I"../../../../../../uCOS-II/Source" -I"../../../../../../uCOS-II/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Source" -I"../../../../../../uC-Probe/Target/Communication/Generic/Source" -I"../../../../../../uC-Probe/Target/Plugins/uCOS-II" -I"../../../../../../uC-CPU/Cfg/Template" -I"../../../../../../uCOS-II/Cfg/Template" -I"../../../../../../uC-LIB/Cfg/Template" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/105359244/os_probe.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/406459372/probe_com.o: ../../../../../../uC-Probe/Target/Communication/Generic/Source/probe_com.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/406459372 
	@${RM} ${OBJECTDIR}/_ext/406459372/probe_com.o.d 
	@${RM} ${OBJECTDIR}/_ext/406459372/probe_com.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../../uC-Probe/Target/Communication/Generic/Source/probe_com.c  -o ${OBJECTDIR}/_ext/406459372/probe_com.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/406459372/probe_com.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -O0 -I"../" -I"../../" -I"../../BSP" -I"." -I"../../../../../../uC-CPU" -I"../../../../../../uC-CPU/Microchip/XC16" -I"../../../../../../uC-LCD/Source" -I"../../../../../../uC-LCD/OS/uCOS-II" -I"../../../../../../uC-LIB" -I"../../../../../../uCOS-II/Source" -I"../../../../../../uCOS-II/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Source" -I"../../../../../../uC-Probe/Target/Communication/Generic/Source" -I"../../../../../../uC-Probe/Target/Plugins/uCOS-II" -I"../../../../../../uC-CPU/Cfg/Template" -I"../../../../../../uCOS-II/Cfg/Template" -I"../../../../../../uC-LIB/Cfg/Template" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/406459372/probe_com.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/2060064257/probe_com_os.o: ../../../../../../uC-Probe/Target/Communication/Generic/OS/uCOS-II/probe_com_os.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2060064257 
	@${RM} ${OBJECTDIR}/_ext/2060064257/probe_com_os.o.d 
	@${RM} ${OBJECTDIR}/_ext/2060064257/probe_com_os.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../../uC-Probe/Target/Communication/Generic/OS/uCOS-II/probe_com_os.c  -o ${OBJECTDIR}/_ext/2060064257/probe_com_os.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2060064257/probe_com_os.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -O0 -I"../" -I"../../" -I"../../BSP" -I"." -I"../../../../../../uC-CPU" -I"../../../../../../uC-CPU/Microchip/XC16" -I"../../../../../../uC-LCD/Source" -I"../../../../../../uC-LCD/OS/uCOS-II" -I"../../../../../../uC-LIB" -I"../../../../../../uCOS-II/Source" -I"../../../../../../uCOS-II/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Source" -I"../../../../../../uC-Probe/Target/Communication/Generic/Source" -I"../../../../../../uC-Probe/Target/Plugins/uCOS-II" -I"../../../../../../uC-CPU/Cfg/Template" -I"../../../../../../uCOS-II/Cfg/Template" -I"../../../../../../uC-LIB/Cfg/Template" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/2060064257/probe_com_os.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1621511116/probe_rs232.o: ../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Source/probe_rs232.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1621511116 
	@${RM} ${OBJECTDIR}/_ext/1621511116/probe_rs232.o.d 
	@${RM} ${OBJECTDIR}/_ext/1621511116/probe_rs232.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Source/probe_rs232.c  -o ${OBJECTDIR}/_ext/1621511116/probe_rs232.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1621511116/probe_rs232.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -O0 -I"../" -I"../../" -I"../../BSP" -I"." -I"../../../../../../uC-CPU" -I"../../../../../../uC-CPU/Microchip/XC16" -I"../../../../../../uC-LCD/Source" -I"../../../../../../uC-LCD/OS/uCOS-II" -I"../../../../../../uC-LIB" -I"../../../../../../uCOS-II/Source" -I"../../../../../../uCOS-II/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Source" -I"../../../../../../uC-Probe/Target/Communication/Generic/Source" -I"../../../../../../uC-Probe/Target/Plugins/uCOS-II" -I"../../../../../../uC-CPU/Cfg/Template" -I"../../../../../../uCOS-II/Cfg/Template" -I"../../../../../../uC-LIB/Cfg/Template" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1621511116/probe_rs232.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/756044361/probe_rs232_os.o: ../../../../../../uC-Probe/Target/Communication/Generic/RS-232/OS/uCOS-II/probe_rs232_os.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/756044361 
	@${RM} ${OBJECTDIR}/_ext/756044361/probe_rs232_os.o.d 
	@${RM} ${OBJECTDIR}/_ext/756044361/probe_rs232_os.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../../uC-Probe/Target/Communication/Generic/RS-232/OS/uCOS-II/probe_rs232_os.c  -o ${OBJECTDIR}/_ext/756044361/probe_rs232_os.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/756044361/probe_rs232_os.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -O0 -I"../" -I"../../" -I"../../BSP" -I"." -I"../../../../../../uC-CPU" -I"../../../../../../uC-CPU/Microchip/XC16" -I"../../../../../../uC-LCD/Source" -I"../../../../../../uC-LCD/OS/uCOS-II" -I"../../../../../../uC-LIB" -I"../../../../../../uCOS-II/Source" -I"../../../../../../uCOS-II/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Source" -I"../../../../../../uC-Probe/Target/Communication/Generic/Source" -I"../../../../../../uC-Probe/Target/Plugins/uCOS-II" -I"../../../../../../uC-CPU/Cfg/Template" -I"../../../../../../uCOS-II/Cfg/Template" -I"../../../../../../uC-LIB/Cfg/Template" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/756044361/probe_rs232_os.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1920874491/probe_rs232c.o: ../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16/probe_rs232c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1920874491 
	@${RM} ${OBJECTDIR}/_ext/1920874491/probe_rs232c.o.d 
	@${RM} ${OBJECTDIR}/_ext/1920874491/probe_rs232c.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16/probe_rs232c.c  -o ${OBJECTDIR}/_ext/1920874491/probe_rs232c.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1920874491/probe_rs232c.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -O0 -I"../" -I"../../" -I"../../BSP" -I"." -I"../../../../../../uC-CPU" -I"../../../../../../uC-CPU/Microchip/XC16" -I"../../../../../../uC-LCD/Source" -I"../../../../../../uC-LCD/OS/uCOS-II" -I"../../../../../../uC-LIB" -I"../../../../../../uCOS-II/Source" -I"../../../../../../uCOS-II/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Source" -I"../../../../../../uC-Probe/Target/Communication/Generic/Source" -I"../../../../../../uC-Probe/Target/Plugins/uCOS-II" -I"../../../../../../uC-CPU/Cfg/Template" -I"../../../../../../uCOS-II/Cfg/Template" -I"../../../../../../uC-LIB/Cfg/Template" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1920874491/probe_rs232c.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1543819695/os_tmr.o: ../../../../../../uCOS-II/Source/os_tmr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1543819695 
	@${RM} ${OBJECTDIR}/_ext/1543819695/os_tmr.o.d 
	@${RM} ${OBJECTDIR}/_ext/1543819695/os_tmr.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../../uCOS-II/Source/os_tmr.c  -o ${OBJECTDIR}/_ext/1543819695/os_tmr.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1543819695/os_tmr.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -O0 -I"../" -I"../../" -I"../../BSP" -I"." -I"../../../../../../uC-CPU" -I"../../../../../../uC-CPU/Microchip/XC16" -I"../../../../../../uC-LCD/Source" -I"../../../../../../uC-LCD/OS/uCOS-II" -I"../../../../../../uC-LIB" -I"../../../../../../uCOS-II/Source" -I"../../../../../../uCOS-II/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Source" -I"../../../../../../uC-Probe/Target/Communication/Generic/Source" -I"../../../../../../uC-Probe/Target/Plugins/uCOS-II" -I"../../../../../../uC-CPU/Cfg/Template" -I"../../../../../../uCOS-II/Cfg/Template" -I"../../../../../../uC-LIB/Cfg/Template" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1543819695/os_tmr.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1445226623/bsp_a.o: ../../BSP/bsp_a.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1445226623 
	@${RM} ${OBJECTDIR}/_ext/1445226623/bsp_a.o.d 
	@${RM} ${OBJECTDIR}/_ext/1445226623/bsp_a.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../../BSP/bsp_a.s  -o ${OBJECTDIR}/_ext/1445226623/bsp_a.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -omf=elf -I"../../BSP" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16" -I"../../../../../../uCOS-II/Ports/Microchip/XC16" -Wa,-MD,"${OBJECTDIR}/_ext/1445226623/bsp_a.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD3=1,-g,--no-relax,-g$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/1445226623/bsp_a.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1247949376/os_cpu_a.o: ../../../../../../uCOS-II/Ports/Microchip/XC16/os_cpu_a.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1247949376 
	@${RM} ${OBJECTDIR}/_ext/1247949376/os_cpu_a.o.d 
	@${RM} ${OBJECTDIR}/_ext/1247949376/os_cpu_a.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../../../../../../uCOS-II/Ports/Microchip/XC16/os_cpu_a.s  -o ${OBJECTDIR}/_ext/1247949376/os_cpu_a.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -omf=elf -I"../../BSP" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16" -I"../../../../../../uCOS-II/Ports/Microchip/XC16" -Wa,-MD,"${OBJECTDIR}/_ext/1247949376/os_cpu_a.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD3=1,-g,--no-relax,-g$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/1247949376/os_cpu_a.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1247949376/os_cpu_util_a.o: ../../../../../../uCOS-II/Ports/Microchip/XC16/os_cpu_util_a.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1247949376 
	@${RM} ${OBJECTDIR}/_ext/1247949376/os_cpu_util_a.o.d 
	@${RM} ${OBJECTDIR}/_ext/1247949376/os_cpu_util_a.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../../../../../../uCOS-II/Ports/Microchip/XC16/os_cpu_util_a.s  -o ${OBJECTDIR}/_ext/1247949376/os_cpu_util_a.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -omf=elf -I"../../BSP" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16" -I"../../../../../../uCOS-II/Ports/Microchip/XC16" -Wa,-MD,"${OBJECTDIR}/_ext/1247949376/os_cpu_util_a.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD3=1,-g,--no-relax,-g$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/1247949376/os_cpu_util_a.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1920874491/probe_rs232a.o: ../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16/probe_rs232a.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1920874491 
	@${RM} ${OBJECTDIR}/_ext/1920874491/probe_rs232a.o.d 
	@${RM} ${OBJECTDIR}/_ext/1920874491/probe_rs232a.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16/probe_rs232a.s  -o ${OBJECTDIR}/_ext/1920874491/probe_rs232a.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -omf=elf -I"../../BSP" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16" -I"../../../../../../uCOS-II/Ports/Microchip/XC16" -Wa,-MD,"${OBJECTDIR}/_ext/1920874491/probe_rs232a.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD3=1,-g,--no-relax,-g$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/1920874491/probe_rs232a.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/_ext/1445226623/bsp_a.o: ../../BSP/bsp_a.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1445226623 
	@${RM} ${OBJECTDIR}/_ext/1445226623/bsp_a.o.d 
	@${RM} ${OBJECTDIR}/_ext/1445226623/bsp_a.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../../BSP/bsp_a.s  -o ${OBJECTDIR}/_ext/1445226623/bsp_a.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -I"../../BSP" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16" -I"../../../../../../uCOS-II/Ports/Microchip/XC16" -Wa,-MD,"${OBJECTDIR}/_ext/1445226623/bsp_a.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax,-g$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/1445226623/bsp_a.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1247949376/os_cpu_a.o: ../../../../../../uCOS-II/Ports/Microchip/XC16/os_cpu_a.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1247949376 
	@${RM} ${OBJECTDIR}/_ext/1247949376/os_cpu_a.o.d 
	@${RM} ${OBJECTDIR}/_ext/1247949376/os_cpu_a.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../../../../../../uCOS-II/Ports/Microchip/XC16/os_cpu_a.s  -o ${OBJECTDIR}/_ext/1247949376/os_cpu_a.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -I"../../BSP" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16" -I"../../../../../../uCOS-II/Ports/Microchip/XC16" -Wa,-MD,"${OBJECTDIR}/_ext/1247949376/os_cpu_a.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax,-g$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/1247949376/os_cpu_a.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1247949376/os_cpu_util_a.o: ../../../../../../uCOS-II/Ports/Microchip/XC16/os_cpu_util_a.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1247949376 
	@${RM} ${OBJECTDIR}/_ext/1247949376/os_cpu_util_a.o.d 
	@${RM} ${OBJECTDIR}/_ext/1247949376/os_cpu_util_a.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../../../../../../uCOS-II/Ports/Microchip/XC16/os_cpu_util_a.s  -o ${OBJECTDIR}/_ext/1247949376/os_cpu_util_a.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -I"../../BSP" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16" -I"../../../../../../uCOS-II/Ports/Microchip/XC16" -Wa,-MD,"${OBJECTDIR}/_ext/1247949376/os_cpu_util_a.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax,-g$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/1247949376/os_cpu_util_a.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1920874491/probe_rs232a.o: ../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16/probe_rs232a.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1920874491 
	@${RM} ${OBJECTDIR}/_ext/1920874491/probe_rs232a.o.d 
	@${RM} ${OBJECTDIR}/_ext/1920874491/probe_rs232a.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16/probe_rs232a.s  -o ${OBJECTDIR}/_ext/1920874491/probe_rs232a.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -I"../../BSP" -I"../../../../../../uC-Probe/Target/Communication/Generic/RS-232/Ports/Microchip/XC16" -I"../../../../../../uCOS-II/Ports/Microchip/XC16" -Wa,-MD,"${OBJECTDIR}/_ext/1920874491/probe_rs232a.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax,-g$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/1920874491/probe_rs232a.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/OS-Probe.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/OS-Probe.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -omf=elf  -mreserve=data@0x1000:0x101B -mreserve=data@0x101C:0x101D -mreserve=data@0x101E:0x101F -mreserve=data@0x1020:0x1021 -mreserve=data@0x1022:0x1023 -mreserve=data@0x1024:0x1027 -mreserve=data@0x1028:0x104F   -Wl,--local-stack,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD3=1,$(MP_LINKER_FILE_OPTION),--heap=500,--stack=2000,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--library-path="../../../../../../../../../Program Files/Microchip/MPLAB C30/lib",--library-path="D:/MicroOS/Microchip Projects/dspic710/Micrium/Software/EvalBoards/Microchip/Explorer16/PIC33FJ256/MPLAB_C30/BSP",--library-path=".",--no-force-link,--smart-io,--report-mem$(MP_EXTRA_LD_POST) 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/OS-Probe.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/OS-Probe.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -Wl,--local-stack,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--heap=500,--stack=2000,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--library-path="../../../../../../../../../Program Files/Microchip/MPLAB C30/lib",--library-path="D:/MicroOS/Microchip Projects/dspic710/Micrium/Software/EvalBoards/Microchip/Explorer16/PIC33FJ256/MPLAB_C30/BSP",--library-path=".",--no-force-link,--smart-io,--report-mem$(MP_EXTRA_LD_POST) 
	${MP_CC_DIR}\\xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/OS-Probe.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf  
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/pic24EP512GU810
	${RM} -r dist/pic24EP512GU810

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
