#pragma once
#include <iostream>
#include <vector>
#include <tuple>
#include "GameObject.h"
#include "Map.h"
#include "Tank.h"
#include "Commands.h" // todo: check if needed line
#include "Projectile.h"
#include "GameState.h"


enum ControlMode {
    LeftUpRightDown,
    RotatePosition,
    RotateVelocity,
    RotateAcceleration
};

class GameRun {
private:
    int level;
    int windowSize = 800;
    int gridSize = 10;
    ControlMode mode = RotateAcceleration;
    std::shared_ptr<Tank> userTank;
    std::shared_ptr<std::vector<Tank>> bots = std::make_shared<std::vector<Tank>>();
    std::shared_ptr<std::vector<Tank>> allBots = std::make_shared<std::vector<Tank>>();
    std::shared_ptr<std::vector<GameObject>> walls = std::make_shared<std::vector<GameObject>>();
    std::shared_ptr<std::vector<Projectile>> projectiles = std::make_shared<std::vector<Projectile>>();
    std::shared_ptr<std::vector<std::vector<bool>>> wallsMap = std::make_shared<std::vector<std::vector<bool>>>(gridSize, std::vector<bool>(gridSize, false));

public:
    GameRun(int windowSize, int gridSize, int difficulty);

    void createMap();

    void reset() {}

    void processCommands(std::vector<Command> commands);

    GameState update(std::vector<Command> commands);

    GameState positions();

    void setSpeed(int extent);

    void moveUserTank();

    bool addBot(int position);

    bool circlesColliding(int x1, int y1, int radius1, int x2, int y2, int radius2);

    bool squareCircleColliding(double squareX, double squareY, double squareSize, double circleX, double circleY, double circleRadius);

    bool squareCircleColliding(int squareX, int squareY, int squareSize, int circleX, int circleY, int circleRadius);

    bool insideGameField(int x, int y) const;

    void changeSize(double increase);

    void run() {}
};

