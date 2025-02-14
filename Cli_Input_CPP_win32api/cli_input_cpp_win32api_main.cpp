#include <sstream>
#include <list>

using namespace std;

#include <windows.h>
#include <winuser.h>

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#include "Cli_Input_win32api.h"
#include "Cli_Output_win32api.h"

#include "Cli_Input_Thread_Args.h"

#define ID_EDITCHILD 101

#define IDM_FILE_EXIT 10001

#define IDM_EDIT_CUT 20001
#define IDM_EDIT_COPY 20002
#define IDM_EDIT_SELECT_ALL 20003
#define IDM_EDIT_CLEAR_ALL 20004

void AppendText(const HWND hwndEdit, const TCHAR *newText) {
    int len_prev1 = GetWindowTextLength(hwndEdit);
    if (len_prev1) {
        SendMessage(hwndEdit, EM_SETSEL, len_prev1, len_prev1); //Select end pos
        SendMessage(hwndEdit, EM_REPLACESEL, FALSE, (LPARAM) "\r\n");
    }
    int len_prev2 = GetWindowTextLength(hwndEdit);
    SendMessage(hwndEdit, EM_SETSEL, len_prev2, len_prev2); //Select end pos
    SendMessage(hwndEdit, EM_REPLACESEL, FALSE, (LPARAM) newText);
    SendMessage(hwndEdit, EM_SETSEL, -1, -1); //Unselect and stay at the end pos
}

static HWND hwndEdit;

static pthread_t Cli_Input_Thread_Handle = 0;

static Cli_Input_Thread_Args_t Cli_Input_Thread_Args;

