/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cmd_Item_Rem.h
 * Author: mike
 *
 * Created on July 16, 2018, 4:15 PM
 */

#ifndef CMD_ITEM_INPUT_REM_H
#define CMD_ITEM__REM_H

#include "Cmd_Item_Base.h"

class Cmd_Item_Rem : public Cmd_Item_Base {
public:

    Cmd_Item_Rem(string str_rem, string help) : Cmd_Item_Base(str_rem, help) {
    }

    virtual string Debug_Value_Get() {
        return Text + " - rem";
    }

    virtual Cmd_Item_Valid_Result Parse(string s) {
        Value_Str = s;

        if (s.size() == 0) return CMD_ITEM_EMPTY;

        if (s.substr(0, Text.size()) == Text) return CMD_ITEM_OK;

        return CMD_ITEM_ERROR;
    }

};

#endif /* CMD_ITEM__REM_H */
