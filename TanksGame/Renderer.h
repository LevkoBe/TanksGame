#pragma once
#include "GameRun.h"
#include "FolderReader.h"
#include "GameState.h"
#include <SFML/Graphics.hpp>



class Renderer {
private:
    const double rotationSpeed = 5.0;
    const double movementSpeed = 5.0;
    const int windowSize = 800;
    sf::Font font;
    sf::Text text;  // todo: text.setString(userInput);
    sf::Sprite backgroundSprite;
    sf::Sprite sprite;
    std::vector<sf::Sprite> users; // expl: at first we pack here all sprites, then gradually delete each destroyed.
    std::vector<std::pair<int, int>> usersPositions = std::vector<std::pair<int, int>>(); // todo: tuple -> angles, size
    std::vector<sf::Sprite> bots;
    std::vector<std::pair<int, int>> botsPositions = std::vector<std::pair<int, int>>(); // todo: tuple -> angles, size
    std::vector<sf::Sprite> walls;
    std::vector<std::pair<int, int>> wallsPositions = std::vector<std::pair<int, int>>(); // extra: cracks
    std::vector<sf::Sprite> projectiles;
    std::vector<std::pair<int, int>> projectilesPositions = std::vector<std::pair<int, int>>(); // todo: tuple, size -> angles
    // todo: move positions from here to methods
public:
    Renderer(int windowSize);

    void render(sf::RenderWindow& window, GameState gamestate);
};
