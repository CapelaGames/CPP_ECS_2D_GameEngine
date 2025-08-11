#pragma once

#include "Component.hpp"

class CCollision : public Component
{
  public:
    float radius = 1;

    CCollision() = default;
    CCollision(float r)
        : radius(r) {}
};
