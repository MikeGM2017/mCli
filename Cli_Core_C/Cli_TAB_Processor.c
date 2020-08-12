/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Cli_TAB_Processor.h"

static char *Str_Trim(char *s, char *s_trim) {
    int s_size = strlen(s);
    int pos_beg = 0;
    int pos_end = s_size ? (s_size - 1) : 0;
    while (pos_beg < s_size && (s[pos_beg] == ' ' || s[pos_beg] == '\t' || s[pos_beg] == '\r' || s[pos_beg] == '\n')) pos_beg++;
    while (pos_end > pos_beg && (s[pos_end] == ' ' || s[pos_end] == '\t' || s[pos_end] == '\r' || s[pos_end] == '\n')) pos_end--;
    if (pos_end >= pos_beg) {
        int len = pos_end - pos_beg + 1;
        strncpy(s_trim, s + pos_beg, len);
        s_trim[len] = '\0';
    } else {
        s_trim[0] = '\0';
    }
    return s_trim;
}

static struct Level_Description Level_Get(struct Cli_TAB_Processor *tab_processor) {
    if (tab_processor->Levels->Size > 0) {
        return tab_processor->Levels->Items[tab_processor->Levels->Size - 1];
    }
    struct Level_Description level_top = Level_Description_Init();
    return level_top;
}

static int TAB_Cmd_Ptr_Check_By_Level(struct Cli_Cmd *cmd_ptr, enum Cli_Cmd_Privilege_ID user_privilege, char *level) {
    if (cmd_ptr && user_privilege <= cmd_ptr->Privilege) {
        if (cmd_ptr->Is_Global) return 1;
        if (!strncmp(cmd_ptr->Level, level, CLI_CMD_LEVEL_SIZE_DEF)) return 1;
    }
    return 0;
}

static void TAB_Cmd_Add_By_Level(struct Cli_Cmd *cmd_ptr, enum Cli_Cmd_Privilege_ID user_privilege, char *level,
        struct Str_List_Item *str_list, int *str_list_size, int str_list_size_max) {
    int is_cmd_prt_valid = TAB_Cmd_Ptr_Check_By_Level(cmd_ptr, user_privilege, level);
    if (is_cmd_prt_valid) {
        char *s = cmd_ptr->Item_Head->Text;

        int i;
        int found = 0;
        for (i = 0; i < (*str_list_size); i++) {
            char *str_list_ptr = str_list[i].Text;
            if (!strcmp(str_list_ptr, s)) {
                found = 1;
                break;
            }
        }

        if (!found && (*str_list_size) < str_list_size_max) {
            Str_List_Item_Text_Set(&str_list[(*str_list_size)], s);
            (*str_list_size)++;
        }
    }
}

static void TAB_Help_Get(enum Cli_Cmd_Privilege_ID user_privilege,
        struct Cli_Modules *modules, char *level,
        char *s_out, int s_out_size) {

#define TAB_HELP_STR_LIST_SIZE_DEF 32

    struct Str_List_Item str_list[TAB_HELP_STR_LIST_SIZE_DEF];
    int str_list_size = 0;

    strncpy(str_list[str_list_size++].Text, "H", CLI_CMD_TEXT_SIZE_DEF);
    strncpy(str_list[str_list_size++].Text, "Q", CLI_CMD_TEXT_SIZE_DEF);
    strncpy(str_list[str_list_size++].Text, "E", CLI_CMD_TEXT_SIZE_DEF);

    struct Cli_Module *module_ptr = modules->Module_Head;
    while (module_ptr) {
        {
            struct Cli_Cmd *cmd_ptr = module_ptr->Cmd_Head;
            while (cmd_ptr) {
                {
                    int is_cmd_prt_valid = TAB_Cmd_Ptr_Check_By_Level(cmd_ptr, user_privilege, level);
                    if (is_cmd_prt_valid) {
                        TAB_Cmd_Add_By_Level(cmd_ptr, user_privilege, level, str_list, &str_list_size, TAB_HELP_STR_LIST_SIZE_DEF);
                    }
                }
                cmd_ptr = cmd_ptr->Cmd_Next;
            }
        }
        module_ptr = module_ptr->Module_Next;
    }

    int s_out_pos = 0;
    int i;
    for (i = 0; i < str_list_size; i++) {
        s_out_pos += snprintf(s_out + s_out_pos, s_out_size - s_out_pos, " %s", str_list[i].Text);
    }

}

static void TAB_Cmd_List_Get_With_Flags(
        // in
        enum Cli_Cmd_Privilege_ID user_privilege, struct Cli_Modules *modules,
        char *level, char *s_cmd_in, char *s_cmd_in_trim, struct Cmd_Token_Array *tokens,
        // out
        char *s_log, int s_log_size_max,
        char *s_add, int s_add_size_max,
        int *Is_Log, int *Is_Add, int *Is_Space_Before, int *Is_Space_After) {

    // Dummy
    strcpy(s_log, " Dummy <Dummy>");
    (*Is_Log) = 1;
    s_add[0] = '\0';
    (*Is_Add) = 0;

}

