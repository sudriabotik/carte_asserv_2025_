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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/CARTE_ASSER_2025.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/CARTE_ASSER_2025.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS
SUB_IMAGE_ADDRESS_COMMAND=--image-address $(SUB_IMAGE_ADDRESS)
else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=Fonctions_deplacements.c Uart.c asserv.c autom_R2.c codeurs.c debug.c gestion_AX12.c interruptions.c main.c pwm.c strategie.c system.c evitement.c RF_uart.c serialusM2M.c Serialus.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/Fonctions_deplacements.o ${OBJECTDIR}/Uart.o ${OBJECTDIR}/asserv.o ${OBJECTDIR}/autom_R2.o ${OBJECTDIR}/codeurs.o ${OBJECTDIR}/debug.o ${OBJECTDIR}/gestion_AX12.o ${OBJECTDIR}/interruptions.o ${OBJECTDIR}/main.o ${OBJECTDIR}/pwm.o ${OBJECTDIR}/strategie.o ${OBJECTDIR}/system.o ${OBJECTDIR}/evitement.o ${OBJECTDIR}/RF_uart.o ${OBJECTDIR}/serialusM2M.o ${OBJECTDIR}/Serialus.o
POSSIBLE_DEPFILES=${OBJECTDIR}/Fonctions_deplacements.o.d ${OBJECTDIR}/Uart.o.d ${OBJECTDIR}/asserv.o.d ${OBJECTDIR}/autom_R2.o.d ${OBJECTDIR}/codeurs.o.d ${OBJECTDIR}/debug.o.d ${OBJECTDIR}/gestion_AX12.o.d ${OBJECTDIR}/interruptions.o.d ${OBJECTDIR}/main.o.d ${OBJECTDIR}/pwm.o.d ${OBJECTDIR}/strategie.o.d ${OBJECTDIR}/system.o.d ${OBJECTDIR}/evitement.o.d ${OBJECTDIR}/RF_uart.o.d ${OBJECTDIR}/serialusM2M.o.d ${OBJECTDIR}/Serialus.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/Fonctions_deplacements.o ${OBJECTDIR}/Uart.o ${OBJECTDIR}/asserv.o ${OBJECTDIR}/autom_R2.o ${OBJECTDIR}/codeurs.o ${OBJECTDIR}/debug.o ${OBJECTDIR}/gestion_AX12.o ${OBJECTDIR}/interruptions.o ${OBJECTDIR}/main.o ${OBJECTDIR}/pwm.o ${OBJECTDIR}/strategie.o ${OBJECTDIR}/system.o ${OBJECTDIR}/evitement.o ${OBJECTDIR}/RF_uart.o ${OBJECTDIR}/serialusM2M.o ${OBJECTDIR}/Serialus.o

# Source Files
SOURCEFILES=Fonctions_deplacements.c Uart.c asserv.c autom_R2.c codeurs.c debug.c gestion_AX12.c interruptions.c main.c pwm.c strategie.c system.c evitement.c RF_uart.c serialusM2M.c Serialus.c



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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/CARTE_ASSER_2025.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33FJ128MC804
MP_LINKER_FILE_OPTION=,--script=p33FJ128MC804.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/Fonctions_deplacements.o: Fonctions_deplacements.c  .generated_files/flags/default/6838b4bab32d9d12c724c1008c36ee0c5e4d3fdd .generated_files/flags/default/e81d1cb0aaadef8a054f10d80330b167810abd0f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Fonctions_deplacements.o.d 
	@${RM} ${OBJECTDIR}/Fonctions_deplacements.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Fonctions_deplacements.c  -o ${OBJECTDIR}/Fonctions_deplacements.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Fonctions_deplacements.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -msmall-data -O0 -msmart-io=1 -Werror -Wall -msfr-warn=off   -fshort-enums 
	
${OBJECTDIR}/Uart.o: Uart.c  .generated_files/flags/default/cb7a9c0051b5032eb8f1111e9c3590cb3b18ae1b .generated_files/flags/default/e81d1cb0aaadef8a054f10d80330b167810abd0f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Uart.o.d 
	@${RM} ${OBJECTDIR}/Uart.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Uart.c  -o ${OBJECTDIR}/Uart.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Uart.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -msmall-data -O0 -msmart-io=1 -Werror -Wall -msfr-warn=off   -fshort-enums 
	
