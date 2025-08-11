#pragma once

#include "Component.hpp"

class CInput : public Component
{
  public:
    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;
    bool shoot = false;

    CInput() = default;
};
