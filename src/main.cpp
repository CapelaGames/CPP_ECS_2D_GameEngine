#include "Circle.hpp"
#include "LoadFile.hpp"
#include "Rectangle.hpp"
#include "Shape.hpp"
#include "imgui-SFML.h"
#include "imgui.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <algorithm>
#include <iostream>
#include <memory>

int main(int argc, char *argv[])
{
    LoadFile file;
    file.windowHeight = 0;
    file.Read("shapes.txt");

    const int wWidth = file.windowWidth;
    const int wHeight = file.windowHeight;
    sf::RenderWindow window(sf::VideoMode(wWidth, wHeight), "SFML works!");
    window.setFramerateLimit(60);

    ImGui::SFML::Init(window);
    sf::Clock deltaClock;

    ImGui::GetStyle().ScaleAllSizes(1.0f);

    std::vector<const char *> shapeNames;
    for (auto shape : file.shapes)
    {
        if (std::shared_ptr<Circle> circle = std::static_pointer_cast<Circle>(shape))
        {
            circle->shape = std::make_shared<sf::CircleShape>(circle->radius, circle->circleSegments);
            circle->shape->setPosition(circle->startingPosition.x, circle->startingPosition.y);
        }
        else if (std::shared_ptr<Rectangle> rectangle = std::static_pointer_cast<Rectangle>(shape))
        {
            rectangle->shape = std::make_shared<sf::RectangleShape>(sf::Vector2f(rectangle->size.x, rectangle->size.y));
            rectangle->shape->setPosition(rectangle->startingPosition.x, rectangle->startingPosition.y);
        }

        shapeNames.push_back(shape->name.c_str());
    }
    sf::Font myFont;

    if (!myFont.loadFromFile("fonts/Roboto-Regular.ttf"))
    {
        std::cerr << "Could not load font!" << std::endl;
        exit(-1);
    }

    sf::Text text("Sample Text", myFont, 24);

    text.setPosition(0, wHeight - (float)text.getCharacterSize());

    char displayString[255] = "Sample Text";

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(window, event);

            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed)
            {
                // std::cout << "Key pressed with code = " << event.key.code << std::endl;

                if (event.key.code == sf::Keyboard::X)
                {
                    // circleSpeedX *= -1.0f;
                }
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::Begin("Window title");
        ImGui::Text("Window text");

        static int comboCurrentItem = 0;
        ImGui::Combo("Shape", &comboCurrentItem, shapeNames.data(), shapeNames.size());

        ImGui::Checkbox("Draw Shape", &file.shapes[comboCurrentItem]->draw);
        ImGui::SameLine();
        ImGui::Checkbox("Draw Circle", &file.shapes[comboCurrentItem]->drawName);
        float scale = 0;
        ImGui::SliderFloat("Radius", &scale, 0.0f, 300.0f);

        ImGui::ColorEdit3("Color Circle", file.shapes[comboCurrentItem]->colour);
        ImGui::InputText("Text", displayString, 255);
        if (ImGui::Button("Set Text"))
        {
            text.setString(displayString);
        }
        ImGui::SameLine();
        // if (ImGui::Button("Reset Circle"))
        // {
        //     circle.setPosition(0, 0);
        // }
        ImGui::End();

        for (auto shape : file.shapes)
        {
            shape->shape->setFillColor(sf::Color(shape->colour[0] * 255, shape->colour[1] * 255, shape->colour[2] * 255));

            if (std::shared_ptr<sf::CircleShape> circle = std::static_pointer_cast<sf::CircleShape>(shape->shape))
            {
                std::shared_ptr<Circle> circleWrapper = std::static_pointer_cast<Circle>(shape);
                circle->setPointCount(32);
                circle->setRadius(circleWrapper->radius);
            }

            shape->shape->setPosition(shape->shape->getPosition().x + shape->startingSpeed.x, shape->shape->getPosition().y + shape->startingSpeed.y);

            window.clear();
            if (shape->draw)
            {
                window.draw(*shape->shape);
            }
            if (shape->drawName)
            {
                window.draw(text);
            }
        }
        ImGui::SFML::Render(window);
        window.display();
    }
    return 0;
}
