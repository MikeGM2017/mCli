/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cmd_Item_Int.h
 * Author: mike
 *
 * Created on July 15, 2020, 9:04 AM
 */

#ifndef CMD_ITEM_INT_H
#define CMD_ITEM_INT_H

#include <sstream>

using namespace std;

#include "Cmd_Item_Base.h"

class Cmd_Item_Int : public Cmd_Item_Base {
protected:

    virtual bool Is_Char_Valid(char c, int pos, int len) {
        if (pos == 0) {
            if (c == '+') return true;
            if (c == '-') return true;
        }
        return (c >= '0' && c <= '9');
    }

    virtual int Char_To_N(char c) {
        if (c >= '0' && c <= '9')
            return c - '0';
        return 0;
    }

public:

    int Value_Int;

    Cmd_Item_Int(string text, string help) : Cmd_Item_Base(text, help), Value_Int(0) {
        Type = "Int";
        Version = "0.02";
    }

    virtual string Debug_Value_Get() {
        return "1";
    }

    virtual Cmd_Item_Valid_Result Parse(string s) {
        Value_Str = s;
        Value_Int = 0;

        if (s.size() == 0) return CMD_ITEM_EMPTY;

        for (int pos = 0; pos < s.size(); pos++) {
            if (!Is_Char_Valid(s[pos], pos, s.size())) return CMD_ITEM_ERROR;
        }

        long v = 0;
        long vMax = INT_MAX;
        for (int pos = 0; pos < s.size(); pos++) {
            int n = Char_To_N(s[pos]);
            v = v * 10 + n;
            if (v > vMax) return CMD_ITEM_TOO_LONG;
        }

        Value_Int = v;

        return CMD_ITEM_OK;
    }

    virtual bool Is_Space_After_Add(string s) {
        Cmd_Item_Valid_Result res = Parse(s);
        if (res == CMD_ITEM_OK)
            return true;
        return false;
    }

};

#endif /* CMD_ITEM_INT_H */
