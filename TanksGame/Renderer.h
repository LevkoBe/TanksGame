// Renderer.h
#pragma once
#include "GameRun.h"
#include "FolderReader.h"
#include "GameState.h"
#include <SFML/Graphics.hpp>

class Renderer {
private:
    const double rotationSpeed = 5.0;
    const double movementSpeed = 5.0;
    int windowSize = 900;
    int gridSize = 10;
    int difficulty = 5;
    sf::Font font;
    sf::Text text;
    sf::Sprite backgroundSprite;
    sf::Sprite sprite;
    std::vector<sf::Sprite> users;
    std::vector<std::pair<int, int>> usersPositions;
    std::vector<sf::Sprite> bots;
    std::vector<std::pair<int, int>> botsPositions;
    std::vector<sf::Sprite> walls;
    std::vector<std::pair<int, int>> wallsPositions;
    std::vector<sf::Sprite> projectiles;
    std::vector<std::pair<int, int>> projectilesPositions;

public:
    Renderer(int windowSize);

    void renderMenu(sf::RenderWindow& window);
    void renderGame(sf::RenderWindow& window, GameState& gamestate);

private:
    void drawBackground(sf::RenderWindow& window);
    void renderGameObjects(sf::RenderWindow& window, const GameState& gamestate);

    void renderWalls(sf::RenderWindow& window, const std::shared_ptr<std::vector<GameObject>>& walls);
    void renderBots(sf::RenderWindow& window, const std::shared_ptr<std::vector<BotTank>>& bots);
    void renderUserTank(sf::RenderWindow& window, const std::shared_ptr<Tank>& userTank);
    void renderProjectiles(sf::RenderWindow& window, const std::shared_ptr<std::vector<Projectile>>& projectiles);

    void renderGameOverText(sf::RenderWindow& window, const std::string& textString, int xPos, int yPos, const sf::Color& textColor);
    void renderTextWithOutline(sf::Text& text, sf::RenderWindow& window, const sf::Color& outlineColor);

    void drawLabelWithButtons(sf::RenderWindow& window, const std::string& label, const sf::Font& font, int centerY, int height,
        const std::string& leftButtonText, const std::string& rightButtonText);
    void drawButton(sf::RenderWindow& window, const std::string& text, const sf::Font& font, const sf::Color& fillColor, float centerX, float centerY, int height);

};
