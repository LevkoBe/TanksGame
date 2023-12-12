#pragma once
#include <iostream>
#include <vector>
#include "GameObject.h"
#include "Map.h"
#include "Tank.h"
#include "Commands.h" // todo: check if needed line

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
    Tank userTank;
    ControlMode mode = RotateAcceleration;
    std::shared_ptr<std::vector<GameObject>> bots = std::make_shared<std::vector<GameObject>>();
    std::shared_ptr<std::vector<GameObject>> walls = std::make_shared<std::vector<GameObject>>();
    std::shared_ptr<std::vector<GameObject>> projectiles = std::make_shared<std::vector<GameObject>>();

public:
    GameRun(int windowSize, int gridSize);

    void createMap();

    void reset() {}

    void update(std::vector<Command> commands) {
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
                userTank.rotate(0.1);
                break;
            case RotateCounterClockWise:
                userTank.rotate(-0.1);
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
            userTank.accelerate(extent);
        default:
            break;
        }
    }

    void move(int x, int y) { // todo: nullify when collision
        userTank.speedUp(userTank.getAcceleration()); // todo: check coefficients system
        int xExpected = userTank.getPos().first + userTank.getVel().first;
        int yExpected = userTank.getPos().second + userTank.getVel().second;

        if (!insideGameField(xExpected, yExpected)) { return; }

        for (auto& wall : *walls)
        {

        }
        // walls collisions
        // bots collisions
        // projectiles
        // max speed
    }

    bool circlesColliding(int x1, int y1, int radius1, int x2, int y2, int radius2) {
        
        int distance = std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));

        return distance < (radius1 + radius2);
    }

    bool checkSquareCircleCollision(double squareX, double squareY, double squareSize, double circleX, double circleY, double circleRadius) { // todo: review the algorithm
        // Find the closest point in the square to the circle
        double closestX = std::max(squareX - squareSize / 2.0, std::min(circleX, squareX + squareSize / 2.0));
        double closestY = std::max(squareY - squareSize / 2.0, std::min(circleY, squareY + squareSize / 2.0));

        // Calculate the distance between the closest point and the circle's center
        double distance = std::sqrt(std::pow(closestX - circleX, 2) + std::pow(closestY - circleY, 2));

        // If the distance is less than the circle's radius, collision occurs
        return distance < circleRadius;
    }


    bool insideGameField(int x, int y) const {
        return x > 0 && y > 0 && x < windowSize && y < windowSize;
    }

    void changeSize(double increase) {
        // todo: check if smaller than a cell;
        userTank.scale(increase);
    }

    void run() {}
};

