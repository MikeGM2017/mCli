/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Cmd_Token.h"

char* Cmd_Token_To_String(struct Cmd_Token *token, char *s_buf, int s_len) {
    snprintf(s_buf, s_len, "Text:%s", token->Text);
    return s_buf;
}

void Cmd_Token_Text_Set(struct Cmd_Token *token, char *s) {
    int len = CMD_TOKEN_TEXT_SIZE_DEF - 1;
    strncpy(token->Text, s, len);
    token->Text[len] = '\0';
}

char* Cmd_Token_Text_Get(struct Cmd_Token *token) {
    return token->Text;
}

char* Cmd_Token_Text_Get_Without_COMMAS(struct Cmd_Token *token, char *s_buf, int s_len) {
    int token_text_len = strlen(token->Text);
    if (token_text_len >= 2 && token->Text[0] == '\"' && token->Text[token_text_len - 1] == '\"') {
        int len = token_text_len - 2;
        strncpy(s_buf, token->Text + 1, len);
        s_buf[len] = '\0';
        return s_buf;
    }
    if (token_text_len >= 2 && token->Text[0] == '\'' && token->Text[token_text_len - 1] == '\'') {
        int len = token_text_len - 2;
        strncpy(s_buf, token->Text + 1, len);
        s_buf[len] = '\0';
        return s_buf;
    }
    return token->Text;
}
