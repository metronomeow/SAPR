#include <windows.h>

const wchar_t windowClass[] = L"win32app";
const wchar_t windowTitle[] = L"Win32API - Ïðèìåð îêíà";
int x, y, t, k;

long __stdcall WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

    PAINTSTRUCT ps;
    HDC hdc;

    RECT r;
    GetClientRect(hWnd, &r);

    HPEN pen, old_pen;
    HBRUSH brush, old_brush;
    switch (message) {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);

        TextOut(hdc, 0, 0, L"ÏÊÈÌÑ ðóëèò!", 12);

        brush = CreateSolidBrush(RGB(0, 167, 167));
        old_brush = (HBRUSH)SelectObject(hdc, brush);

        pen = CreatePen(PS_DASHDOTDOT, 1, RGB(167, 167, 0));
        old_pen = (HPEN)SelectObject(hdc, pen);
        Rectangle(hdc, x, y, x + 150, y + 150);

        brush = CreateSolidBrush(RGB(180, 167, 0));
        old_brush = (HBRUSH)SelectObject(hdc, brush);
        pen = CreatePen(PS_SOLID, 3, RGB(250, 10, 0));
        old_pen = (HPEN)SelectObject(hdc, pen);

        Ellipse(hdc, t, k, t + 250, k + 150);

        SelectObject(hdc, old_brush);
        DeleteObject(brush);

        SelectObject(hdc, old_pen);
        DeleteObject(pen);



        /* MoveToEx(hdc, 50, 120, NULL);
         LineTo(hdc, 100, 100);
         LineTo(hdc, 150, 100);

         SetPixel(hdc, 200, 200, RGB(160,100,0));*/
        EndPaint(hWnd, &ps);
        break;
    case WM_LBUTTONDOWN:
    {
        x = LOWORD(lParam);
        y = HIWORD(lParam);

        InvalidateRect(hWnd, NULL, true);
        if (x < 250) {
            MessageBox(hWnd, L"Clicked", L"Info", MB_CANCELTRYCONTINUE | MB_ICONQUESTION);
        }

        break;
    }



    case WM_RBUTTONDOWN:
    {
        t = LOWORD(lParam);
        k = HIWORD(lParam);

        InvalidateRect(hWnd, NULL, true);
        /* if (x < 250) {
             MessageBox(hWnd, L"Clicked", L"Info", MB_CANCELTRYCONTINUE | MB_ICONQUESTION);
         }*/

        break;
    }

    case WM_CREATE:
        SetTimer(hWnd, 35, 1000, NULL);
        SetTimer(hWnd, 20, 1000, NULL);

        break;

    case WM_CLOSE:
    {
        int ans = MessageBox(hWnd, L"Close?", L"Hmmm", MB_YESNO);
        if (ans == IDNO)
            return(0);
        KillTimer(hWnd, 35);
        KillTimer(hWnd, 20);
        break;
    }
    case WM_TIMER:
        if (wParam == 35) x += 10;
        else k += 2;
        InvalidateRect(hWnd, NULL, true);
        break;

    }


    return DefWindowProc(hWnd, message, wParam, lParam);
}

int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = windowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

    if (!RegisterClassEx(&wcex)) {
        MessageBox(NULL, L"Can’t register window class!", L"Win32 API Test", NULL);
        return 1;
    }

    HWND hWnd = CreateWindow(windowClass, windowTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 500, 400, NULL, NULL, hInstance, NULL);

    if (!hWnd) {
        MessageBox(NULL, L"Can’t create window!", L"Win32 API Test", NULL);
        return 1;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    MSG msg;

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}

