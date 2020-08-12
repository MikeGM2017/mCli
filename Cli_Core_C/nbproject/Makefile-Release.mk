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
	${OBJECTDIR}/Cli_CMD_Processor.o \
	${OBJECTDIR}/Cli_Cmd.o \
	${OBJECTDIR}/Cli_Cmd_Item.o \
	${OBJECTDIR}/Cli_Cmd_Item_Rem.o \
	${OBJECTDIR}/Cli_Cmd_Item_Str.o \
	${OBJECTDIR}/Cli_Cmd_Item_Word.o \
	${OBJECTDIR}/Cli_Core.o \
	${OBJECTDIR}/Cli_History.o \
	${OBJECTDIR}/Cli_Input_C.o \
	${OBJECTDIR}/Cli_Input_C_Item.o \
	${OBJECTDIR}/Cli_Input_C_termios.o \
	${OBJECTDIR}/Cli_Module.o \
	${OBJECTDIR}/Cli_Module_Base_Help.o \
	${OBJECTDIR}/Cli_Module_Base_Rem.o \
	${OBJECTDIR}/Cli_Modules.o \
	${OBJECTDIR}/Cli_Output_C_printf.o \
	${OBJECTDIR}/Cli_TAB_Processor.o \
	${OBJECTDIR}/Cmd_Item_Valid_Result_Func.o \
	${OBJECTDIR}/Cmd_Token.o \
	${OBJECTDIR}/Cmd_Token_Array.o \
	${OBJECTDIR}/Cmd_Token_Parser.o \
	${OBJECTDIR}/Cmd_Token_Parser_Char_Type_Func.o \
	${OBJECTDIR}/Level_Description.o \
	${OBJECTDIR}/Level_Description_Array.o \
	${OBJECTDIR}/Str_Filter.o \
	${OBJECTDIR}/Str_List_Item.o \
	${OBJECTDIR}/TAB_Cmd.o \
	${OBJECTDIR}/cli_core_c_test_main.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cli_core_c

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cli_core_c: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cli_core_c ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/Cli_CMD_Processor.o: Cli_CMD_Processor.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Cli_CMD_Processor.o Cli_CMD_Processor.c

${OBJECTDIR}/Cli_Cmd.o: Cli_Cmd.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Cli_Cmd.o Cli_Cmd.c

${OBJECTDIR}/Cli_Cmd_Item.o: Cli_Cmd_Item.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Cli_Cmd_Item.o Cli_Cmd_Item.c

${OBJECTDIR}/Cli_Cmd_Item_Rem.o: Cli_Cmd_Item_Rem.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Cli_Cmd_Item_Rem.o Cli_Cmd_Item_Rem.c

${OBJECTDIR}/Cli_Cmd_Item_Str.o: Cli_Cmd_Item_Str.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Cli_Cmd_Item_Str.o Cli_Cmd_Item_Str.c

${OBJECTDIR}/Cli_Cmd_Item_Word.o: Cli_Cmd_Item_Word.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Cli_Cmd_Item_Word.o Cli_Cmd_Item_Word.c

${OBJECTDIR}/Cli_Core.o: Cli_Core.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Cli_Core.o Cli_Core.c

${OBJECTDIR}/Cli_History.o: Cli_History.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Cli_History.o Cli_History.c

${OBJECTDIR}/Cli_Input_C.o: Cli_Input_C.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Cli_Input_C.o Cli_Input_C.c

${OBJECTDIR}/Cli_Input_C_Item.o: Cli_Input_C_Item.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Cli_Input_C_Item.o Cli_Input_C_Item.c

${OBJECTDIR}/Cli_Input_C_termios.o: Cli_Input_C_termios.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Cli_Input_C_termios.o Cli_Input_C_termios.c

${OBJECTDIR}/Cli_Module.o: Cli_Module.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Cli_Module.o Cli_Module.c

${OBJECTDIR}/Cli_Module_Base_Help.o: Cli_Module_Base_Help.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Cli_Module_Base_Help.o Cli_Module_Base_Help.c

${OBJECTDIR}/Cli_Module_Base_Rem.o: Cli_Module_Base_Rem.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Cli_Module_Base_Rem.o Cli_Module_Base_Rem.c

${OBJECTDIR}/Cli_Modules.o: Cli_Modules.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Cli_Modules.o Cli_Modules.c

${OBJECTDIR}/Cli_Output_C_printf.o: Cli_Output_C_printf.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Cli_Output_C_printf.o Cli_Output_C_printf.c

${OBJECTDIR}/Cli_TAB_Processor.o: Cli_TAB_Processor.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Cli_TAB_Processor.o Cli_TAB_Processor.c

${OBJECTDIR}/Cmd_Item_Valid_Result_Func.o: Cmd_Item_Valid_Result_Func.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Cmd_Item_Valid_Result_Func.o Cmd_Item_Valid_Result_Func.c

${OBJECTDIR}/Cmd_Token.o: Cmd_Token.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Cmd_Token.o Cmd_Token.c

${OBJECTDIR}/Cmd_Token_Array.o: Cmd_Token_Array.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Cmd_Token_Array.o Cmd_Token_Array.c

${OBJECTDIR}/Cmd_Token_Parser.o: Cmd_Token_Parser.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Cmd_Token_Parser.o Cmd_Token_Parser.c

${OBJECTDIR}/Cmd_Token_Parser_Char_Type_Func.o: Cmd_Token_Parser_Char_Type_Func.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Cmd_Token_Parser_Char_Type_Func.o Cmd_Token_Parser_Char_Type_Func.c

${OBJECTDIR}/Level_Description.o: Level_Description.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Level_Description.o Level_Description.c

${OBJECTDIR}/Level_Description_Array.o: Level_Description_Array.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Level_Description_Array.o Level_Description_Array.c

${OBJECTDIR}/Str_Filter.o: Str_Filter.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Str_Filter.o Str_Filter.c

${OBJECTDIR}/Str_List_Item.o: Str_List_Item.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Str_List_Item.o Str_List_Item.c

${OBJECTDIR}/TAB_Cmd.o: TAB_Cmd.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/TAB_Cmd.o TAB_Cmd.c

${OBJECTDIR}/cli_core_c_test_main.o: cli_core_c_test_main.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cli_core_c_test_main.o cli_core_c_test_main.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cli_core_c

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
