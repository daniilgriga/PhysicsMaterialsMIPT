#pragma once

struct Vector
{
    double x;
    double y;
};

double sqr (double x);

Vector Add (const Vector& v1, const Vector& v2);
Vector Sub (const Vector& v1, const Vector& v2);
Vector Mul (const Vector& v, double value);
Vector Div (const Vector& v, double value);

double Length (const Vector& v);
Vector Normalize (const Vector& v);
double Dist2 (const Vector& v1, const Vector& v2);

Vector operator + (const Vector& v1, const Vector& v2);
Vector operator - (const Vector& v1, const Vector& v2);
Vector operator * (const Vector& v, double val);
Vector operator / (const Vector& v, double val);
Vector operator + (const Vector& v);
Vector operator - (const Vector& v);

// #==============================================================# //

double sqr (double x) { return x*x; }

Vector Add (const Vector& v1, const Vector& v2)
{
    return Vector { v1.x + v2.x, v1.y + v2.y };
}

Vector Sub (const Vector& v1, const Vector& v2)
{
    return Vector { v1.x - v2.x, v1.y - v2.y };
}

Vector Mul (const Vector& v, double value)
{
    return Vector { v.x * value, v.y * value };
}

Vector Div (const Vector& v, double value)
{
    return Vector { v.x / value, v.y / value };
}

double Length (const Vector& v)
{
    return hypot (v.x, v.y);
}

Vector Normalize (const Vector& v)
{
    return Div (v, Length (v));
}

double Dist2 (const Vector& v1, const Vector& v2)
{
    return sqr (v1.x - v2.x) + sqr (v1.y - v2.y);
}

Vector operator + (const Vector& v1, const Vector& v2) { return Add (v1, v2);  }

Vector operator - (const Vector& v1, const Vector& v2) { return Sub (v1, v2);  }

Vector operator * (const Vector& v,  double val)       { return Mul (v, val);  }

Vector operator / (const Vector& v,  double val)       { return Div (v, val);  }

Vector operator + (const Vector& v)                    { return Normalize (v); }

Vector operator - (const Vector& v)                    { return Mul (v , -1);  }
