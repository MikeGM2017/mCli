/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cmd_Token_Array.h
 * Author: mike
 *
 * Created on August 4, 2020, 11:35 AM
 */

#ifndef CMD_TOKEN_ARRAY_H
#define CMD_TOKEN_ARRAY_H

#ifdef __cplusplus
extern "C" {
#endif

#include "Cmd_Token.h"

#define CMD_TOKEN_ARRAY_SIZE_DEF 32

    struct Cmd_Token_Array {
        struct Cmd_Token Items[CMD_TOKEN_ARRAY_SIZE_DEF];
        int Size;
    };
    
    struct Cmd_Token_Array Cmd_Token_Array_Init(void);
    
    int Cmd_Token_Array_Add(struct Cmd_Token_Array *tokens, struct Cmd_Token *token);

#ifdef __cplusplus
}
#endif

#endif /* CMD_TOKEN_ARRAY_H */
