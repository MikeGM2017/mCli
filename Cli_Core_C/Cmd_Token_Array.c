/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Cmd_Token_Array.h"

struct Cmd_Token_Array Cmd_Token_Array_Init(void) {
    struct Cmd_Token_Array tokens;
    memset(&tokens, 0, sizeof (tokens));
    return tokens;
}

int Cmd_Token_Array_Add(struct Cmd_Token_Array *tokens, struct Cmd_Token *token) {
    if (tokens->Size < CMD_TOKEN_ARRAY_SIZE_DEF) {
        tokens->Items[tokens->Size++] = (*token);
        return 1; // Ok
    }
    return 0; // Failed
}
