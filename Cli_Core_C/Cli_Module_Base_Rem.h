/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Module_Base_Rem.h
 * Author: mike
 *
 * Created on August 6, 2020, 3:37 PM
 */

#ifndef CLI_MODULE_BASE_REM_H
#define CLI_MODULE_BASE_REM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "Cli_Module.h"

#include "Cli_Output_C.h"

#define CLI_MODULE_BASE_REM_STR_REM_SIZE_DEF 32

    struct Cli_Module_Base_Rem {
        struct Cli_Module Module_Base;
        char Str_Rem[CLI_MODULE_BASE_REM_STR_REM_SIZE_DEF];
        struct Cli_Output_C *Cli_Output;
    };

    struct Cli_Module_Base_Rem Cli_Module_Base_Rem_Init(char *str_rem, struct Cli_Output_C *cli_output);

#ifdef __cplusplus
}
#endif

#endif /* CLI_MODULE_BASE_REM_H */
