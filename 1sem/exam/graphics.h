#pragma once

#include "vectors.h"
#include "physics.h"

const int SizeX = GetSystemMetrics (SM_CXSCREEN);
const int SizeY = GetSystemMetrics (SM_CYSCREEN);

const double XY_Scale  = 2*1e6;
      double VecScale  = 3.5*1e8;

struct Rect
{
    int x;
    int y;

    int size_x;
    int size_y;

    COLORREF color;

    const char* text;
};

int XToPixels (double x);
int YToPixels (double y);

double XToKMs (double x);
double YToKMs (double y);

void Line (const Vector& p1, const Vector& p2, COLORREF color, int width);
void Circle (const Vector& pos, double radius, COLORREF color);
void Circle_3D (double x, double y, double radius, COLORREF color);

void Draw (const MassPoint& point,   COLORREF color);
void Draw (const Vector&    Vector_, const Vector& Base, COLORREF color, int width);

void StopClear (void);

// #==============================================================================# //

int XToPixels (double x) { return (int) round  (x/XY_Scale) + SizeX/2; }

int YToPixels (double y) { return (int) round (-y/XY_Scale) + SizeY/2; }

double XToKMs (double x) { return  (x - SizeX/2) * XY_Scale; }

double YToKMs (double y) { return (-y + SizeY/2) * XY_Scale; }

void Draw (const MassPoint& point, COLORREF color)
{
    Circle (point.pos, point.r / XY_Scale * 9, color);
}

void Circle_3D (double x, double y, double radius, COLORREF color)
{
    double r = txExtractColor (color, TX_RED)   / 255.0;
    double g = txExtractColor (color, TX_GREEN) / 255.0;
    double b = txExtractColor (color, TX_BLUE)  / 255.0;

    for (double t = 0; t <= 1; t += 0.1)
    {
        double t0 = pow (t + 0.15, 0.3);
        txColor     (r*t0, g*t0, b*t0);
        txFillColor (r*t0, g*t0, b*t0);
        txCircle (x, y, radius * (1 - t));
    }
}

void Circle (const Vector& pos, double radius, COLORREF color)
{
    Circle_3D ( XToPixels (pos.x) , YToPixels (pos.y) , radius, color );
}

void Line (const Vector& p1, const Vector& p2, COLORREF color, int width)
{
    txSetColor (color, width);

    txLine ( XToPixels (p1.x), YToPixels (p1.y), XToPixels (p2.x), YToPixels (p2.y) );
}

void Draw (const Vector& Vector_, const Vector& Base, COLORREF color, int width)
{
    Vector Vec = Mul (Vector_, VecScale);

    txSetColor (color);
    Line (Base, Base + Vec, color, width);

    Vector arr = Vec/10;
    Vector norm1 = Vector {  arr.y, -arr.x },
           norm2 = Vector { -arr.y,  arr.x };

    Line (Base + Vec, Base + Vec + (norm1 - arr), color, width);
    Line (Base + Vec, Base + Vec + (norm2 - arr), color, width);
}

void StopClear (void)
{
    if (!GetKeyState (VK_CAPITAL))
        {
            txSetFillColor (TX_BLACK);
            txClear();
        }
}
