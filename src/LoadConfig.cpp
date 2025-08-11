#include "LoadConfig.h"

void LoadConfig::Read(const std::string &filename)
{
    std::ifstream fin(filename);
    if (!fin.is_open())
    {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    enum class Section
    {
        None,
        Window,
        Font,
        Player,
        Enemy,
        Bullet,
    };

    Section currentSection = Section::None;

    std::string line;
    int multilineLineCount = 0; // to track multiline data per section

    while (std::getline(fin, line))
    {
        // Trim leading whitespace
        size_t firstNonSpace = line.find_first_not_of(" \t");
        if (firstNonSpace == std::string::npos)
            continue; // skip empty lines

        std::string trimmedLine = line.substr(firstNonSpace);

        if (trimmedLine.rfind("//", 0) == 0)
            continue; // skip comments

        auto lowerLine = toLower(trimmedLine);

        // Check if line starts with section keyword:
        if (lowerLine.compare(0, 6, "window") == 0) // 6 = length of "window"
        {
            trimmedLine = trimmedLine.substr(6);
            currentSection = Section::Window;
        }
        else if (lowerLine.compare(0, 4, "font") == 0)
        {
            trimmedLine = trimmedLine.substr(4);
            currentSection = Section::Font;
        }
        else if (lowerLine.compare(0, 6, "player") == 0)
        {
            currentSection = Section::Player;
            multilineLineCount = 0;
            continue;
        }
        else if (lowerLine.compare(0, 5, "enemy") == 0)
        {
            currentSection = Section::Enemy;
            multilineLineCount = 0;
            continue;
        }
        else if (lowerLine.compare(0, 6, "bullet") == 0)
        {
            currentSection = Section::Bullet;
            multilineLineCount = 0;
            continue;
        }
        std::istringstream iss(trimmedLine);

        switch (currentSection)
        {
        case Section::Window:
        {
            iss >> windowWidth >> windowHeight >> refreshRate >> fullScreen;
            currentSection = Section::None; // done reading Window
            break;
        }
        case Section::Font:
        {
            // fontPath fontSize R G B
            iss >> font >> fontSize >> fontColour[0] >> fontColour[1] >> fontColour[2];
            currentSection = Section::None; // done reading Font
            break;
        }

        case Section::Player:
        {
            switch (multilineLineCount)
            {
            case 0:
                iss >> player.shapeRadius;
                break;
            case 1:
                iss >> player.collisionRadius;
                break;
            case 2:
                iss >> player.speed;
                break;
            case 3:
                iss >> player.fillColour[0] >> player.fillColour[1] >> player.fillColour[2];
                break;
            case 4:
                iss >> player.outlineColour[0] >> player.outlineColour[1] >> player.outlineColour[2];
                break;
            case 5:
                iss >> player.outlineThickness;
                break;
            case 6:
                iss >> player.vertCount;
                currentSection = Section::None; // done reading Player
                break;
            }
            multilineLineCount++;
            break;
        }
        case Section::Enemy:
        {
            switch (multilineLineCount)
            {
            case 0:
                iss >> enemy.shapeRadius;
                break;
            case 1:
                iss >> enemy.collisionRadius;
                break;
            case 2:
                iss >> enemy.minSpeed >> enemy.maxSpeed;
                break;
            case 3:
                iss >> enemy.outlineColour[0] >> enemy.outlineColour[1] >> enemy.outlineColour[2];
                break;
            case 4:
                iss >> enemy.outlineThickness;
                break;
            case 5:
                iss >> enemy.minVertCount >> enemy.maxVertCount;
                break;
            case 6:
                iss >> enemy.smallLifespan;
                break;
            case 7:
                iss >> enemy.interval;
                currentSection = Section::None; // done reading Enemy
                break;
            }
            multilineLineCount++;
            break;
        }
        case Section::Bullet:
        {
            switch (multilineLineCount)
            {
            case 0:
                iss >> bullet.shapeRadius;
                break;
            case 1:
                iss >> bullet.collisionRadius;
                break;
            case 2:
                iss >> bullet.speed;
                break;
            case 3:
                iss >> bullet.fillColour[0] >> bullet.fillColour[1] >> bullet.fillColour[2];
                break;
            case 4:
                iss >> bullet.outlineColour[0] >> bullet.outlineColour[1] >> bullet.outlineColour[2];
                break;
            case 5:
                iss >> bullet.outlineThickness;
                break;
            case 6:
                iss >> bullet.vertCount;
                break;
            case 7:
                iss >> bullet.lifespan;
                currentSection = Section::None; // done reading Bullet
                break;
            }
            multilineLineCount++;
            break;
        }
        default:
            break;
        }
    }
}

void LoadConfig::DebugPrint() const
{
    std::cout << "--- Config Debug ---\n";

    std::cout << "Window:\n";
    std::cout << "  Width: " << windowWidth << "\n";
    std::cout << "  Height: " << windowHeight << "\n";
    std::cout << "  Refresh Rate: " << refreshRate << "\n";
    std::cout << "  Full Screen: " << (fullScreen ? "Yes" : "No") << "\n";

    std::cout << "Font:\n";
    std::cout << "  Path: " << font << "\n";
    std::cout << "  Size: " << fontSize << "\n";
    std::cout << "  Colour: " << fontColour[0] << ", " << fontColour[1] << ", " << fontColour[2] << "\n";

    std::cout << "Player:\n";
    std::cout << "  Shape Radius: " << player.shapeRadius << "\n";
    std::cout << "  Collision Radius: " << player.collisionRadius << "\n";
    std::cout << "  Speed: " << player.speed << "\n";
    std::cout << "  Fill Colour: " << player.fillColour[0] << ", " << player.fillColour[1] << ", " << player.fillColour[2] << "\n";
    std::cout << "  Outline Colour: " << player.outlineColour[0] << ", " << player.outlineColour[1] << ", " << player.outlineColour[2] << "\n";
    std::cout << "  Outline Thickness: " << player.outlineThickness << "\n";
    std::cout << "  Vert Count: " << player.vertCount << "\n";

    std::cout << "Enemy:\n";
    std::cout << "  Shape Radius: " << enemy.shapeRadius << "\n";
    std::cout << "  Collision Radius: " << enemy.collisionRadius << "\n";
    std::cout << "  Min Speed: " << enemy.minSpeed << "\n";
    std::cout << "  Max Speed: " << enemy.maxSpeed << "\n";
    std::cout << "  Outline Colour: " << enemy.outlineColour[0] << ", " << enemy.outlineColour[1] << ", " << enemy.outlineColour[2] << "\n";
    std::cout << "  Outline Thickness: " << enemy.outlineThickness << "\n";
    std::cout << "  Min Vert Count: " << enemy.minVertCount << "\n";
    std::cout << "  Max Vert Count: " << enemy.maxVertCount << "\n";
    std::cout << "  Small Lifespan: " << enemy.smallLifespan << "\n";
    std::cout << "  Spawn Interval: " << enemy.interval << "\n";

    std::cout << "Bullet:\n";
    std::cout << "  Shape Radius: " << bullet.shapeRadius << "\n";
    std::cout << "  Collision Radius: " << bullet.collisionRadius << "\n";
    std::cout << "  Speed: " << bullet.speed << "\n";
    std::cout << "  Fill Colour: " << bullet.fillColour[0] << ", " << bullet.fillColour[1] << ", " << bullet.fillColour[2] << "\n";
    std::cout << "  Outline Colour: " << bullet.outlineColour[0] << ", " << bullet.outlineColour[1] << ", " << bullet.outlineColour[2] << "\n";
    std::cout << "  Outline Thickness: " << bullet.outlineThickness << "\n";
    std::cout << "  Vert Count: " << bullet.vertCount << "\n";
    std::cout << "  Lifespan: " << bullet.lifespan << "\n";

    std::cout << "---------------------\n";
}
