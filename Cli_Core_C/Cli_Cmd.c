/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Cli_Cmd.h"

void Cli_Cmd_Init_Base(struct Cli_Cmd *cmd, int id, char *text, char *help) {
    memset(cmd, 0, sizeof (struct Cli_Cmd));
    cmd->ID = id;
    cmd->Privilege = CMD_PRIVILEGE_ROOT_DEF;
    int len_t = CLI_CMD_TEXT_SIZE_DEF - 1;
    strncpy(cmd->Text, text, len_t);
    cmd->Text[len_t] = '\0';
    int len_h = CLI_CMD_HELP_SIZE_DEF - 1;
    strncpy(cmd->Help, help, len_h);
    cmd->Help[len_h] = '\0';
}

struct Cli_Cmd Cli_Cmd_Init(int id, char *text, char *help) {
    struct Cli_Cmd cmd;
    Cli_Cmd_Init_Base(&cmd, id, text, help);
    return cmd;
}

void Cli_Cmd_Add_Item(struct Cli_Cmd *cmd, struct Cli_Cmd_Item *cmd_item) {
    if (!cmd->Item_Head) {
        cmd->Item_Head = cmd_item;
        cmd->Item_Tail = cmd_item;
    } else {
        cmd->Item_Tail->Cmd_Item_Next = cmd_item;
        cmd->Item_Tail = cmd_item;
    }
    cmd->Items_Size++;
}
