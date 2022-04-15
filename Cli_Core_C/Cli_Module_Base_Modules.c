/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Cli_Module_Base_Modules.h"

#include "Cli_Cmd_Item_Word.h"
#include "Cli_Cmd_Item_Str.h"

enum Local_CmdID {
    CMD_ID_NO,

    CMD_ID_modules,
    CMD_ID_modules_by_filter,
    CMD_ID_modules_by_filter_print,

    CMD_ID_LAST
};

static void modules_by_filter_print(char *module_filter, struct Cli_Modules *Modules, struct Str_Filter *Module_Str_Filter,
        struct Cli_Output_C *Cli_Output) {
    Cli_Output->Output_NewLine();
    int found = 0;
    struct Cli_Module *module_ptr = Modules->Module_Head;
    while (module_ptr) {
        char *module_name = module_ptr->Name;
        module_ptr = module_ptr->Module_Next;
        if (Str_Filter_Is_Match(Module_Str_Filter, module_filter, module_name)) {
            Cli_Output->Output_Str(module_name);
            Cli_Output->Output_NewLine();
            found = 1;
        }
    }
    if (!found) {
        Cli_Output->Output_Str(module_filter);
        Cli_Output->Output_Str(" - Not Found");
        Cli_Output->Output_NewLine();
    }
}

static int Execute(struct Cli_Module *module, int cmd_id, struct Cli_Cmd *cmd, struct Level_Description_Array *Levels, int is_debug) {
    struct Cli_Module_Base_Modules *module_modules = (struct Cli_Module_Base_Modules *) module;
    struct Level_Description level = Level_Description_Init();
    //string parameter;
    if (Levels->Size > 0) {
        level = Levels->Items[Levels->Size];
        //parameter = level.Parameter;
    }
    switch (cmd_id) {
        case CMD_ID_modules:
            if (is_debug) return 1;
        {
            char *module_filter = "*";
            modules_by_filter_print(module_filter, module_modules->Modules, module_modules->Module_Str_Filter, module_modules->Cli_Output);
        }
            return 1;
        case CMD_ID_modules_by_filter:
        case CMD_ID_modules_by_filter_print:
            if (is_debug) return 1;
        {
            struct Cli_Cmd_Item *cmd_item_ptr_1 = cmd->Item_Head; // modules
            struct Cli_Cmd_Item *cmd_item_ptr_2 = cmd_item_ptr_1->Cmd_Item_Next; // module_name -> module_filter
            char *module_filter = cmd_item_ptr_2->Value_Str;
            modules_by_filter_print(module_filter, module_modules->Modules, module_modules->Module_Str_Filter, module_modules->Cli_Output);
        }
            return 1;
    }

    return 0; // Failed
}

struct Cli_Module_Base_Modules Cli_Module_Base_Modules_Init(struct Cli_Modules *modules,
        struct Str_Filter *module_str_filter, struct Cli_Output_C *cli_output) {
    struct Cli_Module_Base_Modules module_modules;
    struct Cli_Module *module_base = &module_modules.Module_Base;
    Cli_Module_Init_Base(module_base, "Modules");

    module_base->Execute = Execute;

    module_modules.Modules = modules;
    module_modules.Module_Str_Filter = module_str_filter;
    module_modules.Cli_Output = cli_output;

    {
        static struct Cli_Cmd cmd_modules;

        static struct Cli_Cmd_Item cmd_item_modules;

        cmd_modules = Cli_Cmd_Init(CMD_ID_modules, "modules", "modules print (all)");

        cmd_item_modules = Cli_Cmd_Item_Word_Init("modules", "modules");

        Cli_Cmd_Add_Item(&cmd_modules, &cmd_item_modules);

        Cli_Module_Add_Cmd(module_base, &cmd_modules);
    }
    {
        static struct Cli_Cmd cmd_modules_by_filter;

        static struct Cli_Cmd_Item cmd_item_modules;
        static struct Cli_Cmd_Item cmd_item_filter;

        cmd_modules_by_filter = Cli_Cmd_Init(CMD_ID_modules_by_filter, "modules <module_name>", "modules print (by filter)");

        cmd_item_modules = Cli_Cmd_Item_Word_Init("modules", "modules");
        cmd_item_filter = Cli_Cmd_Item_Str_Init("<module_name>", "modules (by filter)");

        Cli_Cmd_Add_Item(&cmd_modules_by_filter, &cmd_item_modules);
        Cli_Cmd_Add_Item(&cmd_modules_by_filter, &cmd_item_filter);

        Cli_Module_Add_Cmd(module_base, &cmd_modules_by_filter);
    }
    {
        static struct Cli_Cmd cmd_modules_by_filter_print;

        static struct Cli_Cmd_Item cmd_item_modules;
        static struct Cli_Cmd_Item cmd_item_filter;
        static struct Cli_Cmd_Item cmd_item_print;

        cmd_modules_by_filter_print = Cli_Cmd_Init(CMD_ID_modules_by_filter_print, "modules <module_name> print", "modules print (by filter)");

        cmd_item_modules = Cli_Cmd_Item_Word_Init("modules", "modules");
        cmd_item_filter = Cli_Cmd_Item_Str_Init("<module_name>", "modules (by filter)");
        cmd_item_print = Cli_Cmd_Item_Word_Init("print", "modules print (by filter)");

        Cli_Cmd_Add_Item(&cmd_modules_by_filter_print, &cmd_item_modules);
        Cli_Cmd_Add_Item(&cmd_modules_by_filter_print, &cmd_item_filter);
        Cli_Cmd_Add_Item(&cmd_modules_by_filter_print, &cmd_item_print);

        Cli_Module_Add_Cmd(module_base, &cmd_modules_by_filter_print);
    }

    return module_modules;
}
