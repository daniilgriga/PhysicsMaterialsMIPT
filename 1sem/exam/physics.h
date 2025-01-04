#pragma once

#include "vectors.h"

const double KM = 1e3;
const double KG = 1;
const double  S = 1;

const double dT = 1e3;

const double DIST_EARTH_MOON = 384000*KM;
const double DIST_EARTH_CM   = 4671*KM;

const double MASS_EARTH   = 5.9700e24*KG;
const double MASS_MOON    = 0.0735e24*KG;
const double MASS_COMET   = 600*KG;

const int RAD_EARTH   = 6400*KM;
const int RAD_MOON    = 1737*KM;
const int RAD_COMET   = 600*KM;

const double MOON_SPEED  = 1.022 * KM/S;
const double EARTH_SPEED = 0.0125* KM/S;

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

Vector Gravity (const MassPoint& Point_1, const MassPoint& Point_2);

Vector CentrifugalForce (const MassPoint& Point, const MassPoint& centre);

void Kinematics (MassPoint* Point, const Vector& Force);

// #==================================================================================# //

Vector Gravity (const MassPoint& Point_1, const MassPoint& Point_2)
{
    double Force  = GRAVITY_CONST * Point_1.m * Point_2.m / Dist2 (Point_1.pos, Point_2.pos);

    Vector ForceV = +(Point_1.pos - Point_2.pos) * Force;

    return ForceV;
}

Vector CentrifugalForce (const MassPoint& Point, const MassPoint& centre)
{
    double Velocity = MOON_SPEED * Length (Point.pos) / DIST_EARTH_MOON;

    double CentrifugalForce = Point.m * sqr (Velocity) / Length (Point.pos - centre.pos);

    Vector CentrifugalForceV = +Point.pos * CentrifugalForce;

    return CentrifugalForceV;
}

void Kinematics (MassPoint* Point, const Vector& Force)
{
    Point->a   = Force / Point->m;
    Point->v   = Point->v   + Point->a * dT;
    Point->pos = Point->pos + Point->v * dT;
}
