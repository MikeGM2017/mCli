/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Input_Item.h
 * Author: mike
 *
 * Created on June 2, 2020, 9:40 AM
 */

#ifndef CLI_INPUT_ITEM_H
#define CLI_INPUT_ITEM_H

#include <string>

using namespace std;

#include "Cli_Input_Item_Type.h"

class Cli_Input_Item {
protected:
    Cli_Input_Item_Type Type;
    string Text;
public:

    Cli_Input_Item(Cli_Input_Item_Type type, string text) : Type(type), Text(text) {
    }
    
    Cli_Input_Item_Type Type_Get() {
        return Type;
    }
    
    void Type_Set(Cli_Input_Item_Type type) {
        Type = type;
    }
    
    string Text_Get() {
        return Text;
    }
    
    void Text_Set(string text) {
        Text = text;
    }

};

#endif /* CLI_INPUT_ITEM_H */
