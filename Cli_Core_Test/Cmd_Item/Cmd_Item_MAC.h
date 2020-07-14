/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cmd_Item_MAC.h
 * Author: mike
 *
 * Created on July 14, 2020, 9:06 AM
 */

#ifndef CMD_ITEM_MAC_H
#define CMD_ITEM_MAC_H

#include "Cmd_Item_Base.h"

class Cmd_Item_MAC : public Cmd_Item_Base {
protected:

    virtual bool Is_Char_Valid(char c, int pos, int len) {
        switch (pos) {
            case 2:
            case 5:
            case 8:
            case 11:
            case 14:
                return (c == ':' || c == '-');
            default:
                if (c >= '0' && c <= '9')
                    return true;
                if (c >= 'a' && c <= 'f')
                    return true;
                if (c >= 'A' && c <= 'F')
                    return true;
        }
        return false;
    }

public:

    Cmd_Item_MAC(string text, string help) : Cmd_Item_Base(text, help) {
        Type = "MAC";
    }

    virtual string Debug_Value_Get() {
        return "11:22:33:DD:EE:FF";
    }

    virtual Cmd_Item_Valid_Result Parse(string s) {
        Value_Str = s;

        if (s.size() == 0) return CMD_ITEM_EMPTY;

        for (int pos = 0; pos < s.size(); pos++) {
            if (!Is_Char_Valid(s[pos], pos, s.size())) return CMD_ITEM_ERROR;
        }

        if (s.size() < 17) return CMD_ITEM_INCOMPLETE;
        if (s.size() > 17) return CMD_ITEM_ERROR;

        return CMD_ITEM_OK;
    }
    
    virtual bool Is_Space_After_Add(string s) {
        if (s.size() >= 17) {
            Cmd_Item_Valid_Result res = Parse(s);
            if (res == CMD_ITEM_OK)
                return true;
        }
        return false;
    }

};

#endif /* CMD_ITEM_MAC_H */
