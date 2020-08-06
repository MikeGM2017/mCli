/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Cmd_Token_Parser.h"

static int Cmd_Token_Parser_Skip(enum Cmd_Token_Parser_Char_Type char_type, char *s, int pos) {
    while (s[pos] && Cmd_Token_Parser_Char_Type_Get(s[pos]) == char_type)
        pos++;
    return pos;
}

static int Cmd_Token_Parser_Get_Val(char *s, int pos) {
    while (s[pos] && Cmd_Token_Parser_Char_Type_Get(s[pos]) != CMD_TOKEN_PARSER_CHAR_TYPE_SPACE)
        pos++;
    return pos;
}

static int Cmd_Token_Parser_Get_Str(char *s, int pos, char c_commas) {
    int commas_count = 0;
    int is_skip = 0;
    do {
        if (s[pos]) {
            if (!is_skip) {
                if (s[pos] == '\\') {
                    is_skip = 1;
                } else if (s[pos] == c_commas) {
                    commas_count++;
                }
                pos++;
            } else {
                is_skip = 0;
                pos++;
            }
        }
    } while (s[pos] && commas_count < 2);
    return pos;
}

static struct Cmd_Token_Array Cmd_Token_Parser_Parse(char *s, char *str_rem, enum Cmd_Token_Parser_Result *res_out) {
    struct Cmd_Token_Array tokens = Cmd_Token_Array_Init();

    struct Cmd_Token token_tmp;

    char s1[CMD_TOKEN_TEXT_SIZE_DEF];

    int s_size = strlen(s);
    int str_rem_size = strlen(str_rem);

    if (!strncmp(s, str_rem, str_rem_size)) {
        (*res_out) = CMD_TOKEN_PARSER_OK;
        Cmd_Token_Text_Set(&token_tmp, s);
        Cmd_Token_Array_Add(&tokens, &token_tmp);
        return tokens;
    }

    (*res_out) = CMD_TOKEN_PARSER_OK;

    if (s_size > 0) {
        int pos = 0;
        int pos_next = 0;
        do {
            int found = 0;
            char c = s[pos];
            enum Cmd_Token_Parser_Char_Type char_type = Cmd_Token_Parser_Char_Type_Get(c);
            switch (char_type) {
                case CMD_TOKEN_PARSER_CHAR_TYPE_SPACE:
                case CMD_TOKEN_PARSER_CHAR_TYPE_NEWLINE:
                    pos_next = Cmd_Token_Parser_Skip(char_type, s, pos);
                    found = 0;
                    break;
                case CMD_TOKEN_PARSER_CHAR_TYPE_COMMAS:
                    pos_next = Cmd_Token_Parser_Get_Str(s, pos, c);
                    found = 1;
                    break;
                case CMD_TOKEN_PARSER_CHAR_TYPE_ALPHA:
                case CMD_TOKEN_PARSER_CHAR_TYPE_DIGIT:
                default: // @Attention: default: for str filter like *elp 
                    pos_next = Cmd_Token_Parser_Get_Val(s, pos);
                    found = 1;
                    break;
            }
            if (pos == pos_next) {
                (*res_out) = CMD_TOKEN_PARSER_ERROR;
                return tokens;
            }
            if (pos != pos_next && found) {
                int len = pos_next - pos;
                strncpy(s1, s + pos, len);
                s1[len] = '\0';
                Cmd_Token_Text_Set(&token_tmp, s1);
                Cmd_Token_Array_Add(&tokens, &token_tmp);
            }
            pos = pos_next;
        } while (pos < s_size);
    }
    return tokens;
}

struct Cmd_Token_Parser Cmd_Token_Parser_Init(void) {
    struct Cmd_Token_Parser parser = {
        .Skip = Cmd_Token_Parser_Skip,
        .Get_Val = Cmd_Token_Parser_Get_Val,
        .Get_Str = Cmd_Token_Parser_Get_Str,
        .Parse = Cmd_Token_Parser_Parse,
    };
    return parser;
}