static void TAB_Cmd_List_Get(
        // in
        enum Cli_Cmd_Privilege_ID user_privilege, struct Cli_Modules *modules,
        char *level, char *s_cmd_in, char *s_cmd_in_trim, struct Cmd_Token_Array *tokens,
        //out
        struct TAB_Cmd *tab_cmd_list, int *tab_cmd_list_size, int tab_cmd_list_size_max) {

#define TAB_STR_LOG_SIZE_DEF 1024
#define TAB_STR_ADD_SIZE_DEF 1024

    char s_log[TAB_STR_LOG_SIZE_DEF] = "";
    char s_add[TAB_STR_ADD_SIZE_DEF] = "";

    int Is_Log = 0;
    int Is_Add = 0;
    int Is_Space_Before = 0;
    int Is_Space_After = 0;

    TAB_Cmd_List_Get_With_Flags(
            // in
            user_privilege, modules, level, s_cmd_in, s_cmd_in_trim, tokens,
            // out
            s_log, TAB_STR_LOG_SIZE_DEF,
            s_add, TAB_STR_ADD_SIZE_DEF,
            &Is_Log, &Is_Add, &Is_Space_Before, &Is_Space_After);

    if (Is_Log && (*tab_cmd_list_size) < tab_cmd_list_size_max) {
        tab_cmd_list[(*tab_cmd_list_size)].ID = TAB_CMD_ID_LOG_PRINT;

        int len = TAB_CMD_TEXT_SIZE_DEF - 1;
        strncpy(tab_cmd_list[(*tab_cmd_list_size)].Text, s_log, len);
        tab_cmd_list[(*tab_cmd_list_size)].Text[len] = '\0';

        (*tab_cmd_list_size)++;
    }
    if (Is_Space_Before && (*tab_cmd_list_size) < tab_cmd_list_size_max) {
        tab_cmd_list[(*tab_cmd_list_size)].ID = TAB_CMD_ID_INPUT_CHECK_SPACE;
        tab_cmd_list[(*tab_cmd_list_size)].Text[0] = '\0';
        (*tab_cmd_list_size)++;
    }
    if (Is_Add && (*tab_cmd_list_size) < tab_cmd_list_size_max) {
        tab_cmd_list[(*tab_cmd_list_size)].ID = TAB_CMD_ID_INPUT_ADD;

        int len = TAB_CMD_TEXT_SIZE_DEF - 1;
        strncpy(tab_cmd_list[(*tab_cmd_list_size)].Text, s_add, len);
        tab_cmd_list[(*tab_cmd_list_size)].Text[len] = '\0';

        (*tab_cmd_list_size)++;
    }
    if (Is_Space_After && (*tab_cmd_list_size) < tab_cmd_list_size_max) {
        tab_cmd_list[(*tab_cmd_list_size)].ID = TAB_CMD_ID_INPUT_CHECK_SPACE;
        tab_cmd_list[(*tab_cmd_list_size)].Text[0] = '\0';
        (*tab_cmd_list_size)++;
    }

}

