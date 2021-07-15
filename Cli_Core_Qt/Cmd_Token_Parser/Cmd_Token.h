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

#include <string>

using namespace std;

class Cmd_Token {
protected:
    string Text;
public:

    Cmd_Token(string text) {
        Text = text;
    }

    string Text_Get() const {
        return Text;
    }

    string Text_Get_Without_COMMAS() const {
        if (Text.size() >= 2 && Text[0] == '\"' && Text[Text.size() - 1] == '\"') {
            return Text.substr(1, Text.size() - 2);
        }
        if (Text.size() >= 2 && Text[0] == '\'' && Text[Text.size() - 1] == '\'') {
            return Text.substr(1, Text.size() - 2);
        }
        return Text;
    }

    string To_String() {
        return "Text:" + Text;
    }

};

#endif /* CMD_TOKEN_H */
