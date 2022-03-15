#include <windows.h>
#include <cmath>

const wchar_t windowClass[] = L"win32app";
const wchar_t windowTitle[] = L"Win32API - Пример окна";


class Element {
public:
    int x[6] = { 50, 100, 50, 100, 0, 0 };
    virtual void DrawElem(HDC hdc) = 0;
    virtual void Redraw(HDC hdc) = 0;
    bool V = 0;

};

class Elem1 : public Element {
public:

    void DrawElem(HDC hdc);
    void Redraw(HDC hdc);

};

class Elem2 : public Element {
public:

    void DrawElem(HDC hdc);
    void Redraw(HDC hdc);
    Elem2() {
        x[0] = 150;
    }

};

Elem1 elem1;
Elem2 elem2;

void Elem1::DrawElem(HDC hdc) {

    MoveToEx(hdc, x[0] - 20, x[1] + 10, NULL);
    LineTo(hdc, x[0], x[1] + 10);
    MoveToEx(hdc, x[0] - 20, x[1] + 30, NULL);
    LineTo(hdc, x[0], x[1] + 30);
    Rectangle(hdc, x[0], x[1], x[0] + 30, x[1] + 40);
    MoveToEx(hdc, x[0] + 35, x[1] + 10, NULL);
    LineTo(hdc, x[0] + 45, x[1] + 10);
    Ellipse(hdc, x[0] + 25, x[1] + 5, x[0] + 35, x[1] + 15);
    TextOut(hdc, x[0] + 15, x[1] + 3, L"&", 1);
    TextOut(hdc, x[0] - 2, x[1] - 20, L"NAND2", 5);
}

void Elem2::DrawElem(HDC hdc) {
    MoveToEx(hdc, x[0] - 20, x[1] + 10, NULL);
    LineTo(hdc, x[0], x[1] + 10);
    MoveToEx(hdc, x[0] - 20, x[1] + 30, NULL);
    LineTo(hdc, x[0], x[1] + 30);
    Rectangle(hdc, x[0], x[1], x[0] + 30, x[1] + 40);
    MoveToEx(hdc, x[0] + 30, x[1] + 10, NULL);
    LineTo(hdc, x[0] + 45, x[1] + 10);
    TextOut(hdc, x[0] + 15, x[1] + 3, L"1", 1);
    TextOut(hdc, x[0] - 2, x[1] - 20, L"OR2", 3);
}

void Elem1::Redraw(HDC hdc) {
    HPEN pen, old_pen;
    pen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
    old_pen = (HPEN)SelectObject(hdc, pen);

    MoveToEx(hdc, x[0] - 20, x[1] + 10, NULL);
    LineTo(hdc, x[0], x[1] + 10);
    MoveToEx(hdc, x[0] - 20, x[1] + 30, NULL);
    LineTo(hdc, x[0], x[1] + 30);
    Rectangle(hdc, x[0], x[1], x[0] + 30, x[1] + 40);
    MoveToEx(hdc, x[0] + 35, x[1] + 10, NULL);
    LineTo(hdc, x[0] + 45, x[1] + 10);
    Ellipse(hdc, x[0] + 25, x[1] + 5, x[0] + 35, x[1] + 15);
    TextOut(hdc, x[0] + 15, x[1] + 3, L"&", 1);
    TextOut(hdc, x[0] - 2, x[1] - 20, L"NAND2", 5);

    SelectObject(hdc, old_pen);
    DeleteObject(pen);
}

void Elem2::Redraw(HDC hdc) {
    HPEN pen, old_pen;
    pen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
    old_pen = (HPEN)SelectObject(hdc, pen);

    MoveToEx(hdc, x[0] - 20, x[1] + 10, NULL);
    LineTo(hdc, x[0], x[1] + 10);
    MoveToEx(hdc, x[0] - 20, x[1] + 30, NULL);
    LineTo(hdc, x[0], x[1] + 30);
    Rectangle(hdc, x[0], x[1], x[0] + 30, x[1] + 40);
    MoveToEx(hdc, x[0] + 30, x[1] + 10, NULL);
    LineTo(hdc, x[0] + 45, x[1] + 10);
    TextOut(hdc, x[0] + 15, x[1] + 3, L"1", 1);
    TextOut(hdc, x[0] - 2, x[1] - 20, L"OR2", 3);

    SelectObject(hdc, old_pen);
    DeleteObject(pen);
}

struct Plot {
public:
    bool Esc = 0;
    void DrawPlot(HDC hdc, RECT rect);
    void DrawPlot1(HDC hdc, RECT rect);


};

Plot plot;

void DrawGrid(HDC hdc, RECT rect) {
    for (int j = 0; j < rect.bottom; j += 20) {
        for (int i = 0; i < rect.right; i += 20) {
            SetPixel(hdc, i, j, RGB(150, 150, 150));
        }
    }
}



void Plot::DrawPlot(HDC hdc, RECT rect) {
    int A = rect.right / 3;
    int B = rect.bottom - rect.bottom / 3;

    Rectangle(hdc, 0, B, A, rect.bottom);


    int xs, ys;
    double X = 0, Y;
    double K1, K2;

    K1 = rect.right / (12 * 3.1415);
    K2 = rect.bottom / 6;

    for (X; X < 4 * 3.1415; X += 0.01) {
        Y = -cos(X);
        xs = K1 * X;
        ys = K2 * Y + rect.bottom * 5 / 6;
        SetPixel(hdc, xs, ys, RGB(250, 0, 0));

    }
}
void Plot::DrawPlot1(HDC hdc, RECT rect) {
    int A = rect.right / 3;
    int B = rect.bottom - rect.bottom / 3;
    Rectangle(hdc, 0, B, A, rect.bottom);


    int xs, ys;
    double X = 0, Y;
    double K1, K2;

    K1 = rect.right / 3;
    K2 = rect.bottom / 6;

    for (X; X < 1; X += 0.001) {
        Y = -exp(X);
        xs = K1 * X;
        ys = K2 * Y + rect.bottom * 7 / 6;
        SetPixel(hdc, xs, ys, RGB(250, 0, 0));

    }
}

