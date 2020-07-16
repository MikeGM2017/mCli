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
	${TESTDIR}/TestFiles/f6 \
	${TESTDIR}/TestFiles/f8 \
	${TESTDIR}/TestFiles/f13 \
	${TESTDIR}/TestFiles/f14 \
	${TESTDIR}/TestFiles/f12 \
	${TESTDIR}/TestFiles/f3 \
	${TESTDIR}/TestFiles/f4 \
	${TESTDIR}/TestFiles/f5 \
	${TESTDIR}/TestFiles/f2 \
	${TESTDIR}/TestFiles/f7 \
	${TESTDIR}/TestFiles/f10 \
	${TESTDIR}/TestFiles/f11 \
	${TESTDIR}/TestFiles/f9 \
	${TESTDIR}/TestFiles/f1

# Test Object Files
TESTOBJECTFILES= \
	${TESTDIR}/tests/Test_Cmd_Item_Date.o \
	${TESTDIR}/tests/Test_Cmd_Item_DateTime.o \
	${TESTDIR}/tests/Test_Cmd_Item_IP4.o \
	${TESTDIR}/tests/Test_Cmd_Item_IP6.o \
	${TESTDIR}/tests/Test_Cmd_Item_Int.o \
	${TESTDIR}/tests/Test_Cmd_Item_Int_List.o \
	${TESTDIR}/tests/Test_Cmd_Item_Int_Range.o \
	${TESTDIR}/tests/Test_Cmd_Item_MAC.o \
	${TESTDIR}/tests/Test_Cmd_Item_Str.o \
	${TESTDIR}/tests/Test_Cmd_Item_Time.o \
	${TESTDIR}/tests/Test_Cmd_Item_Word.o \
	${TESTDIR}/tests/Test_Cmd_Item_Word_List.o \
	${TESTDIR}/tests/Test_Cmd_Item_Word_Range.o \
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
	$(COMPILE.cc) -g -ICli_Core -ICli_Input -ICli_Output -ICli_Modules -ICmd_Item -ICmd_Token_Parser -ITAB_Cmd -ICli_History -ICli_CMD_Processor -ICli_TAB_Processor -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Cli_Input/Cli_Input_termios.o Cli_Input/Cli_Input_termios.cpp

${OBJECTDIR}/cli_core_test_main.o: cli_core_test_main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -ICli_Core -ICli_Input -ICli_Output -ICli_Modules -ICmd_Item -ICmd_Token_Parser -ITAB_Cmd -ICli_History -ICli_CMD_Processor -ICli_TAB_Processor -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cli_core_test_main.o cli_core_test_main.cpp

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-tests-subprojects .build-conf ${TESTFILES}
.build-tests-subprojects:

${TESTDIR}/TestFiles/f6: ${TESTDIR}/tests/Test_Cmd_Item_Date.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f6 $^ ${LDLIBSOPTIONS} 

${TESTDIR}/TestFiles/f8: ${TESTDIR}/tests/Test_Cmd_Item_DateTime.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f8 $^ ${LDLIBSOPTIONS} 

${TESTDIR}/TestFiles/f13: ${TESTDIR}/tests/Test_Cmd_Item_Int.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f13 $^ ${LDLIBSOPTIONS} 

${TESTDIR}/TestFiles/f14: ${TESTDIR}/tests/Test_Cmd_Item_Int_List.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f14 $^ ${LDLIBSOPTIONS} 

${TESTDIR}/TestFiles/f12: ${TESTDIR}/tests/Test_Cmd_Item_Int_Range.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f12 $^ ${LDLIBSOPTIONS} 

${TESTDIR}/TestFiles/f3: ${TESTDIR}/tests/Test_Cmd_Item_IP4.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f3 $^ ${LDLIBSOPTIONS} 

${TESTDIR}/TestFiles/f4: ${TESTDIR}/tests/Test_Cmd_Item_IP6.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f4 $^ ${LDLIBSOPTIONS} 

${TESTDIR}/TestFiles/f5: ${TESTDIR}/tests/Test_Cmd_Item_MAC.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f5 $^ ${LDLIBSOPTIONS} 

${TESTDIR}/TestFiles/f2: ${TESTDIR}/tests/Test_Cmd_Item_Str.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f2 $^ ${LDLIBSOPTIONS} 

${TESTDIR}/TestFiles/f7: ${TESTDIR}/tests/Test_Cmd_Item_Time.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f7 $^ ${LDLIBSOPTIONS} 

