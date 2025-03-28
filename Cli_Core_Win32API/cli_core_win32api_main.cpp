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
#include <shlwapi.h>

#include "CmdLine_Parse.h"

#include "Cli_Input_Thread_Args.h"

#include "Cli_Input_win32api.h"
#include "Cli_Output_win32api.h"
#include "Cli_Output_ofstream.h"

#include "Cli_Core.h"

#include "Cli_Cmd_Privilege_ID.h"
#include "Cli_Modules.h"

#include "Cli_Module_Base_Rem.h"
#include "Cli_Module_Base_Quit.h"
#include "Cli_Module_Base_Help.h"
#include "Cli_Module_Base_Modules.h"
#include "Cli_Module_Base_History.h"

#include "Cli_Module_Base_Log.h"
#include "Cli_Module_Base_Script.h"
#include "Cli_Module_Base_Wait.h"
#include "Cli_Module_Base_Debug.h"

#include "Cli_Module_Test_Tab_Min_Max.h"
#include "Cli_Module_Test_Terminal.h"

#include "Cli_Module_Vars.h"
#include "Cli_Module_Vars_Expr.h"
#include "Cli_Module_Check.h"
#include "Cli_Module_Base_Level.h"

#include "Str_Filter.h"

#include "Cli_CMD_Processor.h"

#include "Cli_TAB_Processor.h"

#include "Do_Command.h"

const string Version = "0.09";

#define ID_EDITCHILD 101

#define IDM_FILE_EXIT 10001

#define IDM_EDIT_CUT 20001
#define IDM_EDIT_COPY 20002
#define IDM_EDIT_SELECT_ALL 20003
#define IDM_EDIT_CLEAR_ALL 20004

static HWND hwndEdit;

static HANDLE Cli_Input_Thread_Handle = 0;
static DWORD Cli_Input_Thread_ID = 0;

static Cli_Input_Thread_Args_t Args;

void StdOut_Write(wstring s) {
    DWORD written = 0;
    WriteConsole(Args.stdOut, s.c_str(), s.length() * sizeof (wchar_t), &written, NULL);
}

void Version_Print() {
    StdOut_Write(L"V" + wstring(Version.begin(), Version.end()) + L"\r\n");
}

void Help_Print() {
    StdOut_Write(L"Program Cli Core Test V" + wstring(Version.begin(), Version.end()) + L"\r\n");
    StdOut_Write(L"Use: cli_core_test [switches]\r\n");
    StdOut_Write(L"-h                  - print this help;\r\n");
    StdOut_Write(L"-v                  - print version;\r\n");
    StdOut_Write(L"-a                  - print arguments;\r\n");
    StdOut_Write(L"-fscript <file>     - set input script file;\r\n");
    StdOut_Write(L"-fscript_exit_force - set exit force after script executed;\r\n");
    StdOut_Write(L"-flog <file>        - set output log file;\r\n");
    StdOut_Write(L"-ftablog <file>     - set output tab log file;\r\n");
    StdOut_Write(L"-fhistory <file>    - set output history log file;\r\n");
}

void On_Ctrl_C_Z_BACKSLASH(Cli_Input_win32api &Cli_Input, Cli_Output_Abstract &Cli_Output, Cli_Input_Item &input_item) {
    Cli_Input.Input_Default_State_Set();
    Cli_Input.Input_Invitation_Print();
}

