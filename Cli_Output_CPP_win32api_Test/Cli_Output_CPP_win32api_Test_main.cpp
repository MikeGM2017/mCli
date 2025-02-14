#include <windows.h>

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

LRESULT CALLBACK WndProc(HWND hwnd, // window handle
        UINT message, // type of message
        WPARAM wParam, // additional information
        LPARAM lParam) // additional information
{
    static HWND hwndEdit;

    //    TCHAR lpszLatin[] =  L"Lorem ipsum dolor sit amet, consectetur "
    //                         L"adipisicing elit, sed do eiusmod tempor "
    //                         L"incididunt ut labore et dolore magna "
    //                         L"aliqua. Ut enim ad minim veniam, quis "
    //                         L"nostrud exercitation ullamco laboris nisi "
    //                         L"ut aliquip ex ea commodo consequat. Duis "
    //                         L"aute irure dolor in reprehenderit in "
    //                         L"voluptate velit esse cillum dolore eu "
    //                         L"fugiat nulla pariatur. Excepteur sint "
    //                         L"occaecat cupidatat non proident, sunt "
    //                         L"in culpa qui officia deserunt mollit "
    //                         L"anim id est laborum.";

    switch (message) {
        case WM_CREATE:
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
            //            SendMessage(hwndEdit, WM_SETTEXT, 0, (LPARAM) lpszLatin);

            return 0;

        case WM_COMMAND:
            switch (wParam) {
                    //                case IDM_EDUNDO:
                    //                    // Send WM_UNDO only if there is something to be undone.
                    //
                    //                    if (SendMessage(hwndEdit, EM_CANUNDO, 0, 0))
                    //                        SendMessage(hwndEdit, WM_UNDO, 0, 0);
                    //                    else {
                    //                        MessageBox(hwndEdit,
                    //                                L"Nothing to undo.",
                    //                                L"Undo notification",
                    //                                MB_OK);
                    //                    }
                    //                    break;
                    //
                    //                case IDM_EDCUT:
                    //                    SendMessage(hwndEdit, WM_CUT, 0, 0);
                    //                    break;
                    //
                    //                case IDM_EDCOPY:
                    //                    SendMessage(hwndEdit, WM_COPY, 0, 0);
                    //                    break;
                    //
                    //                case IDM_EDPASTE:
                    //                    SendMessage(hwndEdit, WM_PASTE, 0, 0);
                    //                    break;
                    //
                    //                case IDM_EDDEL:
                    //                    SendMessage(hwndEdit, WM_CLEAR, 0, 0);
                    //                    break;
                    //
                    //                case IDM_ABOUT:
                    //                    DialogBox(hInst, // current instance
                    //                            L"AboutBox", // resource to use
                    //                            hwnd, // parent handle
                    //                            (DLGPROC) About);
                    //                    break;

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
