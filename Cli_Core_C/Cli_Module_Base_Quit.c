/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Cli_Module_Base_Quit.h"
#include "Cli_Cmd_Item_Word.h"
#include "Cli_Module_Base_Rem.h"

enum Local_CmdID {
    CMD_ID_NO,

    CMD_ID_Q,
    CMD_ID_quit,
    CMD_ID_quit_force,

    CMD_ID_E,
    CMD_ID_exit,
    CMD_ID_exit_force,

    CMD_ID_LAST
};

static int quit_without_prompt(
        // out
        int *cmd_quit) {
    (*cmd_quit) = 1; // Cmd: Quit
    return 1;
}

static int quit_with_prompt(struct Cli_Input_C *Cli_Input, struct Cli_Output_C *Cli_Output,
        char *prompt,
        // out
        int *cmd_quit) {
    Cli_Output->Output_NewLine(Cli_Output);
    Cli_Output->Output_Str(Cli_Output, prompt);
    char c = Cli_Input->Char_Get_Blocked(Cli_Input);
    Cli_Output->Output_NewLine(Cli_Output);
    if (c == 'y' || c == 'Y') {
        (*cmd_quit) = 1; // Cmd: Quit
    }
    return 1;
}

static int Execute(struct Cli_Module *module, struct Cli_Cmd *cmd, struct Level_Description_Array *Levels, int is_debug) {
    struct Cli_Module_Base_Quit *module_quit = (struct Cli_Module_Base_Quit *) module;
    switch (cmd->ID) {
        case CMD_ID_Q:
        case CMD_ID_quit_force:
        case CMD_ID_E:
        case CMD_ID_exit_force:
            if (is_debug) return 1;
        {
            return quit_without_prompt(module_quit->Cmd_Quit);
        }
        case CMD_ID_quit:
            if (is_debug) return 1;
        {
            return quit_with_prompt(module_quit->Cli_Input, module_quit->Cli_Output, "Quit?(y/n):", module_quit->Cmd_Quit);
        }
        case CMD_ID_exit:
            if (is_debug) return 1;
        {
            return quit_with_prompt(module_quit->Cli_Input, module_quit->Cli_Output, "Exit?(y/n):", module_quit->Cmd_Quit);
        }
    }

    return 0; // Failed
}

struct Cli_Module_Base_Quit Cli_Module_Base_Quit_Init(struct Cli_Input_C *cli_input, struct Cli_Output_C *cli_output,
        // out
        int *cmd_quit) {
    struct Cli_Module_Base_Quit module_quit;
    struct Cli_Module *module_base = &module_quit.Module_Base;
    Cli_Module_Init_Base(module_base, "Quit");

    module_base->Execute = Execute;

    module_quit.Cli_Input = cli_input;
    module_quit.Cli_Output = cli_output;
    module_quit.Cmd_Quit = cmd_quit;

    {
        static struct Cli_Cmd cmd_Q;

        static struct Cli_Cmd_Item cmd_item_Q;

        cmd_Q = Cli_Cmd_Init(CMD_ID_Q, "Q", "quit");

        cmd_item_Q = Cli_Cmd_Item_Word_Init("Q", "quit");

        Cli_Cmd_Add_Item(&cmd_Q, &cmd_item_Q);

        Cli_Module_Add_Cmd(module_base, &cmd_Q);
    }

    {
        static struct Cli_Cmd cmd_quit;

        static struct Cli_Cmd_Item cmd_item_quit;

        cmd_quit = Cli_Cmd_Init(CMD_ID_quit, "quit", "quit");

        cmd_item_quit = Cli_Cmd_Item_Word_Init("quit", "quit");

        Cli_Cmd_Add_Item(&cmd_quit, &cmd_item_quit);

        Cli_Module_Add_Cmd(module_base, &cmd_quit);
    }

    {
        static struct Cli_Cmd cmd_quit_force;

        static struct Cli_Cmd_Item cmd_item_quit;
        static struct Cli_Cmd_Item cmd_item_force;

        cmd_quit_force = Cli_Cmd_Init(CMD_ID_quit_force, "quit force", "quit without prompt");

        cmd_item_quit = Cli_Cmd_Item_Word_Init("quit", "quit");
        cmd_item_force = Cli_Cmd_Item_Word_Init("force", "quit without prompt");

        Cli_Cmd_Add_Item(&cmd_quit_force, &cmd_item_quit);
        Cli_Cmd_Add_Item(&cmd_quit_force, &cmd_item_force);

        Cli_Module_Add_Cmd(module_base, &cmd_quit_force);
    }

    {
        static struct Cli_Cmd cmd_E;

        static struct Cli_Cmd_Item cmd_item_E;

        cmd_E = Cli_Cmd_Init(CMD_ID_E, "E", "exit");

        cmd_item_E = Cli_Cmd_Item_Word_Init("E", "exit");

        Cli_Cmd_Add_Item(&cmd_E, &cmd_item_E);

        Cli_Module_Add_Cmd(module_base, &cmd_E);
    }

    {
        static struct Cli_Cmd cmd_exit;

        static struct Cli_Cmd_Item cmd_item_exit;

        cmd_exit = Cli_Cmd_Init(CMD_ID_exit, "exit", "exit");

        cmd_item_exit = Cli_Cmd_Item_Word_Init("exit", "exit");

        Cli_Cmd_Add_Item(&cmd_exit, &cmd_item_exit);

        Cli_Module_Add_Cmd(module_base, &cmd_exit);
    }

    {
        static struct Cli_Cmd cmd_exit_force;

        static struct Cli_Cmd_Item cmd_item_exit;
        static struct Cli_Cmd_Item cmd_item_force;

        cmd_exit_force = Cli_Cmd_Init(CMD_ID_quit_force, "exit force", "exit without prompt");

        cmd_item_exit = Cli_Cmd_Item_Word_Init("exit", "exit");
        cmd_item_force = Cli_Cmd_Item_Word_Init("force", "exit without prompt");

        Cli_Cmd_Add_Item(&cmd_exit_force, &cmd_item_exit);
        Cli_Cmd_Add_Item(&cmd_exit_force, &cmd_item_force);

        Cli_Module_Add_Cmd(module_base, &cmd_exit_force);
    }

    return module_quit;
}
