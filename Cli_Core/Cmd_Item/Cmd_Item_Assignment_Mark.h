/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cmd_Item_Assignment_Mark.h
 * Author: mike
 *
 * Created on June 7, 2021, 10:32 AM
 */

#ifndef CMD_ITEM_ASSIGNMENT_MARK_H
#define CMD_ITEM_ASSIGNMENT_MARK_H

#include "Cmd_Item_EQU_Range.h"

class Cmd_Item_Assignment_Mark : public Cmd_Item_EQU_Range {
protected:

    virtual bool Is_Char_Valid(char c, int pos, int len) {
        // = += -= *= /= %= ^= &= |= <<= >>= ~=
        if (len == 1) {
            if (pos == 0) {
                if (c == '=') return true;

                if (c == '+') return true;
                if (c == '-') return true;
                if (c == '*') return true;
                if (c == '/') return true;
                if (c == '%') return true;
                if (c == '^') return true;
                if (c == '&') return true;
                if (c == '|') return true;
                if (c == '~') return true;

                if (c == '<') return true;
                if (c == '>') return true;
            }
        }
        if (len == 2) {
            if (pos == 0) {
                if (c == '+') return true;
                if (c == '-') return true;
                if (c == '*') return true;
                if (c == '/') return true;
                if (c == '%') return true;
                if (c == '^') return true;
                if (c == '&') return true;
                if (c == '|') return true;

                if (c == '<') return true;
                if (c == '>') return true;
                return false;
            }
            if (pos == 1) {
                if (c == '=') return true;

                if (c == '<') return true;
                if (c == '>') return true;
                return false;
            }
        }
        if (len == 3) {
            if (pos == 0) {
                if (c == '<') return true;
                if (c == '>') return true;
                return false;
            }
            if (pos == 1) {
                if (c == '<') return true;
                if (c == '>') return true;
                return false;
            }
            if (pos == 2) {
                if (c == '=') return true;
                return false;
            }
        }
        return false;
    }

public:

    Cmd_Item_Assignment_Mark(string text, string help, vector<string> words) : Cmd_Item_EQU_Range(text, help, words) {
        Type = "Assignment_Mark";
        Version = "0.02";
    }

};

#endif /* CMD_ITEM_ASSIGNMENT_MARK_H */
