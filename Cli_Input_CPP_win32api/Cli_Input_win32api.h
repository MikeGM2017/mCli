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

#include "CLI_CT.h"
#include "Cli_Input_Char_Item.h"

class Cli_Input_win32api : public Cli_Input_Abstract {
protected:

    HWND Output_HWND;

    bool Is_kbhit;

public:

    Cli_Input_win32api(Cli_Output_Abstract &cli_output, HWND output_hwnd) : Cli_Input_Abstract(cli_output),
    Output_HWND(output_hwnd), Is_kbhit(false) {
    }

    virtual void Input_Caret_Pos_Set() {
        if (Is_Echo_Get()) {
            int pos = GetWindowTextLength(Output_HWND) - Input_Str.length() + Input_Str_Pos;
            SendMessage(Output_HWND, EM_SETSEL, pos, pos);
        } else {
            int pos = GetWindowTextLength(Output_HWND);
            SendMessage(Output_HWND, EM_SETSEL, pos, pos);
        }
    }

    virtual void Input_Add(char c, bool is_shift) {
        if (Input_Str_Pos == Input_Str.length()) {
            if (Is_Echo_Get()) {
                Cli_Output.Output_Char(c);
            }
            Input_Str += c;
            Input_Str_Pos++;
        } else {
            int len_prev = GetWindowTextLength(Output_HWND);
            int pos_beg = len_prev - Input_Str.length();

            string s_prev = Input_Str;

            string s1 = Input_Str.substr(0, Input_Str_Pos);
            string s2_c;
            s2_c.append(1, c);
            string s3 = Input_Str.substr(Input_Str_Pos, Input_Str.length() - Input_Str_Pos);

            Input_Str = s1 + s2_c + s3;

            Input_Str_Pos++;

            if (Is_Echo_Get()) {
                SendMessage(Output_HWND, EM_SETSEL, pos_beg, len_prev);
                SendMessage(Output_HWND, EM_REPLACESEL, FALSE, (LPARAM) Input_Str.c_str());
            }
        }
        Input_Caret_Pos_Set();
    }

    virtual Cli_Input_Item Input_Back() {
        if (!Input_Str.empty() && Input_Str_Pos > 0) {
            string s_prev = Input_Str;
            if (Input_Str_Pos == Input_Str.length()) {
                if (Input_Str_Pos > 0) {
                    int len_prev = GetWindowTextLength(Output_HWND);

                    Input_Str = s_prev.substr(0, s_prev.size() - 1);
                    Input_Str_Pos--;

                    if (Is_Echo_Get()) {
                        SendMessage(Output_HWND, EM_SETSEL, len_prev - 1, len_prev);
                        SendMessage(Output_HWND, EM_REPLACESEL, FALSE, (LPARAM) "");
                    }
                }
            } else {
                if (Input_Str_Pos > 0) {
                    int len_prev = GetWindowTextLength(Output_HWND);
                    int pos_beg = len_prev - Input_Str.length();

                    Input_Str = s_prev.substr(0, Input_Str_Pos - 1)
                            + s_prev.substr(Input_Str_Pos, s_prev.size() - Input_Str_Pos);
                    Input_Str_Pos--;

                    if (Is_Echo_Get()) {
                        SendMessage(Output_HWND, EM_SETSEL, pos_beg, len_prev);
                        SendMessage(Output_HWND, EM_REPLACESEL, FALSE, (LPARAM) Input_Str.c_str());
                    }
                }
            }
        }
        Input_Caret_Pos_Set();
        return Cli_Input_Item(CLI_INPUT_ITEM_TYPE_BACK, "");
    }

