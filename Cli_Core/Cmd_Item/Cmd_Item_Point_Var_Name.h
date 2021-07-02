/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cmd_Item_Point_Var_Name.h
 * Author: mike
 *
 * Created on June 7, 2021, 10:15 AM
 */

#ifndef CMD_ITEM_POINT_VAR_NAME_H
#define CMD_ITEM_POINT_VAR_NAME_H

#include "Cmd_Item_Word.h"

class Cmd_Item_Point_Var_Name : public Cmd_Item_Word {
protected:

    virtual bool Is_Char_Valid(char c, int pos, int len) {

        if (len < 2) return false;

        if (pos == 0 && c != '.') return false;
        if (c == '.') return true;
        if (c >= 'a' && c <= 'z') return true;
        if (c >= 'A' && c <= 'Z') return true;
        if (c == '_') return true;
        if (pos > 1 && c >= '0' && c <= '9') return true;

        return false;
    }

public:

    virtual Cmd_Item_Valid_Result Parse(string s) {
        Value_Str = s;

        if (s.size() == 0) return CMD_ITEM_EMPTY;

        for (int pos = 0; pos < s.size(); pos++) {
            if (!Is_Char_Valid(s[pos], pos, s.size())) return CMD_ITEM_ERROR;
        }

        return CMD_ITEM_OK;
    }

    Cmd_Item_Point_Var_Name(string text, string help) : Cmd_Item_Word(text, help) {
        Type = "Point_Var_Name";
    }

};

#endif /* CMD_ITEM_POINT_VAR_NAME_H */