${TESTDIR}/TestFiles/f10: ${TESTDIR}/tests/Test_Cmd_Item_Word.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f10 $^ ${LDLIBSOPTIONS} 

${TESTDIR}/TestFiles/f11: ${TESTDIR}/tests/Test_Cmd_Item_Word_List.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f11 $^ ${LDLIBSOPTIONS} 

${TESTDIR}/TestFiles/f9: ${TESTDIR}/tests/Test_Cmd_Item_Word_Range.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f9 $^ ${LDLIBSOPTIONS} 

${TESTDIR}/TestFiles/f1: ${TESTDIR}/tests/Test_Str_Filter.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS} 


${TESTDIR}/tests/Test_Cmd_Item_Date.o: tests/Test_Cmd_Item_Date.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -ICli_Core -ICli_Input -ICli_Output -ICli_Modules -ICmd_Item -ICmd_Token_Parser -ITAB_Cmd -ICli_History -ICli_CMD_Processor -ICli_TAB_Processor -I. -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/Test_Cmd_Item_Date.o tests/Test_Cmd_Item_Date.cpp


${TESTDIR}/tests/Test_Cmd_Item_DateTime.o: tests/Test_Cmd_Item_DateTime.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -ICli_Core -ICli_Input -ICli_Output -ICli_Modules -ICmd_Item -ICmd_Token_Parser -ITAB_Cmd -ICli_History -ICli_CMD_Processor -ICli_TAB_Processor -I. -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/Test_Cmd_Item_DateTime.o tests/Test_Cmd_Item_DateTime.cpp


${TESTDIR}/tests/Test_Cmd_Item_Int.o: tests/Test_Cmd_Item_Int.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -ICli_Core -ICli_Input -ICli_Output -ICli_Modules -ICmd_Item -ICmd_Token_Parser -ITAB_Cmd -ICli_History -ICli_CMD_Processor -ICli_TAB_Processor -I. -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/Test_Cmd_Item_Int.o tests/Test_Cmd_Item_Int.cpp


${TESTDIR}/tests/Test_Cmd_Item_Int_List.o: tests/Test_Cmd_Item_Int_List.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -ICli_Core -ICli_Input -ICli_Output -ICli_Modules -ICmd_Item -ICmd_Token_Parser -ITAB_Cmd -ICli_History -ICli_CMD_Processor -ICli_TAB_Processor -I. -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/Test_Cmd_Item_Int_List.o tests/Test_Cmd_Item_Int_List.cpp


${TESTDIR}/tests/Test_Cmd_Item_Int_Range.o: tests/Test_Cmd_Item_Int_Range.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -ICli_Core -ICli_Input -ICli_Output -ICli_Modules -ICmd_Item -ICmd_Token_Parser -ITAB_Cmd -ICli_History -ICli_CMD_Processor -ICli_TAB_Processor -I. -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/Test_Cmd_Item_Int_Range.o tests/Test_Cmd_Item_Int_Range.cpp


${TESTDIR}/tests/Test_Cmd_Item_IP4.o: tests/Test_Cmd_Item_IP4.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -ICli_Core -ICli_Input -ICli_Output -ICli_Modules -ICmd_Item -ICmd_Token_Parser -ITAB_Cmd -ICli_History -ICli_CMD_Processor -ICli_TAB_Processor -I. -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/Test_Cmd_Item_IP4.o tests/Test_Cmd_Item_IP4.cpp


${TESTDIR}/tests/Test_Cmd_Item_IP6.o: tests/Test_Cmd_Item_IP6.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -ICli_Core -ICli_Input -ICli_Output -ICli_Modules -ICmd_Item -ICmd_Token_Parser -ITAB_Cmd -ICli_History -ICli_CMD_Processor -ICli_TAB_Processor -I. -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/Test_Cmd_Item_IP6.o tests/Test_Cmd_Item_IP6.cpp


${TESTDIR}/tests/Test_Cmd_Item_MAC.o: tests/Test_Cmd_Item_MAC.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -ICli_Core -ICli_Input -ICli_Output -ICli_Modules -ICmd_Item -ICmd_Token_Parser -ITAB_Cmd -ICli_History -ICli_CMD_Processor -ICli_TAB_Processor -I. -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/Test_Cmd_Item_MAC.o tests/Test_Cmd_Item_MAC.cpp


