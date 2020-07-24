/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cmd_Item_Time.h
 * Author: mike
 *
 * Created on July 14, 2020, 10:57 AM
 */

#ifndef CMD_ITEM_TIME_H
#define CMD_ITEM_TIME_H

#include "Cmd_Item_Date.h"

class Cmd_Item_Time : public Cmd_Item_Date {
public:

    Cmd_Item_Time(string text, string help) : Cmd_Item_Date(text, help) {
        Type = "Time";
    }

    virtual string Debug_Value_Get() {
        return "\"12-13-14\"";
    }

    virtual bool Is_Char_Valid(char c, int pos, int len) {
        if (pos == 6 && c == '"')
            return true; // "HH-MM" - без секунд
        switch (pos) {
            case 0:
            case 9:
                return (c == '"');
            case 3:
            case 6:
                return (c == '-');
        }
        return (c >= '0' && c <= '9');
    }

    virtual Cmd_Item_Valid_Result Parse(string s) {
        Value_Str = s;

        if (s.size() == 0) return CMD_ITEM_EMPTY;

        if (s.size() == 1 && s[0] == '"') return CMD_ITEM_INCOMPLETE_STR;
        if (s.size() >= 1 && s[0] != '"') return CMD_ITEM_ERROR;

        for (int pos = 0; pos < s.size(); pos++) {
            if (!Is_Char_Valid(s[pos], pos, s.size())) return CMD_ITEM_ERROR;
        }

        // Time
        if (s.size() >= 2) {
            int H = s[1] - '0';
            if (H < 0 || H > 2) return CMD_ITEM_OUT_OF_RANGE;
            int HH = atoi(s.c_str() + 1);
            if (HH > 23) return CMD_ITEM_OUT_OF_RANGE;
        }

        if (s.size() >= 5) {
            int M = s[4] - '0';
            if (M < 0 || M > 5) return CMD_ITEM_OUT_OF_RANGE;
            int MM = atoi(s.c_str() + 4);
            if (MM > 59) return CMD_ITEM_OUT_OF_RANGE;
        }

        if (s.size() >= 8) {
            int S = s[7] - '0';
            if (S < 0 || S > 5) return CMD_ITEM_OUT_OF_RANGE;
            int SS = atoi(s.c_str() + 7);
            if (SS > 59) return CMD_ITEM_OUT_OF_RANGE;
        }

        if (s.size() == 2) {
            if (s[0] == '"' && s[1] == '"') return CMD_ITEM_ERROR; //CMD_ITEM_OK;
            return CMD_ITEM_INCOMPLETE_STR;
        }

        if (s[s.size() - 1] != '"') return CMD_ITEM_INCOMPLETE_STR;

        return CMD_ITEM_OK;
    }
    
    virtual bool Is_Space_After_Add(string s) {
        if (s.size() >= 10) {
            Cmd_Item_Valid_Result res = Parse(s);
            if (res == CMD_ITEM_OK)
                return true;
        }
        return false;
    }

};

#endif /* CMD_ITEM_TIME_H */
