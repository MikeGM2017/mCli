/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   cli_core_win32api_main.cpp
 * Author: mike
 *
 * Created on February 27, 2025, 10:37 AM
 */

#include <sstream>
#include <list>

using namespace std;

#include <windows.h>
#include <winuser.h>

#include "Cli_Input_Thread_Args.h"

#include "Cli_Input_win32api.h"
#include "Cli_Output_win32api.h"

#include "Cli_Core.h"

#include "Cli_Cmd_Privilege_ID.h"
#include "Cli_Modules.h"

#include "Cli_Module_Base_Quit.h"
#include "Cli_Module_Base_Help.h"
#include "Cli_Module_Base_Modules.h"
#include "Cli_Module_Base_History.h"

#include "Cli_Module_Base_Log.h"
#include "Cli_Module_Base_Script.h"
#include "Cli_Module_Base_Wait.h"
#include "Cli_Module_Base_Debug.h"

#include "Str_Filter.h"

#include "Cli_CMD_Processor.h"

#include "Cli_TAB_Processor.h"

#include "Do_Command.h"

const string Version = "0.01";

#define ID_EDITCHILD 101

#define IDM_FILE_EXIT 10001

#define IDM_EDIT_CUT 20001
#define IDM_EDIT_COPY 20002
#define IDM_EDIT_SELECT_ALL 20003
#define IDM_EDIT_CLEAR_ALL 20004

// DEBUG
#define IDT_TIMER1 100001

static HWND hwndEdit;

static HANDLE Cli_Input_Thread_Handle = 0;
static DWORD Cli_Input_Thread_ID = 0;

static Cli_Input_Thread_Args_t Cli_Input_Thread_Args;

// DEBUG
static Cli_Input_win32api *Cli_Input_Ptr = 0;
static bool *Cmd_Wait_Stop_Ptr = 0;
static bool *Cmd_Script_Stop_Ptr = 0;
static Cli_Module_Base_Script *Module_Script_Ptr = 0;
static Cli_History *History_Ptr = 0;

void On_Ctrl_C_Z_BACKSLASH(Cli_Input_win32api &Cli_Input, Cli_Output_win32api &Cli_Output, Cli_Input_Item &input_item) {
    Cli_Input.Input_Default_State_Set();
    Cli_Input.Input_Invitation_Print();
}

