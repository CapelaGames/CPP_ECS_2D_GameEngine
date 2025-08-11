#pragma once

#include "Component.hpp"

class CScore : public Component
{
  public:
    int score = 0;

    CScore() = default;
    CScore(int s)
        : score(s) {}
};
