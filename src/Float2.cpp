#include "Float2.hpp"
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <ostream>

Float2::Float2() {}

Float2::Float2(float x, float y) : x(x), y(y) {}

Float2 Float2::operator+(Float2 v)
{
    return Float2(x + v.x, y + v.y);
}

Float2 Float2::operator-(Float2 v)
{
    return Float2(x - v.x, y - v.y);
}

Float2 Float2::operator*(float s)
{
    return Float2(x * s, y * s);
}

float Float2::operator*(Float2 v)
{
    return (x * v.x) + (y * v.y);
}

bool Float2::operator==(Float2 v)
{
    return (x == v.x) && (y == v.y);
}

Float2 &Float2::operator=(const Float2 &v)
{
    if (this != &v)
    {
        x = v.x;
        y = v.y;
    }
    return *this;
}

std::ostream &operator<<(std::ostream &os, const Float2 &v)
{
    os << "(" << v.x << "," << v.y << ")";
    return os;
}

std::istream &operator>>(std::istream &is, Float2 &v)
{
    is >> v.x >> v.y;
    return is;
}

float Float2::magnitude()
{
    return sqrtf(x * x + y * y);
}

Float2 Float2::normalised()
{
    float mag = magnitude();
    if (mag == 0)
    {
        return Float2(0, 0);
    }
    return Float2(x / mag, y / mag);
}

Float2 &Float2::normalise()
{
    *this = normalised();
    return *this;
}

float Float2::distance(Float2 v)
{
    return (v - *this).magnitude();
}