${OBJECTDIR}/asserv.o: asserv.c  .generated_files/flags/default/d6106ffd7a3faab55ed9f57fe994c530091f4416 .generated_files/flags/default/e81d1cb0aaadef8a054f10d80330b167810abd0f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/asserv.o.d 
	@${RM} ${OBJECTDIR}/asserv.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  asserv.c  -o ${OBJECTDIR}/asserv.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/asserv.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -msmall-data -O0 -msmart-io=1 -Werror -Wall -msfr-warn=off   -fshort-enums 
	
${OBJECTDIR}/autom_R2.o: autom_R2.c  .generated_files/flags/default/bae18ea97a504079446927b5663aadb11fb51943 .generated_files/flags/default/e81d1cb0aaadef8a054f10d80330b167810abd0f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/autom_R2.o.d 
	@${RM} ${OBJECTDIR}/autom_R2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  autom_R2.c  -o ${OBJECTDIR}/autom_R2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/autom_R2.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -msmall-data -O0 -msmart-io=1 -Werror -Wall -msfr-warn=off   -fshort-enums 
	
${OBJECTDIR}/codeurs.o: codeurs.c  .generated_files/flags/default/2d1e56969ae1862261bc620116343aa39f005c31 .generated_files/flags/default/e81d1cb0aaadef8a054f10d80330b167810abd0f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/codeurs.o.d 
	@${RM} ${OBJECTDIR}/codeurs.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  codeurs.c  -o ${OBJECTDIR}/codeurs.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/codeurs.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -msmall-data -O0 -msmart-io=1 -Werror -Wall -msfr-warn=off   -fshort-enums 
	
${OBJECTDIR}/debug.o: debug.c  .generated_files/flags/default/60d958b96ff77d860eea986d36137885c62697ab .generated_files/flags/default/e81d1cb0aaadef8a054f10d80330b167810abd0f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/debug.o.d 
	@${RM} ${OBJECTDIR}/debug.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  debug.c  -o ${OBJECTDIR}/debug.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/debug.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -msmall-data -O0 -msmart-io=1 -Werror -Wall -msfr-warn=off   -fshort-enums 
	
${OBJECTDIR}/gestion_AX12.o: gestion_AX12.c  .generated_files/flags/default/98e4d2ac78fb39b5319af8ef7117254905e6fb6 .generated_files/flags/default/e81d1cb0aaadef8a054f10d80330b167810abd0f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/gestion_AX12.o.d 
	@${RM} ${OBJECTDIR}/gestion_AX12.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  gestion_AX12.c  -o ${OBJECTDIR}/gestion_AX12.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/gestion_AX12.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -msmall-data -O0 -msmart-io=1 -Werror -Wall -msfr-warn=off   -fshort-enums 
	
${OBJECTDIR}/interruptions.o: interruptions.c  .generated_files/flags/default/182d06769c08ab148e76356540f83560ed731e26 .generated_files/flags/default/e81d1cb0aaadef8a054f10d80330b167810abd0f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/interruptions.o.d 
	@${RM} ${OBJECTDIR}/interruptions.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  interruptions.c  -o ${OBJECTDIR}/interruptions.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/interruptions.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -msmall-data -O0 -msmart-io=1 -Werror -Wall -msfr-warn=off   -fshort-enums 
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/9488f2afa487c0af2cbc34dcdfad4723768a77be .generated_files/flags/default/e81d1cb0aaadef8a054f10d80330b167810abd0f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/main.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -msmall-data -O0 -msmart-io=1 -Werror -Wall -msfr-warn=off   -fshort-enums 
	
${OBJECTDIR}/pwm.o: pwm.c  .generated_files/flags/default/ce666f79736615a3c5ed5460a5c26f861ed5b6de .generated_files/flags/default/e81d1cb0aaadef8a054f10d80330b167810abd0f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/pwm.o.d 
	@${RM} ${OBJECTDIR}/pwm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pwm.c  -o ${OBJECTDIR}/pwm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pwm.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -msmall-data -O0 -msmart-io=1 -Werror -Wall -msfr-warn=off   -fshort-enums 
	
