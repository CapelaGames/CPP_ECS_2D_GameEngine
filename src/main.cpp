#include "GameEngine.h"
#include <SFML/Graphics.hpp>
int main()
{
    GameEngine g("config.txt");
    g.run();
}
// --------------------------------

/*
LoadFile file;
file.Read("shapes.txt");

uint wWidth = file.windowWidth;
uint wHeight = file.windowHeight;

sf::RenderWindow window(sf::VideoMode({wWidth, wHeight}), "liminal2D_Engine");
window.setFramerateLimit(144);
if (!ImGui::SFML::Init(window))
{
    std::cerr << "ImGui-SFML init failed\n";
    return -1;
}
sf::Clock deltaClock;

ImGui::GetStyle().ScaleAllSizes(1.0f);
ImGui::GetIO().FontGlobalScale = 1.0f;

std::cout << "getting read " << std::endl;
std::vector<const char *> shapeNames;
for (auto shape : file.shapes)
{
    std::cout << shape->name << std::endl;
    if (auto circle = std::dynamic_pointer_cast<Circle>(shape))
    {
        std::cout << "circle" << std::endl;
        circle->shape = std::make_shared<sf::CircleShape>(circle->radius, circle->circleSegments);
        circle->shape->setPosition({circle->startingPosition.x, circle->startingPosition.y});
    }
    else if (auto rectangle = std::dynamic_pointer_cast<Rectangle>(shape))
    {
        std::cout << "rectangle" << std::endl;
        rectangle->shape = std::make_shared<sf::RectangleShape>(sf::Vector2f(rectangle->size.x, rectangle->size.y));
        rectangle->shape->setPosition(sf::Vector2f(rectangle->startingPosition.x, rectangle->startingPosition.y));
    }
    std::cout << "push" << std::endl;
    shapeNames.push_back(shape->name.c_str());
}
std::cout << "end reading" << std::endl;

sf::Font font;
if (!font.openFromFile("fonts/Roboto-Regular.ttf"))
{
    std::cerr << "Font load failed\n";
    return -1;
}

int shapeIndex = 0;
while (window.isOpen())
{
    // SFML 3: pollEvent() returns std::optional<sf::Event>
    while (auto event = window.pollEvent())
    {
        // SFML 3: ImGui-SFML needs window reference here
        ImGui::SFML::ProcessEvent(window, *event);

        if (event->is<sf::Event::Closed>())
        {
            window.close();
        }

        if (auto keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            std::cout << "Key pressed with code = " << static_cast<int>(keyPressed->code) << "\n";

            if (keyPressed->code == sf::Keyboard::Key::X)
            {
                std::cout << "Key = X" << "\n";
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X))
        {
            std::cout << "Key2 = X" << "\n";
            // Do thing
        }
    }

    ImGui::SFML::Update(window, deltaClock.restart());
    ImGui::Begin("Debug Menu");
    ImGui::Text("Debugging");
    ImGui::Combo("Shape", &shapeIndex, shapeNames.data(), (int)shapeNames.size());
    ImGui::SliderFloat("Scale", &file.shapes[shapeIndex]->scale, 0, 5);
    ImGui::SliderFloat2("Velocity", file.shapes[shapeIndex]->speed.data(), -5, 5);
    ImGui::Checkbox("Draw shape", &file.shapes[shapeIndex]->draw);

    float colourF[3] = {
        file.shapes[shapeIndex]->colour[0] / 255.0f,
        file.shapes[shapeIndex]->colour[1] / 255.0f,
        file.shapes[shapeIndex]->colour[2] / 255.0f};

    if (ImGui::ColorEdit3("Colour", colourF))
    {
        // Convert back to 0–255
        file.shapes[shapeIndex]->colour[0] = static_cast<int>(colourF[0] * 255);
        file.shapes[shapeIndex]->colour[1] = static_cast<int>(colourF[1] * 255);
        file.shapes[shapeIndex]->colour[2] = static_cast<int>(colourF[2] * 255);
    }

    char buffer[255];
    std::strncpy(buffer, file.shapes[shapeIndex]->name.c_str(), sizeof(buffer));
    if (ImGui::InputText("Name", buffer, 255))
    {
        file.shapes[shapeIndex]->name = buffer;
    }

    ImGui::End();

    window.clear();

    for (auto shape : file.shapes)
    {
        auto position = shape->shape->getPosition();
        auto bounds = shape->shape->getGlobalBounds();
        float left = bounds.position.x;
        float right = bounds.position.x + bounds.size.x;
        float top = bounds.position.y;
        float bottom = bounds.position.y + bounds.size.y;
        if (left < 0)
            shape->speed.x *= -1;
        if (right > wWidth)
            shape->speed.x *= -1;
        if (top < 0)
            shape->speed.y *= -1;
        if (bottom > wHeight)
            shape->speed.y *= -1;

        shape->shape->setFillColor(sf::Color(shape->colour[0], shape->colour[1], shape->colour[2]));
        shape->shape->setPosition(shape->shape->getPosition() + sf::Vector2<float>(shape->speed.x, shape->speed.y));
        shape->shape->setScale(sf::Vector2<float>(shape->scale, shape->scale));
        if (shape->draw)
        {
            window.draw(*shape->shape);
        }
        sf::Text shapeText(font, shape->name, 10);
        auto textBounds = shapeText.getLocalBounds();
        shapeText.setOrigin(
            sf::Vector2f(
                textBounds.position.x + textBounds.size.x / 2.f,
                textBounds.position.y + textBounds.size.y / 2.f));
        bounds = shape->shape->getGlobalBounds();
        shapeText.setPosition(bounds.getCenter());
        sf::Color shapeColor = shape->shape->getFillColor();
        float brightness = 0.299f * shapeColor.r + 0.587f * shapeColor.g + 0.114f * shapeColor.b;
        if (brightness > 128)
        {
            shapeText.setFillColor(sf::Color::Black);
        }
        else
        {
            shapeText.setFillColor(sf::Color::White);
        }

        window.draw(shapeText);
    }
    ImGui::SFML::Render(window);
    window.display();
    */

// ImGui::SFML::Shutdown();
