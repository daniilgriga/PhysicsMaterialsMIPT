#pragma once

#include "vectors.h"
#include "physics.h"

const int SizeX = 1200;
const int SizeY = 1000;

const double XY_Scale = 2*1e6;

int XToPixels (double x);
int YToPixels (double y);

double XToKMs (double x);
double YToKMs (double y);

void Draw (MassPoint point, COLORREF color);
void Circle (Vector pos, double radius, COLORREF color);
void Circle_3D (double x, double y, double radius, COLORREF color);

int XToPixels (double x) { return (int) round  (x/XY_Scale) + SizeX/2; }

int YToPixels (double y) { return (int) round (-y/XY_Scale) + SizeY/2; }

double XToKMs (double x) { return  (x - SizeX/2) * XY_Scale; }

double YToKMs (double y) { return (-y + SizeY/2) * XY_Scale; }

void Draw (MassPoint point, COLORREF color)
{
    Circle (point.pos, point.r / XY_Scale * 8, color);
}

void Circle_3D (double x, double y, double radius, COLORREF color)
{
    double r = txExtractColor (color, TX_RED)   / 255.0;
    double g = txExtractColor (color, TX_GREEN) / 255.0;
    double b = txExtractColor (color, TX_BLUE)  / 255.0;

    for (double t = 0; t <= 1; t += 0.1)
    {
        double t0 = pow (t, 0.3);
        txColor (r*t0, g*t0, b*t0);
        txFillColor (r*t0, g*t0, b*t0);
        txCircle (x, y, radius * (1 - t));
    }
}

void Circle (Vector pos, double radius, COLORREF color)
{
    Circle_3D ( XToPixels (pos.x) , YToPixels (pos.y) , radius, color );
}
