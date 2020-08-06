/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Cli_Module_Base_Help.h"

#include "Cli_Cmd_Item_Word.h"
#include "Cli_Cmd_Item_Str.h"

enum Local_Cmd_ID {
    CMD_ID_NO,

    CMD_ID_help_H,
    CMD_ID_help,
    CMD_ID_help_verbose,

    CMD_ID_help_full,
    CMD_ID_help_full_verbose,

    CMD_ID_help_module_module_name,
    CMD_ID_help_module_module_name_verbose,

    CMD_ID_help_command,
    CMD_ID_help_command_verbose,

    CMD_ID_LAST
};

static int HELP_Cmd_Ptr_Check_By_Level(struct Cli_Cmd *cmd_ptr, enum Cli_Cmd_Privilege_ID user_privilege, char *level,
        int is_full, int is_module_full) {
    if (cmd_ptr && user_privilege <= cmd_ptr->Privilege) {
        if (is_full) return 1;
        if (is_module_full) return 1;
        if (cmd_ptr->Is_Global) return 1;
        if (!strcmp(cmd_ptr->Level, level)) return 1;
    }
    return 0;
}

static int Help_Cli_Modules_Get_Len(int user_privilege, struct Cli_Modules *modules,
        char *level,
        int is_full, int is_verbose, int is_module_full,
        char *module_filter, char *command_filter, struct Str_Filter *str_filter) {
    int len_max = 0;

    struct Cli_Module *module_ptr = modules->Module_Head;
    while (module_ptr) {
        {
            if (is_full || Str_Filter_Is_Match(str_filter, module_filter, module_ptr->Name)) {
                struct Cli_Cmd *cmd_ptr = module_ptr->Cmd_Head;
                while (cmd_ptr) {
                    {
                        int is_cmd_prt_valid = HELP_Cmd_Ptr_Check_By_Level(cmd_ptr, user_privilege, level, is_full, is_module_full);
                        if (is_cmd_prt_valid && Str_Filter_Is_Match(str_filter, command_filter, cmd_ptr->Item_Head->Text)) {
                            int len = 0;
                            if (level[0] == '\0') {
                                if (cmd_ptr->Level[0] != '\0') {
                                    int len_level = strlen(cmd_ptr->Level);
                                    if (len_level > 0)
                                        len += len_level + 3; // "[" + ... + "] " - OnHelp_CliModules(...)
                                }
                            }
                            len += strlen(cmd_ptr->Text);
                            if (len_max < len)
                                len_max = len;
                            if (is_verbose) {
                                struct Cli_Cmd_Item *cmd_item_ptr = cmd_ptr->Item_Head;
                                while (cmd_item_ptr) {
                                    {
                                        len = 1 + strlen(cmd_item_ptr->Text); // " " + ...
                                        if (len_max < len)
                                            len_max = len;
                                    }
                                    cmd_item_ptr = cmd_item_ptr->Cmd_Item_Next;
                                }
                            }
                        }
                    }
                    cmd_ptr = cmd_ptr->Cmd_Next;
                }
            }
        }
        module_ptr = module_ptr->Module_Next;
    }

    return len_max;
}