void *Cli_Input_Thread_Func(void *arg) {

    Cli_Input_Thread_Args_t *thread_args = (Cli_Input_Thread_Args_t *) arg;

    string Help_Str = "Help: Q - quit, C - clear, H - help, A - ask(y/n), P - passwd(no echo), W - wait";

    Cli_Output_win32api Cli_Output;
    Cli_Output.Output_HWND_Set(thread_args->Output_HWND_Get());

    Cli_Output.Output_NewLine();
    Cli_Output.Output_Str("Cli Input Win32API started");
    Cli_Output.Output_NewLine();
    Cli_Output.Output_NewLine();

    Cli_Input_win32api Cli_Input(Cli_Output, thread_args);

    Cli_Input.Title_Set("cli demo");
    Cli_Input.User_Set("root");
    Cli_Input.Level_Set("top level");
    Cli_Input.Invitation_Set("> ");
    Cli_Input.Divider_L_Set("[");
    Cli_Input.Divider_R_Set("]");
    Cli_Input.Input_Init();

    Cli_Output.Output_Str(Cli_Input.Invitation_Full_Get());

    int state = 0;
    while (1) {

        if (thread_args->Cli_Input_Thread_CMD_Stop) {
            break;
        }

        if (thread_args->Cli_Input_Thread_Queue.empty()) {

            if (Cli_Input.Input_Mode_Get() == INPUT_MODE_NORMAL) {

                switch (state) {
                    case 0:
                        usleep(1000);
                        break;
                    case 1:
                        Cli_Output.Output_Str("Press Any Key to stop");
                        Cli_Output.Output_NewLine();
                        Cli_Input.Input_sleep(1);
                        break;
                }

            } else if (Cli_Input.Input_Mode_Get() == INPUT_MODE_WAIT) {
                sleep(1);
                stringstream s_str;
                if (Cli_Input.Wait_Count_Get() > 0) {
                    if (thread_args->Cli_Input_Thread_Queue.empty()) {
                        s_str << "Wait " << Cli_Input.Wait_Count_Get() << "...";
                        Cli_Output.Output_NewLine();
                        Cli_Output.Output_Str(s_str.str());
                        Cli_Input.Wait_Count_Set(Cli_Input.Wait_Count_Get() - 1);
                    }
                } else {
                    Cli_Output.Output_NewLine();
                    Cli_Input.Input_Str_Set_Empty();
                    Cli_Output.Output_Str(Cli_Input.Invitation_Full_Get());
                    Cli_Output.Output_Str(Cli_Input.Input_Str_Get());
                    Cli_Input.Is_Ctrl_C_Pressed_Clear();
                    Cli_Input.Input_Mode_Set(INPUT_MODE_NORMAL);
                    Cli_Input.Is_Echo_On();
                    Cli_Input.Wait_Count_Set(-1);
                }
            }

        } else {

            Cli_Input_Char_Item_t char_item = thread_args->Cli_Input_Queue_Get();
            Cli_Input_Item input_item = Cli_Input.On_Key_Pressed(char_item);

            if (state == 0) {

                if (input_item.Type_Get() == CLI_INPUT_ITEM_TYPE_STR) {

                    if (Cli_Input.Input_Mode_Get() == INPUT_MODE_NORMAL) {

                        string input_str = input_item.Text_Get();
                        if (input_str == "Q" || input_str == "quit") {
                            Cli_Output.Output_NewLine();
                            Cli_Output.Output_Str("Quit - Processed");
                            Cli_Output.Output_NewLine();
                            state = 1; // Quit
                        } else if (input_str == "C" || input_str == "clear") {
                            Cli_Input.Input_Clear();
                            Cli_Output.Output_NewLine();
                            Cli_Output.Output_Str("Clear - Processed");
                            Cli_Output.Output_NewLine();
                            Cli_Input.Input_Str_Set_Empty();
                            Cli_Output.Output_Str(Cli_Input.Invitation_Full_Get());
                            Cli_Output.Output_Str(Cli_Input.Input_Str_Get());
                        } else if (input_str == "H" || input_str == "help") {
                            Cli_Output.Output_NewLine();
                            Cli_Output.Output_Str(Help_Str);
                            Cli_Output.Output_NewLine();
                            Cli_Input.Input_Str_Set_Empty();
                            Cli_Output.Output_Str(Cli_Input.Invitation_Full_Get());
                            Cli_Output.Output_Str(Cli_Input.Input_Str_Get());
                        } else if (input_str == "A" || input_str == "ask") {
                            Cli_Output.Output_NewLine();
                            Cli_Output.Output_Str("Is it right?(yes/no) ");
                            Cli_Input.Input_Str_Set_Empty();
                            Cli_Input.Input_Mode_Set(INPUT_MODE_PROMPT);
                        } else if (input_str == "P" || input_str == "passwd") {
                            Cli_Output.Output_NewLine();
                            Cli_Output.Output_Str("Password:");
                            Cli_Input.Input_Str_Set_Empty();
                            Cli_Input.Input_Mode_Set(INPUT_MODE_PASSWD);
                            Cli_Input.Is_Echo_Off();
                        } else if (input_str == "W" || input_str == "wait") {
                            Cli_Output.Output_NewLine();
                            Cli_Output.Output_Str("Wait (Press Enter to stop):");
                            //Cli_Output.Output_NewLine();
                            Cli_Input.Input_Str_Set_Empty();
                            Cli_Input.Input_Mode_Set(INPUT_MODE_WAIT);
                            Cli_Input.Wait_Count_Set(10);
                        } else if (!input_str.empty()) {
                            Cli_Output.Output_NewLine();
                            Cli_Output.Output_Str(input_item.Text_Get());
                            Cli_Output.Output_Str(" - Not Processed");
                            Cli_Output.Output_NewLine();
                            Cli_Input.Input_Str_Set_Empty();
                            Cli_Output.Output_Str(Cli_Input.Invitation_Full_Get());
                            Cli_Output.Output_Str(Cli_Input.Input_Str_Get());
                        } else {
                            Cli_Output.Output_NewLine();
                            Cli_Input.Input_Str_Set_Empty();
                            Cli_Output.Output_Str(Cli_Input.Invitation_Full_Get());
                            Cli_Output.Output_Str(Cli_Input.Input_Str_Get());
                        }

                    } else if (Cli_Input.Input_Mode_Get() == INPUT_MODE_PROMPT) {
                        Cli_Output.Output_NewLine();
                        if (input_item.Text_Get() == ("Y") || input_item.Text_Get() == ("y")
                                || input_item.Text_Get() == ("YES") || input_item.Text_Get() == ("Yes") || input_item.Text_Get() == ("yes")) {
                            Cli_Output.Output_Str("Answer: Yes");
                        } else {
                            Cli_Output.Output_Str("Answer: No");
                        }
                        Cli_Output.Output_NewLine();
                        Cli_Input.Input_Str_Set_Empty();
                        Cli_Output.Output_Str(Cli_Input.Invitation_Full_Get());
                        Cli_Output.Output_Str(Cli_Input.Input_Str_Get());
                        Cli_Input.Input_Mode_Set(INPUT_MODE_NORMAL);

                    } else if (Cli_Input.Input_Mode_Get() == INPUT_MODE_PASSWD) {
                        Cli_Output.Output_NewLine();
                        Cli_Output.Output_Str("Password:" + input_item.Text_Get());
                        Cli_Output.Output_NewLine();
                        Cli_Input.Input_Str_Set_Empty();
                        Cli_Output.Output_Str(Cli_Input.Invitation_Full_Get());
                        Cli_Output.Output_Str(Cli_Input.Input_Str_Get());
                        Cli_Input.Input_Mode_Set(INPUT_MODE_NORMAL);
                        Cli_Input.Is_Echo_On();

                    } else if (Cli_Input.Input_Mode_Get() == INPUT_MODE_WAIT) {
                        Cli_Input.Wait_Count_Set(-1);
                        Cli_Output.Output_NewLine();
                        Cli_Output.Output_Str("Wait stopped");
                        Cli_Output.Output_NewLine();
                        Cli_Input.Input_Str_Set_Empty();
                        Cli_Output.Output_Str(Cli_Input.Invitation_Full_Get());
                        Cli_Output.Output_Str(Cli_Input.Input_Str_Get());
                        Cli_Input.Input_Mode_Set(INPUT_MODE_NORMAL);
                    }

                } else if (input_item.Type_Get() == CLI_INPUT_ITEM_TYPE_TAB) {
                    Cli_Output.Output_NewLine();
                    Cli_Output.Output_Str(Help_Str);

                    Cli_Input.Input_Str_Pos_Set(Cli_Input.Input_Str_Get().length());

                    Cli_Output.Output_NewLine();
                    Cli_Output.Output_Str(Cli_Input.Invitation_Full_Get());
                    Cli_Output.Output_Str(Cli_Input.Input_Str_Get());

                } else if (input_item.Type_Get() == CLI_INPUT_ITEM_TYPE_UP) {
                    Cli_Output.Output_NewLine();
                    Cli_Output.Output_Str("UP: ");
                    Cli_Output.Output_Str(input_item.Text_Get());
                    Cli_Output.Output_NewLine();
                    Cli_Output.Output_Str(Cli_Input.Invitation_Full_Get());
                    Cli_Output.Output_Str(Cli_Input.Input_Str_Get());
                } else if (input_item.Type_Get() == CLI_INPUT_ITEM_TYPE_DOWN) {
                    Cli_Output.Output_NewLine();
                    Cli_Output.Output_Str("DOWN: ");
                    Cli_Output.Output_Str(input_item.Text_Get());
                    Cli_Output.Output_NewLine();
                    Cli_Output.Output_Str(Cli_Input.Invitation_Full_Get());
                    Cli_Output.Output_Str(Cli_Input.Input_Str_Get());
                } else if (input_item.Type_Get() == CLI_INPUT_ITEM_TYPE_QUIT) {
                    Cli_Output.Output_NewLine();
                    Cli_Output.Output_Str("Quit - Processed");
                    Cli_Output.Output_NewLine();
                    state = 1; // Quit

                } else if (input_item.Type_Get() == CLI_INPUT_ITEM_TYPE_CTRL_C) {

                    if (Cli_Input.Input_Mode_Get() == INPUT_MODE_WAIT) {
                        Cli_Output.Output_NewLine();
                        Cli_Output.Output_Str("Wait stopped");
                        Cli_Output.Output_NewLine();
                        Cli_Input.Input_Str_Set_Empty();
                        Cli_Output.Output_Str(Cli_Input.Invitation_Full_Get());
                        Cli_Output.Output_Str(Cli_Input.Input_Str_Get());
                        Cli_Input.Is_Ctrl_C_Pressed_Clear();
                        Cli_Input.Input_Mode_Set(INPUT_MODE_NORMAL);
                        Cli_Input.Is_Echo_On();
                        Cli_Input.Wait_Count_Set(-1);
                    } else {
                        Cli_Output.Output_NewLine();
                        Cli_Output.Output_Str("Ctrl+C - Processed");
                        Cli_Output.Output_NewLine();
                        Cli_Input.Input_Str_Set_Empty();
                        Cli_Output.Output_Str(Cli_Input.Invitation_Full_Get());
                        Cli_Output.Output_Str(Cli_Input.Input_Str_Get());
                        Cli_Input.Is_Ctrl_C_Pressed_Clear();
                        Cli_Input.Input_Mode_Set(INPUT_MODE_NORMAL);
                        Cli_Input.Is_Echo_On();
                        Cli_Input.Wait_Count_Set(-1);
                    }

                } else if (input_item.Type_Get() == CLI_INPUT_ITEM_TYPE_CTRL_Z) {

                    if (Cli_Input.Input_Mode_Get() == INPUT_MODE_WAIT) {
                        Cli_Output.Output_NewLine();
                        Cli_Output.Output_Str("Wait stopped");
                        Cli_Output.Output_NewLine();
                        Cli_Input.Input_Str_Set_Empty();
                        Cli_Output.Output_Str(Cli_Input.Invitation_Full_Get());
                        Cli_Output.Output_Str(Cli_Input.Input_Str_Get());
                        Cli_Input.Is_Ctrl_C_Pressed_Clear();
                        Cli_Input.Input_Mode_Set(INPUT_MODE_NORMAL);
                        Cli_Input.Is_Echo_On();
                        Cli_Input.Wait_Count_Set(-1);
                    } else {
                        Cli_Output.Output_NewLine();
                        Cli_Output.Output_Str("Ctrl+Z - Processed");
                        Cli_Output.Output_NewLine();
                        Cli_Input.Input_Str_Set_Empty();
                        Cli_Output.Output_Str(Cli_Input.Invitation_Full_Get());
                        Cli_Output.Output_Str(Cli_Input.Input_Str_Get());
                        Cli_Input.Is_Ctrl_C_Pressed_Clear();
                        Cli_Input.Input_Mode_Set(INPUT_MODE_NORMAL);
                        Cli_Input.Is_Echo_On();
                        Cli_Input.Wait_Count_Set(-1);
                    }

                } else if (input_item.Type_Get() == CLI_INPUT_ITEM_TYPE_CTRL_BACKSLASH) {

                    if (Cli_Input.Input_Mode_Get() == INPUT_MODE_WAIT) {
                        Cli_Output.Output_NewLine();
                        Cli_Output.Output_Str("Wait stopped");
                        Cli_Output.Output_NewLine();
                        Cli_Input.Input_Str_Set_Empty();
                        Cli_Output.Output_Str(Cli_Input.Invitation_Full_Get());
                        Cli_Output.Output_Str(Cli_Input.Input_Str_Get());
                        Cli_Input.Is_Ctrl_C_Pressed_Clear();
                        Cli_Input.Input_Mode_Set(INPUT_MODE_NORMAL);
                        Cli_Input.Is_Echo_On();
                        Cli_Input.Wait_Count_Set(-1);
                    } else {
                        Cli_Output.Output_NewLine();
                        Cli_Output.Output_Str("Ctrl+BackSlash - Processed");
                        Cli_Output.Output_NewLine();
                        Cli_Input.Input_Str_Set_Empty();
                        Cli_Output.Output_Str(Cli_Input.Invitation_Full_Get());
                        Cli_Output.Output_Str(Cli_Input.Input_Str_Get());
                        Cli_Input.Is_Ctrl_C_Pressed_Clear();
                        Cli_Input.Input_Mode_Set(INPUT_MODE_NORMAL);
                        Cli_Input.Is_Echo_On();
                        Cli_Input.Wait_Count_Set(-1);
                    }

                }

            } else if (state == 1) {

                if (Cli_Input.Input_kbhit()) {
                    Cli_Output.Output_Str("Press Any Key to exit");
                    Cli_Output.Output_NewLine();
                    state = 2;
                }

            } else if (state == 2) {

                if (Cli_Input.Input_kbhit()) {
                    state = 3;
                    SendMessage(thread_args->Main_HWND_Get(), WM_DESTROY, 0, 0);
                }

            }

        }

    }

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
                        0, "EDIT", // predefined class
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
                HMENU hTest = CreateMenu();
                HMENU hHelp = CreateMenu();

                if (hMainMenu != NULL) {

                    BOOL res_file = AppendMenu(hMainMenu, MF_POPUP, (UINT_PTR) hFile, "&File");
                    AppendMenu(hFile, MF_ENABLED | MF_STRING, IDM_FILE_EXIT, "E&xit");

                    BOOL res_edit = AppendMenu(hMainMenu, MF_POPUP, (UINT_PTR) hEdit, "&Edit");
                    AppendMenu(hEdit, MF_ENABLED | MF_STRING, IDM_EDIT_CUT, "Cut");
                    AppendMenu(hEdit, MF_ENABLED | MF_STRING, IDM_EDIT_COPY, "Copy");
                    AppendMenu(hEdit, MF_SEPARATOR, 0, 0);
                    AppendMenu(hEdit, MF_ENABLED | MF_STRING, IDM_EDIT_SELECT_ALL, "Select All");
                    AppendMenu(hEdit, MF_SEPARATOR, 0, 0);
                    AppendMenu(hEdit, MF_ENABLED | MF_STRING, IDM_EDIT_CLEAR_ALL, "Clear All");

                    BOOL res_set = SetMenu(hwnd, hMainMenu);

                } else {
                    MessageBox(0, "hMainMenu = NULL", "hMainMenu = NULL", MB_ICONEXCLAMATION | MB_OK);
                }
            }

            Cli_Input_Thread_Args.Main_HWND_Set(hwnd);
            Cli_Input_Thread_Args.Output_HWND_Set(hwndEdit);

            // Create Cli_Thread
            {
                pthread_create(&Cli_Input_Thread_Handle, 0, Cli_Input_Thread_Func, &Cli_Input_Thread_Args);
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
                    Cli_Input_Thread_Args.Cli_Input_Thread_CMD_Stop = true;
                    WaitForSingleObject((HANDLE) Cli_Input_Thread_Handle, INFINITE);
                    CloseHandle(Cli_Input_Thread_Args.Cli_Input_Queue_Mutex);
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
            Cli_Input_Thread_Args.Cli_Input_Thread_CMD_Stop = true;
            WaitForSingleObject((HANDLE) Cli_Input_Thread_Handle, INFINITE);
            CloseHandle(Cli_Input_Thread_Args.Cli_Input_Queue_Mutex);
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
    static const char *szAppName = "Cli_Input_CPP_win32api";

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
