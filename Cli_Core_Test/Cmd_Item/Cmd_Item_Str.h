/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cmd_Item_Str.h
 * Author: mike
 *
 * Created on July 10, 2018, 12:16 PM
 */

#ifndef CMD_ITEM_STR_H
#define CMD_ITEM_STR_H

#include "Cmd_Item_Base.h"

class Cmd_Item_Str : public Cmd_Item_Base {
protected:

    Cmd_Item_Valid_Result Decode(string s_src, string &s_dst) {
        Cmd_Item_Valid_Result decode_res = CMD_ITEM_OK;
        bool is_in_commas = false;
        char c_commas = '\0';
        char c_last = '\0';
        bool is_escape = false;
        s_dst = "";
        for (int i = 0; i < s_src.size(); i++) {
            if (i == 0) {
                char c = s_src[i];
                if (c == '"' || c == '\'') {
                    is_in_commas = true;
                    c_commas = c;
                }
            }
            char c = s_src[i];
            switch (c) {
                case '\\':
                    decode_res = CMD_ITEM_INCOMPLETE;
                    is_escape = true;
                    break;
                default:
                    if (is_escape) {
                        switch (c) {
                            case 'n':
                                c = '\n';
                                c_last = c;
                                break;
                            case 'r':
                                c = '\r';
                                c_last = c;
                                break;
                            case 't':
                                c = '\t';
                                c_last = c;
                                break;
                            case '\"':
                            case '\'':
                                c_last = 0; // @Attention: Escaped '"' and '''
                                break;
                            default:
                                c_last = c;
                        }
                    } else {
                        c_last = c;
                    }
                    s_dst.append(&c, 1);
                    decode_res = CMD_ITEM_OK;
                    is_escape = false;
                    break;
            }
        }

        if (is_in_commas && c_commas != c_last)
            return CMD_ITEM_INCOMPLETE;

        if (c_last == '"' || c_last == '\'') {
            if (c_last != s_src[0])
                return CMD_ITEM_ERROR;
        }

        return decode_res;
    }

public:

    Cmd_Item_Str(string text, string help) : Cmd_Item_Base(text, help) {
        Type = "Str";
    }

    virtual string Debug_Value_Get() {
        return "\"<str>\"";
    }

    virtual Cmd_Item_Valid_Result Parse(string s) {
        if (s.size() == 0) return CMD_ITEM_EMPTY; // @Attention

        //if (s == "\"\"") s = ""; // @Attention

        if (s.size() >= 2 && s[0] == '"' && s[s.size() - 1] == '"')
            s = s.substr(1, s.size() - 2);
        else if (s.size() >= 2 && s[0] == '\'' && s[s.size() - 1] == '\'')
            s = s.substr(1, s.size() - 2);

        Value_Str = s; // @Attention: s is not decoded with escapes

        if (s.size() == 0) return CMD_ITEM_OK; // @Attention

        if (s.size() == 1) {
            if (s[0] == '\n') return CMD_ITEM_ERROR;
            if (s[0] == '\r') return CMD_ITEM_ERROR;
            if (s[0] == '"') return CMD_ITEM_INCOMPLETE;
            if (s[0] == '\'') return CMD_ITEM_INCOMPLETE;
            if (s[0] != '"' && s[0] != '\'') return CMD_ITEM_OK;
        }

        //        if (s.size() >= 1 && s[0] != '"') {
        //            return INPUT_ERROR;
        //        }

        if (s.size() == 2) {
            if (s[0] == '"' && s[1] == '"') return CMD_ITEM_OK;
            if (s[0] == '\'' && s[1] == '\'') return CMD_ITEM_OK;
            if (s[0] == '"' && s[1] != '"') return CMD_ITEM_INCOMPLETE;
            if (s[0] == '\'' && s[1] != '\'') return CMD_ITEM_INCOMPLETE;
            if (s[0] != '\\' && s[1] != '\\') {
                if (s[0] != '"' && s[1] == '"') return CMD_ITEM_ERROR;
                if (s[0] != '\'' && s[1] == '\'') return CMD_ITEM_ERROR;
                if (s[0] != '"' && s[1] != '"') return CMD_ITEM_OK;
                if (s[0] != '\'' && s[1] != '\'') return CMD_ITEM_OK;
            }
        }

        for (int pos = 0; pos < s.size(); pos++) {
            if (!Is_Char_Valid(s[pos], pos, s.size())) return CMD_ITEM_ERROR;
        }

        //if (s[0] == '"' && s[s.size() - 1] != '"') return INPUT_INCOMPLETE;

        //if (s[0] != '"' && s[s.size() - 1] == '"') return INPUT_ERROR;

        //return INPUT_OK;

        Cmd_Item_Valid_Result decode_res = Decode(s, Value_Str); // @Attention: s is decoded with escapes
        return decode_res;

    }

    virtual bool Is_Char_Valid(char c, int pos, int len) {
        return true; // Допустимы все символы в любой позиции
    }

};

#endif /* CMD_ITEM_STR_H */
