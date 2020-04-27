#include <windef.h>
#include <wingdi.h>
#include <cmath>

struct Vector2 {
    double x, y;

    Vector2(double a = 0, double b = 0) {
        x = a;
        y = b;
    }
};

class task2 {
    COLORREF insideColor = RGB(0, 0, 255);
    COLORREF clippingColor = RGB(0, 128, 128);
    COLORREF outsideColor = RGB(255, 0, 0);
    bool clipping = true;
    int centerX = 0, centerY = 0;
    int r = 0;

    void MySetPixel(HDC hdc, int x, int y) {
        if (!clipping) SetPixel(hdc, x, y, clippingColor);
        else if (distance(x, y, centerX, centerY) < r) SetPixel(hdc, x, y, insideColor);
        else SetPixel(hdc, x, y, outsideColor);

    }

    void SetMultiPixel(HDC hdc, int xc, int yc, int x, int y) {
        MySetPixel(hdc, xc + x, yc + y);
        MySetPixel(hdc, xc - x, yc + y);
        MySetPixel(hdc, xc + x, yc - y);
        MySetPixel(hdc, xc - x, yc - y);

        MySetPixel(hdc, xc + y, yc + x);
        MySetPixel(hdc, xc - y, yc + x);
        MySetPixel(hdc, xc + y, yc - x);
        MySetPixel(hdc, xc - y, yc - x);
    }


    void DrawCircle(HDC hdc, int xc, int yc, int R) {
        int x = R;
        int y = 0;
        SetMultiPixel(hdc, xc, yc, x, y);
        int d = 1 - R;
        while (x > y) {
            if (d > 0) {
                d += -2 * x + 2;
                x--;
            }
            d += 2 * y + 3;
            y++;

            SetMultiPixel(hdc, xc, yc, x, y);
        }
    }

public:
    static double distance(int x1, int y1, int x2, int y2) {
        // Calculating distance
        return sqrt(pow(x2 - x1, 2) +
                    pow(y2 - y1, 2) * 1.0);
    }

    static void swap(int *a, int *b) {
        int t = *a;
        *a = *b;
        *b = t;
    }

    void DrawLine(HDC hdc, Vector2 &P0, Vector2 &P1) {
        int dx, dy, d, yInc, change1, change2;
        int x1 = P0.x, y1 = P0.y, x2 = P1.x, y2 = P1.y;
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
                MySetPixel(hdc, y1, x1);
            else
                MySetPixel(hdc, x1, y1);
            if (d <= 0)
                d += change1;
            else {
                d += change2;
                y1 += yInc;
            }
            ++x1;
        }

    }


    void DrawCircle(HDC hdc, Vector2 &P0, Vector2 &P1, bool clipCircle) {
        int radius = int(distance(P0.x, P0.y, P1.x, P1.y));
        if (clipCircle) {
            clipping = false;
            centerX = P0.x;
            centerY = P0.y;
            r = radius;
        }
        DrawCircle(hdc, P0.x, P0.y, radius);
        clipping = true;
    }


    void DrawBezierCurve(HDC hdc, Vector2 &P0, Vector2 &P1, Vector2 &P2, Vector2 &P3) {

        int x1 = P0.x, y1 = P0.y, x2 = P1.x, y2 = P1.y, x3 = P2.x, y3 = P2.y, x4 = P3.x, y4 = P3.y;

        x2 = 3 * (x2 - x1), y2 = 3 * (y2 - y1), x3 = 3 * (x4 - x3), y3 = 3 * (y4 - y3);

        double dt = 0.0001;
        for (double t = 0; t <= 1; t += dt) {
            int x = x1 + x2 * t + (-3 * x1 - 2 * x2 + 3 * x4 - x3) * t * t + (2 * x1 + x2 - 2 * x4 + x3) * t * t * t;
            int y = y1 + y2 * t + (-3 * y1 - 2 * y2 + 3 * y4 - y3) * t * t + (2 * y1 + y2 - 2 * y4 + y3) * t * t * t;
            MySetPixel(hdc, round(x), round(y));
        }
    }
};


