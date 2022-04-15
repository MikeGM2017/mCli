/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Module_Base_Modules.h
 * Author: mike
 *
 * Created on June 10, 2021, 2:49 PM
 */

#ifndef CLI_MODULE_BASE_MODULES_H
#define CLI_MODULE_BASE_MODULES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "Cli_Module.h"

#include "Cli_Modules.h"
#include "Str_Filter.h"
#include "Cli_Output_C.h"

    struct Cli_Module_Base_Modules {
        struct Cli_Module Module_Base;
        struct Cli_Modules *Modules;
        struct Str_Filter *Module_Str_Filter;
        struct Cli_Output_C *Cli_Output;
    };

    struct Cli_Module_Base_Modules Cli_Module_Base_Modules_Init(struct Cli_Modules *modules,
            struct Str_Filter *module_str_filter, struct Cli_Output_C *cli_output);

#ifdef __cplusplus
}
#endif

#endif /* CLI_MODULE_BASE_MODULES_H */
