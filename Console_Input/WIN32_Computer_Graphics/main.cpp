#include <tchar.h>
#include <windows.h>
#include <iostream>
#include "task2.h"


#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif


/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[] = _T("Ass-2_Task3: CS_1 20170077");


int WINAPI WinMain(HINSTANCE hThisInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpszArgument,
                   int nCmdShow) {
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof(WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx(&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx(
            0,                   /* Extended possibilites for variation */
            szClassName,         /* Classname */
            _T("Ass-2_Task3: CS_1 20170077"),       /* Title Text */
            WS_OVERLAPPEDWINDOW, /* default window */
            CW_USEDEFAULT,       /* Windows decides the position */
            CW_USEDEFAULT,       /* where the window ends up on the screen */
            800,                 /* The programs width */
            500,                 /* and height in pixels */
            HWND_DESKTOP,        /* The window is a child-window to desktop */
            NULL,                /* No menu */
            hThisInstance,       /* Program Instance handler */
            NULL                 /* No Window Creation data */
    );

    /* Make the window visible on the screen */
    ShowWindow(hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage(&messages, NULL, 0, 0)) {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */
const int MAX_INPUT = 10;

int click, clickCPY, clear, c = 4; // set clear = 1 if you want to clear the screen every mouse click
bool takeInput = false,draw = true;
Vector2 input[MAX_INPUT];
task2 t;

void task(HDC hdc) {
    switch (c) {
        case 1:
            t.DrawLine(hdc, input[0], input[1]);
            break;
        case 2:
            t.DrawCircle(hdc, input[0], input[1], false);
            break;
        case 3:
            t.DrawBezierCurve(hdc, input[0], input[1], input[2], input[3]);
            break;
        case 4:
            t.DrawCircle(hdc, input[0], input[1], true);
            break;
    }
}

DWORD WINAPI consoleThread(LPVOID ) {
    click = clickCPY = 2;
    if (!takeInput) {
        printf("Enter Clipping Circle\n");
        takeInput = true;
        return 0;
    }
    printf("1- Line (2 Clicks)\n2- Circle (2 Clicks)\n3- Cubic Curve (4 Clicks)\n4- New Clipping Circle (2 Clicks)\n5- Exit\n\n");
    scanf("%d", &c);
    if (c > 4 || c < 1) exit(0);
    if (c == 3) click = clickCPY = 4;
    draw = true;
    return 0;
}

int main() {
    DWORD myThreadID;
    HANDLE myHandle = CreateThread(0, 0, consoleThread, 0, 0, &myThreadID);
    CloseHandle(myHandle);
    return WinMain(GetModuleHandle(NULL), NULL, NULL, SW_SHOWNORMAL);
}

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    PAINTSTRUCT ps;
    HDC hdc;
    switch (message)                  /* handle the messages */
    {
        case WM_DESTROY:
            PostQuitMessage(0);       /* send a WM_QUIT to the message queue */
            break;
        case WM_LBUTTONDOWN:
            if (!click) click = clickCPY;
            input[clickCPY - click].x = LOWORD(lParam);
            input[clickCPY - click].y = HIWORD(lParam);
            --click;
            InvalidateRect(hwnd, nullptr, clear);
            break;
        case WM_PAINT:
            hdc = BeginPaint(hwnd, &ps);
            if (!click) {
                task(hdc);
            }
            EndPaint(hwnd, &ps);
            if (!click && draw){
                draw = false;
                return main();
            }
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc(hwnd, message, wParam, lParam);
    }

    return 0;
}
