#include <windows.h>
#include "task2.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void AddMenus(HWND);

#define LINE 1
#define CIRCLE 2
#define CUBIC_CURVE 3
#define CLIPPING_CIRCLE 4


HMENU method;


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PWSTR lpCmdLine, int nCmdShow) {

    MSG msg;
    WNDCLASSW wc = {0};
    wc.lpszClassName = L"Ass-2_Task3: CS_1 20170077 - Menu Input";
    wc.hInstance = hInstance;
    wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
    wc.lpfnWndProc = WndProc;
    wc.hCursor = LoadCursor(0, IDC_ARROW);

    RegisterClassW(&wc);
    CreateWindowW(wc.lpszClassName, L"Ass-2_Task3: CS_1 20170077 - Menu Input",
                  WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                  100, 100, 800, 500, 0, 0, hInstance, 0);

    while (GetMessage(&msg, NULL, 0, 0)) {

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int) msg.wParam;
}

const int MAX_INPUT = 10;
int click, clickCPY, c = 4; // set clear = 1 if you want to clear the screen every mouse click
bool takeInput = false;
Vector2 input[MAX_INPUT];
task2 t;

void handleTask(int clicks, int choose) {
    click = clickCPY = clicks;
    c = choose;
}

void task(HDC hdc) {
    switch (c) {
        case LINE:
            t.DrawLine(hdc, input[0], input[1]);
            break;
        case CIRCLE:
            t.DrawCircle(hdc, input[0], input[1], false);
            break;
        case CUBIC_CURVE:
            t.DrawBezierCurve(hdc, input[0], input[1], input[2], input[3]);
            break;
        case CLIPPING_CIRCLE:
            t.DrawCircle(hdc, input[0], input[1], true);
            break;
    }
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    PAINTSTRUCT ps;
    HDC hdc;
    switch (msg) {
        case WM_CREATE:
            AddMenus(hwnd);
            break;
        case WM_COMMAND:
            switch (LOWORD(wParam)) {
                case LINE:
                    CheckMenuRadioItem(method, LINE, CLIPPING_CIRCLE, LINE, MF_BYCOMMAND);
                    handleTask(2, LINE);
                    break;
                case CIRCLE:
                    CheckMenuRadioItem(method, LINE, CLIPPING_CIRCLE, CIRCLE, MF_BYCOMMAND);
                    handleTask(2, CIRCLE);
                    break;
                case CUBIC_CURVE:
                    CheckMenuRadioItem(method, LINE, CLIPPING_CIRCLE, CUBIC_CURVE, MF_BYCOMMAND);
                    handleTask(4, CUBIC_CURVE);
                    break;
                case CLIPPING_CIRCLE:
                    CheckMenuRadioItem(method, LINE, CLIPPING_CIRCLE, CLIPPING_CIRCLE, MF_BYCOMMAND);
                    handleTask(2, CLIPPING_CIRCLE);
                    break;
            }

            break;
        case WM_LBUTTONDOWN:
            if (!click) click = clickCPY;
            input[clickCPY - click].x = LOWORD(lParam);
            input[clickCPY - click].y = HIWORD(lParam);
            --click;
            InvalidateRect(hwnd, nullptr, 0);
            break;
        case WM_PAINT:
            hdc = BeginPaint(hwnd, &ps);
            if (!click) {
                task(hdc);
            }
            EndPaint(hwnd, &ps);
            break;
        case WM_DESTROY:

            PostQuitMessage(0);
            break;
    }

    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

void AddMenus(HWND hwnd) {

    HMENU hMenubar;

    hMenubar = CreateMenu();
    method = CreateMenu();

    AppendMenuW(method, MF_STRING, LINE, L"&Line (2)");
    AppendMenuW(method, MF_STRING, CIRCLE, L"&Circle (2)");
    AppendMenuW(method, MF_STRING, CUBIC_CURVE, L"&Cubic Curve (4)");
    AppendMenuW(method, MF_STRING, CLIPPING_CIRCLE, L"Clipping Circle (2)");

    CheckMenuRadioItem(method, LINE, CLIPPING_CIRCLE, CLIPPING_CIRCLE, MF_BYCOMMAND);
    handleTask(2,CLIPPING_CIRCLE);

    AppendMenuW(hMenubar, MF_POPUP, (UINT_PTR) method, L"&Method");
    SetMenu(hwnd, hMenubar);
}

int main() {
    return wWinMain(GetModuleHandle(NULL), NULL, NULL, SW_SHOWNORMAL);
}