DWORD WINAPI Cli_Input_Thread_Func(LPVOID arg) {

    Cli_Input_Thread_Args_t *thread_args = (Cli_Input_Thread_Args_t *) arg;

    Cli_Output_win32api Cli_Output;
    Cli_Output.Output_HWND_Set(thread_args->Output_HWND_Get());

    Cli_Input_win32api Cli_Input(Cli_Output, thread_args);

    vector<Level_Description> Levels;

    Cmd_Token_Parser Token_Parser;

    const string Str_Rem_DEF = "$";

    Cli_Cmd_Privilege_ID User_Privilege = CMD_PRIVILEGE_ROOT_DEF;
    Cli_Modules Modules;

    bool tab_log_is_active = false; //!Arg_TAB_Log_Output_File_Name.empty();

    Cli_CMD_Processor CMD_Processor
            (User_Privilege, Modules, Levels, Token_Parser, Cli_Input, Cli_Output, Str_Rem_DEF);
    Cli_TAB_Processor TAB_Processor
            (User_Privilege, Modules, Levels, Token_Parser, Cli_Input, Cli_Output, Str_Rem_DEF, tab_log_is_active);
    Cli_Core Cli
            (User_Privilege, Modules, Levels, Token_Parser, Cli_Input, Cli_Output, Str_Rem_DEF);

    // Modules Add - Begin

    string level_root = "top level";

    bool Cmd_Exit = false;
    bool Cmd_Quit = false;
    Modules.Add(new Cli_Module_Base_Quit(Cli_Input, Cli_Output, Cmd_Exit, Cmd_Quit));

    char C_Single = '?';
    char C_Multy = '*';
    Str_Filter str_filter(C_Single, C_Multy);
    Modules.Add(new Cli_Module_Base_Help(User_Privilege, Modules, str_filter, Cli_Output));
    Modules.Add(new Cli_Module_Base_Modules(Version, Modules, str_filter, Cli_Input, Cli_Output));

    Cli_History History;
    Modules.Add(new Cli_Module_Base_History(History, Cli_Output));

    Modules.Add(new Cli_Module_Base_Log(Cli_Input));

    bool Cmd_Script_Stop = false;
    int Script_Buf_Size = 1024;
    string Script_Command_Str;
    string Script_Label_Str;
    string Script_Dir_Str = "./scripts";
    Cli_Module_Base_Script Module_Script(History, Cli_Input, Cli_Output,
            Str_Rem_DEF, Cmd_Script_Stop, Cmd_Quit, Script_Buf_Size,
            CMD_Processor, Script_Command_Str, Script_Label_Str, Script_Dir_Str,
            str_filter);
    Modules.Add(&Module_Script);
    Do_Command Do_Command_Object(Module_Script);

    bool Log_Wait_Enable = true;
    bool Cmd_Wait_Stop = false;
    Modules.Add(new Cli_Module_Base_Wait(Log_Wait_Enable, Cmd_Wait_Stop, Cli_Input, Cli_Output));

    Modules.Add(new Cli_Module_Base_Debug(User_Privilege, Modules, Levels, CMD_Processor, Cli_Output));

    // DEBUG
    Cli_Input_Ptr = &Cli_Input;
    Cmd_Wait_Stop_Ptr = &Cmd_Wait_Stop;
    Cmd_Script_Stop_Ptr = &Cmd_Script_Stop;
    Module_Script_Ptr = &Module_Script;
    History_Ptr = &History;

    // Modules Add - End

    Cli_Input.Title_Set("Cli Core Test Win32API");
    Cli_Input.User_Set("root");
    Cli_Input.Level_Set(level_root);
    Cli_Input.Invitation_Set("> ");
    Cli_Input.Divider_L_Set("[");
    Cli_Input.Divider_R_Set("]");
    Cli_Input.Input_Init();

    Cli_Output.Output_NewLine();
    Cli_Output.Output_Str("mCli: Cli Core Test");
    Cli_Output.Output_Str(" V");
    Cli_Output.Output_Str(Version);
    Cli_Output.Output_NewLine();
    Cli_Output.Output_NewLine();

    Cli_Output.Output_Str(Cli_Input.Invitation_Full_Get());

    bool stop = false;
    bool is_invitation_print = true;
    while (1) {

        Sleep(1); // 1ms - Minimum Delay for all cases

        if (thread_args->Cli_Input_Thread_CMD_Stop_Get()) {
            break;
        }

        bool is_kbhit = Cli_Input.Input_kbhit(); // Get and Clear Is_kbhit

        if (!is_kbhit) {

            switch (Cli_Input.Input_Mode_Get()) {

                case INPUT_MODE_WAIT:
                {
                    Cli_Input.Input_sleep(1);
                    if (Cli_Input.Wait_Count_Get() > 0) {
                        stringstream s_str;
                        s_str << "Wait " << Cli_Input.Wait_Count_Get() << "...";
                        Cli_Output.Output_NewLine();
                        Cli_Output.Output_Str(s_str.str());
                        Cli_Input.Wait_Count_Set(Cli_Input.Wait_Count_Get() - 1);
                    } else {
                        Cli_Input.Input_Default_State_Set();
                        Cli_Input.Input_Invitation_Print();
                    }
                }
                    break;

            } // switch (Cli_Input.Input_Mode_Get())

        }

        if (is_kbhit) {

            Cli_Input_Char_Item_t char_item = thread_args->Cli_Input_Queue_Get();
            Cli_Input_Item input_item = Cli_Input.On_Key_Pressed(char_item);

            switch (Cli_Input.Input_Mode_Get()) {

                case INPUT_MODE_NORMAL: // Str + Enter / TAB / UP / DOWN / Ctrl+C/Z/BackSlash
                {

                    switch (input_item.Type_Get()) {

                        case CLI_INPUT_ITEM_TYPE_STR:
                        {
                            bool is_no_history = false;
                            bool is_debug = false;

                            string s_trim = Cli.Str_Trim(input_item.Text_Get());

                            if (!is_no_history && !is_debug && !s_trim.empty()) {
                                History.History_Put(s_trim);
                            }

                            bool debug_res = false;
                            CMD_Processor.Process_Input_Item(input_item, is_debug, debug_res);
                            Cli_Input.Input_Str_Set_Empty();
                            if (Cli_Input.Input_Mode_Get() != INPUT_MODE_PROMPT) {
                                Cli_Output.Output_NewLine();
                            }
                        }
                            break;

                        case CLI_INPUT_ITEM_TYPE_TAB:
                        {
                            TAB_Processor.Process_Input_Item(input_item, is_invitation_print);
                        }
                            break;

                        case CLI_INPUT_ITEM_TYPE_UP:
                        {
                            string s_prev = Cli_Input.Input_Str_Get();
                            Cli_Input.Input_Str_Set(History.History_Up());
                            Cli_Input.Input_Str_Modified_To_Output(s_prev);
                            Cli_Input.Input_End();
                            is_invitation_print = false;
                        }
                            break;

                        case CLI_INPUT_ITEM_TYPE_DOWN:
                        {
                            string s_prev = Cli_Input.Input_Str_Get();
                            Cli_Input.Input_Str_Set(History.History_Down());
                            Cli_Input.Input_Str_Modified_To_Output(s_prev);
                            Cli_Input.Input_End();
                            is_invitation_print = false;
                        }
                            break;

                        case CLI_INPUT_ITEM_TYPE_QUIT:
                        {
                            Cli_Output.Output_NewLine();
                            Cli_Output.Output_Str("Quit - Processed");
                            Cli_Output.Output_NewLine();
                            Cli_Input.Input_Default_State_Set();
                            Cli_Input.Input_kbhit(); // Clear Is_kbhit
                            thread_args->Cli_Input_Thread_CMD_Stop_Set(true); // Quit
                        }
                            break;

                        case CLI_INPUT_ITEM_TYPE_CTRL_C:
                        case CLI_INPUT_ITEM_TYPE_CTRL_Z:
                        case CLI_INPUT_ITEM_TYPE_CTRL_BACKSLASH:
                            On_Ctrl_C_Z_BACKSLASH(Cli_Input, Cli_Output, input_item);
                            is_invitation_print = false;
                            break;

                    } // switch (input_item.Type_Get())

                    if (Cli_Input.Input_Mode_Get() != INPUT_MODE_PROMPT) {
                        if (input_item.Type_Get() != CLI_INPUT_ITEM_TYPE_NO) {
                            if (is_invitation_print) {
                                Cli_Output.Output_Str(Cli_Input.Invitation_Full_Get());
                                Cli_Output.Output_Str(Cli_Input.Input_Str_Get());
                            }
                            is_invitation_print = true;
                        }
                    }

                }
                    break;

                case INPUT_MODE_PROMPT: // Str + Enter / Ctrl+C/Z/BackSlash
                {

                    switch (input_item.Type_Get()) {

                        case CLI_INPUT_ITEM_TYPE_STR:
                        {
                            Cli_Output.Output_NewLine();
                            if (input_item.Text_Get() == ("Y") || input_item.Text_Get() == ("y")
                                    || input_item.Text_Get() == ("YES") || input_item.Text_Get() == ("Yes")
                                    || input_item.Text_Get() == ("yes")) {
                                Cli_Output.Output_Str("Answer: Yes");
                                Cli_Input.Do_Object_Yes();
                            } else {
                                Cli_Output.Output_Str("Answer: No");
                            }
                            Cli_Input.Input_Default_State_Set();
                            Cli_Input.Input_Invitation_Print();
                        }
                            break;

                        case CLI_INPUT_ITEM_TYPE_CTRL_C:
                        case CLI_INPUT_ITEM_TYPE_CTRL_Z:
                        case CLI_INPUT_ITEM_TYPE_CTRL_BACKSLASH:
                            On_Ctrl_C_Z_BACKSLASH(Cli_Input, Cli_Output, input_item);
                            break;

                    } // switch (input_item.Type_Get())

                }
                    break;

                case INPUT_MODE_PASSWD: // Str + Enter / Ctrl+C/Z/BackSlash
                {

                    switch (input_item.Type_Get()) {

                        case CLI_INPUT_ITEM_TYPE_STR:
                        {
                            Cli_Output.Output_NewLine();
                            Cli_Output.Output_Str("Password:" + input_item.Text_Get());
                            Cli_Input.Input_Default_State_Set();
                            Cli_Input.Input_Invitation_Print();
                        }
                            break;

                        case CLI_INPUT_ITEM_TYPE_CTRL_C:
                        case CLI_INPUT_ITEM_TYPE_CTRL_Z:
                        case CLI_INPUT_ITEM_TYPE_CTRL_BACKSLASH:
                            On_Ctrl_C_Z_BACKSLASH(Cli_Input, Cli_Output, input_item);
                            break;

                    } // switch (input_item.Type_Get())

                }
                    break;

                case INPUT_MODE_WAIT: // Any Key -> Stop Wait
                {
                    Cli_Output.Output_NewLine();
                    Cli_Output.Output_Str("Wait stopped");
                    Cli_Input.Input_Default_State_Set();
                    Cli_Input.Input_Invitation_Print();
                }
                    break;

            } // switch (Cli_Input.Input_Mode_Get())

        }

        if (Cmd_Exit) {
            Cli_Output.Output_Str("Exit - Processed");
            Cli_Output.Output_NewLine();
            stop = true; // Exit
            thread_args->Cli_Input_Thread_CMD_Stop_Set(true); // Quit
        }
        if (Cmd_Quit) {
            Cli_Output.Output_Str("Quit - Processed");
            Cli_Output.Output_NewLine();
            stop = true; // Quit
            thread_args->Cli_Input_Thread_CMD_Stop_Set(true); // Quit
        }

    }

    PostMessage(thread_args->Main_HWND_Get(), WM_COMMAND, IDM_FILE_EXIT, 0);

    return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, // window handle
        UINT message, // type of message
        WPARAM wParam, // additional information
        LPARAM lParam) // additional information
{

    switch (message) {

        case WM_CREATE:
        {

            // Create Window
            {
                hwndEdit = CreateWindowEx(
                        0, TEXT("EDIT"), // predefined class
                        NULL, // no window title
                        WS_CHILD | WS_VISIBLE | WS_VSCROLL |
                        ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL,
                        0, 0, 0, 0, // set size in WM_SIZE message
                        hwnd, // parent window
                        (HMENU) ID_EDITCHILD, // edit control ID
                        (HINSTANCE) GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                        NULL); // pointer not needed
            }

            // Set new Font
            {
                HFONT hwndEdit_hFont_new = CreateFont(0, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, TEXT("Courier New"));
                SendMessage(hwndEdit, WM_SETFONT, (WPARAM) hwndEdit_hFont_new, 0);
            }

            // Set Main Menu
            {
                HMENU hMainMenu = CreateMenu();
                HMENU hFile = CreateMenu();
                HMENU hEdit = CreateMenu();

                if (hMainMenu != NULL) {

                    BOOL res_file = AppendMenu(hMainMenu, MF_POPUP, (UINT_PTR) hFile, TEXT("&File"));
                    AppendMenu(hFile, MF_ENABLED | MF_STRING, IDM_FILE_EXIT, TEXT("E&xit"));

                    BOOL res_edit = AppendMenu(hMainMenu, MF_POPUP, (UINT_PTR) hEdit, TEXT("&Edit"));
                    AppendMenu(hEdit, MF_ENABLED | MF_STRING, IDM_EDIT_CUT, TEXT("Cut"));
                    AppendMenu(hEdit, MF_ENABLED | MF_STRING, IDM_EDIT_COPY, TEXT("Copy"));
                    AppendMenu(hEdit, MF_SEPARATOR, 0, 0);
                    AppendMenu(hEdit, MF_ENABLED | MF_STRING, IDM_EDIT_SELECT_ALL, TEXT("Select All"));
                    AppendMenu(hEdit, MF_SEPARATOR, 0, 0);
                    AppendMenu(hEdit, MF_ENABLED | MF_STRING, IDM_EDIT_CLEAR_ALL, TEXT("Clear All"));

                    BOOL res_set = SetMenu(hwnd, hMainMenu);

                } else {
                    MessageBox(0, TEXT("hMainMenu = NULL"), TEXT("hMainMenu = NULL"), MB_ICONEXCLAMATION | MB_OK);
                }
            }

            Cli_Input_Thread_Args.Main_HWND_Set(hwnd);
            Cli_Input_Thread_Args.Output_HWND_Set(hwndEdit);

            // Create Cli_Thread
            {
                Cli_Input_Thread_Handle = CreateThread(
                        NULL, // default security attributes
                        0, // use default stack size
                        Cli_Input_Thread_Func, // thread function name
                        &Cli_Input_Thread_Args, // argument to thread function
                        0, // use default creation flags
                        &Cli_Input_Thread_ID);
            }

            // DEBUG
            {
                SetTimer(hwnd, // handle to main window
                        IDT_TIMER1, // timer identifier
                        100, //1000, // 0.1-second interval
                        (TIMERPROC) NULL); // no timer callback
            }

        }
            break;

        case WM_COMMAND:
        {
            switch (wParam) {

                case IDM_EDIT_CUT:
                    SendMessage(hwndEdit, WM_CUT, 0, 0);
                    break;

                case IDM_EDIT_COPY:
                    SendMessage(hwndEdit, WM_COPY, 0, 0);
                    break;

                case IDM_EDIT_SELECT_ALL:
                    SendMessage(hwndEdit, EM_SETSEL, 0, -1); //Select all
                    break;

                case IDM_EDIT_CLEAR_ALL:
                    SendMessage(hwndEdit, EM_SETSEL, 0, -1); //Select all
                    SendMessage(hwndEdit, WM_CLEAR, 0, 0);
                    break;

                case IDM_FILE_EXIT:
                    Cli_Input_Thread_Args.Cli_Input_Thread_CMD_Stop_Set(true);
                    WaitForSingleObject((HANDLE) Cli_Input_Thread_Handle, INFINITE);
                    CloseHandle(Cli_Input_Thread_Args.Cli_Input_Queue_Mutex_Get());
                    PostQuitMessage(0);
                    break;

                default:
                    return DefWindowProc(hwnd, message, wParam, lParam);
            }
        }
            break;

        case WM_SETFOCUS:
        {
            SetFocus(hwndEdit);
        }
            break;

        case WM_SIZE:
        {
            // Make the edit control the size of the window's client area.
            MoveWindow(hwndEdit,
                    0, 0, // starting x- and y-coordinates
                    LOWORD(lParam), // width of client area
                    HIWORD(lParam), // height of client area
                    TRUE); // repaint window
        }
            break;

            // DEBUG
        case WM_TIMER:
        {
            // DEBUG
            {
                static int debug_count = 0;
                stringstream s_str;
                debug_count++;
                s_str << "DEBUG[" << debug_count << "]:";

                if (0) {
                    if (Cli_Input_Ptr) {
                        s_str << " CTRL: " << (Cli_Input_Ptr->Is_Ctrl_C_Pressed_Get() ? " TRUE" : "-");
                        s_str << " set: " << Cli_Input_Ptr->Is_Ctrl_C_Pressed_Set_Count;
                        s_str << " clr: " << Cli_Input_Ptr->Is_Ctrl_C_Pressed_Clear_Count;
                        s_str << " MODE: ";
                        switch (Cli_Input_Ptr->Input_Mode_Get()) {
                            case INPUT_MODE_NORMAL:
                                s_str << "NORMAL";
                                break;
                            case INPUT_MODE_PROMPT:
                                s_str << "PROMPT";
                                break;
                            case INPUT_MODE_PASSWD:
                                s_str << "PASSWD";
                                break;
                            case INPUT_MODE_WAIT:
                                s_str << "WAIT";
                                break;
                        }
                        s_str << " WAIT: " << Cli_Input_Ptr->Wait_Count_Get();

                    } else {
                        s_str << "Cli_Input_Ptr=0";
                    }

                    if (Cmd_Wait_Stop_Ptr) {
                        s_str << " WAIT_STOP: " << (*Cmd_Wait_Stop_Ptr ? " TRUE" : "-");
                    } else {
                        s_str << "Cmd_Wait_Stop_Ptr=0";
                    }

                    if (Cmd_Script_Stop_Ptr) {
                        s_str << " SCRIPT_STOP: " << (*Cmd_Script_Stop_Ptr ? " TRUE" : "-");
                    } else {
                        s_str << "Cmd_Scrip_Stop_Ptr=0";
                    }

                    if (Module_Script_Ptr) {
                        s_str << Module_Script_Ptr->Debug_S_Str.str();
                    } else {
                        s_str << "Module_Script_Ptr=0";
                    }
                }

                {
                    s_str << " Cli_Input: \"" << Cli_Input_Ptr->Input_Str_Get() << "\" pos=" << Cli_Input_Ptr->Input_Str_Pos_Get();
                    s_str << " History: size=" << History_Ptr->History_Size_Get() << " pos=" << History_Ptr->History_Pos_Get();
                }

                string s = s_str.str();
                SetWindowText(Cli_Input_Thread_Args.Main_HWND_Get(), s.c_str());
            }
        }
            break;

        case WM_DESTROY:
        {
            Cli_Input_Thread_Args.Cli_Input_Thread_CMD_Stop_Set(true);
            WaitForSingleObject((HANDLE) Cli_Input_Thread_Handle, INFINITE);
            CloseHandle(Cli_Input_Thread_Args.Cli_Input_Queue_Mutex_Get());
            PostQuitMessage(0);
        }
            break;

        default:
            return DefWindowProc(hwnd, message, wParam, lParam);

    }

    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) {
    HWND hwnd;
    MSG msg;
    WNDCLASS wndclass;
    TCHAR szAppName[] = TEXT("Cli_Core_Win32API");

    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = WndProc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = hInstance;
    wndclass.hIcon = LoadIcon(NULL, IDI_INFORMATION);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH) GetStockObject(LTGRAY_BRUSH);
    wndclass.lpszMenuName = NULL;
    wndclass.lpszClassName = szAppName;

    RegisterClass(&wndclass);

    hwnd = CreateWindow(szAppName, szAppName,
            WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
            CW_USEDEFAULT, CW_USEDEFAULT,
            400, 300,
            NULL, NULL,
            hInstance, NULL);

    ShowWindow(hwnd, iCmdShow);
    UpdateWindow(hwnd);

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}
