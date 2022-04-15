/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Module_Base_History.h
 * Author: mike
 *
 * Created on June 10, 2021, 12:04 PM
 */

#ifndef CLI_MODULE_BASE_HISTORY_H
#define CLI_MODULE_BASE_HISTORY_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

#include "Cli_Module.h"

#include "Cli_History.h"
#include "Cli_Output_C.h"

    struct Cli_Module_Base_History {
        struct Cli_Module Module_Base;
        struct Cli_History *History;
        struct Cli_Output_C *Cli_Output;
    };

    struct Cli_Module_Base_History Cli_Module_Base_History_Init(struct Cli_History *history, struct Cli_Output_C *cli_output);

#ifdef __cplusplus
}
#endif

#endif /* CLI_MODULE_BASE_HISTORY_H */
