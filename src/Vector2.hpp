#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <array>
#include <cmath>
#include <iostream>

template <typename T>
class Vector2
{
  public:
    T x = 0, y = 0;

    Vector2() = default;
    Vector2(T x, T y) : x(x), y(y) {}
    Vector2(const sf::Vector2<T> &vec) : x(vec.x), y(vec.y) {}

    operator sf::Vector2<T>() { return sf::Vector2<T>(x, y); }

    T *data() { return &x; }
    float magnitude() { return std::sqrt(x * x + y * y); }
    Vector2 normalised()
    {
        float mag = magnitude();
        return mag == 0 ? Vector2(0, 0) : Vector2(x / mag, y / mag);
    }
    Vector2 &normalise()
    {
        *this = normalised();
        return *this;
    }
    std::array<T, 2> to_array() const { return {x, y}; }

    // Operators
    Vector2 operator+(const Vector2 &rhs) const { return {x + rhs.x, y + rhs.y}; }
    Vector2 operator-(const Vector2 &rhs) const { return {x - rhs.x, y - rhs.y}; }
    Vector2 operator*(const T &val) const { return {x * val, y * val}; }
    Vector2 operator*(const Vector2 &val) const { return {x * val.x, y * val.y}; }
    Vector2 operator/(const Vector2 &val) const { return {x / val.x, y / val.y}; }
    bool operator==(const Vector2 &rhs) const { return x == rhs.x && y == rhs.y; }
    bool operator!=(const Vector2 &rhs) const { return !(*this == rhs); }
    void operator+=(const Vector2 &rhs)
    {
        x += rhs.x;
        y += rhs.y;
    }
    Vector2 &operator=(const Vector2 &v)
    {
        if (this != &v)
        {
            x = v.x;
            y = v.y;
        }
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &os, const Vector2 &v)
    {
        return os << "(" << v.x << "," << v.y << ")";
    }
    friend std::istream &operator>>(std::istream &is, Vector2 &v)
    {
        return is >> v.x >> v.y;
    }
};

using float2 = Vector2<float>;
using int2 = Vector2<int>;
