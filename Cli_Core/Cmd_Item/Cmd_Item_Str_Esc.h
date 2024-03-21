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

    virtual Cmd_Item_Valid_Result Decode(string s, string &s_decoded) {
        string s_decoded_escaped;
        int st = 0;
        for (int i = 0; i < s.length(); i++) {
            char c = s[i];
            switch (st) {
                case 0:
                    if (c != '\\') {
                        s_decoded.append(1, c);
                        s_decoded_escaped.append(1, 'n');
                    } else {
                        st = 1;
                        //s_decoded_escaped.append(1, 'n'); //@Warning: Skip!
                    }
                    break;
                case 1:
                    switch (c) {
                        case '\"':
                            s_decoded.append(1, '\"');
                            //s_decoded_escaped[s_decoded_escaped.length() - 1] = 'Y';
                            s_decoded_escaped.append(1, 'Y');
                            break;
                        case '\'':
                            s_decoded.append(1, '\'');
                            //s_decoded_escaped[s_decoded_escaped.length() - 1] = 'Y';
                            s_decoded_escaped.append(1, 'Y');
                            break;
                        case '\\':
                            s_decoded.append(1, '\\');
                            s_decoded_escaped.append(1, 'n');
                            break;
                        case ' ':
                            s_decoded.append(1, ' ');
                            s_decoded_escaped.append(1, 'n');
                            break;
                        case 'a':
                            s_decoded.append(1, '\a');
                            s_decoded_escaped.append(1, 'n');
                            break;
                        case 'b':
                            s_decoded.append(1, '\b');
                            s_decoded_escaped.append(1, 'n');
                            break;
                        case 'f':
                            s_decoded.append(1, '\f');
                            s_decoded_escaped.append(1, 'n');
                            break;
                        case 'n':
                            s_decoded.append(1, '\n');
                            s_decoded_escaped.append(1, 'n');
                            break;
                        case 'r':
                            s_decoded.append(1, '\r');
                            s_decoded_escaped.append(1, 'n');
                            break;
                        case 't':
                            s_decoded.append(1, '\t');
                            s_decoded_escaped.append(1, 'n');
                            break;
                        case 'v':
                            s_decoded.append(1, '\v');
                            s_decoded_escaped.append(1, 'n');
                            break;
                        default:
                            s_decoded.append(1, c);
                            s_decoded_escaped.append(1, 'n');
                            break;
                    }
                    st = 0;
                    break;
            }
        }
        if (st == 0) {
            if (s_decoded.length() >= 2) {
                int s_decoded_length = s_decoded.length();
                int s_decoded_escaped_length = s_decoded_escaped.length();
                assert(s_decoded.length() == s_decoded_escaped.length());
                if (s_decoded[0] == '\"' && s_decoded[s_decoded.length() - 1] == '\"') {
                    if (s_decoded_escaped[0] == 'n' && s_decoded_escaped[s_decoded.length() - 1] == 'n') {
                        s_decoded = s_decoded.substr(1, s_decoded.length() - 2);
                        return CMD_ITEM_OK_STR_WITHOUT_COMMAS;
                    }
                    return CMD_ITEM_OK;
                } else if (s_decoded[0] == '\"' && s_decoded[s_decoded.length() - 1] != '\"') {
                    return CMD_ITEM_INCOMPLETE_STR;
                } else if (s_decoded[0] != '\"' && s_decoded[s_decoded.length() - 1] == '\"') {
                    return CMD_ITEM_ERROR;
                } else if (s_decoded[0] != '\"' && s_decoded[s_decoded.length() - 1] != '\"') {

                    if (s_decoded[0] == '\'' && s_decoded[s_decoded.length() - 1] == '\'') {
                        if (s_decoded_escaped[0] == 'n' && s_decoded_escaped[s_decoded.length() - 1] == 'n') {
                            s_decoded = s_decoded.substr(1, s_decoded.length() - 2);
                            return CMD_ITEM_OK_STR_WITHOUT_COMMAS;
                        }
                        return CMD_ITEM_OK;
                    } else if (s_decoded[0] == '\'' && s_decoded[s_decoded.length() - 1] != '\'') {
                        return CMD_ITEM_INCOMPLETE_STR;
                    } else if (s_decoded[0] != '\'' && s_decoded[s_decoded.length() - 1] == '\'') {
                        return CMD_ITEM_ERROR;
                    } else if (s_decoded[0] != '\'' && s_decoded[s_decoded.length() - 1] != '\'') {
                        return CMD_ITEM_OK_STR_WITHOUT_COMMAS;
                    }

                    return CMD_ITEM_OK_STR_WITHOUT_COMMAS;
                }
            } else {
                return CMD_ITEM_OK_STR_WITHOUT_COMMAS;
            }
        } else {
            return CMD_ITEM_INCOMPLETE_STR;
        }
    }

