#include <sstream>
#include <list>

using namespace std;

#include <windows.h>
#include <winuser.h>

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#include "Cli_Output_win32api.h"

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

typedef LRESULT CALLBACK fpWndProc(HWND hwnd, // window handle
        UINT message, // type of message
        WPARAM wParam, // additional information
        LPARAM lParam);

static HWND hwndEdit;
static fpWndProc *hwndEdit_WndProc_Org;

static pthread_t Cli_Input_Thread_Handle = 0;

enum CLI_CT {
    CLI_CT_NO,

    CLI_CT_CHAR,

    CLI_CT_CTRL_C,
    CLI_CT_CTRL_Z,
    CLI_CT_CTRL_BACKSLASH,

    CLI_CT_UP,
    CLI_CT_DOWN,
    CLI_CT_LEFT,
    CLI_CT_RIGHT,

    CLI_CT_HOME,
    CLI_CT_END,
    CLI_CT_DELETE,

    CLI_CT_ENTER,
    CLI_CT_TAB,
    CLI_CT_ESC,
    CLI_CT_BACK,

    CLI_CT_LAST,
    CLI_CT_UNDEFINED
};

class Cli_Input_Char_Item {
public:
    CLI_CT Char_Type;
    WPARAM wParam;
    string Text;

    Cli_Input_Char_Item(CLI_CT char_type, WPARAM wparam, string text) : Char_Type(char_type), wParam(wparam), Text(text) {
    }

};

class Cli_Input_Thread_Args_t {
public:
    HWND Output_HWND;
    bool Cli_Input_Thread_CMD_Stop;
    list<Cli_Input_Char_Item> Cli_Input_Thread_Queue;
    HANDLE Cli_Input_Queue_Mutex;
    int Cli_Input_Queue_Mutex_Wait_Time;

    Cli_Input_Thread_Args_t() : Output_HWND(0), Cli_Input_Thread_CMD_Stop(false),
    Cli_Input_Queue_Mutex(0), Cli_Input_Queue_Mutex_Wait_Time(100) {
        Cli_Input_Queue_Mutex = CreateMutex(
                NULL, // default security attributes
                FALSE, // initially not owned
                NULL);
    }

    void Output_HWND_Set(HWND hwnd) {
        Output_HWND = hwnd;
    }

    HWND Output_HWND_Get() {
        return Output_HWND;
    }

    void Cli_Input_Queue_Add(WPARAM wParam, CLI_CT ct, string s) {
        DWORD dwWaitResult = WaitForSingleObject(Cli_Input_Queue_Mutex, INFINITE);
        switch (dwWaitResult) {
            case WAIT_OBJECT_0:
            {
                Cli_Input_Thread_Queue.push_back(Cli_Input_Char_Item(ct, wParam, s));
                ReleaseMutex(Cli_Input_Queue_Mutex);
            }
                break;
        }
    }

};

static Cli_Input_Thread_Args_t Cli_Input_Thread_Args;

void *Cli_Input_Thread_Func(void *arg) {

    Cli_Input_Thread_Args_t *thread_args = (Cli_Input_Thread_Args_t *) arg;

    Cli_Output_win32api Cli_Output;
    Cli_Output.Output_HWND_Set(thread_args->Output_HWND_Get());

    Cli_Output.Output_Str("Started");
    Cli_Output.Output_NewLine();

    while (1) {

        if (thread_args->Cli_Input_Thread_CMD_Stop) {
            break;
        }

        if (thread_args->Cli_Input_Thread_Queue.empty()) {
            usleep(1000);
        } else {

            DWORD dwWaitResult = WaitForSingleObject(thread_args->Cli_Input_Queue_Mutex, thread_args->Cli_Input_Queue_Mutex_Wait_Time);
            switch (dwWaitResult) {
                case WAIT_OBJECT_0:
                {
                    static bool is_newline = true;
                    if (!thread_args->Cli_Input_Thread_Queue.empty()) {
                        Cli_Input_Char_Item item = thread_args->Cli_Input_Thread_Queue.front();
                        thread_args->Cli_Input_Thread_Queue.pop_front();
                        ReleaseMutex(thread_args->Cli_Input_Queue_Mutex);

                        CLI_CT ct = item.Char_Type;
                        string s = item.Text;
                        if (ct == CLI_CT_ENTER
                                || ct == CLI_CT_CTRL_C || ct == CLI_CT_CTRL_Z || ct == CLI_CT_CTRL_BACKSLASH
                                || ct == CLI_CT_TAB || ct == CLI_CT_BACK || ct == CLI_CT_ESC
                                || ct == CLI_CT_UP || ct == CLI_CT_DOWN || ct == CLI_CT_LEFT || ct == CLI_CT_RIGHT
                                || ct == CLI_CT_HOME || ct == CLI_CT_END || ct == CLI_CT_DELETE) {
                            if (!is_newline) {
                                Cli_Output.Output_NewLine();
                            }
                            Cli_Output.Output_Str(s);
                            Cli_Output.Output_NewLine();
                            is_newline = true;
                        } else {
                            Cli_Output.Output_Str(s);
                            is_newline = false;
                        }

                    }

                }
                    break;
            }

        }

    }
    return 0;
}

