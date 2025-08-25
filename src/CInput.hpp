#pragma once

#include "Component.hpp"
#include "Vector2.hpp"

class CInput : public Component
{
  public:
    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;
    bool shoot = false;
    bool alt = false;

    CInput() = default;

    float2 moveInput()
    {
        float2 input = float2(-left + right, up + -down);

        // Correct input for stick diagonal values
        if (input.x != 0.f || input.y != 0.f)
        {
            float length = std::sqrt(input.x * input.x + input.y * input.y);
            input.x /= length;
            input.y /= length;
        }
        return input;
    }
};
