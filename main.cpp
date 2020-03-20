#include <tchar.h>
#include <windows.h>
#include "DrawingAlgorithms.h"

#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif


/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[] = _T("CodeBlocksWindowsApp");


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
            _T("Task3: CS_1 20170077"),       /* Title Text */
            WS_OVERLAPPEDWINDOW, /* default window */
            CW_USEDEFAULT,       /* Windows decides the position */
            CW_USEDEFAULT,       /* where the window ends up on the screen */
            544,                 /* The programs width */
            375,                 /* and height in pixels */
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
int x[3], y[3], c;

void task(HDC hdc) {
    COLORREF color = RGB(0, 0, 0);
    int r1 = distance(x[0], y[0], x[1], y[1]);
    int r2 = distance(x[0], y[0], x[2], y[2]);
    if (r2 < r1) swap(&r2,&r1);
    DrawCircle(hdc, x[0], y[0], r1, color);
    DrawCircle(hdc, x[0], y[0], r2, color);
    for (int i = r1+1; i < r2; ++i) DrawCircle(hdc, x[0], y[0], i, color);
    DrawLine(hdc, x[0], y[0], x[1], y[1], color);
    DrawLine(hdc, x[0], y[0], x[2], y[2], color);
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
            if (c == 3) c = 0;
            x[c] = LOWORD(lParam);
            y[c] = HIWORD(lParam);
            ++c;
            InvalidateRect(hwnd, 0, TRUE);
            break;
        case WM_PAINT:
            hdc = BeginPaint(hwnd, &ps);
            if (c == 3) {
                task(hdc);
            }
            EndPaint(hwnd, &ps);
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc(hwnd, message, wParam, lParam);
    }

    return 0;
}
