/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Cmd_Item_Type.h
 * Author: mike
 *
 * Created on August 3, 2020, 4:55 PM
 */

#ifndef CLI_CMD_ITEM_TYPE_H
#define CLI_CMD_ITEM_TYPE_H

#ifdef __cplusplus
extern "C" {
#endif

    enum Cli_Cmd_Item_Type {
        CLI_CMD_ITEM_TYPE_NO,

        CLI_CMD_ITEM_TYPE_REM,

        CLI_CMD_ITEM_TYPE_INT,
        CLI_CMD_ITEM_TYPE_INT_RANGE,
        CLI_CMD_ITEM_TYPE_INT_LIST,

        CLI_CMD_ITEM_TYPE_STR,
        CLI_CMD_ITEM_TYPE_DATE,
        CLI_CMD_ITEM_TYPE_DATE_TIME,
        CLI_CMD_ITEM_TYPE_TIME,

        CLI_CMD_ITEM_TYPE_WORD,
        CLI_CMD_ITEM_TYPE_WORD_RANGE,
        CLI_CMD_ITEM_TYPE_WORD_LIST,

        CLI_CMD_ITEM_TYPE_IP4,
        CLI_CMD_ITEM_TYPE_IP6,
        CLI_CMD_ITEM_TYPE_MAC,

        CLI_CMD_ITEM_TYPE_LAST,
        CLI_CMD_ITEM_TYPE_UNDEFINED
    };

#ifdef __cplusplus
}
#endif

#endif /* CLI_CMD_ITEM_TYPE_H */
