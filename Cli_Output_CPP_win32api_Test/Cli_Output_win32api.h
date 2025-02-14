/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Output_win32api.h
 * Author: mike
 *
 * Created on February 4, 2025, 9:36 AM
 */

#ifndef CLI_OUTPUT_WIN32API_H
#define CLI_OUTPUT_WIN32API_H

#include <windows.h>
#include <winuser.h>

#include "Cli_Output_Abstract.h"

class Cli_Output_win32api : public Cli_Output_Abstract {
protected:

    HWND output_hwnd;

    void AppendText(const HWND hwndEdit, const TCHAR *newText) {
        int len_prev = GetWindowTextLength(hwndEdit);
        SendMessage(hwndEdit, EM_SETSEL, len_prev, len_prev); //Select end pos
        SendMessage(hwndEdit, EM_REPLACESEL, FALSE, (LPARAM) newText);
        SendMessage(hwndEdit, EM_SETSEL, -1, -1); //Unselect and stay at the end pos
    }

public:

    Cli_Output_win32api() : output_hwnd(0) {
    }

    virtual void HWND_Set(HWND hwnd) {
        output_hwnd = hwnd;
    }

    virtual bool Output_Init() {
        return true;
    }

    virtual bool Output_Close() {
        return true;
    }

    virtual bool Output_Clear() {
        SetWindowText(output_hwnd, "\0");
        return true;
    }

    virtual void Output_NewLine() {
        AppendText(output_hwnd, "\n");
    }

    virtual void Output_Char(char c) {
        TCHAR s[2];
        s[0] = c;
        s[1] = 0;
        AppendText(output_hwnd, s);
    }

    virtual void Output_Str(string s) {
        AppendText(output_hwnd, s.c_str());
    }

    virtual void Output_Return() {
        int buf_size = GetWindowTextLength(output_hwnd);
        if (buf_size) {
            TCHAR *buf = new TCHAR[buf_size];
            int len = GetWindowText(output_hwnd, buf, buf_size);
            if (len > 0) {
                int pos = len - 1;
                while (1) {
                    TCHAR c = buf[pos];
                    if (c == '\n' || c == '\r') {
                        SendMessage(output_hwnd, EM_SETSEL, pos + 1, pos + 1);
                        break;
                    } else {
                        pos--;
                        if (pos < 0) {
                            SendMessage(output_hwnd, EM_SETSEL, 0, 0);
                            break;
                        }
                    }
                }
            }
            delete[] buf;
        } else {
            SendMessage(output_hwnd, EM_SETSEL, 0, 0);
        }
    }

};

#endif /* CLI_OUTPUT_WIN32API_H */
