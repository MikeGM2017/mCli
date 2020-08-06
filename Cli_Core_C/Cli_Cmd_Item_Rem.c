/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Cli_Cmd_Item_Rem.h"

static enum Cmd_Item_Valid_Result Parse(struct Cli_Cmd_Item *item, char *s) {
    int len = CLI_CMD_ITEM_VALUE_STR_SIZE_DEF - 1;
    strncpy(item->Value_Str, s, len);
    item->Value_Str[len] = '\0';

    if (s[0] == 0) return CMD_ITEM_EMPTY;

    int text_len = strnlen(item->Text, CLI_CMD_ITEM_TEXT_SIZE_DEF);
    int s_len = strnlen(s, CLI_CMD_ITEM_TEXT_SIZE_DEF);
    if (text_len <= s_len) {
        if (!strncmp(s, item->Text, text_len)) return CMD_ITEM_OK;
    }

    return CMD_ITEM_ERROR;
}

struct Cli_Cmd_Item Cli_Cmd_Item_Rem_Init(char *text, char *help) {
    struct Cli_Cmd_Item item;
    Cli_Cmd_Item_Init_Base(&item, CLI_CMD_ITEM_TYPE_REM, text, help);

    item.Parse = Parse;

    return item;
}
