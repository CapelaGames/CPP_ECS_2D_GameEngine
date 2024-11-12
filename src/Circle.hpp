
#pragma once

#include "Shape.hpp"
#include <SFML/Graphics/CircleShape.hpp>

class Circle : public Shape
{
  public:
    float radius = 50;
    int circleSegments = 32;
};