${OBJECTDIR}/strategie.o: strategie.c  .generated_files/flags/default/1a18c1f33708e93f0dd3d3abd6b1076023292625 .generated_files/flags/default/e81d1cb0aaadef8a054f10d80330b167810abd0f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/strategie.o.d 
	@${RM} ${OBJECTDIR}/strategie.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  strategie.c  -o ${OBJECTDIR}/strategie.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/strategie.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -msmall-data -O0 -msmart-io=1 -Werror -Wall -msfr-warn=off   -fshort-enums 
	
${OBJECTDIR}/system.o: system.c  .generated_files/flags/default/fe70d1e2786cc04e8fa6f73337bf373ea8c76351 .generated_files/flags/default/e81d1cb0aaadef8a054f10d80330b167810abd0f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/system.o.d 
	@${RM} ${OBJECTDIR}/system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  system.c  -o ${OBJECTDIR}/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/system.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -msmall-data -O0 -msmart-io=1 -Werror -Wall -msfr-warn=off   -fshort-enums 
	
${OBJECTDIR}/evitement.o: evitement.c  .generated_files/flags/default/6bf993683a3bf8b300d913e0c1b41b00e0077544 .generated_files/flags/default/e81d1cb0aaadef8a054f10d80330b167810abd0f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/evitement.o.d 
	@${RM} ${OBJECTDIR}/evitement.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  evitement.c  -o ${OBJECTDIR}/evitement.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/evitement.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -msmall-data -O0 -msmart-io=1 -Werror -Wall -msfr-warn=off   -fshort-enums 
	
${OBJECTDIR}/RF_uart.o: RF_uart.c  .generated_files/flags/default/393166699de0ecefec7f6f19151a52a608320213 .generated_files/flags/default/e81d1cb0aaadef8a054f10d80330b167810abd0f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/RF_uart.o.d 
	@${RM} ${OBJECTDIR}/RF_uart.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  RF_uart.c  -o ${OBJECTDIR}/RF_uart.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/RF_uart.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -msmall-data -O0 -msmart-io=1 -Werror -Wall -msfr-warn=off   -fshort-enums 
	
${OBJECTDIR}/serialusM2M.o: serialusM2M.c  .generated_files/flags/default/e360ae0a877cc126265424ed0e695d39db06a0e9 .generated_files/flags/default/e81d1cb0aaadef8a054f10d80330b167810abd0f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/serialusM2M.o.d 
	@${RM} ${OBJECTDIR}/serialusM2M.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  serialusM2M.c  -o ${OBJECTDIR}/serialusM2M.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/serialusM2M.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -msmall-data -O0 -msmart-io=1 -Werror -Wall -msfr-warn=off   -fshort-enums 
	
${OBJECTDIR}/Serialus.o: Serialus.c  .generated_files/flags/default/6c12c78066aed187d59d875b8695f4cdce343d0a .generated_files/flags/default/e81d1cb0aaadef8a054f10d80330b167810abd0f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Serialus.o.d 
	@${RM} ${OBJECTDIR}/Serialus.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Serialus.c  -o ${OBJECTDIR}/Serialus.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Serialus.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -msmall-data -O0 -msmart-io=1 -Werror -Wall -msfr-warn=off   -fshort-enums 
	
else
${OBJECTDIR}/Fonctions_deplacements.o: Fonctions_deplacements.c  .generated_files/flags/default/775db15483e945c496e5b47dc51dfa540f124030 .generated_files/flags/default/e81d1cb0aaadef8a054f10d80330b167810abd0f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Fonctions_deplacements.o.d 
	@${RM} ${OBJECTDIR}/Fonctions_deplacements.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Fonctions_deplacements.c  -o ${OBJECTDIR}/Fonctions_deplacements.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Fonctions_deplacements.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -msmall-data -O0 -msmart-io=1 -Werror -Wall -msfr-warn=off   -fshort-enums 
	
