/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Cli_CMD_Processor.h"

static char *Str_Trim(char *s, char *s_trim, int s_trim_size) {
    int s_size = strlen(s);
    int pos_beg = 0;
    int pos_end = s_size ? (s_size - 1) : 0;
    while (pos_beg < s_size && (s[pos_beg] == ' ' || s[pos_beg] == '\t' || s[pos_beg] == '\r' || s[pos_beg] == '\n')) pos_beg++;
    while (pos_end > pos_beg && (s[pos_end] == ' ' || s[pos_end] == '\t' || s[pos_end] == '\r' || s[pos_end] == '\n')) pos_end--;
    if (pos_end >= pos_beg) {
        int len = s_trim_size - 1;
        strncpy(s_trim, s + pos_beg, len);
        s_trim[len] = '\0';
    } else {
        s_trim[0] = '\0';
    }
    return s_trim;
}

static struct Level_Description Level_Get(struct Cli_CMD_Processor *cmd_processor) {
    if (cmd_processor->Levels->Size > 0) {
        return cmd_processor->Levels->Items[cmd_processor->Levels->Size - 1];
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

static enum Cmd_Item_Valid_Result Cmd_Is_Valid(struct Cli_CMD_Processor *cmd_processor,
        struct Cli_Cmd *cmd_ptr, struct Cmd_Token_Array *tokens) {
    if (tokens->Size > cmd_ptr->Items_Size) return CMD_ITEM_ERROR;

    if (tokens->Size <= cmd_ptr->Items_Size) {
        int i;
        struct Cli_Cmd_Item *cmd_item_ptr = cmd_ptr->Item_Head;
        for (i = 0; i < tokens->Size; i++) {
            {
                enum Cmd_Item_Valid_Result res_valid = cmd_item_ptr->Parse(cmd_item_ptr, tokens->Items[i].Text);
                if (i == cmd_ptr->Items_Size - 1) {
                    // Последний токен может быть введен не до конца или с ошибкой
                    return res_valid;
                } else if (res_valid != CMD_ITEM_OK
                        && res_valid != CMD_ITEM_OK_CAN_CONTINUE
                        && res_valid != CMD_ITEM_OK_STR_WITHOUT_COMMAS) {
                    return res_valid;
                }
            }
            cmd_item_ptr = cmd_item_ptr->Cmd_Item_Next;
        }
    }
    if (tokens->Size == cmd_ptr->Items_Size) return CMD_ITEM_OK;

    return CMD_ITEM_INCOMPLETE;
}

static int Process_Input_Item(struct Cli_CMD_Processor *cmd_processor,
        struct Cli_Input_C_Item *input_item, int is_debug, int *debug_res) {
    char s_trim[CLI_INPUT_C_ITEM_TEXT_SIZE];
    Str_Trim(Cli_Input_C_Item_Text_Get(input_item), s_trim, CLI_INPUT_C_ITEM_TEXT_SIZE);
    int s_trim_size = strnlen(s_trim, CLI_INPUT_C_ITEM_TEXT_SIZE);

    if (s_trim_size == 0) return 0;

    if (s_trim_size) {

        struct Level_Description level_description = Level_Get(cmd_processor);
        char level[LEVEL_DESCRIPTION_LEVEL_SIZE_DEF];
        int len = LEVEL_DESCRIPTION_LEVEL_SIZE_DEF - 1;
        strncpy(level, level_description.Level, len);
        level[len] = '\0';

        int is_processed = 0;
        int stop = 0;
        enum Cmd_Token_Parser_Result parse_res = CMD_TOKEN_PARSER_ERROR;
        struct Cmd_Token_Array tokens = cmd_processor->Parser->Parse(s_trim, cmd_processor->Str_Rem, &parse_res);

        struct Cli_Module *module_ptr = cmd_processor->Modules->Module_Head;
        while (module_ptr && !stop) {
            {
                struct Cli_Cmd *cmd_ptr = module_ptr->Cmd_Head;
                while (cmd_ptr && !stop) {
                    {
                        int is_cmd_prt_valid = TAB_Cmd_Ptr_Check_By_Level(cmd_ptr, cmd_processor->User_Privilege, level);
                        if (is_cmd_prt_valid) {
                            enum Cmd_Item_Valid_Result res_cmd_valid = Cmd_Is_Valid(cmd_processor, cmd_ptr, &tokens);
                            switch (res_cmd_valid) {
                                case CMD_ITEM_OK:
                                case CMD_ITEM_OK_CAN_CONTINUE:
                                case CMD_ITEM_OK_STR_WITHOUT_COMMAS:
                                {
                                    if (!is_debug)
                                        cmd_processor->Cli_Output->Output_NewLine(cmd_processor->Cli_Output);
                                    int res_execute = module_ptr->Execute(module_ptr, cmd_ptr, cmd_processor->Levels, is_debug);
                                    if (!res_execute) {
                                        if (!is_debug) {
                                            cmd_processor->Cli_Output->Output_NewLine(cmd_processor->Cli_Output);
                                            cmd_processor->Cli_Output->Output_Str(cmd_processor->Cli_Output, s_trim);
                                            cmd_processor->Cli_Output->Output_Str(cmd_processor->Cli_Output, " - Not Implemented (Module \"");
                                            cmd_processor->Cli_Output->Output_Str(cmd_processor->Cli_Output, module_ptr->Name);
                                            cmd_processor->Cli_Output->Output_Str(cmd_processor->Cli_Output, "\")");
                                            //cmd_processor->Cli_Output->Output_NewLine();
                                        }
                                    } else {
                                        (*debug_res) = 1;
                                    }
                                    is_processed = 1;
                                    stop = 1;
                                }
                                    break;
                                case CMD_ITEM_ERROR:
                                case CMD_ITEM_NOT_MATCH:
                                    break;
                                default:
                                    cmd_processor->Cli_Output->Output_NewLine(cmd_processor->Cli_Output);
                                    cmd_processor->Cli_Output->Output_Str(cmd_processor->Cli_Output, "ERROR: ");
                                    cmd_processor->Cli_Output->Output_Str(cmd_processor->Cli_Output, s_trim);
                                    cmd_processor->Cli_Output->Output_Str(cmd_processor->Cli_Output, " - ");
                                    cmd_processor->Cli_Output->Output_Str(cmd_processor->Cli_Output, Cmd_Item_Valid_Result_To_String(res_cmd_valid));
                            }
                        }
                    }
                    cmd_ptr = cmd_ptr->Cmd_Next;
                }
            }
            module_ptr = module_ptr->Module_Next;
        }
        if (!is_processed) {
            cmd_processor->Cli_Output->Output_NewLine(cmd_processor->Cli_Output);
            cmd_processor->Cli_Output->Output_Str(cmd_processor->Cli_Output, s_trim);
            cmd_processor->Cli_Output->Output_Str(cmd_processor->Cli_Output, " - Not Processed");
            //cmd_processor->Cli_Output->Output_NewLine();
        }
    } else {
        //cmd_processor->Cli_Output->Output_NewLine();
    }
    return 1; // Ok
}

struct Cli_CMD_Processor Cli_CMD_Processor_Init(enum Cli_Cmd_Privilege_ID user_privilege,
        struct Cli_Modules *modules,
        struct Level_Description_Array *levels,
        struct Cmd_Token_Parser *parser,
        struct Cli_Input_C *cli_input,
        struct Cli_Output_C *cli_output,
        char *str_rem) {
    struct Cli_CMD_Processor cmd_processor;
    memset(&cmd_processor, 0, sizeof (cmd_processor));

    cmd_processor.User_Privilege = user_privilege;
    cmd_processor.Modules = modules;
    cmd_processor.Levels = levels;
    cmd_processor.Parser = parser;
    cmd_processor.Cli_Input = cli_input;
    cmd_processor.Cli_Output = cli_output;

    if (str_rem) {
        int len = CLI_CMD_PROCESSOR_STR_REM_SIZE_DEF - 1;
        strncpy(cmd_processor.Str_Rem, str_rem, len);
        cmd_processor.Str_Rem[len] = '\0';
    } else {
        cmd_processor.Str_Rem[0] = '\0';
    }

    cmd_processor.Process_Input_Item = Process_Input_Item;

    return cmd_processor;
}
