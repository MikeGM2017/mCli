/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cmd_Token_Parser_Char_Type_Func.h
 * Author: mike
 *
 * Created on July 12, 2018, 1:47 PM
 */

#ifndef CMD_TOKEN_PARSER_CHAR_TYPE_FUNC_H
#define CMD_TOKEN_PARSER_CHAR_TYPE_FUNC_H

#include "Cmd_Token_Parser_Char_Type.h"

class Cmd_Token_Parser_Char_Type_Func {
public:

    static Cmd_Token_Parser_Char_Type Char_Type_Get(char c) {
        if (c >= 'a' && c <= 'z') return CMD_TOKEN_PARSER_CHAR_TYPE_ALPHA;
        if (c >= 'A' && c <= 'Z') return CMD_TOKEN_PARSER_CHAR_TYPE_ALPHA;
        if (c == '_') return CMD_TOKEN_PARSER_CHAR_TYPE_ALPHA;
        if (c >= '0' && c <= '9') return CMD_TOKEN_PARSER_CHAR_TYPE_DIGIT;
        switch (c) {
            case ' ':
            case '\t':
                return CMD_TOKEN_PARSER_CHAR_TYPE_SPACE;
            case '\n':
            case '\r':
                return CMD_TOKEN_PARSER_CHAR_TYPE_NEWLINE;
            case '\"':
            case '\'': // @Attention
                return CMD_TOKEN_PARSER_CHAR_TYPE_COMMAS;
        }
        return CMD_TOKEN_PARSER_CHAR_TYPE_ERROR;
    }

};

#endif /* CMD_TOKEN_PARSER_CHAR_TYPE_FUNC_H */
