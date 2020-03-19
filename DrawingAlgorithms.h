#include <windef.h>
#include <wingdi.h>
#include <cmath>

double distance(int x1, int y1, int x2, int y2)
{
    // Calculating distance
    return sqrt(pow(x2 - x1, 2) +
                pow(y2 - y1, 2) * 1.0);
}

void SetMultiPixel(HDC hdc, int xc, int yc, COLORREF color, int x, int y) {
    SetPixel(hdc, xc + x, yc + y, RGB(255, 255, 0));
    SetPixel(hdc, xc - x, yc + y, RGB(255, 0, 255));
    SetPixel(hdc, xc + x, yc - y, RGB(0, 255, 0));
    SetPixel(hdc, xc - x, yc - y, RGB(0, 255, 255));

    SetPixel(hdc, xc + y, yc + x, RGB(128, 255, 0));
    SetPixel(hdc, xc - y, yc + x, RGB(255, 128, 0));
    SetPixel(hdc, xc + y, yc - x, RGB(128, 128, 0));
    SetPixel(hdc, xc - y, yc - x, RGB(128, 128, 128));
}

void DrawCircle(HDC hdc, int xc, int yc, int R, COLORREF color) {
    int x = R;
    int y = 0;
    SetMultiPixel(hdc, xc, yc, color, x, y);
    int d = 5 - 4 * R;
    while (x > y) {
        if (d > 0) {
            d += -8 * x + 8;
            x--;
        }
        d += 8 * y + 12;
        y++;

        SetMultiPixel(hdc, xc, yc, color, x, y);
    }
}
void DrawCircle(HDC hdc, int x1, int y1, int x2, int y2, COLORREF color) {
    DrawCircle(hdc,x1,y1,int(distance(x1,y1,x2,y2)),color);
}

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void DrawLine(HDC hdc, int x1, int y1, int x2, int y2, COLORREF color) {
    int dx, dy, d, incry, incre, incrne, slopegt1 = 0;
    dx = abs(x1 - x2);
    dy = abs(y1 - y2);
    if (dy > dx) {
        swap(&x1, &y1);
        swap(&x2, &y2);
        swap(&dx, &dy);
        slopegt1 = 1;
    }
    if (x1 > x2) {
        swap(&x1, &x2);
        swap(&y1, &y2);
    }
    if (y1 > y2)
        incry = -1;
    else
        incry = 1;
    d = 2 * dy - dx;
    incre = 2 * dy;
    incrne = 2 * (dy - dx);
    while (x1 < x2) {
        if (d <= 0)
            d += incre;
        else {
            d += incrne;
            y1 += incry;
        }
        x1++;
        if (slopegt1)
            SetPixel(hdc, y1, x1, color);
        else
            SetPixel(hdc, x1, y1, color);
    }

}
