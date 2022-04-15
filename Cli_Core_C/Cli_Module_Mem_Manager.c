/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Cli_Module_Mem_Manager.h"

#include "Cli_Cmd_Item_Word.h"

enum Local_Cmd_ID {
    CMD_ID_NO,

    CMD_ID_M,
    CMD_ID_mem,
    CMD_ID_mem_info,

    CMD_ID_LAST
};

static void mem_info(struct Mem_Manager_C *Mem_Manager, struct Cli_Output_C *Cli_Output) {
    const int s_size = 1000;
    char s[s_size];
    Mem_Manager->Mem_Manager_Info(Mem_Manager, s, s_size);
    Cli_Output->Output_NewLine();
    Cli_Output->Output_Str(s);
    Cli_Output->Output_NewLine();
}

static int Execute(struct Cli_Module *module, int cmd_id, struct Cli_Cmd *cmd, struct Level_Description_Array *Levels, int is_debug) {
    struct Cli_Module_Mem_Manager *module_mem_manager = (struct Cli_Module_Mem_Manager *) module;
    struct Level_Description level = Level_Description_Init();
    //string parameter;
    if (Levels->Size > 0) {
        level = Levels->Items[Levels->Size];
        //parameter = level.Parameter;
    }
    switch (cmd_id) {
        case CMD_ID_M:
        case CMD_ID_mem:
        case CMD_ID_mem_info:
            if (is_debug) return 1;
        {
            mem_info(module_mem_manager->Mem_Manager, module_mem_manager->Cli_Output);
        }
            return 1;
    }

    return 0; // Failed
}

struct Cli_Module_Mem_Manager Cli_Module_Mem_Manager_Init(struct Mem_Manager_C *mem_manager, struct Cli_Output_C *cli_output) {
    struct Cli_Module_Mem_Manager module_mem_manager;
    struct Cli_Module *module_base = &module_mem_manager.Module_Base;
    Cli_Module_Init_Base(module_base, "Mem_Manager");

    module_base->Execute = Execute;

    module_mem_manager.Mem_Manager = mem_manager;
    module_mem_manager.Cli_Output = cli_output;

    {
        static struct Cli_Cmd cmd_M;

        static struct Cli_Cmd_Item cmd_item_M;

        cmd_M = Cli_Cmd_Init(CMD_ID_mem_info, "M", "show memory manager information");

        cmd_item_M = Cli_Cmd_Item_Word_Init("M", "show memory manager");

        Cli_Cmd_Add_Item(&cmd_M, &cmd_item_M);

        Cli_Module_Add_Cmd(module_base, &cmd_M);
    } // CMD_ID_M
    {
        static struct Cli_Cmd cmd_mem;

        static struct Cli_Cmd_Item cmd_item_mem;

        cmd_mem = Cli_Cmd_Init(CMD_ID_mem, "mem", "show memory manager information");

        cmd_item_mem = Cli_Cmd_Item_Word_Init("mem", "show memory manager");

        Cli_Cmd_Add_Item(&cmd_mem, &cmd_item_mem);

        Cli_Module_Add_Cmd(module_base, &cmd_mem);
    } // CMD_ID_mem
    {
        static struct Cli_Cmd cmd_mem_info;

        static struct Cli_Cmd_Item cmd_item_mem;
        static struct Cli_Cmd_Item cmd_item_info;

        cmd_mem_info = Cli_Cmd_Init(CMD_ID_mem_info, "mem info", "show memory manager information");

        cmd_item_mem = Cli_Cmd_Item_Word_Init("mem", "show memory manager");
        cmd_item_info = Cli_Cmd_Item_Word_Init("info", "show memory manager information");

        Cli_Cmd_Add_Item(&cmd_mem_info, &cmd_item_mem);
        Cli_Cmd_Add_Item(&cmd_mem_info, &cmd_item_info);

        Cli_Module_Add_Cmd(module_base, &cmd_mem_info);
    } // CMD_ID_mem_info

    return module_mem_manager;
}