static void Help_Cli_Modules_Print(int user_privilege, struct Cli_Modules *modules,
        char *level,
        int is_full, int is_verbose, int is_module_full,
        char *module_filter, char *command_filter, struct Str_Filter *str_filter,
        int len_max, int *modules_count, int *commands_count,
        struct Cli_Output_C *Cli_Output) {

    Cli_Output->Output_NewLine();

    struct Cli_Module *module_ptr = modules->Module_Head;
    while (module_ptr) {
        {
            if (is_full || Str_Filter_Is_Match(str_filter, module_filter, module_ptr->Name)) {
                (*modules_count)++;
                struct Cli_Cmd *cmd_ptr = module_ptr->Cmd_Head;
                while (cmd_ptr) {
                    {
                        int is_cmd_prt_valid = HELP_Cmd_Ptr_Check_By_Level(cmd_ptr, user_privilege, level, is_full, is_module_full);
                        if (is_cmd_prt_valid && Str_Filter_Is_Match(str_filter, command_filter, cmd_ptr->Item_Head->Text)) {
                            if (level[0] == '\0') {
                                if (cmd_ptr->Level[0] != '\0') {
                                    Cli_Output->Output_Str("[");
                                    Cli_Output->Output_Str(cmd_ptr->Level);
                                    Cli_Output->Output_Str("] ");
                                }
                            }
                            Cli_Output->Output_Str(cmd_ptr->Text);
                            int text_len = strlen(cmd_ptr->Text);
                            //if (text_len < len_max) {
                            if (text_len < len_max + 1) { // @Attention: len_max + 1 - cmd_item adds: ' '
                                int i;
                                //for (i = text_len; i < len_max; i++) {
                                for (i = text_len; i < len_max + 1; i++) { // @Attention: len_max + 1 - cmd_item adds: ' '
                                    Cli_Output->Output_Char(' ');
                                }
                            }
                            Cli_Output->Output_Str(" - ");
                            Cli_Output->Output_Str(cmd_ptr->Help);
                            Cli_Output->Output_NewLine();
                            (*commands_count)++;
                            if (is_verbose) {
                                struct Cli_Cmd_Item *cmd_item_ptr = cmd_ptr->Item_Head;
                                while (cmd_item_ptr) {
                                    {
                                        Cli_Output->Output_Str(" ");
                                        Cli_Output->Output_Str(cmd_item_ptr->Text);
                                        int text_len = strlen(cmd_item_ptr->Text);
                                        if (text_len < len_max) {
                                            int i;
                                            for (i = text_len; i < len_max; i++) {
                                                Cli_Output->Output_Char(' ');
                                            }
                                        }
                                        Cli_Output->Output_Str(" - ");
                                        Cli_Output->Output_Str(cmd_item_ptr->Help);
                                        Cli_Output->Output_NewLine();
                                    }
                                    cmd_item_ptr = cmd_item_ptr->Cmd_Item_Next;
                                }
                            }
                        }
                    }
                    cmd_ptr = cmd_ptr->Cmd_Next;
                }
            }
        }
        module_ptr = module_ptr->Module_Next;
    }

}

static void help(struct Cli_Module_Base_Help *module_help,
        char *level, int is_full, int is_verbose, int is_module_full,
        char *module_filter, char *command_filter, struct Cli_Output_C *Cli_Output) {
    int modules_count = 0;
    int commands_count = 0;
    int len_max = 0;
    int len;

    len = Help_Cli_Modules_Get_Len(module_help->User_Privilege, module_help->Modules, level,
            is_full, is_verbose, is_module_full,
            module_filter, command_filter, module_help->Help_Str_Filter);
    if (len_max < len)
        len_max = len;

    Help_Cli_Modules_Print(module_help->User_Privilege, module_help->Modules, level,
            is_full, is_verbose, is_module_full,
            module_filter, command_filter, module_help->Help_Str_Filter,
            len_max, &modules_count, &commands_count,
            Cli_Output);

    if (modules_count == 0) {
        Cli_Output->Output_Str("modules \"");
        Cli_Output->Output_Str(module_filter);
        Cli_Output->Output_Str("\" - not found");
        Cli_Output->Output_NewLine();
    } else if (commands_count == 0) {
        Cli_Output->Output_Str("commands \"");
        Cli_Output->Output_Str(command_filter);
        Cli_Output->Output_Str("\" - not found");
        Cli_Output->Output_NewLine();
    } else {
        //Cli_Output->Output_NewLine();
    }

}

