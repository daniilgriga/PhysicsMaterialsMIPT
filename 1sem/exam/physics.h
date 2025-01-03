#pragma once

#include "vectors.h"

const double KM = 1e3;
const double KG = 1;
const double  S = 1;

const double dT = 1e3;

const double DIST_EARTH_MOON = 384000*KM;
const double MASS_EARTH   = 5.9700e24*KG;
const double MASS_MOON    = 0.0735e24*KG;
const double MASS_COMET   = 500*KG;

const int RAD_EARTH   = 6400*KM;
const int RAD_MOON    = 1737*KM;
const int RAD_COMET   = 900*KM;

const double GRAVITY_CONST = 6.67e-11;

struct MassPoint
{
    Vector pos;

    double m;
    double r;

    Vector v;
    Vector a;

    int valid;
};

Vector Gravity (MassPoint point_1, MassPoint point_2)
{
    double Force  = GRAVITY_CONST * point_1.m * point_2.m / Dist2 (point_1.pos, point_2.pos);

    Vector ForceV = +(point_1.pos - point_2.pos) * Force;

    return ForceV;
}
