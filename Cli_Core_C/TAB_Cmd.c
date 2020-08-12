/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "TAB_Cmd.h"

void TAB_Cmd_Init(struct TAB_Cmd *tab_cmd, enum TAB_Cmd_ID id, char *text) {
    tab_cmd->ID = id;
    int len = TAB_CMD_TEXT_SIZE_DEF - 1;
    strncpy(tab_cmd->Text, text, len);
    tab_cmd->Text[len] = '\0';
}
