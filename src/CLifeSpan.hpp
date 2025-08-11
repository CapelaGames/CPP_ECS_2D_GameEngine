#pragma once

#include "Component.hpp"

class CLifeSpan : public Component
{
  public:
    int lifespan = 0;
    int remaining = 0;
    CLifeSpan() = default;
    CLifeSpan(int totalLifespan)
        : lifespan(totalLifespan),
          remaining(totalLifespan) {}
};