${OBJECTDIR}/Uart.o: Uart.c  .generated_files/flags/default/fd2486029d988943b9262e7c3241af90b5d81b9c .generated_files/flags/default/e81d1cb0aaadef8a054f10d80330b167810abd0f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Uart.o.d 
	@${RM} ${OBJECTDIR}/Uart.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Uart.c  -o ${OBJECTDIR}/Uart.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Uart.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -msmall-data -O0 -msmart-io=1 -Werror -Wall -msfr-warn=off   -fshort-enums 
	
${OBJECTDIR}/asserv.o: asserv.c  .generated_files/flags/default/1bb5d2426ab148f9a0066d0d97dadab3a1fbffa0 .generated_files/flags/default/e81d1cb0aaadef8a054f10d80330b167810abd0f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/asserv.o.d 
	@${RM} ${OBJECTDIR}/asserv.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  asserv.c  -o ${OBJECTDIR}/asserv.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/asserv.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -msmall-data -O0 -msmart-io=1 -Werror -Wall -msfr-warn=off   -fshort-enums 
	
${OBJECTDIR}/autom_R2.o: autom_R2.c  .generated_files/flags/default/a18ed7a3386ee6628f30f7a84e7f098105b348ec .generated_files/flags/default/e81d1cb0aaadef8a054f10d80330b167810abd0f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/autom_R2.o.d 
	@${RM} ${OBJECTDIR}/autom_R2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  autom_R2.c  -o ${OBJECTDIR}/autom_R2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/autom_R2.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -msmall-data -O0 -msmart-io=1 -Werror -Wall -msfr-warn=off   -fshort-enums 
	
${OBJECTDIR}/codeurs.o: codeurs.c  .generated_files/flags/default/3b0063282a0282ae82443a6c1b8e491ecf4f5533 .generated_files/flags/default/e81d1cb0aaadef8a054f10d80330b167810abd0f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/codeurs.o.d 
	@${RM} ${OBJECTDIR}/codeurs.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  codeurs.c  -o ${OBJECTDIR}/codeurs.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/codeurs.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -msmall-data -O0 -msmart-io=1 -Werror -Wall -msfr-warn=off   -fshort-enums 
	
${OBJECTDIR}/debug.o: debug.c  .generated_files/flags/default/a3928147b79e362b9957dc47caf5d2ffcb0c443c .generated_files/flags/default/e81d1cb0aaadef8a054f10d80330b167810abd0f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/debug.o.d 
	@${RM} ${OBJECTDIR}/debug.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  debug.c  -o ${OBJECTDIR}/debug.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/debug.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -msmall-data -O0 -msmart-io=1 -Werror -Wall -msfr-warn=off   -fshort-enums 
	
${OBJECTDIR}/gestion_AX12.o: gestion_AX12.c  .generated_files/flags/default/daba42a028eda4f62e934688ade72b3fe055ab1c .generated_files/flags/default/e81d1cb0aaadef8a054f10d80330b167810abd0f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/gestion_AX12.o.d 
	@${RM} ${OBJECTDIR}/gestion_AX12.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  gestion_AX12.c  -o ${OBJECTDIR}/gestion_AX12.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/gestion_AX12.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -msmall-data -O0 -msmart-io=1 -Werror -Wall -msfr-warn=off   -fshort-enums 
	
${OBJECTDIR}/interruptions.o: interruptions.c  .generated_files/flags/default/fc772f3a0e5f4b7109e71b279b8c5e69a7e3b989 .generated_files/flags/default/e81d1cb0aaadef8a054f10d80330b167810abd0f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/interruptions.o.d 
	@${RM} ${OBJECTDIR}/interruptions.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  interruptions.c  -o ${OBJECTDIR}/interruptions.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/interruptions.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -msmall-data -O0 -msmart-io=1 -Werror -Wall -msfr-warn=off   -fshort-enums 
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/373a9037552a3c539b52882dfc50ad9089023a7e .generated_files/flags/default/e81d1cb0aaadef8a054f10d80330b167810abd0f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/main.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -msmall-data -O0 -msmart-io=1 -Werror -Wall -msfr-warn=off   -fshort-enums 
	
