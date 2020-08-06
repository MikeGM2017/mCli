/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cmd_Token_Parser_Char_Type.h
 * Author: mike
 *
 * Created on July 12, 2018, 1:42 PM
 */

#ifndef CMD_TOKEN_PARSER_CHAR_TYPE_H
#define CMD_TOKEN_PARSER_CHAR_TYPE_H

enum Cmd_Token_Parser_Char_Type {
    CMD_TOKEN_PARSER_CHAR_TYPE_NO,

    CMD_TOKEN_PARSER_CHAR_TYPE_SPACE,
    CMD_TOKEN_PARSER_CHAR_TYPE_NEWLINE,
    CMD_TOKEN_PARSER_CHAR_TYPE_ALPHA,
    CMD_TOKEN_PARSER_CHAR_TYPE_DIGIT,

    CMD_TOKEN_PARSER_CHAR_TYPE_COMMAS,

    CMD_TOKEN_PARSER_CHAR_TYPE_ERROR,

    CMD_TOKEN_PARSER_CHAR_TYPE_LAST,
    CMD_TOKEN_PARSER_CHAR_TYPE_UNDEFINED
};

#endif /* CMD_TOKEN_PARSER_CHAR_TYPE_H */