static int Process_Input_Item(struct Cli_TAB_Processor *tab_processor,
        struct Cli_Input_C_Item *input_item, int *is_invitation_print) {

#define TAB_CMD_LIST_SIZE_DEF 4

#define TAB_HELP_TOKEN_LIST_SIZE_DEF 32

    struct TAB_Cmd tab_cmd_list[TAB_CMD_LIST_SIZE_DEF];
    int tab_cmd_list_size = 0;

    char s_trim[CLI_INPUT_C_ITEM_TEXT_SIZE];
    Str_Trim(Cli_Input_C_Item_Text_Get(input_item), s_trim);
    int s_trim_size = strnlen(s_trim, CLI_INPUT_C_ITEM_TEXT_SIZE);

    struct Level_Description level_description = Level_Get(tab_processor);

    char level[LEVEL_DESCRIPTION_LEVEL_SIZE_DEF];
    int len = LEVEL_DESCRIPTION_LEVEL_SIZE_DEF - 1;
    strncpy(level, level_description.Level, len);
    level[len] = '\0';

    if (s_trim_size == 0) {
        TAB_Help_Get(tab_processor->User_Privilege, tab_processor->Modules, level, tab_cmd_list[0].Text, TAB_CMD_TEXT_SIZE_DEF);
        tab_cmd_list[0].ID = TAB_CMD_ID_LOG_PRINT;
        tab_cmd_list_size = 1;
    } else {
        //        Cmd_Token_Parser_Result parse_res = CMD_TOKEN_PARSER_ERROR;
        //        vector<Cmd_Token *> tokens = Token_Parser.Parse(s_trim, Str_Rem, parse_res);
        //
        //        tab_cmd_list = TAB_Cmd_List_Get(User_Privilege, Modules, level, input_item.Text_Get(), s_trim, tokens);
        //
        //        for (int i = 0; i < tokens.size(); i++)
        //            delete tokens[i];
        //        tokens.clear();
        enum Cmd_Token_Parser_Result parse_res = CMD_TOKEN_PARSER_ERROR;
        struct Cmd_Token_Array tokens = tab_processor->Parser->Parse(s_trim, tab_processor->Str_Rem, &parse_res);

        TAB_Cmd_List_Get(
                // in
                tab_processor->User_Privilege, tab_processor->Modules, level,
                Cli_Input_C_Item_Text_Get(input_item), s_trim, &tokens,
                // out
                tab_cmd_list, &tab_cmd_list_size, TAB_CMD_LIST_SIZE_DEF);
    }

    if (tab_cmd_list_size) {
        for (int tab_cmd = 0; tab_cmd < tab_cmd_list_size; tab_cmd++) {
            struct TAB_Cmd *tab_cmd_ptr = &tab_cmd_list[tab_cmd];
            if (tab_cmd_ptr) {
                switch (tab_cmd_ptr->ID) {
                    case TAB_CMD_ID_LOG_PRINT:
                        tab_processor->Cli_Output->Output_NewLine();
                        tab_processor->Cli_Output->Output_Str(tab_cmd_ptr->Text);
                        tab_processor->Cli_Output->Output_NewLine();
                        (*is_invitation_print) = 1;
                        break;
                    case TAB_CMD_ID_INPUT_ADD:
                    {
                        struct Cli_Input_C *Cli_Input = tab_processor->Cli_Input;
                        char s_prev[CLI_INPUT_C_INPUT_STR_SIZE];
                        int len = CLI_INPUT_C_INPUT_STR_SIZE - 1;
                        strncpy(s_prev, Cli_Input->Input_Str_Get(Cli_Input), len);
                        s_prev[len] = '\0';

                        char s_new[CLI_INPUT_C_INPUT_STR_SIZE];
                        len = CLI_INPUT_C_INPUT_STR_SIZE - 1;
                        snprintf(s_new, len, "%s%s", s_prev, tab_cmd_ptr->Text);
                        s_new[len] = '\0';

                        Cli_Input->Input_Str_Set(Cli_Input, s_new);
                        Cli_Input->Input_Str_Modified_To_Output(Cli_Input, s_prev);
                        Cli_Input->Input_End(Cli_Input);
                        (*is_invitation_print) = 0;
                    }
                        break;
                    case TAB_CMD_ID_INPUT_CHECK_SPACE:
                    {
                        struct Cli_Input_C *Cli_Input = tab_processor->Cli_Input;
                        char s_prev[CLI_INPUT_C_INPUT_STR_SIZE];
                        int len = CLI_INPUT_C_INPUT_STR_SIZE - 1;
                        strncpy(s_prev, Cli_Input->Input_Str_Get(Cli_Input), len);
                        s_prev[len] = '\0';

                        int s_prev_size = strnlen(s_prev, CLI_INPUT_C_INPUT_STR_SIZE);
                        if (s_prev[0] == '\0' || s_prev[s_prev_size - 1] != ' ') {

                            char s_new[CLI_INPUT_C_INPUT_STR_SIZE];
                            len = CLI_INPUT_C_INPUT_STR_SIZE - 1;
                            snprintf(s_new, len, "%s%c", s_prev, ' ');
                            s_new[len] = '\0';

                            Cli_Input->Input_Str_Set(Cli_Input, s_new);
                        }
                        Cli_Input->Input_Str_Modified_To_Output(Cli_Input, s_prev);
                        Cli_Input->Input_End(Cli_Input);
                        (*is_invitation_print) = 0;
                    }
                        break;
                }
            }
        }
    } else {
        tab_processor->Cli_Output->Output_NewLine();
    }

    return 1; // Ok
}

struct Cli_TAB_Processor Cli_TAB_Processor_Init(enum Cli_Cmd_Privilege_ID user_privilege,
        struct Cli_Modules *modules,
        struct Level_Description_Array *levels,
        struct Cmd_Token_Parser *parser,
        struct Cli_Input_C *cli_input,
        struct Cli_Output_C *cli_output,
        char *str_rem) {
    struct Cli_TAB_Processor tab_processor;
    memset(&tab_processor, 0, sizeof (tab_processor));

    tab_processor.User_Privilege = user_privilege;
    tab_processor.Modules = modules;
    tab_processor.Levels = levels;
    tab_processor.Parser = parser;
    tab_processor.Cli_Input = cli_input;
    tab_processor.Cli_Output = cli_output;

    if (str_rem) {
        int len = CLI_TAB_PROCESSOR_STR_REM_SIZE_DEF - 1;
        strncpy(tab_processor.Str_Rem, str_rem, len);
        tab_processor.Str_Rem[len] = '\0';
    } else {
        tab_processor.Str_Rem[0] = '\0';
    }

    tab_processor.Process_Input_Item = Process_Input_Item;

    return tab_processor;
}
