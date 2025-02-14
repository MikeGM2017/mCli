/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Input_Char_Item.h
 * Author: mike
 *
 * Created on February 6, 2025, 1:34 PM
 */

#ifndef CLI_INPUT_CHAR_ITEM_H
#define CLI_INPUT_CHAR_ITEM_H

#include <string>

using namespace std;

class Cli_Input_Char_Item_t {
public:
    CLI_CT Char_Type;
    int wParam;
    string Text;

    Cli_Input_Char_Item_t(CLI_CT char_type, int wparam, string text) : Char_Type(char_type), wParam(wparam), Text(text) {
    }

};

#endif /* CLI_INPUT_CHAR_ITEM_H */
