/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Modules.h
 * Author: mike
 *
 * Created on August 3, 2020, 5:26 PM
 */

#ifndef CLI_MODULES_H
#define CLI_MODULES_H

#ifdef __cplusplus
extern "C" {
#endif
    
#include "Cli_Module.h"

    struct Cli_Modules {
        struct Cli_Module *Module_Head;
        struct Cli_Module *Module_Tail;
    };

    void Cli_Modules_Init_Base(struct Cli_Modules *module_list);
    
    struct Cli_Modules Cli_Modules_Init(void);
    
    void Cli_Modules_Add(struct Cli_Modules *module_list, struct Cli_Module *module);

#ifdef __cplusplus
}
#endif

#endif /* CLI_MODULES_H */
