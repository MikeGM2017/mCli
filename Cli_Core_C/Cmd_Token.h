/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cmd_Token.h
 * Author: mike
 *
 * Created on August 6, 2020, 1:18 PM
 */

#ifndef CMD_TOKEN_H
#define CMD_TOKEN_H

#ifdef __cplusplus
extern "C" {
#endif

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

#ifdef __cplusplus
}
#endif

#endif /* CMD_TOKEN_H */
