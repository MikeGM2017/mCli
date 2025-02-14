
#include <sstream>

using namespace std;

#include <windows.h>
#include <winuser.h>

#define ID_HELP   150
#define ID_TEXT   200

void AppendText(const HWND &hwndEdit, const TCHAR *newText) {
    int len_prev = GetWindowTextLength(hwndEdit);
    int buf_size = len_prev + strlen(newText) + 1 + 1024;
    char *buf = new char[buf_size];
    int res_gettext = GetWindowText(hwndEdit, buf, buf_size - 1);
    int pos = res_gettext;
    if (!len_prev) {
        pos += sprintf(buf + pos, "%s", newText);
    } else {
        pos += sprintf(buf + pos, "\n%s", newText);
    }
    SendMessage(hwndEdit, WM_SETTEXT, 0, (LPARAM) buf);
    SendMessage(hwndEdit, EM_SETSEL, 0, -1); //Select all
    SendMessage(hwndEdit, EM_SETSEL, -1, -1); //Unselect and stay at the end pos
    delete[] buf;
}

typedef LRESULT CALLBACK fpWndProc(HWND hwnd, // window handle
        UINT message, // type of message
        WPARAM wParam, // additional information
        LPARAM lParam);

static HWND hwndEdit;
static fpWndProc *hwndEdit_WndProc_Org;
static bool Is_Ctrl = false;

LRESULT CALLBACK hwndEdit_WndProc_New(HWND hwnd, // window handle
        UINT message, // type of message
        WPARAM wParam, // additional information
        LPARAM lParam) // additional information
{
    switch (message) {
        case WM_KEYDOWN:
        {
            char buf[1024];
            const char *s = "";
            bool is_print = true;
            switch (wParam) {
                case VK_CONTROL:
                    //s = "CTRL";
                    Is_Ctrl = true;
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
                    if (Is_Ctrl) {
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
                sprintf(buf, " WM_KEYDOWN: 0x%02X %s", wParam, s);
                AppendText(hwndEdit, buf);
            }
        }
            break;

        case WM_KEYUP:
        {
            char buf[1024];
            const char *s = "";
            bool is_print = true;
            switch (wParam) {
                case VK_CONTROL:
                    //s = "CTRL";
                    Is_Ctrl = false;
                    is_print = false;
                    break;
                default:
                    is_print = false;
                    break;
            }
            if (is_print) {
                sprintf(buf, "   WM_KEYUP: 0x%02X %s", wParam, s);
                AppendText(hwndEdit, buf);
            }
        }
            break;

        case WM_CHAR:
        {
            char buf[1024];
            char s_buf[] = "12";
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
                default:
                    s_buf[0] = wParam;
                    s_buf[1] = '\0';
            }
            sprintf(buf, "         WM_CHAR: 0x%02X %s", wParam, s);
            AppendText(hwndEdit, buf);
        }
            break;
        default:
            return hwndEdit_WndProc_Org(hwnd, message, wParam, lParam);
    }

    return 0;
}

LPWORD lpwAlign(LPWORD lpIn) {
    //ULONG ul;
    unsigned long long int ul;

    ul = (unsigned long long int) lpIn;
    ul += 3;
    ul >>= 2;
    ul <<= 2;
    return (LPWORD) ul;
}

LRESULT CALLBACK DialogProc(HWND hDlg, UINT Msg, WPARAM wParam, LPARAM lParam) {
    //	std::string* pPass = NULL;
    //
    if (Msg == WM_INITDIALOG) {
        SetWindowLongPtr(hDlg, GWLP_USERDATA, lParam);
    }
    //        else {
    //		pPass = reinterpret_cast<std::string*>(GetWindowLong(hDlg, GWL_USERDATA));
    //	}

    switch (Msg) {
        case WM_COMMAND:
        {
            switch (LOWORD(wParam)) {
                case IDOK:
                    EndDialog(hDlg, IDOK);
                    return 1;
            }
            break;
        }
            break;
        case WM_CLOSE:
            EndDialog(hDlg, IDCANCEL);
            return 1;
    }

    return 0;
}

