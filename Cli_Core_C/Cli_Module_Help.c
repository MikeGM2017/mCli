/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Cli_Module_Help.h"

#include "Cli_Cmd_Item_Word.h"

enum Local_Cmd_ID {
    CMD_ID_NO,

    CMD_ID_help_H,
    CMD_ID_help,
    CMD_ID_help_verbose,
    CMD_ID_help_full,
    CMD_ID_help_full_verbose,
    CMD_ID_help_command,
    CMD_ID_help_command_verbose,

    CMD_ID_help_module_module_name,
    CMD_ID_help_module_module_name_verbose,

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

    //    for (int module = 0; module < modules->.Get_Size(); module++) {
    //        struct Cli_Module *module_ptr = modules.Get(module);
    //        if (is_full || Str_Filter_Is_Match(str_filter, module_filter, module_ptr->Name_Get())) {
    //            for (int cmd = 0; cmd < module_ptr->Module_Cmd_List.size(); cmd++) {
    //                struct Cli_Cmd *cmd_ptr = module_ptr->Module_Cmd_List[cmd];
    //                int is_cmd_prt_valid = HELP_Cmd_Ptr_Check_By_Level(cmd_ptr, User_Privilege, level, is_full, is_module_full);
    //                if (is_cmd_prt_valid && str_filter.Is_Match(command_filter, cmd_ptr->Items[0]->Text_Get())) {
    //                    int len = 0;
    //                    if (level.size() == 0) {
    //                        int len_level = cmd_ptr->Level_Get().size();
    //                        if (len_level > 0)
    //                            len += len_level + 3; // "[" + ... + "] " - OnHelp_CliModules(...)
    //                    }
    //                    len += cmd_ptr->Text_Get().size();
    //                    if (len_max < len)
    //                        len_max = len;
    //                    if (is_verbose) {
    //                        for (int i = 0; i < cmd_ptr->Items.size(); i++) {
    //                            Cmd_Item_Base *item = cmd_ptr->Items[i];
    //                            len = 1 + item->Text_Get().size(); // " " + ...
    //                            if (len_max < len)
    //                                len_max = len;
    //                        }
    //                    }
    //                }
    //            }
    //        }
    //    }

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

static void Help_Cli_Modules_Print_V01(int user_privilege, struct Cli_Modules *modules,
        char *level,
        int is_full, int is_verbose, int is_module_full,
        char *module_filter, char *command_filter, struct Str_Filter *str_filter,
        int len_max, int *modules_count, int *commands_count,
        struct Cli_Output_C *Cli_Output) {

    Cli_Output->Output_NewLine();