public:

    Cmd_Item_Str_Esc(string text, string help) : Cmd_Item_Str(text, help) {
        Type = "Str_Esc";
    }

    virtual Cmd_Item_Valid_Result Parse(string s) {

        if (s.size() == 1) {
            if (s[0] == '\"') {
                Value_Str = s;
                return CMD_ITEM_INCOMPLETE_STR;
            }
            if (s[0] == '\'') {
                Value_Str = s;
                return CMD_ITEM_INCOMPLETE_STR;
            }
            if (s[0] == '\\') {
                Value_Str = s;
                return CMD_ITEM_INCOMPLETE_STR;
            }
            Value_Str = s;
            return CMD_ITEM_OK_STR_WITHOUT_COMMAS;
        } // if (s.size() == 1)

        if (s.find('\\', 0) == s.npos) {

            if (s.size() == 0) {
                Value_Str = "";
                return CMD_ITEM_EMPTY; // @Attention
            }

            if (s.length() == 2 && s.at(0) == '"' && s.at(1) == '"') {
                Value_Str = "";
                return CMD_ITEM_OK_STR_WITHOUT_COMMAS;
            }
            if (s.length() == 2 && s.at(0) == '\'' && s.at(1) == '\'') {
                Value_Str = "";
                return CMD_ITEM_OK_STR_WITHOUT_COMMAS;
            }

            if (s.find('\\', 0) == s.npos && s.find('\"', 0) == s.npos && s.find('\'', 0) == s.npos) {
                Value_Str = s;
                return CMD_ITEM_OK_STR_WITHOUT_COMMAS;
            }

            if (s.find('\\', 0) == s.npos
                    && s.find('\"', 0) != s.npos && s.at(0) != '\"'
                    && s.find('\'', 0) != s.npos && s.at(0) != '\'') {
                Value_Str = s;
                return CMD_ITEM_ERROR;
            }

            if (s.find('\\', 0) == s.npos && s.find('\"', 0) != s.npos
                    && s.length() > 1
                    && s.at(0) == '\"'
                    && s.at(s.length() - 1) == '\"') {
                Value_Str = s.substr(1, s.length() - 2);
                return CMD_ITEM_OK_STR_WITHOUT_COMMAS;
            }
            if (s.find('\\', 0) == s.npos && s.find('\'', 0) != s.npos
                    && s.length() > 1
                    && s.at(0) == '\''
                    && s.at(s.length() - 1) == '\'') {
                Value_Str = s.substr(1, s.length() - 2);
                return CMD_ITEM_OK_STR_WITHOUT_COMMAS;
            }

            if (s.find('\\', 0) == s.npos && s.find('\"', 0) != s.npos
                    && s.length() > 1
                    && s.at(0) == '\"'
                    && s.at(s.length() - 1) != '\"') {
                Value_Str = s;
                return CMD_ITEM_INCOMPLETE_STR;
            }
            if (s.find('\\', 0) == s.npos && s.find('\'', 0) != s.npos
                    && s.length() > 1
                    && s.at(0) == '\''
                    && s.at(s.length() - 1) != '\'') {
                Value_Str = s;
                return CMD_ITEM_INCOMPLETE_STR;
            }

        } // if (s.find('\\', 0) == s.npos)

        if (s.find('\\', 0) != s.npos) {
            string s_decoded;
            Cmd_Item_Valid_Result res = Decode(s, s_decoded);
            if (res == CMD_ITEM_OK || res == CMD_ITEM_OK_STR_WITHOUT_COMMAS) {
                Value_Str = s_decoded;
            } else {
                Value_Str = s; // Error or Incomplete
            }
            return res;
        } // if (s.find('\\', 0) != s.npos)

        Value_Str = s; // Error
        return CMD_ITEM_ERROR;
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
