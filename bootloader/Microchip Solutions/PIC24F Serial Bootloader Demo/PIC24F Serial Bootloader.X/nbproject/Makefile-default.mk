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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/PIC24F_Serial_Bootloader.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/PIC24F_Serial_Bootloader.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED="../../Microchip/PIC24F Serial Bootloader/memory.c" "../../Microchip/PIC24F Serial Bootloader/boot.c"

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/421035786/memory.o ${OBJECTDIR}/_ext/421035786/boot.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/421035786/memory.o.d ${OBJECTDIR}/_ext/421035786/boot.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/421035786/memory.o ${OBJECTDIR}/_ext/421035786/boot.o

# Source Files
SOURCEFILES=../../Microchip/PIC24F Serial Bootloader/memory.c ../../Microchip/PIC24F Serial Bootloader/boot.c


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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/PIC24F_Serial_Bootloader.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=24F32KA302
MP_LINKER_FILE_OPTION=,--script="..\gld\p24F32KA302.gld"
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
${OBJECTDIR}/_ext/421035786/memory.o: ../../Microchip/PIC24F\ Serial\ Bootloader/memory.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/421035786" 
	@${RM} ${OBJECTDIR}/_ext/421035786/memory.o.d 
	@${RM} ${OBJECTDIR}/_ext/421035786/memory.o.ok ${OBJECTDIR}/_ext/421035786/memory.o.err 
	@${RM} ${OBJECTDIR}/_ext/421035786/memory.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/421035786/memory.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../../Include" -I".." -I"../../../PIC24F Serial Bootloader Demo" -I"../../Microchip/Include" -I"../../Microchip/Include/PIC24F Serial Bootloader" -I"." -Os -MMD -MF "${OBJECTDIR}/_ext/421035786/memory.o.d" -o ${OBJECTDIR}/_ext/421035786/memory.o "../../Microchip/PIC24F Serial Bootloader/memory.c"    
	
${OBJECTDIR}/_ext/421035786/boot.o: ../../Microchip/PIC24F\ Serial\ Bootloader/boot.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/421035786" 
	@${RM} ${OBJECTDIR}/_ext/421035786/boot.o.d 
	@${RM} ${OBJECTDIR}/_ext/421035786/boot.o.ok ${OBJECTDIR}/_ext/421035786/boot.o.err 
	@${RM} ${OBJECTDIR}/_ext/421035786/boot.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/421035786/boot.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../../Include" -I".." -I"../../../PIC24F Serial Bootloader Demo" -I"../../Microchip/Include" -I"../../Microchip/Include/PIC24F Serial Bootloader" -I"." -Os -MMD -MF "${OBJECTDIR}/_ext/421035786/boot.o.d" -o ${OBJECTDIR}/_ext/421035786/boot.o "../../Microchip/PIC24F Serial Bootloader/boot.c"    
	
else
${OBJECTDIR}/_ext/421035786/memory.o: ../../Microchip/PIC24F\ Serial\ Bootloader/memory.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/421035786" 
	@${RM} ${OBJECTDIR}/_ext/421035786/memory.o.d 
	@${RM} ${OBJECTDIR}/_ext/421035786/memory.o.ok ${OBJECTDIR}/_ext/421035786/memory.o.err 
	@${RM} ${OBJECTDIR}/_ext/421035786/memory.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/421035786/memory.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../../Include" -I".." -I"../../../PIC24F Serial Bootloader Demo" -I"../../Microchip/Include" -I"../../Microchip/Include/PIC24F Serial Bootloader" -I"." -Os -MMD -MF "${OBJECTDIR}/_ext/421035786/memory.o.d" -o ${OBJECTDIR}/_ext/421035786/memory.o "../../Microchip/PIC24F Serial Bootloader/memory.c"    
	
${OBJECTDIR}/_ext/421035786/boot.o: ../../Microchip/PIC24F\ Serial\ Bootloader/boot.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/421035786" 
	@${RM} ${OBJECTDIR}/_ext/421035786/boot.o.d 
	@${RM} ${OBJECTDIR}/_ext/421035786/boot.o.ok ${OBJECTDIR}/_ext/421035786/boot.o.err 
	@${RM} ${OBJECTDIR}/_ext/421035786/boot.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/421035786/boot.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../../Include" -I".." -I"../../../PIC24F Serial Bootloader Demo" -I"../../Microchip/Include" -I"../../Microchip/Include/PIC24F Serial Bootloader" -I"." -Os -MMD -MF "${OBJECTDIR}/_ext/421035786/boot.o.d" -o ${OBJECTDIR}/_ext/421035786/boot.o "../../Microchip/PIC24F Serial Bootloader/boot.c"    
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/PIC24F_Serial_Bootloader.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    ../gld/p24F32KA302.gld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -omf=elf -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -o dist/${CND_CONF}/${IMAGE_TYPE}/PIC24F_Serial_Bootloader.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}         -Wl,--defsym=__MPLAB_BUILD=1,-L"../../../Program Files/Microchip/MPLAB C30/lib",-L"../gld",-L".",--report-mem$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1
else
dist/${CND_CONF}/${IMAGE_TYPE}/PIC24F_Serial_Bootloader.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   ../gld/p24F32KA302.gld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -omf=elf -mcpu=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/PIC24F_Serial_Bootloader.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}         -Wl,--defsym=__MPLAB_BUILD=1,-L"../../../Program Files/Microchip/MPLAB C30/lib",-L"../gld",-L".",--report-mem$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION)
	${MP_CC_DIR}\\pic30-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/PIC24F_Serial_Bootloader.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -omf=elf
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
