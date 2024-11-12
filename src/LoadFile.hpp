#pragma once

#include "Circle.hpp"
#include "Rectangle.hpp"
#include "Shape.hpp"
#include <algorithm>
#include <cctype>
#include <fstream>
#include <string>
#include <vector>

class LoadFile
{
  public:
    int windowHeight;
    int windowWidth;

    std::string font;
    int fontSize;
    float fontColour[3];

    std::vector<std::shared_ptr<Shape>> shapes;

    void Read(const std::string &filename);
};
