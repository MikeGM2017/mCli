/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Cmd_Token_Parser_Char_Type_Func.h"

enum Cmd_Token_Parser_Char_Type Cmd_Token_Parser_Char_Type_Get(char c) {
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
