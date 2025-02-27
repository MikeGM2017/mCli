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

#include "Cmd_Item_Base.h"

class Cmd_Item_Assignment_Mark : public Cmd_Item_Base {
protected:

    virtual bool Is_Char_Valid(char c, int pos, int len) {
        // =
        if (len == 1 && pos == 0 && c == '=') return true;
        return false;
    }

public:

    Cmd_Item_Assignment_Mark(string text, string help) : Cmd_Item_Base(text, help) {
        Type = "Assignment_Mark";
    }

};

#endif /* CMD_ITEM_ASSIGNMENT_MARK_H */
