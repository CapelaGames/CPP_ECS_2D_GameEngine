#pragma once

#include "Component.hpp"
#include "Vector2.hpp"

class CTransform : public Component
{
  public:
    float2 pos = {0.0, 0.0};
    float2 velocity = {0.0, 0.0};
    float2 scale = {1.0, 1.0};
    float angle = 0;

    CTransform() = default;
    CTransform(const float2 &p, const float2 &v, float a)
        : pos(p),
          velocity(v),
          angle(a) {}
};