    virtual Cli_Input_Item Input_Delete() {
        if (!Input_Str.empty() && Input_Str_Pos < Input_Str.size()) {
            int len_prev = GetWindowTextLength(Output_HWND);
            int pos_beg = len_prev - Input_Str.length();

            string s_prev = Input_Str;
            Input_Str = s_prev.substr(0, Input_Str_Pos)
                    + s_prev.substr(Input_Str_Pos + 1, s_prev.size() - Input_Str_Pos - 1);

            if (Is_Echo_Get()) {
                SendMessage(Output_HWND, EM_SETSEL, pos_beg, len_prev);
                SendMessage(Output_HWND, EM_REPLACESEL, FALSE, (LPARAM) Input_Str.c_str());
            }
        }
        Input_Caret_Pos_Set();
        return Cli_Input_Item(CLI_INPUT_ITEM_TYPE_DELETE, "");
    }

    virtual void Input_Home() {
        Input_Str_Pos = 0;
        Input_Caret_Pos_Set();
    }

    virtual void Input_End() {
        Input_Str_Pos = Input_Str.length();
        Input_Caret_Pos_Set();
    }

    virtual void Input_Left() {
        if (Input_Str_Pos > 0) {
            Input_Str_Pos--;
        }
        Input_Caret_Pos_Set();
    }

    virtual void Input_Right() {
        if (Input_Str_Pos < Input_Str.length()) {
            Input_Str_Pos++;
        }
        Input_Caret_Pos_Set();
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
        bool ret = Is_kbhit;
        Is_kbhit = false;
        return ret;
    }

    virtual bool Is_Char_Valid(string char_str) {
        return true; // all chars valid
    }

    virtual Cli_Input_Item On_Key_Pressed(int key_code, string key_str, bool is_ctrl, bool is_shift) { //@Warning: Not Used
        Cli_Input_Item item(CLI_INPUT_ITEM_TYPE_NO, ""); // No Action
        return item;
    }

    virtual Cli_Input_Item On_Key_Pressed(Cli_Input_Char_Item_t &char_item) { // Attention: Not Blocked
        Cli_Input_Item item(CLI_INPUT_ITEM_TYPE_NO, "");
        switch (char_item.Char_Type) {
            case CLI_CT_CHAR:
                if (!char_item.Text.empty()) {
                    bool is_shift;
                    Input_Add(char_item.Text[0], is_shift = false);
                }
                break;
            case CLI_CT_ENTER:
                item.Type_Set(CLI_INPUT_ITEM_TYPE_STR);
                item.Text_Set(Input_Str_Get());
                break;
            case CLI_CT_TAB:
                item.Type_Set(CLI_INPUT_ITEM_TYPE_TAB);
                item.Text_Set(Input_Str_Get());
                break;
            case CLI_CT_UP:
                item.Type_Set(CLI_INPUT_ITEM_TYPE_UP);
                item.Text_Set(Input_Str_Get());
                break;
            case CLI_CT_DOWN:
                item.Type_Set(CLI_INPUT_ITEM_TYPE_DOWN);
                item.Text_Set(Input_Str_Get());
                break;

            case CLI_CT_HOME:
                Input_Home();
                break;
            case CLI_CT_END:
                Input_End();
                break;
            case CLI_CT_LEFT:
                Input_Left();
                break;
            case CLI_CT_RIGHT:
                Input_Right();
                break;
            case CLI_CT_BACK:
                Input_Back();
                break;
            case CLI_CT_DELETE:
                Input_Delete();
                break;

            case CLI_CT_CTRL_C:
                Is_Ctrl_C_Pressed_Set();
                item.Type_Set(CLI_INPUT_ITEM_TYPE_CTRL_C);
                item.Text_Set(Input_Str_Get());
                break;
            case CLI_CT_CTRL_Z:
                Is_Ctrl_C_Pressed_Set();
                item.Type_Set(CLI_INPUT_ITEM_TYPE_CTRL_Z);
                item.Text_Set(Input_Str_Get());
                break;
            case CLI_CT_CTRL_BACKSLASH:
                Is_Ctrl_C_Pressed_Set();
                item.Type_Set(CLI_INPUT_ITEM_TYPE_CTRL_BACKSLASH);
                item.Text_Set(Input_Str_Get());
                break;
        }
        if (char_item.Char_Type != CLI_CT_NO) {
            Is_kbhit = true;
        }
        return item;
    }

};

#endif /* CLI_INPUT_WIN32API_H */
