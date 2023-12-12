#pragma once
#include <iostream>
#include <vector>
#include "GameObject.h"
#include "Map.h"

class GameRun {
private:
    int level;
    int gridSize = 10;
    int windowSize = 800;
    std::shared_ptr<std::vector<GameObject>> users = std::make_shared<std::vector<GameObject>>();
    std::shared_ptr<std::vector<GameObject>> bots = std::make_shared<std::vector<GameObject>>();
    std::shared_ptr<std::vector<GameObject>> walls = std::make_shared<std::vector<GameObject>>();
    std::shared_ptr<std::vector<GameObject>> projectiles = std::make_shared<std::vector<GameObject>>();

public:
    GameRun();

    void createMap();

    void reset() {}

    void makeMove(int x, int y) {}

    void run() {}
};

