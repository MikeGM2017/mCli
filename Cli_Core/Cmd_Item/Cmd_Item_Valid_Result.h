/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cmd_Item_Valid_Result.h
 * Author: mike
 *
 * Created on July 10, 2018, 8:41 AM
 */

#ifndef CMD_ITEM_VALID_RESULT_H
#define CMD_ITEM_VALID_RESULT_H

enum Cmd_Item_Valid_Result {
    CMD_ITEM_OK,
    CMD_ITEM_OK_CAN_CONTINUE,
    CMD_ITEM_OK_STR_WITHOUT_COMMAS,
    CMD_ITEM_NOT_MATCH,
    CMD_ITEM_ERROR,
    CMD_ITEM_MATCH_BUT_ERROR,
    CMD_ITEM_EMPTY,
    CMD_ITEM_INCOMPLETE,
    CMD_ITEM_INCOMPLETE_STR,
    CMD_ITEM_TOO_LONG,
    CMD_ITEM_OUT_OF_RANGE,
    CMD_ITEM_OUT_OF_ORDER,
    CMD_ITEM_UNDEFINED
};

#endif /* CMD_ITEM_VALID_RESULT_H */
