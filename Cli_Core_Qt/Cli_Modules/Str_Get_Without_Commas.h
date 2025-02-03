/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Str_Get_Without_Commas.h
 * Author: mike
 *
 * Created on July 16, 2024, 2:33 PM
 */

#ifndef STR_GET_WITHOUT_COMMAS_H
#define STR_GET_WITHOUT_COMMAS_H

#include <string>

using namespace std;

class Str_Get_Without_Commas {
public:

    string Get(string value_str) {
        string s = value_str;
        if (value_str.size() >= 2) {
            if (
                    (value_str[0] == '\"' && value_str[value_str.size() - 1] == '\"')
                    || (value_str[0] == '\'' && value_str[value_str.size() - 1] == '\'')
                    ) {
                s = value_str.substr(1, value_str.size() - 2);
            }
        }
        return s;
    }

};

#endif /* STR_GET_WITHOUT_COMMAS_H */