static int Execute(struct Cli_Module *module, int cmd_id, struct Cli_Cmd *cmd, struct Level_Description_Array *Levels, int is_debug) {
    struct Cli_Module_Base_Help *module_help = (struct Cli_Module_Base_Help *) module;
    struct Level_Description level = Level_Description_Init();
    //string parameter;
    if (Levels->Size > 0) {
        level = Levels->Items[Levels->Size];
        //parameter = level.Parameter;
    }
    switch (cmd_id) {
        case CMD_ID_help_H:
        case CMD_ID_help:
            if (is_debug) return 1;
        {
            int is_full = 0;
            int is_verbose = 0;
            int is_module_full = 0;
            char *module_filter = "*";
            char *command_filter = "*";
            help(module_help, level.Level,
                    is_full, is_verbose, is_module_full,
                    module_filter, command_filter,
                    module_help->Cli_Output);
        }
            return 1;
        case CMD_ID_help_verbose:
            if (is_debug) return 1;
        {
            int is_full = 0;
            int is_verbose = 1;
            int is_module_full = 0;
            char *module_filter = "*";
            char *command_filter = "*";
            help(module_help, level.Level,
                    is_full, is_verbose, is_module_full,
                    module_filter, command_filter,
                    module_help->Cli_Output);
        }
            return 1;

        case CMD_ID_help_full:
            if (is_debug) return 1;
        {
            int is_full = 1;
            int is_verbose = 0;
            int is_module_full = 0;
            char *module_filter = "*";
            char *command_filter = "*";
            help(module_help, level.Level,
                    is_full, is_verbose, is_module_full,
                    module_filter, command_filter,
                    module_help->Cli_Output);
        }
            return 1;
        case CMD_ID_help_full_verbose:
            if (is_debug) return 1;
        {
            int is_full = 1;
            int is_verbose = 1;
            int is_module_full = 0;
            char *module_filter = "*";
            char *command_filter = "*";
            help(module_help, level.Level,
                    is_full, is_verbose, is_module_full,
                    module_filter, command_filter,
                    module_help->Cli_Output);
        }
            return 1;

        case CMD_ID_help_module_module_name:
            if (is_debug) return 1;
        {
            struct Cli_Cmd_Item *cmd_item_ptr_1 = cmd->Item_Head; // help
            struct Cli_Cmd_Item *cmd_item_ptr_2 = cmd_item_ptr_1->Cmd_Item_Next; // module
            struct Cli_Cmd_Item *cmd_item_ptr_3 = cmd_item_ptr_2->Cmd_Item_Next; // module_name -> module_filter

            int is_full = 0;
            int is_verbose = 0;
            int is_module_full = 0;
            char *module_filter = cmd_item_ptr_3->Value_Str;
            char *command_filter = "*";
            help(module_help, level.Level,
                    is_full, is_verbose, is_module_full,
                    module_filter, command_filter,
                    module_help->Cli_Output);
        }
            return 1;
        case CMD_ID_help_module_module_name_verbose:
            if (is_debug) return 1;
        {
            struct Cli_Cmd_Item *cmd_item_ptr_1 = cmd->Item_Head; // help
            struct Cli_Cmd_Item *cmd_item_ptr_2 = cmd_item_ptr_1->Cmd_Item_Next; // module
            struct Cli_Cmd_Item *cmd_item_ptr_3 = cmd_item_ptr_2->Cmd_Item_Next; // module_name -> module_filter

            int is_full = 0;
            int is_verbose = 1;
            int is_module_full = 0;
            char *module_filter = cmd_item_ptr_3->Value_Str;
            char *command_filter = "*";
            help(module_help, level.Level,
                    is_full, is_verbose, is_module_full,
                    module_filter, command_filter,
                    module_help->Cli_Output);
        }
            return 1;

        case CMD_ID_help_command:
            if (is_debug) return 1;
        {
            struct Cli_Cmd_Item *cmd_item_ptr_1 = cmd->Item_Head; // help
            struct Cli_Cmd_Item *cmd_item_ptr_2 = cmd_item_ptr_1->Cmd_Item_Next; // <command>

            int is_full = 0;
            int is_verbose = 0;
            int is_module_full = 0;
            char *module_filter = "*";
            char *command_filter = cmd_item_ptr_2->Value_Str;
            help(module_help, level.Level,
                    is_full, is_verbose, is_module_full,
                    module_filter, command_filter,
                    module_help->Cli_Output);
        }
            return 1;
        case CMD_ID_help_command_verbose:
            if (is_debug) return 1;
        {
            struct Cli_Cmd_Item *cmd_item_ptr_1 = cmd->Item_Head; // help
            struct Cli_Cmd_Item *cmd_item_ptr_2 = cmd_item_ptr_1->Cmd_Item_Next; // <command>

            int is_full = 0;
            int is_verbose = 1;
            int is_module_full = 0;
            char *module_filter = "*";
            char *command_filter = cmd_item_ptr_2->Value_Str;
            help(module_help, level.Level,
                    is_full, is_verbose, is_module_full,
                    module_filter, command_filter,
                    module_help->Cli_Output);
        }
            return 1;
    }

    return 0; // Failed
}