${OBJECTDIR}/pwm.o: pwm.c  .generated_files/flags/default/1531109a33245eda6de339af419c34fdd0de32ef .generated_files/flags/default/e81d1cb0aaadef8a054f10d80330b167810abd0f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/pwm.o.d 
	@${RM} ${OBJECTDIR}/pwm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pwm.c  -o ${OBJECTDIR}/pwm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pwm.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -msmall-data -O0 -msmart-io=1 -Werror -Wall -msfr-warn=off   -fshort-enums 
	
${OBJECTDIR}/strategie.o: strategie.c  .generated_files/flags/default/42454f26c1ddde2802ab5c742cfdd918c2e52ba .generated_files/flags/default/e81d1cb0aaadef8a054f10d80330b167810abd0f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/strategie.o.d 
	@${RM} ${OBJECTDIR}/strategie.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  strategie.c  -o ${OBJECTDIR}/strategie.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/strategie.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -msmall-data -O0 -msmart-io=1 -Werror -Wall -msfr-warn=off   -fshort-enums 
	
${OBJECTDIR}/system.o: system.c  .generated_files/flags/default/4d63a863f5b612270fb0220343f445ab6c553a29 .generated_files/flags/default/e81d1cb0aaadef8a054f10d80330b167810abd0f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/system.o.d 
	@${RM} ${OBJECTDIR}/system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  system.c  -o ${OBJECTDIR}/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/system.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -msmall-data -O0 -msmart-io=1 -Werror -Wall -msfr-warn=off   -fshort-enums 
	
${OBJECTDIR}/evitement.o: evitement.c  .generated_files/flags/default/b19fe01bf9e0b7bf1b4cdd99d9ab18942f700b69 .generated_files/flags/default/e81d1cb0aaadef8a054f10d80330b167810abd0f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/evitement.o.d 
	@${RM} ${OBJECTDIR}/evitement.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  evitement.c  -o ${OBJECTDIR}/evitement.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/evitement.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -msmall-data -O0 -msmart-io=1 -Werror -Wall -msfr-warn=off   -fshort-enums 
	
${OBJECTDIR}/RF_uart.o: RF_uart.c  .generated_files/flags/default/1c1fad9f81574f3e227484aa858cb73680a1664c .generated_files/flags/default/e81d1cb0aaadef8a054f10d80330b167810abd0f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/RF_uart.o.d 
	@${RM} ${OBJECTDIR}/RF_uart.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  RF_uart.c  -o ${OBJECTDIR}/RF_uart.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/RF_uart.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -msmall-data -O0 -msmart-io=1 -Werror -Wall -msfr-warn=off   -fshort-enums 
	
${OBJECTDIR}/serialusM2M.o: serialusM2M.c  .generated_files/flags/default/2454118df81aba07f842939d17f0b7eac039bb0e .generated_files/flags/default/e81d1cb0aaadef8a054f10d80330b167810abd0f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/serialusM2M.o.d 
	@${RM} ${OBJECTDIR}/serialusM2M.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  serialusM2M.c  -o ${OBJECTDIR}/serialusM2M.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/serialusM2M.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -msmall-data -O0 -msmart-io=1 -Werror -Wall -msfr-warn=off   -fshort-enums 
	
${OBJECTDIR}/Serialus.o: Serialus.c  .generated_files/flags/default/b08e95b2966c0f54ecab768088b6b9645c473ec .generated_files/flags/default/e81d1cb0aaadef8a054f10d80330b167810abd0f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Serialus.o.d 
	@${RM} ${OBJECTDIR}/Serialus.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Serialus.c  -o ${OBJECTDIR}/Serialus.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Serialus.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -msmall-data -O0 -msmart-io=1 -Werror -Wall -msfr-warn=off   -fshort-enums 
	
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
dist/${CND_CONF}/${IMAGE_TYPE}/CARTE_ASSER_2025.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/CARTE_ASSER_2025.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG=__DEBUG   -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -mreserve=data@0x800:0x81F -mreserve=data@0x820:0x821 -mreserve=data@0x822:0x823 -mreserve=data@0x824:0x825 -mreserve=data@0x826:0x84F   -Wl,,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D__DEBUG=__DEBUG,,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST)  
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/CARTE_ASSER_2025.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/CARTE_ASSER_2025.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -Wl,,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST)  
	${MP_CC_DIR}\\xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/CARTE_ASSER_2025.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf   
	
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
