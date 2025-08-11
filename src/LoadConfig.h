#pragma once

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>

class LoadConfig
{
  public:
    struct PlayerConfig
    {
        float shapeRadius;
        float collisionRadius;
        float speed;
        float fillColour[3];
        float outlineColour[3];
        float outlineThickness;
        int vertCount;
    };

    struct EnemyConfig
    {
        float shapeRadius;
        float collisionRadius;
        float minSpeed;
        float maxSpeed;
        float outlineColour[3];
        float outlineThickness;
        int minVertCount;
        int maxVertCount;
        float smallLifespan;
        float interval;
    };

    struct BulletConfig
    {
        float shapeRadius;
        float collisionRadius;
        float speed;
        float fillColour[3];
        float outlineColour[3];
        float outlineThickness;
        int vertCount;
        float lifespan;
    };

    // Window Settings
    uint windowHeight;
    uint windowWidth;
    uint refreshRate;
    bool fullScreen;

    // Font settings
    std::string font;
    int fontSize;
    float fontColour[3];

    PlayerConfig player;
    EnemyConfig enemy;
    BulletConfig bullet;

    void Read(const std::string &filename);
    void DebugPrint() const;
    static inline std::string toLower(const std::string &s)
    {
        std::string result = s;
        std::transform(result.begin(), result.end(), result.begin(), ::tolower);
        return result;
    }
    static std::string ltrim(const std::string &s)
    {
        size_t start = 0;
        while (start < s.size() && std::isspace((unsigned char)s[start]))
            start++;
        return s.substr(start);
    }
};
