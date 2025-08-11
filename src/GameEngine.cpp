#include "GameEngine.h"
#include "imgui/imgui.h"
#include <iostream>

void GameEngine::init(const std::string &path)
{
    m_config.Read("config.txt");

    uint wWidth = m_config.windowWidth;
    uint wHeight = m_config.windowHeight;

    m_window.create(sf::VideoMode({wWidth, wHeight}), "liminal2D_Engine");
    m_window.setFramerateLimit(m_config.refreshRate);

    if (!ImGui::SFML::Init(m_window))
    {
        std::cerr << "ImGui-SFML init failed\n";
        return;
    }

    ImGui::GetStyle().ScaleAllSizes(1.0f);
    ImGui::GetIO().FontGlobalScale = 1.0f;

    spawnPlayer();
}

void GameEngine::run()
{
    // TODO: Pause functionality
    while (m_running)
    {
        m_entities.update();

        ImGui::SFML::Update(m_window, m_deltaTime.restart());
        sEnemySpawner();
        sMovement();
        sCollision();
        sUserInput();
        sGUI();
        sRender();
        m_currentFrame++;
    }
}

std::shared_ptr<Entity> GameEngine::player()
{
    auto &players = m_entities.getEntities("player");
    return players.front();
}

void GameEngine::spawnPlayer()
{
    auto entity = m_entities.addEntity("player");

    entity->add<CTransform>(float2(200.0f, 200.0f), float2(0.0f, 0.0f), 0.0f);
    entity->add<CShape>(m_config.player.shapeRadius,
                        m_config.player.vertCount,
                        sf::Color(m_config.player.fillColour[0],
                                  m_config.player.fillColour[1],
                                  m_config.player.fillColour[2]),
                        sf::Color(m_config.player.outlineColour[0],
                                  m_config.player.outlineColour[1],
                                  m_config.player.outlineColour[2]),
                        m_config.player.outlineThickness);
    entity->add<CInput>();
}

void GameEngine::spawnEnemy()
{
    auto entity = m_entities.addEntity("enemy");
    entity->add<CTransform>(float2(400.0f, 400.0f), float2(1.0f, 1.0f), 0.0f);
    entity->add<CShape>(m_config.enemy.shapeRadius,
                        m_config.enemy.minVertCount,
                        sf::Color(255, 255, 255),
                        sf::Color(m_config.enemy.outlineColour[0],
                                  m_config.enemy.outlineColour[1],
                                  m_config.enemy.outlineColour[2]),
                        m_config.enemy.outlineThickness);
}

void GameEngine::spawnSmallEnemies(std::shared_ptr<Entity> e)
{
    // TODO:
}

void GameEngine::spawnBullet(std::shared_ptr<Entity> entity, const float2 &target)
{
    // TODO:
}

void GameEngine::spawnSpecialWeapon(std::shared_ptr<Entity> entity)
{
    // TODO:
}

void GameEngine::sMovement()
{
    // TODO:

    auto &transform = player()->get<CTransform>();
    transform.pos += transform.velocity;
}
void GameEngine::sLifespan()
{
    // TODO:
}

void GameEngine::sCollision()
{
    // TODO:
    for (auto bullet : m_entities.getEntities("bullet"))
    {

        for (auto enemy : m_entities.getEntities("enemy"))
        {
        }

        for (auto enemy : m_entities.getEntities("smallEnemy"))
        {
        }
    }
}

void GameEngine::sEnemySpawner()
{
    // TODO:

    if (5.0f + m_lastEnemySpawnTime < m_time.getElapsedTime().asSeconds())
    {
        spawnEnemy();
        m_lastEnemySpawnTime = m_time.getElapsedTime().asSeconds();
    }
}

void GameEngine::sGUI()
{
    ImGui::Begin("Geometry Wars");
    for (auto &e : m_entities.getEntities())
    {
        ImGui::Text("%s", e->tag().data());
    }
    // ImGui::Combo("Shape", &shapeIndex, shapeNames.data(), (int)shapeNames.size());
    // ImGui::SliderFloat("Scale", &file.shapes[shapeIndex]->scale, 0, 5);
    // ImGui::SliderFloat2("Velocity", file.shapes[shapeIndex]->speed.data(), -5, 5);
    // ImGui::Checkbox("Draw shape", &file.shapes[shapeIndex]->draw);

    // float colourF[3] = {
    //     file.shapes[shapeIndex]->colour[0] / 255.0f,
    //     file.shapes[shapeIndex]->colour[1] / 255.0f,
    //     file.shapes[shapeIndex]->colour[2] / 255.0f};

    // if (ImGui::ColorEdit3("Colour", colourF))
    // {
    //     // Convert back to 0–255
    //     file.shapes[shapeIndex]->colour[0] = static_cast<int>(colourF[0] * 255);
    //     file.shapes[shapeIndex]->colour[1] = static_cast<int>(colourF[1] * 255);
    //     file.shapes[shapeIndex]->colour[2] = static_cast<int>(colourF[2] * 255);
    // }

    // char buffer[255];
    // std::strncpy(buffer, file.shapes[shapeIndex]->name.c_str(), sizeof(buffer));
    // if (ImGui::InputText("Name", buffer, 255))
    // {
    //     file.shapes[shapeIndex]->name = buffer;
    // }
    ImGui::End();
}

void GameEngine::sRender()
{
    m_window.clear();

    for (auto &e : m_entities.getEntities())
    {
        if (e->has<CShape>() && e->has<CTransform>())
        {
            e->get<CShape>().shape.setPosition(e->get<CTransform>().pos);
            e->get<CTransform>().angle += 1.0f;
            e->get<CShape>().shape.setRotation(sf::degrees(e->get<CTransform>().angle));

            m_window.draw(e->get<CShape>().shape);
        }
    }
    ImGui::SFML::Render(m_window);
    m_window.display();
}

void GameEngine::sUserInput()
{
    // TODO:
    while (auto event = m_window.pollEvent())
    {
        ImGui::SFML::ProcessEvent(m_window, *event);

        if (event->is<sf::Event::Closed>())
        {
            m_running = false;
        }

        if (auto keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            switch (keyPressed->code)
            {
            case sf::Keyboard::Key::W:
                std::cout << "W pressed\n";
                break;
            default:
                break;
            }
        }

        if (auto keyReleased = event->getIf<sf::Event::KeyReleased>())
        {
            switch (keyReleased->code)
            {
            case sf::Keyboard::Key::W:
                std::cout << "W released\n";
                break;
            default:
                break;
            }
        }

        if (auto mousePressed = event->getIf<sf::Event::MouseButtonPressed>())
        {
            if (ImGui::GetIO().WantCaptureMouse)
            {
                continue;
            }

            if (mousePressed->button == sf::Mouse::Button::Left)
            {
                std::cout << "left pressed at " << mousePressed->position.x << " " << mousePressed->position.y << std::endl;
            }

            if (mousePressed->button == sf::Mouse::Button::Right)
            {
                std::cout << "right pressed at " << mousePressed->position.x << " " << mousePressed->position.y << std::endl;
            }
        }
    }
}
