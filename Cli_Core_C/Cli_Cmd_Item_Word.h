/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Cmd_Item_Word.h
 * Author: mike
 *
 * Created on August 3, 2020, 4:53 PM
 */

#ifndef CLI_CMD_ITEM_WORD_H
#define CLI_CMD_ITEM_WORD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "Cli_Cmd_Item.h"

    struct Cli_Cmd_Item Cli_Cmd_Item_Word_Init(char *text, char *help);

#ifdef __cplusplus
}
#endif

#endif /* CLI_CMD_ITEM_WORD_H */
