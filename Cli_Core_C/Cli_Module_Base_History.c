/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Cli_Module_Base_History.h"

#include "Cli_Cmd_Item_Word.h"
#include "Cli_Cmd_Item_Str.h"

enum Local_CmdID {
    CMD_ID_NO,

    CMD_ID_history,
    CMD_ID_history_show,
    CMD_ID_history_clear,

    CMD_ID_LAST
};

static void history_show(struct Cli_History *History, struct Cli_Output_C *Cli_Output) {
    Cli_Output->Output_NewLine(Cli_Output);
    Cli_Output->Output_Str(Cli_Output, "History:");
    Cli_Output->Output_NewLine(Cli_Output);
    int history_size = History->History_Size_Get(History);
    int i;
    for (i = 0; i < (history_size - 1); i++) { // @Attention : Not show last cmd!
        Cli_Output->Output_Str(Cli_Output, History->History_Item_Get(History, i));
        Cli_Output->Output_NewLine(Cli_Output);
    }
}

static void history_clear(struct Cli_History *History, struct Cli_Output_C * Cli_Output) {
    History->Clear(History);
}

static int Execute(struct Cli_Module *module, struct Cli_Cmd *cmd, struct Level_Description_Array *Levels, int is_debug) {
    struct Cli_Module_Base_History *module_history = (struct Cli_Module_Base_History *) module;
    struct Level_Description level = Level_Description_Init();
    //string parameter;
    if (Levels->Size > 0) {
        level = Levels->Items[Levels->Size];
        //parameter = level.Parameter;
    }
    switch (cmd->ID) {
        case CMD_ID_history:
        case CMD_ID_history_show:
            if (is_debug) return 1;
            history_show(module_history->History, module_history->Cli_Output);
            return 1;
        case CMD_ID_history_clear:
            if (is_debug) return 1;
            history_clear(module_history->History, module_history->Cli_Output);
            return 1;
    }

    return 0; // Failed
}

struct Cli_Module_Base_History Cli_Module_Base_History_Init(struct Cli_History *history, struct Cli_Output_C *cli_output) {
    struct Cli_Module_Base_History module_history;
    struct Cli_Module *module_base = &module_history.Module_Base;
    Cli_Module_Init_Base(module_base, "History");

    module_base->Execute = Execute;

    module_history.History = history;
    module_history.Cli_Output = cli_output;

    {
        static struct Cli_Cmd cmd_history;

        static struct Cli_Cmd_Item cmd_item_history;

        cmd_history = Cli_Cmd_Init(CMD_ID_history, "history", "history show");

        cmd_item_history = Cli_Cmd_Item_Word_Init("history", "history");

        Cli_Cmd_Add_Item(&cmd_history, &cmd_item_history);

        Cli_Module_Add_Cmd(module_base, &cmd_history);
    }
    {
        static struct Cli_Cmd cmd_history_show;

        static struct Cli_Cmd_Item cmd_item_history;
        static struct Cli_Cmd_Item cmd_item_show;

        cmd_history_show = Cli_Cmd_Init(CMD_ID_history_show, "history show", "history show");

        cmd_item_history = Cli_Cmd_Item_Word_Init("history", "history");
        cmd_item_show = Cli_Cmd_Item_Word_Init("show", "history show");

        Cli_Cmd_Add_Item(&cmd_history_show, &cmd_item_history);
        Cli_Cmd_Add_Item(&cmd_history_show, &cmd_item_show);

        Cli_Module_Add_Cmd(module_base, &cmd_history_show);
    }

    {
        static struct Cli_Cmd cmd_history_clear;

        static struct Cli_Cmd_Item cmd_item_history;
        static struct Cli_Cmd_Item cmd_item_clear;

        cmd_history_clear = Cli_Cmd_Init(CMD_ID_history_clear, "history clear", "history clear");

        cmd_item_history = Cli_Cmd_Item_Word_Init("history", "history");
        cmd_item_clear = Cli_Cmd_Item_Word_Init("clear", "history clear");

        Cli_Cmd_Add_Item(&cmd_history_clear, &cmd_item_history);
        Cli_Cmd_Add_Item(&cmd_history_clear, &cmd_item_clear);

        Cli_Module_Add_Cmd(module_base, &cmd_history_clear);
    }

    return module_history;
}
