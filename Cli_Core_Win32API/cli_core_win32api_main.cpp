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

#define ID_EDITCHILD 101

#define IDM_FILE_EXIT 10001

#define IDM_EDIT_CUT 20001
#define IDM_EDIT_COPY 20002
#define IDM_EDIT_SELECT_ALL 20003
#define IDM_EDIT_CLEAR_ALL 20004

static HWND hwndEdit;

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

            //            Cli_Input_Thread_Args.Main_HWND_Set(hwnd);
            //            Cli_Input_Thread_Args.Output_HWND_Set(hwndEdit);
            //
            //            // Create Cli_Thread
            //            {
            //                Cli_Input_Thread_Handle = CreateThread(
            //                        NULL, // default security attributes
            //                        0, // use default stack size
            //                        Cli_Input_Thread_Func, // thread function name
            //                        &Cli_Input_Thread_Args, // argument to thread function
            //                        0, // use default creation flags
            //                        &Cli_Input_Thread_ID);
            //            }

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
                    //                    Cli_Input_Thread_Args.Cli_Input_Thread_CMD_Stop_Set(true);
                    //                    WaitForSingleObject((HANDLE) Cli_Input_Thread_Handle, INFINITE);
                    //                    CloseHandle(Cli_Input_Thread_Args.Cli_Input_Queue_Mutex_Get());
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
            //            Cli_Input_Thread_Args.Cli_Input_Thread_CMD_Stop_Set(true);
            //            WaitForSingleObject((HANDLE) Cli_Input_Thread_Handle, INFINITE);
            //            CloseHandle(Cli_Input_Thread_Args.Cli_Input_Queue_Mutex_Get());
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
