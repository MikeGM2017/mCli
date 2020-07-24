/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cmd_Item_IP4.h
 * Author: mike
 *
 * Created on July 13, 2020, 9:11 AM
 */

#ifndef CMD_ITEM_IP4_H
#define CMD_ITEM_IP4_H

#include "Cmd_Item_Base.h"

class Cmd_Item_IP4 : public Cmd_Item_Base {
public:

    Cmd_Item_IP4(string text, string help) : Cmd_Item_Base(text, help) {
        Type = "IP4";
    }

    virtual string Debug_Value_Get() {
        return "1.2.3.4";
    }

    virtual Cmd_Item_Valid_Result Parse(string s) {
        Value_Str = s;

        if (s.size() == 0) return CMD_ITEM_EMPTY;

        for (int pos = 0; pos < s.size(); pos++) {
            if (!Is_Char_Valid(s[pos], pos, s.size())) return CMD_ITEM_ERROR;
        }

        int pointCount = 0;
        int n = 0;
        int nCount = 0;
        bool nPrev = false;
        bool is_Point_Double = false;

        int nn_count = 0;
        for (int pos = 0; pos < s.size(); pos++) {
            char c = s[pos];
            if (c >= '0' && c <= '9') {
                n = n * 10 + c - '0';
                nn_count++;
                if (nn_count > 3) return CMD_ITEM_ERROR;
                if (n > 255) return CMD_ITEM_OUT_OF_RANGE;
                if (!nPrev) {
                    nPrev = true;
                    nCount++;
                }
            }
            if (c == '.') {
                if (!nPrev)
                    is_Point_Double = true;
                pointCount++;
                n = 0;
                nPrev = false;
                nn_count = 0;
            }
        }

        if (is_Point_Double) return CMD_ITEM_ERROR;

        if (pointCount < 3) return CMD_ITEM_INCOMPLETE_STR;
        if (pointCount > 3) return CMD_ITEM_ERROR;

        if (nCount < 4) return CMD_ITEM_INCOMPLETE_STR;
        if (nCount > 4) return CMD_ITEM_ERROR;

        return CMD_ITEM_OK;
    }

    virtual bool Is_Char_Valid(char c, int pos, int len) {
        if (c >= '0' && c <= '9')
            return true;
        if (pos >= 1 && c == '.')
            return true;
        return false;
    }

    virtual bool Is_Space_After_Add(string s) {
        if (s.size() >= 7) {
            Cmd_Item_Valid_Result res = Parse(s);
            if (res == CMD_ITEM_OK)
                return true;
        }
        return false;
    }

};

#endif /* CMD_ITEM_IP4_H */
