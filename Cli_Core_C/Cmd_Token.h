/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cmd_Token.h
 * Author: mike
 *
 * Created on July 16, 2018, 11:58 AM
 */

#ifndef CMD_TOKEN_H
#define CMD_TOKEN_H

#include <string.h>
#include <stdio.h>

#define CMD_TOKEN_TEXT_SIZE_DEF 32

struct Cmd_Token {
    char Text[CMD_TOKEN_TEXT_SIZE_DEF];
};

char* Cmd_Token_To_String(struct Cmd_Token *token, char *s_buf, int s_len);

void Cmd_Token_Text_Set(struct Cmd_Token *token, char *s);
char* Cmd_Token_Text_Get(struct Cmd_Token *token);

char* Cmd_Token_Text_Get_Without_COMMAS(struct Cmd_Token *token, char *s_buf, int s_len);

#endif /* CMD_TOKEN_H */
