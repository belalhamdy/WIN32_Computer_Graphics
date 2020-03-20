#include <windef.h>
#include <wingdi.h>
#include <cmath>

double distance(int x1, int y1, int x2, int y2)
{
    // Calculating distance
    return sqrt(pow(x2 - x1, 2) +
                pow(y2 - y1, 2) * 1.0);
}
void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void DrawLine(HDC hdc, int x1, int y1, int x2, int y2, COLORREF color) {
    int dx, dy, d, yInc, change1, change2;
    bool rotate = false;
    dx = abs(x1 - x2);
    dy = abs(y1 - y2);
    if (dy > dx) {
        swap(&x1, &y1);
        swap(&x2, &y2);
        swap(&dx, &dy);
        rotate = true;
    }
    if (x1 > x2) {
        swap(&x1, &x2);
        swap(&y1, &y2);
    }
    if (y1 > y2)
        yInc = -1;
    else
        yInc = 1;
    d = 2 * dy - dx;
    change1 = 2 * dy;
    change2 = 2 * (dy - dx);
    while (x1 <= x2) {
        if (rotate)
            SetPixel(hdc, y1, x1, color);
        else
            SetPixel(hdc, x1, y1, color);
        if (d <= 0)
            d += change1;
        else {
            d += change2;
            y1 += yInc;
        }
        ++x1;
    }

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

