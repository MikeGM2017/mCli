/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Input_Thread_Args.h
 * Author: mike
 *
 * Created on February 10, 2025, 9:06 AM
 */

#ifndef CLI_INPUT_THREAD_ARGS_H
#define CLI_INPUT_THREAD_ARGS_H

#include <windows.h>
#include <winuser.h>

#include <list>

using namespace std;

#include "Cli_Input_Char_Item.h"

typedef LRESULT CALLBACK fpWndProc(HWND hwnd, // window handle
        UINT message, // type of message
        WPARAM wParam, // additional information
        LPARAM lParam);

class Cli_Input_Thread_Args_t {
protected:

    HWND Main_HWND;
    HWND Output_HWND;
    fpWndProc *hwndEdit_WndProc_Org;
    bool Cli_Input_Thread_CMD_Stop;
    HANDLE Cli_Input_Queue_Mutex;
    bool Is_kbhit;

    list<Cli_Input_Char_Item_t> Cli_Input_Thread_Queue;
    int Cli_Input_Queue_Mutex_Wait_Time;

public:

    HANDLE stdOut;

    bool Arg_Help_Print;
    bool Arg_Version_Print;
    bool Arg_Arguments_Print;
    wstring Arg_Script_File_Name;
    bool Arg_Script_Exit_Force;
    wstring Arg_Log_Output_File_Name;
    wstring Arg_TAB_Log_Output_File_Name;
    wstring Arg_HISTORY_Log_Output_File_Name;

    Cli_Input_Thread_Args_t() : Output_HWND(0), Cli_Input_Thread_CMD_Stop(false),
    Cli_Input_Queue_Mutex(0), Cli_Input_Queue_Mutex_Wait_Time(100), hwndEdit_WndProc_Org(0),
    Is_kbhit(false),
    stdOut(0),
    Arg_Help_Print(false),
    Arg_Version_Print(false),
    Arg_Arguments_Print(false),
    Arg_Script_Exit_Force(false) {
        Cli_Input_Queue_Mutex = CreateMutex(
                NULL, // default security attributes
                FALSE, // initially not owned
                NULL);
    }

    void Main_HWND_Set(HWND hwnd) {
        Main_HWND = hwnd;
    }

    HWND Main_HWND_Get() {
        return Main_HWND;
    }

    void Output_HWND_Set(HWND hwnd) {
        Output_HWND = hwnd;
    }

    HWND Output_HWND_Get() {
        return Output_HWND;
    }

    void hwndEdit_WndProc_Org_Set(fpWndProc *fp) {
        hwndEdit_WndProc_Org = fp;
    }

    fpWndProc *hwndEdit_WndProc_Org_Get() {
        return hwndEdit_WndProc_Org;
    }

    void Cli_Input_Thread_CMD_Stop_Set(bool v) {
        Cli_Input_Thread_CMD_Stop = v;
    }

    bool Cli_Input_Thread_CMD_Stop_Get() {
        return Cli_Input_Thread_CMD_Stop;
    }

    HANDLE Cli_Input_Queue_Mutex_Get() {
        return Cli_Input_Queue_Mutex;
    }

    void Cli_Input_Queue_Mutex_Set(HANDLE h) {
        Cli_Input_Queue_Mutex = h;
    }

    void Is_kbhit_Set() {
        Is_kbhit = true;
    }

    void Is_kbhit_Clear() {
        Is_kbhit = false;
    }

    bool Is_kbhit_Get() {
        return Is_kbhit;
    }

    void Cli_Input_Queue_Add(WPARAM wParam, CLI_CT ct, string s) {
        DWORD dwWaitResult = WaitForSingleObject(Cli_Input_Queue_Mutex, INFINITE);
        switch (dwWaitResult) {
            case WAIT_OBJECT_0:
            {
                Cli_Input_Thread_Queue.push_back(Cli_Input_Char_Item_t(ct, wParam, s));
                ReleaseMutex(Cli_Input_Queue_Mutex);
            }
                break;
        }
    }

    Cli_Input_Char_Item_t Cli_Input_Queue_Get() {
        if (!Cli_Input_Thread_Queue.empty()) {
            DWORD dwWaitResult = WaitForSingleObject(Cli_Input_Queue_Mutex, Cli_Input_Queue_Mutex_Wait_Time);
            switch (dwWaitResult) {
                case WAIT_OBJECT_0:
                {
                    Cli_Input_Char_Item_t char_item = Cli_Input_Thread_Queue.front();
                    Cli_Input_Thread_Queue.pop_front();
                    ReleaseMutex(Cli_Input_Queue_Mutex);
                    return char_item;
                }
                    break;
            }
        }
        Cli_Input_Char_Item_t char_item(CLI_CT_NO, 0, ""); // No Action
        return char_item;
    }

};

#endif /* CLI_INPUT_THREAD_ARGS_H */
