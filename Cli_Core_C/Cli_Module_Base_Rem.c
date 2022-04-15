/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Cli_Module_Base_Rem.h"

#include "Cli_Cmd_Item_Rem.h"

enum Local_CmdID {
    CMD_ID_NO,

    CMD_ID_rem,

    CMD_ID_LAST
};

int rem(struct Cli_Output_C *Cli_Output, char *s_rem) {
    Cli_Output->Output_NewLine(Cli_Output);
    Cli_Output->Output_Str(Cli_Output, s_rem);
    Cli_Output->Output_NewLine(Cli_Output);
    return 1;
}

static int Execute(struct Cli_Module *module, int cmd_id, struct Cli_Cmd *cmd, struct Level_Description_Array *Levels, int is_debug) {
    struct Cli_Module_Base_Rem *module_rem = (struct Cli_Module_Base_Rem *) module;
    switch (cmd_id) {
        case CMD_ID_rem:
            if (is_debug) return 1;
        {
            char *s_rem = cmd->Item_Head->Value_Str;
            return rem(module_rem->Cli_Output, s_rem);
        }
    }

    return 0; // Failed
}

struct Cli_Module_Base_Rem Cli_Module_Base_Rem_Init(char *str_rem, struct Cli_Output_C *cli_output) {
    struct Cli_Module_Base_Rem module_rem;
    struct Cli_Module *module_base = &module_rem.Module_Base;
    Cli_Module_Init_Base(module_base, "Rem");

    module_base->Execute = Execute;

    int len = CLI_MODULE_BASE_REM_STR_REM_SIZE_DEF - 1;
    strncpy(module_rem.Str_Rem, str_rem, len);
    module_rem.Str_Rem[len] = '\0';

    module_rem.Cli_Output = cli_output;

    {
        static struct Cli_Cmd cmd_rem;

        static struct Cli_Cmd_Item cmd_item_rem;

        cmd_rem = Cli_Cmd_Init(CMD_ID_rem, str_rem, "comment (for use in scripts)");

        cmd_item_rem = Cli_Cmd_Item_Rem_Init(str_rem, "comment");

        Cli_Cmd_Add_Item(&cmd_rem, &cmd_item_rem);

        Cli_Module_Add_Cmd(module_base, &cmd_rem);
    }

    return module_rem;
}
