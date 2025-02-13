#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) {
    HWND hwnd;
    MSG msg;
    WNDCLASS wndclass;
    static const char *szAppName = "Splitter Example";

    wndclass.style = CS_HREDRAW | CS_VREDRAW;//0; //CS_HREDRAW | CS_VREDRAW;
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

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    HINSTANCE hInst;
    RECT rect;
    static HCURSOR hCursor;
    static BOOL bSplitterMoving;
    static DWORD dwSplitterPos;
    static HWND hWnd1, hWnd2;

    switch (uMsg) {
        case WM_CREATE:
        {
            hInst = ((LPCREATESTRUCT) lParam) -> hInstance;

            hWnd1 = CreateWindowEx(WS_EX_CLIENTEDGE,
                    "edit", NULL,
                    WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | ES_MULTILINE | WS_VSCROLL,
                    0, 0, 0, 0,
                    hWnd, (HMENU) 1,
                    hInst, NULL);

            hWnd2 = CreateWindowEx(WS_EX_CLIENTEDGE,
                    "edit", NULL,
                    WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | ES_MULTILINE | WS_VSCROLL,
                    0, 0, 0, 0,
                    hWnd, (HMENU) 2,
                    hInst, NULL);


            hCursor = LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZENS));
            bSplitterMoving = FALSE;

            dwSplitterPos = 130;
        }
            return 0;

        case WM_SIZE:
        {
            /* 
               If window is shrunk so that splitter now lies outside the 
               window boundaries, move the splitter within the window.
             */
            if ((wParam != SIZE_MINIMIZED) && (HIWORD(lParam) < dwSplitterPos))
                dwSplitterPos = HIWORD(lParam) - 10;

            /* Adjust the children's size and position */
            MoveWindow(hWnd1, 0, 0, LOWORD(lParam), dwSplitterPos - 1, TRUE);
            MoveWindow(hWnd2, 0, dwSplitterPos + 2, LOWORD(lParam), HIWORD(lParam) - dwSplitterPos - 2, TRUE);
        }
            return 0;

        case WM_MOUSEMOVE:
        {
            if (HIWORD(lParam) > 10) // do not allow above this mark
            {
                SetCursor(hCursor);
                if ((wParam == MK_LBUTTON) && bSplitterMoving) {
                    GetClientRect(hWnd, &rect);
                    if (HIWORD(lParam) > rect.bottom)
                        return 0;

                    dwSplitterPos = HIWORD(lParam);
                    SendMessage(hWnd, WM_SIZE, 0, MAKELPARAM(rect.right, rect.bottom));
                }
            }
        }
            return 0;

        case WM_LBUTTONDOWN:
        {
            SetCursor(hCursor);
            bSplitterMoving = TRUE;
            SetCapture(hWnd);
        }
            return 0;

        case WM_LBUTTONUP:
        {
            ReleaseCapture();
            bSplitterMoving = FALSE;
        }
            return 0;

        case WM_DESTROY:
        {
            PostQuitMessage(0);
        }
            return 0;
    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
