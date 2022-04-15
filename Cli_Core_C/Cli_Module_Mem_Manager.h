/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Module_Mem_Manager.h
 * Author: mike
 *
 * Created on June 10, 2021, 9:14 AM
 */

#ifndef CLI_MODULE_MEM_MANAGER_H
#define CLI_MODULE_MEM_MANAGER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

#include "Cli_Module.h"

#include "Mem_Manager_C.h"
#include "Cli_Output_C.h"

    struct Cli_Module_Mem_Manager {
        struct Cli_Module Module_Base;
        struct Mem_Manager_C *Mem_Manager;
        struct Cli_Output_C *Cli_Output;
    };

    struct Cli_Module_Mem_Manager Cli_Module_Mem_Manager_Init(struct Mem_Manager_C *mem_manager, struct Cli_Output_C *cli_output);

#ifdef __cplusplus
}
#endif

#endif /* CLI_MODULE_MEM_MANAGER_H */
