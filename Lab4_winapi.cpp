#include <windows.h>
#include<iostream>
#include <cmath>
#include<fstream>
#include<vector>
#include<string.h>
#include <algorithm>
#define E 

const wchar_t windowClass[] = L" ";
const wchar_t windowTitle[] = L" ";
HBRUSH brush, old_brush;
HPEN pen, old_pen;
OPENFILENAME ofn;

class Trace {
public:
    std::vector <double> X;
    std::vector <double> Y1;
    std::vector <double> Y2;
    std::string Name1;
    std::string Name2;

};
Trace t;
class FileData {
public:
    std::vector<Trace*> traces;
    bool readfile(HWND hWnd);
    bool DrawWin(HDC hdc, RECT rect);
};
FileData filedata;
bool FileData::DrawWin(HDC hdc, RECT rect) {
    brush = CreateSolidBrush(RGB(50, 50, 50));
    old_brush = (HBRUSH)SelectObject(hdc, brush);
    Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
    DeleteObject(old_brush);
    DeleteObject(brush);
    brush = CreateSolidBrush(RGB(0, 0, 0));
    old_brush = (HBRUSH)SelectObject(hdc, brush);
    Rectangle(hdc, rect.left + 100, rect.top, rect.right, rect.bottom - 30);
    pen = CreatePen(PS_SOLID, 1, RGB(90, 90, 90));
    old_pen = (HPEN)SelectObject(hdc, pen);
    int k = (int)((rect.right - 100) / 10);
    for (int i = rect.left + 100; i < 100 + k * 10; i = i + k) {
        MoveToEx(hdc, i, 0, NULL);
        LineTo(hdc, i, rect.bottom - 30);
    }
    k = (int)((rect.bottom - 30) / 10);
    for (int i = rect.top; i < rect.bottom - 30; i = i + k) {
        MoveToEx(hdc, 100, i, NULL);
        LineTo(hdc, rect.right, i);
    }

    DeleteObject(old_brush);
    DeleteObject(brush);
    DeleteObject(old_pen);
    DeleteObject(pen);
    return true;
}

int N;
bool FileData::readfile(HWND hWnd) {
    std::ifstream f;
    f.open(ofn.lpstrFile, std::ios::in);
    if (f.is_open()) {
        f >> N;
        t.X.clear();
        t.Y2.clear();
        t.Y1.clear();
        if (N == 2) {
            f >> t.Name1;
            f >> t.Name2;
            while (!f.eof()) {
                double data = 0;
                f >> data;
                t.X.push_back(data);
                f >> data;
                t.Y1.push_back(data);
                f >> data;
                t.Y2.push_back(data);
            }
        }
        if (N == 1) {
            f >> t.Name1;
            while (!f.eof()) {
                double data = 0;
                f >> data;
                t.X.push_back(data);
                f >> data;
                t.Y1.push_back(data);
            }
        }
    }
    else {
        MessageBox(hWnd, L"Error", L"File not founded", MB_OK);
    }
    f.close();
    return true;
}

struct Plot {
public:
    void DrawPlot(HDC hdc, RECT rect);

};

Plot plot;
double Max = 0;
double fmax(std::vector<double> x) {
    Max = 0;
    std::for_each(x.begin(), x.end() - 1, [](double x) {if (x > Max) Max = x; });
    return(Max);
}
double Min;
double fmin(std::vector<double> x) {
    Min = 1000;
    std::for_each(x.begin(), x.end() - 1, [](double x) {if (x < Min) Min = x; });
    return(Min);
}

void DrawPoints(HDC hdc, double K1, double K2, RECT rect, std::vector<double> Y) {

    std::vector<double>::const_iterator it, it2;
    int i = 0;
    int xs, ys;
    it2 = Y.begin();
    it = t.X.begin();

    while (it2 != Y.end() - 1 || it != t.X.end() - 1) {
        if (i % 15 == 0 || it == t.X.end() - 2) {
            xs = (*it) * K1;
            ys = (rect.bottom - 30) - (*it2) * K2;
            MoveToEx(hdc, xs + 100, ys + K2 * fmin(Y) - 5, NULL);
            LineTo(hdc, xs + 100, ys + +K2 * fmin(Y) + 5);
            MoveToEx(hdc, xs + 100 - 5, ys + K2 * fmin(Y), NULL);
            LineTo(hdc, xs + 100 + 5, ys + +K2 * fmin(Y));

        }
        i++; it++; it2++;
    }

}

void Text(HDC hdc, RECT rect) {
    TextOut(hdc, 10, 10, L"YEY", 3);
    //FillRect(hdc, &rect, GetStockObject(GRAY_BRUSH));
}

