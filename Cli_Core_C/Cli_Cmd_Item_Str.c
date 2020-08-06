/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Cli_Cmd_Item.h"

static int Is_Char_Valid(char c, int pos, int len) {
    return 1; // Допустимы все символы в любой позиции
}

static enum Cmd_Item_Valid_Result Decode(char *s_src, char *s_dst) {
    enum Cmd_Item_Valid_Result decode_res = CMD_ITEM_OK;
    int is_in_commas = 0;
    char c_commas = '\0';
    char c_last = '\0';
    int is_escape = 0;

    int s_src_size = strnlen(s_src, CLI_CMD_ITEM_VALUE_STR_SIZE_DEF);

    int s_dst_pos = 0;
    s_dst[0] = '\0';

    int i;
    for (i = 0; i < s_src_size; i++) {
        if (i == 0) {
            char c = s_src[i];
            if (c == '"' || c == '\'') {
                is_in_commas = 1;
                c_commas = c;
            }
        }
        char c = s_src[i];
        switch (c) {
            case '\\':
                decode_res = CMD_ITEM_INCOMPLETE_STR;
                is_escape = 1;
                break;
            default:
                if (is_escape) {
                    switch (c) {
                        case 'n':
                            c = '\n';
                            c_last = c;
                            break;
                        case 'r':
                            c = '\r';
                            c_last = c;
                            break;
                        case 't':
                            c = '\t';
                            c_last = c;
                            break;
                        case '\"':
                        case '\'':
                            c_last = 0; // @Attention: Escaped '"' and '''
                            break;
                        default:
                            c_last = c;
                    }
                } else {
                    c_last = c;
                }
                //s_dst.append(&c, 1);
                s_dst[s_dst_pos] = c;
                s_dst_pos++;
                s_dst[s_dst_pos] = '\0';
                decode_res = CMD_ITEM_OK;
                is_escape = 0;
                break;
        }
    }

    if (is_in_commas && c_commas != c_last)
        return CMD_ITEM_INCOMPLETE_STR;

    if (c_last == '"' || c_last == '\'') {
        if (c_last != s_src[0])
            return CMD_ITEM_ERROR;
    }

    if (decode_res == CMD_ITEM_OK && s_src[0] != '\0' && s_src[0] != '\"' && s_src[0] != '\'') {
        decode_res = CMD_ITEM_OK_STR_WITHOUT_COMMAS;
    }

    return decode_res;
}

static enum Cmd_Item_Valid_Result Parse(struct Cli_Cmd_Item *item, char *s) {
    if (s[0] == 0) return CMD_ITEM_EMPTY; // @Attention

    //if (s == "\"\"") s = ""; // @Attention

    //if (s_size >= 2 && s[0] == '"' && s[s_size - 1] == '"')
    //    s = s.substr(1, s_size - 2);
    //else if (s_size >= 2 && s[0] == '\'' && s[s_size - 1] == '\'')
    //    s = s.substr(1, s_size - 2);

    int len = CLI_CMD_ITEM_VALUE_STR_SIZE_DEF - 1;
    strncpy(item->Value_Str, s, len);
    item->Value_Str[len] = '\0';

    if (s[0] == 0) return CMD_ITEM_OK_STR_WITHOUT_COMMAS; // @Attention

    int s_size = strnlen(s, CLI_CMD_ITEM_VALUE_STR_SIZE_DEF);

    if (s_size == 1) {
        if (s[0] == '\n') return CMD_ITEM_ERROR;
        if (s[0] == '\r') return CMD_ITEM_ERROR;
        if (s[0] == '"') return CMD_ITEM_INCOMPLETE_STR;
        if (s[0] == '\'') return CMD_ITEM_INCOMPLETE_STR;
        if (s[0] != '"' && s[0] != '\'') return CMD_ITEM_OK_STR_WITHOUT_COMMAS;
    }

    //        if (s_size >= 1 && s[0] != '"') {
    //            return INPUT_ERROR;
    //        }

    if (s_size == 2) {
        if (s[0] == '"' && s[1] == '"') return CMD_ITEM_OK;
        if (s[0] == '\'' && s[1] == '\'') return CMD_ITEM_OK;
        if (s[0] == '"' && s[1] != '"') return CMD_ITEM_INCOMPLETE_STR;
        if (s[0] == '\'' && s[1] != '\'') return CMD_ITEM_INCOMPLETE_STR;
        if (s[0] != '\\' && s[1] != '\\') {
            if (s[0] != '"' && s[1] == '"') return CMD_ITEM_ERROR;
            if (s[0] != '\'' && s[1] == '\'') return CMD_ITEM_ERROR;
            if (s[0] != '"' && s[1] != '"') return CMD_ITEM_OK_STR_WITHOUT_COMMAS;
            if (s[0] != '\'' && s[1] != '\'') return CMD_ITEM_OK_STR_WITHOUT_COMMAS;
        }
    }

    int pos;
    for (pos = 0; pos < s_size; pos++) {
        if (!item->Is_Char_Valid(s[pos], pos, s_size)) return CMD_ITEM_ERROR;
    }

    //if (s[0] == '"' && s[s_size - 1] != '"') return INPUT_INCOMPLETE;

    //if (s[0] != '"' && s[s_size - 1] == '"') return INPUT_ERROR;

    //return INPUT_OK;

    enum Cmd_Item_Valid_Result decode_res = Decode(s, item->Value_Str); // @Attention: s is decoded with escapes
    return decode_res;

}

struct Cli_Cmd_Item Cli_Cmd_Item_Str_Init(char *text, char *help) {
    struct Cli_Cmd_Item item;
    Cli_Cmd_Item_Init_Base(&item, CLI_CMD_ITEM_TYPE_WORD, text, help);

    item.Is_Char_Valid = Is_Char_Valid;
    item.Parse = Parse;

    return item;
}
