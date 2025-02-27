/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Input_Item_Type.h
 * Author: mike
 *
 * Created on June 2, 2020, 10:00 AM
 */

#ifndef CLI_INPUT_ITEM_TYPE_H
#define CLI_INPUT_ITEM_TYPE_H

enum Cli_Input_Item_Type {
    CLI_INPUT_ITEM_TYPE_NO,
    CLI_INPUT_ITEM_TYPE_CTRL,
    CLI_INPUT_ITEM_TYPE_SHIFT,
    CLI_INPUT_ITEM_TYPE_CTRL_C,
    CLI_INPUT_ITEM_TYPE_CTRL_Z,
    CLI_INPUT_ITEM_TYPE_CTRL_BACKSLASH,
    CLI_INPUT_ITEM_TYPE_STR,
    CLI_INPUT_ITEM_TYPE_TAB,
    CLI_INPUT_ITEM_TYPE_UP,
    CLI_INPUT_ITEM_TYPE_DOWN,

    CLI_INPUT_ITEM_TYPE_LEFT,
    CLI_INPUT_ITEM_TYPE_RIGHT,
    CLI_INPUT_ITEM_TYPE_HOME,
    CLI_INPUT_ITEM_TYPE_END,

    CLI_INPUT_ITEM_TYPE_BACK,
    CLI_INPUT_ITEM_TYPE_DELETE,

    CLI_INPUT_ITEM_TYPE_CHAR_ADD,

    CLI_INPUT_ITEM_TYPE_NO_ACTION,

    CLI_INPUT_ITEM_TYPE_QUIT
};

#endif /* CLI_INPUT_ITEM_TYPE_H */
