#include "LoadFile.hpp"
#include <memory>

void LoadFile::Read(const std::string &filename)
{
    shapes.clear();

    std::ifstream fin(filename);
    std::string type;

    if (!fin.is_open())
    {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    while (fin >> type)
    {
        std::transform(type.begin(), type.end(), type.begin(), [](unsigned char c)
                       { return std::tolower(c); });

        if (type == "window")
        {
            fin >> windowWidth >> windowHeight;
        }
        else if (type == "font")
        {
            fin >> font >> fontSize >> fontColour[0] >> fontColour[1] >> fontColour[2];
        }
        else if (type == "rectangle")
        {
            std::shared_ptr<Rectangle> shape = std::make_shared<Rectangle>();
            fin >> shape->name >> shape->startingPosition >> shape->startingSpeed >> shape->colour[0] >> shape->colour[1] >> shape->colour[2] >> shape->size;
            shapes.push_back(shape);
        }
        else if (type == "circle")
        {
            std::shared_ptr<Circle> shape = std::make_shared<Circle>();
            fin >> shape->name >> shape->startingPosition >> shape->startingSpeed >> shape->colour[0] >> shape->colour[1] >> shape->colour[2] >> shape->radius;
            shapes.push_back(shape);
        }
    }
}
