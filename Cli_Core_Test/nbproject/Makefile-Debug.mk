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
	${OBJECTDIR}/Cli_Input/Cli_Input_termios.o \
	${OBJECTDIR}/cli_core_test_main.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f1

# Test Object Files
TESTOBJECTFILES= \
	${TESTDIR}/tests/Test_Str_Filter.o

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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cli_core_test

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cli_core_test: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cli_core_test ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/Cli_Input/Cli_Input_termios.o: Cli_Input/Cli_Input_termios.cpp 
	${MKDIR} -p ${OBJECTDIR}/Cli_Input
	${RM} "$@.d"
	$(COMPILE.cc) -g -ICli_Core -ICli_Input -ICli_Output -ICli_Modules -ICmd_Item -ICmd_Token_Parser -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Cli_Input/Cli_Input_termios.o Cli_Input/Cli_Input_termios.cpp

${OBJECTDIR}/cli_core_test_main.o: cli_core_test_main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -ICli_Core -ICli_Input -ICli_Output -ICli_Modules -ICmd_Item -ICmd_Token_Parser -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cli_core_test_main.o cli_core_test_main.cpp

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-tests-subprojects .build-conf ${TESTFILES}
.build-tests-subprojects:

${TESTDIR}/TestFiles/f1: ${TESTDIR}/tests/Test_Str_Filter.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS} 


${TESTDIR}/tests/Test_Str_Filter.o: tests/Test_Str_Filter.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -ICli_Core -ICli_Input -ICli_Output -ICli_Modules -ICmd_Item -ICmd_Token_Parser -I. -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/Test_Str_Filter.o tests/Test_Str_Filter.cpp


${OBJECTDIR}/Cli_Input/Cli_Input_termios_nomain.o: ${OBJECTDIR}/Cli_Input/Cli_Input_termios.o Cli_Input/Cli_Input_termios.cpp 
	${MKDIR} -p ${OBJECTDIR}/Cli_Input
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Cli_Input/Cli_Input_termios.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -ICli_Core -ICli_Input -ICli_Output -ICli_Modules -ICmd_Item -ICmd_Token_Parser -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Cli_Input/Cli_Input_termios_nomain.o Cli_Input/Cli_Input_termios.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Cli_Input/Cli_Input_termios.o ${OBJECTDIR}/Cli_Input/Cli_Input_termios_nomain.o;\
	fi

${OBJECTDIR}/cli_core_test_main_nomain.o: ${OBJECTDIR}/cli_core_test_main.o cli_core_test_main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/cli_core_test_main.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -ICli_Core -ICli_Input -ICli_Output -ICli_Modules -ICmd_Item -ICmd_Token_Parser -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cli_core_test_main_nomain.o cli_core_test_main.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/cli_core_test_main.o ${OBJECTDIR}/cli_core_test_main_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f1 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cli_core_test

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
