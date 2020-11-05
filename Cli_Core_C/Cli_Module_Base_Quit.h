/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Module_Base_Quit.h
 * Author: mike
 *
 * Created on November 5, 2020, 11:27 AM
 */

#ifndef CLI_MODULE_BASE_QUIT_H
#define CLI_MODULE_BASE_QUIT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "Cli_Module.h"

#include "Cli_Input_C.h"
#include "Cli_Output_C.h"

    struct Cli_Module_Base_Quit {
        struct Cli_Module Module_Base;
        struct Cli_Input_C *Cli_Input;
        struct Cli_Output_C *Cli_Output;
        int *Cmd_Quit;
    };

    struct Cli_Module_Base_Quit Cli_Module_Base_Quit_Init(
            struct Cli_Input_C *cli_input, struct Cli_Output_C *cli_output,
            int *cmd_quit);

#ifdef __cplusplus
}
#endif

#endif /* CLI_MODULE_BASE_QUIT_H */
