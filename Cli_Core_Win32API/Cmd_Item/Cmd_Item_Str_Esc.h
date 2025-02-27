/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cmd_Item_Str_Esc.h
 * Author: mike
 *
 * Created on January 12, 2024, 1:29 PM
 */

#ifndef CMD_ITEM_STR_ESC_H
#define CMD_ITEM_STR_ESC_H

#include "Cmd_Item_Str.h"

#include <cassert>

class Cmd_Item_Str_Esc : public Cmd_Item_Str {
protected:

    enum ST {
        ST_NO,

        ST_STR_NOT_COMMAS,
        ST_STR_NOT_COMMAS_ESC,

        ST_STR_WITH_COMMAS,
        ST_STR_WITH_COMMAS_ESC,
        ST_STR_WITH_COMMAS_END,

        ST_ERROR,
        ST_LAST,
        ST_UNDEFINED
    };

    void Append_After_ESC(char c, string &s_decoded) {
        if (c == '\\') s_decoded.append(1, '\\');
        else if (c == ' ') s_decoded.append(1, ' ');
        else if (c == '\\') s_decoded.append(1, '\\');
        else if (c == 'n') s_decoded.append(1, '\n');
        else if (c == 'r') s_decoded.append(1, '\r');
        else if (c == 't') s_decoded.append(1, '\t');
        else if (c == '\"') s_decoded.append(1, '\"');
        else if (c == '\'') s_decoded.append(1, '\'');

        else if (c == 'a') s_decoded.append(1, '\a');
        else if (c == 'b') s_decoded.append(1, '\b');
        else if (c == 'f') s_decoded.append(1, '\f');
        else if (c == 'v') s_decoded.append(1, '\v');

        else s_decoded.append(1, c);
    }

    virtual Cmd_Item_Valid_Result Decode(string s, string &s_decoded) {
        Cmd_Item_Valid_Result res = CMD_ITEM_EMPTY;

        ST st = ST_NO;
        ST st_next = ST_NO;

        char c_commas = '\0';

        for (int i = 0; i < s.size(); i++) {
            char c = s[i];

            switch (st) {

                    // ST_NO -> ST_STR_NOT_COMMAS / ST_STR_NOT_COMMAS_ESC
                case ST_NO:
                {
                    if (c != '\"' && c != '\'') {
                        if (c != '\\') {
                            st_next = ST_STR_NOT_COMMAS;
                            s_decoded.append(1, c);
                            res = CMD_ITEM_OK_STR_WITHOUT_COMMAS; //CMD_ITEM_OK;
                        } else {
                            st_next = ST_STR_NOT_COMMAS_ESC;
                            //s_decoded.append(1, c); // Skip
                            res = CMD_ITEM_INCOMPLETE_STR;
                        }
                    } else {
                        c_commas = c;
                        st_next = ST_STR_WITH_COMMAS;
                        //s_decoded.append(1, c); // Skip
                        res = CMD_ITEM_INCOMPLETE_STR;
                    }
                }
                    break;

                    // ST_STR_NOT_COMMAS -> ST_STR_NOT_COMMAS / ST_STR_NOT_COMMAS_ESC / ST_ERROR
                case ST_STR_NOT_COMMAS:
                {
                    if (c != '\\') {
                        if (c != '\"' && c != '\'') {
                            st_next = ST_STR_NOT_COMMAS;
                            s_decoded.append(1, c);
                            res = CMD_ITEM_OK_STR_WITHOUT_COMMAS; //CMD_ITEM_OK;
                        } else {
                            st_next = ST_ERROR;
                            s_decoded.append(1, c);
                            res = CMD_ITEM_ERROR;
                        }
                    } else {
                        st_next = ST_STR_NOT_COMMAS_ESC;
                        //s_decoded.append(1, c); // Skip
                        res = CMD_ITEM_INCOMPLETE_STR;
                    }
                }
                    break;

                    // ST_STR_NOT_COMMAS_ESC -> ST_STR_NOT_COMMAS
                case ST_STR_NOT_COMMAS_ESC:
                {
                    st_next = ST_STR_NOT_COMMAS;
                    Append_After_ESC(c, s_decoded);
                    res = CMD_ITEM_OK_STR_WITHOUT_COMMAS; //CMD_ITEM_OK;
                }
                    break;

                    // ST_STR_WITH_COMMAS -> ST_STR_WITH_COMMAS / ST_STR_WITH_COMMAS_ESC
                case ST_STR_WITH_COMMAS:
                {
                    if (c != c_commas) {
                        if (c != '\\') {
                            st_next = ST_STR_WITH_COMMAS;
                            s_decoded.append(1, c);
                            res = CMD_ITEM_INCOMPLETE_STR;
                        } else {
                            st_next = ST_STR_WITH_COMMAS_ESC;
                            //s_decoded.append(1, c); // Skip
                            res = CMD_ITEM_INCOMPLETE_STR;
                        }

                    } else {
                        st_next = ST_STR_WITH_COMMAS_END;
                        //s_decoded.append(1, c); // Skip
                        res = CMD_ITEM_OK;
                    }
                }
                    break;

                    // ST_STR_WITH_COMMAS_ESC -> ST_STR_WITH_COMMAS
                case ST_STR_WITH_COMMAS_ESC:
                {
                    st_next = ST_STR_WITH_COMMAS;
                    Append_After_ESC(c, s_decoded);
                    res = CMD_ITEM_INCOMPLETE_STR;
                }
                    break;

                    // ST_STR_WITH_COMMAS_END -> ST_ERROR
                case ST_STR_WITH_COMMAS_END:
                {
                    st_next = ST_ERROR;
                    s_decoded.append(1, c);
                    res = CMD_ITEM_ERROR;
                }
                    break;

                    // ST_ERROR -> ST_ERROR
                default:
                {
                    st_next = ST_ERROR;
                    s_decoded.append(1, c);
                    res = CMD_ITEM_ERROR;
                }
                    break;

            }

            st = st_next;

        }

        return res;
    }

public:

    Cmd_Item_Str_Esc(string text, string help) : Cmd_Item_Str(text, help) {
        Type = "Str_Esc";
        Version = "0.02";
    }

    virtual Cmd_Item_Valid_Result Parse(string s) {
        string s_decoded;
        Cmd_Item_Valid_Result res = Decode(s, s_decoded);
        if (res == CMD_ITEM_OK || res == CMD_ITEM_OK_STR_WITHOUT_COMMAS) {
            Value_Str = s_decoded;
        } else {
            Value_Str = s; // Error or Incomplete
        }
        return res;
    }

    virtual bool Is_Char_Valid(char c, int pos, int len) {
        return true; // Допустимы все символы в любой позиции
    }

    virtual bool Is_Space_After_Add(string s) {
        if (s.size() >= 2) {
            if (s[0] == '\"' && s[s.size() - 1] == '\"') return true;
            if (s[0] == '\'' && s[s.size() - 1] == '\'') return true;
        }
        return false;
    }

};

#endif /* CMD_ITEM_STR_ESC_H */
