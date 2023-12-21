#pragma once
#include "GameRun.h"
#include "Renderer.h"
#include "UserCommandHandler.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include "Tank.h"

class GameManager {
    UserCommandHandler commander;
    Renderer renderer;
    std::unique_ptr<GameRun> game = nullptr;
    int windowSize = 900;
    int gridSize = 10;
    int difficulty = 5;
    float unit = windowSize / 6;
    sf::RenderWindow window;
    GameRunningState runningState = Menu;

public:
    GameManager(int windowSize);

    void run();
    void pause();

private:
    void initWindow();
    void handleMenuInteractions(Command command);
    void startNewGame();
    void startNewGame(GameRun previousGame);

    void handlePause(Command command);
};

