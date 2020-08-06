/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_CMD_Processor.h
 * Author: mike
 *
 * Created on August 4, 2020, 4:25 PM
 */

#ifndef CLI_CMD_PROCESSOR_H
#define CLI_CMD_PROCESSOR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>

#include "Cli_Cmd_Privilege_ID.h"
#include "Cli_Modules.h"
#include "Level_Description_Array.h"
#include "Cmd_Token_Parser.h"
#include "Cli_Input_C.h"
#include "Cli_Output_C.h"

#include "Cmd_Item_Valid_Result_Func.h"

#define CLI_CMD_PROCESSOR_STR_REM_SIZE_DEF 32

    struct Cli_CMD_Processor;

    typedef int ftCli_CMD_Processor_Process_Input_Item(struct Cli_CMD_Processor *cmd_processor,
            struct Cli_Input_C_Item *input_item, int is_debug, int *debug_res);

    struct Cli_CMD_Processor {
        enum Cli_Cmd_Privilege_ID User_Privilege;
        struct Cli_Modules *Modules;
        struct Level_Description_Array *Levels;
        struct Cmd_Token_Parser *Parser;
        struct Cli_Input_C *Cli_Input;
        struct Cli_Output_C *Cli_Output;
        char Str_Rem[CLI_CMD_PROCESSOR_STR_REM_SIZE_DEF];

        ftCli_CMD_Processor_Process_Input_Item *Process_Input_Item;
    };

    struct Cli_CMD_Processor Cli_CMD_Processor_Init(enum Cli_Cmd_Privilege_ID user_privilege,
            struct Cli_Modules *modules,
            struct Level_Description_Array *levels,
            struct Cmd_Token_Parser *parser,
            struct Cli_Input_C *cli_input,
            struct Cli_Output_C *cli_output,
            char *str_rem);

#ifdef __cplusplus
}
#endif

#endif /* CLI_CMD_PROCESSOR_H */
