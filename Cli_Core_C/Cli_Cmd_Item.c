/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Cli_Cmd_Item.h"

static enum Cmd_Item_Valid_Result Parse(struct Cli_Cmd_Item *item, char *s) {
    int len = CLI_CMD_ITEM_VALUE_STR_SIZE_DEF - 1;
    strncpy(item->Value_Str, s, len);
    item->Value_Str[len] = '\0';

    if (s[0] == '\0') return CMD_ITEM_EMPTY;

    if (!strncmp(item->Text, s, CLI_CMD_ITEM_TEXT_SIZE_DEF)) return CMD_ITEM_OK;

    return CMD_ITEM_ERROR;
}

void Cli_Cmd_Item_Init_Base(struct Cli_Cmd_Item *item, enum Cli_Cmd_Item_Type item_type, char *text, char *help) {
    item->Cmd_Item_Type = item_type;

    if (!text)
        item->Text[0] = '\0';
    else {
        int len = CLI_CMD_ITEM_TEXT_SIZE_DEF - 1;
        strncpy(item->Text, text, len);
        item->Text[len] = '\0';
    }

    if (!help)
        item->Help[0] = '\0';
    else {
        int len = CLI_CMD_ITEM_HELP_SIZE_DEF - 1;
        strncpy(item->Help, help, len);
        item->Help[len] = '\0';
    }

    item->Cmd_Item_Next = NULL;

    item->Parse = Parse;
}
