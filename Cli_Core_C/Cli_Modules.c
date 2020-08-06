/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Cli_Modules.h"

void Cli_Modules_Init_Base(struct Cli_Modules *module_list) {
    module_list->Module_Head = NULL;
    module_list->Module_Tail = NULL;
}

struct Cli_Modules Cli_Modules_Init(void) {
    struct Cli_Modules modules;
    Cli_Modules_Init_Base(&modules);
    return modules;
}

void Cli_Modules_Add(struct Cli_Modules *module_list, struct Cli_Module *module) {
    if(!module_list->Module_Head) {
        module_list->Module_Head = module;
        module_list->Module_Tail = module;
    } else {
        module_list->Module_Tail->Module_Next = module;
        module_list->Module_Tail = module;
    }
}
