/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cmd_Item_Base.h
 * Author: mike
 *
 * Created on July 10, 2018, 8:41 AM
 */

#ifndef CMD_ITEM_BASE_H
#define CMD_ITEM_BASE_H

#include <limits.h>

#include <string>
#include <vector>

using namespace std;

#include "Cmd_Item_Valid_Result.h"
#include "Cmd_Item_Valid_Result_Func.h"

class Cmd_Item_Base {
protected:
    string Type;
    string Text;
    string Help;

    virtual bool Is_Char_Valid(char c, int pos, int len) {
        return true; // Допустимы любые символы в любой позиции
    }

public:

    string Value_Str;

    Cmd_Item_Base(string text, string help) : Text(text), Help(help) {
        Type = "Base";
    }

    virtual string Debug_Value_Get() {
        return Text;
    }

    string Type_Get() const {
        return Type;
    }

    const string Text_Get() {
        return Text;
    }

    string Help_Get() const {
        return Help;
    }

    virtual bool Is_Str_Valid(string s) {
        for (int pos = 0; pos < s.size(); pos++) {
            if (!Is_Char_Valid(s[pos], pos, s.size())) return false;
        }
        return true;
    }

    virtual Cmd_Item_Valid_Result Parse(string s) {
        Value_Str = s;

        if (s.size() == 0) return CMD_ITEM_EMPTY;

        if (Text == s) return CMD_ITEM_OK;

        return CMD_ITEM_ERROR;
    }

    virtual string To_String() {
        string s = Type + ": Text:\"" + Text_Get() + "\" "
                + ": Value_Str:\"" + Value_Str + "\" ";
        return s;
    }
    
    virtual vector<string> Incomplete_Tail_List_Get(string s) {
        vector<string> tail_list;
        return tail_list;
    }
    
    virtual bool Is_Space_After_Add(string s) {
        return true;
    }

};

#endif /* CMD_ITEM_BASE_H */
