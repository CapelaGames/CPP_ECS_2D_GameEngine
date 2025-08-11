#pragma once

#include "Component.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>

class CShape : public Component
{
  public:
    sf::CircleShape shape;

    CShape() = default;
    CShape(float radius, size_t points, const sf::Color &fill, const sf::Color &outline, float thickness)
        : shape(radius, points)
    {
        shape.setFillColor(fill);
        shape.setOutlineColor(outline);
        shape.setOutlineThickness(thickness);
        shape.setOrigin(sf::Vector2f(radius, radius));
    }
};
