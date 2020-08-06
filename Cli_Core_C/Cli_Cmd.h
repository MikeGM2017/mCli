/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Cmd.h
 * Author: mike
 *
 * Created on August 3, 2020, 4:56 PM
 */

#ifndef CLI_CMD_H
#define CLI_CMD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "Cli_Cmd_Privilege_ID.h"
#include "Cli_Cmd_Item.h"

#define CLI_CMD_TEXT_SIZE_DEF 32
#define CLI_CMD_LEVEL_SIZE_DEF 32
#define CLI_CMD_HELP_SIZE_DEF 64

    struct Cli_Cmd {
        char Text[CLI_CMD_TEXT_SIZE_DEF];
        char Level[CLI_CMD_LEVEL_SIZE_DEF];
        char Help[CLI_CMD_HELP_SIZE_DEF];

        int ID;
        enum Cli_Cmd_Privilege_ID Privilege;
        int Is_Global;
        int Is_Set;
        int Min;
        int Max;

        struct Cli_Cmd_Item *Item_Head;
        struct Cli_Cmd_Item *Item_Tail;
        int Items_Size;

        struct Cli_Cmd *Cmd_Next;
    };

    void Cli_Cmd_Init_Base(struct Cli_Cmd *cmd, int id, char *text, char *help);

    struct Cli_Cmd Cli_Cmd_Init(int id, char *text, char *help);

    void Cli_Cmd_Add_Item(struct Cli_Cmd *cmd, struct Cli_Cmd_Item *cmd_item);

#ifdef __cplusplus
}
#endif

#endif /* CLI_CMD_H */
