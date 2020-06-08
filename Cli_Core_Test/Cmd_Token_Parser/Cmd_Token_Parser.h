/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cmd_Token_Parser.h
 * Author: mike
 *
 * Created on July 12, 2018, 1:39 PM
 */

#ifndef CMD_TOKEN_PARSER_H
#define CMD_TOKEN_PARSER_H

#include <vector>

using namespace std;

#include "Cmd_Token_Parser_Char_Type_Func.h"
#include "Cmd_Token.h"
#include "Cmd_Token_Parser_Result.h"

class Cmd_Token_Parser {
protected:

    virtual int Skip(Cmd_Token_Parser_Char_Type char_type, string s, int pos) {
        while (pos < s.size() && Cmd_Token_Parser_Char_Type_Func::Char_Type_Get(s[pos]) == char_type)
            pos++;
        return pos;
    }

    virtual int Get_Val(string s, int pos) {
        while (pos < s.size() && Cmd_Token_Parser_Char_Type_Func::Char_Type_Get(s[pos]) != CMD_TOKEN_PARSER_CHAR_TYPE_SPACE)
            pos++;
        return pos;
    }

    virtual int Get_Str(string s, int pos, char c_commas) {
        int commas_count = 0;
        bool is_skip = false;
        do {
            if (pos < s.size()) {
                if (!is_skip) {
                    if (s[pos] == '\\') {
                        is_skip = true;
                    } else if (s[pos] == c_commas) {
                        commas_count++;
                    }
                    pos++;
                } else {
                    is_skip = false;
                    pos++;
                }
            }
        } while (pos < s.size() && commas_count < 2);
        return pos;
    }

public:

    virtual ~Cmd_Token_Parser() {
    }

    virtual vector<Cmd_Token *> Parse(string s, const string str_rem, Cmd_Token_Parser_Result &res_out) {
        vector<Cmd_Token *> tokens;

        if (s.substr(0, str_rem.size()) == str_rem) {
            res_out = CMD_TOKEN_PARSER_OK;
            Cmd_Token *token_ptr = new Cmd_Token(s);
            tokens.push_back(token_ptr);
            return tokens;
        }

        res_out = CMD_TOKEN_PARSER_OK;

        if (s.size() > 0) {
            int pos = 0;
            int pos_next = 0;
            do {
                bool found = false;
                char c = s[pos];
                Cmd_Token_Parser_Char_Type char_type = Cmd_Token_Parser_Char_Type_Func::Char_Type_Get(c);
                switch (char_type) {
                    case CMD_TOKEN_PARSER_CHAR_TYPE_SPACE:
                    case CMD_TOKEN_PARSER_CHAR_TYPE_NEWLINE:
                        pos_next = Skip(char_type, s, pos);
                        found = false;
                        break;
                    case CMD_TOKEN_PARSER_CHAR_TYPE_ALPHA:
                    case CMD_TOKEN_PARSER_CHAR_TYPE_DIGIT:
                        pos_next = Get_Val(s, pos);
                        found = true;
                        break;
                }
                if (pos == pos_next) {
                    res_out = CMD_TOKEN_PARSER_ERROR;
                    return tokens;
                }
                if (pos != pos_next && found) {
                    string s1 = s.substr(pos, pos_next - pos);
                    Cmd_Token *token_ptr = new Cmd_Token(s1);
                    tokens.push_back(token_ptr);
                }
                pos = pos_next;
            } while (pos < s.size());
        }
        return tokens;
    }

};

#endif /* CMD_TOKEN_PARSER_H */