DWORD WINAPI Cli_Input_Thread_Func(LPVOID arg) {

    Cli_Input_Thread_Args_t *thread_args = (Cli_Input_Thread_Args_t *) arg;

    map<string, string> Values_Map;

    Cli_Output_win32api Cli_Output_Win32API;
    Cli_Output_Win32API.Output_HWND_Set(thread_args->Output_HWND_Get());

    Cli_Output_ofstream Cli_Output_File(string(Args.Arg_Log_Output_File_Name.begin(), Args.Arg_Log_Output_File_Name.end()));
    Cli_Output_Abstract &Cli_Output = (Args.Arg_Log_Output_File_Name.empty() ? (Cli_Output_Abstract &) Cli_Output_Win32API : (Cli_Output_Abstract &) Cli_Output_File);

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

    Modules.Add(new Cli_Module_Base_Rem(Str_Rem_DEF, Cli_Output));

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

    Modules.Add(new Cli_Module_Test_Tab_Min_Max());
    Modules.Add(new Cli_Module_Test_Terminal(Cli_Input, Cli_Output));

    Modules.Add(new Cli_Module_Base_Debug(User_Privilege, Modules, Levels, CMD_Processor, Cli_Output));

    Str_Get_Without_Commas str_without_commas;
    Str_Get_Int str_int;

    Modules.Add((new Cli_Module_Vars(Modules, Values_Map, str_filter, str_without_commas, str_int,
            Cli_Output, C_Single, C_Multy)));

    Modules.Add((new Cli_Module_Vars_Expr(Values_Map, str_without_commas, str_int,
            Cli_Output, C_Single, C_Multy)));

    Modules.Add((new Cli_Module_Check(Modules, Values_Map, str_filter, str_without_commas, str_int,
            Cli_Output, Cmd_Script_Stop, Script_Command_Str, Script_Label_Str,
            Do_Command_Object)));

    Modules.Add(new Cli_Module_Base_Level(Cli_Input, Cli_Output, level_root));

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

    if (!Args.Arg_Script_File_Name.empty()) {
        Module_Script.Script_Execute_Level = 0;
        Module_Script.Script_Execute_File_Name = string(Args.Arg_Script_File_Name.begin(), Args.Arg_Script_File_Name.end());
        Module_Script.Script_Execute_Exit_Force = Args.Arg_Script_Exit_Force;
        stringstream s_str;
        s_str << "Executing script \"" << Module_Script.Script_Execute_File_Name << "\""
                << (Module_Script.Script_Execute_Exit_Force ? " (exit force)" : " (no exit force)") << "...";
        Cli_Output_Win32API.Output_Str(s_str.str());
        bool is_no_history;
        bool res_script = Module_Script.do_script(Module_Script.Script_Execute_File_Name, is_no_history = true);
        if (!res_script) {
            Cli_Output.Output_Str("ERROR: execute script \"" + string(Args.Arg_Script_File_Name.begin(), Args.Arg_Script_File_Name.end()) + "\" - Failed");
            Cli_Output.Output_NewLine();
        }
    }

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
                            if (Cli_Input.Input_Mode_Get() != INPUT_MODE_PROMPT
                                    && Cli_Input.Input_Mode_Get() != INPUT_MODE_PASSWD) {
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

                    if (Cli_Input.Input_Mode_Get() != INPUT_MODE_PROMPT
                            && Cli_Input.Input_Mode_Get() != INPUT_MODE_PASSWD) {
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
                            Cli_Input.Do_Object_Yes();
                            Cli_Output.Output_NewLine();
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
                            Cli_Input.Do_Object_Yes();
                            Cli_Output.Output_NewLine();
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
                HFONT hwndEdit_hFont_new = (HFONT) GetStockObject(ANSI_FIXED_FONT);
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

            Args.Main_HWND_Set(hwnd);
            Args.Output_HWND_Set(hwndEdit);

            // Create Cli_Thread
            {
                Cli_Input_Thread_Handle = CreateThread(
                        NULL, // default security attributes
                        0, // use default stack size
                        Cli_Input_Thread_Func, // thread function name
                        &Args, // argument to thread function
                        0, // use default creation flags
                        &Cli_Input_Thread_ID);
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
                    Args.Cli_Input_Thread_CMD_Stop_Set(true);
                    WaitForSingleObject((HANDLE) Cli_Input_Thread_Handle, INFINITE);
                    CloseHandle(Args.Cli_Input_Queue_Mutex_Get());
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

        case WM_DESTROY:
        {
            Args.Cli_Input_Thread_CMD_Stop_Set(true);
            WaitForSingleObject((HANDLE) Cli_Input_Thread_Handle, INFINITE);
            CloseHandle(Args.Cli_Input_Queue_Mutex_Get());
            PostQuitMessage(0);
        }
            break;

        default:
            return DefWindowProc(hwnd, message, wParam, lParam);

    }

    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) {

    int error_code = 0; // Ok

    {
        Args.stdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        if (Args.stdOut != NULL && Args.stdOut != INVALID_HANDLE_VALUE) {

            vector<wstring> argv = CmdLine_Parse(GetCommandLine());

            for (int i = 1; i < argv.size(); i++) {
                wstring s = argv[i];
                if (s == L"-h" || s == L"-help" || s == L"-?"
                        || s == L"--h" || s == L"--help" || s == L"--?"
                        || s == L"/h" || s == L"/help" || s == L"/?") {
                    Args.Arg_Help_Print = true;
                } else if (s == L"-v" || s == L"--v"
                        || s == L"-version" || s == L"--version") {
                    Args.Arg_Version_Print = true;
                } else if (s == L"-a") {
                    Args.Arg_Arguments_Print = true;
                } else if (s == L"-fscript") {
                    i++;
                    if (i < argv.size() && argv[i][0] != '-') {
                        Args.Arg_Script_File_Name = argv[i];
                    } else {
                        StdOut_Write(L"ERROR: switch \"" + s + L"\" without argument\r\n");
                        exit(1); // Error
                    }
                } else if (s == L"-fscript_exit_force") {
                    Args.Arg_Script_Exit_Force = true;
                } else if (s == L"-flog") {
                    i++;
                    if (i < argv.size() && argv[i][0] != '-') {
                        Args.Arg_Log_Output_File_Name = argv[i];
                    } else {
                        StdOut_Write(L"ERROR: switch \"" + s + L"\" without argument\r\n");
                        exit(1); // Error
                    }
                } else if (s == L"-ftablog") {
                    i++;
                    if (i < argv.size() && argv[i][0] != '-') {
                        Args.Arg_TAB_Log_Output_File_Name = argv[i];
                    } else {
                        StdOut_Write(L"ERROR: switch \"" + s + L"\" without argument\r\n");
                        exit(1); // Error
                    }
                } else if (s == L"-fhistory") {
                    i++;
                    if (i < argv.size() && argv[i][0] != '-') {
                        Args.Arg_HISTORY_Log_Output_File_Name = argv[i];
                    } else {
                        StdOut_Write(L"ERROR: switch \"" + s + L"\" without argument\r\n");
                        exit(1); // Error
                    }
                }
            }

            //if (argc == 1) {
            //    Arg_Help_Print = true;
            //}

            bool is_action = false;

            if (Args.Arg_Version_Print) {
                Version_Print();
                is_action = true;
            }

            if (Args.Arg_Help_Print) {
                Help_Print();
                is_action = true;
            }

            if (Args.Arg_Arguments_Print) {
                StdOut_Write(L"Arguments:\r\n");
                StdOut_Write(L"             Arg_Script_File_Name:" + Args.Arg_Script_File_Name + L"\r\n");
                StdOut_Write(L"            Arg_Script_Exit_Force:" + wstring(Args.Arg_Script_Exit_Force ? L"on" : L"off") + L"\r\n");
                StdOut_Write(L"         Arg_Log_Output_File_Name:" + Args.Arg_Log_Output_File_Name + L"\r\n");
                StdOut_Write(L"     Arg_TAB_Log_Output_File_Name:" + Args.Arg_TAB_Log_Output_File_Name + L"\r\n");
                StdOut_Write(L" Arg_HISTORY_Log_Output_File_Name:" + Args.Arg_HISTORY_Log_Output_File_Name + L"\r\n");
                is_action = true;
            }

            if (is_action) {
                exit(error_code); // Ok
            }

        }
    }

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
