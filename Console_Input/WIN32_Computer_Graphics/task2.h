#include <windef.h>
#include <wingdi.h>
#include <cmath>
#include "Matrix.h"


class task2 {
    COLORREF insideColor = RGB(0, 0, 255);
    COLORREF outsideColor = RGB(255, 0, 0);
    bool clipping = true;
    int centerX = 0, centerY = 0;
    int r = 0;

    void MySetPixel(HDC hdc, int x, int y) {

        if (clipping && distance(x, y, centerX, centerY) < r)
            SetPixel(hdc, x, y, insideColor);

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

    Vector4 GetHermiteCoefficient(double x0, double s0, double x1, double s1) {
        static double H[16] = {2, 1, -2, 1,
                               -3, -2, 3, -1,
                               0, 1, 0, 0,
                               1, 0, 0, 0};

        static Matrix4 basis(H);
        Vector4 v(x0, s0, x1, s1);
        return basis * v;
    }

    void DrawHermiteCurve(HDC hdc, Vector2 &P0, Vector2 &T0, Vector2 &P1, Vector2 &T1, int numpoints) {
        Vector4 xcoeff = GetHermiteCoefficient(P0.x, T0.x, P1.x, T1.x);
        Vector4 ycoeff = GetHermiteCoefficient(P0.y, T0.y, P1.y, T1.y);
        if (numpoints < 2)return;
        double dt = 1.0 / (numpoints - 1);
        for (double t = 0; t <= 1; t += dt) {
            Vector4 vt;
            vt[3] = 1;
            for (int i = 2; i >= 0; i--)vt[i] = vt[i + 1] * t;
            int x = round(DotProduct(xcoeff, vt));
            int y = round(DotProduct(ycoeff, vt));
            MySetPixel(hdc, x, y);
        }

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
        Vector2 T0(3 * (P1.x - P0.x), 3 * (P1.y - P0.y));
        Vector2 T1(3 * (P3.x - P2.x), 3 * (P3.y - P2.y));
        DrawHermiteCurve(hdc, P0, T0, P3, T1, 200);
    }

};