    char s_buf[CLI_CMD_TEXT_SIZE_DEF];
    char s_format[CLI_CMD_TEXT_SIZE_DEF];
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
                            //Cli_Output->Output_Str(cmd_ptr->Text);
                            sprintf(s_format, "%%-%ds", len_max);
                            snprintf(s_buf, CLI_CMD_TEXT_SIZE_DEF, s_format, cmd_ptr->Text);
                            Cli_Output->Output_Str(s_buf);
                            Cli_Output->Output_Str(" - ");
                            Cli_Output->Output_Str(cmd_ptr->Help);
                            Cli_Output->Output_NewLine();
                            (*commands_count)++;
                            if (is_verbose) {
                                //                        for (int i = 0; i < cmd_ptr->Items.size(); i++) {
                                //                            Cmd_Item_Base *item = cmd_ptr->Items[i];
                                //                            stringstream s_str3;
                                //                            stringstream s_str4;
                                //                            s_str3 << " " << item->Text_Get();
                                //                            s_str4 << setw(len_max) << left << s_str3.str() << " - " << item->Help_Get();
                                //                            Cli_Output->Output_Str(s_str4.str());
                                //                            Cli_Output->Output_NewLine();
                                //                        }
                                struct Cli_Cmd_Item *cmd_item_ptr = cmd_ptr->Item_Head;
                                while (cmd_item_ptr) {
                                    {
                                        Cli_Output->Output_Str(" ");
                                        snprintf(s_buf, CLI_CMD_TEXT_SIZE_DEF, s_format, cmd_item_ptr->Text);
                                        Cli_Output->Output_Str(s_buf);
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

    //    for (int module = 0; module < modules->.Get_Size(); module++) {
    //        Cli_Module *module_ptr = modules.Get(module);
    //        if (is_full || str_filter.Is_Match(module_filter, module_ptr->Name_Get())) {
    //            (*modules_count)++;
    //            for (int cmd = 0; cmd < module_ptr->Module_Cmd_List.size(); cmd++) {
    //                Cli_Cmd *cmd_ptr = module_ptr->Module_Cmd_List[cmd];
    //                string s;
    //                stringstream s_str1;
    //                stringstream s_str2;
    //                if (level.size() == 0) {
    //                    string s_level = cmd_ptr->Level_Get();
    //                    if (s_level.size() > 0) {
    //                        s += "[" + s_level + "] ";
    //                        s_str1 << "[" << s_level << "] ";
    //                    }
    //                }
    //                s += cmd_ptr->Text_Get();
    //                s_str1 << cmd_ptr->Text_Get();
    //                int is_cmd_prt_valid = HELP_Cmd_Ptr_Check_By_Level(cmd_ptr, User_Privilege, level, is_full, is_module_full);
    //                if (is_cmd_prt_valid && str_filter.Is_Match(command_filter, cmd_ptr->Items[0]->Text_Get())) {
    //                    s_str2 << setw(len_max) << left << s_str1.str() << " - " << cmd_ptr->Help_Get();
    //                    Cli_Output->Output_Str(s_str2.str());
    //                    Cli_Output->Output_NewLine();
    //                    (*commands_count)++;
    //                    if (is_verbose) {
    //                        for (int i = 0; i < cmd_ptr->Items.size(); i++) {
    //                            Cmd_Item_Base *item = cmd_ptr->Items[i];
    //                            stringstream s_str3;
    //                            stringstream s_str4;
    //                            s_str3 << " " << item->Text_Get();
    //                            s_str4 << setw(len_max) << left << s_str3.str() << " - " << item->Help_Get();
    //                            Cli_Output->Output_Str(s_str4.str());
    //                            Cli_Output->Output_NewLine();
    //                        }
    //                    }
    //                }
    //            }
    //        }
    //    }

}

static void Help_Cli_Modules_Print(int user_privilege, struct Cli_Modules *modules,
        char *level,
        int is_full, int is_verbose, int is_module_full,
        char *module_filter, char *command_filter, struct Str_Filter *str_filter,
        int len_max, int *modules_count, int *commands_count,
        struct Cli_Output_C *Cli_Output) {

    Cli_Output->Output_NewLine();

    //char s_buf[CLI_CMD_TEXT_SIZE_DEF] = "";
    //char s_format[CLI_CMD_TEXT_SIZE_DEF] = "";
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
                            //sprintf(s_format, "%%-%ds", len_max);
                            //snprintf(s_buf, CLI_CMD_TEXT_SIZE_DEF, s_format, cmd_ptr->Text);
                            //Cli_Output->Output_Str(s_buf);
                            int text_len = strlen(cmd_ptr->Text);
                            //if (text_len < len_max) {
                            if (text_len < len_max + 1) { // @Attention: len_max + 1 - cmd_item adds: ' '
                                int i;
                                //for (i = text_len; i < len_max; i++) {
                                for (i = text_len; i < len_max + 1; i++) { // @Attention: len_max + 1 - cmd_item adds: ' '
                                    Cli_Output->Output_Char(' ');
                                    //Cli_Output->Output_Char('.');
                                }
                            }
                            Cli_Output->Output_Str(" - ");
                            Cli_Output->Output_Str(cmd_ptr->Help);
                            Cli_Output->Output_NewLine();
                            (*commands_count)++;
                            if (is_verbose) {
                                //                        for (int i = 0; i < cmd_ptr->Items.size(); i++) {
                                //                            Cmd_Item_Base *item = cmd_ptr->Items[i];
                                //                            stringstream s_str3;
                                //                            stringstream s_str4;
                                //                            s_str3 << " " << item->Text_Get();
                                //                            s_str4 << setw(len_max) << left << s_str3.str() << " - " << item->Help_Get();
                                //                            Cli_Output->Output_Str(s_str4.str());
                                //                            Cli_Output->Output_NewLine();
                                //                        }
                                struct Cli_Cmd_Item *cmd_item_ptr = cmd_ptr->Item_Head;
                                while (cmd_item_ptr) {
                                    {
                                        Cli_Output->Output_Str(" ");
                                        Cli_Output->Output_Str(cmd_item_ptr->Text);
                                        //snprintf(s_buf, CLI_CMD_TEXT_SIZE_DEF, s_format, item->Text);
                                        //Cli_Output->Output_Str(s_buf);
                                        int text_len = strlen(cmd_item_ptr->Text);
                                        if (text_len < len_max) {
                                            int i;
                                            for (i = text_len; i < len_max; i++) {
                                                Cli_Output->Output_Char(' ');
                                                //Cli_Output->Output_Char('-');
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

    //    for (int module = 0; module < modules->.Get_Size(); module++) {
    //        Cli_Module *module_ptr = modules.Get(module);
    //        if (is_full || str_filter.Is_Match(module_filter, module_ptr->Name_Get())) {
    //            (*modules_count)++;
    //            for (int cmd = 0; cmd < module_ptr->Module_Cmd_List.size(); cmd++) {
    //                Cli_Cmd *cmd_ptr = module_ptr->Module_Cmd_List[cmd];
    //                string s;
    //                stringstream s_str1;
    //                stringstream s_str2;
    //                if (level.size() == 0) {
    //                    string s_level = cmd_ptr->Level_Get();
    //                    if (s_level.size() > 0) {
    //                        s += "[" + s_level + "] ";
    //                        s_str1 << "[" << s_level << "] ";
    //                    }
    //                }
    //                s += cmd_ptr->Text_Get();
    //                s_str1 << cmd_ptr->Text_Get();
    //                int is_cmd_prt_valid = HELP_Cmd_Ptr_Check_By_Level(cmd_ptr, User_Privilege, level, is_full, is_module_full);
    //                if (is_cmd_prt_valid && str_filter.Is_Match(command_filter, cmd_ptr->Items[0]->Text_Get())) {
    //                    s_str2 << setw(len_max) << left << s_str1.str() << " - " << cmd_ptr->Help_Get();
    //                    Cli_Output->Output_Str(s_str2.str());
    //                    Cli_Output->Output_NewLine();
    //                    (*commands_count)++;
    //                    if (is_verbose) {
    //                        for (int i = 0; i < cmd_ptr->Items.size(); i++) {
    //                            Cmd_Item_Base *item = cmd_ptr->Items[i];
    //                            stringstream s_str3;
    //                            stringstream s_str4;
    //                            s_str3 << " " << item->Text_Get();
    //                            s_str4 << setw(len_max) << left << s_str3.str() << " - " << item->Help_Get();
    //                            Cli_Output->Output_Str(s_str4.str());
    //                            Cli_Output->Output_NewLine();
    //                        }
    //                    }
    //                }
    //            }
    //        }
    //    }

}

static void help(struct Cli_Module_Help *module_help,
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
        Cli_Output->Output_NewLine();
    }

}

static int Execute(struct Cli_Module *module, int cmd_id, struct Cli_Cmd *cmd, struct Level_Description_Array *Levels, int is_debug) {
    struct Cli_Module_Help *module_help = (struct Cli_Module_Help *) module;
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
            char module_filter[] = "*";
            char command_filter[] = "*";
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
            char module_filter[] = "*";
            char command_filter[] = "*";
            help(module_help, level.Level,
                    is_full, is_verbose, is_module_full,
                    module_filter, command_filter,
                    module_help->Cli_Output);
        }
            return 1;
    }

    return 0; /*Failed*/
}

struct Cli_Module_Help Cli_Module_Help_Init(enum Cli_Cmd_Privilege_ID user_privilege, struct Cli_Modules *modules,
        struct Str_Filter *help_str_filter, struct Cli_Output_C *cli_output) {
    struct Cli_Module_Help module_help;
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

        cmd_H = Cli_Cmd_Init(CMD_ID_help_H, "H", "help");

        cmd_item_H = Cli_Cmd_Item_Word_Init("H", "help");

        Cli_Cmd_Add_Item(&cmd_H, &cmd_item_H);

        Cli_Module_Add_Cmd(module_base, &cmd_H);
    }

    {
        static struct Cli_Cmd cmd_help;
        static struct Cli_Cmd_Item cmd_item_help;

        cmd_help = Cli_Cmd_Init(CMD_ID_help, "help", "help");

        cmd_item_help = Cli_Cmd_Item_Word_Init("help", "help");

        Cli_Cmd_Add_Item(&cmd_help, &cmd_item_help);

        Cli_Module_Add_Cmd(module_base, &cmd_help);
    }

    {
        static struct Cli_Cmd cmd_help_verbose;
        static struct Cli_Cmd_Item cmd_item_help;
        static struct Cli_Cmd_Item cmd_item_verbose;

        cmd_help_verbose = Cli_Cmd_Init(CMD_ID_help_verbose, "help verbose", "help verbose");

        cmd_item_help = Cli_Cmd_Item_Word_Init("help", "help");
        cmd_item_verbose = Cli_Cmd_Item_Word_Init("verbose", "help verbose");

        Cli_Cmd_Add_Item(&cmd_help_verbose, &cmd_item_help);
        Cli_Cmd_Add_Item(&cmd_help_verbose, &cmd_item_verbose);

        Cli_Module_Add_Cmd(module_base, &cmd_help_verbose);
    }

    return module_help;
}
