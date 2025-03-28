
#include <sstream>

using namespace std;

#include <windows.h>
#include <winuser.h>

#include <stdio.h>

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
        SendMessage(hwndEdit, EM_REPLACESEL, FALSE, (LPARAM) (TEXT("\r\n")));
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

LRESULT CALLBACK hwndEdit_WndProc_New(HWND hwnd, // window handle
        UINT message, // type of message
        WPARAM wParam, // additional information
        LPARAM lParam) // additional information
{

    switch (message) {

        case WM_KEYDOWN:
        {
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
                    break;
                case 0x1A:
                    s = "Ctrl+Z";
                    break;
                case 0xDC:
                    if (GetKeyState(VK_CONTROL) < 0) {
                        s = "Ctrl+BACKSLASH";
                    } else {
                        is_print = false;
                    }
                    break;
                case VK_UP:
                    s = "UP";
                    break;
                case VK_DOWN:
                    s = "DOWN";
                    break;
                case VK_RIGHT:
                    s = "RIGHT";
                    break;
                case VK_LEFT:
                    s = "LEFT";
                    break;
                case VK_DELETE:
                    s = "DELETE";
                    break;
                case VK_HOME:
                    s = "HOME";
                    break;
                case VK_END:
                    s = "END";
                    break;

                default:
                    is_print = false;
                    break;
            }
            if (is_print) {
                snprintf(buf, buf_size, " WM_KEYDOWN: 0x%02X %s", wParam, s);
                string s_tmp = buf;
#ifdef UNICODE
                wstring ws(s_tmp.begin(), s_tmp.end());
                AppendText(hwndEdit, ws.c_str());
#else
                AppendText(hwndEdit, s_tmp.c_str());
#endif
            }
        }
            break;

        case WM_CHAR:
        {
            const int buf_size = 1024;
            char buf[buf_size];
            char s_buf[] = "12"; // Dummy value
            const char *s = s_buf;
            switch (wParam) {
                case VK_RETURN:
                    s = "ENTER";
                    break;
                case VK_TAB:
                    s = "TAB";
                    break;
                case VK_BACK:
                    s = "BACK";
                    break;
                case VK_CANCEL:
                    s = "Ctrl+C";
                    break;
                case 0x1A:
                    s = "Ctrl+Z";
                    break;
                case 0x0A:
                    s = "\"\\r\"";
                    break;
                case 0x1B:
                    s = "ESC";
                    break;
                default:
                    s_buf[0] = wParam;
                    s_buf[1] = '\0';
            }
            if (s_buf[0] >= 0x20) {
                snprintf(buf, buf_size, "         WM_CHAR: 0x%02X %s", wParam, s);
            } else {
                snprintf(buf, buf_size, "         WM_CHAR: 0x%02X", wParam);
            }
            string s_tmp = buf;
#ifdef UNICODE
            wstring ws(s_tmp.begin(), s_tmp.end());
            AppendText(hwndEdit, ws.c_str());
#else
            AppendText(hwndEdit, s_tmp.c_str());
#endif
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
    TCHAR szAppName[] = TEXT("Cli Input Test Key Codes CPP Win32API");

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