LRESULT DisplayMyMessage(HINSTANCE hinst, HWND hwndOwner, LPSTR lpszMessage) {
    HGLOBAL hgbl;
    LPDLGTEMPLATE lpdt;
    LPDLGITEMTEMPLATE lpdit;
    LPWORD lpw;
    LPWSTR lpwsz;
    LRESULT ret;
    int nchar;

    hgbl = GlobalAlloc(GMEM_ZEROINIT, 1024);
    if (!hgbl)
        return -1;

    lpdt = (LPDLGTEMPLATE) GlobalLock(hgbl);

    // Define a dialog box.

    lpdt->style = WS_POPUP | WS_BORDER | WS_SYSMENU
            | DS_MODALFRAME | WS_CAPTION;
    lpdt->dwExtendedStyle = 0; // added by codeguru (olivthill)
    lpdt->cdit = 3; // number of controls
    lpdt->x = 10;
    lpdt->y = 10;
    lpdt->cx = 100;
    lpdt->cy = 100;

    lpw = (LPWORD) (lpdt + 1);
    *lpw++ = 0; // no menu
    *lpw++ = 0; // predefined dialog box class (by default)

    lpwsz = (LPWSTR) lpw;
    nchar = 1 + MultiByteToWideChar(CP_ACP, 0, "My Dialog",
            -1, lpwsz, 50);
    lpw += nchar;

    //-----------------------
    // Define an OK button.
    //-----------------------
    lpw = lpwAlign(lpw); // align DLGITEMTEMPLATE on DWORD boundary
    lpdit = (LPDLGITEMTEMPLATE) lpw;
    lpdit->x = 10;
    lpdit->y = 70;
    lpdit->cx = 80;
    lpdit->cy = 20;
    lpdit->id = IDOK; // OK button identifier
    lpdit->style = WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON;

    lpw = (LPWORD) (lpdit + 1);
    *lpw++ = 0xFFFF;
    *lpw++ = 0x0080; // button class

    lpwsz = (LPWSTR) lpw;
    nchar = 1 + MultiByteToWideChar(CP_ACP, 0, "OK", -1, lpwsz, 50);
    lpw += nchar;
    // commented by codeguru (olivthill)   lpw = lpwAlign (lpw); // align creation data on DWORD boundary
    *lpw++ = 0; // no creation data

    //-----------------------
    // Define a Help button.
    //-----------------------
    lpw = lpwAlign(lpw); // align DLGITEMTEMPLATE on DWORD boundary
    lpdit = (LPDLGITEMTEMPLATE) lpw;
    lpdit->x = 55;
    lpdit->y = 10;
    lpdit->cx = 40;
    lpdit->cy = 20;
    lpdit->id = ID_HELP; // Help button identifier
    lpdit->style = WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON;

    lpw = (LPWORD) (lpdit + 1);
    *lpw++ = 0xFFFF;
    *lpw++ = 0x0080; // button class atom

    lpwsz = (LPWSTR) lpw;
    nchar = 1 + MultiByteToWideChar(CP_ACP, 0, "Help", -1, lpwsz, 50);
    lpw += nchar;
    // commented by codeguru (olivthill)   lpw = lpwAlign (lpw); // align creation data on DWORD boundary
    *lpw++ = 0; // no creation data

    //-----------------------
    // Define a static text control.
    //-----------------------
    lpw = lpwAlign(lpw); // align DLGITEMTEMPLATE on DWORD boundary
    lpdit = (LPDLGITEMTEMPLATE) lpw;
    lpdit->x = 10;
    lpdit->y = 10;
    lpdit->cx = 40;
    lpdit->cy = 40;
    lpdit->id = ID_TEXT; // text identifier
    lpdit->style = WS_CHILD | WS_VISIBLE | SS_LEFT;

    lpw = (LPWORD) (lpdit + 1);
    *lpw++ = 0xFFFF;
    *lpw++ = 0x0082; // static class

    for (lpwsz = (LPWSTR) lpw;
            *lpwsz++ = (WCHAR) * lpszMessage++;
            );
    lpw = (LPWORD) lpwsz;
    lpw = lpwAlign(lpw); // align creation data on DWORD boundary
    *lpw++ = 0; // no creation data

    GlobalUnlock(hgbl);
    ret = DialogBoxIndirect(hinst, (LPDLGTEMPLATE) hgbl, hwndOwner, (DLGPROC) DialogProc);

    LPVOID lpMsgBuf;
    FormatMessage(
            FORMAT_MESSAGE_ALLOCATE_BUFFER |
            FORMAT_MESSAGE_FROM_SYSTEM |
            FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL,
            GetLastError(),
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
            (LPTSTR) & lpMsgBuf,
            0,
            NULL
            );
    // Process any inserts in lpMsgBuf.
    // ...
    // Display the string.
    //MessageBox( NULL, (LPCTSTR)lpMsgBuf, "Error", MB_OK | MB_ICONINFORMATION );
    // Free the buffer.
    LocalFree(lpMsgBuf);

    GlobalFree(hgbl);

    return ret;
}

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
#define IDM_EDIT_SELECT_ALL 20006
#define IDM_EDIT_CLEAR_ALL 20007

