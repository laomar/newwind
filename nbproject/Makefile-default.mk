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
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/newwind.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/newwind.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=oled.c main.c i2c.c ds1302.c rn8302.c at93c46.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/oled.o ${OBJECTDIR}/main.o ${OBJECTDIR}/i2c.o ${OBJECTDIR}/ds1302.o ${OBJECTDIR}/rn8302.o ${OBJECTDIR}/at93c46.o
POSSIBLE_DEPFILES=${OBJECTDIR}/oled.o.d ${OBJECTDIR}/main.o.d ${OBJECTDIR}/i2c.o.d ${OBJECTDIR}/ds1302.o.d ${OBJECTDIR}/rn8302.o.d ${OBJECTDIR}/at93c46.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/oled.o ${OBJECTDIR}/main.o ${OBJECTDIR}/i2c.o ${OBJECTDIR}/ds1302.o ${OBJECTDIR}/rn8302.o ${OBJECTDIR}/at93c46.o

# Source Files
SOURCEFILES=oled.c main.c i2c.c ds1302.c rn8302.c at93c46.c


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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/newwind.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=ATmega128A
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
${OBJECTDIR}/oled.o: oled.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/oled.o.d 
	@${RM} ${OBJECTDIR}/oled.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a  -I "/Applications/microchip/mplabx/v5.10/packs/Atmel/ATmega_DFP/1.2.285/include"  -B "/Applications/microchip/mplabx/v5.10/packs/Atmel/ATmega_DFP/1.2.285/gcc/dev/atmega128a" -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/oled.o.d" -MT "${OBJECTDIR}/oled.o.d" -MT ${OBJECTDIR}/oled.o  -o ${OBJECTDIR}/oled.o oled.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a  -I "/Applications/microchip/mplabx/v5.10/packs/Atmel/ATmega_DFP/1.2.285/include"  -B "/Applications/microchip/mplabx/v5.10/packs/Atmel/ATmega_DFP/1.2.285/gcc/dev/atmega128a" -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/main.o.d" -MT "${OBJECTDIR}/main.o.d" -MT ${OBJECTDIR}/main.o  -o ${OBJECTDIR}/main.o main.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/i2c.o: i2c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/i2c.o.d 
	@${RM} ${OBJECTDIR}/i2c.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a  -I "/Applications/microchip/mplabx/v5.10/packs/Atmel/ATmega_DFP/1.2.285/include"  -B "/Applications/microchip/mplabx/v5.10/packs/Atmel/ATmega_DFP/1.2.285/gcc/dev/atmega128a" -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/i2c.o.d" -MT "${OBJECTDIR}/i2c.o.d" -MT ${OBJECTDIR}/i2c.o  -o ${OBJECTDIR}/i2c.o i2c.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/ds1302.o: ds1302.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ds1302.o.d 
	@${RM} ${OBJECTDIR}/ds1302.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a  -I "/Applications/microchip/mplabx/v5.10/packs/Atmel/ATmega_DFP/1.2.285/include"  -B "/Applications/microchip/mplabx/v5.10/packs/Atmel/ATmega_DFP/1.2.285/gcc/dev/atmega128a" -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/ds1302.o.d" -MT "${OBJECTDIR}/ds1302.o.d" -MT ${OBJECTDIR}/ds1302.o  -o ${OBJECTDIR}/ds1302.o ds1302.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/rn8302.o: rn8302.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/rn8302.o.d 
	@${RM} ${OBJECTDIR}/rn8302.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a  -I "/Applications/microchip/mplabx/v5.10/packs/Atmel/ATmega_DFP/1.2.285/include"  -B "/Applications/microchip/mplabx/v5.10/packs/Atmel/ATmega_DFP/1.2.285/gcc/dev/atmega128a" -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/rn8302.o.d" -MT "${OBJECTDIR}/rn8302.o.d" -MT ${OBJECTDIR}/rn8302.o  -o ${OBJECTDIR}/rn8302.o rn8302.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/at93c46.o: at93c46.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/at93c46.o.d 
	@${RM} ${OBJECTDIR}/at93c46.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a  -I "/Applications/microchip/mplabx/v5.10/packs/Atmel/ATmega_DFP/1.2.285/include"  -B "/Applications/microchip/mplabx/v5.10/packs/Atmel/ATmega_DFP/1.2.285/gcc/dev/atmega128a" -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/at93c46.o.d" -MT "${OBJECTDIR}/at93c46.o.d" -MT ${OBJECTDIR}/at93c46.o  -o ${OBJECTDIR}/at93c46.o at93c46.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
