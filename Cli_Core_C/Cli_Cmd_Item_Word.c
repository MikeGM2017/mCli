/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Cli_Cmd_Item.h"

struct Cli_Cmd_Item Cli_Cmd_Item_Word_Init(char *text, char *help) {
    struct Cli_Cmd_Item item;
    Cli_Cmd_Item_Init_Base(&item, CLI_CMD_ITEM_TYPE_WORD, text, help);
    return item;
}
