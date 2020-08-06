/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cmd_Token_Parser.h
 * Author: mike
 *
 * Created on August 4, 2020, 1:20 PM
 */

#ifndef CMD_TOKEN_PARSER_H
#define CMD_TOKEN_PARSER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>

#include "Cmd_Token_Parser_Char_Type_Func.h"
#include "Cmd_Token.h"
#include "Cmd_Token_Parser_Result.h"

#include "Cmd_Token_Array.h"

typedef int ftCmd_Token_Parser_Skip(enum Cmd_Token_Parser_Char_Type char_type, char *s, int pos);
typedef int ftCmd_Token_Parser_Get_Val(char *s, int pos);
typedef int ftCmd_Token_Parser_Get_Str(char *s, int pos, char c_commas);
typedef struct Cmd_Token_Array ftCmd_Token_Parser_Parse(char *s, char *str_rem, enum Cmd_Token_Parser_Result *res_out);

struct Cmd_Token_Parser {
    ftCmd_Token_Parser_Skip *Skip;
    ftCmd_Token_Parser_Get_Val *Get_Val;
    ftCmd_Token_Parser_Get_Str *Get_Str;
    ftCmd_Token_Parser_Parse *Parse;
};

struct Cmd_Token_Parser Cmd_Token_Parser_Init(void);

#ifdef __cplusplus
}
#endif

#endif /* CMD_TOKEN_PARSER_H */
