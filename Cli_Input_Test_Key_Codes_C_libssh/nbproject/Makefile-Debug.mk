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
	${OBJECTDIR}/Cli_Input_Test_Key_Codes_C_libssh_main.o


# C Compiler Flags
CFLAGS=-lutil

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L../libssh-0.7.7/build/src /usr/lib/x86_64-linux-gnu/libutil.a ../libssh-0.7.7/build/src/libssh.so

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cli_input_test_key_codes_c_libssh

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cli_input_test_key_codes_c_libssh: /usr/lib/x86_64-linux-gnu/libutil.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cli_input_test_key_codes_c_libssh: ../libssh-0.7.7/build/src/libssh.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cli_input_test_key_codes_c_libssh: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cli_input_test_key_codes_c_libssh ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/Cli_Input_Test_Key_Codes_C_libssh_main.o: Cli_Input_Test_Key_Codes_C_libssh_main.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I../libssh-0.7.7/build -I../libssh-0.7.7/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Cli_Input_Test_Key_Codes_C_libssh_main.o Cli_Input_Test_Key_Codes_C_libssh_main.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cli_input_test_key_codes_c_libssh

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
