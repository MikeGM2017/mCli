/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cmd_Item_EQU.h
 * Author: mike
 *
 * Created on December 2, 2020, 1:43 PM
 */

#ifndef CMD_ITEM_EQU_H
#define CMD_ITEM_EQU_H

#include "Cmd_Item_Word.h"

class Cmd_Item_EQU : public Cmd_Item_Word {
protected:

    virtual bool Is_Char_Valid(char c, int pos, int len) {
        // == != < > <= >= & | && ||

        if (len > 2) return false;

        if (pos == 0) {
            if (c == '=' || c == '!' || c == '<' || c == '>' || c == '&' || c == '|') return true;
        } else if (pos == 1) {
            if (c == '=' || c == '&' || c == '|') return true;
        }

        return false;
    }

public:

    Cmd_Item_EQU(string text, string help) : Cmd_Item_Word(text, help) {
        Type = "EQU";
    }

};

#endif /* CMD_ITEM_EQU_H */
