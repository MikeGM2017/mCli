/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TAB_Cmd.h
 * Author: mike
 *
 * Created on August 10, 2020, 10:30 AM
 */

#ifndef TAB_CMD_H
#define TAB_CMD_H

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>

#include "TAB_Cmd_ID.h"

#define TAB_CMD_TEXT_SIZE_DEF 1024

    struct TAB_Cmd {
        enum TAB_Cmd_ID ID;
        char Text[TAB_CMD_TEXT_SIZE_DEF];
    };

    void TAB_Cmd_Init(struct TAB_Cmd *tab_cmd, enum TAB_Cmd_ID id, char *text);

#ifdef __cplusplus
}
#endif

#endif /* TAB_CMD_H */
