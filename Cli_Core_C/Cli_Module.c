/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Cli_Module.h"

static int Execute(struct Cli_Module *module, struct Cli_Cmd *cmd, struct Level_Description_Array *Levels, int is_debug) {
    return 0; /*Failed*/
}

void Cli_Module_Init_Base(struct Cli_Module *module, char *name) {
    module->Cmd_Head = NULL;
    module->Cmd_Tail = NULL;
    module->Module_Next = NULL;
    if (!name) {
        int len = CLI_MODULE_NAME_SIZE_DEF - 1;
        strncpy(module->Name, "Base", len);
        module->Name[len] = '\0';
    } else {
        int len = CLI_MODULE_NAME_SIZE_DEF - 1;
        strncpy(module->Name, name, len);
        module->Name[len] = '\0';
    }

    module->Execute = Execute;
}

struct Cli_Module Cli_Module_Init(char *name) {
    struct Cli_Module module;
    Cli_Module_Init_Base(&module, name);
    return module;
}

void Cli_Module_Add(struct Cli_Module *module_parent, struct Cli_Module *module) {
    module_parent->Module_Next = module;
    module->Module_Next = NULL;
}

void Cli_Module_Add_Cmd(struct Cli_Module *module, struct Cli_Cmd *cmd) {
    if (!module->Cmd_Head) {
        module->Cmd_Head = cmd;
        module->Cmd_Tail = cmd;
    } else {
        module->Cmd_Tail->Cmd_Next = cmd;
        module->Cmd_Tail = cmd;
    }
}
