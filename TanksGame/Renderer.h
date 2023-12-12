#pragma once
#include "GameRun.h"
#include <SFML/Graphics.hpp>



class Renderer {
private:
    int windowSize = 800;
    float rotationAngle = 0.0f;
    const float rotationSpeed = 5.0f;
    const float movementSpeed = 5.0f;
    sf::RenderWindow window;
    sf::Font font;
    sf::Text text;
    sf::Texture texture;
    sf::Sprite sprite;
    std::string userInput = "";
    GameRun gamerun;

public:
    Renderer(int windowSize, GameRun gamerun);

    void run();

private:

    void initWindow();

    void update();

    void render();

    void processEvents();

    void handleTextEvent(sf::Event& event);

    void handleKeyEvent(sf::Event& event);

    void moveTankForward();
};
