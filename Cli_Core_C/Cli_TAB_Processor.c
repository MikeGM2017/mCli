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

static void Str_List_Add_Unique(struct Str_List_Item *s_list, int *s_list_size, int s_list_size_max, char *s) {
    if ((*s_list_size) < s_list_size_max) {
        int i;
        int found = 0;
        for (i = 0; i < (*s_list_size); i++) {
            if (!strncmp(s_list[i].Text, s, STR_LIST_ITEM_TEXT_SIZE_DEF)) {
                found = 1;
                break;
            }
        }

        if (!found) {
            int len = STR_LIST_ITEM_TEXT_SIZE_DEF - 1;
            strncpy(s_list[(*s_list_size)].Text, s, len);
            s_list[(*s_list_size)].Text[len] = '\0';
            (*s_list_size)++;
        }
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

    int is_incomplete_str = 0;
    char last_char = 0;
    int is_last_char_space = 0;
    int is_last_char_comma = 0;
    int is_last_char_commas = 0;

    int s_cmd_in_size = strlen(s_cmd_in);
    int s_cmd_in_empty = (s_cmd_in[0] == '\0');
    if (!s_cmd_in_empty) {
        last_char = s_cmd_in[s_cmd_in_size - 1];
        if (last_char == ' ' || last_char == '\t') is_last_char_space = 1;
        else if (last_char == ',') is_last_char_comma = 1;
        else if (last_char == '\'' || last_char == '\"') is_last_char_commas = 1;
    }

    int Is_Enter = 0;

#define TAB_STR_LOG_LIST_SIZE_DEF 64
#define TAB_STR_ADD_LIST_SIZE_DEF 64

    struct Str_List_Item s_log_list[TAB_STR_LOG_LIST_SIZE_DEF];
    int s_log_list_size = 0;

    struct Str_List_Item s_add_list[TAB_STR_ADD_LIST_SIZE_DEF];
    int s_add_list_size = 0;

    struct Cli_Module *module_ptr = modules->Module_Head;
    while (module_ptr) {
        {
            struct Cli_Cmd *cmd_ptr = module_ptr->Cmd_Head;
            while (cmd_ptr) {
                {
                    int is_cmd_prt_valid = TAB_Cmd_Ptr_Check_By_Level(cmd_ptr, user_privilege, level);
                    if (is_cmd_prt_valid) {
                        if (tokens->Size <= cmd_ptr->Items_Size) {
                            int is_valid = 1;
                            int token;
                            struct Cli_Cmd_Item *cmd_item_ptr = cmd_ptr->Item_Head;
                            for (token = 0; token < tokens->Size && cmd_item_ptr; token++) {
                                struct Cmd_Token *token_ptr = &tokens->Items[token];
                                {
                                    //                                    enum Cmd_Item_Valid_Result res_parse = cmd_item_ptr->Parse(cmd_item_ptr, token_ptr->Text);
                                    //                                    if (res_parse == CMD_ITEM_OK_CAN_CONTINUE) {
                                    //                                        Cli_TAB_Result *cmd_tab_ptr = new Cli_TAB_Result;
                                    //                                        cmd_tab_ptr->cmd_ptr = cmd_ptr;
                                    //                                        cmd_tab_ptr->Is_Enter = true;
                                    //                                        cmd_tab_ptr->s_log = ",";
                                    //                                        cmd_tab_ptr->is_space_after_add = false;
                                    //                                        cmd_tab_list.push_back(cmd_tab_ptr);
                                    //                                    }
                                    enum Cmd_Item_Valid_Result res_parse = cmd_item_ptr->Parse(cmd_item_ptr, token_ptr->Text);
                                    if (res_parse == CMD_ITEM_OK
                                            || res_parse == CMD_ITEM_OK_STR_WITHOUT_COMMAS) {
                                        if (token == cmd_ptr->Items_Size - 1) { // Full cmd found -> <Enter>
                                            Is_Enter = 1;
                                        } else if (token == tokens->Size - 1) { // Partial cmd found -> next token -> log or add
                                            struct Cli_Cmd_Item *cmd_item_ptr_next = cmd_item_ptr->Cmd_Item_Next;
                                            Str_List_Add_Unique(s_log_list, &s_log_list_size, TAB_STR_LOG_LIST_SIZE_DEF, cmd_item_ptr_next->Text);
                                        }
                                    }
                                }
                                cmd_item_ptr = cmd_item_ptr->Cmd_Item_Next;
                            }
                        }
                    }
                }
                cmd_ptr = cmd_ptr->Cmd_Next;
            }
        }
        module_ptr = module_ptr->Module_Next;
    }

    int i;
    int s_log_pos = 0;
    for (i = 0; i < s_log_list_size; i++) {
        s_log_pos += snprintf(s_log + s_log_pos, TAB_STR_LOG_LIST_SIZE_DEF - 1 - s_log_pos, " %s", s_log_list[i].Text);
    }
    if (Is_Enter) {
        s_log_pos += snprintf(s_log + s_log_pos, TAB_STR_LOG_LIST_SIZE_DEF - 1 - s_log_pos, " %s", "<Enter>");
    }
    if (s_log_pos > 0) {
        (*Is_Log) = 1;
    }

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
                        tab_processor->Cli_Output->Output_NewLine(tab_processor->Cli_Output);
                        tab_processor->Cli_Output->Output_Str(tab_processor->Cli_Output, tab_cmd_ptr->Text);
                        tab_processor->Cli_Output->Output_NewLine(tab_processor->Cli_Output);
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
        tab_processor->Cli_Output->Output_NewLine(tab_processor->Cli_Output);
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
