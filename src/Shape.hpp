#pragma once

#include "Float2.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <memory>
#include <string>

class Shape
{

  public:
    std::string name;
    Float2 startingPosition;
    Float2 startingSpeed;
    float colour[3];
    bool draw = true;
    bool drawName = true;
    std::shared_ptr<sf::Shape> shape;
};