long __stdcall WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

    RECT rect;
    GetClientRect(hWnd, &rect);

    PAINTSTRUCT ps;
    HDC hdc;
    HBRUSH brush, old_brush;
    RECT r;
    GetClientRect(hWnd, &r);

    switch (message) {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        //brush = CreateSolidBrush(RGB(0, 0, 0));
       // old_brush = (HBRUSH)SelectObject(hdc, brush);
        Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);

        TextOut(hdc, 0, 0, L"ЛКМ - перем 1 эл", 16);
        TextOut(hdc, 0, 15, L"ПКМ+шифт - перем 2 эл", 21);
        TextOut(hdc, 0, 30, L"ЛКМ+ктрл зажать - выдел", 23);

        elem1.DrawElem(hdc);
        elem2.DrawElem(hdc);
        DrawGrid(hdc, rect); // в этой функции рисуется сетка        
        if (plot.Esc)
            plot.DrawPlot1(hdc, rect);
        else plot.DrawPlot(hdc, rect); // в этой функции рисуется график

        if (elem1.x[3]<elem1.x[1] && elem1.x[2]<elem1.x[0]
            && elem1.x[4]>elem1.x[0] + 30 && elem1.x[5] > elem1.x[1] + 40) {
            elem1.Redraw(hdc);
            elem1.x[3] = 0;
            elem1.x[2] = 0;
            elem1.x[4] = 0;
            elem1.x[5] = 0;
            elem1.V = 1;
        }

        if (elem2.x[3]<elem2.x[1] && elem2.x[2]<elem2.x[0]
            && elem2.x[4]>elem2.x[0] + 30 && elem2.x[5] > elem2.x[1] + 40) {
            elem2.Redraw(hdc);
            elem2.x[3] = 0;
            elem2.x[2] = 0;
            elem2.x[4] = 0;
            elem2.x[5] = 0;
            elem2.V = 1;
        }


        EndPaint(hWnd, &ps);
        break;
    case WM_LBUTTONDOWN:
    {
        if (wParam & MK_CONTROL) {
            elem1.x[2] = LOWORD(lParam);
            elem1.x[3] = HIWORD(lParam);
            elem2.x[2] = LOWORD(lParam);
            elem2.x[3] = HIWORD(lParam);
        }
        else {
            elem1.x[0] = LOWORD(lParam);
            elem1.x[1] = HIWORD(lParam);
            if ((elem1.x[0] < rect.right / 3) && (elem1.x[1] > rect.bottom * 2 / 3)) break;
            else
            {
                InvalidateRect(hWnd, NULL, true);
            }
        }
        elem1.V = 0;
        elem2.V = 0;
        break;
    }



    case WM_RBUTTONDOWN:
    {


        if (wParam & MK_SHIFT) {
            elem2.x[1] = HIWORD(lParam);
            elem2.x[0] = LOWORD(lParam);
            if ((elem2.x[0] < rect.right / 3) & (elem2.x[1] > rect.bottom * 2 / 3)) break;
            else
                InvalidateRect(hWnd, NULL, true);
            elem1.V = 0;
            elem2.V = 0;
        }

        if ((elem1.V) && (elem2.V))
        {
            elem1.x[0] = LOWORD(lParam);
            elem1.x[1] = HIWORD(lParam);
            elem2.x[0] = elem1.x[0] + 100;
            elem2.x[1] = elem1.x[1];
            InvalidateRect(hWnd, NULL, true);
            elem1.V = 0;
            elem2.V = 0;
        }
        else  if (elem1.V) {
            elem1.x[0] = LOWORD(lParam);
            elem1.x[1] = HIWORD(lParam);
            InvalidateRect(hWnd, NULL, true);
            elem1.V = 0;
        }
        else if (elem2.V) {
            elem2.x[0] = LOWORD(lParam);
            elem2.x[1] = HIWORD(lParam);
            InvalidateRect(hWnd, NULL, true);
            elem2.V = 0;
        }


        break;
    }

    case WM_LBUTTONUP:
    {
        if (wParam & MK_CONTROL) {
            elem1.x[4] = LOWORD(lParam);
            elem1.x[5] = HIWORD(lParam);
            elem2.x[4] = LOWORD(lParam);
            elem2.x[5] = HIWORD(lParam);
            InvalidateRect(hWnd, NULL, true);
        }

    }

    case WM_KEYDOWN:
    {
        if (wParam == VK_ESCAPE)
        {
            if (plot.Esc == 0) plot.Esc = 1;
            else plot.Esc = 0;
            InvalidateRect(hWnd, NULL, true);
        }
    }

    case WM_CLOSE:
    {

        break;
    }

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
        MessageBox(NULL, L"Can’x[0] register window class!", L"Win32 API Test", NULL);
        return 1;
    }

    HWND hWnd = CreateWindow(windowClass, windowTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 500, 400, NULL, NULL, hInstance, NULL);

    if (!hWnd) {
        MessageBox(NULL, L"Can’x[0] create window!", L"Win32 API Test", NULL);
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