LRESULT CALLBACK hwndEdit_WndProc_New(HWND hwnd, // window handle
        UINT message, // type of message
        WPARAM wParam, // additional information
        LPARAM lParam) // additional information
{

    switch (message) {

        case WM_KEYDOWN:
        {
            CLI_CT ct = CLI_CT_NO;
            const int buf_size = 1024;
            char buf[buf_size];
            const char *s = "";
            bool is_print = true;
            switch (wParam) {
                case VK_CONTROL:
                    //s = "CTRL";
                    is_print = false;
                    break;
                case VK_RETURN:
                    s = "ENTER";
                    is_print = false;
                    break;
                case VK_TAB:
                    s = "TAB";
                    is_print = false;
                    break;
                case VK_BACK:
                    s = "BACK";
                    is_print = false;
                    break;
                case VK_CANCEL:
                    s = "Ctrl+C";
                    ct = CLI_CT_CTRL_C;
                    break;
                case 0x1A:
                    s = "Ctrl+Z";
                    ct = CLI_CT_CTRL_Z;
                    break;
                case 0xDC:
                    if (GetKeyState(VK_CONTROL) < 0) {
                        s = "Ctrl+BACKSLASH";
                        ct = CLI_CT_CTRL_BACKSLASH;
                    } else {
                        is_print = false;
                    }
                    break;
                case VK_UP:
                    s = "UP";
                    ct = CLI_CT_UP;
                    break;
                case VK_DOWN:
                    s = "DOWN";
                    ct = CLI_CT_DOWN;
                    break;
                case VK_RIGHT:
                    s = "RIGHT";
                    ct = CLI_CT_RIGHT;
                    break;
                case VK_LEFT:
                    s = "LEFT";
                    ct = CLI_CT_LEFT;
                    break;
                case VK_DELETE:
                    s = "DELETE";
                    ct = CLI_CT_DELETE;
                    break;
                case VK_HOME:
                    s = "HOME";
                    ct = CLI_CT_HOME;
                    break;
                case VK_END:
                    s = "END";
                    ct = CLI_CT_END;
                    break;

                default:
                    is_print = false;
                    break;
            }

            if (is_print) {
                Cli_Input_Thread_Args.Cli_Input_Queue_Add(wParam, ct, s);
            }

        }
            break;

        case WM_CHAR:
        {
            CLI_CT ct = CLI_CT_NO;
            const int buf_size = 1024;
            char buf[buf_size];
            char s_buf[] = "12"; // Dummy value
            const char *s = s_buf;
            bool is_print = true;
            switch (wParam) {
                case VK_RETURN:
                    s = "ENTER";
                    ct = CLI_CT_ENTER;
                    break;
                case VK_TAB:
                    s = "TAB";
                    ct = CLI_CT_TAB;
                    break;
                case VK_BACK:
                    s = "BACK";
                    ct = CLI_CT_BACK;
                    break;
                case VK_CANCEL:
                    s = "Ctrl+C";
                    ct = CLI_CT_CTRL_C;
                    break;
                case 0x1A:
                    s = "Ctrl+Z";
                    ct = CLI_CT_CTRL_Z;
                    break;
                case 0x0A:
                    s = "\"\\r\"";
                    ct = CLI_CT_ENTER;
                    break;
                case 0x1B:
                    s = "ESC";
                    ct = CLI_CT_ESC;
                    break;
                default:
                    s_buf[0] = wParam;
                    s_buf[1] = '\0';
                    if (wParam < 0x20) {
                        is_print = false;
                    } else {
                        ct = CLI_CT_CHAR;
                    }
            }

            if (is_print) {
                Cli_Input_Thread_Args.Cli_Input_Queue_Add(wParam, ct, s);
            }

        }
            break;

        default:
            return hwndEdit_WndProc_Org(hwnd, message, wParam, lParam);
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

            // Set new WndProc
            {
                hwndEdit_WndProc_Org = (fpWndProc *) GetWindowLongPtr(hwndEdit, GWLP_WNDPROC);
                hwndEdit_WndProc_Org = (fpWndProc *) SetWindowLongPtr(hwndEdit, GWLP_WNDPROC, (LONG_PTR) hwndEdit_WndProc_New);
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
                    sleep(1);
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
            sleep(1);
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
