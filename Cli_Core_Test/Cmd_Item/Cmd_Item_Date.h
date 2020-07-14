/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cmd_Item_Date.h
 * Author: mike
 *
 * Created on July 14, 2020, 10:56 AM
 */

#ifndef CMD_ITEM_DATE_H
#define CMD_ITEM_DATE_H

#include "Cmd_Item_Str.h"

class Cmd_Item_Date : public Cmd_Item_Str {
public:

    Cmd_Item_Date(string text, string help) : Cmd_Item_Str(text, help) {
        Type = "Date";
    }

    virtual string Debug_Value_Get() {
        return "\"2018-01-02\"";
    }

    virtual bool Is_Char_Valid(char c, int pos, int len) {
        switch (pos) {
            case 0:
            case 11:
                return (c == '"');
            case 5:
            case 8:
                return (c == '-');
        }
        return (c >= '0' && c <= '9');
    }

    virtual Cmd_Item_Valid_Result Parse(string s) {
        Value_Str = s;

        if (s.size() == 0) return CMD_ITEM_EMPTY;

        if (s.size() == 1 && s[0] == '"') return CMD_ITEM_INCOMPLETE;
        if (s.size() >= 1 && s[0] != '"') return CMD_ITEM_ERROR;

        for (int pos = 0; pos < s.size(); pos++) {
            if (!Is_Char_Valid(s[pos], pos, s.size())) return CMD_ITEM_ERROR;
        }

        // Date
        if (s.size() >= 7) {
            int m = s[6] - '0';
            if (m < 0 || m > 1) return CMD_ITEM_OUT_OF_RANGE;
            if (s.size() >= 8) {
                int mm = atoi(s.c_str() + 6);
                if (mm == 0 || mm > 12) return CMD_ITEM_OUT_OF_RANGE;
            }
        }

        if (s.size() >= 10) {
            int d = s[9] - '0';
            if (d < 0 || d > 3) return CMD_ITEM_OUT_OF_RANGE;
            if (s.size() >= 11) {
                int dd = atoi(s.c_str() + 9);
                if (dd == 0 || dd > 31) return CMD_ITEM_OUT_OF_RANGE;
            }
        }

        if (s.size() == 2) {
            if (s[0] == '"' && s[1] == '"') return CMD_ITEM_ERROR; //CMD_ITEM_OK;
            return CMD_ITEM_INCOMPLETE;
        }

        if (s[s.size() - 1] != '"') return CMD_ITEM_INCOMPLETE;

        return CMD_ITEM_OK;
    }
    
    virtual bool Is_Space_After_Add(string s) {
        if (s.size() >= 12) {
            Cmd_Item_Valid_Result res = Parse(s);
            if (res == CMD_ITEM_OK)
                return true;
        }
        return false;
    }

};

#endif /* CMD_ITEM_DATE_H */