#define IDM_HELP_ABOUT 30001
#define IDM_HELP_SITE 30002

LRESULT CALLBACK WndProc(HWND hwnd, // window handle
        UINT message, // type of message
        WPARAM wParam, // additional information
        LPARAM lParam) // additional information
{

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

            // Set new Font
            HFONT hwndEdit_hFont_new = CreateFont(0, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, TEXT("Courier New"));
            SendMessage(hwndEdit, WM_SETFONT, (WPARAM) hwndEdit_hFont_new, 0);

            // Set new WndProc
            hwndEdit_WndProc_Org = (fpWndProc *) GetWindowLongPtr(hwndEdit, GWLP_WNDPROC);
            hwndEdit_WndProc_Org = (fpWndProc *) SetWindowLongPtr(hwndEdit, GWLP_WNDPROC, (LONG_PTR) hwndEdit_WndProc_New);

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
                AppendMenu(hEdit, MF_SEPARATOR, 0, 0);
                AppendMenu(hEdit, MF_ENABLED | MF_STRING, IDM_EDIT_SELECT_ALL, "Select All");
                AppendMenu(hEdit, MF_SEPARATOR, 0, 0);
                AppendMenu(hEdit, MF_ENABLED | MF_STRING, IDM_EDIT_CLEAR_ALL, "Clear All");

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

                case IDM_EDIT_SELECT_ALL:
                    SendMessage(hwndEdit, EM_SETSEL, 0, -1); //Select all
                    break;

                case IDM_EDIT_CLEAR_ALL:
                    SendMessage(hwndEdit, EM_SETSEL, 0, -1); //Select all
                    SendMessage(hwndEdit, WM_CLEAR, 0, 0);
                    break;

                case IDM_HELP_ABOUT:
                {
                    HINSTANCE hInst = GetModuleHandle(NULL);
                    LRESULT res_dlg = DisplayMyMessage(hInst, hwnd, (LPSTR) "Cli Output C++ Win32API Test");
                    stringstream s_str;
                    s_str << "Dialog Result: " << res_dlg << endl;
                    SendMessage(hwndEdit, WM_SETTEXT, 0, (LPARAM) s_str.str().c_str());
                }
                    break;
                case IDM_HELP_SITE:
                    ShellExecute(NULL, "Open", "https://npotelecom.ru/", NULL, NULL, SW_SHOWNORMAL);
                    break;

                case IDM_FILE_EXIT:
                    PostQuitMessage(0);
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

    return 0;
}
