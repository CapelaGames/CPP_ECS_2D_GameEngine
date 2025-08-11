#pragma once

#include "EntityManager.h"
#include "LoadConfig.h"
#include "Vector2.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <algorithm>
#include <cstring>
#include <memory>
#include <ostream>

#include "Entity.hpp"
#include "imgui/imgui-SFML.h"
#include "imgui/imgui.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

#include "CTransform.hpp"
#include "imgui/imgui-SFML.h"
#include "imgui/imgui.h"
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Angle.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

class GameEngine
{
    // int m_currentFrame;

    LoadConfig m_config;
    sf::RenderWindow m_window;
    EntityManager m_entities;
    sf::Font m_font;
    sf::Text m_text;
    sf::Clock m_time;
    sf::Clock m_deltaTime;
    int m_score = 0;
    int m_currentFrame = 0;
    int m_lastEnemySpawnTime = 0;
    bool m_paused = false;
    bool m_running = true;

    void init(const std::string &path);
    void setPaused(bool paused);
    // systems
    void sMovement();
    void sUserInput();
    void sLifespan();
    void sRender();
    void sGUI();
    void sEnemySpawner();
    void sCollision();

    void spawnPlayer();
    void spawnEnemy();
    void spawnSmallEnemies(std::shared_ptr<Entity> entity);
    void spawnBullet(std::shared_ptr<Entity> entity, const float2 &mousePos);
    void spawnSpecialWeapon(std::shared_ptr<Entity> entity);

    std::shared_ptr<Entity> player();

  public:
    GameEngine(const std::string &config)
        : m_text(sf::Text(m_font, "test", 10))
    {
        init(config);
    }

    void run();
};
