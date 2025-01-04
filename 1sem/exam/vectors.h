#pragma once

struct Vector
{
    double x;
    double y;
};

double sqr (double x);

Vector Add (Vector v1, Vector v2);
Vector Sub (Vector v1, Vector v2);
Vector Mul (Vector v, double value);
Vector Div (Vector v, double value);

double Length (Vector v);
Vector Normalize (Vector v);
double Dist2 (Vector v1, Vector v2);

Vector operator + (Vector v1, Vector v2);
Vector operator - (Vector v1, Vector v2);
Vector operator * (Vector v, double val);
Vector operator / (Vector v, double val);
Vector operator + (Vector v);
Vector operator - (Vector v);

// #==============================================================# //

double sqr (double x) { return x*x; }

Vector Add (Vector v1, Vector v2)
{
    return Vector { v1.x + v2.x, v1.y + v2.y };
}

Vector Sub (Vector v1, Vector v2)
{
    return Vector { v1.x - v2.x, v1.y - v2.y };
}

Vector Mul (Vector v, double value)
{
    return Vector { v.x * value, v.y * value };
}

Vector Div (Vector v, double value)
{
    return Vector { v.x / value, v.y / value };
}

double Length (Vector v)
{
    return hypot (v.x, v.y);
}

Vector Normalize (Vector v)
{
    return Div (v, Length (v));
}

double Dist2 (Vector v1, Vector v2)
{
    return sqr (v1.x - v2.x) + sqr (v1.y - v2.y);
}

Vector operator + (Vector v1, Vector v2) { return Add (v1, v2);  }

Vector operator - (Vector v1, Vector v2) { return Sub (v1, v2);  }

Vector operator * (Vector v, double val) { return Mul (v, val);  }

Vector operator / (Vector v, double val) { return Div (v, val);  }

Vector operator + (Vector v)             { return Normalize (v); }

Vector operator - (Vector v)             { return Mul (v , -1);  }
