#pragma once

#include "vectors.h"

const double KM = 1e3;
const double KG = 1;
const double  S = 1;

const double dT = 1e3;

struct MassPoint
{
    Vector pos;

    double m;
    double r;

    Vector v;
    Vector a;

    int valid;
};
