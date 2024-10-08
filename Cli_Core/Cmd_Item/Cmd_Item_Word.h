/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cmd_Item_Word.h
 * Author: mike
 *
 * Created on July 12, 2018, 3:26 PM
 */

#ifndef CMD_ITEM_WORD_H
#define CMD_ITEM_WORD_H

#include "Cmd_Item_Base.h"

class Cmd_Item_Word : public Cmd_Item_Base {
protected:

    virtual bool Is_Char_Valid(char c, int pos, int len) {
        if (c >= 'a' && c <= 'z') return true;
        if (c >= 'A' && c <= 'Z') return true;
        if (c == '_') return true;
        //if (pos > 0 && c >= '0' && c <= '9') return true;
        if (c >= '0' && c <= '9') return true;
        if (c == '-') return true;
        return false;
    }

public:

    Cmd_Item_Word(string text, string help) : Cmd_Item_Base(text, help) {
        Type = "Word";
        Version = "0.02";
    }

    virtual string Debug_Value_Get() {
        return Text;
    }

    virtual Cmd_Item_Valid_Result Parse(string s) {
        Value_Str = s;

        if (s.size() == 0) return CMD_ITEM_EMPTY;

        for (int pos = 0; pos < s.size(); pos++) {
            if (!Is_Char_Valid(s[pos], pos, s.size())) return CMD_ITEM_ERROR;
        }

        if (Text == s) return CMD_ITEM_OK;

        if (s.size() < Text.size()) {
            if (Text.substr(0, s.size()) == s) {
                return CMD_ITEM_INCOMPLETE;
            }
        }

        return CMD_ITEM_ERROR;
    }

    virtual vector<string> Incomplete_Tail_List_Get(string s) {
        vector<string> tail_list;
        if (s.size() < Text.size()) {
            if (Text.substr(0, s.size()) == s) {
                tail_list.push_back(Text.substr(s.size()));
            }
        }
        return tail_list;
    }

};

#endif /* CMD_ITEM_WORD_H */