${TESTDIR}/tests/Test_Cmd_Item_Str.o: tests/Test_Cmd_Item_Str.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -ICli_Core -ICli_Input -ICli_Output -ICli_Modules -ICmd_Item -ICmd_Token_Parser -ITAB_Cmd -ICli_History -ICli_CMD_Processor -ICli_TAB_Processor -I. -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/Test_Cmd_Item_Str.o tests/Test_Cmd_Item_Str.cpp


${TESTDIR}/tests/Test_Cmd_Item_Time.o: tests/Test_Cmd_Item_Time.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -ICli_Core -ICli_Input -ICli_Output -ICli_Modules -ICmd_Item -ICmd_Token_Parser -ITAB_Cmd -ICli_History -ICli_CMD_Processor -ICli_TAB_Processor -I. -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/Test_Cmd_Item_Time.o tests/Test_Cmd_Item_Time.cpp


${TESTDIR}/tests/Test_Cmd_Item_Word.o: tests/Test_Cmd_Item_Word.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -ICli_Core -ICli_Input -ICli_Output -ICli_Modules -ICmd_Item -ICmd_Token_Parser -ITAB_Cmd -ICli_History -ICli_CMD_Processor -ICli_TAB_Processor -I. -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/Test_Cmd_Item_Word.o tests/Test_Cmd_Item_Word.cpp


${TESTDIR}/tests/Test_Cmd_Item_Word_List.o: tests/Test_Cmd_Item_Word_List.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -ICli_Core -ICli_Input -ICli_Output -ICli_Modules -ICmd_Item -ICmd_Token_Parser -ITAB_Cmd -ICli_History -ICli_CMD_Processor -ICli_TAB_Processor -I. -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/Test_Cmd_Item_Word_List.o tests/Test_Cmd_Item_Word_List.cpp


${TESTDIR}/tests/Test_Cmd_Item_Word_Range.o: tests/Test_Cmd_Item_Word_Range.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -ICli_Core -ICli_Input -ICli_Output -ICli_Modules -ICmd_Item -ICmd_Token_Parser -ITAB_Cmd -ICli_History -ICli_CMD_Processor -ICli_TAB_Processor -I. -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/Test_Cmd_Item_Word_Range.o tests/Test_Cmd_Item_Word_Range.cpp


${TESTDIR}/tests/Test_Str_Filter.o: tests/Test_Str_Filter.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -ICli_Core -ICli_Input -ICli_Output -ICli_Modules -ICmd_Item -ICmd_Token_Parser -ITAB_Cmd -ICli_History -ICli_CMD_Processor -ICli_TAB_Processor -I. -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/Test_Str_Filter.o tests/Test_Str_Filter.cpp


${OBJECTDIR}/Cli_Input/Cli_Input_termios_nomain.o: ${OBJECTDIR}/Cli_Input/Cli_Input_termios.o Cli_Input/Cli_Input_termios.cpp 
	${MKDIR} -p ${OBJECTDIR}/Cli_Input
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Cli_Input/Cli_Input_termios.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -ICli_Core -ICli_Input -ICli_Output -ICli_Modules -ICmd_Item -ICmd_Token_Parser -ITAB_Cmd -ICli_History -ICli_CMD_Processor -ICli_TAB_Processor -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Cli_Input/Cli_Input_termios_nomain.o Cli_Input/Cli_Input_termios.cpp;\
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
	    $(COMPILE.cc) -g -ICli_Core -ICli_Input -ICli_Output -ICli_Modules -ICmd_Item -ICmd_Token_Parser -ITAB_Cmd -ICli_History -ICli_CMD_Processor -ICli_TAB_Processor -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cli_core_test_main_nomain.o cli_core_test_main.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/cli_core_test_main.o ${OBJECTDIR}/cli_core_test_main_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f6 || true; \
	    ${TESTDIR}/TestFiles/f8 || true; \
	    ${TESTDIR}/TestFiles/f13 || true; \
	    ${TESTDIR}/TestFiles/f14 || true; \
	    ${TESTDIR}/TestFiles/f12 || true; \
	    ${TESTDIR}/TestFiles/f3 || true; \
	    ${TESTDIR}/TestFiles/f4 || true; \
	    ${TESTDIR}/TestFiles/f5 || true; \
	    ${TESTDIR}/TestFiles/f2 || true; \
	    ${TESTDIR}/TestFiles/f7 || true; \
	    ${TESTDIR}/TestFiles/f10 || true; \
	    ${TESTDIR}/TestFiles/f11 || true; \
	    ${TESTDIR}/TestFiles/f9 || true; \
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
