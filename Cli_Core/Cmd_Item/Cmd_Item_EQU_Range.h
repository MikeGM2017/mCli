/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cmd_Item_EQU_Range.h
 * Author: mike
 *
 * Created on December 2, 2020, 2:34 PM
 */

#ifndef CMD_ITEM_EQU_RANGE_H
#define CMD_ITEM_EQU_RANGE_H

#include "Cmd_Item_EQU.h"

class Cmd_Item_EQU_Range : public Cmd_Item_EQU {
public:

    vector<string> Words;

    Cmd_Item_EQU_Range(string text, string help, vector<string> words) : Cmd_Item_EQU(text, help), Words(words) {
        Type = "EQU_Range";
    }

    virtual string Debug_Value_Get() {
        if (Words.size() > 0)
            return Words[0];
        return Text;
    }

    virtual Cmd_Item_Valid_Result Parse(string s) {
        Value_Str = s;

        if (s.size() == 0) return CMD_ITEM_EMPTY;

        for (int pos = 0; pos < s.size(); pos++) {
            if (!Is_Char_Valid(s[pos], pos, s.size())) return CMD_ITEM_ERROR;
        }

        bool is_incomplete_found = false;
        for (int i = 0; i < Words.size(); i++) {
            if (Words[i] == s) return CMD_ITEM_OK;
            if (Words[i].substr(0, s.size()) == s) is_incomplete_found = true;
        }
        if (is_incomplete_found)
            return CMD_ITEM_INCOMPLETE;

        return CMD_ITEM_ERROR;
    }

    virtual bool Is_Space_After_Add(string s) {
        Cmd_Item_Valid_Result res = Parse(s);
        if (res == CMD_ITEM_OK)
            return true;
        return false;
    }

    virtual vector<string> Incomplete_Tail_List_Get(string s) {
        vector<string> tail_list;
        for (int i = 0; i < Words.size(); i++) {
            if (Words[i].substr(0, s.size()) == s) {
                tail_list.push_back(Words[i].substr(s.size()));
            }
        }
        return tail_list;
    }

};

#endif /* CMD_ITEM_EQU_RANGE_H */
