#pragma once

#include "vectors.h"
#include "physics.h"

const int SizeX = 1200;
const int SizeY = 1000;

const double XY_Scale  = 2*1e6;
      double VecScale  =   1e7;


int XToPixels (double x);
int YToPixels (double y);

double XToKMs (double x);
double YToKMs (double y);

void Draw (MassPoint point, COLORREF color);
void Circle (Vector pos, double radius, COLORREF color);
void Circle_3D (double x, double y, double radius, COLORREF color);

void Line (Vector p1, Vector p2, COLORREF color, int width);
void Draw (Vector Vector_, Vector Base, COLORREF color, int width);

void FreezingSystem (void);

// #==============================================================================# //

int XToPixels (double x) { return (int) round  (x/XY_Scale) + SizeX/2; }

int YToPixels (double y) { return (int) round (-y/XY_Scale) + SizeY/2; }

double XToKMs (double x) { return  (x - SizeX/2) * XY_Scale; }

double YToKMs (double y) { return (-y + SizeY/2) * XY_Scale; }

void Draw (MassPoint point, COLORREF color)
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

void Circle (Vector pos, double radius, COLORREF color)
{
    Circle_3D ( XToPixels (pos.x) , YToPixels (pos.y) , radius, color );
}

void Line (Vector p1, Vector p2, COLORREF color, int width)
{
    txSetColor (color, width);

    txLine ( XToPixels (p1.x), YToPixels (p1.y), XToPixels (p2.x), YToPixels (p2.y) );
}

void Draw (Vector Vector_, Vector Base, COLORREF color, int width)
{
    Vector_ = Mul (Vector_, VecScale);

    txSetColor (color);
    Line (Base, Base + Vector_, color, width);

    Vector arr = Vector_/10;
    Vector norm1 = Vector {  arr.y, -arr.x },
           norm2 = Vector { -arr.y,  arr.x };

    Line (Base + Vector_, Base + Vector_ + (norm1 - arr), color, width);
    Line (Base + Vector_, Base + Vector_ + (norm2 - arr), color, width);
}

void FreezingSystem (void)
{
    if (GetKeyState (VK_CAPITAL))
        {
            txSetFillColor (TX_BLACK);
            txClear();
        }
}
