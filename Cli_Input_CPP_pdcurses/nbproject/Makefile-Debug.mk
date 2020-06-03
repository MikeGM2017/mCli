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
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/Cli_Input_pdcurses.o \
	${OBJECTDIR}/cli_input_cpp_pdcurses_main.o


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
LDLIBSOPTIONS=-L../PDCurses-3.8/sdl2 -L../SDL2-2.0.10/build/.libs ../PDCurses-3.8/sdl2/pdcurses.a -lSDL2

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cli_input_cpp_pdcurses

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cli_input_cpp_pdcurses: ../PDCurses-3.8/sdl2/pdcurses.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cli_input_cpp_pdcurses: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cli_input_cpp_pdcurses ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/Cli_Input_pdcurses.o: Cli_Input_pdcurses.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../PDCurses-3.8 -include ../PDCurses-3.8/curses.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Cli_Input_pdcurses.o Cli_Input_pdcurses.cpp

${OBJECTDIR}/cli_input_cpp_pdcurses_main.o: cli_input_cpp_pdcurses_main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../PDCurses-3.8 -include ../PDCurses-3.8/curses.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cli_input_cpp_pdcurses_main.o cli_input_cpp_pdcurses_main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cli_input_cpp_pdcurses

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
