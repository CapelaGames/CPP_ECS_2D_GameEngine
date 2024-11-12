#pragma once

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <ostream>

class Float2
{
  public:
    float x = 0;
    float y = 0;

    Float2();

    Float2(float x, float y);

    float magnitude();

    Float2 normalised();

    Float2 &normalise();

    float distance(Float2 v);

    Float2 operator+(Float2 v);

    Float2 operator-(Float2 v);

    Float2 operator*(float s);

    float operator*(Float2 v);

    bool operator==(Float2 v);

    Float2 &operator=(const Float2 &v);

    friend std::ostream &operator<<(std::ostream &os, const Float2 &v);

    friend std::istream &operator>>(std::istream &is, Float2 &v);
};