struct Cli_Module_Base_Help Cli_Module_Base_Help_Init(enum Cli_Cmd_Privilege_ID user_privilege, struct Cli_Modules *modules,
        struct Str_Filter *help_str_filter, struct Cli_Output_C *cli_output) {
    struct Cli_Module_Base_Help module_help;
    struct Cli_Module *module_base = &module_help.Module_Base;
    Cli_Module_Init_Base(module_base, "Help");

    module_base->Execute = Execute;

    module_help.User_Privilege = user_privilege;
    module_help.Modules = modules;
    module_help.Help_Str_Filter = help_str_filter;
    module_help.Cli_Output = cli_output;

    {
        static struct Cli_Cmd cmd_H;

        static struct Cli_Cmd_Item cmd_item_H;

        cmd_H = Cli_Cmd_Init(CMD_ID_help_H, "H", "show help");

        cmd_item_H = Cli_Cmd_Item_Word_Init("H", "show help");

        Cli_Cmd_Add_Item(&cmd_H, &cmd_item_H);

        Cli_Module_Add_Cmd(module_base, &cmd_H);
    }

    {
        static struct Cli_Cmd cmd_help;

        static struct Cli_Cmd_Item cmd_item_help;

        cmd_help = Cli_Cmd_Init(CMD_ID_help, "help", "show help");

        cmd_item_help = Cli_Cmd_Item_Word_Init("help", "show help");

        Cli_Cmd_Add_Item(&cmd_help, &cmd_item_help);

        Cli_Module_Add_Cmd(module_base, &cmd_help);
    }

    {
        static struct Cli_Cmd cmd_help_verbose;

        static struct Cli_Cmd_Item cmd_item_help;
        static struct Cli_Cmd_Item cmd_item_verbose;

        cmd_help_verbose = Cli_Cmd_Init(CMD_ID_help_verbose, "help verbose", "show commands with arguments information");

        cmd_item_help = Cli_Cmd_Item_Word_Init("help", "show help");
        cmd_item_verbose = Cli_Cmd_Item_Word_Init("verbose", "show all arguments information");

        Cli_Cmd_Add_Item(&cmd_help_verbose, &cmd_item_help);
        Cli_Cmd_Add_Item(&cmd_help_verbose, &cmd_item_verbose);

        Cli_Module_Add_Cmd(module_base, &cmd_help_verbose);
    }

    {
        static struct Cli_Cmd cmd_help_full;

        static struct Cli_Cmd_Item cmd_item_help;
        static struct Cli_Cmd_Item cmd_item_full;

        cmd_help_full = Cli_Cmd_Init(CMD_ID_help_full, "help full", "show all commands");

        cmd_item_help = Cli_Cmd_Item_Word_Init("help", "show help");
        cmd_item_full = Cli_Cmd_Item_Word_Init("full", "show all commands");

        Cli_Cmd_Add_Item(&cmd_help_full, &cmd_item_help);
        Cli_Cmd_Add_Item(&cmd_help_full, &cmd_item_full);

        Cli_Module_Add_Cmd(module_base, &cmd_help_full);
    }

    {
        static struct Cli_Cmd cmd_help_full_verbose;

        static struct Cli_Cmd_Item cmd_item_help;
        static struct Cli_Cmd_Item cmd_item_full;
        static struct Cli_Cmd_Item cmd_item_verbose;

        cmd_help_full_verbose = Cli_Cmd_Init(CMD_ID_help_full_verbose, "help full verbose", "show all commands with arguments information");

        cmd_item_help = Cli_Cmd_Item_Word_Init("help", "show help");
        cmd_item_full = Cli_Cmd_Item_Word_Init("full", "show all commands");
        cmd_item_verbose = Cli_Cmd_Item_Word_Init("verbose", "show all arguments information");

        Cli_Cmd_Add_Item(&cmd_help_full_verbose, &cmd_item_help);
        Cli_Cmd_Add_Item(&cmd_help_full_verbose, &cmd_item_full);
        Cli_Cmd_Add_Item(&cmd_help_full_verbose, &cmd_item_verbose);

        Cli_Module_Add_Cmd(module_base, &cmd_help_full_verbose);
    }

    {
        static struct Cli_Cmd cmd_help_module_module_name;

        static struct Cli_Cmd_Item cmd_item_help;
        static struct Cli_Cmd_Item cmd_item_module;
        static struct Cli_Cmd_Item cmd_item_module_name;

        cmd_help_module_module_name = Cli_Cmd_Init(CMD_ID_help_module_module_name,
                "help module \"<module_name>\"", "show module commands (modules by filter)");

        cmd_item_help = Cli_Cmd_Item_Word_Init("help", "show help");
        cmd_item_module = Cli_Cmd_Item_Word_Init("module", "show module commands (modules by filter)");
        cmd_item_module_name = Cli_Cmd_Item_Str_Init("\"<module_name>\"", "modules about which need to obtain information (by filter)");

        Cli_Cmd_Add_Item(&cmd_help_module_module_name, &cmd_item_help);
        Cli_Cmd_Add_Item(&cmd_help_module_module_name, &cmd_item_module);
        Cli_Cmd_Add_Item(&cmd_help_module_module_name, &cmd_item_module_name);

        Cli_Module_Add_Cmd(module_base, &cmd_help_module_module_name);
    }

    {
        static struct Cli_Cmd cmd_help_module_module_name;

        static struct Cli_Cmd_Item cmd_item_help;
        static struct Cli_Cmd_Item cmd_item_module;
        static struct Cli_Cmd_Item cmd_item_module_name;
        static struct Cli_Cmd_Item cmd_item_verbose;

        cmd_help_module_module_name = Cli_Cmd_Init(CMD_ID_help_module_module_name_verbose,
                "help module \"<module_name>\" verbose", "show module commands (modules by filter) with arguments information");

        cmd_item_help = Cli_Cmd_Item_Word_Init("help", "show help");
        cmd_item_module = Cli_Cmd_Item_Word_Init("module", "show module commands (modules by filter)");
        cmd_item_module_name = Cli_Cmd_Item_Str_Init("\"<module_name>\"", "modules about which need to obtain information (by filter)");
        cmd_item_verbose = Cli_Cmd_Item_Word_Init("verbose", "show all arguments information");

        Cli_Cmd_Add_Item(&cmd_help_module_module_name, &cmd_item_help);
        Cli_Cmd_Add_Item(&cmd_help_module_module_name, &cmd_item_module);
        Cli_Cmd_Add_Item(&cmd_help_module_module_name, &cmd_item_module_name);
        Cli_Cmd_Add_Item(&cmd_help_module_module_name, &cmd_item_verbose);

        Cli_Module_Add_Cmd(module_base, &cmd_help_module_module_name);
    }

    {
        static struct Cli_Cmd cmd_help_command;

        static struct Cli_Cmd_Item cmd_item_help;
        static struct Cli_Cmd_Item cmd_item_command;

        cmd_help_command = Cli_Cmd_Init(CMD_ID_help_command, "help \"<command>\"", "show selected commands (by filter)");

        cmd_item_help = Cli_Cmd_Item_Word_Init("help", "show help");
        cmd_item_command = Cli_Cmd_Item_Str_Init("\"<command>\"", "command about which need to obtain information (by filter)");

        Cli_Cmd_Add_Item(&cmd_help_command, &cmd_item_help);
        Cli_Cmd_Add_Item(&cmd_help_command, &cmd_item_command);

        Cli_Module_Add_Cmd(module_base, &cmd_help_command);
    }

    {
        static struct Cli_Cmd cmd_help_command_verbose;

        static struct Cli_Cmd_Item cmd_item_help;
        static struct Cli_Cmd_Item cmd_item_command;
        static struct Cli_Cmd_Item cmd_item_verbose;

        cmd_help_command_verbose = Cli_Cmd_Init(CMD_ID_help_command_verbose,
                "help \"<command>\" verbose", "show selected commands (by filter) with arguments information");

        cmd_item_help = Cli_Cmd_Item_Word_Init("help", "show help");
        cmd_item_command = Cli_Cmd_Item_Str_Init("\"<command>\"", "command about which need to obtain information (by filter)");
        cmd_item_verbose = Cli_Cmd_Item_Word_Init("verbose", "show all arguments information");

        Cli_Cmd_Add_Item(&cmd_help_command_verbose, &cmd_item_help);
        Cli_Cmd_Add_Item(&cmd_help_command_verbose, &cmd_item_command);
        Cli_Cmd_Add_Item(&cmd_help_command_verbose, &cmd_item_verbose);

        Cli_Module_Add_Cmd(module_base, &cmd_help_command_verbose);
    }

    return module_help;
}