else
${OBJECTDIR}/oled.o: oled.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/oled.o.d 
	@${RM} ${OBJECTDIR}/oled.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a  -I "/Applications/microchip/mplabx/v5.10/packs/Atmel/ATmega_DFP/1.2.285/include"  -B "/Applications/microchip/mplabx/v5.10/packs/Atmel/ATmega_DFP/1.2.285/gcc/dev/atmega128a"  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/oled.o.d" -MT "${OBJECTDIR}/oled.o.d" -MT ${OBJECTDIR}/oled.o  -o ${OBJECTDIR}/oled.o oled.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a  -I "/Applications/microchip/mplabx/v5.10/packs/Atmel/ATmega_DFP/1.2.285/include"  -B "/Applications/microchip/mplabx/v5.10/packs/Atmel/ATmega_DFP/1.2.285/gcc/dev/atmega128a"  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/main.o.d" -MT "${OBJECTDIR}/main.o.d" -MT ${OBJECTDIR}/main.o  -o ${OBJECTDIR}/main.o main.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/i2c.o: i2c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/i2c.o.d 
	@${RM} ${OBJECTDIR}/i2c.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a  -I "/Applications/microchip/mplabx/v5.10/packs/Atmel/ATmega_DFP/1.2.285/include"  -B "/Applications/microchip/mplabx/v5.10/packs/Atmel/ATmega_DFP/1.2.285/gcc/dev/atmega128a"  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/i2c.o.d" -MT "${OBJECTDIR}/i2c.o.d" -MT ${OBJECTDIR}/i2c.o  -o ${OBJECTDIR}/i2c.o i2c.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/ds1302.o: ds1302.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ds1302.o.d 
	@${RM} ${OBJECTDIR}/ds1302.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a  -I "/Applications/microchip/mplabx/v5.10/packs/Atmel/ATmega_DFP/1.2.285/include"  -B "/Applications/microchip/mplabx/v5.10/packs/Atmel/ATmega_DFP/1.2.285/gcc/dev/atmega128a"  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/ds1302.o.d" -MT "${OBJECTDIR}/ds1302.o.d" -MT ${OBJECTDIR}/ds1302.o  -o ${OBJECTDIR}/ds1302.o ds1302.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/rn8302.o: rn8302.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/rn8302.o.d 
	@${RM} ${OBJECTDIR}/rn8302.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a  -I "/Applications/microchip/mplabx/v5.10/packs/Atmel/ATmega_DFP/1.2.285/include"  -B "/Applications/microchip/mplabx/v5.10/packs/Atmel/ATmega_DFP/1.2.285/gcc/dev/atmega128a"  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/rn8302.o.d" -MT "${OBJECTDIR}/rn8302.o.d" -MT ${OBJECTDIR}/rn8302.o  -o ${OBJECTDIR}/rn8302.o rn8302.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/at93c46.o: at93c46.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/at93c46.o.d 
	@${RM} ${OBJECTDIR}/at93c46.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a  -I "/Applications/microchip/mplabx/v5.10/packs/Atmel/ATmega_DFP/1.2.285/include"  -B "/Applications/microchip/mplabx/v5.10/packs/Atmel/ATmega_DFP/1.2.285/gcc/dev/atmega128a"  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/at93c46.o.d" -MT "${OBJECTDIR}/at93c46.o.d" -MT ${OBJECTDIR}/at93c46.o  -o ${OBJECTDIR}/at93c46.o at93c46.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/newwind.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mmcu=atmega128a  -B "/Applications/microchip/mplabx/v5.10/packs/Atmel/ATmega_DFP/1.2.285/gcc/dev/atmega128a"   -gdwarf-2 -D__$(MP_PROCESSOR_OPTION)__  -Wl,-Map="dist/${CND_CONF}/${IMAGE_TYPE}/newwind.${IMAGE_TYPE}.map"    -o dist/${CND_CONF}/${IMAGE_TYPE}/newwind.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}      -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1 -Wl,--gc-sections -Wl,--start-group  -Wl,-lm -Wl,--end-group 
	
	
	
	
	
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/newwind.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mmcu=atmega128a  -B "/Applications/microchip/mplabx/v5.10/packs/Atmel/ATmega_DFP/1.2.285/gcc/dev/atmega128a"  -D__$(MP_PROCESSOR_OPTION)__  -Wl,-Map="dist/${CND_CONF}/${IMAGE_TYPE}/newwind.${IMAGE_TYPE}.map"    -o dist/${CND_CONF}/${IMAGE_TYPE}/newwind.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}      -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION) -Wl,--gc-sections -Wl,--start-group  -Wl,-lm -Wl,--end-group 
	${MP_CC_DIR}/avr-objcopy -O ihex "dist/${CND_CONF}/${IMAGE_TYPE}/newwind.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}" "dist/${CND_CONF}/${IMAGE_TYPE}/newwind.${IMAGE_TYPE}.hex"
	
	
	
	
	
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

DEPFILES=$(shell "${PATH_TO_IDE_BIN}"mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
