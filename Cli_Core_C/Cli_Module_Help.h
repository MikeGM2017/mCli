/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Module_Help.h
 * Author: mike
 *
 * Created on August 3, 2020, 4:33 PM
 */

#ifndef CLI_MODULE_HELP_H
#define CLI_MODULE_HELP_H

#include <stdio.h>

#include "Cli_Module.h"

#include "Cli_Cmd_Privilege_ID.h"
#include "Cli_Modules.h"
#include "Str_Filter.h"
#include "Cli_Output_C.h"

#ifdef __cplusplus
extern "C" {
#endif

    struct Cli_Module_Help {
        struct Cli_Module Module_Base;
        enum Cli_Cmd_Privilege_ID User_Privilege;
        struct Cli_Modules *Modules;
        struct Str_Filter *Help_Str_Filter;
        struct Cli_Output_C *Cli_Output;
    };

    struct Cli_Module_Help Cli_Module_Help_Init(enum Cli_Cmd_Privilege_ID user_privilege, struct Cli_Modules *modules,
            struct Str_Filter *help_str_filter, struct Cli_Output_C *cli_output);

#ifdef __cplusplus
}
#endif

#endif /* CLI_MODULE_HELP_H */
