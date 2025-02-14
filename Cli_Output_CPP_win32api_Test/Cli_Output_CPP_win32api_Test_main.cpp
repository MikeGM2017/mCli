#include <windows.h>
#include <winuser.h>

#include "main_resource_def.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) {
    HWND hwnd;
    MSG msg;
    WNDCLASS wndclass;
    static const char *szAppName = "Cli Output CPP Win32API Test";

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

#define ID_EDITCHILD 100

#define IDM_FILE_OPEN 10001
#define IDM_FILE_SAVE 10002
#define IDM_FILE_SAVE_AS 10003
#define IDM_FILE_EXIT 10004

#define IDM_EDIT_UNDO 20001
#define IDM_EDIT_CUT 20002
#define IDM_EDIT_COPY 20003
#define IDM_EDIT_PASTE 20004
#define IDM_EDIT_DELETE 20005

#define IDM_HELP_ABOUT 30001
#define IDM_HELP_SITE 30002

LRESULT CALLBACK WndProc(HWND hwnd, // window handle
        UINT message, // type of message
        WPARAM wParam, // additional information
        LPARAM lParam) // additional information
{
    static HWND hwndEdit;

    TCHAR lpszLatin[] = "Test Text:\n"
            "Lorem ipsum dolor sit amet, consectetur "
            "adipisicing elit, sed do eiusmod tempor "
            "incididunt ut labore et dolore magna "
            "aliqua. Ut enim ad minim veniam, quis "
            "nostrud exercitation ullamco laboris nisi "
            "ut aliquip ex ea commodo consequat. Duis "
            "aute irure dolor in reprehenderit in "
            "voluptate velit esse cillum dolore eu "
            "fugiat nulla pariatur. Excepteur sint "
            "occaecat cupidatat non proident, sunt "
            "in culpa qui officia deserunt mollit "
            "anim id est laborum.";

    switch (message) {
        case WM_CREATE:
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

            // Add text to the window.
            SendMessage(hwndEdit, WM_SETTEXT, 0, (LPARAM) lpszLatin);

            HMENU hMainMenu = CreateMenu();
            HMENU hFile = CreateMenu();
            HMENU hEdit = CreateMenu();
            HMENU hHelp = CreateMenu();

            if (hMainMenu != NULL) {

                BOOL res_file = AppendMenu(hMainMenu, MF_POPUP, (UINT_PTR) hFile, "&File");

                AppendMenu(hFile, MF_ENABLED | MF_STRING, IDM_FILE_OPEN, "&Open...");
                AppendMenu(hFile, MF_SEPARATOR, 0, 0);
                AppendMenu(hFile, MF_ENABLED | MF_STRING, IDM_FILE_SAVE, "&Save");
                AppendMenu(hFile, MF_ENABLED | MF_STRING, IDM_FILE_SAVE_AS, "Save &As...");
                AppendMenu(hFile, MF_SEPARATOR, 0, 0);
                AppendMenu(hFile, MF_ENABLED | MF_STRING, IDM_FILE_EXIT, "E&xit");

                BOOL res_edit = AppendMenu(hMainMenu, MF_POPUP, (UINT_PTR) hEdit, "&Edit");

                AppendMenu(hEdit, MF_ENABLED | MF_STRING, IDM_EDIT_UNDO, "Undo");
                AppendMenu(hEdit, MF_SEPARATOR, 0, 0);
                AppendMenu(hEdit, MF_ENABLED | MF_STRING, IDM_EDIT_CUT, "Cut");
                AppendMenu(hEdit, MF_ENABLED | MF_STRING, IDM_EDIT_COPY, "Copy");
                AppendMenu(hEdit, MF_ENABLED | MF_STRING, IDM_EDIT_PASTE, "Paste");
                AppendMenu(hEdit, MF_ENABLED | MF_STRING, IDM_EDIT_DELETE, "Delete");

                BOOL res_help = AppendMenu(hMainMenu, MF_POPUP, (UINT_PTR) hHelp, "&Help");

                AppendMenu(hHelp, MF_ENABLED | MF_STRING, IDM_HELP_ABOUT, "&About");
                AppendMenu(hHelp, MF_SEPARATOR, 0, 0);
                AppendMenu(hHelp, MF_ENABLED | MF_STRING, IDM_HELP_SITE, "Site...");


                BOOL res_set = SetMenu(hwnd, hMainMenu);

            } else {
                MessageBox(0, "hMainMenu = NULL", "hMainMenu = NULL", MB_ICONEXCLAMATION | MB_OK);
            }

        }

            return 0;

        case WM_COMMAND:
            switch (wParam) {

                case IDM_EDIT_UNDO:
                    // Send WM_UNDO only if there is something to be undone.

                    if (SendMessage(hwndEdit, EM_CANUNDO, 0, 0))
                        SendMessage(hwndEdit, WM_UNDO, 0, 0);
                    else {
                        MessageBox(hwndEdit,
                                "Nothing to undo.",
                                "Undo notification",
                                MB_OK);
                    }
                    break;

                case IDM_EDIT_CUT:
                    SendMessage(hwndEdit, WM_CUT, 0, 0);
                    break;

                case IDM_EDIT_COPY:
                    SendMessage(hwndEdit, WM_COPY, 0, 0);
                    break;

                case IDM_EDIT_PASTE:
                    SendMessage(hwndEdit, WM_PASTE, 0, 0);
                    break;

                case IDM_EDIT_DELETE:
                    SendMessage(hwndEdit, WM_CLEAR, 0, 0);
                    break;

                case IDM_HELP_ABOUT:
                {
                    MessageBox(hwndEdit,
                                "Cli Output C++ Win32API Test",
                                "About",
                                MB_OK);
                }
                    break;
                case IDM_HELP_SITE:
                    ShellExecute(NULL, "Open", "https://npotelecom.ru/", NULL, NULL, SW_SHOWNORMAL);
                    break;

                default:
                    return DefWindowProc(hwnd, message, wParam, lParam);
            }
            break;

        case WM_SETFOCUS:
            SetFocus(hwndEdit);
            return 0;

        case WM_SIZE:
            // Make the edit control the size of the window's client area.

            MoveWindow(hwndEdit,
                    0, 0, // starting x- and y-coordinates
                    LOWORD(lParam), // width of client area
                    HIWORD(lParam), // height of client area
                    TRUE); // repaint window
            return 0;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        default:
            return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return NULL;
}
