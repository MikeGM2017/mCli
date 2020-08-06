/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Module.h
 * Author: mike
 *
 * Created on August 3, 2020, 4:19 PM
 */

#ifndef CLI_MODULE_H
#define CLI_MODULE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>

#include "Cli_Cmd.h"

#include "Level_Description_Array.h"

#define CLI_MODULE_NAME_SIZE_DEF 32

    struct Cli_Module;

    typedef int ftExecute(struct Cli_Module *module, int cmd_id, struct Cli_Cmd *cmd, struct Level_Description_Array *Levels, int is_debug);

    struct Cli_Module {
        char Name[CLI_MODULE_NAME_SIZE_DEF];
        struct Cli_Cmd *Cmd_Head;
        struct Cli_Cmd *Cmd_Tail;
        struct Cli_Module *Module_Next;

        ftExecute *Execute;
    };

    void Cli_Module_Init_Base(struct Cli_Module *module, char *name);

    struct Cli_Module Cli_Module_Init(char *name);

    void Cli_Module_Add(struct Cli_Module *module_parent, struct Cli_Module *module);

    void Cli_Module_Add_Cmd(struct Cli_Module *module, struct Cli_Cmd *cmd);

#ifdef __cplusplus
}
#endif

#endif /* CLI_MODULE_H */
