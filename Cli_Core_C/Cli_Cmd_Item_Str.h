/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Cmd_Item_Str.h
 * Author: mike
 *
 * Created on August 6, 2020, 1:43 PM
 */

#ifndef CLI_CMD_ITEM_STR_H
#define CLI_CMD_ITEM_STR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "Cli_Cmd_Item.h"

    struct Cli_Cmd_Item Cli_Cmd_Item_Str_Init(char *text, char *help);

#ifdef __cplusplus
}
#endif

#endif /* CLI_CMD_ITEM_STR_H */
