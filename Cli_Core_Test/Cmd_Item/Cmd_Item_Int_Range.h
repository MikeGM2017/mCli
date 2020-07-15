/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cmd_Item_Int_Range.h
 * Author: mike
 *
 * Created on July 15, 2020, 9:02 AM
 */

#ifndef CMD_ITEM_INT_RANGE_H
#define CMD_ITEM_INT_RANGE_H

#include "Cmd_Item_Int.h"

class Cmd_Item_Int_Range : public Cmd_Item_Int {
protected:
    int Min;
    int Max;

public:

    Cmd_Item_Int_Range(int min, int max, string text, string help) : Cmd_Item_Int(text, help), Min(min), Max(max) {
        Type = "Int_Range";
    }

    virtual string Debug_Value_Get() {
        stringstream s_str;
        s_str << Min;
        return s_str.str();
    }

    virtual Cmd_Item_Valid_Result Parse(string s) {
        Value_Str = s;
        Value_Int = 0;

        if (s.size() == 0) return CMD_ITEM_EMPTY;

        Cmd_Item_Valid_Result res = Cmd_Item_Int::Parse(s);
        if (res == CMD_ITEM_OK) {
            int v = atoi(s.c_str());
            if (v >= Min && v <= Max) {
                Value_Int = v;
                return CMD_ITEM_OK;
            }
            return CMD_ITEM_OUT_OF_RANGE;
        }
        return res;
    }

    virtual string To_String() {
        stringstream s_str;
        s_str << "Int_Range: " << Min << "..." << Max << ": " << Cmd_Item_Int::To_String();
        return s_str.str();
    }

};

#endif /* CMD_ITEM_INT_RANGE_H */
