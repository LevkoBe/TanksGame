#pragma once
#include <iostream>
#include <tuple>

enum ObjectShape {
    Circle,
    Square
};

class GameObject {
protected:
    int xPos = 0;
    int yPos = 0;
    int xVel = 0;
    int yVel = 0;
    int xAcc = 0;
    int yAcc = 0;
    int size = 10;
    int maxSpeed = 100;
    int maxAccel = 10;
    int healthPoints = 100;
    int angle = 0;
    ObjectShape shape = Circle;

public:
    GameObject(int initialXPos, int initialYPos, int initialSize, int initialMaxSpeed, int initialMaxAccel, int angle, ObjectShape shape);

    std::tuple<int, int> getPos() const;

    std::tuple<int, int> getVel() const;

    std::tuple<int, int> getAcc() const;

    int getMaxSpeed() const;

    int getMaxAccel() const;
};