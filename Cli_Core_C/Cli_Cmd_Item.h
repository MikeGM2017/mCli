/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Cmd_Item.h
 * Author: mike
 *
 * Created on August 3, 2020, 4:54 PM
 */

#ifndef CLI_CMD_ITEM_H
#define CLI_CMD_ITEM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>

#include "Cli_Cmd_Item_Type.h"
#include "Cmd_Item_Valid_Result.h"

#define CLI_CMD_ITEM_TEXT_SIZE_DEF 32
#define CLI_CMD_ITEM_HELP_SIZE_DEF 32
#define CLI_CMD_ITEM_VALUE_STR_SIZE_DEF 32

    struct Cli_Cmd_Item;

    typedef enum Cmd_Item_Valid_Result ftParse(struct Cli_Cmd_Item *item, char *s);
    typedef int ftIs_Char_Valid(char c, int pos, int len);

    struct Cli_Cmd_Item {
        enum Cli_Cmd_Item_Type Cmd_Item_Type;
        char Text[CLI_CMD_ITEM_TEXT_SIZE_DEF];
        char Help[CLI_CMD_ITEM_HELP_SIZE_DEF];
        struct Cli_Cmd_Item *Cmd_Item_Next;

        char Value_Str[CLI_CMD_ITEM_VALUE_STR_SIZE_DEF];

        ftIs_Char_Valid *Is_Char_Valid;
        ftParse *Parse;
    };

    void Cli_Cmd_Item_Init_Base(struct Cli_Cmd_Item *item, enum Cli_Cmd_Item_Type item_type, char *text, char *help);

#ifdef __cplusplus
}
#endif

#endif /* CLI_CMD_ITEM_H */
