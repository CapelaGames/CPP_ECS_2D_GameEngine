#pragma once

#include "Shape.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Shape.hpp>

class Rectangle : public Shape
{
  public:
    Float2 size;
};