void Plot::DrawPlot(HDC hdc, RECT rect) {
    int xs, ys;
    pen = CreatePen(PS_SOLID, 1, RGB(250, 250, 0));
    old_pen = (HPEN)SelectObject(hdc, pen);
    std::vector<double>::const_iterator it, it2, it3; // Ó·˙ˇ‚ÎˇÂÏ ËÚÂ‡ÚÓ 
    double K1 = 0, K2 = 0, K3 = 0;
    double r1, r2, r3 = 0;

    if (!t.X.empty() && !t.Y1.empty()) {
        SetTextColor(hdc, RGB(250, 250, 250));
        SetBkMode(hdc, RGB(0, 0, 0));
        std::wstring stemp = std::wstring(t.Name1.begin(), t.Name1.end());
        LPCWSTR sw = stemp.c_str();
        TextOut(hdc, 15, rect.bottom - 20, sw, t.Name1.length());

        it3 = t.Y2.begin();
        it2 = t.Y1.begin();
        it = t.X.begin();
        r1 = ((fmax(t.X)) - fmin(t.X));
        r2 = ((fmax(t.Y1)) - fmin(t.Y1));
        if (N == 2) {
            r3 = ((fmax(t.Y2)) - fmin(t.Y2));
            K3 = (rect.bottom - 30) / r3;
        }
        K1 = (rect.right - 100) / r1;
        K2 = (rect.bottom - rect.top - 30) / r2;

        DrawPoints(hdc, K1, K2, rect, t.Y1);

        while (it2 != t.Y1.end() - 2 || it != t.X.end() - 2) {
            xs = (*it) * K1;
            ys = r2 > r3 ? (r2 - (*it2)) * K2 : (r3 - (*it2)) * K3;
            MoveToEx(hdc, xs + 100 - K1 * fmin(t.X), ys + K2 * fmin(t.Y1), NULL);
            ++it;
            ++it2;
            xs = (*it) * K1;
            if (r2 > r3)
                ys = (r2 - (*it2)) * K2;
            else ys = (r3 - (*it2)) * K3;
            LineTo(hdc, xs + 100 - K1 * fmin(t.X), ys + K2 * fmin(t.Y1));
        }

        wchar_t buf[100];
        double W = fmin(t.X);
#ifdef E
        for (int i = 0; i <= 10; i++) {
            swprintf_s(buf, L"%8.2E", W);
            TextOut(hdc, 80 + i * (rect.right - 100) / 10, rect.bottom - 20, (LPCWSTR)buf, 8);
            W = (fmax(t.X) - fmin(t.X)) / 10 + W;
        }
#endif
#ifndef E
        for (int i = 0; i <= 10; i++) {
            swprintf_s(buf, L"%lf", W);
            TextOut(hdc, 80 + i * (rect.right - 100) / 10, rect.bottom - 20, (LPCWSTR)buf, 4);
            W = (fmax(t.X) - fmin(t.X)) / 10 + W;
        }
#endif

        W = fmin(t.X);
        for (int i = 0; i <= 10; i++) {
            swprintf_s(buf, L"%lf", W);
            TextOut(hdc, 60, rect.bottom - 30 - i * (rect.bottom - 30) / 10, (LPCWSTR)buf, 4);
            if (r2 > r3) W = fmax(t.Y1) / 10 + W;
            else W = (fmax(t.Y2) - fmin(t.Y2)) / 10 + W;
        }

        if (N == 2) {
            stemp = std::wstring(t.Name2.begin(), t.Name2.end());
            sw = stemp.c_str();
            TextOut(hdc, 50, rect.bottom - 20, sw, t.Name2.length());
            pen = CreatePen(PS_SOLID, 1, RGB(0, 250, 0));
            old_pen = (HPEN)SelectObject(hdc, pen);
            DrawPoints(hdc, K1, K2, rect, t.Y2);
            it = t.X.begin();
            while (it3 != t.Y2.end() - 2 || it != t.X.end() - 2) {
                xs = (*it) * K1;
                ys = r2 > r3 ? (rect.bottom - 30) - (*it3) * K2 : (rect.bottom - 30) - (*it3) * K3;
                MoveToEx(hdc, xs + 100, ys + K2 * fmin(t.Y2), NULL);
                ++it;
                ++it3;
                xs = (*it) * K1;
                ys = r2 > r3 ? (rect.bottom - 30) - (*it3) * K2 : ys = (rect.bottom - 30) - (*it3) * K3;
                LineTo(hdc, xs + 100, ys + +K2 * fmin(t.Y2));
            }
        }
    }
    DeleteObject(pen);
    DeleteObject(old_pen);
}



long __stdcall WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

    RECT rect;
    GetClientRect(hWnd, &rect);

    PAINTSTRUCT ps;
    HDC hdc;

    RECT r;
    GetClientRect(hWnd, &r);

    switch (message) {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        filedata.DrawWin(hdc, rect);
        plot.DrawPlot(hdc, rect);



        EndPaint(hWnd, &ps);
        break;
    case WM_LBUTTONDOWN:
    {

        break;
    }



    case WM_RBUTTONDOWN:
    {


        break;
    }

    case WM_LBUTTONUP:
    {


    }

    case WM_KEYDOWN:
        if (wParam == VK_INSERT) {

            wchar_t szFileName[MAX_PATH] = L"";
            ZeroMemory(&ofn, sizeof(ofn));
            ofn.lStructSize = sizeof(ofn);
            ofn.hwndOwner = hWnd;
            ofn.lpstrFilter = L"Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";
            ofn.lpstrFile = szFileName;
            ofn.nMaxFile = MAX_PATH;
            ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
            ofn.lpstrDefExt = L"txt";
            if (GetOpenFileName(&ofn))
                MessageBox(hWnd, ofn.lpstrFile, L"»Ïˇ Ù‡ÈÎ‡", MB_OK);
            filedata.readfile(hWnd);
            InvalidateRect(hWnd, NULL, true);
        }

        if (wParam == VK_SPACE) {
            message = WM_CLOSE;
        }

        break;



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
        MessageBox(NULL, L"Caníx[0] register window class!", L"Win32 API Test", NULL);
        return 1;
    }

    HWND hWnd = CreateWindow(windowClass, windowTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 500, 400, NULL, NULL, hInstance, NULL);

    if (!hWnd) {
        MessageBox(NULL, L"Caníx[0] create window!", L"Win32 API Test", NULL);
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
