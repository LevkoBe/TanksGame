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
    std::shared_ptr<std::vector<GameObject>> walls = std::make_shared<std::vector<GameObject>>();
    std::shared_ptr<std::vector<Projectile>> projectiles = std::make_shared<std::vector<Projectile>>();

public:
    GameRun(int windowSize, int gridSize, int difficulty);

    void createMap();

    void reset() {}

    void processCommands(std::vector<Command> commands) {
        for (auto& command : commands)
        {
            switch (command)
            {
            case ScaleUp:
                changeSize(1.1);
                break;
            case ScaleDown:
                changeSize(0.9);
                break;
            case RotateClockWise:
                userTank->rotate(0.1);
                break;
            case RotateCounterClockWise:
                userTank->rotate(-0.1);
                break;
            case MoveForward:
                setSpeed(1);
                break;
            case MoveBackward:
                setSpeed(-1);
                break;
            default:
                break;
            }
        }
    }

    void update(std::vector<Command> commands) {
        processCommands(move(commands));
        moveUserTank();
        // todo: move projectiles
        // todo: move bots
    }

    GameState positions() {
        GameState state;
        state.userTankPosition = userTank->getPos();
        state.walls = walls;
        state.bots = bots;
        state.projectiles = projectiles;
        return state;
    }

    void setSpeed(int extent) {
        switch (mode)
        {
        case LeftUpRightDown:
            break;
        case RotatePosition:
            break;
        case RotateVelocity:
            break;
        case RotateAcceleration:
            userTank->accelerate(extent);
        default:
            break;
        }
    }

    void moveUserTank() { // todo: nullify when collision
        userTank->speedUp(userTank->getAcceleration()); // todo: check coefficients system
        int xExpected = userTank->getPos().first + userTank->getVel().first;
        int yExpected = userTank->getPos().second + userTank->getVel().second;
        bool stopTheTank = false;

        if (!insideGameField(xExpected, yExpected)) { return; }

        for (auto& wall : *walls)
        { // collisions with walls
            if (squareCircleColliding(wall.getPos().first, wall.getPos().second, wall.getSize(), xExpected, yExpected, userTank->getSize() / 2))
            {
                stopTheTank = true;
            }
        }

        for (auto& bot : *bots)
        { // collisions with bots
            if (circlesColliding(bot.getPos().first, bot.getPos().second, bot.getSize(), xExpected, yExpected, userTank->getSize() / 2))
            {
                stopTheTank = true;
            }
        }

        for (auto& projectile : *projectiles)
        { // collisions with projectiles
            if (circlesColliding(projectile.getPos().first, projectile.getPos().second, projectile.getSize(), xExpected, yExpected, userTank->getSize() / 2))
            {
                if (projectile.destroyObject(*userTank)) {
                    std::cout << "Game over!" << std::endl;
                }
            }
        }

        if (stopTheTank)
        {
            userTank->speedUp(-userTank->getSpeed() / userTank->getChange());
        }
        
        // max speed
    }



    bool circlesColliding(int x1, int y1, int radius1, int x2, int y2, int radius2) {
        
        int distance = std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
        return distance < (radius1 + radius2);
    }

    bool squareCircleColliding(double squareX, double squareY, double squareSize, double circleX, double circleY, double circleRadius) {
        
        double closestX = std::max(squareX - squareSize / 2.0, std::min(circleX, squareX + squareSize / 2.0));
        double closestY = std::max(squareY - squareSize / 2.0, std::min(circleY, squareY + squareSize / 2.0));

        double distance = std::sqrt(std::pow(closestX - circleX, 2) + std::pow(closestY - circleY, 2));
        return distance < circleRadius;
    }

    bool squareCircleColliding(int squareX, int squareY, int squareSize, int circleX, int circleY, int circleRadius) {
        double sqX = static_cast<double>(squareX);
        double sqY = static_cast<double>(squareY);
        double sqS = static_cast<double>(squareSize);
        double crX = static_cast<double>(circleX);
        double crY = static_cast<double>(circleY);
        double crR = static_cast<double>(circleRadius);
        return squareCircleColliding(sqX, sqY, sqS, crX, crY, crR);
    }


    bool insideGameField(int x, int y) const {
        return x > 0 && y > 0 && x < windowSize && y < windowSize;
    }

    void changeSize(double increase) {
        // todo: check if smaller than a cell;
        userTank->scale(increase);
    }

    void run() {}
};

