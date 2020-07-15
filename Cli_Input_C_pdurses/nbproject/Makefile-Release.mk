#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/Cli_Input_C.o \
	${OBJECTDIR}/Cli_Input_C_Item.o \
	${OBJECTDIR}/Cli_Input_C_pdcurses.o \
	${OBJECTDIR}/Cli_Output_C_pdurses.o \
	${OBJECTDIR}/cli_input_c_pdurses_main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cli_input_c_pdurses

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cli_input_c_pdurses: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cli_input_c_pdurses ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/Cli_Input_C.o: Cli_Input_C.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Cli_Input_C.o Cli_Input_C.c

${OBJECTDIR}/Cli_Input_C_Item.o: Cli_Input_C_Item.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Cli_Input_C_Item.o Cli_Input_C_Item.c

${OBJECTDIR}/Cli_Input_C_pdcurses.o: Cli_Input_C_pdcurses.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Cli_Input_C_pdcurses.o Cli_Input_C_pdcurses.c

${OBJECTDIR}/Cli_Output_C_pdurses.o: Cli_Output_C_pdurses.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Cli_Output_C_pdurses.o Cli_Output_C_pdurses.c

${OBJECTDIR}/cli_input_c_pdurses_main.o: cli_input_c_pdurses_main.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cli_input_c_pdurses_main.o cli_input_c_pdurses_main.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cli_input_c_pdurses

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
