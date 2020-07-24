/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cmd_Item_Valid_Result_Func.h
 * Author: mike
 *
 * Created on July 11, 2018, 4:50 PM
 */

#ifndef CMD_ITEM_VALID_RESULT_FUNC_H
#define CMD_ITEM_VALID_RESULT_FUNC_H

#include <string>

using namespace std;

#include "Cmd_Item_Valid_Result.h"

class Cmd_Item_Valid_Result_Func {
public:

    static string To_String(Cmd_Item_Valid_Result v) {
        switch (v) {
            case CMD_ITEM_OK: return "OK";
            case CMD_ITEM_OK_CAN_CONTINUE: return "OK_CAN_CONTINUE";
            case CMD_ITEM_NOT_MATCH: return "NOT_MATCH";
            case CMD_ITEM_ERROR: return "ERROR";
            case CMD_ITEM_MATCH_BUT_ERROR: return "MATCH_BUT_ERROR";
            case CMD_ITEM_EMPTY: return "EMPTY";
            case CMD_ITEM_INCOMPLETE: return "INCOMPLETE";
            case CMD_ITEM_INCOMPLETE_STR: return "INCOMPLETE_STR";
            case CMD_ITEM_TOO_LONG: return "TOO_LONG";
            case CMD_ITEM_OUT_OF_RANGE: return "OUT_OF_RANGE";
            case CMD_ITEM_OUT_OF_ORDER: return "OUT_OF_ORDER";
            case CMD_ITEM_UNDEFINED: return "UNDEFINED";
            default: return "???";
        }
    }

};

#endif /* CMD_ITEM_VALID_RESULT_FUNC_H */
