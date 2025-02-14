/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Input_win32api.h
 * Author: mike
 *
 * Created on February 6, 2025, 10:53 AM
 */

#ifndef CLI_INPUT_WIN32API_H
#define CLI_INPUT_WIN32API_H

#include "Cli_Input_Abstract.h"

class Cli_Input_win32api : public Cli_Input_Abstract {
public:

    Cli_Input_win32api(Cli_Output_Abstract &cli_output) : Cli_Input_Abstract(cli_output) {
    }

    virtual Cli_Input_Item Input_Item_Get() { // Attention: Main Cli Input Method - Blocked
        Cli_Input_Item item(CLI_INPUT_ITEM_TYPE_NO, "");
        return item;
    }

    virtual bool Input_sleep(int sleep_sec) {
        sleep(sleep_sec);
        return true;
    }

    virtual bool Input_kbhit() { // Attention: Not Blocked
        return false;
    }

    virtual bool Is_Char_Valid(string char_str) {
        return true; // all chars valid
    }

    virtual Cli_Input_Item On_Key_Pressed(int key_code, string key_str, bool is_ctrl, bool is_shift) { // Attention: Not Blocked
        Cli_Input_Item item(CLI_INPUT_ITEM_TYPE_NO, "");
        return item;
    }

};

#endif /* CLI_INPUT_WIN32API_H */
