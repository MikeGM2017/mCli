/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Str_Get_Int.h
 * Author: mike
 *
 * Created on October 10, 2024, 4:53 PM
 */

#ifndef STR_GET_INT_H
#define STR_GET_INT_H

#include <string>
#include <sstream>

using namespace std;

#include <stdlib.h> // for atoi(...)

class Str_Get_Int {
public:

    string Int_To_Str(int v) {
        stringstream s_str;
        s_str << v;
        return s_str.str();
    }

    int Str_To_Int(string s) {
        return atoi(s.c_str());
    }

    bool Char_Is_Digit(char c) {
        if (c >= '0' && c <= '9') return true;
        return false;
    }

    bool Char_Is_Digit_Or_Plus_Or_Minus(char c) {
        if (c >= '0' && c <= '9') return true;
        if (c == '+') return true;
        if (c == '-') return true;
        return false;
    }

    bool Str_Is_Int(string s) {
        if (s.empty()) return false; // Case: empty string is not digit
        if (s.size() == 1 && !Char_Is_Digit(s[0])) return false; // Case: "+" or "-" without digits
        for (int i = 0; i < s.length(); i++) {
            char c = s[i];
            if (i == 0) {
                if (!Char_Is_Digit_Or_Plus_Or_Minus(c)) return false;
            } else {
                if (!Char_Is_Digit(c)) return false;
            }
        }
        return true;
    }

};

#endif /* STR_GET_INT_H */
